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
class UImage;

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

	// UPROPERTY(meta =(BindWidget))
	// UTextBlock* Direction_TextBlock;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Direction_Image;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Right_Texture;

	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Left_Texture;

	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Up_Texture;

	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Down_Texture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Punch_Texture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pattern Images")
	UTexture2D* Start_Texture;
	
	
	UPROPERTY()
	UBoxingActivityComponent* BoxingActivityComponent;
};
