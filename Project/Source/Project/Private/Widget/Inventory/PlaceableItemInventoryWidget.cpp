// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/PlaceableItemInventoryWidget.h"
#include "Widget/Inventory/PlaceableItemSelectionWidget.h"
#include "Goods/Data/FPlaceableItemData.h"

void UPlaceableItemInventoryWidget::SetupWithData(EPlaceableItemType PlaceableItemType, const TArray<FPlaceableItemData*>& DataArray)
{
	if (!PlaceableItemSelectionWidget) return;

	// 슬롯을 설정할 수 있도록 데이터를 넘긴다.
	PlaceableItemSelectionWidget->PopulateGrid(PlaceableItemType, DataArray);
}
