// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlaceableItemSubsystem.generated.h"

/**
 * 
 */

class UDataTable;
class AStaticMeshPool;
struct FFurnitureItemData;

UCLASS()
class PROJECT_API UPlaceableItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitializeStaticMeshPool(UWorld* World);
	AStaticMeshPool* GetStaticMeshPool() { return StaticMeshPool;};
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY()
	UDataTable* FurnitureDataTable;

	UPROPERTY()
	AStaticMeshPool* StaticMeshPool;

	UPROPERTY()
	TSubclassOf<AStaticMeshPool> StaticMeshPoolClass;

public:
	TArray<FFurnitureItemData*> GetAllFurnitureData();
};
