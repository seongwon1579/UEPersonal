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
UCLASS()
class PROJECT_API AMovableNPC : public ACharacter
{
	GENERATED_BODY()
	AMovableNPC();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Navigation", meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComp;
};
