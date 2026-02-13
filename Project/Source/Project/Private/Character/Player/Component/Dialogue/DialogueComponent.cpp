// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Component/Dialogue/DialogueComponent.h"
#include "SubSystem/UISubSystem.h"
#include "Interfaces/Dialogue/DialogueableInterface.h"
#include "Widget/Dialogue/DialogueWidget.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogueComponent::StartDialogue(AActor* NPCActor)
{
	if (!NPCActor || bIsInDialogue) return;

	IDialogueableInterface* DialogueNPC = Cast<IDialogueableInterface>(NPCActor);
	if (!DialogueNPC || !DialogueNPC->HasDialogue()) return;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;
	
	PC->bShowMouseCursor = true;
	PC->SetInputMode(FInputModeGameAndUI());

	CurrentNPCActor = NPCActor;
	CurrentNPC = DialogueNPC;
	bIsInDialogue = true;

	CurrentNPC->StartConversation();
	CurrentNPC->GetOnNPCResponded().AddUObject(this, &UDialogueComponent::HandleNPCResponse);

	// if (UISubSystem)
	// {
	// 	UISubSystem->ShowDialogueWidget(this);
	// }

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			if (UISubSystem && bIsInDialogue)
			{
				UISubSystem->ShowDialogueWidget(this);
			}
		},
		1.5f,
		false
	);
}

void UDialogueComponent::EndDialogue()
{
	if (!bIsInDialogue) return;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;
	
	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());
	
	GetWorld()->GetTimerManager().ClearTimer(ResponseTimerHandle);

	if (CurrentNPC)
	{
		CurrentNPC->GetOnNPCResponded().RemoveAll(this);
		CurrentNPC->EndConversation();
	}

	if (UISubSystem)
	{
		UISubSystem->HideDialogueWidget();
	}

	CurrentNPCActor = nullptr;
	CurrentNPC = nullptr;
	bIsInDialogue = false;
}

// 선택지 입력
void UDialogueComponent::OnChoiceInput(int32 OptionIndex)
{
	if (!CurrentNPC || !bIsInDialogue) return;

	TArray<FDialogueOption> Options = CurrentNPC->GetCurrentOptions();

	if (!Options.IsValidIndex(OptionIndex)) return;

	// NPC의 현재 답변을 보냄
	CurrentNPC->ReceiveDialogueChoice(OptionIndex);
}

void UDialogueComponent::HandleNPCResponse(const FDialogueResult& Result)
{
	if (UISubSystem)
	{
		UDialogueWidget* Widget = UISubSystem->GetDialogueWidget();
		if (!Widget) return;
		Widget->ShowResponse(Result);
	}
	if (Result.bIsEnd)
	{
		GetWorld()->GetTimerManager().SetTimer(ResponseTimerHandle, this, &UDialogueComponent::EndDialogue, 1.f, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ResponseTimerHandle, this, &UDialogueComponent::ShowNextNode, 1.5f,
		                                       false);
	}
}

void UDialogueComponent::ShowNextNode()
{
	if (!bIsInDialogue) return;

	if (UISubSystem)
	{
		UDialogueWidget* Widget = UISubSystem->GetDialogueWidget();
		if (!Widget) return;
		Widget->RefreshDisplay();
	}
}

FString UDialogueComponent::GetCurrentNPCName() const
{
	if (!CurrentNPC) return FString();
	return CurrentNPC->GetNPCName();
}

FText UDialogueComponent::GetCurrentNPCText() const
{
	if (!CurrentNPC) return FText::GetEmpty();
	return CurrentNPC->GetCurrentNPCText();
}

TArray<FDialogueOption> UDialogueComponent::GetCurrentNPCOptions() const
{
	if (!CurrentNPC) return TArray<FDialogueOption>();
	return CurrentNPC->GetCurrentOptions();
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	UISubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UUISubSystem>();
}
