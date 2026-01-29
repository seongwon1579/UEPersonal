// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "StationaryNPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStationaryNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "NPCAnim")
	UAnimSequence* IdleAnim;

	UPROPERTY()
	UAnimSequence* GreetingAnim;

	UPROPERTY()
	UAnimSequence* TalkAnim;
	
	UPROPERTY(BlueprintReadOnly, Category = "NPCAnim")
	bool bIsAnimDataReady;
};
