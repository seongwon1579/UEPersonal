// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDialogueInstigatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueInstigatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IDialogueInstigatorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanDialogue() = 0;
	virtual void StartDialogue(AActor* OtherActor) = 0;
};
