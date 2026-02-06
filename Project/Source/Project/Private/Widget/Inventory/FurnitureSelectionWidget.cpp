// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/FurnitureSelectionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Widget/Inventory/FurnitureSlotWidget.h"
#include "Goods/Data/FFurnitureItemData.h"

void UFurnitureSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Furniture_Button->OnClicked.AddDynamic(this, &UFurnitureSelectionWidget::Test);
	//PopulateGrid(10);
}

void UFurnitureSelectionWidget::PopulateGrid(const TArray<FFurnitureItemData*>& DataArray)
{
	
	if (!UniformGridPanel || !FurnitureSlot)
		return;
	
	UniformGridPanel->ClearChildren();

	UniformGridPanel->SetMinDesiredSlotWidth(160.f);
	UniformGridPanel->SetMinDesiredSlotHeight(160.f);
	UniformGridPanel->SetSlotPadding(FMargin(30.f));
	
	int32 Columns = 2;
    
	for (int32 i = 0; i < DataArray.Num(); i++)
	{
		UFurnitureSlotWidget* NewWidget = CreateWidget<UFurnitureSlotWidget>(this, FurnitureSlot);
		if (NewWidget)
		{
			int32 Row = i / Columns;
			int32 Col = i % Columns;
            
			UUniformGridSlot* GridSlot = UniformGridPanel->AddChildToUniformGrid(NewWidget, Row, Col);
			// GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			// GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
			GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			
			NewWidget->SetupSlot(DataArray[i]);
		}
	}
}

void UFurnitureSelectionWidget::Some()
{
	TArray<FFurnitureItemData*> temp;
	PopulateGrid(temp);
}


