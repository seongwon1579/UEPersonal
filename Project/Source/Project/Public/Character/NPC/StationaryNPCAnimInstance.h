// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "Animation/AnimInstance.h"
#include "Character/NPC/Data/IdleAnimData.h"
#include "StationaryNPCAnimInstance.generated.h"

/**
 * 
 */

enum class EDialogueReaction : uint8;

UENUM()
enum class EIdlePhase : uint8
{
	None, Start, Loop, End,
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
	virtual void AnimNotify_EndFinished();
	
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
	EIdlePhase CurrentIdlePhase = EIdlePhase::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IdleSet Data")
	TArray<FIdleAnimData> IdleAnimData;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	TMap<EDialogueReaction, UAnimMontage*> ReactionMontages;
	
	void SetupIdleParams(float InIdleBaseDuration, bool bInIsReady);
	void StartDialogue();
	void EndDialogue();
	void PlayReaction(EDialogueReaction Reaction);

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	float IdleBaseTimer = 0.f;
	
private:
	void SelectRandomIdleSet();
	void UpdateBaseIdle(float DeltaSeconds);
	void UpdateIdleVariation(float DeltaSeconds);
	
	bool bIsAnimDataReady = false;
	bool bIsDialogue = false;
	bool bIsInDialogue = false;
	float IdleSetTimer = 0.f;
	int32 CurrentIndex = 0;
	float IdleBaseDuration = 0.f;
};
