// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "SubSystem/Data/ContentData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StatSubsystem.generated.h"

/**
 * 
 */
class UUISubSystem;

UCLASS()
class PROJECT_API UStatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ApplyReward(const FStatReward& StatReward);
	
	TMap<EPlayerStatType, int32> GetCurrentStats() {return CurrentStats;}

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY()
	TMap<EPlayerStatType, int32> CurrentStats;
	
	UPROPERTY()
	UUISubSystem* UISubSystem;
};
