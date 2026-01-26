// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Goods/GoodsData/FFurnitureItemData.h"  

#include "ObjectPlacementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectPlacementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IObjectPlacementInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Placement")
	void PreparePlacement(const FFurnitureItemData& ItemData);
};
