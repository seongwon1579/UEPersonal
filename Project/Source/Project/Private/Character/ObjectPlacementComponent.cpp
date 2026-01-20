// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ObjectPlacementComponent.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Goods/HomeGoods.h"


void UObjectPlacementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Camera = Character->FindComponentByClass<UCameraComponent>();
		PlayerController = Character->GetController<APlayerController>();
	}
}

UObjectPlacementComponent::UObjectPlacementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UObjectPlacementComponent::RotatePlacement(float Direction)
{
	//if (!bIsPlacing || !HomeGoods) return;
	if (!bIsEditing || !HomeGoods) return;

	CurrentRotation += RotationSpeed * Direction;
	HomeGoods->SetActorRotation(FRotator(0.f, CurrentRotation, 0.f));
}

void UObjectPlacementComponent::TrySelectObject()
{
	if (bIsEditing || !PlayerController) return;

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = Start + WorldDirection * PlacementRange;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

	if (Hit.bBlockingHit)
	{
		AHomeGoods* SelectedGoods = Cast<AHomeGoods>(Hit.GetActor());

		if (SelectedGoods && SelectedGoods->CanBeSelected())
		{
			//bIsPlacing = true;
			bIsEditing = true;
			LastEditStartTime = GetWorld()->GetTimeSeconds();

			HomeGoods = SelectedGoods;
			HomeGoods->StartEditing();

			PrevTransform = HomeGoods->GetActorTransform();

			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI());

			GetWorld()->GetTimerManager().SetTimer(
				PlacementTimerHandle,
				this,
				&UObjectPlacementComponent::UpdatePlacementPreview,
				0.016f,
				true
			);
		}
	}
}

void UObjectPlacementComponent::StartPlacing()
{
	if (!Goods || !PlayerController) return;
	if (bIsEditing) return;

	bIsEditing = true;
	//bIsPlacing = true;

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());


	GetWorld()->GetTimerManager().SetTimer(
		PlacementTimerHandle,
		this,
		&UObjectPlacementComponent::UpdatePlacementPreview,
		0.016f,
		true
	);

	// 프리뷰 오브젝트 생성
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	HomeGoods = GetWorld()->SpawnActor<AHomeGoods>(Goods, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (HomeGoods)
	{
		HomeGoods->StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	}
}

void UObjectPlacementComponent::UpdatePlacementPreview()
{
	if (!PlayerController || !HomeGoods) return;
	
	//bIsEditing = true;

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = Start + WorldDirection * PlacementRange;

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(HomeGoods);
	QueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);

	if (bHit)
	{
		HomeGoods->SetActorLocationAndRotation(Hit.Location, FRotator(0.f, CurrentRotation, 0.f));
		HomeGoods->CheckSpawn();
	}
}

void UObjectPlacementComponent::ConfirmPlacement()
{
	if (!bIsEditing || !HomeGoods) return;

	if (GetWorld()->GetTimeSeconds() - LastEditStartTime < 0.3f)
	{
		return;
	}

	if (HomeGoods->bCanSpawn)
	{
		HomeGoods->Place();
		HomeGoods = nullptr;
		//bIsPlacing = false;
		bIsEditing = false;
		GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
	}
	else
	{
	}
}

void UObjectPlacementComponent::CancelPlacement()
{
	if (!HomeGoods) return;

	if (bIsEditing)
	{
		HomeGoods->SetActorTransform(PrevTransform);
		HomeGoods->Place();
	}
	else
	{
		HomeGoods->Destroy();
	}
	HomeGoods = nullptr;
	
	//bIsPlacing = false;
	bIsEditing = false;
	GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
}
