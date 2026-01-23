// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlaceActorWidget.h"

#include "DebugHelper.h"
#include "Widget/FurnitureSelectionWidget.h"

void UPlaceActorWidget::SetupWithData(const TArray<FFurnitureItemData*>& DataArray)
{
	
	if (!FurnitureSelectionWidget) return;
	
	FurnitureSelectionWidget->PopulateGrid(DataArray);
}