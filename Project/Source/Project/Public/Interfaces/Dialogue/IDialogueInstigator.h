// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDialogueInstigator.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueInstigator : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IDialogueInstigator
{
	GENERATED_BODY()

public:
	virtual void StartDialogueWith(AActor* OtherActor) = 0;
};
