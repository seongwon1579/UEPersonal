// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.generated.h"

/**
 * 
 */
class UPlaceActorWidget;
class APlayerController;
UCLASS()
class PROJECT_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	UUIManager();
	
	UPROPERTY()
	TSubclassOf<UPlaceActorWidget> PlaceWidget;
	
	UPROPERTY()
	APlayerController* Controller;
	
	void ShowPlaceActorWidget();
	void Initialize(APlayerController* PC, TSubclassOf<UPlaceActorWidget> Widget);
};
