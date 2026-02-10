// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Goods/GoodsData/FFurnitureItemData.h"
#include "Goods/Data/FPlaceableItemData.h"
#include "PlaceableItemSelectionWidget.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
class UUniformGridPanel;
class UButton;
class UCommonButtonBase;

UCLASS()
class PROJECT_API UPlaceableItemSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void PopulateGrid(EPlaceableItemType ItemType, const TArray<FPlaceableItemData*>& DataArray);

private:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Building_Button;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Interior_Button;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* Exterior_Button;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* Switcher;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Building_GridPanel;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Interior_GridPanel;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Exterior_GridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget>  PlaceableItemSlot;
	
	TMap<EPlaceableItemType, UUniformGridPanel*> GridPanels;
};
