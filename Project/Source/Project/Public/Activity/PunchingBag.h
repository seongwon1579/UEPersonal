// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/InteractableInterface.h"

#include "PunchingBag.generated.h"

class UBoxComponent;
class USceneComponent;
class UWidgetComponent;
UCLASS()
class PROJECT_API APunchingBag : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	APunchingBag();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanInteract() const override;
	FORCEINLINE virtual void Interact(AActor* Interactor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boxing")
	UStaticMeshComponent* PunchingBagMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* InteractionWidgetComp;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                    bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	UBoxComponent* InteractionZone;
};
