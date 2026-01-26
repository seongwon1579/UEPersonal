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
	AHomeGoods* GetHomeGoods();
	void ReturnHomeGoods(AHomeGoods* Goods);
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Pool")
	TSubclassOf<AHomeGoods> HomeGoods;

	TArray<AHomeGoods*> HomeGoodsArray;

protected:
	virtual void BeginPlay() override;

private:
	void SetActiveState(AHomeGoods* Goods, const bool bActive);
	void PopulatePool(int32 size);
	
	UPROPERTY(EditAnywhere, Category= "Pool", meta=(AllowPrivateAccess=true))
	int32 PoolSize = 10;
};
