// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Data/NPCMovableAnimDataAsset.h"
#include "Character/NPC/MovableNPCAnimInstance.h"

// 부모의 AnimSequence를 할당하고 캐스팅하여 자식도 할당을 마친다.
void UNPCMovableAnimDataAsset::SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance)
{
	Super::SetupAnimationInstance(AnimInstance);
	
	UMovableNPCAnimInstance* MovableNPCAnimInstance = Cast<UMovableNPCAnimInstance>(AnimInstance);
	
	if (!MovableNPCAnimInstance) return;
	
	MovableNPCAnimInstance->WalkAnim = WalkAnim;
}
