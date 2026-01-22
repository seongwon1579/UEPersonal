// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ACraftPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/FurnitureSelectionWidget.h"

void AACraftPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!WidgetClass) return;
	
	FurnitureWidget = CreateWidget<UFurnitureSelectionWidget>(this, WidgetClass);
	
	UPlaceableItemSubsystem* PlaceableItemSubsystem = GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	TArray<FFurnitureItemData*> FurnitureItemData = PlaceableItemSubsystem->GetAllFurnitureData();
	
	if (!FurnitureItemData.IsEmpty())
	{
		FurnitureWidget->PopulateGrid(FurnitureItemData);
		FurnitureWidget->AddToViewport();
	}
}
