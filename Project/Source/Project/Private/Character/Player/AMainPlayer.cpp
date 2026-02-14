// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/AMainPlayer.h"

#include "DebugHelper.h"
#include "EnhancedInputComponent.h"
#include "Activity/PunchingBag.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "Character/Player/Component/Dialogue/DialogueComponent.h"

bool AMainPlayer::IsBoxing() const
{
	if (!BoxingComp) return false;
	return BoxingComp->IsBoxing();
}

void AMainPlayer::StartBoxing()
{
	if (!BoxingComp) return;
	BoxingComp->StartBoxing();
}

void AMainPlayer::StartDialogueWith(AActor* OtherActor)
{
	if (!DialogueComp || !OtherActor) return;
	
	DialogueComp->StartDialogueWith(OtherActor);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	BoxingComp = FindComponentByClass<UBoxingActivityComponent>();
	DialogueComp = FindComponentByClass<UDialogueComponent>();
}

// 키입력에 바인딩(키입력시 호출)
void AMainPlayer::OnInteractInput()
{
	if (!CurrentInteractable) return;

	IInteractableInterface* Interactable = Cast<IInteractableInterface>(CurrentInteractable);
	if (!Interactable) return;

	if (Interactable->CanInteract())
	{
		Interactable->Interact(this);
	}
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainPlayer::OnInteractInput);
	}
}
