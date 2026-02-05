// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubSystem/Data/ContentData.h"
#include "UObject/Interface.h"
#include "BoxingActivityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBoxingActivityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IBoxingActivityInterface
{
	GENERATED_BODY()

public:
	virtual void StartBoxing() = 0;
	virtual void EndBoxing(const FStatReward& Reward) = 0;
	virtual bool IsBoxing() const = 0;
};
