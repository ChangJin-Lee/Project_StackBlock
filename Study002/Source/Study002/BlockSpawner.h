// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockSpawner.generated.h"

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
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Spawn Block")
	TSubclassOf<AActor> BlockToSpawn;

	UPROPERTY(EditAnywhere, Category="Spawn Block")
	float SpawnInterval = 3.f;

	void StopSpawningBlock();

	void OnBlockStacked();
	
private:
	ABase_Player* MyPlayer;

	// SpawnBlock*
	bool StopSpawning;
	bool IsFloor;

	FVector SpawnLocation;
	FTimerHandle TimerHandle;
	
	void SpawningBlocks();
	FVector GetRandomSpawnPosition();
};
