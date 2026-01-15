#pragma once

#include "CoreMinimal.h"
#include "FRoadPavement.h"
#include "FRoadRail.h"
#include "FRoadSegment.h"
#include "FRoadSideWalk.h"
#include "Engine/DataTable.h"
#include "FRoadProperties.generated.h" 

USTRUCT(BlueprintType)
struct FRoadProperties : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	FRoadPavement RoadPavement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	FRoadSegment RoadSegment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	FRoadSideWalk RoadSideWalk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road")
	FRoadRail RoadRail;
	
};
