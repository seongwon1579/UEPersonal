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
class UPlayerStatWidget;
class UPlaceableItemInventoryWidget;
class UBoxingPatternWidget;
class UDialogueWidget;

UCLASS()
class PROJECT_API AAMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPlaceableItemInventoryWidget> PlaceActorWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBoxingPatternWidget> BoxingPatternWidgetClass;
	
	// UPROPERTY(EditAnywhere, Category = "UI")
	// TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	
	// UPROPERTY(EditAnywhere, Category = "UI")
	// TSubclassOf<UPlayerStatWidget> PlayerStatWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;	
	
	UPROPERTY()
	UPlaceableItemInventoryWidget* PlaceActorWidget;
	
	UPROPERTY()
	UBoxingPatternWidget* BoxingPatternWidget;
	
	// UPROPERTY()
	// UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UUISubSystem* UISubSystem;
	
	UPROPERTY()
	UPlayerStatWidget* PlayerStatWidget;
	
	UPROPERTY()
	UDialogueWidget* DialogueWidget;

private:
	void CreateWidgets();
};
