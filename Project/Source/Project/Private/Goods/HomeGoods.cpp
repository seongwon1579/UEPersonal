// Fill out your copyright notice in the Description page of Project Settings.


#include "Goods/HomeGoods.h"
#include "NaniteSceneProxy.h"
#include "Engine/OverlapResult.h" 
#include "Engine/World.h"

// Sets default values
AHomeGoods::AHomeGoods()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//StaticMeshComponent->SetupAttachment(RootComponent);
	RootComponent = StaticMeshComponent;
}

void AHomeGoods::StartEditing()
{
	bIsSelectable = false;
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AHomeGoods::CheckSpawn()
{
	// TArray<AActor*> OverlappingActors;
	// GetOverlappingActors(OverlappingActors);
	// if (OverlappingActors.Num() > 0)
	// {
	// 	StaticMeshComponent->SetMaterial(0, Material_Red);
	// 	bCanSpawn = false;
	// }
	// else
	// {
	// 	StaticMeshComponent->SetMaterial(0, Material_Green);
	// 	bCanSpawn = true;
	// }
	
	// 1. 충돌 영역 설정 (현재 메쉬의 크기 활용)
	
	// FVector MyLocation = GetActorLocation();
	// FQuat MyRotation = GetActorQuat();
    
	// // 메시 바운드 가져오기
	// FBoxSphereBounds Bounds = StaticMeshComponent->Bounds;
	// FVector BoxExtent = Bounds.BoxExtent * 0.8f;  // 약간 작게
 //    
	// // 바닥 제외: 박스를 위로 올리고 높이 줄임
	// MyLocation.Z += BoxExtent.Z * 0.5f;
	// BoxExtent.Z *= 0.5f;
	
	// FBoxSphereBounds Bounds = StaticMeshComponent->Bounds;
	// FBox Bounds =  StaticMeshComponent->GetStaticMesh()->GetBoundingBox();
	//
	// FVector BoxExtent = Bounds.BoxExtent * 0.98f; 
 //    
	// // 바닥에서 더 멀리
	// MyLocation.Z += BoxExtent.Z + 10.f;  // 10cm 추가 여유
	// BoxExtent.Z *= 0.3f;  // 높이 더 줄임
 //    
	// FCollisionQueryParams QueryParams;
	// QueryParams.AddIgnoredActor(this);
 //    
	// TArray<FOverlapResult> Overlaps;
	// bool bIsOverlapping = GetWorld()->OverlapMultiByChannel(
	// 	Overlaps,
	// 	MyLocation,
	// 	MyRotation,
	// 	ECC_Visibility,
	// 	FCollisionShape::MakeBox(BoxExtent),
	// 	QueryParams
	// );
 //    
	// if (bIsOverlapping)
	// {
	// 	StaticMeshComponent->SetMaterial(0, Material_Red);
	// 	bCanSpawn = false;
	// }
	// else
	// {
	// 	StaticMeshComponent->SetMaterial(0, Material_Green);
	// 	bCanSpawn = true;
	// }
	
	FVector MyLocation = GetActorLocation();
	FQuat MyRotation = GetActorQuat();
    

	FBox LocalBox = StaticMeshComponent->GetStaticMesh()->GetBoundingBox();
	FVector BoxExtent = LocalBox.GetExtent() * 0.98f;
	
	MyLocation.Z += BoxExtent.Z + 10.f;
	BoxExtent.Z *= 0.9f;
    
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
    
	TArray<FOverlapResult> Overlaps;
	bool bIsOverlapping = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		MyLocation,
		MyRotation,
		ECC_Visibility,
		FCollisionShape::MakeBox(BoxExtent),
		QueryParams
	);
    
	// 디버그 시각화
	DrawDebugBox(GetWorld(), MyLocation, BoxExtent, MyRotation, 
		bIsOverlapping ? FColor::Red : FColor::Green, false, 0.1f);
    
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
}

void AHomeGoods::Place()
{
	if (bCanSpawn)
	{
		StaticMeshComponent->SetMaterial(0, Material_Target);
		// StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		
		
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
		StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
		
		bIsSelectable = true;
	}
}

