// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlaceableItemSlotWidget.generated.h"

/**
 * 
 */
class USizeBox;
class UTextBlock;
class UImage;
class UButton;
struct FPlaceableItemData;
class APlayerController;
class UObjectPlacementComponent;

UCLASS()
class PROJECT_API UPlaceableItemSlotWidget : public UUserWidget
{
public:
	void SetupSlot(FPlaceableItemData* Data);

	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	USizeBox* FurnitureSlot_SizeBox;
	
	
	UPROPERTY(meta =(BindWidget))
	UButton* FurnitureIcon_Button;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FurnitureSlotName_TextBlock;

	UFUNCTION()
	void OnButtonClicked();

	virtual void NativeConstruct() override;

private:
	FPlaceableItemData* FurnitureItemData;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	UObjectPlacementComponent* PlacementComponent;
};
