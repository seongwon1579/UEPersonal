// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/MovableNPC.h"

#include "DebugHelper.h"
#include "Character/NPC/MovableNPCAnimInstance.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMovableNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!SplineComp) return;

	if (bIsWaiting)
	{
		HandleWaiting();
	}
	else
	{
		MoveAlongSpline(DeltaSeconds);
	}
}

void AMovableNPC::BeginPlay()
{
	Super::BeginPlay();

	if (!SplineComp) return;

	// 총 이동거리 캐싱
	SplineComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SplineLength = SplineComp->GetSplineLength();

	// 시작 위치를 Spline의 시작위치로 
	FVector StartLocation = SplineComp->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::World);
	SetActorLocation(StartLocation);

	AnimInstance = Cast<UMovableNPCAnimInstance>(GetMesh()->GetAnimInstance());
	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotationStrength, 0.0f);
}

AMovableNPC::AMovableNPC()
{
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	if (!SplineComp) return;

	SplineComp->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AMovableNPC::MoveAlongSpline(float DeltaSeconds)
{
	FVector Location = GetActorLocation();
	
	// FindInputKeyClosestToWorldLocation : 스플라인 포인트 사이의 보간 인덱스
	// GetDistanceAlongSplineAtSplineInputKey : 현재 거리
	CurrentDistance = SplineComp->GetDistanceAlongSplineAtSplineInputKey(
		SplineComp->FindInputKeyClosestToWorldLocation(Location));

	bool bReachedEnd = bMovingForward && CurrentDistance >= SplineLength - 30.f;
	bool bReachedStart = !bMovingForward && CurrentDistance <= 30.f;

	if (bReachedEnd || bReachedStart)
	{
		bMovingForward = !bMovingForward;
		bIsWaiting = true;
		return;
	}

	float Direction = bMovingForward ? 1.f : -1.f;
	
	FVector MoveDir = SplineComp->GetDirectionAtDistanceAlongSpline(
		CurrentDistance, ESplineCoordinateSpace::World) * Direction;

	AddMovementInput(MoveDir, 1.f);
}

void AMovableNPC::HandleWaiting()
{
	// Idle 상태가 끝날 때 까지 이동 멈춤
	if (!AnimInstance || AnimInstance->IsIdleCycleCompleted())
	{
		bIsWaiting = false;
		AnimInstance->SetIdleCycleCompleted(false);
	}
}
