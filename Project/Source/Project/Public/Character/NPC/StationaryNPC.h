// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Dialogue/DialogueResponder.h"
#include "Dialogue/Data/DialogueData.h"
#include "Interfaces/Interaction/InteractableInterface.h"

#include "StationaryNPC.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class USceneComponent;
class UNPCMovableAnimDataAsset;
class UStationaryNPCAnimInstance;
class UWidgetComponent;

UCLASS()
class PROJECT_API AStationaryNPC : public AActor , public IInteractableInterface, public IDialogueResponder
{
	GENERATED_BODY()

public:
	AStationaryNPC();
	
	// IInteractableInterface
	virtual void Interact(AActor* OtherActor) override;
	virtual bool CanInteract() const override;
	
	// IDialogueResponder
	virtual void InitDialogue() override;
	virtual void EndDialogue() override;
	virtual void ReceiveDialogueChoice(int32 OptionIndex) override;
	virtual bool HasDialogue() const override { return DialogueNodes.Num() > 0; }
	virtual const FNextNodeData GetNextNodeData() override;
	virtual FOnDialogueResponded& OnDialogueResponded() override { return OnNPCResponded; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* InteractionZone = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "NPCText"))
	FText NPCName = FText::FromString(TEXT("NPC"));
	
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "NPCText"))
	TArray<FDialogueNode> DialogueNodes;
	
	UPROPERTY()
	UStationaryNPCAnimInstance* StationaryNPCAnimInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* InteractionWidgetComp;
	
	FOnDialogueResponded OnNPCResponded;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex);
	
	virtual void BeginPlay() override;
	
	FDialogueNode GetCurrentNode() const;
	void PlayReaction(EDialogueReaction Reaction);
	
	int32 CurrentNodeID = 0;
};
