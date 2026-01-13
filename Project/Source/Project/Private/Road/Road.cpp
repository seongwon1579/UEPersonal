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

	if (!DefaultProperty )
	{
		UE_LOG(LogTemp, Warning, TEXT("No Road Data Context"));
		return;
	}

	// 스플라인 갯수
	float SplineLength = SplineComponent->GetSplineLength();

	// 현재 메시의 X 방향의 길이(피벗이 중앙에서의 x길이를 반환하므로 2배 적용
	float meshXLenght = DefaultProperty->RoadPavement.RoadMesh->GetBounds().BoxExtent.X * 2;

	// Spline의 길이에 현재 할당된 메시의 길이(마지막 메시가 meshXLenght보가 짧은경우까지 고려하여 올림처리)
	int Count = FMath::CeilToInt(SplineLength / meshXLenght);

	RefreshRoadProperties(DefaultProperty , Count);
	
	for (int32 i = 0; i < RoadProperties.Num(); i++)
	{
		FName MeshName = *FString::Printf(TEXT("SplineMesh_%d"), i);
		USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(),
		                                                                MeshName);
		SetupSplineMesh(i, NewMesh, RoadProperties[i]);
		SplineMeshComponents.Add(NewMesh);
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

void ARoad::SetupSplineMesh(int32 Index, USplineMeshComponent* TargetMeshComponent, FRoadProperties RoadProperty)
{
	float meshXLenght = RoadProperty.RoadPavement.RoadMesh->GetBounds().BoxExtent.X * 2;

	FName MeshName = *FString::Printf(TEXT("SplineMesh_%d"), Index);
	USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), MeshName);

	// 메시가 움직일 수 있도록 한다.
	NewMesh->SetMobility(EComponentMobility::Movable);
	// 에디터 관리
	NewMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	NewMesh->SetupAttachment(SplineComponent);
	NewMesh->SetStaticMesh(RoadProperty.RoadPavement.RoadMesh);
	NewMesh->SetForwardAxis(ESplineMeshAxis::X);
	NewMesh->RegisterComponent();
	
	// 일단 하드 코딩, 메시의 길이, 1000은 탄젠트 길이(각 세그먼트의 길이)
	FVector StartPos = SplineComponent->GetLocationAtDistanceAlongSpline(
		Index * meshXLenght, ESplineCoordinateSpace::Local);
	FVector StartTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(
		Index * meshXLenght, ESplineCoordinateSpace::Local) * 1000;
	FVector EndPos = SplineComponent->GetLocationAtDistanceAlongSpline(Index * meshXLenght + meshXLenght,
	                                                                   ESplineCoordinateSpace::Local);
	FVector EndTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(
		Index * meshXLenght + meshXLenght, ESplineCoordinateSpace::Local) * 1000;

	NewMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);

	// 메시 컴포넌트 롤링
	NewMesh->SetStartRollDegrees(RoadProperty.RoadSegment.BeginRoll);
	NewMesh->SetEndRollDegrees(RoadProperty.RoadSegment.EndRoll);
}
#pragma endregion
