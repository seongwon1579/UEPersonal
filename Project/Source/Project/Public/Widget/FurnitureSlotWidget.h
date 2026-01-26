// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureSlotWidget.generated.h"

/**
 * 
 */
class USizeBox;
class UTextBlock;
class UImage;
class UButton;
struct FFurnitureItemData;
class APlayerController;
class UObjectPlacementComponent;

UCLASS()
class PROJECT_API UFurnitureSlotWidget : public UUserWidget
{
public:
	void SetSizeBox(float Width, float Height);
	void SetupSlot(FFurnitureItemData* Data);

	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	USizeBox* FurnitureSlot_SizeBox;

	UPROPERTY(meta = (BindWidget))
	UImage* FurnitureSlot_Thumbnail_Image;

	UPROPERTY(meta =(BindWidget))
	UButton* FurnitureIconBtn;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FurnitureSlot_Name_TextBlock;

	UFUNCTION()
	void OnButtonClicked();

	virtual void NativeConstruct() override;

private:
	FFurnitureItemData* FurnitureItemData;
	UPROPERTY()
	APlayerController* OwningPlayerController;
	UPROPERTY()
	UObjectPlacementComponent* PlacementComponent;
};
