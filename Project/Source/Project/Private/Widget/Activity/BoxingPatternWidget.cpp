// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Activity/BoxingPatternWidget.h"
#include "Character/Player/Component/Activity/Data/BoxingData.h"
#include "Components/Image.h"

void UBoxingPatternWidget::BindToPatternDelegate(FOnShowPattern& InDelegate)
{
	UnbindToPatternDelegate();

	BoundDelegate = &InDelegate;
	PatternDelegateHandle = InDelegate.AddUObject(this, &UBoxingPatternWidget::HandleShowPattern);
}

void UBoxingPatternWidget::UnbindToPatternDelegate()
{
	if (BoundDelegate)
	{
		BoundDelegate->Remove(PatternDelegateHandle);
		BoundDelegate = nullptr;
	}
}

void UBoxingPatternWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DirectionImages = {
		{EPunchDirection::Left, Left_Direction_Image},
		{EPunchDirection::Right, Right_Direction_Image},
		{EPunchDirection::Up, Up_Direction_Image},
		{EPunchDirection::Down, Down_Direction_Image},
		{EPunchDirection::Punch, Punch_Direction_Image}
	};

	for (const auto& Image : DirectionImages)
	{
		Image.Value->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBoxingPatternWidget::NativeDestruct()
{
	UnbindToPatternDelegate();

	Super::NativeDestruct();
}

void UBoxingPatternWidget::HandleShowPattern(EPunchDirection Direction)
{
	for (const auto& Image : DirectionImages)
	{
		Image.Value->SetVisibility(ESlateVisibility::Hidden);
	}

	if (UImage* FoundImage = DirectionImages.FindRef(Direction))
	{
		FoundImage->SetVisibility(ESlateVisibility::Visible);
	}
}
