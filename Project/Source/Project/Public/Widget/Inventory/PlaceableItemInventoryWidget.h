// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Goods/Data/FPlaceableItemData.h"
#include "PlaceableItemInventoryWidget.generated.h"

/**
 * 
 */

class UPlaceableItemSelectionWidget;
UCLASS()
class PROJECT_API UPlaceableItemInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupWithData(EPlaceableItemType PlaceableItemType, const TArray<FPlaceableItemData*>& DataArray);
	

private:
	UPROPERTY(meta = (BindWidget))
	UPlaceableItemSelectionWidget* PlaceableItemSelectionWidget;
	
};
