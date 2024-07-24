// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "DynamicBlockActor.generated.h"

/**
 * 
 */
UCLASS()
class STUDY002_API ADynamicBlockActor : public ADynamicMeshActor
{
	GENERATED_BODY()

public:
	ADynamicBlockActor();
	
private:
	virtual void OnConstruction(const FTransform& Transform) override;

// Component
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CuttingMeshComponent;

// Function
public:
	void SubstractBlock();
};
