// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicBlockActor.h"

#include "AI/NavigationModifier.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"

ADynamicBlockActor::ADynamicBlockActor()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DynamicMeshComponent);
}

// BoxCollision의 Scale에 따라서 매시의 크기가 바뀜
void ADynamicBlockActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UDynamicMesh* DynamicMesh =  DynamicMeshComponent->GetDynamicMesh();
	if(DynamicMesh)
	{
		DynamicMesh->Reset();

		FTransform T;
		FGeometryScriptPrimitiveOptions Options;
		FVector Dimension = BoxCollision->GetScaledBoxExtent();
		float DimensionX = Dimension.X * 2;
		float DimensionY = Dimension.Y * 2;
		float DimensionZ = Dimension.Z * 2;
		float TransformLocationZ = Dimension.Z * -1;
		T.SetLocation(FVector(0,0,TransformLocationZ));
		UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(DynamicMesh, Options, T, DimensionX, DimensionY, DimensionZ);
		DynamicMeshComponent->EnableComplexAsSimpleCollision();
	}
}

// 겹쳐진 영역의 좌표, 크기를 구하는 함수
void ADynamicBlockActor::SetOverlapExtentAndLocation(UBoxComponent* Box1, UBoxComponent* Box2)
{
    FVector Box1Location = Box1->GetComponentLocation();
    FVector Box1Extent = Box1->GetScaledBoxExtent();

    FVector Box2Location = Box2->GetComponentLocation();
    FVector Box2Extent = Box2->GetScaledBoxExtent();

    FVector Max1 = Box1Location + Box1Extent;
    FVector Min1 = Box1Location - Box1Extent;

    FVector Max2 = Box2Location + Box2Extent;
    FVector Min2 = Box2Location - Box2Extent;
	
	FVector OverlapMax = FVector(FMath::Min(Max1.X, Max2.X), FMath::Min(Max1.Y, Max2.Y), FMath::Min(Max1.Z, Max2.Z));
    FVector OverlapMin = FVector(FMath::Max(Min1.X, Min2.X), FMath::Max(Min1.Y, Min2.Y), FMath::Max(Min1.Z, Min2.Z));
	
	OverlapLocationVector = (OverlapMin + OverlapMax) / 2.0f;
	OverlapExtentVector = OverlapMax - OverlapMin;

	UE_LOG(LogTemp, Warning, TEXT("OverlapLocationVector :  %s"), *OverlapLocationVector.ToString());
	UE_LOG(LogTemp, Warning, TEXT("OverlapExtentVector :  %s"), *OverlapExtentVector.ToString());
}

// 겹친 영역 만큼 DynamicMesh를 만들고 Return하는 함수
UDynamicMesh* ADynamicBlockActor::GetOverlappedArea(UBoxComponent* TargetBoxComponent)
{
	UDynamicMesh* TargetMesh = nullptr;
	SetOverlapExtentAndLocation(BoxCollision, TargetBoxComponent);

	UDynamicMesh* DynamicMesh = DynamicMeshComponent->GetDynamicMesh();
	FTransform Transform = DynamicMeshComponent->GetComponentTransform();
	FVector BoxTransform = Transform.InverseTransformPosition(OverlapLocationVector);

	if(DynamicMesh)
	{
		UDynamicMesh* ComputeMesh = AllocateComputeMesh();
		if(ComputeMesh)
		{
			FTransform T;
			FGeometryScriptPrimitiveOptions Options;
			FVector LocalOverlapLocation = FVector(BoxTransform.X, BoxTransform.Y, BoxTransform.Z - OverlapExtentVector.Z /2 );
			T.SetLocation(LocalOverlapLocation);
			
			TargetMesh = UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(
				ComputeMesh,
				Options,
				T,
				OverlapExtentVector.X,
				OverlapExtentVector.Y,
				OverlapExtentVector.Z
				);
		}
	}

	return TargetMesh;
}