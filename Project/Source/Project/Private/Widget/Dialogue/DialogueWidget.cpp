// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Dialogue/DialogueWidget.h"

#include "DebugHelper.h"
#include "Character/Player/Component/Dialogue/DialogueComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UDialogueWidget::UpdateDialogueDisplay(const FNextNodeData& Data)
{
	if (NPCName_TextBlock)
		NPCName_TextBlock->SetText(Data.NPCName);
    
	if (Dialogue_TextBlock)
		Dialogue_TextBlock->SetText(Data.NPCText);
    
	if (Choice_VerticalBox)
		Choice_VerticalBox->SetVisibility(ESlateVisibility::Visible);
    
	UpdateChoiceButtons(Data.OptionsTexts);
}

void UDialogueWidget::ShowResponseText(const FText& ResponseText)
{
	if (Choice_VerticalBox)
		Choice_VerticalBox->SetVisibility(ESlateVisibility::Hidden);
    
	if (Dialogue_TextBlock)
		Dialogue_TextBlock->SetText(ResponseText);
}

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Choice1_Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnChoice1Clicked);
	Choice2_Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnChoice2Clicked);
	Choice3_Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnChoice3Clicked);
}

void UDialogueWidget::OnChoice1Clicked()
{
	OnDialogueChoiceSelected.Broadcast(0);
}

void UDialogueWidget::OnChoice2Clicked()
{
	OnDialogueChoiceSelected.Broadcast(1);
}

void UDialogueWidget::OnChoice3Clicked()
{
	OnDialogueChoiceSelected.Broadcast(2);
}

void UDialogueWidget::UpdateChoiceButtons(const TArray<FText>& Options)
{
	SetupButton(Choice1_Button, Choice1_TextBlock, Options.IsValidIndex(0), 
			   Options.IsValidIndex(0) ? Options[0] : FText::GetEmpty());
    
	SetupButton(Choice2_Button, Choice2_TextBlock, Options.IsValidIndex(1), 
				Options.IsValidIndex(1) ? Options[1] : FText::GetEmpty());
    
	SetupButton(Choice3_Button, Choice3_TextBlock, Options.IsValidIndex(2), 
				Options.IsValidIndex(2) ? Options[2] : FText::GetEmpty());
}

void UDialogueWidget::SetupButton(UButton* Button, UTextBlock* Text, bool bVisible, const FText& OptionText)
{
	if (!Button) return;
    
	ESlateVisibility Visible = bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	Button->SetVisibility(Visible);
    
	if (Text && bVisible) Text->SetText(OptionText);
}
