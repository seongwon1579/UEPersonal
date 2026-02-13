// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Goods/Data/FPlaceableItemData.h"

#include "PlaceableItemSubsystem.generated.h"

/**
 * 
 */

class UDataTable;
class AStaticMeshPool;
struct FPlaceableItemData;

UCLASS()
class PROJECT_API UPlaceableItemSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	AStaticMeshPool* GetStaticMeshPool() { return StaticMeshPool;};
	void InitializeStaticMeshPool(UWorld* World);
	
	TArray<FPlaceableItemData*> GetPlaceableItemData(EPlaceableItemType ItemType);
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void LoadDataTable(EPlaceableItemType Type, const TCHAR* Path);
	
	UPROPERTY()
	AStaticMeshPool* StaticMeshPool;

	UPROPERTY()
	TSubclassOf<AStaticMeshPool> StaticMeshPoolClass;
	
	UPROPERTY()
	TMap<EPlaceableItemType, UDataTable*> PlaceableItemData;
};
