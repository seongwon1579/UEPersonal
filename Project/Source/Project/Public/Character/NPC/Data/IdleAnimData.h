#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IdleAnimData.generated.h" 

USTRUCT(BlueprintType)
struct FIdleAnimData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UAnimSequence* StartAnim = nullptr;
    
	UPROPERTY(EditAnywhere)
	UAnimSequence* LoopAnim = nullptr;
    
	UPROPERTY(EditAnywhere)
	UAnimSequence* EndAnim = nullptr;
    
	UPROPERTY(EditAnywhere)
	float Weight = 1.0f;
    
	UPROPERTY(EditAnywhere)
	float LoopDuration = 5.f;
};
