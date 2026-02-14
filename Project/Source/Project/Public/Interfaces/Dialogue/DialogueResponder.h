// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Dialogue/Data/DialogueData.h"

#include "DialogueResponder.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueResponder : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IDialogueResponder
{
	GENERATED_BODY()

public:
	virtual void InitDialogue() = 0;
	virtual void EndDialogue() = 0;
	virtual void ReceiveDialogueChoice(int32 OptionIndex) = 0;
	virtual bool HasDialogue() const = 0;
	virtual const FNextNodeData GetNextNodeData() = 0;

	virtual FOnDialogueResponded& OnDialogueResponded() = 0;
};
