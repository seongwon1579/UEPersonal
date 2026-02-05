// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/PlaceableItemSubsystem.h"

#include "DebugHelper.h"
#include "Goods/Data/FFurnitureItemData.h"
#include "Pool/StaticMeshPool.h"

// 풀을 초기화 한다.
void UPlaceableItemSubsystem::InitializeStaticMeshPool(UWorld* World)
{
	StaticMeshPoolClass = LoadClass<AStaticMeshPool>(nullptr, 
	TEXT("/Game/_BP/Pool/BP_StaticMeshPool.BP_StaticMeshPool_C"));
	
	StaticMeshPool = World->SpawnActor<AStaticMeshPool>(StaticMeshPoolClass);
}

// 데이터 테이블을 로드한다.
void UPlaceableItemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	FurnitureDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/_BP/Goods/Data/DT_Furniture.DT_Furniture"));
}


// 데이터 테이블에서 데이터를 가져온다.
TArray<FFurnitureItemData*> UPlaceableItemSubsystem::GetAllFurnitureData()
{
	TArray<FFurnitureItemData*> Result;
	if (FurnitureDataTable)
	{
		FurnitureDataTable->GetAllRows<FFurnitureItemData>(TEXT("GetAllFurnitureData"), Result);
	}
	return Result;
}