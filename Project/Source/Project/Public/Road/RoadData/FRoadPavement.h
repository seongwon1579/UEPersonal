#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FRoadPavement.generated.h" 

USTRUCT(BlueprintType)
struct FRoadPavement : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadPavement")
	UStaticMesh* RoadMesh = nullptr;
};
