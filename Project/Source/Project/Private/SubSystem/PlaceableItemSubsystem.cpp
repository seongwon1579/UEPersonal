// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/PlaceableItemSubsystem.h"

#include "DebugHelper.h"
#include "Goods/GoodsData/FFurnitureItemData.h"

void UPlaceableItemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	FurnitureDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_BP/Goods/Data/DT_Furniture.DT_Furniture"));
	
	// TArray<FFurnitureItemData*> Result;
	// FurnitureDataTable->GetAllRows<FFurnitureItemData>(TEXT("GetAllFurnitureData"), Result);
	//
	// UE_LOG(LogTemp, Warning, TEXT("Data: %s"), *Result[0]->Name.ToString());
	
}


TArray<FFurnitureItemData*> UPlaceableItemSubsystem::GetAllFurnitureData()
{
	TArray<FFurnitureItemData*> Result;
	if (FurnitureDataTable)
	{
		FurnitureDataTable->GetAllRows<FFurnitureItemData>(TEXT("GetAllFurnitureData"), Result);
	}
	return Result;
}