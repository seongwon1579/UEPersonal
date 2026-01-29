// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StationaryNPCAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "MovableNPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMovableNPCAnimInstance : public UStationaryNPCAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "NPCAnim")
	UAnimSequence* WalkAnim;
};
