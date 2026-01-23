// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlaceActorWidget.generated.h"

/**
 * 
 */
struct FFurnitureItemData;
class UFurnitureSelectionWidget;
UCLASS()
class PROJECT_API UPlaceActorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupWithData(const TArray<FFurnitureItemData*>& DataArray);
	

public:
	UPROPERTY(meta = (BindWidget))
	UFurnitureSelectionWidget* FurnitureSelectionWidget;
	
};
