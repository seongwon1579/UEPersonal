// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelper.h"
#include "Character/Player/Component/Activity/BoxingActivityInputComponent.h"
#include "GameFramework/Character.h"
#include "SubSystem/UISubSystem.h"
#include "SubSystem/StatSubsystem.h"

namespace
{
	constexpr EPunchDirection RandomDirections[] = {
		EPunchDirection::Left,
		EPunchDirection::Right,
		EPunchDirection::Up,
		EPunchDirection::Down
	};
}

// Sets default values for this component's properties
UBoxingActivityComponent::UBoxingActivityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBoxingActivityComponent::StartBoxing()
{
	if (!BoxingInputComponent)
	{
		Debug::Print("not bind to inputComponent");
		return;
	}
	BoxingInputComponent->EnableBoxingInput(true);
	
	bIsBoxing = true;
	SetABPBoxingState(true);
	AccumulatedStrength = 0;
	PatternLength = 3;
	
	if (MovementComponent)
	{
		MovementComponent->SetMovementMode(EMovementMode::MOVE_None);
	}

	if (UISubsystem)
	{
		UISubsystem->ShowBoxingPatternWidget(this);
	}

	OnShowPattern.Broadcast(EPunchDirection::Start);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		OnShowPattern.Broadcast(EPunchDirection::None);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]
		{
			GeneratePattern();
		}, 1.f, false);
	}, 1.f, false);
}


bool UBoxingActivityComponent::IsBoxing() const
{
	return bIsBoxing;
}

void UBoxingActivityComponent::OnPunchInput()
{
	if (!bIsBoxing || !bPatternCompleted) return;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	OnShowPattern.Broadcast(EPunchDirection::None);
	OnPatternSuccess();
}

void UBoxingActivityComponent::OnDirectionInput(EPunchDirection Input)
{
	// 이미 패턴이 끝났는데 입력이 추가로 들어온 경우
	if (CurrentPatternIndex >= CurrentPattern.Num())
	{
		OnPatternFail();
		return;
	}

	if (Input == CurrentPattern[CurrentPatternIndex])
	{
		CurrentPatternIndex++;

		if (CurrentPatternIndex >= CurrentPattern.Num())
		{
			bPatternCompleted = true;
		}
	}
	// 입력을 잘못 눌렀을 경우
	else
	{
		OnPatternFail();
	}
}

void UBoxingActivityComponent::GeneratePattern()
{
	bIsFail = false;
	CurrentPattern.Empty();
	bPatternCompleted = false;
	CurrentPatternIndex = 0;

	// 패턴 랜덤으로 생성
	for (int32 i = 0; i < PatternLength; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, 3);
		CurrentPattern.Add(RandomDirections[RandomIndex]);
	}
	OnPatternStart();
}

void UBoxingActivityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		MovementComponent = Character->GetCharacterMovement();
		AnimInstance = Character->GetMesh()->GetAnimInstance();
	}

	UISubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubSystem>();

	StatSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UStatSubsystem>();
	
	BoxingInputComponent = GetOwner()->GetComponentByClass<UBoxingActivityInputComponent>();
}

void UBoxingActivityComponent::OnPatternFail()
{
	//Debug::Print("Failed");
	bIsFail = true;
	SetABPBoxingState(false);
	UISubsystem->HideBoxingPatternWidget();
	bIsBoxing = false;

	AddReward();
	BoxingInputComponent->EnableBoxingInput(false);

	if (!AnimInstance) return;

	AnimInstance->Montage_Play(FailMontage, 2.5f);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UBoxingActivityComponent::OnFailAnimEnded);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, FailMontage);
}

void UBoxingActivityComponent::OnPunchAnimEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AccumulatedStrength++;
	PatternLength++;
	GeneratePattern();
}

void UBoxingActivityComponent::OnFailAnimEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!MovementComponent) return;

	MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UBoxingActivityComponent::OnPatternStart()
{
	PatternDisplayIndex = 0;
	OnPatternDisplay();
}

void UBoxingActivityComponent::OnPatternDisplay()
{
	// 종료조건 1. 키입력 실패한 경우
	if (bIsFail) return;

	// 종료조건 2. 키입력을 모두 끝낸 경우
	if (PatternDisplayIndex >= CurrentPattern.Num())
	{
		OnShowPattern.Broadcast(EPunchDirection::Punch);

		// 펀치 UI 지우고
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			OnShowPattern.Broadcast(EPunchDirection::None);

			// 미지막 키 입력 제한 시간 추가
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				if (!bIsBoxing) return; 
				OnPatternFail();
			}, 0.5f, false);
		}, 1.f, false);
		return;
	}

	// 현재 패턴 디스플레이
	OnShowPattern.Broadcast(CurrentPattern[PatternDisplayIndex]);
	PatternDisplayIndex++;

	// 현재 패턴 UI 지우고 재귀
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		OnShowPattern.Broadcast(EPunchDirection::None);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			// 재귀 호출을 하면서 UI의 현재 키입력을 업데이트 한다.
			OnPatternDisplay();
		}, 0.3f, false);
	}, 0.2f, false);
}

void UBoxingActivityComponent::AddReward()
{
	if (!StatSubsystem) return;

	FStatReward Reward;
	Reward.Stats.Add(EPlayerStatType::Strength, AccumulatedStrength);
	StatSubsystem->ApplyReward(Reward);
}

void UBoxingActivityComponent::OnPatternSuccess()
{
	if (!AnimInstance || !PunchMontage) return;

	AnimInstance->Montage_Play(PunchMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UBoxingActivityComponent::OnPunchAnimEnded);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, PunchMontage);
}

void UBoxingActivityComponent::SetABPBoxingState(bool bBoxing)
{
	if (!AnimInstance) return;
	
	FProperty* Prop = AnimInstance->GetClass()->FindPropertyByName(FName("IsBoxing"));
	if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Prop))
	{
		BoolProp->SetPropertyValue_InContainer(AnimInstance, bBoxing);
	}
}
