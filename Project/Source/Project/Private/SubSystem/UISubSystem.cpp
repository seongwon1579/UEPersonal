// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem//UISubSystem.h"

#include "Blueprint/UserWidget.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/PlaceActorWidget.h"
#include "Widget/Activity/BoxingPatternWidget.h"
#include "Widget/Interaction/InteractionWidget.h"

void UUISubSystem::ShowPlaceActorWidget()
{
	if (!PlaceActorWidget) return;

	UPlaceableItemSubsystem* PlaceableItemSubsystem = GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	TArray<FFurnitureItemData*> FurnitureItemData = PlaceableItemSubsystem->GetAllFurnitureData();

	// 데이터를 가지고 위젯을 초기화한다.
	if (!FurnitureItemData.IsEmpty())
	{
		PlaceActorWidget->SetupWithData(FurnitureItemData);
	}

	PlaceActorWidget->AddToViewport();
}

void UUISubSystem::HidePlaceActorWidget()
{
	if (!PlaceActorWidget) return;
	PlaceActorWidget->RemoveFromParent();
}

void UUISubSystem::ShowBoxingPatternWidget(UBoxingActivityComponent* InBoxingActivityComponent)
{
	if (!BoxingPatternWidget || !InBoxingActivityComponent) return;
	
	BoxingPatternWidget->InitWidget(InBoxingActivityComponent);
	BoxingPatternWidget->AddToViewport();
}

void UUISubSystem::HideBoxingPatternWidget()
{
	if (!BoxingPatternWidget) return;
	BoxingPatternWidget->RemoveFromParent();
}

void UUISubSystem::ShowInteractionWidget()
{
	if (!InteractionWidget) return;
	InteractionWidget->AddToViewport();
}

void UUISubSystem::HideInteractionWidget()
{
	if (!InteractionWidget) return;
	InteractionWidget->RemoveFromParent();
}

void UUISubSystem::RegisterWidgets(UPlaceActorWidget* InPlaceActorWidget, UBoxingPatternWidget* InBoxingPatternWidget, UInteractionWidget* InInteractionWidget)
{
	PlaceActorWidget = InPlaceActorWidget;
	BoxingPatternWidget = InBoxingPatternWidget;
	InteractionWidget = InInteractionWidget;
}
