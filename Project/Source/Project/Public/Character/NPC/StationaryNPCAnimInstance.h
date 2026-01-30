// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/NPC/Data/IdleAnimData.h"
#include "StationaryNPCAnimInstance.generated.h"

/**
 * 
 */

UENUM()
enum class EIdlePhase : uint8
{
	Start, Loop, End,	
};

UCLASS()
class PROJECT_API UStationaryNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	

	UPROPERTY()
	UAnimSequence* GreetingAnim;

	UPROPERTY()
	UAnimSequence* TalkAnim;
	
	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* BaseAnim;
	
	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentStartAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentLoopAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentEndAnim;

	TArray<FIdleAnimData> IdleAnimData;
	
	float LoopTimer;
	float BaseTimer;
	
	UPROPERTY(BlueprintReadOnly)
	EIdlePhase CurrentIdlePhase;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentIndex;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsAnimDataReady;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsIdleVariation;
	
	UFUNCTION()
	void AnimNotify_StartFinished();
	
	UFUNCTION()
	void AnimNotify_EndFinished();
	
	void ChangeAnimState();
	
	void PlayVariation();
	
	
};
