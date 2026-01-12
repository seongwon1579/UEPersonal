#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FRoadSegment.generated.h" 

USTRUCT(BlueprintType)
struct FRoadSegment : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoadSegment")
	float BeginRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoadSegment")
	float EndRoll;

};
