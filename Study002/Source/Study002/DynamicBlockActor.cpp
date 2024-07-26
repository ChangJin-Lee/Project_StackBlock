// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicBlockActor.h"

#include "AI/NavigationModifier.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"

ADynamicBlockActor::ADynamicBlockActor()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DynamicMeshComponent);
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
		float DimensionX = BoxCollision->GetScaledBoxExtent().X * 2;
		float DimensionY = BoxCollision->GetScaledBoxExtent().Y * 2;
		float DimensionZ = BoxCollision->GetScaledBoxExtent().Z * 2;
		float TransformLocationZ = BoxCollision->GetScaledBoxExtent().Z * -1;
		T.SetLocation(FVector(0,0,TransformLocationZ));
		UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(DynamicMesh, Options, T, DimensionX, DimensionY, DimensionZ);
		DynamicMeshComponent->EnableComplexAsSimpleCollision();
	}
}

UDynamicMesh* ADynamicBlockActor::GetOverlappedArea(UBoxComponent* TargetBoxComponent)
{
	FVector Location = BoxCollision->GetComponentLocation();
	FVector Extent = BoxCollision->GetScaledBoxExtent();
	UDynamicMesh* TargetMesh = nullptr;
	MaxAxis1 = Location + Extent;
	MinAxis1 = Location - Extent;

	FVector TargetLocation = TargetBoxComponent->GetComponentLocation();
	FVector TargetExtent = TargetBoxComponent->GetScaledBoxExtent();
	
	MaxAxis2 = TargetLocation + TargetExtent;
	MinAxis2 = TargetLocation - TargetExtent;

	FVector MaxPoint = FVector(
			FMath::Min(MaxAxis1.X, MaxAxis2.X),
			FMath::Min(MaxAxis1.Y, MaxAxis2.Y),
			FMath::Min(MaxAxis1.Z, MaxAxis2.Z)
			);
	
	FVector MinPoint = FVector(
		FMath::Max(MinAxis1.X, MinAxis2.X),
		FMath::Max(MinAxis1.Y, MinAxis2.Y),
		FMath::Max(MinAxis1.Z, MinAxis2.Z)
		);

	FVector Dimension = FVector(MaxPoint.X - MinPoint.X,MaxPoint.Y - MinPoint.Y,MaxPoint.Z - MinPoint.Z);
	FVector TLocation = FVector((MaxPoint.X + MinPoint.X)/2,(MaxPoint.Y + MinPoint.Y)/2,(MaxPoint.Z + MinPoint.Z)/2);

	UDynamicMesh* DynamicMesh = DynamicMeshComponent->GetDynamicMesh();
	FTransform Transform = DynamicMeshComponent->GetComponentTransform();
	FVector BoxTransform = Transform.InverseTransformPosition(TLocation);
	
	UE_LOG(LogTemp, Warning, TEXT("Dimension Location: %s"), *Dimension.ToString());
	UE_LOG(LogTemp, Warning, TEXT("BoxTransform Location: %s"), *BoxTransform.ToString());
	
	if(DynamicMesh)
	{
		UDynamicMesh* ComputeMesh = AllocateComputeMesh();
		if(ComputeMesh)
		{
			FTransform T;
			FGeometryScriptPrimitiveOptions Options;
			T.SetLocation(FVector(BoxTransform.X, BoxTransform.Y, BoxTransform.Z - Dimension.Z /2 ));
			TargetMesh = UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(
				DynamicMesh,
				Options,
				T,
				Dimension.X,
				Dimension.Y,
				Dimension.Z
				);
		}
	}

	return TargetMesh;
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
