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
	if (!bIsEditing || !HomeGoods) return;

	CurrentRotationExtent += RotationSpeed * Direction;
	HomeGoods->SetActorRotation(FRotator(0.f, CurrentRotationExtent, 0.f));
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
			bIsEditing = true;
			bIsNewPlacing = false;
			LastEditStartTime = GetWorld()->GetTimeSeconds();

			HomeGoods = SelectedGoods;
			HomeGoods->StartEditing();

			PrevTransform = HomeGoods->GetActorTransform();
			CurrentRotationExtent = SelectedGoods->GetActorRotation().Yaw;

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
	if (!Goods || !PlayerController || bIsEditing) return;

	bIsEditing = true;
	bIsNewPlacing = true;

	CurrentRotationExtent = 0.f;

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());
	
	GetWorld()->GetTimerManager().SetTimer(
		PlacementTimerHandle,
		this,
		&UObjectPlacementComponent::UpdatePlacementPreview,
		0.016f,
		true
	);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	HomeGoods = GetWorld()->SpawnActor<AHomeGoods>(Goods, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	HomeGoods->StartEditing();
	// if (HomeGoods)
	// {
	// 	//HomeGoods->StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	// }
}

void UObjectPlacementComponent::UpdatePlacementPreview()
{
	if (!PlayerController || !HomeGoods) return;
	
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
		HomeGoods->SetActorLocationAndRotation(Hit.Location, FRotator(0.f, CurrentRotationExtent, 0.f));
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

	if (HomeGoods->CanSpawn())
	{
		HomeGoods->Place();
		HomeGoods = nullptr;
		bIsEditing = false;
		GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
	}
	else
	{
	}
	//PlayerController->bShowMouseCursor = false;
}

void UObjectPlacementComponent::CancelPlacement()
{
	if (!HomeGoods) return;

	if (!bIsNewPlacing)
	{
		HomeGoods->SetActorTransform(PrevTransform);
		HomeGoods->Place();
	}
	else
	{
		HomeGoods->Destroy();
	}
	HomeGoods = nullptr;

	bIsEditing = false;
	GetWorld()->GetTimerManager().ClearTimer(PlacementTimerHandle);
	//PlayerController->bShowMouseCursor = false;
}
