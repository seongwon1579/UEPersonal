#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

UENUM(BlueprintType)
enum class EDialogueReaction : uint8
{
	None,
	Laugh,
	Angry,
	End,
};


USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPCResponse;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AffinityChanged;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueReaction Reaction = EDialogueReaction::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextNodeID = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOneTimeOnly;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NodeID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText NPCText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (TitileProperty = "OptionText"))
	TArray<FDialogueOption> Options;
	
};

USTRUCT(BlueprintType)
struct FDialogueResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FText ResponseText;
	
	UPROPERTY(BlueprintReadOnly)
	EDialogueReaction Reaction = EDialogueReaction::None;
	
	UPROPERTY(BlueprintReadOnly)
	int32 AffinityChange;
	
	UPROPERTY(BlueprintReadOnly)
	int32 NewAffinity;
	
	UPROPERTY(BlueprintReadOnly)
	int32 NextNodeID = -1;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsEnd;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNPCResponded, const FDialogueResult&);