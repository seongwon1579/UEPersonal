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
}

AMovableNPC::AMovableNPC()
{
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	if (!SplineComp) return;

	SplineComp->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, RotationStrength, 0.0f);
	bUseControllerRotationYaw = false;
}

void AMovableNPC::MoveAlongSpline(float DeltaSeconds)
{
	// Spline을 따라 이동하면 끝점에 다다르면 시작점으로 이동
	float Direction = bMovingForward ? 1.f : -1.f;
	CurrentDistance += MoveSpeed * DeltaSeconds * Direction;
	
	// 종점에 다다르면
	if (CurrentDistance >= SplineLength)
	{
		CurrentDistance = SplineLength;
		bMovingForward = false;
		bIsWaiting = true;
	}
	// 시점에 다다르면
	else if (CurrentDistance <= 0.f)
	{
		CurrentDistance = 0.f;
		bMovingForward = true;
		bIsWaiting = true;
	}
	
	// Spline 이동시에 현재 이동지점에서 방향 벡터
	FVector MoveDirection = SplineComp->GetDirectionAtDistanceAlongSpline(
		CurrentDistance, ESplineCoordinateSpace::World) * Direction;

	// 해당 방향벡터로 설정 속도로 이동
	AddMovementInput(MoveDirection, 1.f);
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
