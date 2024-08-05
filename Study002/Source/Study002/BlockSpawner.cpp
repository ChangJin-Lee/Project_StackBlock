// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockSpawner.h"

#include "Base_Player.h"
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
	MyPlayer->BlockSpawner = this;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABlockSpawner::SpawningBlocks, SpawnInterval, true);
}

void ABlockSpawner::SpawningBlocks()
{
	SpawnLocation = GetRandomSpawnPosition();
	
	if(UBoxComponent* BoxComp = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass())))
	{
		FVector BoxExtent = BoxComp->GetScaledBoxExtent();
		SpawnLocation.Z += BoxExtent.Z * 2.0f * MyPlayer->StackedHeight;
	}
	
	if(BlockToSpawn != nullptr)
	{
		AActor* SpawnedBlock = GetWorld()->SpawnActor<AActor>(BlockToSpawn, SpawnLocation, FRotator3d::ZeroRotator);
	}
}

FVector ABlockSpawner::GetRandomSpawnPosition()
{
	float Angle = FMath::RandRange(0.0f, 2.0f * PI);
	float Radius = FMath::RandRange(1500, 3000);
	float Height = FMath::RandRange(500, 800);
	
	FVector RandomLocation = FVector(
		Radius * FMath::Cos(Angle),
		Radius * FMath::Sin(Angle),
		Height);

	return RandomLocation;
}

// 블록을 그만 생성할때 호출
void ABlockSpawner::StopSpawningBlock()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	UE_LOG(LogTemp, Display, TEXT("Stop Spawn Block!"));
}

