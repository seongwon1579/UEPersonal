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
class UTextBlock;

UCLASS()
class PROJECT_API UPlaceableItemSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void PopulateGrid(EPlaceableItemType ItemType, const TArray<FPlaceableItemData*>& DataArray);
	void RefreshAvailableItems(int32 Value); 

private:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnBuildingClicked();

	UFUNCTION()
	void OnInteriorClicked();

	UFUNCTION()
	void OnExteriorClicked();
	
	UPROPERTY(meta = (BindWidget))
	UButton* Building_Button;	
	
	UPROPERTY(meta = (BindWidget))
	UButton* Interior_Button;	
	
	UPROPERTY(meta = (BindWidget))
	UButton* Exterior_Button;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* Switcher;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Building_GridPanel;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Interior_GridPanel;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* Exterior_GridPanel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Strength_Value_TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget>  PlaceableItemSlot;
	
	UPROPERTY()
	TMap<EPlaceableItemType, UUniformGridPanel*> GridPanels;
	
};
