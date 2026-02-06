// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "ObjectPlacementInputComponent.generated.h"


class UInputMappingContext;
class UInputAction;
class UObjectPlacementComponent;
class UBoxingActivityComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UObjectPlacementInputComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UObjectPlacementInputComponent();
	void BindInputAction(UEnhancedInputComponent* EnhancedInputComponent);
	void OnSelectObject(const FInputActionValue& Value);
	void OnRotateAction(const FInputActionValue& Value);
	void OnStartPlacement(const FInputActionValue& Value);
	void OnConfirmPlacement(const FInputActionValue& Value);
	void OnCancelPlacement(const FInputActionValue& Value);
	
	UPROPERTY()
	UObjectPlacementComponent* PlacementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlacementMappingContext;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* StartPlacementAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ConfirmPlacementAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* CancelPlacementAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SelectObjectAction;
	
	float LastClickTime = 0.f;
	float DoubleClickThreshold = 0.3f; 
	
};
