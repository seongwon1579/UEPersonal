// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Dialogue/Data/DialogueData.h"
#include "DialogueComponent.generated.h"


struct FDialogueResult;
class UUISubSystem;
class IDialogueableInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();
	
	void StartDialogue(AActor* NPCActor);
	void EndDialogue();
	
	void OnChoiceInput(int32 OptionIndex);
	bool IsInDialogue() const {return bIsInDialogue;};
	
	FString GetCurrentNPCName() const;
	FText GetCurrentNPCText() const;
	TArray<FDialogueOption> GetCurrentNPCOptions() const;

private:
	// Called when the game starts
	virtual void BeginPlay() override;
	void HandleNPCResponse(const FDialogueResult& Result);
	void ShowNextNode();

	UPROPERTY()
	AActor* CurrentNPCActor;
	
	UPROPERTY()
	UUISubSystem* UISubSystem;
	
	IDialogueableInterface* CurrentNPC;
	bool bIsInDialogue = false;
	FTimerHandle ResponseTimerHandle;

};
