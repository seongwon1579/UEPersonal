// Fill out your copyright notice in the Description page of Project Settings.


#include "Goods/HomeGoods.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"

AHomeGoods::AHomeGoods()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMeshComponent;
}

void AHomeGoods::StartEditing()
{
	if (!HomeGoodsMaterial || !StaticMeshComponent) return;
	
	bIsSelectable = false;
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AHomeGoods::CheckSpawn()
{
	if (!HomeGoodsMaterial || !StaticMeshComponent) return;
	
	FVector Location = GetActorLocation();
	FQuat Quat = GetActorQuat();

	FBox LocalBox = StaticMeshComponent->GetStaticMesh()->GetBoundingBox();
	FVector BoxExtent = LocalBox.GetExtent() * 0.98f;

	Location.Z += BoxExtent.Z + 10.f;
	BoxExtent.Z *= 0.9f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	TArray<FOverlapResult> Overlaps;
	bool bIsOverlapping = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Location,
		Quat,
		ECC_Visibility,
		FCollisionShape::MakeBox(BoxExtent),
		QueryParams
	);

	if (bIsOverlapping)
	{
		StaticMeshComponent->SetMaterial(0, Material_Red);
		bCanSpawn = false;
	}
	else
	{
		StaticMeshComponent->SetMaterial(0, Material_Green);
		bCanSpawn = true;
	}

	if (!bDebugMode) return;
	DrawDebugBox(GetWorld(), Location, BoxExtent, Quat,
	             bIsOverlapping ? FColor::Red : FColor::Green, false, 0.1f);
}

void AHomeGoods::Place()
{
	if (!bCanSpawn|| !HomeGoodsMaterial) return;

	StaticMeshComponent->SetMaterial(0, HomeGoodsMaterial);
	// StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

	bIsSelectable = true;
}
