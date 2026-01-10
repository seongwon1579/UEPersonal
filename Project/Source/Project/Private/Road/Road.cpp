// Fill out your copyright notice in the Description page of Project Settings.


#include "Road/Road.h"

#include "DebugHelper.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

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

	int32 NumberOfSegments = SplineComponent->GetNumberOfSplinePoints() - 1;

	for (int32 i = 0; i < NumberOfSegments; i++)
	{
		FName MeshName = *FString::Printf(TEXT("SplineMesh_%d"), i);
		USplineMeshComponent* NewMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), MeshName);

		// 메시가 움직일 수 있도록 한다.
		NewMesh->SetMobility(EComponentMobility::Movable);
		// 에디터 관리
		NewMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
        
		NewMesh->SetupAttachment(SplineComponent);
		NewMesh->SetStaticMesh(RoadMesh);
		NewMesh->SetForwardAxis(ESplineMeshAxis::X);
		NewMesh->RegisterComponent();
		
		// FVector StartPos = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		// FVector StartTangent = SplineComponent->GetLeaveTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		// FVector EndPos = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		// FVector EndTangent = SplineComponent->GetArriveTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		
		// 일단 하드 코딩, 메시가의 길이, 탄젠트 길이
		FVector StartPos = SplineComponent->GetLocationAtDistanceAlongSpline(i * 1000, ESplineCoordinateSpace::Local);
		FVector StartTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(i * 1000, ESplineCoordinateSpace::Local) * 1000;
		FVector EndPos = SplineComponent->GetLocationAtDistanceAlongSpline(i * 1000 + 1000, ESplineCoordinateSpace::Local);
		FVector EndTangent = SplineComponent->GetDirectionAtDistanceAlongSpline(i * 1000 + 1000, ESplineCoordinateSpace::Local) * 1000;

		NewMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);
        
		SplineMeshComponents.Add(NewMesh);
	}
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
