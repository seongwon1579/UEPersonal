// Fill out your copyright notice in the Description page of Project Settings.


#include "Goods/HomeGoods.h"
#include "NaniteSceneProxy.h"

// Sets default values
AHomeGoods::AHomeGoods()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//StaticMeshComponent->SetupAttachment(RootComponent);
	RootComponent = StaticMeshComponent;
}
void AHomeGoods::CheckSpawn()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	if (OverlappingActors.Num() > 0)
	{
		StaticMeshComponent->SetMaterial(0, Material_Red);
		bCanSpawn = false;
	}
	else
	{
		StaticMeshComponent->SetMaterial(0, Material_Green);
		bCanSpawn = true;
	}
}

void AHomeGoods::Place()
{
	if (bCanSpawn)
	{
		StaticMeshComponent->SetMaterial(0, Material_Target);
		StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}
}

