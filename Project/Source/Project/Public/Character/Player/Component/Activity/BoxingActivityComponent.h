// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Activity/BoxingActivityInterface.h"
#include "Character/Player/Component/Activity/Data/BoxingData.h"

#include "BoxingActivityComponent.generated.h"

class UBoxingActivityInputComponent;
class UStatSubsystem;
class UGameContentSubsystem;
class UUISubSystem;
class UCharacterMovementComponent;
class AnimInstance;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowPattern, EPunchDirection)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UBoxingActivityComponent : public UActorComponent, public IBoxingActivityInterface
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	virtual bool IsBoxing() const override;
	UFUNCTION()
	virtual void StartBoxing() override;
	void OnPunchInput();
	void OnDirectionInput(EPunchDirection Input); 
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* PunchMontage;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* FailMontage;
	UPROPERTY()
	TArray<EPunchDirection> CurrentPattern;
	UPROPERTY()
	UBoxingActivityInputComponent* BoxingInputComponent;
	
	FOnShowPattern OnShowPattern;

private:
	UBoxingActivityComponent();
	virtual void BeginPlay() override;
	
	void GeneratePattern();
	void OnPatternFail();
	void OnPunchAnimEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnFailAnimEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnPatternStart();
	void OnPatternDisplay();
	void AddReward();
	void OnPatternSuccess();
	void SetABPBoxingState(bool bBoxing);
	
	bool bIsBoxing = false;
	bool bIsFail = false;
	bool bPatternCompleted;
	
	int32 CurrentPatternIndex;
	int32 PatternDisplayIndex;
	int32 AccumulatedStrength;
	int32 PatternLength;
	
	UPROPERTY()
	UUISubSystem* UISubsystem;
	UPROPERTY()
	UStatSubsystem* StatSubsystem;
	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;
	UPROPERTY()
	UAnimInstance* AnimInstance;

	FTimerHandle TimerHandle;
};
