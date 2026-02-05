// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UISubSystem.generated.h"

/**
 * 
 */
class UPlaceActorWidget;
class UBoxingPatternWidget;
class UInteractionWidget;

class UBoxingActivityComponent;

UCLASS()
class PROJECT_API UUISubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	UBoxingPatternWidget* BoxingPatternWidget;
	
	UPROPERTY()
	UPlaceActorWidget* PlaceActorWidget;
	
	UPROPERTY()
	UInteractionWidget* InteractionWidget;
	
	// 물건 배치
	void ShowPlaceActorWidget();
	void HidePlaceActorWidget();
	
	// 복싱
	void ShowBoxingPatternWidget(UBoxingActivityComponent* InBoxingActivityComponent);
	void HideBoxingPatternWidget();
	
	// 인터렉션
	void ShowInteractionWidget();
	void HideInteractionWidget();
	
	void RegisterWidgets(UPlaceActorWidget* InPlaceActorWidget, UBoxingPatternWidget* InBoxingPatternWidget, UInteractionWidget* InInteractionWidget );
};
