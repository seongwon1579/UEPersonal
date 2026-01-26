// Fill out your copyright notice in the Description page of Project Settings.


#include "Pool/StaticMeshPool.h"
#include "Goods/HomeGoods.h"

void AStaticMeshPool::BeginPlay()
{
	Super::BeginPlay();
	PopulatePool(PoolSize);
}

// 풀에서 들어오거 나갈때 액터의 상태 설정
void AStaticMeshPool::SetActiveState(AHomeGoods* Goods, const bool bActive)
{
	if (!Goods) return;
	
	Goods->SetActorHiddenInGame(!bActive);
	Goods->SetActorEnableCollision(bActive);
}

// 풀의 크기를 조절
void AStaticMeshPool::PopulatePool(int32 size)
{
	for (int32 i = 0; i < size; i++)
	{
		AHomeGoods* Goods = GetWorld()->SpawnActor<AHomeGoods>(HomeGoods);
		if (!Goods) return;

		HomeGoodsArray.Add(Goods);
	}
}

// 풀에서 액터를 반환한다.
AHomeGoods* AStaticMeshPool::GetHomeGoods()
{
	// 풀에 모든 액터가 빠져나가면 풀의 크기를 늘린다.
	if (HomeGoodsArray.Num() <= 0)
	{
		PopulatePool(PoolSize);
	}

	AHomeGoods* Goods = HomeGoodsArray.Pop();
	SetActiveState(Goods, true);
	return Goods;
}

// 사용이 끝난 액터를 반환한다.
void AStaticMeshPool::ReturnHomeGoods(AHomeGoods* Goods)
{
	if (!Goods) return;
	
	HomeGoodsArray.Add(Goods);
	SetActiveState(Goods, false);
}
