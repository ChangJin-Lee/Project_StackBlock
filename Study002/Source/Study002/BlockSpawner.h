// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockSpawner.generated.h"

class ADynamicBlockActor;
class ABase_Player;


UCLASS()
class STUDY002_API ABlockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnBlockUpdateLocation(const FVector& NewBlockLocation);
	
	UPROPERTY(EditAnywhere, Category="Spawn Block")
	TSubclassOf<ADynamicBlockActor> BlockToSpawn;

	UPROPERTY(EditAnywhere, Category="Spawn Block")
	float SpawnInterval = 4.f;

	UFUNCTION()
	void StartSpawningBlock();
	UFUNCTION()
	void StopSpawningBlock();

private:
	UPROPERTY()
	ABase_Player* MyPlayer = nullptr;

	// SpawnBlock*
	bool StopSpawning = false;
	bool IsFloor = false;

	FVector StackedBlockLocation;
	FVector SpawnLocation;
	FTimerHandle TimerHandle;

	void SpawningBlocks();
	FVector GetRandomSpawnPosition();
};
