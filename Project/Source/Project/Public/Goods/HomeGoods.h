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
	void StartPreview();
	bool CanSpawn() const { return bCanSpawn;}
	void SetHomeGoods(UMaterialInterface* Material, UStaticMesh* StaticMesh);

private:	
	AHomeGoods();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material_Green;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material_Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials",meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* HomeGoodsMaterial;
	
	UPROPERTY(EditAnywhere, Blueprintable, Category = "DebugMode",meta = (AllowPrivateAccess = "true"))
	bool bDebugMode = false;
	
	bool bIsSelectable = false;  
	bool bCanSpawn;
	
};
