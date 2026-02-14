// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dialogue/Data/DialogueData.h"

#include "DialogueWidget.generated.h"

/**
 * 
 */
class UDialogueComponent;
class UTextBlock;
class UVerticalBox;
class UButton; 

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueChoiceSelected, int32)

UCLASS()
class PROJECT_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnDialogueChoiceSelected OnDialogueChoiceSelected;
	
	// void InitWidget(UDialogueComponent* InDialogueComponent);
	// void ShowResponse(const FDialogueResult& Result);
	// void RefreshDisplay();
	
	void UpdateDialogueDisplay(const FNextNodeData& Data);
	void ShowResponseText(const FText& ResponseText);

private:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnChoice1Clicked();

	UFUNCTION()
	void OnChoice2Clicked();

	UFUNCTION()
	void OnChoice3Clicked();
	
	void UpdateChoiceButtons(const TArray<FText>& );
	
	void SetupButton(UButton* Button, UTextBlock* Text, bool bVisible, const FText& OptionText);
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NPCName_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Dialogue_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Choice_VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Choice1_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Choice2_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Choice3_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Choice1_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Choice2_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Choice3_TextBlock;
};
