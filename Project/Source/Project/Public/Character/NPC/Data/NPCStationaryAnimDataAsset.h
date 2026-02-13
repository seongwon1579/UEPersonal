// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPC/data/IdleAnimData.h"
#include "Dialogue/Data/DialogueData.h"
#include "NPCStationaryAnimDataAsset.generated.h"
/**
 * 
 */

class UStationaryNPCAnimInstance;
UCLASS()
class PROJECT_API UNPCStationaryAnimDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* BaseAnim = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TArray<FIdleAnimData> IdleAnims;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* GreetingAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* TalkAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations|Reaction")
	TMap<EDialogueReaction, UAnimMontage*> ReactionMontages;
	
	// AnimInstance에 AnimSequence를 데이터 에셋으로 초기화
	virtual void SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance);
};
