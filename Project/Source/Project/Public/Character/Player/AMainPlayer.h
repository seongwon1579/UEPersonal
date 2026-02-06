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
	// 현재 인터럭션 인스턴스 set
	void SetCurrentInteractable(AActor* InInteractable) { CurrentInteractable = InInteractable; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;
	
private:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void OnInteractInput();	
	void BindInputActions();

	UPROPERTY()
	AActor* CurrentInteractable;
	
};
