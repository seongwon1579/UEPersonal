#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FRoadSideWalk.generated.h" 

USTRUCT(BlueprintType)
struct FRoadSideWalk : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadSideWalk")
	UStaticMesh* Left_RoadSideWalk = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadSideWalk")
	UStaticMesh* Right_RoadSideWalk = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadSideWalk")
	bool bNeed_LeftSideWalk = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadSideWalk")
	bool bNeed_RightSideWalk = false;
	
	bool IsValid() const
	{
		return Left_RoadSideWalk || Right_RoadSideWalk;
	}
};
