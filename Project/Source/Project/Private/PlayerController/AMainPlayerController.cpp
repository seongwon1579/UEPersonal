// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/AMainPlayerController.h"
#include "DebugHelper.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "SubSystem/UISubSystem.h"

#include "Widget/Inventory/PlaceableItemInventoryWidget.h"
#include "Widget/Activity/BoxingPatternWidget.h"
#include "widget/Interaction/InteractionWidget.h"
#include "widget/PlayerStat/PlayerStatWidget.h"
#include "Widget/Dialogue/DialogueWidget.h"

void AAMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UPlaceableItemSubsystem* PlaceableItemSubsystem = GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	PlaceableItemSubsystem->InitializeStaticMeshPool(GetWorld());
	
	CreateWidgets();
}

// 플레이어 위젯을 생성하고 UISubSystem에 위젯을 등록한다.
void AAMainPlayerController::CreateWidgets()
{
	PlaceActorWidget = CreateWidget<UPlaceableItemInventoryWidget>(this, PlaceActorWidgetClass);
	BoxingPatternWidget = CreateWidget<UBoxingPatternWidget>(this, BoxingPatternWidgetClass);
	//InteractionWidget = CreateWidget<UInteractionWidget>(this, InteractionWidgetClass);
	//PlayerStatWidget = CreateWidget<UPlayerStatWidget>(this, PlayerStatWidgetClass);
	DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWidgetClass);
	
	if (!PlaceActorWidget || !BoxingPatternWidget ||  !DialogueWidget) return;
	
	PlaceActorWidget->AddToViewport();
	BoxingPatternWidget->AddToViewport();
	//InteractionWidget->AddToViewport();
	//PlayerStatWidget->AddToViewport();
	DialogueWidget->AddToViewport();
	
	PlaceActorWidget->SetVisibility(ESlateVisibility::Collapsed);
	BoxingPatternWidget->SetVisibility(ESlateVisibility::Collapsed);
	//InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	//PlayerStatWidget->SetVisibility(ESlateVisibility::Collapsed);
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	UISubSystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	
	if (!UISubSystem) return;
	
	UISubSystem->RegisterWidgets(PlaceActorWidget, BoxingPatternWidget, DialogueWidget);
}
