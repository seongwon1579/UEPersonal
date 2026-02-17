// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Activity/BoxingActivityInputComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"

UBoxingActivityInputComponent::UBoxingActivityInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBoxingActivityInputComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;
	
	// 컨트롤러 캐싱
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!PlayerController) return;

	// EIC 캐싱
	EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	if (!EnhancedInputLocalPlayerSubsystem) return;
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	if (!EnhancedInputComponent) return;

	BindInputActions(EnhancedInputComponent);
}

// 복싱 인풋 액션 바인딩
void UBoxingActivityInputComponent::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (!BoxingMappingContext) return;

	if (LeftAction)
	{
		EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Started, this,
		                                   &UBoxingActivityInputComponent::OnLeftInput);
	}
	if (RightAction)
	{
		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this,
		                                   &UBoxingActivityInputComponent::OnRightInput);
	}
	if (UpAction)
	{
		EnhancedInputComponent->BindAction(UpAction, ETriggerEvent::Started, this,
		                                   &UBoxingActivityInputComponent::OnUpInput);
	}
	if (DownAction)
	{
		EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Started, this,
										   &UBoxingActivityInputComponent::OnDownInput);
	}
	if (PunchAction)
	{
		EnhancedInputComponent->BindAction(PunchAction, ETriggerEvent::Started, this,
		                                   &UBoxingActivityInputComponent::OnPunchInput);
	}
}

void UBoxingActivityInputComponent::OnLeftInput()
{
	OnDirectionInputDelegate.Broadcast(EPunchDirection::Left);
}

void UBoxingActivityInputComponent::OnRightInput()
{
	OnDirectionInputDelegate.Broadcast(EPunchDirection::Right);
}

void UBoxingActivityInputComponent::OnUpInput()
{
	OnDirectionInputDelegate.Broadcast(EPunchDirection::Up);
}

void UBoxingActivityInputComponent::OnDownInput()
{
	OnDirectionInputDelegate.Broadcast(EPunchDirection::Down);
}

void UBoxingActivityInputComponent::OnPunchInput()
{
	OnPunchInputDelegate.Broadcast();
}

// 복싱이 시작되고 끝날 때, 인풋 추가 삭제
void UBoxingActivityInputComponent::EnableBoxingInput(bool Enable)
{
	if (!EnhancedInputLocalPlayerSubsystem || !BoxingMappingContext) return;

	if (Enable)
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(BoxingMappingContext, 1);
	}
	else
	{
		EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(BoxingMappingContext);
	}
}
