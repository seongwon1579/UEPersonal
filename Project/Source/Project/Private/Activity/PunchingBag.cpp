// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity/PunchingBag.h"

#include "DebugHelper.h"
#include "Character/Player/AMainPlayer.h"
#include "Components/BoxComponent.h"
#include "SubSystem/UISubSystem.h"

APunchingBag::APunchingBag()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APunchingBag::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionZone = FindComponentByClass<UBoxComponent>();
	
	if (InteractionZone)
	{
		InteractionZone->OnComponentBeginOverlap.AddDynamic(this, &APunchingBag::OnOverlapBegin);
		InteractionZone->OnComponentEndOverlap.AddDynamic(this, &APunchingBag::OnOverlapEnd);
	}
}

void APunchingBag::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;
	
	Player->SetCurrentInteractable(this);
	
	UUISubSystem* UISubSystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	if (UISubSystem)
	{
		UISubSystem->ShowInteractionWidget();
	}
}

void APunchingBag::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(nullptr);

	UUISubSystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	if (UISubsystem)
	{
		UISubsystem->HideInteractionWidget();
	}
}



