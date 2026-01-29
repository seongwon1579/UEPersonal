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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	UNPCStationaryAnimDataAsset* AnimDataAsset;
	
	UPROPERTY()
	UStationaryNPCAnimInstance* NPCAnimInstance;

protected:
	virtual void BeginPlay() override;

private:
	void InitializeAnimData(UStationaryNPCAnimInstance* InStationaryNPCAnimInstance);
};
