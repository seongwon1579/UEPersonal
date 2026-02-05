// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AMainPlayerController.generated.h"

/**
 * 
 */

class UInteractionWidget;
class UUISubSystem;

class UPlaceActorWidget;
class UBoxingPatternWidget;

UCLASS()
class PROJECT_API AAMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPlaceActorWidget> PlaceActorWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBoxingPatternWidget> BoxingPatternWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
	UPROPERTY()
	UPlaceActorWidget* PlaceActorWidget;
	
	UPROPERTY()
	UBoxingPatternWidget* BoxingPatternWidget;
	
	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UUISubSystem* UISubSystem;

private:
	void CreateWidgets();
};
