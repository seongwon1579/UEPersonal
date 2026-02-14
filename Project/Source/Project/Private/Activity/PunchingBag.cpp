// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity/PunchingBag.h"

#include "DebugHelper.h"
#include "Character/Player/AMainPlayer.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

APunchingBag::APunchingBag()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	SetRootComponent(SceneComponent);
	
	InteractionWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComp->SetupAttachment(RootComponent);
	InteractionWidgetComp->SetVisibility(false);
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

bool APunchingBag::CanInteract() const
{
	return true;
}

void APunchingBag::Interact(AActor* Interactor)
{
	IBoxingActivityInterface* BoxingInterface = Cast<IBoxingActivityInterface>(Interactor);
	if (!BoxingInterface) return;

	if (BoxingInterface->IsBoxing()) return;

	BoxingInterface->StartBoxing();
}

void APunchingBag::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;
	
	// 현재 인터렉션 대상을 플레이어에게 전달
	Player->SetCurrentInteractable(this);
	
	if (InteractionWidgetComp)
	{
		InteractionWidgetComp->SetVisibility(true);
	}
	
}

void APunchingBag::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(nullptr);
	
	if (InteractionWidgetComp)
	{
		InteractionWidgetComp->SetVisibility(false);
	}
}



