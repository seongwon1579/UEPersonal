// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/PlaceableItemSlotWidget.h"

#include "DebugHelper.h"
#include "Character/Player/Component/Placement/ObjectPlacementComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Goods/Data/FPlaceableItemData.h"


//슬롯을 세팅한다.
void UPlaceableItemSlotWidget::SetupSlot(FPlaceableItemData* Data)
{
	FurnitureItemData = Data;  

	if (Data->Image)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(Data->Image);
		Brush.ImageSize = FVector2D(140.f, 140.f);  
		Brush.DrawAs = ESlateBrushDrawType::Image;
		Brush.ImageType = ESlateBrushImageType::FullColor;

		FSlateBrush HoveredBrush = Brush;
		HoveredBrush.TintColor = FSlateColor(FLinearColor(1.2f, 1.2f, 1.2f, 1.f));

		FSlateBrush PressedBrush = Brush;
		PressedBrush.TintColor = FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.f));

		FButtonStyle NewStyle = FurnitureIcon_Button->GetStyle();
		NewStyle.Normal = Brush;
		NewStyle.Hovered = HoveredBrush;
		NewStyle.Pressed = PressedBrush;
		NewStyle.Disabled = Brush;

		FurnitureIcon_Button->SetStyle(NewStyle);
	}
	
	FurnitureSlotName_TextBlock->SetText(FText::AsNumber(Data->Strength));
}

// 버튼을 클릭시 물체 배치를 구현할 수 있는 플레이어이면 배치에 필요한 정보를 넘긴다.
void UPlaceableItemSlotWidget::OnButtonClicked()
{
	if (!FurnitureItemData || !PlacementComponent) return;
	
	IObjectPlacementInterface::Execute_PreparePlacement(PlacementComponent, *FurnitureItemData);
}

void UPlaceableItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (FurnitureIcon_Button)
	{
		FurnitureIcon_Button->OnClicked.AddDynamic(this, &UPlaceableItemSlotWidget::OnButtonClicked);
	}

	// 컴포넌트 캐싱
	PlayerController = GetOwningPlayer();
	if (PlayerController && PlayerController->GetPawn())
	{
		PlacementComponent = PlayerController->GetPawn()->FindComponentByClass<UObjectPlacementComponent>();
	}
}
