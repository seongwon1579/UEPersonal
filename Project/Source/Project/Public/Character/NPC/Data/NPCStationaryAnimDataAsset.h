// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UAnimSequence* IdleAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* GreetingAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimSequence* TalkAnim;
	
	// AnimInstance에 AnimSequence를 데이터 어셋으로 초기화
	virtual void SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance);
};
