// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "ObjectPlacementComponent.generated.h"


class AHomeGoods;
// class UCameraComponent;
// class AHomeGoods;
//
// UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
// class PROJECT_API UObjectPlacementComponent : public UActorComponent
// {
// 	GENERATED_BODY()
// 	
// private:
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
// 	class UCameraComponent* CachedCamera;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
// 	class AHomeGoods* HomeGoods;
//
// public:	
// 	UPROPERTY(EditAnywhere,  BlueprintReadWrite ,Category = "Spawning")
// 	TSubclassOf<AHomeGoods> GoodsBlueprintClass;
// 	// Sets default values for this component's properties
// 	UObjectPlacementComponent();
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
// 	bool bPlacingTarget;
//
// protected:
// 	// Called when the game starts
// 	virtual void BeginPlay() override;
//
//
// public:	
// 	// Called every frame
// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
// 	UFUNCTION(BlueprintCallable, Category = "Goods")
// 	void TryPlace();
// 	
// };
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API  UObjectPlacementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement")
	TSubclassOf<AHomeGoods> GoodsBlueprintClass;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement")
	float PlacementRange = 1500.f;

	UFUNCTION(BlueprintCallable, Category = "Placement")
	void StartPlacing();
    
	UFUNCTION(BlueprintCallable, Category = "Placement")
	void ConfirmPlacement();
    
	UFUNCTION(BlueprintCallable, Category = "Placement")
	void CancelPlacement();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UCameraComponent* CachedCamera;
    
	UPROPERTY()
	AHomeGoods* HomeGoods;
    
	UPROPERTY()
	APlayerController* CachedController;
    
	bool bPlacingTarget = false;
    
	void UpdatePlacementPreview();
};