// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"

#include "Blueprint/UserWidget.h"
#include "SubSystem/PlaceableItemSubsystem.h"
#include "Widget/PlaceActorWidget.h"

UUIManager::UUIManager()
{
}

void UUIManager::ShowPlaceActorWidget()
{
	if (!PlaceWidget || !Controller) return;
	
	// 위젯 생성
	UPlaceActorWidget* PlaceActorWidget = CreateWidget<UPlaceActorWidget>(Controller, PlaceWidget);
	
	// 서브시스템에서 데이터를 가져온다.
	UPlaceableItemSubsystem* PlaceableItemSubsystem = Controller->GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
	TArray<FFurnitureItemData*> FurnitureItemData = PlaceableItemSubsystem->GetAllFurnitureData();
	
	// 데이터를 가지고 위젯을 초기화한다.
	if (!FurnitureItemData.IsEmpty())
	{
		PlaceActorWidget->SetupWithData(FurnitureItemData);
	}
	PlaceActorWidget->AddToViewport();
}

// 위젯을 생성하기 위해 컨트롤러와 위젯을 할당한다.
void UUIManager::Initialize(APlayerController* PC, TSubclassOf<UPlaceActorWidget> Widget)
{
	Controller = PC;
	PlaceWidget = Widget;
}
