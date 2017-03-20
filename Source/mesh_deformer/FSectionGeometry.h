#pragma once

#include "ProceduralMeshComponent.h"	// Needed for FProcMeshTangent
#include "FSectionGeometry.generated.h"

USTRUCT(BlueprintType)
struct FSectionGeometry {
	GENERATED_USTRUCT_BODY()

	// These are all of the standard data members passed into ProceduralMeshComponent::CreateMeshSection_LinearColor()
	UPROPERTY(BlueprintReadWrite)
		TArray<FVector> vertices;
	UPROPERTY(BlueprintReadWrite)
		TArray<int32> triangles;
	UPROPERTY(BlueprintReadWrite)
		TArray<FVector> normals;
	UPROPERTY(BlueprintReadWrite)
		TArray<FVector2D> uvs;
	UPROPERTY(BlueprintReadWrite)
		TArray<FProcMeshTangent> tangents;
	UPROPERTY(BlueprintReadWrite)
		TArray<FLinearColor> vertexColors;

	// Simple constructor
	FSectionGeometry() {
		vertices = TArray<FVector>();
		triangles = TArray<int32>();
		normals = TArray<FVector>();
		uvs = TArray<FVector2D>();
		tangents = TArray<FProcMeshTangent>();
		vertexColors = TArray<FLinearColor>();
	}
};