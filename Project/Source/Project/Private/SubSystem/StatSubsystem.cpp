// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/StatSubsystem.h"
#include "SubSystem/UISubSystem.h"
#include "SubSystem/Data/ContentData.h"
#include "Widget/PlayerStat/PlayerStatWidget.h"

// 액티비티를 즐기고나서 보상을 적용한다.
void UStatSubsystem::ApplyReward(const FStatReward& StatReward)
{
	for (const auto& Reward : StatReward.Stats)
	{
		int32& Amount = CurrentStats.FindOrAdd(Reward.Key);
		Amount += Reward.Value;
	}
	if (!UISubSystem) return;
	
	UPlayerStatWidget* PlayerStatWidget = UISubSystem->GetPlayerStatWidget();
	
	if (!PlayerStatWidget) return;
	
	PlayerStatWidget->UpdateStats(CurrentStats);
}

void UStatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Collection.InitializeDependency<UUISubSystem>();

	UISubSystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	
	for (int32 i = 0; i < static_cast<int32>(EPlayerStatType::End); i++)
	{
		CurrentStats.Add(static_cast<EPlayerStatType>(i), 0);
	}
}
