// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class PROJECT_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInteractionType(const FText& Text);

private:
	UPROPERTY(meta =(BindWidget))
	UTextBlock* Interaction_TextBlock;
};
