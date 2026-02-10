// Fill out your copyright notice in the Description page of Project Settings.


#include "Goods/HomeGoods.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"

void AHomeGoods::SetHomeGoods(const TArray<UMaterialInterface*>& Materials, UStaticMesh* StaticMesh)
{
	if (!StaticMeshComponent) return;
	
	if (StaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh);
	}
	
	HomeGoodsMaterials = Materials;
	
	// 액터의 materials의 갯수 만큼 setting
	const int32 NumSlots = StaticMeshComponent->GetNumMaterials();
	for (int32 i = 0; i < HomeGoodsMaterials.Num() && i < NumSlots; i++)
	{
		if (HomeGoodsMaterials[i])
		{
			StaticMeshComponent->SetMaterial(i, HomeGoodsMaterials[i]);
		}
	}
}

AHomeGoods::AHomeGoods()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// 스테틱 매시 컴포넌트만 가지는 액터로 생성
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMeshComponent;
}

void AHomeGoods::StartPreview()
{
	if (!StaticMeshComponent) return;
	
	// 프리뷰 모드인경우 선택되지 않도록한다.
	bIsSelectable = false;
	
	// 오버랩으로 변경하여 물체 충돌을 없앤다.
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AHomeGoods::CheckSpawn()
{
	if (!StaticMeshComponent) return;
	
	FVector Location = GetActorLocation();
	FQuat Quat = GetActorQuat();

	// 현재 메시 크기보다 약간 작은 크기로 바닥 오버랩을 방지한다.
	FBox LocalBox = StaticMeshComponent->GetStaticMesh()->GetBoundingBox();
	FVector BoxExtent = LocalBox.GetExtent() * 0.98f;

	Location.Z += BoxExtent.Z + 10.f;
	BoxExtent.Z *= 0.9f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// 오버랩이 되는 경우를 확인하여 배치가 되는지를 확인한다.
	TArray<FOverlapResult> Overlaps;
	bool bIsOverlapping = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Location,
		Quat,
		ECC_Visibility,
		FCollisionShape::MakeBox(BoxExtent),
		QueryParams
	);
	
	// 현재 배치할 액터가 오버랩 상태인경우 모든 material의 색상을 red로, 아닌경우는 green
	const int32 NumSlots = StaticMeshComponent->GetNumMaterials();
	UMaterialInterface* PreviewMaterial = bIsOverlapping ? Material_Red : Material_Green;
	
	for (int32 i = 0; i  < NumSlots; i++)
	{
		StaticMeshComponent->SetMaterial(i, PreviewMaterial);
	}
	bCanSpawn = !bIsOverlapping;
	
	// 디버그 모드 일 경우 맵 상에 콜리전이 보이도록 한다.
	if (!bDebugMode) return;
	DrawDebugBox(GetWorld(), Location, BoxExtent, Quat,
	             bIsOverlapping ? FColor::Red : FColor::Green, false, 0.1f);
}

void AHomeGoods::Place()
{
	if (!bCanSpawn || HomeGoodsMaterials.Num() == 0 || !StaticMeshComponent) return;
	
	// 배치를 확정할 때 캐싱된 material로 설정
	const int32 NumSlots = StaticMeshComponent->GetNumMaterials();
	for (int32 i = 0; i < HomeGoodsMaterials.Num() && i < NumSlots; i++)
	{
		if (HomeGoodsMaterials[i])
		{
			StaticMeshComponent->SetMaterial(i, HomeGoodsMaterials[i]);
		}
	}
	
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

	bIsSelectable = true;
}
