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
	Super::Initialize(Collection);
	Collection.InitializeDependency<UStatSubsystem>();

	StatSubsystem = GetGameInstance()->GetSubsystem<UStatSubsystem>();
}
