// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FurnitureSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Goods/GoodsData/FFurnitureItemData.h"


void UFurnitureSlot::SetSizeBox(float Width, float Height)
{
	if (!FurnitureSlot_SizeBox) return;
	
	FurnitureSlot_SizeBox->SetWidthOverride(Width);
	FurnitureSlot_SizeBox->SetHeightOverride(Height);
}
void UFurnitureSlot::SetupSlot(FFurnitureItemData* Data)
{
	if (Data->Thumbnail)
	{
		FurnitureSlot_Thumbnail_Image->SetBrushFromTexture(Data->Image);
	}

	FurnitureSlot_Name_TextBlock->SetText(FText::FromName(Data->Name));
}