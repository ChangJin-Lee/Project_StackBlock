// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DefaultGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlockStacked, bool, IsStacked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlockUpdateLocation, const FVector&, NewLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropBlock);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnBlock);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);



/**
 * 
 */
UCLASS()
class STUDY002_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UPROPERTY()
	FOnBlockStacked CallOnBlockStacked;
	void OnBlockStacked(bool IsStacked) const;

	UPROPERTY()
	FOnBlockUpdateLocation CallOnBlockUpdateLocation;
	void OnBlockUpdateLocation(const FVector& NewLocation) const;

	UPROPERTY()
	FOnDropBlock CallOnDropBlock;
	void OnDropBlock() const;

	UPROPERTY()
	FOnSpawnBlock CallOnSpawnBlock;
	void OnSpawnBlock() const;
	
	UPROPERTY()
	FOnGameOver CallOnGameOver;
	void OnGameOver() const;
	
	int32 GetStageClearHeight() const { return StageClearHeight; }
	int32 GetAttemptCount() const { return AttemptCount; }
	
private:
	int32 StageClearHeight = 5;
	int32 AttemptCount = 5;
	
};
