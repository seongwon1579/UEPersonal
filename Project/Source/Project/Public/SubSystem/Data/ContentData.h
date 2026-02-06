#pragma once

#include "CoreMinimal.h"
#include "ContentData.generated.h"

UENUM(BlueprintType)
enum class EActivityType : uint8
{
	None,
	Boxing,
	Handstand,
	Swimming,
};

UENUM(BlueprintType)
enum class EUnlockableType : uint8
{
	None,
	Dancing,
	Crafting,
};

UENUM(BlueprintType)
enum class EPlayerStatType : uint8
{
	None,
	Strength,
	Endurance,
	Flexibility,
	
	End UMETA(Hidden) 
};

// 스탯 보상
USTRUCT(BlueprintType)
struct FStatReward
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPlayerStatType, int32> Stats;
};


