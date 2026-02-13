// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/StationaryNPC.h"
#include "DebugHelper.h"
#include "Character/Player/AMainPlayer.h"
#include "Components/SphereComponent.h"
#include "SubSystem/UISubSystem.h"


AStationaryNPC::AStationaryNPC()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("Interactor"));
	InteractionZone->SetupAttachment(RootComponent);
	//InteractionZone->SetCollisionProfileName(TEXT("Trigger"));

	if (InteractionZone)
	{
		InteractionZone->OnComponentBeginOverlap.AddDynamic(this, &AStationaryNPC::OnOverlapBegin);
		InteractionZone->OnComponentEndOverlap.AddDynamic(this, &AStationaryNPC::OnOverlapEnd);
	}
}

void AStationaryNPC::Interact(AActor* OtherActor)
{
	if (IDialogueInstigatorInterface* DialogueInstigator = Cast<IDialogueInstigatorInterface>(OtherActor))
	{
		if (DialogueInstigator->CanDialogue())
		{
			DialogueInstigator->StartDialogue(this);
		}
	}
}

bool AStationaryNPC::CanInteract() const
{
	return HasDialogue();
}

void AStationaryNPC::StartConversation()
{
	CurrentNodeID = GetStartNodeID();
	UsedOptions.Empty();
}

void AStationaryNPC::EndConversation()
{
	UsedOptions.Empty();
}

void AStationaryNPC::ReceiveDialogueChoice(int32 OptionIndex)
{
	TArray<FDialogueOption> Options = GetCurrentOptions();

	if (!Options.IsValidIndex(OptionIndex)) return;

	const FDialogueOption& SelectedOption = Options[OptionIndex];

	FDialogueResult Result;

	// 호감도 변경
	ChangeAffinity(SelectedOption.AffinityChanged);
	Result.AffinityChange = SelectedOption.AffinityChanged;
	Result.NewAffinity = Affinity;

	// 반응 결정(애니메이션)
	Result.Reaction = DetermineReaction(SelectedOption);

	// 반응 결정 (Text)
	Result.ResponseText = DetermineResponse(SelectedOption);

	// 다음 노드
	Result.NextNodeID = SelectedOption.NextNodeID;
	Result.bIsEnd = (SelectedOption.NextNodeID < 0);

	// 사용한 선택지 기록
	if (SelectedOption.bOneTimeOnly)
	{
		if (!UsedOptions.Contains(CurrentNodeID))
		{
			UsedOptions.Add(CurrentNodeID, TArray<int32>());
		}
		
		// 선택한 선택지 캐싱
		FDialogueNode CurrentNode = GetCurrentNode();
		for (int32 i = 0; i < CurrentNode.Options.Num(); i++)
		{
			if (CurrentNode.Options[i].OptionText.EqualTo(SelectedOption.OptionText))
			{
				UsedOptions[CurrentNodeID].AddUnique(i);
				break;
			}
		}
	}
	
	// 애니메이션 재생
	PlayReaction(Result.Reaction);

	// 다음 노드로 변경
	if (!Result.bIsEnd)
	{
		CurrentNodeID = Result.NextNodeID;
	}

	// 결과 전달
	OnNPCResponded.Broadcast(Result);
}

FText AStationaryNPC::GetCurrentNPCText() const
{
	return GetCurrentNode().NPCText;
}

TArray<FDialogueOption> AStationaryNPC::GetCurrentOptions() const
{
	FDialogueNode CurrentNode = GetCurrentNode();
	TArray<FDialogueOption> AvailableOptions;

	const TArray<int32>* UsedIndices = UsedOptions.Find(CurrentNodeID);

	for (int32 i = 0; i < CurrentNode.Options.Num(); i++)
	{
		// 조건: bOneTimeOnly가 true이고 + 이미 사용한 선택지면
		if (CurrentNode.Options[i].bOneTimeOnly && UsedIndices && UsedIndices->Contains(i))
		{
			continue;
		}
		AvailableOptions.Add(CurrentNode.Options[i]);
	}

	return AvailableOptions;
}


void AStationaryNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	// 현재 인터렉션 대상을 플레이어에게 전달
	Player->SetCurrentInteractable(this);

	// UI를 담당하는 서스시스템에서 인터렉션 UI를 출력
	UUISubSystem* UISubSystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	if (UISubSystem)
	{
		UISubSystem->ShowInteractionWidget();
	}
}

void AStationaryNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (!Player) return;

	Player->SetCurrentInteractable(nullptr);

	UUISubSystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubSystem>();
	if (UISubsystem)
	{
		UISubsystem->HideInteractionWidget();
	}
}

EDialogueReaction AStationaryNPC::DetermineReaction(const FDialogueOption& Option)
{
	return Option.Reaction;
}

FText AStationaryNPC::DetermineResponse(const FDialogueOption& Option)
{
	return Option.NPCResponse;
}

int32 AStationaryNPC::GetStartNodeID()
{
	if (Affinity >= 70 && HighAffinityStartNodeID >= 0 && DialogueNodes.IsValidIndex(HighAffinityStartNodeID))
	{
		return HighAffinityStartNodeID;
	}

	if (Affinity <= 30 && LowAffinityStartNodeID >= 0 && DialogueNodes.IsValidIndex(LowAffinityStartNodeID))
	{
		return LowAffinityStartNodeID;
	}

	return DefaultStartNodeID;
}

FDialogueNode AStationaryNPC::GetNode(int32 NodeID) const
{
	if (DialogueNodes.IsValidIndex(NodeID))
	{
		return DialogueNodes[NodeID];
	}
	return FDialogueNode();
}

FDialogueNode AStationaryNPC::GetCurrentNode() const
{
	return GetNode(CurrentNodeID);
}

void AStationaryNPC::ChangeAffinity(int32 Amount)
{
	Affinity = FMath::Clamp(Affinity + Amount, 0, 100);
}

void AStationaryNPC::PlayReaction(EDialogueReaction Reaction)
{
	if (Reaction == EDialogueReaction::None) return;

	UAnimMontage** FoundMontage = ReactionMontages.Find(Reaction);
	if (!FoundMontage || !*FoundMontage) return;

	UAnimInstance* Anim = MeshComponent->GetAnimInstance();
	if (!Anim) return;
	
	Anim->Montage_Play(*FoundMontage);
}
