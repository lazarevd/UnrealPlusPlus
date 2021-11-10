// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "BasicShapes.generated.h"

UCLASS()
class PLUSPLUS_API ABasicShapes : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasicShapes();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshParameters")
	FVector PolySize = FVector(100.f, 100.f, 100.f);
protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* ThisScene;
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ThisMesh;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	void GenerateMesh();

private:	
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent>Tangents;
	TArray<FVector2D>UVs;
	TArray<FLinearColor>Colors;


	void AddSquareMesh(FVector normal, int32 resolution, int32 planeNumber, FProcMeshTangent Tangent);

	FVector PointOnCurveToPointOnSphere(FVector p);

};
