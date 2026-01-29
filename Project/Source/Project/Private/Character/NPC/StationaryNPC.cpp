// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/StationaryNPC.h"

// Sets default values
AStationaryNPC::AStationaryNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStationaryNPC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStationaryNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

