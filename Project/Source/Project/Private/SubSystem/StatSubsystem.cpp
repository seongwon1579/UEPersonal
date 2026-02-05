// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/StatSubsystem.h"

#include "SubSystem/Data/ContentData.h"

// 액티비티를 즐기고나서 보상을 적용한다.
void UStatSubsystem::ApplyReward(const FStatReward& StatReward)
{	
	for (const auto& Reward : StatReward.Stats)
	{
		int32& Amount = CurrentStats.FindOrAdd(Reward.Key);
		Amount += Reward.Value;

	}
}
