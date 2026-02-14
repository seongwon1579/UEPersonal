// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Activity/BoxingActivityInterface.h"
#include "Interfaces/Dialogue/IDialogueInstigator.h"
#include "Project/ProjectCharacter.h"

#include "AMainPlayer.generated.h"

class UDialogueComponent;
class UInputAction;
class UBoxingActivityComponent;

UCLASS()
class PROJECT_API AMainPlayer : public AProjectCharacter, public IBoxingActivityInterface, public IDialogueInstigator
{
	GENERATED_BODY()

public:
	// 현재 인터럭션 인스턴스 set
	void SetCurrentInteractable(AActor* InInteractable) { CurrentInteractable = InInteractable; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;
	
	virtual bool IsBoxing() const override;
	virtual void StartBoxing() override;

	virtual void StartDialogueWith(AActor* OtherActor) override;
	
private:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void OnInteractInput();	

	UPROPERTY()
	AActor* CurrentInteractable;
	
	UPROPERTY()
	UBoxingActivityComponent* BoxingComp;
	
	UPROPERTY()
	UDialogueComponent* DialogueComp;
	
};
