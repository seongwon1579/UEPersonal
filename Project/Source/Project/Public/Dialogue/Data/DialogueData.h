#pragma once

#include "CoreMinimal.h"
#include "DialogueData.generated.h"

UENUM(BlueprintType)
enum class EDialogueReaction : uint8
{
	None,
	Laugh,
	Angry,
	Surprised,
	Shy,
	Happy,
	Speak,
	WaveHands,
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
	FText NPCResponse;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnd;
};

USTRUCT(BlueprintType)
struct FNextNodeData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FText NPCName;

	UPROPERTY(BlueprintReadOnly)
	FText NPCText;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> OptionsTexts;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueResponded, const FDialogueResult&);
