// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/StationaryNPC.h"
#include "Character/NPC/StationaryNPCAnimInstance.h"
#include "Character/Player/AMainPlayer.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/Interaction/InteractionWidget.h"

AStationaryNPC::AStationaryNPC()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	
	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("Interactable"));
	InteractionZone->SetupAttachment(RootComponent);
	
	InteractionWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidgetComp->SetupAttachment(RootComponent);
	
	SetWidgetVisibility(false);
}

void AStationaryNPC::Interact(AActor* OtherActor)
{
	SetWidgetVisibility(false);
	
	if (IDialogueInstigator* DialogueInstigator = 
		Cast<IDialogueInstigator>(OtherActor))
	{
		DialogueInstigator->StartDialogueWith(this);
	}
}

bool AStationaryNPC::CanInteract() const
{
	return HasDialogue();
}

void AStationaryNPC::InitDialogue()
{
	// 대화가 시작되면 현재 노드(0)를 할당
	CurrentNodeID = 0;
	
	if (StationaryNPCAnimInstance)
		StationaryNPCAnimInstance->StartDialogue();
}

void AStationaryNPC::EndDialogue()
{
	if (StationaryNPCAnimInstance)
		StationaryNPCAnimInstance->EndDialogue();
}

// 선택지 버튼이 클릭시 호출됨
void AStationaryNPC::ReceiveDialogueChoice(int32 OptionIndex)
{
	// 현재 노드의 선택지 찾기
	FDialogueNode CurrentNode = GetCurrentNode();
	FDialogueOption CurrentOption = CurrentNode.Options[OptionIndex];
	
	// 리액션 애니메이션 재생
	PlayReaction(CurrentOption.Reaction);
	
	// 버튼 클릭에 대한 정보 
	FDialogueResult Result;
	Result.bIsEnd = CurrentOption.NextNodeID < 0;
	Result.NPCResponse = CurrentOption.NPCResponse;
	
	// 다음노드로 변경
	CurrentNodeID = CurrentOption.NextNodeID;
	
	// 정보 전달
	OnNPCResponded.Broadcast(Result);
}

const FNextNodeData AStationaryNPC::GetNextNodeData()
{
	FNextNodeData Data;
	
	// 현재 노드가 있는지 확인
	if (CurrentNodeID < 0) return Data;
	
	// 현재 노드의 정보 
	FDialogueNode CurrentNode = GetCurrentNode();
	Data.NPCName = NPCName;
	Data.NPCText = CurrentNode.NPCText;
	
	for (auto Option : CurrentNode.Options)
	{
		Data.OptionsTexts.Add(Option.OptionText);
	}
	return Data;
}

void AStationaryNPC::BeginPlay()
{
	Super::BeginPlay();
	
	UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
	StationaryNPCAnimInstance = Cast<UStationaryNPCAnimInstance>(AnimInstance);
	
	if (!bCanDialogue) return;

	if (InteractionZone)
	{
		InteractionZone->OnComponentBeginOverlap.AddDynamic(this, &AStationaryNPC::OnDialogueOverlapBegin);
		InteractionZone->OnComponentEndOverlap.AddDynamic(this, &AStationaryNPC::OnDialogueOverlapEnd);
	}
	
	if (UInteractionWidget* Widget = Cast<UInteractionWidget>(InteractionWidgetComp->GetWidget()))
	{
		Widget->SetInteractionType(FText::FromString(TEXT("대화하기")));
	}
	
	SetWidgetVisibility(false);
}

void AStationaryNPC::OnDialogueOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(this);
	
	SetWidgetVisibility(true);
}

void AStationaryNPC::OnDialogueOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex)
{
	if (!bCanDialogue) return;
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(nullptr);
	
	SetWidgetVisibility(false);
}


FDialogueNode AStationaryNPC::GetCurrentNode() const
{
	if (DialogueNodes.IsValidIndex(CurrentNodeID))
	{
		return DialogueNodes[CurrentNodeID];
	}
	return FDialogueNode();
}

void AStationaryNPC::PlayReaction(EDialogueReaction Reaction)
{
	if (Reaction == EDialogueReaction::None) return;
	
	StationaryNPCAnimInstance->PlayReaction(Reaction);
}

void AStationaryNPC::SetWidgetVisibility(bool bVisible)
{
	if (InteractionWidgetComp)
	{
		InteractionWidgetComp->SetVisibility(bVisible);
	}
}
