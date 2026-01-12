// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

class USplineMeshComponent;
class USplineComponent;
class USceneComponent;
class UStaticMesh;

UCLASS()
class PROJECT_API ARoad : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=  "Scene")
	USceneComponent* DefaultSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline");
	USplineComponent* SplineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TArray<USplineMeshComponent*> SplineMeshComponents;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	// UStaticMesh* RoadMesh; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
	FDataTableRowHandle RoadDataHandle;
	
public:	
	// Sets default values for this actor's properties
	ARoad();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
