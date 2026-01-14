// Fill out your copyright notice in the Description page of Project Settings.


#include "Road/Road.h"

#include "DebugHelper.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Road/RoadData/FRoadProperties.h"

// Sets default values
ARoad::ARoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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


// 에디터용 재생성
void ARoad::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 초기화
	// 이전 생성 컴포너트 제거
	for (USplineMeshComponent* Mesh : SplineMeshComponents)
	{
		if (Mesh)
		{
			Mesh->UnregisterComponent();
			Mesh->DestroyComponent();
		}
	}
	SplineMeshComponents.Empty();
	
	FRoadProperties* DefaultProperty = RoadDataHandle.GetRow<FRoadProperties>(TEXT("Road Data Context"));

	if (!DefaultProperty ) return;
	
	// 스플라인 갯수
	float SplineLength = SplineComponent->GetSplineLength();

	// 현재 메시의 X 방향의 길이(피벗이 중앙에서의 x길이를 반환하므로 2배 적용
	float meshXLenght = DefaultProperty->RoadPavement.RoadMesh->GetBounds().BoxExtent.X * 2;

	// Spline의 길이에 현재 할당된 메시의 길이(마지막 메시가 meshXLenght보가 짧은경우까지 고려하여 올림처리)
	int Count = FMath::CeilToInt(SplineLength / meshXLenght);

	RefreshRoadProperties(DefaultProperty , Count);
	
	int32 Index = 0;
	for (auto RoadProperty : RoadProperties)
	{
		//FName MeshName = *FString::Printf(TEXT("SplineMesh_%d"), index);
		USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		
		// 기본 road mesh 세팅
		SetupSplineMesh(Index, NewMesh, RoadProperty.RoadPavement.RoadMesh, meshXLenght);
		RollSplineMesh(NewMesh, RoadProperty.RoadSegment.BeginRoll, RoadProperty.RoadSegment.EndRoll);
		SplineMeshComponents.Add(NewMesh);
		
		
		if (RoadProperty.RoadSideWalk.IsValid())
		{
			if (RoadProperty.RoadSideWalk.bNeed_LeftSideWalk)
			{
				USplineMeshComponent* LeftSideMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
				SetupSplineMesh(Index, LeftSideMesh, RoadProperty.RoadSideWalk.Left_RoadSideWalk, meshXLenght);
				RollSplineMesh(LeftSideMesh, RoadProperty.RoadSegment.BeginRoll, RoadProperty.RoadSegment.EndRoll);
				// LeftSideMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				// LeftSideMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
				
				SplineMeshComponents.Add(LeftSideMesh);
			}
			if (RoadProperty.RoadSideWalk.bNeed_RightSideWalk)
			{
				USplineMeshComponent* RightSideMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
				SetupSplineMesh(Index, RightSideMesh, RoadProperty.RoadSideWalk.Right_RoadSideWalk, meshXLenght);
				RollSplineMesh(RightSideMesh, RoadProperty.RoadSegment.BeginRoll, RoadProperty.RoadSegment.EndRoll);
				// RightSideMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				// RightSideMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
				SplineMeshComponents.Add(RightSideMesh);
			}
		}
		Index++;
	}
}

#pragma region Framework
void ARoad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#pragma endregion

#pragma region Private Methods
void ARoad::RefreshRoadProperties(const FRoadProperties* DefaultProperty, int Count)
{
	// road mesh를 늘리면 default 추가
	while (RoadProperties.Num() < Count)
	{
		RoadProperties.Add(*DefaultProperty);
	}
	// road mesh를 줄이면 뒤에서 부터 삭제
	int32 ToRemove = RoadProperties.Num() - Count;
	RoadProperties.RemoveAt(Count, ToRemove);
}

void ARoad::SetupSplineMesh(int32 Index ,USplineMeshComponent* TargetMeshComponent, UStaticMesh* StaticMesh, float MeshLenght)
{
	if (TargetMeshComponent == nullptr ) return;
	
	// 메시가 움직일 수 있도록 한다.
	TargetMeshComponent->SetMobility(EComponentMobility::Movable);
	// 에디터 관리
	TargetMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	TargetMeshComponent->SetupAttachment(SplineComponent);
	TargetMeshComponent->SetStaticMesh(StaticMesh);
	TargetMeshComponent->SetForwardAxis(ESplineMeshAxis::X);
	
	// 일단 하드 코딩, 메시의 길이, 1000은 탄젠트 길이(각 세그먼트의 길이)
	FVector StartPos = SplineComponent->GetLocationAtDistanceAlongSpline(
		Index * MeshLenght, ESplineCoordinateSpace::Local);
	FVector StartTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(
		Index * MeshLenght, ESplineCoordinateSpace::Local) * 1000;
	FVector EndPos = SplineComponent->GetLocationAtDistanceAlongSpline(Index * MeshLenght + MeshLenght,
	                                                                   ESplineCoordinateSpace::Local);
	FVector EndTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(
		Index * MeshLenght + MeshLenght, ESplineCoordinateSpace::Local) * 1000;
	
	TargetMeshComponent->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);
	
	TargetMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//TargetMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	TargetMeshComponent->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
	
	TargetMeshComponent->UpdateMesh();
	// 등록은 모든 세팅이 끝나고 해야 한다(콜리전 세팅을 하기전에 등록하면 반영 안됨)
	TargetMeshComponent->RegisterComponent();
	
}

void ARoad::RollSplineMesh(USplineMeshComponent* TargetMeshComponent, float BeginRoll, float EndRoll)
{
	if (TargetMeshComponent == nullptr) return;
	
	TargetMeshComponent->SetStartRollDegrees(BeginRoll);
	TargetMeshComponent->SetEndRollDegrees(EndRoll);
}
#pragma endregion
