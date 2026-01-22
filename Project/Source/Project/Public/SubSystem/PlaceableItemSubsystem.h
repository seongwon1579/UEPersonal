// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlaceableItemSubsystem.generated.h"

/**
 * 
 */

class UDataTable;
struct FFurnitureItemData;

UCLASS()
class PROJECT_API UPlaceableItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	UDataTable* FurnitureDataTable;

public:
	TArray<FFurnitureItemData*> GetAllFurnitureData();
};
