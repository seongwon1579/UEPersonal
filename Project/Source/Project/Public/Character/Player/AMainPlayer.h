// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/ProjectCharacter.h"

#include "AMainPlayer.generated.h"

class UInputAction;

UCLASS()
class PROJECT_API AMainPlayer : public AProjectCharacter
{
	GENERATED_BODY()

public:
	void SetCurrentInteractable(AActor* InInteractable) { CurrentInteractable = InInteractable; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;
	
private:
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* CurrentInteractable;
	
	
	void OnInteractInput();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
