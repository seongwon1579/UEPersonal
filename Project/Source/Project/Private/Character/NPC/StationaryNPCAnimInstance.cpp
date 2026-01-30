// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/StationaryNPCAnimInstance.h"

#include "DebugHelper.h"

void UStationaryNPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!bIsAnimDataReady) return;
	if (IdleAnimData.Num() <= 0) return;
	
	if (!bIsIdleVariation)
	{
		BaseTimer += DeltaSeconds;
		
		if (BaseTimer >= 10.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Base"));
			ChangeAnimState(); 
			BaseTimer = 0.f; 
			bIsIdleVariation = true;
		}
		return;
	}

	// loop 애니메이션에서는 루프 시간 동안 계속 
	if (CurrentIdlePhase == EIdlePhase::Loop)
	{
		LoopTimer += DeltaSeconds;
        
		if (LoopTimer >= IdleAnimData[CurrentIndex].LoopDuration)
		{
			CurrentIdlePhase = EIdlePhase::End;
		}
	}
}

// 애니메이션을 가중치에 따라 랜덤으로 변경한다.
void UStationaryNPCAnimInstance::ChangeAnimState()
{
	float TotalWeight = 0.f;
	// 모든 애니메이션의 가중치를 더한다.
	for (const FIdleAnimData& Data : IdleAnimData)
	{
		TotalWeight += Data.Weight;
	}

	// 총 가중치에서 랜덤으로 재생할 가중치를 구한다.
	float Random = FMath::FRandRange(0.f, TotalWeight);
	
	UE_LOG(LogTemp, Warning, TEXT("Weight: %f"),Random);

	float Accumulated = 0.f;

	for (int32 i = 0; i < IdleAnimData.Num(); i++)
	{
		Accumulated += IdleAnimData[i].Weight;
		// 재생할 애니메이션을 찾는다.
		if (Accumulated >= Random)
		{
			CurrentIndex = i;
			
			// ABP State Machine에서 사용할 애니메이션을 설정한다.
			CurrentStartAnim = IdleAnimData[i].StartAnim;
			CurrentLoopAnim = IdleAnimData[i].LoopAnim;
			CurrentEndAnim = IdleAnimData[i].EndAnim;
			
			CurrentIdlePhase = EIdlePhase::Start;
			LoopTimer = 0.f;
			return;
		}
	}
}

void UStationaryNPCAnimInstance::PlayVariation()
{
	// if (bIsIdleVariation) return;
	//
	// ChangeAnimState();
	// bIsIdleVariation = true;
}

// Start 애니메이션이 끝나면 Loop로
void UStationaryNPCAnimInstance::AnimNotify_StartFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("StartFinished"))
	CurrentIdlePhase = EIdlePhase::Loop;
	LoopTimer = 0.f;
}

// End 애니메이션이 끝나면 애니메이션을 변경한다.
void UStationaryNPCAnimInstance::AnimNotify_EndFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("EndFinished"))
	//ChangeAnimState();
	bIsIdleVariation = false;
}
