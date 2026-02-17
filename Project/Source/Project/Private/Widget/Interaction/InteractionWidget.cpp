// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/InteractionWidget.h"
#include "Components/TextBlock.h"

void UInteractionWidget::SetInteractionType(const FText& Text)
{
	if (Interaction_TextBlock)
	{
		Interaction_TextBlock->SetText(Text);
	}
}
