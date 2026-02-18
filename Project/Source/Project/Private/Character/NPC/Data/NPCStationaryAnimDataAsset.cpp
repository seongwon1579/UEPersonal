// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Data/NPCStationaryAnimDataAsset.h"

#include "Character/NPC/StationaryNPCAnimInstance.h"

void UNPCStationaryAnimDataAsset::SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance)
{
	if (!AnimInstance) return;
	
	AnimInstance->IdleAnimData = IdleAnims;
	AnimInstance->CurrentBaseAnim = BaseAnim;
	AnimInstance->ReactionMontages = ReactionMontages;
}