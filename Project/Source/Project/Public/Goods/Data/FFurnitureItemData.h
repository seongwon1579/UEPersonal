#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FFurnitureItemData.generated.h" 

USTRUCT(BlueprintType)
struct FFurnitureItemData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail = nullptr;
};
