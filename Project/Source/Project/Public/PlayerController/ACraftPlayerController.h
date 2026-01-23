// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ACraftPlayerController.generated.h"

/**
 * 
 */

class UUIManager;

class UPlaceActorWidget;
UCLASS()
class PROJECT_API AACraftPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPlaceActorWidget> WidgetClass;
	
	UPROPERTY()
	UPlaceActorWidget* PlaceActorWidget;
	
	UPROPERTY()
	UUIManager* UIManager;
	
};
