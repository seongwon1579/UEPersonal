// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/PlaceableItemSelectionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "DebugHelper.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

#include "Widget/Inventory/PlaceableItemSlotWidget.h"


void UPlaceableItemSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GridPanels.Add(EPlaceableItemType::Building, Building_GridPanel);
	GridPanels.Add(EPlaceableItemType::Interior, Interior_GridPanel);
	GridPanels.Add(EPlaceableItemType::Exterior, Exterior_GridPanel);

	Building_Button->OnClicked.AddDynamic(this, &UPlaceableItemSelectionWidget::OnBuildingClicked);
	Interior_Button->OnClicked.AddDynamic(this, &UPlaceableItemSelectionWidget::OnInteriorClicked);
	Exterior_Button->OnClicked.AddDynamic(this, &UPlaceableItemSelectionWidget::OnExteriorClicked);
	
}

void UPlaceableItemSelectionWidget::OnBuildingClicked()
{
	Switcher->SetActiveWidgetIndex(0);
}

void UPlaceableItemSelectionWidget::OnInteriorClicked()
{
	Switcher->SetActiveWidgetIndex(1);
}

void UPlaceableItemSelectionWidget::OnExteriorClicked()
{
	Switcher->SetActiveWidgetIndex(2);
}

void UPlaceableItemSelectionWidget::PopulateGrid(EPlaceableItemType ItemType ,const TArray<FPlaceableItemData*>& DataArray)
{
	UUniformGridPanel* GridPanel = GridPanels.FindRef(ItemType);
    
	if (!GridPanel || !PlaceableItemSlot)
		return;
    
	GridPanel->ClearChildren();
	GridPanel->SetSlotPadding(FMargin(15.f));

	int32 Columns = 2;

	for (int32 i = 0; i < DataArray.Num(); i++)
	{
		UPlaceableItemSlotWidget* NewWidget = CreateWidget<UPlaceableItemSlotWidget>(this, PlaceableItemSlot);
		if (NewWidget)
		{
			int32 Row = i / Columns;
			int32 Col = i % Columns;

			UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(NewWidget, Row, Col);
			GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
			GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Top);

			NewWidget->SetupSlot(DataArray[i]);
		}
	}
}

void UPlaceableItemSelectionWidget::RefreshAvailableItems(int32 Value)
{
	Strength_Value_TextBlock->SetText(FText::AsNumber(Value));
}
