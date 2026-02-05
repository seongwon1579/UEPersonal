// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/Player/Component/Activity/Data/BoxingData.h"

#include "BoxingPatternWidget.generated.h"

/**
 * 
 */
class UBoxingActivityComponent;
class UTextBlock;

UCLASS()
class PROJECT_API UBoxingPatternWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitWidget(UBoxingActivityComponent* InComponent);

protected:
	virtual void NativeDestruct() override;

private:
	void HandleShowPattern(EPunchDirection Direction);
	void HandlePatternDisplayComplete();

	UPROPERTY(meta =(BindWidget))
	UTextBlock* Direction_TextBlock;
	
	UPROPERTY()
	UBoxingActivityComponent* BoxingActivityComponent;
};
