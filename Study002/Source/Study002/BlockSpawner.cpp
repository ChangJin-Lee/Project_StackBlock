// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockSpawner.h"

#include "Base_Player.h"
#include "DefaultGameInstance.h"
#include "DefaultPlayerController.h"
#include "DynamicBlockActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABlockSpawner::ABlockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlockSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	MyPlayer = Cast<ABase_Player>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnBlockUpdateLocation.AddDynamic(this, &ABlockSpawner::OnBlockUpdateLocation);
		DefaultGameInstance->CallOnGameOver.AddDynamic(this, &ABlockSpawner::StopSpawningBlock);
		DefaultGameInstance->CallOnSpawnBlock.AddDynamic(this, &ABlockSpawner::StartSpawningBlock);
	}

	StackedBlockLocation = GetActorLocation();
}

void ABlockSpawner::OnBlockUpdateLocation(const FVector& NewBlockLocation)
{
	StackedBlockLocation = NewBlockLocation;
	
}


void ABlockSpawner::SpawningBlocks()
{
	FVector TargetLoation = StackedBlockLocation;
	
	SpawnLocation = GetRandomSpawnPosition();
	
	ADynamicBlockActor* SpawnedBlock = GetWorld()->SpawnActor<ADynamicBlockActor>(BlockToSpawn, SpawnLocation, FRotator3d::ZeroRotator);
	
	if(ADynamicMeshActor* DynamicMeshActor = Cast<ADynamicMeshActor>(SpawnedBlock))
	{
		if(UBoxComponent* BoxComp = DynamicMeshActor->FindComponentByClass<UBoxComponent>())
		{
			FVector BoxExtent = BoxComp->GetScaledBoxExtent();
		
			if(ADefaultPlayerController* PlayerController = Cast<ADefaultPlayerController>(MyPlayer->GetController()))
			{
				float Stackedheight = BoxExtent.Z * 2.0f * PlayerController->GetStackedHeight();
				SpawnLocation.Z += Stackedheight + 200.f;
				TargetLoation.Z += Stackedheight + 200.f;

				
				UE_LOG(LogTemp, Warning, TEXT("Stacked Height %f"), Stackedheight);
				UE_LOG(LogTemp, Warning, TEXT("Set Spawn Location %s"), *SpawnLocation.ToString());
			}
		}
	}
	
	SpawnedBlock->SetTargetLocation(TargetLoation);
	SpawnedBlock->SetActorLocation(SpawnLocation);
	SpawnedBlock->InitialIzeBlock();
}

FVector ABlockSpawner::GetRandomSpawnPosition()
{
	float Angle = FMath::RandRange(0.0f, 2.0f * PI);
	float Radius = FMath::RandRange(1500, 3000);
	float Height = FMath::RandRange(200, 500);
	
	FVector RandomLocation = FVector(
		Radius * FMath::Cos(Angle),
		Radius * FMath::Sin(Angle),
		Height);

	return RandomLocation;
}


void ABlockSpawner::StartSpawningBlock()
{
	SpawningBlocks();
}

void ABlockSpawner::StopSpawningBlock()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
