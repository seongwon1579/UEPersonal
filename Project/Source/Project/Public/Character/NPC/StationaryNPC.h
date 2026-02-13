// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Dialogue/DialogueableInterface.h"
#include "Dialogue/Data/DialogueData.h"
#include "Interfaces/Interaction/InteractableInterface.h"

#include "StationaryNPC.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class USceneComponent;
class UNPCMovableAnimDataAsset;

UCLASS()
class PROJECT_API AStationaryNPC : public AActor , public IInteractableInterface, public IDialogueableInterface
{
	GENERATED_BODY()

public:
	AStationaryNPC();
	
	virtual void Interact(AActor* OtherActor) override;
	virtual bool CanInteract() const override;
	
	virtual void StartConversation() override;
	virtual void EndConversation() override;
	virtual void ReceiveDialogueChoice(int32 OptionIndex) override;
	virtual FString GetNPCName() const override { return NPCName; }
	virtual bool HasDialogue() const override { return DialogueNodes.Num() > 0; }
	virtual FText GetCurrentNPCText() const override;
	virtual TArray<FDialogueOption> GetCurrentOptions() const override;
	virtual FOnNPCResponded& GetOnNPCResponded() override { return OnNPCResponded; }
	
	int32 GetAffinity() const {return Affinity;}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* InteractionZone = nullptr;
	
	FString NPCName = TEXT("NPC");
	int32 Affinity = 50;
	
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "NPCText"))
	TArray<FDialogueNode> DialogueNodes;
	
	int32 DefaultStartNodeID = 0;
	int32 HighAffinityStartNodeID = -1;
	int32 LowAffinityStartNodeID = -1;
	
	UPROPERTY(EditAnywhere, Category = "NPC|Animation")
	TMap<EDialogueReaction, UAnimMontage*> ReactionMontages;
	
	FOnNPCResponded OnNPCResponded;
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex);
	
	EDialogueReaction DetermineReaction(const FDialogueOption& Option);
	FText DetermineResponse(const FDialogueOption& Option);
	
	int32 GetStartNodeID();
	FDialogueNode GetNode(int32 NodeID) const;
	FDialogueNode GetCurrentNode() const;
	
	void ChangeAffinity(int32 Amount);
	void PlayReaction(EDialogueReaction Reaction);
	
	int32 CurrentNodeID = 0;
	TMap<int32, TArray<int32>> UsedOptions;
	
};
