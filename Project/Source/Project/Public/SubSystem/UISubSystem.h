// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubSystem.generated.h"

/**
 * 
 */
class UPlaceableItemInventoryWidget;
class UBoxingPatternWidget;
class UInteractionWidget;
class UPlayerStatWidget;
class UDialogueWidget;

class UBoxingActivityComponent;
class UDialogueComponent;

// TODO: 자동화 필요 
UCLASS()
class PROJECT_API UUISubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBoxingPatternWidget* BoxingPatternWidget;

	UPROPERTY()
	UPlaceableItemInventoryWidget* PlaceActorWidget;

	// UPROPERTY()
	// UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UPlayerStatWidget* PlayerStatWidget;
	
	UPROPERTY()
	UDialogueWidget* DialogueWidget;

	// 물건 배치
	UPlaceableItemInventoryWidget* GetPlaceableItemInventoryWidget() {return PlaceActorWidget;};
	void ShowPlaceActorWidget();
	void HidePlaceActorWidget();

	// 복싱
	void ShowBoxingPatternWidget(UBoxingActivityComponent* InBoxingActivityComponent);
	void HideBoxingPatternWidget();

	// // 인터렉션
	// void ShowInteractionWidget();
	// void HideInteractionWidget();

	// 스텟
	// UPlayerStatWidget* GetPlayerStatWidget() { return PlayerStatWidget; };
	// UFUNCTION(blueprintCallable)
	// void ShowPlayerStatWidget();
	// void HidePlayerStatWidget();
	
	// 대화
	UDialogueWidget* GetDialogueWidget() { return DialogueWidget; };
	void ShowDialogueWidget(UDialogueComponent* InDialogueComponent);
	void HideDialogueWidget();

	void RegisterWidgets(
		UPlaceableItemInventoryWidget* InPlaceActorWidget,
		UBoxingPatternWidget* InBoxingPatternWidget,
		UDialogueWidget* InDialogueWidget);
};

