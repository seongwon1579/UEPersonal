// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/BoxingData.h"
#include "BoxingActivityInputComponent.generated.h"

class UInputMappingContext;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDirectionInput, EPunchDirection);
DECLARE_MULTICAST_DELEGATE(FOnPunchInput);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UBoxingActivityInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void EnableBoxingInput(bool Enable);
	
	FOnDirectionInput OnDirectionInputDelegate;
	FOnPunchInput OnPunchInputDelegate;

private:
	UBoxingActivityInputComponent();
	virtual void BeginPlay() override;
	void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent);
	void OnLeftInput();
	void OnRightInput();
	void OnUpInput();
	void OnDownInput();
	void OnPunchInput();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* BoxingMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* UpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DownAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PunchAction;

	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem;
};
