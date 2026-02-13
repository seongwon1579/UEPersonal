// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Data/NPCStationaryAnimDataAsset.h"

#include "Character/NPC/StationaryNPCAnimInstance.h"

void UNPCStationaryAnimDataAsset::SetupAnimationInstance(UStationaryNPCAnimInstance* AnimInstance)
{
	if (!AnimInstance) return;
	
	AnimInstance->IdleAnimData = IdleAnims;
	AnimInstance->GreetingAnim = GreetingAnim;
	AnimInstance->TalkAnim = TalkAnim;
	AnimInstance->BaseAnim = BaseAnim;
	AnimInstance->ReactionMontages = ReactionMontages;
	
	// if (IdleAnims.Num() > 0)
	// {
	// 	AnimInstance->CurrentStartAnim = IdleAnims[0].StartAnim;
	// 	AnimInstance->CurrentEndAnim = IdleAnims[0].EndAnim;
	// 	AnimInstance->CurrentLoopAnim = IdleAnims[0].LoopAnim;
	// }
}