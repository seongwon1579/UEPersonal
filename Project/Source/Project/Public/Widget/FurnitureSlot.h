// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FurnitureSlot.generated.h"

/**
 * 
 */
class USizeBox;
class UTextBlock;
class UImage;
struct FFurnitureItemData;

UCLASS()
class PROJECT_API UFurnitureSlot : public UUserWidget
{
public:
	void SetSizeBox(float Width, float Height);
	void SetupSlot(FFurnitureItemData* Data);
	
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	USizeBox* FurnitureSlot_SizeBox;
	
	UPROPERTY(meta = (BindWidget))
	UImage* FurnitureSlot_Thumbnail_Image;
    
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FurnitureSlot_Name_TextBlock;
};
