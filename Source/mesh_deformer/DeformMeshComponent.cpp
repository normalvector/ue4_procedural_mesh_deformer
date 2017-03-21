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
void UDeformMeshComponent::Rebuild(bool createCollision) {
	UE_LOG(LogTemp, Log, TEXT("Rebuilding DMC"));
	UE_LOG(LogTemp, Log, TEXT("Running up to pre-loop"));

	
	// Check we have a PMC
	if (!ProceduralMeshComponent) {
		UE_LOG(LogTemp, Warning, TEXT("DeformMeshComponent has no ProceduralMeshComponent, cannot rebuild"));
		return;
	}

	// Check we have a static mesh
	if (!StaticMesh) {
		UE_LOG(LogTemp, Warning, TEXT("DeformMeshComponent has no StaticMesh, cannot rebuild"));
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
	TArray<FLinearColor> vertexColors;

	// Iterate over the mesh sections
	const int32 LOD = 0;
	const int32 numSections = StaticMesh->GetNumSections(LOD);
	UE_LOG(LogTemp, Log, TEXT("Found %d sections for LOD %d"), numSections, LOD);

	for (int meshSectionIndex = 0; meshSectionIndex < numSections; ++meshSectionIndex) {
		UE_LOG(LogTemp, Log, TEXT("DeformMeshComponent rebuilding section %d"), meshSectionIndex);

		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
			StaticMesh, LOD, meshSectionIndex,
			vertices, triangles, normals, uvs, tangents
		);
		UE_LOG(LogTemp, Log, TEXT("Found %d verts and %d triangles"), vertices.Num(), triangles.Num() / 3);

		// Load vertex colors with default values for as many vertices as needed
		vertexColors.Empty();
		vertexColors.InsertDefaulted(0, vertices.Num());

		// Create the PMC section with the StaticMesh's data.
		ProceduralMeshComponent->CreateMeshSection_LinearColor(LOD, vertices, triangles, normals, uvs, vertexColors, tangents, createCollision);
		
	}
}

// Get the mesh geometry
FMeshGeometry UDeformMeshComponent::GetStaticMeshGeometry(int32 LOD) {
	FMeshGeometry meshGeometry;

	const int32 numSections = StaticMesh->GetNumSections(LOD);
	UE_LOG(LogTemp, Log, TEXT("Found %d sections for LOD %d"), numSections, LOD);

	for (int meshSectionIndex = 0; meshSectionIndex < numSections; ++meshSectionIndex) {
		UE_LOG(LogTemp, Log, TEXT("DeformMeshComponent rebuilding section %d"), meshSectionIndex);
		// Create the geometry for the section
		FSectionGeometry sectionGeometry;

		// Copy the static mesh's geometry for the section to the struct.
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
			StaticMesh, LOD, meshSectionIndex,
			sectionGeometry.vertices, sectionGeometry.triangles,
			sectionGeometry.normals, sectionGeometry.uvs, sectionGeometry.tangents
		);
		UE_LOG(LogTemp, Log, TEXT("Found %d verts and %d triangles"), sectionGeometry.vertices.Num(), sectionGeometry.triangles.Num() / 3);

		// Load vertex colors with default values for as many vertices as needed
		sectionGeometry.vertexColors.InsertDefaulted(0, sectionGeometry.vertices.Num());

		// Add the finished struct to the mesh's section list
		meshGeometry.sections.Emplace(sectionGeometry);
	}

	return meshGeometry;
}