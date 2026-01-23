// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FurnitureSlot.h"

#include "DebugHelper.h"
#include "Character/ObjectPlacementComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Goods/GoodsData/FFurnitureItemData.h"

//TODO: 필요없는 듯
void UFurnitureSlot::SetSizeBox(float Width, float Height)
{
	if (!FurnitureSlot_SizeBox) return;
	
	FurnitureSlot_SizeBox->SetWidthOverride(Width);
	FurnitureSlot_SizeBox->SetHeightOverride(Height);
}
//TODO: 버튼 설정
void UFurnitureSlot::SetupSlot(FFurnitureItemData* Data)
{
	FurnitureItemData = Data;
	
	if (Data->Image)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->Image);

		FSlateBrush HoveredBrush = Brush;
		HoveredBrush.TintColor = FSlateColor(FLinearColor(1.2f, 1.2f, 1.2f, 1.f));

		FSlateBrush PressedBrush = Brush;
		PressedBrush.TintColor = FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.f));
        
		FButtonStyle NewStyle = FurnitureIconBtn->GetStyle();
		NewStyle.Normal = Brush;
		NewStyle.Hovered = HoveredBrush;
		NewStyle.Pressed = PressedBrush;
		NewStyle.Disabled = Brush;
        
		FurnitureIconBtn->SetStyle(NewStyle);
	}

	if (!Data->Name.IsNone())
	{
		FurnitureSlot_Name_TextBlock->SetText(FText::FromName(Data->Name));
	}
}

void UFurnitureSlot::OnButtonClicked()
{
	if (!FurnitureItemData) return;
	
	Debug::Print("FurnitureSlot::OnButtonClicked()");
	
	APlayerController* PC = GetOwningPlayer();
	APawn* Pawn = PC->GetPawn();
	UObjectPlacementComponent* PlacementComp = Pawn->FindComponentByClass<UObjectPlacementComponent>();
    
	if (PlacementComp)
	{
		PlacementComp->TestMethod(FurnitureItemData);
	}
}

void UFurnitureSlot::NativeConstruct()
{
	Super::NativeConstruct();
	FurnitureIconBtn->OnClicked.AddDynamic(this, &UFurnitureSlot::OnButtonClicked);
}
