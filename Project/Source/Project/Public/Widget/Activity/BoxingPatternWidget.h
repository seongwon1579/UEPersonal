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
	void BindToPatternDelegate(FOnShowPattern& InDelegate);
	void UnbindToPatternDelegate();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void HandleShowPattern(EPunchDirection Direction);
	
	FDelegateHandle PatternDelegateHandle;
	FOnShowPattern* BoundDelegate = nullptr;
	
	UPROPERTY()
	TMap<EPunchDirection, UImage*> DirectionImages;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Left_Direction_Image;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Right_Direction_Image;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Up_Direction_Image;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Down_Direction_Image;
	
	UPROPERTY(meta =(BindWidget))
	UImage* Punch_Direction_Image;
	
	UPROPERTY()
	UBoxingActivityComponent* BoxingActivityComponent;
};
