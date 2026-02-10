// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/PlaceableItemSelectionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "CommonButtonBase.h"
#include "DebugHelper.h"
#include "Components/WidgetSwitcher.h"

#include "Widget/Inventory/PlaceableItemSlotWidget.h"


void UPlaceableItemSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GridPanels.Add(EPlaceableItemType::Building, Building_GridPanel);
	GridPanels.Add(EPlaceableItemType::Interior, Interior_GridPanel);
	GridPanels.Add(EPlaceableItemType::Exterior, Exterior_GridPanel);

	Building_Button->OnClicked().AddLambda([this]()
	{
		Switcher->SetActiveWidgetIndex(0);
	});
	
	Interior_Button->OnClicked().AddLambda([this]()
	{
		Switcher->SetActiveWidgetIndex(1);
	});

	Exterior_Button->OnClicked().AddLambda([this]()
	{
		Switcher->SetActiveWidgetIndex(2);
	});
}

void UPlaceableItemSelectionWidget::PopulateGrid(EPlaceableItemType ItemType ,const TArray<FPlaceableItemData*>& DataArray)
{
	UUniformGridPanel* GridPanel = GridPanels.FindRef(ItemType);
	
	
	if (!GridPanel || !PlaceableItemSlot)
		return;
	
	
	GridPanel->ClearChildren();
	GridPanel->SetMinDesiredSlotWidth(160.f);
	GridPanel->SetMinDesiredSlotHeight(160.f);
	GridPanel->SetSlotPadding(FMargin(30.f));

	int32 Columns = 2;

	for (int32 i = 0; i < DataArray.Num(); i++)
	{
		UPlaceableItemSlotWidget* NewWidget = CreateWidget<UPlaceableItemSlotWidget>(this, PlaceableItemSlot);
		if (NewWidget)
		{
			int32 Row = i / Columns;
			int32 Col = i % Columns;

			UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(NewWidget, Row, Col);
			// GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			// GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

			NewWidget->SetupSlot(DataArray[i]);
		}
	}
}
