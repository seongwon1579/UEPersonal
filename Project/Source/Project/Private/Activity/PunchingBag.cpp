// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity/PunchingBag.h"

#include "DebugHelper.h"
#include "Character/Player/AMainPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/Interaction/InteractionWidget.h"

APunchingBag::APunchingBag()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	SetRootComponent(SceneComponent);
	
	InteractionWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComp->SetupAttachment(RootComponent);
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
	
	if (UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComp->GetWidget()))
	{
		Widget->SetInteractionType(FText::FromString(TEXT("복싱하기")));
	}
	
	SetWidgetVisibility(false);
}

bool APunchingBag::CanInteract() const
{
	return true;
}

void APunchingBag::Interact(AActor* Interactor)
{
	SetWidgetVisibility(false);
	
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
	
	SetWidgetVisibility(true);
}

void APunchingBag::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(nullptr);
	
	SetWidgetVisibility(false);
}

void APunchingBag::SetWidgetVisibility(bool bIsVisible)
{
	if (InteractionWidgetComp)
	{
		InteractionWidgetComp->SetVisibility(bIsVisible);
	}
}



