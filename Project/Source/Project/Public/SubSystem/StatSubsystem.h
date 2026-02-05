// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "SubSystem/Data/ContentData.h"
#include "StatSubsystem.generated.h"

/**
 * 
 */


UCLASS()
class PROJECT_API UStatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ApplyReward(const FStatReward& StatReward);

private:
	UPROPERTY()
	TMap<EPlayerStatType, int32> CurrentStats;
};
