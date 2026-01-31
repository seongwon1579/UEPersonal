// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotionComponent.generated.h"


class UNPCStationaryAnimDataAsset;
class UStationaryNPCAnimInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMotionComponent();

	UPROPERTY(EditAnywhere, Category = "DataSetting")
	UNPCStationaryAnimDataAsset* AnimDataAsset;
	
	UPROPERTY(EditAnywhere, Category = "DataSetting")
	float IdleBaseDuration = 7.f;

protected:
	virtual void BeginPlay() override;
	void InitializeAnimData(UStationaryNPCAnimInstance* InStationaryNPCAnimInstance);
};
