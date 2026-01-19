// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ObjectPlacementComponent.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Goods/HomeGoods.h"

// // Sets default values for this component's properties
// UObjectPlacementComponent::UObjectPlacementComponent()
// {
// 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// 	// off to improve performance if you don't need them.
// 	PrimaryComponentTick.bCanEverTick = false;
//
//
// 	// ...
// }
//
//
// void UObjectPlacementComponent::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// 	if (CachedCamera == nullptr)
// 	{
// 		if (AActor* Owner = GetOwner())
// 		{
// 			CachedCamera = Owner->FindComponentByClass<UCameraComponent>();
// 		}
// 	}
// }
//
// // Called every frame
// void UObjectPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }
//
// void UObjectPlacementComponent::TryPlace()
// {
// 	if (!CachedCamera) return;
// 	
// 	if (bPlacingTarget == false) return;
// 	
// 	FVector Start = CachedCamera->GetComponentLocation();
// 	FVector End = Start + CachedCamera->GetForwardVector() * 1500.f;
// 	
// 	FHitResult Hit;
// 	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility);
// 	
// 	if (!Hit.bBlockingHit)
// 	{
// 		if (HomeGoods)
// 		{
// 			HomeGoods->Destroy();
// 			HomeGoods = nullptr;
// 		}
// 		return;
// 	}
// 	
// 	if (HomeGoods)
// 	{
// 		HomeGoods->SetActorLocation(Hit.Location);
// 	}
// 	else
// 	{
// 		FActorSpawnParameters SpawnParams;
// 		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 		if (!GoodsBlueprintClass)
// 		{
// 			return;
// 		}
//                 
// 		HomeGoods = GetWorld()->SpawnActor<AHomeGoods>(GoodsBlueprintClass, Hit.Location, FRotator::ZeroRotator, SpawnParams);
// 	}
// 	HomeGoods->CheckSpawn();
// 	
// }

void UObjectPlacementComponent::BeginPlay()
{
    Super::BeginPlay();
    
    if (AActor* Owner = GetOwner())
    {
        CachedCamera = Owner->FindComponentByClass<UCameraComponent>();
        
        if (ACharacter* Character = Cast<ACharacter>(Owner))
        {
            CachedController = Cast<APlayerController>(Character->GetController());
        }
    }
}

void UObjectPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (bPlacingTarget)
    {
        UpdatePlacementPreview();
    }
}

void UObjectPlacementComponent::StartPlacing()
{
    if (!GoodsBlueprintClass || !CachedController) return;
    
    bPlacingTarget = true;
    PrimaryComponentTick.bCanEverTick = true;
    
    // 프리뷰 오브젝트 생성
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    HomeGoods = GetWorld()->SpawnActor<AHomeGoods>(GoodsBlueprintClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    
    if (HomeGoods)
    {
        HomeGoods->StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    }
}

void UObjectPlacementComponent::UpdatePlacementPreview()
{
    if (!CachedController || !HomeGoods) return;
    
    FVector WorldLocation, WorldDirection;
    CachedController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
    
    FVector Start = WorldLocation;
    FVector End = Start + WorldDirection * PlacementRange;
    
    FHitResult Hit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(HomeGoods);
    QueryParams.AddIgnoredActor(GetOwner());
    
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);
    
    if (bHit)
    {
        HomeGoods->SetActorLocation(Hit.Location);
        HomeGoods->CheckSpawn();
    }
}

void UObjectPlacementComponent::ConfirmPlacement()
{
    if (!bPlacingTarget || !HomeGoods) return;
    
    if (HomeGoods->bCanSpawn)
    {
        // 배치 확정
        HomeGoods->Place();
        HomeGoods = nullptr;
        bPlacingTarget = false;
        PrimaryComponentTick.bCanEverTick = false;
    }
    else
    {

    }
}

void UObjectPlacementComponent::CancelPlacement()
{
    if (HomeGoods)
    {
        HomeGoods->Destroy();
        HomeGoods = nullptr;
    }
    
    bPlacingTarget = false;
    PrimaryComponentTick.bCanEverTick = false;
}



