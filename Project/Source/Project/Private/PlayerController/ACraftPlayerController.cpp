// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ACraftPlayerController.h"

#include "DebugHelper.h"
#include "Blueprint/UserWidget.h"
#include "Manager/UIManager.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/FurnitureSelectionWidget.h"
#include "Widget/PlaceActorWidget.h"

void AACraftPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	 if (!WidgetClass) return;
	
	UPlaceableItemSubsystem* PlaceableItemSubsystem = GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	PlaceableItemSubsystem->InitializeStaticMeshPool(GetWorld());
	
	//TODO: 임시로 플레이어 컨트롤러에서 만듬 
	UIManager = NewObject<UUIManager>(this);
	
	UIManager->Initialize(this, WidgetClass);
	UIManager->ShowPlaceActorWidget();
}
