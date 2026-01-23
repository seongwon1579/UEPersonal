// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlacementInputComponent.h"

#include "Character/ObjectPlacementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

UPlacementInputComponent::UPlacementInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Asset(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement"));

	if (IMC_Asset.Succeeded())
	{
		PlacementMappingContext = IMC_Asset.Object;
	}
}

void UPlacementInputComponent::BindInputAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (StartPlacingAction)
	{
		EnhancedInputComponent->BindAction(StartPlacingAction, ETriggerEvent::Started,
										   this, &UPlacementInputComponent::OnStartPlacing);
	}
	if (ConfirmPlacementAction)
	{
		EnhancedInputComponent->BindAction(ConfirmPlacementAction, ETriggerEvent::Started,
										   this, &UPlacementInputComponent::OnConfirmPlacement);
	}
	if (CancelPlacementAction)
	{
		EnhancedInputComponent->BindAction(CancelPlacementAction, ETriggerEvent::Started,
										   this, &UPlacementInputComponent::OnCancelPlacement);
	}
	if (RotateAction)
	{
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this,
										   &UPlacementInputComponent::OnRotateAction);
	}
	if (SelectObjectAction)
	{
		EnhancedInputComponent->BindAction(SelectObjectAction, ETriggerEvent::Started,
										   this, &UPlacementInputComponent::OnSelectObject);
	}
}

void UPlacementInputComponent::BeginPlay()
{
	Super::BeginPlay();
	// static TSoftObjectPtr<UInputMappingContext> MappingContext(
	// 	FSoftObjectPath(TEXT("/Game/_BP/Input/IMC_Placement.IMC_Placement")));
	//
	// PlacementMappingContext = MappingContext.LoadSynchronous();
	
	PlacementComponent = GetOwner()->FindComponentByClass<UObjectPlacementComponent>();

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	// InputComponent 가져오기
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	if (!EnhancedInputComponent) return;
	
	// IMC 추가
	if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (PlacementMappingContext)
			{
				Subsystem->AddMappingContext(PlacementMappingContext, 1);
			}
		}
	}
	
	BindInputAction(EnhancedInputComponent);
}

void UPlacementInputComponent::OnSelectObject(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	if (PlacementComponent->IsEditMode()) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastClickTime < DoubleClickThreshold)
	{
		PlacementComponent->TrySelectObject();
	}

	LastClickTime = CurrentTime;
}

void UPlacementInputComponent::OnRotateAction(const FInputActionValue& Value)
{
	if (PlacementComponent)
	{
		float ScrollValue = Value.Get<float>();
		PlacementComponent->RotatePlacement(ScrollValue);
	}
}

void UPlacementInputComponent::OnStartPlacing(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	PlacementComponent->StartPlacing();
}

void UPlacementInputComponent::OnConfirmPlacement(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	if (!PlacementComponent->IsEditMode()) return;

	PlacementComponent->ConfirmPlacement();
}

void UPlacementInputComponent::OnCancelPlacement(const FInputActionValue& Value)
{
	if (!PlacementComponent) return;

	PlacementComponent->CancelPlacement();
}
