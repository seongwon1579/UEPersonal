// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubSystem.generated.h"

/**
 * 
 */
class UPlaceActorWidget;
class UBoxingPatternWidget;
class UInteractionWidget;
class UPlayerStatWidget;

class UBoxingActivityComponent;

// TODO: 자동화 필요 
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
	
	UPROPERTY()
	UPlayerStatWidget* PlayerStatWidget;
	
	// 물건 배치
	UFUNCTION(blueprintCallable)
	void ShowPlaceActorWidget();
	void HidePlaceActorWidget();
	
	// 복싱
	void ShowBoxingPatternWidget(UBoxingActivityComponent* InBoxingActivityComponent);
	void HideBoxingPatternWidget();
	
	// 인터렉션
	void ShowInteractionWidget();
	void HideInteractionWidget();
	
	// 스텟
	UPlayerStatWidget* GetPlayerStatWidget() { return PlayerStatWidget;};
	UFUNCTION(blueprintCallable)
	void ShowPlayerStatWidget();
	void HidePlayerStatWidget();
	
	FORCEINLINE void RegisterWidgets(UPlaceActorWidget* InPlaceActorWidget, UBoxingPatternWidget* InBoxingPatternWidget, UInteractionWidget* InInteractionWidget, UPlayerStatWidget* InPlayerStatWidget );
};
