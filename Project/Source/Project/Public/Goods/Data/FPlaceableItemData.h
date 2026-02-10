#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "FPlaceableItemData.generated.h"

UENUM()
enum class EPlaceableItemType : uint8
{
	Building,
	Exterior,
	Interior,
	End,
};

USTRUCT(BlueprintType)
struct FPlaceableItemData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh = nullptr;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// UMaterialInterface* Material = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInterface*> Materials; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Strength;
};
