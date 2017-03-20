// DeformMeshComponent, (c)2017 Paul Golds- released under MIT license.

#include "mesh_deformer.h"
#include "DeformMeshComponent.h"

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

	// Iterate over the mesh sections
	const int32 LOD = 0;
	const int32 numSections = StaticMesh->GetNumSections(LOD);
	for (int meshSectionIndex = 0; meshSectionIndex < numSections; ++meshSectionIndex) {
		UE_LOG(LogTemp, Log, TEXT("DeformMeshComponent rebuilding section %d"), meshSectionIndex);

	}
}