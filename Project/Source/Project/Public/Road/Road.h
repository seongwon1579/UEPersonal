// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

struct FRoadProperties;
class USplineMeshComponent;
class USplineComponent;
class USceneComponent;
class UStaticMesh;

UCLASS()
class PROJECT_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:
	ARoad();
	virtual void OnConstruction(const FTransform& Transform) override;

#pragma region Private
private:
	void SetupSplineComponent();
	void ClearRoadMeshes();
	void UpdateRoadMeshes(const FRoadProperties* RoadProperties);
	void RefreshRoadProperties(const FRoadProperties* DefaultProperty, int Count);
	void CreateSplineMesh(int32 Index, UStaticMesh* StaticMesh, float BeginRoll, float EndRoll, float MeshLenght);
	void SetupSplineMesh(int32 Index ,USplineMeshComponent* TargetMeshComponent, UStaticMesh* StaticMesh, float MeshLenght);
	void RollSplineMesh(USplineMeshComponent* TargetMeshComponent, float BeginRoll, float EndRoll);
#pragma endregion

protected:
	USceneComponent* DefaultSceneComponent;
	USplineComponent* SplineComponent;
	TArray<USplineMeshComponent*> SplineMeshComponents;
	
	// Spline Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineData")
	FDataTableRowHandle RoadDataHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineData")
	TArray<FRoadProperties> RoadProperties;
	
	// Trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	bool bShowSplineOnly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	bool bShowRoadOnly;
};
