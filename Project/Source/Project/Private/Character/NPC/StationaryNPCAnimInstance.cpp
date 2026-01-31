// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/StationaryNPCAnimInstance.h"

void UStationaryNPCAnimInstance::SetupIdleParams(float InIdleBaseDuration, bool bInIsReady)
{
	IdleBaseDuration = InIdleBaseDuration;
	bIsAnimDataReady = bInIsReady;
}

void UStationaryNPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!bIsAnimDataReady) return;
	
	if (!bIsIdleVariation)
	{
		UpdateBaseIdle(DeltaSeconds);
	}
	else
	{
		UpdateIdleVariation(DeltaSeconds);
	}
}

// 애니메이션을 가중치에 따라 랜덤으로 변경한다.
void UStationaryNPCAnimInstance::SelectRandomIdleSet()
{
	// 재생할 데이터가 없으면 early return
	if (IdleAnimData.Num() <= 0) return;
	
	float TotalWeight = 0.f;
	// 모든 애니메이션의 가중치를 더한다.
	for (const FIdleAnimData& Data : IdleAnimData)
	{
		TotalWeight += Data.Weight;
	}

	// 총 가중치에서 랜덤으로 재생할 가중치를 구한다.
	float CurrentWeight = FMath::FRandRange(0.f, TotalWeight);
	//UE_LOG(LogTemp, Warning, TEXT("Weight: %f"),Random);

	float Accumulated = 0.f;

	for (int32 i = 0; i < IdleAnimData.Num(); i++)
	{
		Accumulated += IdleAnimData[i].Weight;
		// 재생할 애니메이션을 찾는다.
		if (Accumulated >= CurrentWeight)
		{
			CurrentIndex = i;
			
			// ABP State Machine에서 사용할 애니메이션을 설정한다.
			CurrentStartAnim = IdleAnimData[i].StartAnim;
			CurrentLoopAnim = IdleAnimData[i].LoopAnim;
			CurrentEndAnim = IdleAnimData[i].EndAnim;
			return;
		}
	}
}

void UStationaryNPCAnimInstance::UpdateBaseIdle(float DeltaSeconds)
{
	IdleBaseTimer += DeltaSeconds;
    
	if (IdleBaseTimer >= IdleBaseDuration)
	{
		IdleBaseTimer = 0.f;
		SelectRandomIdleSet();
		bIsIdleVariation = true;
	}
}

// loop 애니메이션에서는 루프 시간 동안 계속 
void UStationaryNPCAnimInstance::UpdateIdleVariation(float DeltaSeconds)
{
	if (CurrentIdlePhase != EIdlePhase::Loop) return;
    
	IdleSetTimer += DeltaSeconds;
    
	if (IdleSetTimer >= IdleAnimData[CurrentIndex].LoopDuration)
	{
		CurrentIdlePhase = EIdlePhase::End;
	}
}

void UStationaryNPCAnimInstance::AnimNotify_StartFinished()
{
	//UE_LOG(LogTemp, Warning, TEXT("StartFinished"))
	
	// loop animation이 있는경우 loop duration 동안 loop 진행
	if (IdleAnimData[CurrentIndex].LoopAnim)
	{
		IdleSetTimer = 0.f;
		CurrentIdlePhase = EIdlePhase::Loop;
	}
	// loop가 없는 하나의 sequence로 이뤄진 애니메이션은 해당 애니메이션 진행 후 base로 이동
	else
	{
		bIsIdleVariation = false;
		CurrentIdlePhase = EIdlePhase::Start;
	}
}

// End 애니메이션이 끝나면 애니메이션을 변경한다.
void UStationaryNPCAnimInstance::AnimNotify_EndFinished()
{
	//UE_LOG(LogTemp, Warning, TEXT("EndFinished"))
	bIsIdleVariation = false;
	CurrentIdlePhase = EIdlePhase::Start;
}
