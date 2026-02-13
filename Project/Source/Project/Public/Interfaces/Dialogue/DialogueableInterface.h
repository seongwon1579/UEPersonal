// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Dialogue/Data/DialogueData.h"

#include "DialogueableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_API IDialogueableInterface
{
	GENERATED_BODY()

public:
	virtual void StartConversation() = 0;
	virtual void EndConversation() = 0;
	virtual void ReceiveDialogueChoice(int32 OptionIndex) = 0;
	
	virtual FString GetNPCName() const = 0;
	virtual bool HasDialogue() const = 0;
	virtual FText GetCurrentNPCText() const = 0;
	virtual TArray<FDialogueOption> GetCurrentOptions() const = 0;

	virtual FOnNPCResponded& GetOnNPCResponded() = 0;
};
