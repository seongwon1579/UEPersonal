// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Dialogue/DialogueComponent.h"
#include "SubSystem/UISubSystem.h"
#include "Interfaces/Dialogue/DialogueResponder.h"
#include "Widget/Dialogue/DialogueWidget.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueComponent::StartDialogueWith(AActor* NPCActor)
{
	if (!NPCActor || bOnDialogue) return;

	IDialogueResponder* Responder = Cast<IDialogueResponder>(NPCActor);
	if (!Responder || !Responder->HasDialogue()) return;

	ConfigureInputMode(true);
	ConfigureDialogue(Responder, true);
	
	if (DialogueResponder)
	{
		DialogueResponder->OnDialogueResponded().AddUObject(this, &UDialogueComponent::HandleDialogueResponse);
		DialogueResponder->InitDialogue();
	}
	
	// UI 시작
	if (UISubSystem)
	{
		UISubSystem->ShowDialogueWidget(this);
		
		if (DialogueWidget)
		{
			DialogueWidget->OnDialogueChoiceSelected.AddUObject(this, &UDialogueComponent::OnChoiceInput);
			ShowNextNode();
		}
	}
}

void UDialogueComponent::EndDialogue()
{
	if (!bOnDialogue) return;

	GetWorld()->GetTimerManager().ClearTimer(ResponseTimerHandle);
	
	if (DialogueWidget)
	{
		DialogueWidget->OnDialogueChoiceSelected.RemoveAll(this);
	}
	
	if (DialogueResponder)
	{
		DialogueResponder->OnDialogueResponded().RemoveAll(this);
		DialogueResponder->EndDialogue();
	}

	if (UISubSystem)
	{
		UISubSystem->HideDialogueWidget();
	}
	
	ConfigureInputMode(false);
	ConfigureDialogue(nullptr, false);
}

// 옵션 선택
void UDialogueComponent::OnChoiceInput(int32 OptionIndex)
{
	if (!bOnDialogue || !DialogueResponder) return;
	
	// NPC의 현재 답변을 보냄
	DialogueResponder->ReceiveDialogueChoice(OptionIndex);
}

void UDialogueComponent::HandleDialogueResponse(const FDialogueResult& Result)
{
	if (DialogueWidget)
	{
		DialogueWidget->ShowResponseText(Result.NPCResponse);
	}
	
	if (Result.bIsEnd)
	{
		GetWorld()->GetTimerManager().SetTimer(ResponseTimerHandle, this, &UDialogueComponent::EndDialogue, 3.f, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ResponseTimerHandle, this, &UDialogueComponent::ShowNextNode, 3.f,
		                                       false);
	}
}

void UDialogueComponent::ShowNextNode()
{
	if (!DialogueWidget || !bOnDialogue) return;
	
	DialogueWidget->UpdateDialogueDisplay(DialogueResponder->GetNextNodeData());
}

void UDialogueComponent::ConfigureInputMode(bool IsUIMode)
{
	if (!PlayerController) return;

	PlayerController->bShowMouseCursor = IsUIMode;

	if (IsUIMode)
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void UDialogueComponent::ConfigureDialogue(IDialogueResponder* Target, bool bInOnDialogue)
{
	bOnDialogue = bInOnDialogue;
	DialogueResponder = Target;
}


void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	UISubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubSystem>();

	if (UISubSystem)
	{
		DialogueWidget = UISubSystem->GetDialogueWidget();
	}
	
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;
	
	PlayerController = Cast<APlayerController>(Pawn->GetController());
}
