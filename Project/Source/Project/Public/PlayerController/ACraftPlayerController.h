// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ACraftPlayerController.generated.h"

/**
 * 
 */

class UFurnitureSelectionWidget;
UCLASS()
class PROJECT_API AACraftPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UFurnitureSelectionWidget> WidgetClass;
	
	UPROPERTY()
	UFurnitureSelectionWidget* FurnitureWidget;
	
};
