// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameContentSubsystem.generated.h"

enum class EUnlockableType : uint8;
struct FStatReward;
class UStatSubsystem;
/**
 * 
 */
UCLASS()
class PROJECT_API UGameContentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ReportActivityResult(const FStatReward& Result);

	// 소비 컨텐츠를 할 수 있는지 체크
	UFUNCTION(BlueprintCallable)
	bool CanUnlock(EUnlockableType Type);

	// 현재 소비 컨텐츠 진행 중인지
	UFUNCTION(BlueprintCallable)
	bool IsUnlockableInProgress() const;

	// 소비 컨텐츠 시작
	UFUNCTION(BlueprintCallable)
	void StartUnlockable(EUnlockableType Type);

	// 소비 컨텐츠 종료
	UFUNCTION(BlueprintCallable)
	void EndUnlockable();

	// stat subsystem 캐싱
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	UPROPERTY()
	UStatSubsystem* StatSubsystem;
};
