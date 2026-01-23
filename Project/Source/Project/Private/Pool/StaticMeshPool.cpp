// Fill out your copyright notice in the Description page of Project Settings.


#include "Pool/StaticMeshPool.h"
#include "Goods/HomeGoods.h"

void AStaticMeshPool::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < 20; i++)
	{
		AHomeGoods* Goods = GetWorld()->SpawnActor<AHomeGoods>(HomeGoods);
		
		if (!Goods) return;
		
		Goods->SetActorHiddenInGame(true);
		Goods->SetActorEnableCollision(false);
		HomeGoodsArray.Add(Goods);
	}
}

AHomeGoods* AStaticMeshPool::GetHomeGoods()
{
	AHomeGoods* Goods = nullptr;
	
	if (HomeGoodsArray.Num() > 0)
	{
		Goods = HomeGoodsArray.Pop();
		Goods->SetActorHiddenInGame(false);
		Goods->SetActorEnableCollision(true);
	}
	return Goods;
}

void AStaticMeshPool::ReturnHomeGoods(AHomeGoods* Goods)
{
	Goods->SetActorHiddenInGame(true);
	Goods->SetActorEnableCollision(false);
	HomeGoodsArray.Add(Goods);
}


