// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "PlacementInputComponent.generated.h"


class UInputMappingContext;
class UInputAction;
class UObjectPlacementComponent;
class UBoxingActivityComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UPlacementInputComponent : public UActorComponent
{
	GENERATED_BODY()
	/////////////////////////
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxingActivityComponent* BoxingComponent;
	///////////////////////
protected:
	virtual void BeginPlay() override;

private:
	UPlacementInputComponent();
	
	//////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* UpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EnterAction;
	
	
	///////////////////////////////////
	
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
	
	void BindInputAction(UEnhancedInputComponent* EnhancedInputComponent);
    
	void OnSelectObject(const FInputActionValue& Value);
	void OnRotateAction(const FInputActionValue& Value);
	void OnStartPlacement(const FInputActionValue& Value);
	void OnConfirmPlacement(const FInputActionValue& Value);
	void OnCancelPlacement(const FInputActionValue& Value);
	
	/////////////////////////
	
	void OnLeftInput();
	void OnRightInput();
	void OnUpInput();
	void OnSpaceInput();
	//void OnInteractionInput();
	
	////////////////////////
	
	
};
