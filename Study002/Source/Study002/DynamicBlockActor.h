// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "Components/BoxComponent.h"
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
	UBoxComponent* BoxCollision;

// Function
public:
	void SubstractBlock();

	UPROPERTY(BlueprintReadWrite)
	FVector MaxAxis1;

	UPROPERTY(BlueprintReadWrite)
	FVector MinAxis1;

	UPROPERTY(BlueprintReadWrite)
	FVector MaxAxis2;

	UPROPERTY(BlueprintReadWrite)
	FVector MinAxis2;
	
	UFUNCTION(BlueprintCallable)
	UDynamicMesh* GetOverlappedArea(UBoxComponent* TargetBoxComponent);
};
