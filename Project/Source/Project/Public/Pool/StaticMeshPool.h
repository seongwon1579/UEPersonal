// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticMeshPool.generated.h"

class AHomeGoods;
/**
 * 
 */
UCLASS()
class PROJECT_API AStaticMeshPool : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Pool")
	TSubclassOf<AHomeGoods> HomeGoods;
	
	TArray<AHomeGoods*> HomeGoodsArray;
	
public:
	virtual void BeginPlay() override;
	
	AHomeGoods* GetHomeGoods();
	void ReturnHomeGoods(AHomeGoods* Goods);
	
	
};
