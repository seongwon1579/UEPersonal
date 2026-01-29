// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/Component/MotionComponent.h"

#include "DebugHelper.h"
#include "Character/NPC/StationaryNPCAnimInstance.h"
#include "Character/NPC/Data/NPCStationaryAnimDataAsset.h"

// Sets default values for this component's properties
UMotionComponent::UMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!AnimDataAsset) return;
	
	// NPCAnimInstance 초기화
	if (USkeletalMeshComponent* Mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
	{
		NPCAnimInstance = Cast<UStationaryNPCAnimInstance>(Mesh->GetAnimInstance());
		if (NPCAnimInstance)
		{
			InitializeAnimData(NPCAnimInstance);
		}
	}
}

// AnimInstance의 AnimSequence의 할당을 위해 데이터 어셋에 요청한다.
void UMotionComponent::InitializeAnimData(UStationaryNPCAnimInstance* InStationaryNPCAnimInstance)
{
	if (!AnimDataAsset) return;

	AnimDataAsset->SetupAnimationInstance(InStationaryNPCAnimInstance);
	InStationaryNPCAnimInstance->bIsAnimDataReady = true;
}
