// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlaceActorWidget.h"

#include "DebugHelper.h"
#include "Widget/FurnitureSelectionWidget.h"

void UPlaceActorWidget::SetupWithData(const TArray<FFurnitureItemData*>& DataArray)
{
	
	if (!FurnitureSelectionWidget) return;
	
	// 슬롯을 설정할 수 있도록 데이터를 넘긴다.
	FurnitureSelectionWidget->PopulateGrid(DataArray);
}