// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Activity/BoxingActivityInterface.h"
#include "Character/Player/Component/Activity/Data/BoxingData.h"

#include "BoxingActivityComponent.generated.h"

class UUISubSystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowPattern, EPunchDirection)
DECLARE_MULTICAST_DELEGATE(FOnHidePattern);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UBoxingActivityComponent : public UActorComponent, public IBoxingActivityInterface
{
	GENERATED_BODY()

	UBoxingActivityComponent();
public:	
	UFUNCTION(BlueprintCallable)
	virtual void StartBoxing() override;
	virtual void EndBoxing(const FStatReward& Reward) override;
	UFUNCTION(BlueprintCallable)
	virtual bool IsBoxing() const override;
	
	void OnSpaceBarInput();
	void OnDirectionInput(EPunchDirection Input); 
	
	UPROPERTY(BlueprintReadOnly)
	TArray<EPunchDirection> CurrentPattern;
	UFUNCTION(BlueprintCallable)
	void GeneratePattern();
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* PunchMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* FailMontage;
	
	FOnShowPattern OnShowPattern;
	
	FOnHidePattern OnHidePattern;

	
private:

	void HidePattern();
	void OnPatternTimeout();
	void FailPattern();
	void OnPunchMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnFailMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void StartPatternDisplay();
	void NextPatternDisplay();
	void HidePunchAndStartInput();
	
	bool bIsBoxing = false;
	bool bIsFail = false;
	bool bPatternCompleted;
	
	int32 CurrentPatternIndex;
	int32 DisplayPatternIndex;
	
	UUISubSystem* UISubsystem;
	
	FTimerHandle PatternTimerHandle;
	FTimerHandle DisplayTimerHandle;
};
