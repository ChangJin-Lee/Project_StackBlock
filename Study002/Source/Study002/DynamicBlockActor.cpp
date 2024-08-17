// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicBlockActor.h"
#include "DefaultGameInstance.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"
#include "Kismet/GameplayStatics.h"


ADynamicBlockActor::ADynamicBlockActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DynamicMeshComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADynamicBlockActor::OnOverlapBegin);

	Tags.Add("Block");
}

void ADynamicBlockActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);
}

void ADynamicBlockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Timeline.TickTimeline(DeltaTime);
}

void ADynamicBlockActor::InitialIzeBlock()
{
	InitialLocation = GetActorLocation();
	FVector NormalVector = TargetLocation - InitialLocation;
	NormalVector.Normalize();
	TargetLocation += NormalVector * 800;
	
	if(MoveBlockCurve)
	{
		FOnTimelineFloat MoveBlockFunction;
		MoveBlockFunction.BindUFunction(this, FName("HandleMoveProgress"));
		Timeline.AddInterpFloat(MoveBlockCurve, MoveBlockFunction);
		Timeline.SetLooping(false);

		FOnTimelineEvent EndMovementFunction;
		EndMovementFunction.BindUFunction(this, FName("HandleMoveFinished"));
		Timeline.SetTimelineFinishedFunc(EndMovementFunction);
		
		Timeline.PlayFromStart();
	}
	
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnDropBlock.AddDynamic(this, &ADynamicBlockActor::OnDropBlock);
	}	
}


void ADynamicBlockActor::OnDropBlock()
{
	StopMovement();
	
	// 블록을 자르기
	RemoveOverlappingArea();

	// 아래로 움직이기
	FVector NewTargetLocation = GetActorLocation();
	NewTargetLocation.Z = 0.f;
	
	ChangeBlockDirection(NewTargetLocation);
}


void ADynamicBlockActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!IsOverlapped)
	{
		if(OtherActor && OtherActor != this)
		{
			if(OtherActor->ActorHasTag("Wall"))
			{
				return;
			}
			
			if(OtherActor->ActorHasTag("Stackable"))
			{
				StopMovement();
				OtherActor->Tags.Remove("Stackable");
				OtherActor->Tags.Add("NonStackable");

				Tags.Remove("Block");
				Tags.Add("Stackable");
				
				OnBlockStacked(true);
				OnBlockUpdateLocation(GetActorLocation());

				if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
				{
					DefaultGameInstance->CallOnDropBlock.RemoveDynamic(this, &ADynamicBlockActor::OnDropBlock);
				}
				
				IsOverlapped = true;
			}
			else if(OtherActor->ActorHasTag("NonStackable"))
			{
				OnBlockStacked(false);
				Destroy();
			}
		}
	}
}

void ADynamicBlockActor::OnBlockStacked(const bool IsStacked) const
{
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnBlockStacked.Broadcast(IsStacked);
	}
}

void ADynamicBlockActor::OnBlockUpdateLocation(const FVector& NewBlockLocation) const
{
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnBlockUpdateLocation.Broadcast(NewBlockLocation);
	}	
}


void ADynamicBlockActor::HandleMoveProgress(const float Value)
{
	FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, Value);
	SetActorLocation(NewLocation);
}

void ADynamicBlockActor::StopMovement()
{
	Timeline.Stop();
}

void ADynamicBlockActor::HandleMoveFinished()
{
	OnBlockStacked(false);
	Destroy();
}

void ADynamicBlockActor::ChangeBlockDirection(const FVector& NewTarget)
{
	InitialLocation = GetActorLocation();
	TargetLocation = NewTarget;

	Timeline.PlayFromStart();
}


void ADynamicBlockActor::RemoveOverlappingArea()
{
	TArray<AActor*> OverlappingActors;

	BoxCollision->GetOverlappingActors(OverlappingActors);

	for(AActor* OverlappingActor: OverlappingActors)
	{
		if(OverlappingActor && OverlappingActor->ActorHasTag("Wall"))
		{
			UBoxComponent* TargetBoxComponent = Cast<UBoxComponent>(OverlappingActor->GetComponentByClass(UBoxComponent::StaticClass()));

			if(UDynamicMesh* OverlappedMesh = GetOverlappedArea(TargetBoxComponent))
			{
				DynamicMeshComponent->SetDynamicMesh(OverlappedMesh);
			}
			
			return;
		}
	}

	OnBlockStacked(false);
	Destroy();
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