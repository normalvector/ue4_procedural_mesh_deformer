// DeformMeshComponent, (c)2017 Paul Golds- released under MIT license.

#include "mesh_deformer.h"
#include "DeformMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Turn on/off debug options
#define DEBUG_DEFORM_MESH_COMPONENT 1

// Sets default values for this component's properties
UDeformMeshComponent::UDeformMeshComponent()
{
	// This component cannot tick.  It could be updated every tick by another system but that's none of our concern.
	PrimaryComponentTick.bCanEverTick = false;
}


// Rebuild the PMC
void UDeformMeshComponent::Rebuild() {
	UE_LOG(LogTemp, Log, TEXT("Rebuilding DMC"));
	
	// Check we have a PMC
	if (!ProceduralMeshComponent) {
		UE_LOG(LogTemp, Warning, TEXT("DeformMeshComponent has no ProceduralMeshComponent, cannot rebuild"));
		return;
	}

	// Clear the geometry
	ProceduralMeshComponent->ClearAllMeshSections();

	// These are the structures which will hold each mesh section
	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> uvs;
	TArray<FProcMeshTangent> tangents;

	// Iterate over the mesh sections
	const int32 LOD = 0;
	const int32 numSections = StaticMesh->GetNumSections(LOD);
	for (int meshSectionIndex = 0; meshSectionIndex < numSections; ++meshSectionIndex) {
		UE_LOG(LogTemp, Log, TEXT("DeformMeshComponent rebuilding section %d"), meshSectionIndex);
		//  static void GetSectionFromStaticMesh(UStaticMesh* InMesh, int32 LODIndex, int32 SectionIndex, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals,
		// TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents);
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
			StaticMesh, LOD, meshSectionIndex,
			vertices, triangles, normals, uvs, tangents
		);
		UE_LOG(LogTemp, Log, TEXT("Found %d verts and %d triangles"), vertices.Num(), triangles.Num() / 3);
	}
}

