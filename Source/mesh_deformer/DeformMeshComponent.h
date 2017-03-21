// DeformMeshComponent, (c)2017 Paul Golds- released under MIT license.

#pragma once

#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"
#include "FMeshGeometry.h"
#include "FSectionGeometry.h"
#include "SelectionSetBPFunctionLibrary.h"
#include "DeformMeshComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MESH_DEFORMER_API UDeformMeshComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// The source mesh that we're deforming.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StaticMesh)
		UStaticMesh *StaticMesh;

	// The PMC that we're building
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = DeformMeshComponent)
		UProceduralMeshComponent *ProceduralMeshComponent;

	// Sets default values for this component's properties
	UDeformMeshComponent();

	// Rebuild the PMC
	UFUNCTION(BlueprintCallable, Category = DeformMeshComponent)
		void Rebuild(bool createCollision = false);

	// Pull out the geometry of the mesh so we're able to modify it
	UFUNCTION(BlueprintCallable, Category = DeformMeshComponent)
		FMeshGeometry GetStaticMeshGeometry(int32 LOD=0);

protected:
public:	
};
