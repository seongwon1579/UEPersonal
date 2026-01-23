// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "ObjectPlacementComponent.generated.h"

struct FFurnitureItemData;
class AHomeGoods;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API  UObjectPlacementComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void StartPlacing();
	void ConfirmPlacement();
	void CancelPlacement();
	void TrySelectObject();
	void RotatePlacement(float Direction); 
	bool IsEditMode() const { return bIsEditing; }
	
	void TestMethod(FFurnitureItemData* Data);
	
private:
	void UpdatePlacementPreview();

private:
	//TODO: 데이터 테이블 데이터 할당 고려
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Placement", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHomeGoods> Goods;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement", meta = (AllowPrivateAccess = "true"))
	float PlacementRange = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placement", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 10.f;
	
	UPROPERTY()
	UCameraComponent* Camera;
	
	UPROPERTY()
	AHomeGoods* HomeGoods;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	bool bIsEditing = false;
	bool bIsNewPlacing = false;
	float CurrentRotationExtent = 0.f;
	float LastEditStartTime;
	FTimerHandle PlacementTimerHandle;
	FTransform PrevTransform;
	
	UObjectPlacementComponent();
	virtual void BeginPlay() override;
};