// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DanceActivityComponent.generated.h"

class UAnimInstance;
class UAnimMontage;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UCharacterMovementComponent;
class ACharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UDanceActivityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDanceActivityComponent();

	bool IsDancing() const { return bIsDancing; }

protected:
	virtual void BeginPlay() override;

private:
	void PlayDance(int32 Index);
	void OnDanceMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UPROPERTY()
	TObjectPtr<ACharacter> Character;

	// 1, 2, 3 키에 대응하는 몽타주
	UPROPERTY(EditAnywhere, Category = "Dance")
	TArray<TObjectPtr<UAnimMontage>> DanceMontages;

	// Enhanced Input
	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputMappingContext> DanceMappingContext;

	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance1Action;

	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance2Action;

	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance3Action;
	
	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance4Action;
	
	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance5Action;
	
	UPROPERTY(EditAnywhere, Category = "Dance|Input")
	TObjectPtr<UInputAction> Dance6Action;

	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;

	bool bIsDancing = false;
};
