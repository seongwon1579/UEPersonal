// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/FurnitureSlotWidget.h"

#include "DebugHelper.h"
#include "Character/Player/Component/Placement/ObjectPlacementComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Goods/Data/FFurnitureItemData.h"

//TODO: 필요없는 듯
void UFurnitureSlotWidget::SetSizeBox(float Width, float Height)
{
	if (!FurnitureSlot_SizeBox) return;

	FurnitureSlot_SizeBox->SetWidthOverride(Width);
	FurnitureSlot_SizeBox->SetHeightOverride(Height);
}

//슬롯을 세팅한다.
void UFurnitureSlotWidget::SetupSlot(FFurnitureItemData* Data)
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

// 버튼을 클릭시 물체 배치를 구현할 수 있는 플레이어이면 배치에 필요한 정보를 넘긴다.
void UFurnitureSlotWidget::OnButtonClicked()
{
	if (!FurnitureItemData || !PlacementComponent) return;
	
	IObjectPlacementInterface::Execute_PreparePlacement(PlacementComponent, *FurnitureItemData);
}

void UFurnitureSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// 버튼 이벤트 등록
	FurnitureIconBtn->OnClicked.AddDynamic(this, &UFurnitureSlotWidget::OnButtonClicked);

	// 컴포넌트 캐싱
	OwningPlayerController = GetOwningPlayer();
	PlacementComponent = OwningPlayerController->GetPawn()->FindComponentByClass<UObjectPlacementComponent>();
}
