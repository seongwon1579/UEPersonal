// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Dialogue/DialogueWidget.h"

#include "DebugHelper.h"
#include "Character/Player/Component/Dialogue/DialogueComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UDialogueWidget::InitWidget(UDialogueComponent* InDialogueComponent)
{
	DialogueComponent = InDialogueComponent;
	
	if (!DialogueComponent) return;
	
	NPCName_TextBlock->SetText(FText::FromString(DialogueComponent->GetCurrentNPCName()));
	RefreshDisplay();
}

void UDialogueWidget::ShowResponse(const FDialogueResult& Result)
{
	if (Choice_VerticalBox)
	{
		Choice_VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Dialogue_TextBlock)
	{
		Dialogue_TextBlock->SetText(Result.ResponseText);
	}
}

void UDialogueWidget::RefreshDisplay()
{
	if (!DialogueComponent) return;
	
	// NPC 대사
	Dialogue_TextBlock->SetText(DialogueComponent->GetCurrentNPCText());
	
	Choice_VerticalBox->SetVisibility(ESlateVisibility::Visible);
	
	UpdateChoiceButtons();
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
	if (DialogueComponent) DialogueComponent->OnChoiceInput(0);
}

void UDialogueWidget::OnChoice2Clicked()
{
	if (DialogueComponent) DialogueComponent->OnChoiceInput(1);
}

void UDialogueWidget::OnChoice3Clicked()
{
	if (DialogueComponent) DialogueComponent->OnChoiceInput(2);
}

void UDialogueWidget::UpdateChoiceButtons()
{
	if (!DialogueComponent) return;
	
	TArray<FDialogueOption> Options = DialogueComponent->GetCurrentNPCOptions();
	
	SetupButton(Choice1_Button, Choice1_TextBlock, Options.IsValidIndex(0), Options.IsValidIndex(0) ? Options[0].OptionText : FText::GetEmpty());
	SetupButton(Choice2_Button, Choice2_TextBlock, Options.IsValidIndex(1), Options.IsValidIndex(1) ? Options[1].OptionText : FText::GetEmpty());
	SetupButton(Choice3_Button, Choice3_TextBlock, Options.IsValidIndex(2), Options.IsValidIndex(2) ? Options[2].OptionText : FText::GetEmpty());
}

void UDialogueWidget::SetupButton(UButton* Button, UTextBlock* Text, bool bVisible, const FText& OptionText)
{
	ESlateVisibility Visible = bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	Button->SetVisibility(Visible);
	if (Text && bVisible) Text->SetText(OptionText);
}
