// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/AMainPlayer.h"

#include "DebugHelper.h"
#include "EnhancedInputComponent.h"
#include "Activity/PunchingBag.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"


void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayer::OnInteractInput()
{
	if (!Cast<APunchingBag>(CurrentInteractable)) return;

	UBoxingActivityComponent* BoxingComp = FindComponentByClass<UBoxingActivityComponent>();
	if (!BoxingComp) return;

	if (IBoxingActivityInterface* BoxingActivity = Cast<IBoxingActivityInterface>(BoxingComp))
	{
		if (BoxingActivity->IsBoxing()) return;
		
		BoxingActivity->StartBoxing();
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
