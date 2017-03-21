// (c)2017 Paul Golds, released under MIT license.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FSelectionSet.h"
#include "FMeshGeometry.h"
#include "SelectionSetBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MESH_DEFORMER_API USelectionSetBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Create a full-strength (all 1's) selection set from a FMeshGeometry item.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SelectionSet")
		static FSelectionSet FullSelectionSetFromMeshGeometry(FMeshGeometry meshGeo);

	// Create a random selection set from an FMeshGeometry item.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SelectionSet")
		static FSelectionSet RandomSelectionSetFromMeshGeometry(
			FMeshGeometry meshGeo, FRandomStream randomStream, float min=0.0f, float max=1.0f
		);


	// TODO: This shouldn't really be here..
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SelectionSet")
		static FMeshGeometry Translate(
			FMeshGeometry meshGeo, FVector translation, FSelectionSet selection
		);
};
