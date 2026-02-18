// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Activity/DanceActivityComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDanceActivityComponent::UDanceActivityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDanceActivityComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	
	MovementComponent = Character->GetCharacterMovement();
	AnimInstance = Character->GetMesh()->GetAnimInstance();

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (!PlayerController) return;

	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!InputSubsystem || !DanceMappingContext) return;

	InputSubsystem->AddMappingContext(DanceMappingContext, 0);

	// 입력 바인딩
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(Character->InputComponent);
	if (!EIC) return;

	if (Dance1Action)
		EIC->BindAction(Dance1Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 0);
	if (Dance2Action)
		EIC->BindAction(Dance2Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 1);
	if (Dance3Action)
		EIC->BindAction(Dance3Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 2);
	if (Dance4Action)
		EIC->BindAction(Dance4Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 3);
	if (Dance5Action)
		EIC->BindAction(Dance5Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 4);
	if (Dance6Action)
		EIC->BindAction(Dance6Action, ETriggerEvent::Started, this, &UDanceActivityComponent::PlayDance, 5);
}

void UDanceActivityComponent::PlayDance(int32 Index)
{
	// 이미 춤추는 중이거나 몽타주가 없으면 무시
	if (bIsDancing) return;
	if (!AnimInstance || !DanceMontages.IsValidIndex(Index) || !DanceMontages[Index]) return;

	bIsDancing = true;

	// 이동 정지
	// 카메라 회전 자유도 증가
	if (MovementComponent)
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->bOrientRotationToMovement = false;
		MovementComponent->SetMovementMode(EMovementMode::MOVE_None);
	}
	
	if (Character)
	{
		Character->bUseControllerRotationYaw = false;
	}

	AnimInstance->Montage_Play(DanceMontages[Index]);

	// 몽타주 끝나면 복귀
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &UDanceActivityComponent::OnDanceMontageEnded);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, DanceMontages[Index]);
}

void UDanceActivityComponent::OnDanceMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsDancing = false;

	// 이동 및 카메라 회전 초기화
	if (Character)
	{
		Character->bUseControllerRotationYaw = true;
	}

	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}