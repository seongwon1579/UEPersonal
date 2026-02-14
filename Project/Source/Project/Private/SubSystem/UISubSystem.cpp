// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem//UISubSystem.h"

#include "DebugHelper.h"
#include "Blueprint/UserWidget.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/Inventory/PlaceableItemInventoryWidget.h"
#include "Widget/Activity/BoxingPatternWidget.h"
#include "Widget/Dialogue/DialogueWidget.h"
#include "Widget/Interaction/InteractionWidget.h"
#include "Widget/PlayerStat/PlayerStatWidget.h"

void UUISubSystem::ShowPlaceActorWidget()
{
	if (!PlaceActorWidget) return;

	UPlaceableItemSubsystem* PlaceableItemSubsystem = GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	
	for (uint8 i = 0; i < static_cast<uint8>(EPlaceableItemType::End); i++)
	{
		EPlaceableItemType ItemType = static_cast<EPlaceableItemType>(i);
		TArray<FPlaceableItemData*> ItemData = PlaceableItemSubsystem->GetPlaceableItemData(ItemType);
		
		PlaceActorWidget->SetupWithData(ItemType, ItemData);
	}
	
	PlaceActorWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUISubSystem::HidePlaceActorWidget()
{
	if (!PlaceActorWidget) return;
	PlaceActorWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUISubSystem::ShowBoxingPatternWidget(UBoxingActivityComponent* InBoxingActivityComponent)
{
	if (!BoxingPatternWidget || !InBoxingActivityComponent) return;
	
	BoxingPatternWidget->InitWidget(InBoxingActivityComponent);
	BoxingPatternWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUISubSystem::HideBoxingPatternWidget()
{
	if (!BoxingPatternWidget) return;
	BoxingPatternWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUISubSystem::ShowInteractionWidget()
{
	if (!InteractionWidget) return;
	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUISubSystem::HideInteractionWidget()
{
	if (!InteractionWidget) return;
	InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUISubSystem::ShowPlayerStatWidget()
{
	if (!PlayerStatWidget) return;
	PlayerStatWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUISubSystem::HidePlayerStatWidget()
{
	if (!PlayerStatWidget) return;
	PlayerStatWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUISubSystem::ShowDialogueWidget(UDialogueComponent* InDialogueComponent)
{
	if (!DialogueWidget || !InDialogueComponent) return;
	
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}

void UUISubSystem::HideDialogueWidget()
{
	if (!DialogueWidget) return;
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UUISubSystem::RegisterWidgets(UPlaceableItemInventoryWidget* InPlaceActorWidget, UBoxingPatternWidget* InBoxingPatternWidget, UInteractionWidget* InInteractionWidget, UPlayerStatWidget* InPlayerStatWidget, UDialogueWidget* InDialogueWidget)
{
	PlaceActorWidget = InPlaceActorWidget;
	BoxingPatternWidget = InBoxingPatternWidget;
	InteractionWidget = InInteractionWidget;
	PlayerStatWidget = InPlayerStatWidget;
	DialogueWidget = InDialogueWidget;
}
