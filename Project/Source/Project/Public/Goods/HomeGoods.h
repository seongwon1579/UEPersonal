// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeGoods.generated.h"

class UMaterialInterface;
class UStaticMesh;

UCLASS()
class PROJECT_API AHomeGoods : public AActor
{
	GENERATED_BODY()
	
public:
	bool CanBeSelected() const { return bIsSelectable; }
	void CheckSpawn();
	void Place();
	void StartEditing();
	bool CanSpawn() const { return bCanSpawn;}
	// void SetMaterial(UMaterialInterface* HomeGoodsMaterial) {this->HomeGoodsMaterial = HomeGoodsMaterial;};
	// void SetStaticMesh(UStaticMesh* HomeGoodsStaticMesh) {this->HomeGoodsStaticMesh = HomeGoodsStaticMesh;};
	void SetHomeGoods(UMaterialInterface* Material, UStaticMesh* StaticMesh)
	{
		HomeGoodsMaterial = Material;
		HomeGoodsStaticMesh = StaticMesh;
		
		if (StaticMesh)
		{
			StaticMeshComponent->SetStaticMesh(StaticMesh);
		}
    
		if (Material)
		{
			StaticMeshComponent->SetMaterial(0, Material);
		}
	}

private:	
	// Sets default values for this actor's properties
	AHomeGoods();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material_Green;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material_Red;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	// UMaterialInterface* Material_Target;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DebugMode",meta = (AllowPrivateAccess = "true"))
	bool bDebugMode = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* HomeGoodsMaterial;
	UPROPERTY()
	UStaticMesh* HomeGoodsStaticMesh;
	
	bool bIsSelectable = false;  
	bool bCanSpawn;
	
};
