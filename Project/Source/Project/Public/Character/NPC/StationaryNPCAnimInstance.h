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
	// 애니메이션 끝날때 호출
	UFUNCTION()
	void AnimNotify_StartFinished();

	// 애니메이션 끝날때 호출
	UFUNCTION()
	void AnimNotify_EndFinished();
	
	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* GreetingAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* TalkAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* BaseAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentStartAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentLoopAnim;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* CurrentEndAnim;
	
	UPROPERTY(BlueprintReadOnly)
	EIdlePhase CurrentIdlePhase;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsIdleVariation = false;
	
	TArray<FIdleAnimData> IdleAnimData;
	
	void SetupIdleParams(float InIdleBaseDuration, bool bInIsReady);

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	void SelectRandomIdleSet();
	void UpdateBaseIdle(float DeltaSeconds);
	void UpdateIdleVariation(float DeltaSeconds);
	
	bool bIsAnimDataReady = false;
	float IdleSetTimer = 0.f;
	float IdleBaseTimer = 0.f;
	int32 CurrentIndex = 0;
	float IdleBaseDuration = 0.f;
};
