#pragma once

#include "ProceduralMeshComponent.h"	// Needed for FProcMeshTangent
#include "FSelectionSet.generated.h"

USTRUCT(BlueprintType)
struct FSelectionSet {
	GENERATED_USTRUCT_BODY()

	// This is the normalized list of selection weightings for whatever we're selecting
	UPROPERTY(BlueprintReadWrite)
		TArray<float> selectionWeights;

	// Simple constructor
	FSelectionSet() {
		selectionWeights = TArray<float>();
	}
};