// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MovableNPC.generated.h"

/**
 * 
 */
class USplineComponent;
class UNPCMovableAnimDataAsset;
class UMovableNPCAnimInstance;

UCLASS()
class PROJECT_API AMovableNPC : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USplineComponent* SplineComp;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 150.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationStrength = 300.f;

private:
	AMovableNPC();
	void MoveAlongSpline(float DeltaSeconds);
	void HandleWaiting();
	
	UPROPERTY()
	UMovableNPCAnimInstance* AnimInstance = nullptr;
	
	bool bIsWaiting = false;
	bool bMovingForward = true;
	float CurrentDistance = 0.f;
	float SplineLength = 0.f;
};
