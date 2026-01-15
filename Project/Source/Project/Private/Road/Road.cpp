// Fill out your copyright notice in the Description page of Project Settings.


#include "Road/Road.h"

#include "DebugHelper.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Road/RoadData/FRoadProperties.h"

// Sets default values
ARoad::ARoad()
{
	SetupSplineComponent();
	bShowSplineOnly = false;
	bShowRoadOnly = false;
}

// 에디터용 재생성
void ARoad::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ClearRoadMeshes();

	FRoadProperties* DefaultProperty = RoadDataHandle.GetRow<FRoadProperties>(TEXT("Road Data Context"));
	UpdateRoadMeshes(DefaultProperty);
}

void ARoad::SetupSplineComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->ClearSplinePoints();
	RootComponent = DefaultSceneComponent;
	SplineComponent->SetupAttachment(RootComponent);

	if (SplineComponent->GetNumberOfSplinePoints() < 2)
	{
		SplineComponent->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::Local);
		SplineComponent->AddSplinePoint(FVector(2000, 0, 0), ESplineCoordinateSpace::Local);
	}
	SplineComponent->UpdateSpline();
}


#pragma region SplineMeshComponent
void ARoad::ClearRoadMeshes()
{
	// 초기화
	// 이전 생성 컴포너트 제거
	for (USplineMeshComponent* Mesh : SplineMeshComponents)
	{
		if (!Mesh) continue;
		Mesh->UnregisterComponent();
		Mesh->DestroyComponent();
	}
	SplineMeshComponents.Empty();
}

void ARoad::UpdateRoadMeshes(const FRoadProperties* Properties)
{
	if (!Properties) return;

	// 스플라인 갯수
	float SplineLength = SplineComponent->GetSplineLength();

	// 현재 메시의 X 방향의 길이(피벗이 중앙에서의 x길이를 반환하므로 2배 적용
	float MeshXLenght = Properties->RoadPavement.RoadMesh->GetBounds().BoxExtent.X * 2;

	// Spline의 길이에 현재 할당된 메시의 길이(마지막 메시가 meshXLenght보가 짧은경우까지 고려하여 올림처리)
	int Count = FMath::CeilToInt(SplineLength / MeshXLenght);

	RefreshRoadProperties(Properties, Count);

	if (bShowSplineOnly)
	{
		bShowRoadOnly = false;
		return;
	}
	
	for (int32 i = 0; i < RoadProperties.Num(); i++)
	{
		CreateSplineMesh(i, RoadProperties[i].RoadPavement.RoadMesh, RoadProperties[i].RoadSegment.BeginRoll,
		                 RoadProperties[i].RoadSegment.EndRoll, MeshXLenght);

		auto AddOptionalMesh = [&](bool bCondition, UStaticMesh* StaticMesh)
		{
			if (!bCondition || !StaticMesh) return;

			CreateSplineMesh(i, StaticMesh, RoadProperties[i].RoadSegment.BeginRoll,
			                 RoadProperties[i].RoadSegment.EndRoll, MeshXLenght);
		};
		
		if (bShowRoadOnly) continue;

		if (RoadProperties[i].RoadSideWalk.IsValid())
		{
			AddOptionalMesh(RoadProperties[i].RoadSideWalk.bNeed_LeftSideWalk,
			                RoadProperties[i].RoadSideWalk.Left_RoadSideWalk);
			AddOptionalMesh(RoadProperties[i].RoadSideWalk.bNeed_RightSideWalk,
			                RoadProperties[i].RoadSideWalk.Right_RoadSideWalk);
		}

		if (RoadProperties[i].RoadRail.IsValid())
		{
			AddOptionalMesh(RoadProperties[i].RoadRail.bNeed_Left_Rail, RoadProperties[i].RoadRail.Left_RoadRail);
			AddOptionalMesh(RoadProperties[i].RoadRail.bNeed_Right_Rail, RoadProperties[i].RoadRail.Right_RoadRail);
		}
	}
}

void ARoad::RefreshRoadProperties(const FRoadProperties* DefaultProperty, int Count)
{
	if (!DefaultProperty) return;
	
	// road mesh를 늘리면 default 추가
	while (RoadProperties.Num() < Count)
	{
		RoadProperties.Add(*DefaultProperty);
	}
	// road mesh를 줄이면 뒤에서 부터 삭제
	if (RoadProperties.Num() > Count)
	{
		int32 ToRemove = RoadProperties.Num() - Count;
		RoadProperties.RemoveAt(Count, ToRemove);
	}
}

void ARoad::CreateSplineMesh(int32 Index, UStaticMesh* StaticMesh, float BeginRoll, float EndRoll, float MeshLenght)
{
	if (!StaticMesh) return;
	
	USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
	SetupSplineMesh(Index, NewMesh, StaticMesh, MeshLenght);
	RollSplineMesh(NewMesh, BeginRoll, EndRoll);
	SplineMeshComponents.Add(NewMesh);
}

void ARoad::SetupSplineMesh(int32 Index, USplineMeshComponent* TargetMeshComponent, UStaticMesh* StaticMesh,
                            float MeshLenght)
{
	if (!TargetMeshComponent || !StaticMesh) return;

	// 메시가 움직일 수 있도록 한다.
	TargetMeshComponent->SetMobility(EComponentMobility::Movable);
	// 에디터 관리
	TargetMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	TargetMeshComponent->SetupAttachment(SplineComponent);
	TargetMeshComponent->SetStaticMesh(StaticMesh);
	TargetMeshComponent->SetForwardAxis(ESplineMeshAxis::X);

	const float StartDistance = Index * MeshLenght;
	const float EndDistance = StartDistance + MeshLenght;

	// 일단 하드 코딩, 메시의 길이, 1000은 탄젠트 길이(각 세그먼트의 길이)
	FVector StartPos = SplineComponent->GetLocationAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
	FVector StartTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local) * 1000;
	FVector EndPos = SplineComponent->GetLocationAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
	FVector EndTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local) * 1000;

	TargetMeshComponent->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);
	TargetMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TargetMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	TargetMeshComponent->UpdateMesh();
	// 등록은 모든 세팅이 끝나고 해야 한다(콜리전 세팅을 하기전에 등록하면 반영 안됨)
	TargetMeshComponent->RegisterComponent();
}

void ARoad::RollSplineMesh(USplineMeshComponent* TargetMeshComponent, float BeginRoll, float EndRoll)
{
	if (!TargetMeshComponent) return;

	TargetMeshComponent->SetStartRollDegrees(BeginRoll);
	TargetMeshComponent->SetEndRollDegrees(EndRoll);
}
#pragma endregion
