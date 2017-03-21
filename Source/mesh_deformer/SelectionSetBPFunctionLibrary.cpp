// Fill out your copyright notice in the Description page of Project Settings.

#include "mesh_deformer.h"
#include "SelectionSetBPFunctionLibrary.h"

FSelectionSet USelectionSetBPFunctionLibrary::FullSelectionSetFromMeshGeometry(FMeshGeometry meshGeo)
{
	FSelectionSet selectionSet;

	// Iterate over the mesh's sections
	for (auto &section : meshGeo.sections) {
		// Add a number of 1's to the selection set equal to the number of vertices.
		const int vertexCount = section.vertices.Num();
		for (int32 i = 0; i < vertexCount; ++i) {
			selectionSet.selectionWeights.Add(1.0f);
		}
	}

	return selectionSet;
}

FSelectionSet USelectionSetBPFunctionLibrary::RandomSelectionSetFromMeshGeometry(
	FMeshGeometry meshGeo, FRandomStream randomStream, float min, float max
) {
	FSelectionSet selectionSet;

	// Iterate over the mesh's sections
	for (auto &section : meshGeo.sections) {
		// Add a number of 1's to the selection set equal to the number of vertices.
		const int vertexCount = section.vertices.Num();
		for (int32 i = 0; i < vertexCount; ++i) {
			selectionSet.selectionWeights.Add(randomStream.FRandRange(min, max));
		}
	}

	return selectionSet;
}

// TODO: These should be somewhere sensible..
FMeshGeometry USelectionSetBPFunctionLibrary::Translate(
	FMeshGeometry meshGeo, FVector translation, FSelectionSet selection
) {
	// We'll be iterating over the selection set by index, this is the next item.
	int32 selectionNextItem = 0;


	// Iterate over the mesh's sections
	FVector translatedVertex;
	float weighting;
	for (auto &section : meshGeo.sections) {
		// Iterate over the vertices of the section
		for (auto &vertex : section.vertices) {
			// Calculate the translated vertex position
			translatedVertex = vertex + translation;

			// Get the next weighting
			weighting = selection.selectionWeights[selectionNextItem++];

			// Do a LERP to calculate the actual position when the selection weighting is included
			FVector originalPos = vertex;
			vertex = FMath::Lerp(vertex, translatedVertex, weighting);

			UE_LOG(
				LogTemp, Log,
				TEXT("Blend %f,%f,%f x %f,%f,%f @ %f = %f,%f,%f"),
				originalPos.X, originalPos.Y, originalPos.Z,
				translatedVertex.X, translatedVertex.Y, translatedVertex.Z,
				weighting,
				vertex.X, vertex.Y, vertex.Z
			);
		}
	}

	// All done, return the final geometry
	return meshGeo;
}