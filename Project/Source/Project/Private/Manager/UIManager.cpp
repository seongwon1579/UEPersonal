// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"

#include "Blueprint/UserWidget.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/PlaceActorWidget.h"

UUIManager::UUIManager()
{
}

void UUIManager::ShowPlaceActorWidget()
{
	if (!PlaceWidget || !Controller) return;
	
	UPlaceActorWidget* PlaceActorWidget = CreateWidget<UPlaceActorWidget>(Controller, PlaceWidget);
	
	UPlaceableItemSubsystem* PlaceableItemSubsystem = Controller->GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	TArray<FFurnitureItemData*> FurnitureItemData = PlaceableItemSubsystem->GetAllFurnitureData();
	
	if (!FurnitureItemData.IsEmpty())
	{
		PlaceActorWidget->SetupWithData(FurnitureItemData);
	}
	PlaceActorWidget->AddToViewport();
}

void UUIManager::Initialize(APlayerController* PC, TSubclassOf<UPlaceActorWidget> Widget)
{
	Controller = PC;
	PlaceWidget = Widget;
}
