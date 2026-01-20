// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeGoods.generated.h"

UCLASS()
class PROJECT_API AHomeGoods : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomeGoods();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInterface* Material_Green;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInterface* Material_Red;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInterface* Material_Target;
	
	UPROPERTY(BlueprintReadOnly, Category = "Placement")
	bool bIsSelectable = false;  
	UFUNCTION(BlueprintCallable, Category = "Placement")
	bool CanBeSelected() const { return bIsSelectable; }

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void StartEditing();  // 추가
	
	
	bool bCanSpawn;
	void CheckSpawn();
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void Place();

};
