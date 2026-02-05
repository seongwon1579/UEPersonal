// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Activity/BoxingPatternWidget.h"

#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "Components/TextBlock.h"

void UBoxingPatternWidget::InitWidget(UBoxingActivityComponent* InComponent)
{
	BoxingActivityComponent = InComponent;

	if (!BoxingActivityComponent) return;

	BoxingActivityComponent->OnShowPattern.AddUObject(this, &UBoxingPatternWidget::HandleShowPattern);
}

void UBoxingPatternWidget::NativeDestruct()
{
	if (!BoxingActivityComponent) return;
	BoxingActivityComponent->OnShowPattern.RemoveAll(this);

	Super::NativeDestruct();
}

void UBoxingPatternWidget::HandleShowPattern(EPunchDirection Direction)
{
	if (!Direction_TextBlock) return;

	switch (Direction)
	{
		
	case EPunchDirection::None:
		{
			Direction_TextBlock->SetText(FText::FromString(TEXT("")));
			break;
		}
	case EPunchDirection::Left:
		{
			Direction_TextBlock->SetText(FText::FromString(TEXT("<")));
			break;
		}
	case EPunchDirection::Right:
		{
			Direction_TextBlock->SetText(FText::FromString(TEXT(">")));
			break;
		}
	case EPunchDirection::Up:
		{
			Direction_TextBlock->SetText(FText::FromString(TEXT("^")));
			break;
		}
	case EPunchDirection::Punch:
		{
			Direction_TextBlock->SetText(FText::FromString(TEXT("PUNCH!")));
			break;
		}
	}
}

void UBoxingPatternWidget::HandlePatternDisplayComplete()
{
}
