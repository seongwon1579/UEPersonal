// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCStationaryAnimDataAsset.h"
#include "Engine/DataAsset.h"
#include "NPCMovableAnimDataAsset.generated.h"

/**
 * 
 */
class UAnimSequence;

UCLASS()
class PROJECT_API UNPCMovableAnimDataAsset : public UNPCStationaryAnimDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* WalkAnim;
	
	virtual void SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance) override;
};
