// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/AMainPlayer.h"

#include "DebugHelper.h"
#include "EnhancedInputComponent.h"
#include "Activity/PunchingBag.h"
#include "Character/Player/Component/Activity/BoxingActivityComponent.h"

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// 키입력에 바인딩(키입력시 호출)
void AMainPlayer::OnInteractInput()
{
	// 현재 인터렉션이 무었인지 확인
	if (!Cast<APunchingBag>(CurrentInteractable)) return;

	// 복싱 컴포넌트 캐스팅
	UBoxingActivityComponent* BoxingComp = FindComponentByClass<UBoxingActivityComponent>();
	if (!BoxingComp) return;

	// 복싱 컴포넌트가 복싱을 구현하고 있으면 로직 시작
	if (IBoxingActivityInterface* BoxingActivity = Cast<IBoxingActivityInterface>(BoxingComp))
	{
		// 현재 복싱을 하고 있으면 리턴(반복된 상호작용을 방지)
		if (BoxingActivity->IsBoxing()) return;
		
		// 복싱 로직 시작
		BoxingActivity->StartBoxing();
	}
}

void AMainPlayer::BindInputActions()
{
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainPlayer::OnInteractInput);
	}
}
