// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Placement//ObjectPlacementInputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Character/Player/Component/Placement//ObjectPlacementComponent.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

UObjectPlacementInputComponent::UObjectPlacementInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// 사용자 입력 이벤트를 바인딩 한다.
void UObjectPlacementInputComponent::BindInputAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (StartPlacementAction)
	{
		EnhancedInputComponent->BindAction(StartPlacementAction, ETriggerEvent::Started,
		                                   this, &UObjectPlacementInputComponent::OnStartPlacement);
	}
	if (ConfirmPlacementAction)
	{
		EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Started,
		                                   this, &UObjectPlacementInputComponent::OnConfirmPlacement);
	}
	if (CancelPlacementAction)
	{
		EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Started,
		                                   this, &UObjectPlacementInputComponent::OnCancelPlacement);
	}
	if (RotateAction)
	{
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this,
		                                   &UObjectPlacementInputComponent::OnRotateAction);
	}
	if (SelectObjectAction)
	{
		EnhancedInputComponent->BindAction(SelectObjectAction, ETriggerEvent::Started,
		                                   this, &UObjectPlacementInputComponent::OnSelectObject);
	}
	if (RemoveObjectAction)
	{
		EnhancedInputComponent->BindAction(RemoveObjectAction, ETriggerEvent::Started, 
			this, &UObjectPlacementInputComponent::OnRemoveObject);
	}
	
}

void UObjectPlacementInputComponent::BeginPlay()
{
	Super::BeginPlay();

	PlacementComponent = GetOwner()->FindComponentByClass<UObjectPlacementComponent>();
	if (!PlacementComponent) return;

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	// EIC 캐스팅
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	if (!EnhancedInputComponent) return;

	// 배치 모드 입력 매핑 등록
	APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	if (!PC) return;

	if (!PlacementMappingContext) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlacementMappingContext, 1);
	}

	// 인풋 액션 바인딩
	BindInputAction(EnhancedInputComponent);
}

// 배치가 된 오브젝트를 더블 클릭으로 선택가능한지를 확인
void UObjectPlacementInputComponent::OnSelectObject(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	// 현재 프리뷰 모드인 경우, 리턴
	if (PlacementComponent->IsPreviewMode()) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();

	// 더블 클릭 체크, 더블 클릭시에만 물체를 선택 가능다 하도록 한다.
	if (CurrentTime - LastClickTime < DoubleClickThreshold)
	{
		PlacementComponent->TrySelectObject();
	}

	LastClickTime = CurrentTime;
}

// 물체의 회전 입력을 받는다.
void UObjectPlacementInputComponent::OnRotateAction(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	float ScrollValue = Value.Get<float>();
	PlacementComponent->RotateObject(ScrollValue);
}

// 물체 배치 시작 입력을 받는다.
void UObjectPlacementInputComponent::OnStartPlacement(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	PlacementComponent->StartPlacement();
}

// 물체를 배치 확정 입력을 받는다.
void UObjectPlacementInputComponent::OnConfirmPlacement(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	if (!PlacementComponent->IsPreviewMode()) return;

	PlacementComponent->ConfirmPlacement();
}

// 배치 취소 입력을 받는다.
void UObjectPlacementInputComponent::OnCancelPlacement(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	PlacementComponent->CancelPlacement();
}

void UObjectPlacementInputComponent::OnRemoveObject(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;
	
	PlacementComponent->RemoveObject();
}
