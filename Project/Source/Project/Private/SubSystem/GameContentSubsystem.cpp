// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/GameContentSubsystem.h"
#include "SubSystem/StatSubsystem.h"
#include "Engine/GameInstance.h" 
#include "SubSystem/Data/ContentData.h"
#include "Subsystems/GameInstanceSubsystem.h"

void UGameContentSubsystem::ReportActivityResult(const FStatReward& Result)
{
}

bool UGameContentSubsystem::CanUnlock(EUnlockableType Type)
{
	return false;
}

bool UGameContentSubsystem::IsUnlockableInProgress() const
{
	return false;
}

void UGameContentSubsystem::StartUnlockable(EUnlockableType Type)
{
}

void UGameContentSubsystem::EndUnlockable()
{
}

void UGameContentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency<UStatSubsystem>();
	Super::Initialize(Collection);

	StatSubsystem = GetGameInstance()->GetSubsystem<UStatSubsystem>();
	
	// FStatReward TestReward;
	//
	// TestReward.Stats.Add(EPlayerStatType::Strength, 10);
	
	// StatSubsystem->ApplyReward(TestReward);
}
