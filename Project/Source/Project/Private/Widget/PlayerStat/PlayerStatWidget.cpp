// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStat/PlayerStatWidget.h"
#include "Components/TextBlock.h"

// 스텟이 변경되면 업데이트
void UPlayerStatWidget::UpdateStats(const TMap<EPlayerStatType, int32>& InStats)
{
	for (const auto& Stat : InStats)
	{
		if (UTextBlock* TextBlock = Stat_Map_TextBlocks.FindRef(Stat.Key))
		{
			TextBlock->SetText(FText::AsNumber(Stat.Value));
		}
	}
}

void UPlayerStatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Stat_Map_TextBlocks.Add(EPlayerStatType::Strength, Strength_TextBlock);
}
