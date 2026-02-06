// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/AMainPlayerController.h"
#include "DebugHelper.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "SubSystem/UISubSystem.h"

#include "Widget/Inventory/PlaceActorWidget.h"
#include "Widget/Activity/BoxingPatternWidget.h"
#include "widget/Interaction/InteractionWidget.h"
#include "widget/PlayerStat/PlayerStatWidget.h"

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
	PlaceActorWidget = CreateWidget<UPlaceActorWidget>(this, PlaceActorWidgetClass);
	BoxingPatternWidget = CreateWidget<UBoxingPatternWidget>(this, BoxingPatternWidgetClass);
	InteractionWidget = CreateWidget<UInteractionWidget>(this, InteractionWidgetClass);
	PlayerStatWidget = CreateWidget<UPlayerStatWidget>(this, PlayerStatWidgetClass);
	
	if (!PlaceActorWidget || !BoxingPatternWidget || !InteractionWidget || !PlayerStatWidget) return;
	
	UISubSystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	
	if (!UISubSystem) return;
	
	UISubSystem->RegisterWidgets(PlaceActorWidget, BoxingPatternWidget, InteractionWidget, PlayerStatWidget);
}
