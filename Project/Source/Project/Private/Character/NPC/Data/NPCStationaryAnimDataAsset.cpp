// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Data/NPCStationaryAnimDataAsset.h"

#include "Character/NPC/StationaryNPCAnimInstance.h"

void UNPCStationaryAnimDataAsset::SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance)
{
	if (!AnimInstance) return;
	
	AnimInstance->IdleAnim = IdleAnim;
	AnimInstance->GreetingAnim = GreetingAnim;
	AnimInstance->TalkAnim = TalkAnim;
}