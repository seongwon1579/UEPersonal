// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component//ObjectPlacementComponent.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Goods/HomeGoods.h"
#include "Goods/Data/FFurnitureItemData.h"
#include "Pool/StaticMeshPool.h"
#include "SubSystem/PlaceableItemSubsystem.h"


void UObjectPlacementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Camera = Character->FindComponentByClass<UCameraComponent>();
		PlayerController = Character->GetController<APlayerController>();
	}

	PlaceableItemSubsystem = GetOwner()->GetGameInstance()->GetSubsystem<UPlaceableItemSubsystem>();
}

UObjectPlacementComponent::UObjectPlacementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// 프리뷰상에서 물체를 회전한다.
void UObjectPlacementComponent::RotateObject(float Direction)
{
	if (!bIsPreview || !HomeGoods) return;

	CurrentRotationExtent += RotationSpeed * Direction;
	HomeGoods->SetActorRotation(FRotator(0.f, CurrentRotationExtent, 0.f));
}

// 배치가 된 물체를 재선택하여 재배치를 시도한다.
void UObjectPlacementComponent::TrySelectObject()
{
	if (bIsPreview || !PlayerController) return;

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	// 현재 위치에서 배치 가능한 걸리의 최대거리 제한
	FVector End = Start + WorldDirection * PlacementRange;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	if (!Hit.bBlockingHit) return;

	AHomeGoods* SelectedGoods = Cast<AHomeGoods>(Hit.GetActor());

	// 현재 물체가 배치 가능한 경우 
	if (SelectedGoods && SelectedGoods->CanBeSelected())
	{
		bIsNewPlacing = false;
		
		HomeGoods = SelectedGoods;
		// 이전 transform 정보와 회전정도를 저장(배치 취소를 대비)
		PrevTransform = HomeGoods->GetActorTransform();
		CurrentRotationExtent = HomeGoods->GetActorRotation().Yaw;
		
		// 더블클릭으로 물체를 선택하려고 할 때 단순 클릭으로 잘 못 사용된느것을  방지 하기 위해 캐싱
		LastEditStartTime = GetWorld()->GetTimeSeconds();

		// 현재 선택된 객체가 프리뷰 모드 시에 필요한 설정 하도록 호출
		SetupPreview();
	}
}

// 오브젝트를 배치 하기 시작한다.
void UObjectPlacementComponent::StartPlacement()
{
	if (!HomeGoods || !PlayerController || bIsPreview) return;
	
	bIsNewPlacing = true;
	
	CurrentRotationExtent = 0.f;
	
	// 현재 선택된 객체가 프리뷰 모드 시에 필요한 설정 하도록 호출
	SetupPreview();
}

// 데이터를 바탕으로 객체 생성준비
void UObjectPlacementComponent::PreparePlacement_Implementation(const FFurnitureItemData& ItemData)
{
	HomeGoods = PlaceableItemSubsystem->GetStaticMeshPool()->GetHomeGoods();

	if (!HomeGoods) return;

	HomeGoods->SetHomeGoods(ItemData.Material, ItemData.Mesh);
}

// 객체를 배치를 확정하기전 프리뷰 이미지를 보여준다.
void UObjectPlacementComponent::UpdatePlacementPreview()
{
	if (!PlayerController || !HomeGoods) return;

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = Start + WorldDirection * PlacementRange;

	FHitResult Hit;
	// 자기 자신과 플레이어는 hit에서 제외
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(HomeGoods);
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);

	if (bHit)
	{
		HomeGoods->SetActorLocationAndRotation(Hit.Location, FRotator(0.f, CurrentRotationExtent, 0.f));
		HomeGoods->CheckSpawn();
	}
}

void UObjectPlacementComponent::ResetPlacement()
{
	HomeGoods = nullptr;
	bIsPreview = false;
	GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
}

void UObjectPlacementComponent::SetupPreview()
{
	// 프리뷰 모드 돌입
	bIsPreview = true;
	HomeGoods->StartPreview();
	
	// 마우스가 보이도록
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());

	GetWorld()->GetTimerManager().SetTimer(
		PlacementTimerHandle,
		this,
		&UObjectPlacementComponent::UpdatePlacementPreview,
		PreviewUpdateInterval,
		true
	);
}

// 오브젝트 배치를 확정한다.
void UObjectPlacementComponent::ConfirmPlacement()
{
	if (!bIsPreview || !HomeGoods) return;

	// 재 배치를 위해 더블클릭을 시도하는경우 일반 클릭으로 인식돼 두번쨰 클릭으로 바로 배치 되는 것을 방지
	if (GetWorld()->GetTimeSeconds() - LastEditStartTime < DoubleClickThreshold) return;

	// 현재 배치하려는 오브젝트가 스폰이 가능한지 확인
	if (HomeGoods->CanSpawn())
	{
		HomeGoods->Place();
		ResetPlacement();
	}
	//PlayerController->bShowMouseCursor = false;
}

// 최초 배치를 시도하다 취소 하는경우 오브젝트를 삭제한다.
// 기존에 배치되어 있던 물체의 재배치를 취소하는경우 기존의 위치로 되돌린다.
void UObjectPlacementComponent::CancelPlacement()
{
	if (!HomeGoods) return;

	// 재배치를 시도하다가 배치를 취소할 경우 이전 transform으로 돌아간다.
	if (!bIsNewPlacing)
	{
		HomeGoods->SetActorTransform(PrevTransform);
		HomeGoods->Place();
	}
	// 최초 배치의 경우 오브젝트를 반환한다.
	else
	{
		PlaceableItemSubsystem->GetStaticMeshPool()->ReturnHomeGoods(HomeGoods);
	}
	ResetPlacement();
	//PlayerController->bShowMouseCursor = false;
}
