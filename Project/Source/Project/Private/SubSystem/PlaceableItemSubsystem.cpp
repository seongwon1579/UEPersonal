// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/PlaceableItemSubsystem.h"

#include "DebugHelper.h"
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
	
	LoadDataTable(EPlaceableItemType::Building, TEXT("/Game/_BP/Goods/Data/DT_Building.DT_Building"));
	LoadDataTable(EPlaceableItemType::Interior, TEXT("/Game/_BP/Goods/Data/DT_Interior.DT_Interior"));
	LoadDataTable(EPlaceableItemType::Exterior, TEXT("/Game/_BP/Goods/Data/DT_Exterior.DT_Exterior"));
}

// 데이터 로드
void UPlaceableItemSubsystem::LoadDataTable(EPlaceableItemType Type, const TCHAR* Path)
{
	if (UDataTable* DataTable = LoadObject<UDataTable>(nullptr, Path))
	{
		PlaceableItemData.Add(Type, DataTable);
	}
}

// 데이터 Get
TArray<FPlaceableItemData*> UPlaceableItemSubsystem::GetPlaceableItemData(EPlaceableItemType ItemType)
{
	TArray<FPlaceableItemData*> Result;
	
	if (UDataTable* Data = PlaceableItemData.FindRef(ItemType))
	{
		Data->GetAllRows<FPlaceableItemData>(TEXT("GetBuildingData"), Result);

		//Debug::Print(Result[0]->Name.ToString());
	}
	
	return Result;
}

