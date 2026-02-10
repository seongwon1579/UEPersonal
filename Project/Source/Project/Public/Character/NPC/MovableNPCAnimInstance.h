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
	virtual void AnimNotify_EndFinished() override;
	
	bool IsIdleCycleCompleted() const { return bIsIdleCycleCompleted; }
	void SetIdleCycleCompleted(bool bIsCompleted) { bIsIdleCycleCompleted = bIsCompleted; }
	
	UPROPERTY(BlueprintReadOnly, Category = "NPCAnim")
	UAnimSequence* WalkAnim;
	
	UPROPERTY(BlueprintReadOnly, Category = "NPCAnim")
	bool bIsMoving;

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;
	
	UPROPERTY()
	APawn* Owner;

	bool bIsIdleCycleCompleted;
};
