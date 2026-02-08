// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Activity/BoxingPatternWidget.h"

#include "Character/Player/Component/Activity/BoxingActivityComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBoxingPatternWidget::InitWidget(UBoxingActivityComponent* InComponent)
{
	BoxingActivityComponent = InComponent;

	if (!BoxingActivityComponent) return;
	// 델리게이트 구독
	BoxingActivityComponent->OnShowPattern.AddUObject(this, &UBoxingPatternWidget::HandleShowPattern);
}

void UBoxingPatternWidget::NativeDestruct()
{
	if (!BoxingActivityComponent) return;
	// 델리게이트 구독 취소
	BoxingActivityComponent->OnShowPattern.RemoveAll(this);

	Super::NativeDestruct();
}

void UBoxingPatternWidget::HandleShowPattern(EPunchDirection Direction)
{
	//if (!Direction_TextBlock) return;
	
	UTexture2D* CurrentDirectionTexture = nullptr;

	switch (Direction)
	{
	case EPunchDirection::None:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT("")));
			Direction_Image->SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	case EPunchDirection::Left:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT("<")));
			CurrentDirectionTexture = Left_Texture;
			break;
		}
	case EPunchDirection::Right:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT(">")));
			CurrentDirectionTexture = Right_Texture;
			break;
		}
	case EPunchDirection::Up:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT("^")));
			CurrentDirectionTexture = Up_Texture;
			break;
		}
	case EPunchDirection::Down:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT("^")));
			CurrentDirectionTexture = Down_Texture;
			break;
		}
	case EPunchDirection::Punch:
		{
			//
			//Direction_TextBlock->SetText(FText::FromString(TEXT("PUNCH!")));
			CurrentDirectionTexture = Punch_Texture;
			break;
		}
	case EPunchDirection::Start:
		{
			//Direction_TextBlock->SetText(FText::FromString(TEXT("Start!")));
			CurrentDirectionTexture = Start_Texture;
			break;
		}
	}
	
	if (!CurrentDirectionTexture) return;
	
	Direction_Image->SetBrushFromTexture(CurrentDirectionTexture);
	Direction_Image->SetVisibility(ESlateVisibility::Visible);
}