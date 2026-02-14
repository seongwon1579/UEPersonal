// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Dialogue/Data/DialogueData.h"
#include "DialogueComponent.generated.h"


struct FDialogueResult;
class UUISubSystem;
class IDialogueResponder;
class APlayerController;
class UDialogueWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueComponent();
	
	void StartDialogueWith(AActor* NPCActor);
	void EndDialogue();
	
	void OnChoiceInput(int32 OptionIndex);
	bool IsInDialogue() const {return bOnDialogue;}

private:
	virtual void BeginPlay() override;
	
	void HandleDialogueResponse(const FDialogueResult& Result);
	void ShowNextNode();
	
	void ConfigureInputMode(bool IsUIMode);
	void ConfigureDialogue(IDialogueResponder* Target, bool bInOnDialogue);
	
	UPROPERTY()
	UUISubSystem* UISubSystem;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY()
	UDialogueWidget* DialogueWidget;
	
	IDialogueResponder* DialogueResponder;
	bool bOnDialogue = false;
	FTimerHandle ResponseTimerHandle;
};
