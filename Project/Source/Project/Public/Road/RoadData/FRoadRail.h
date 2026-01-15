#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FRoadRail.generated.h" 

USTRUCT(BlueprintType)
struct FRoadRail : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadRail")
	UStaticMesh* Left_RoadRail = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadRail")
	UStaticMesh* Right_RoadRail = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadRail")
	bool bNeed_Left_Rail = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoadRail")
	bool bNeed_Right_Rail = false;
	
	bool IsValid() const
	{
		return Left_RoadRail || Left_RoadRail;
	}
};
