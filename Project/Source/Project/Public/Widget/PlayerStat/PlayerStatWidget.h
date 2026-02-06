// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubSystem/Data/ContentData.h"

#include "PlayerStatWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class PROJECT_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateStats(const TMap<EPlayerStatType, int32>& InStats);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Strength_TextBlock;

	TMap<EPlayerStatType, TObjectPtr<UTextBlock>> Stat_Map_TextBlocks;
};
