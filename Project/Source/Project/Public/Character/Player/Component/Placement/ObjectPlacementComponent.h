// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ObjectPlacementInterface.h"

#include "ObjectPlacementComponent.generated.h"

class UStatSubsystem;
struct FPlaceableItemData;
class AHomeGoods;
class UPlaceableItemSubsystem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UObjectPlacementComponent : public UActorComponent, public IObjectPlacementInterface
{
	GENERATED_BODY()

public:
	void StartPlacement();
	void ConfirmPlacement();
	void CancelPlacement();
	void TrySelectObject();
	void RotateObject(float Direction);
	bool IsPreviewMode() const { return bIsPreview; }
	void RemoveObject();

	virtual void PreparePlacement_Implementation(const FPlaceableItemData& ItemData) override;

protected:
	virtual void BeginPlay() override;

private:
	UObjectPlacementComponent();
	void UpdatePlacementPreview();
	void ResetPlacement();
	void SetupPreview();
	
	UPROPERTY()
	UStatSubsystem* StatSubsystem;
	
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

	UPROPERTY()
	UPlaceableItemSubsystem* PlaceableItemSubsystem;

	bool bIsPreview = false;
	bool bIsNewPlacing = false;
	float CurrentRotationExtent = 0.f;
	float PreviewUpdateInterval = 0.016f;
	float DoubleClickThreshold = 0.3f;
	float LastEditStartTime;
	FTimerHandle PlacementTimerHandle;
	FTransform PrevTransform;
};
