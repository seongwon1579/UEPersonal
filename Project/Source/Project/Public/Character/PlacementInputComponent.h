// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "PlacementInputComponent.generated.h"


class UInputMappingContext;
class UInputAction;
class UObjectPlacementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UPlacementInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlacementInputComponent();

	// Enhanced Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PlacementMappingContext;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* StartPlacingAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ConfirmPlacementAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CancelPlacementAction;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RotateAction;

	void OnRotateAction(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SelectObjectAction;

	void OnSelectObject(const FInputActionValue& Value);

	// 더블클릭 감지용
	float LastClickTime = 0.f;
	float DoubleClickThreshold = 0.3f; 

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	//void SetupInputComponent(class UInputComponent* PlayerInputComponent);
	

private:
	UPROPERTY()
	UObjectPlacementComponent* PlacementComponent;
    
	void OnStartPlacing(const FInputActionValue& Value);
	void OnConfirmPlacement(const FInputActionValue& Value);
	void OnCancelPlacement(const FInputActionValue& Value);

		
};
