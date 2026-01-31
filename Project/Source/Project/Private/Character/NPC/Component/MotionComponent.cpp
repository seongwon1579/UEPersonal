// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Component/MotionComponent.h"
#include "Character/NPC/StationaryNPCAnimInstance.h"
#include "Character/NPC/Data/NPCStationaryAnimDataAsset.h"

UMotionComponent::UMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!AnimDataAsset) return;
	
	USkeletalMeshComponent* Mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (!Mesh) return;
	
	UStationaryNPCAnimInstance* NPCAnimInstance = Cast<UStationaryNPCAnimInstance>(Mesh->GetAnimInstance());
	if (!NPCAnimInstance) return;
	
	InitializeAnimData(NPCAnimInstance);
}

// AnimInstance의 AnimSequence의 할당을 위해 데이터 어셋에 요청한다.
void UMotionComponent::InitializeAnimData(UStationaryNPCAnimInstance* InStationaryNPCAnimInstance)
{
	if (!AnimDataAsset) return;

	AnimDataAsset->SetupAnimationInstance(InStationaryNPCAnimInstance);
	InStationaryNPCAnimInstance->SetupIdleParams(IdleBaseDuration, true);
}
