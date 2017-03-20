#pragma once

#include "FSectionGeometry.h"
#include "FMeshGeometry.generated.h"

USTRUCT(BlueprintType)
struct FMeshGeometry {
	GENERATED_USTRUCT_BODY()

	// These are all of the standard data members passed into ProceduralMeshComponent::CreateMeshSection_LinearColor()
	UPROPERTY(BlueprintReadWrite)
		TArray<FSectionGeometry> sections;

	// Simple constructor
	FMeshGeometry() {
		sections = TArray<FSectionGeometry>();
	}
};