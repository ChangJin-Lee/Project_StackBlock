// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicBlockActor.h"

#include "AI/NavigationModifier.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"

ADynamicBlockActor::ADynamicBlockActor()
{
	
}

void ADynamicBlockActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UDynamicMesh* DynamicMesh =  DynamicMeshComponent->GetDynamicMesh();
	if(DynamicMesh)
	{
		DynamicMesh->Reset();

		FTransform T;
		FGeometryScriptPrimitiveOptions Options;
		UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(DynamicMesh, Options, T, 100, 100, 100);
	}
}

void ADynamicBlockActor::SubstractBlock()
{
	UDynamicMesh* AllocatedMesh = AllocateComputeMesh();

	if(AllocatedMesh)
	{
		FTransform T;
		T.SetLocation(FVector(20,20,50));
		FGeometryScriptPrimitiveOptions Options;
		UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(AllocatedMesh, Options, T, 100, 100, 100);
	}
	
	UDynamicMesh* DynamicMesh = DynamicMeshComponent->GetDynamicMesh();

	if(DynamicMesh)
	{
		FTransform T;
		T.SetLocation(FVector(20,20,50));
	}
}
