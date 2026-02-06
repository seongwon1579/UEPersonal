// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Goods/GoodsData/FFurnitureItemData.h"
#include "FurnitureSelectionWidget.generated.h"

/**
 * 
 */
class UUniformGridPanel;
struct FFurnitureItemData;
class UButton;

UCLASS()
class PROJECT_API UFurnitureSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

	
	virtual void NativeConstruct() override;
	
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Furniture_Button;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UniformGridPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> FurnitureSlot;
	
public:
	void PopulateGrid(const TArray<FFurnitureItemData*>& DataArray);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Some();
	
};
