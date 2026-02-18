// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/MovableNPCAnimInstance.h"


void UMovableNPCAnimInstance::AnimNotify_EndFinished()
{
	Super::AnimNotify_EndFinished();
	SetIdleCycleCompleted(true);
}

void UMovableNPCAnimInstance::SelectIdleSet() 
{
	if (IdleAnimData.Num() <= 0) return;

	CurrentStartAnim = IdleAnimData[CurrentIndex].StartAnim;
	CurrentLoopAnim = IdleAnimData[CurrentIndex].LoopAnim;
	CurrentEndAnim = IdleAnimData[CurrentIndex].EndAnim;

	CurrentIndex = (CurrentIndex + 1) % IdleAnimData.Num();
}

void UMovableNPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Owner) return;
	// 전이조건
	bIsMoving = Owner->GetVelocity().Size() > 10.f;
	
	if (!bIsMoving)
	{
		Super::NativeUpdateAnimation(DeltaSeconds);
	}
}

void UMovableNPCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = TryGetPawnOwner();
}
