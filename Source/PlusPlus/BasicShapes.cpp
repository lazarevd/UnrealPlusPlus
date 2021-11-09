// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicShapes.h"
#include "Engine.h"




// By Sebastian Lague tutorial
ABasicShapes::ABasicShapes()
{
    ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = ThisScene;

    ThisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GenerateMesh"));
    ThisMesh->SetupAttachment(RootComponent);

}

void ABasicShapes::PostActorCreated()
{
    Super::PostActorCreated();
    GenerateMesh();
}

void ABasicShapes::PostLoad()
{
    Super::PostLoad();
    GenerateMesh();
}

void ABasicShapes::GenerateMesh()
{
    Vertices.Reset();
    Triangles.Reset();
    Normals.Reset();
    Tangents.Reset();
    UVs.Reset();
    Colors.Reset();

    int32 resolution = 13;
    int32 planeCount = 6;
    float scale = 100.0f;
    FProcMeshTangent TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);

    Vertices.SetNum(resolution * resolution * planeCount);
    Triangles.SetNum((resolution - 1) * (resolution - 1) * 6 * planeCount);
    Normals.SetNum((resolution - 1) * (resolution - 1) * 2 * planeCount);
    Tangents.SetNum((resolution - 1) * (resolution - 1) * 2 * planeCount);
    Colors.SetNum((resolution - 1) * (resolution - 1) * 2 * planeCount);
    UVs.SetNum((resolution - 1) * (resolution - 1) * 6 * planeCount);

    AddSquareMesh(FVector(0.0f, 1.0f, 0.0f), resolution, scale, 0,  TangentSetup);
    AddSquareMesh(FVector(0.0f, -1.0f, 0.0f), resolution, scale, 1, TangentSetup);
    AddSquareMesh(FVector(1.0f, 0.0f, 0.0f), resolution, scale, 2, TangentSetup);
    AddSquareMesh(FVector(-1.0f, 0.0f, 0.0f), resolution, scale, 3,  TangentSetup);
    AddSquareMesh(FVector(0.0f, 0.0f, 1.0f), resolution, scale, 4, TangentSetup);
    AddSquareMesh(FVector(0.0f, 0.0f, -1.0f), resolution, scale, 5, TangentSetup);

    ThisMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

}


void ABasicShapes::AddSquareMesh(FVector normal, int32 resolution, int32 scale, int32 planeNumber, FProcMeshTangent Tangent)
{
    FVector axisA = FVector(normal.Y, normal.Z, normal.X);//WTF Sebastian Lague says to do so (Procedural planets (E01))
    FVector axisB = FVector::CrossProduct(normal, axisA).GetSafeNormal()*-1;


    int32 triIndex = 0;
    int32 triangleCount = 0;
    if (planeNumber != 0) {
        triIndex += (resolution - 1) * (resolution - 1) * 2 * 3 * planeNumber;// res * 2 triangles per poly * 3 vertice per triangle 
        triangleCount += (resolution - 1) * (resolution - 1) * 2 * planeNumber;
    }
    
    for (int x = 0; x < resolution; x++) {
        for (int y = 0; y < resolution; y++) {
            int32 vertexIndex = (x + y * resolution) + resolution * resolution * planeNumber;
            FVector2D gridPos = FVector2D(x, y) / (resolution - 1.0f);
            FVector point = normal*scale + axisA * (2 * gridPos.X - 1)*scale + axisB * (2 * gridPos.Y - 1)*scale;
            Vertices[vertexIndex] = point;
            UVs[vertexIndex] = FVector2D(0.f, 0.f);
        
            if (x != resolution - 1 && y != resolution - 1) {
                Triangles[triIndex + 0] = vertexIndex;
                Triangles[triIndex + 1] = vertexIndex + resolution + 1;
                Triangles[triIndex + 2] = vertexIndex + resolution;
                triIndex += 3;
                Normals[triangleCount] = normal;
                Tangents[triangleCount] = Tangent;
                Colors[triangleCount] = FLinearColor::Green;
                triangleCount += 1;
                Triangles[triIndex + 0] = vertexIndex;
                Triangles[triIndex + 1] = vertexIndex + 1;
                Triangles[triIndex + 2] = vertexIndex  + resolution + 1;
                triIndex += 3;
                Normals[triangleCount] = normal;
                Tangents[triangleCount] = Tangent;
                Colors[triangleCount] = FLinearColor::Green;
                triangleCount += 1;
        }
        }
    }
}


