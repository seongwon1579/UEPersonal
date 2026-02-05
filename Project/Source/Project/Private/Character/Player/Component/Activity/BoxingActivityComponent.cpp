// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelper.h"
#include "GameFramework/Character.h"
#include "SubSystem/UISubSystem.h"

// Sets default values for this component's properties
UBoxingActivityComponent::UBoxingActivityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UBoxingActivityComponent::StartBoxing()
{
	bIsBoxing = true;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();

	if (MoveComp)
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_None);
	}

	UISubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubSystem>();

	if (UISubsystem)
	{
		UISubsystem->ShowBoxingPatternWidget(this);
	}
	GeneratePattern();
}

void UBoxingActivityComponent::EndBoxing(const FStatReward& Reward)
{
	bIsBoxing = false;
}

bool UBoxingActivityComponent::IsBoxing() const
{
	return bIsBoxing;
}

void UBoxingActivityComponent::OnSpaceBarInput()
{
	if (!bIsBoxing || !bPatternCompleted) return;

	Debug::Print("Clear");

	GetWorld()->GetTimerManager().ClearTimer(PatternTimerHandle);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(PunchMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBoxingActivityComponent::OnPunchMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, PunchMontage);
	}
}

void UBoxingActivityComponent::OnDirectionInput(EPunchDirection Input)
{
	if (CurrentPatternIndex >= CurrentPattern.Num())
	{
		FailPattern();
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
	else
	{
		FailPattern();
	}
}

void UBoxingActivityComponent::GeneratePattern()
{
	bIsFail = false;
	CurrentPattern.Empty();
	bPatternCompleted = false;
	CurrentPatternIndex = 0;

	for (int32 i = 0; i < 9; i++)
	{
		int32 Random = FMath::RandRange(0, 2);
		switch (Random)
		{
		case 0:
			{
				CurrentPattern.Add(EPunchDirection::Left);
				Debug::Print("Left");
				break;
			}
		case 1:
			{
				Debug::Print("right");
				CurrentPattern.Add(EPunchDirection::Right);
				break;
			}
		case 2:
			{
				Debug::Print("up");
				CurrentPattern.Add(EPunchDirection::Up);
				break;
			}
		}
	}
	StartPatternDisplay();
}

void UBoxingActivityComponent::HidePattern()
{
	OnShowPattern.Broadcast(EPunchDirection::None);

	if (bIsFail) return;

	GetWorld()->GetTimerManager().SetTimer(
		DisplayTimerHandle,
		this,
		&UBoxingActivityComponent::NextPatternDisplay,
		0.2f
	);
}

void UBoxingActivityComponent::OnPatternTimeout()
{
	if (!bIsBoxing) return;
	FailPattern();
}

void UBoxingActivityComponent::FailPattern()
{
	Debug::Print("Failed");
	bIsFail = true;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(FailMontage, 2.5f);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UBoxingActivityComponent::OnFailMontageEnded);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, FailMontage);
		bIsBoxing = false;
	}
}

void UBoxingActivityComponent::OnPunchMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GeneratePattern();
}

void UBoxingActivityComponent::OnFailMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();

	if (MoveComp)
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void UBoxingActivityComponent::StartPatternDisplay()
{
	DisplayPatternIndex = 0;
	NextPatternDisplay();
}

void UBoxingActivityComponent::NextPatternDisplay()
{
	if (DisplayPatternIndex < CurrentPattern.Num())
	{
		OnShowPattern.Broadcast(CurrentPattern[DisplayPatternIndex]);

		DisplayPatternIndex++;

		GetWorld()->GetTimerManager().SetTimer(
			DisplayTimerHandle,
			this,
			&UBoxingActivityComponent::HidePattern,
			0.3f
		);
	}
	else
	{
		// Punch 표시
		OnShowPattern.Broadcast(EPunchDirection::Punch);
        
		// 0.5초 후 Punch 숨기고 입력 대기 시작
		GetWorld()->GetTimerManager().SetTimer(
			DisplayTimerHandle,
			this,
			&UBoxingActivityComponent::HidePunchAndStartInput,
			1.f
		);
	}
}

void UBoxingActivityComponent::HidePunchAndStartInput()
{
	OnShowPattern.Broadcast(EPunchDirection::None);
    
	float AdjustedTime = 10.f;
	GetWorld()->GetTimerManager().SetTimer(
		PatternTimerHandle,
		this,
		&UBoxingActivityComponent::OnPatternTimeout,
		AdjustedTime
	);

}
