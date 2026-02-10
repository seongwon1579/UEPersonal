// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/MovableNPC.h"

#include "Components/SplineComponent.h"

AMovableNPC::AMovableNPC()
{
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	if (!SplineComp) return;
	
	SplineComp->SetupAttachment(RootComponent);
}
