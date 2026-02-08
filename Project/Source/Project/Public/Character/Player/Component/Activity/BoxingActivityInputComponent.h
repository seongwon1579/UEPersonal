// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoxingActivityInputComponent.generated.h"

class APlayerController;
class UBoxingActivityComponent;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UBoxingActivityInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBoxingActivityInputComponent();
	virtual void BeginPlay() override;
	void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent);
	void OnLeftInput();
	void OnRightInput();
	void OnUpInput();
	void OnDownInput();
	void OnPunchInput();
	void EnableBoxingInput(bool Enable);
	
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
	APlayerController* PlayerController;
	
	UPROPERTY()
	UBoxingActivityComponent* BoxingComponent;
	
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem;
};
