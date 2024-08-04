// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
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

	virtual void BeginPlay() override;
	
	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
// Function
public:
	UPROPERTY(BlueprintReadWrite)
	FVector MaxAxis1;

	UPROPERTY(BlueprintReadWrite)
	FVector MinAxis1;

	UPROPERTY(BlueprintReadWrite)
	FVector MaxAxis2;

	UPROPERTY(BlueprintReadWrite)
	FVector MinAxis2;

	// Call from Blueprint
	UFUNCTION(BlueprintCallable)
	UDynamicMesh* GetOverlappedArea(UBoxComponent* TargetBoxComponent);

	void SetOverlapExtentAndLocation(UBoxComponent* Box1, UBoxComponent* Box2);

	// FTimerHandle TimerHandle;
	//
	//
	// UTimelineComponent* MoveBlockTimelineComponent;
	//
	// UPROPERTY()
	// FOnTimelineFloat MoveBlockCallback;
	//
	// UPROPERTY()
	// FOnTimelineEvent MoveBlockFinishedCallback;
	//
	// UPROPERTY(EditAnywhere)
	// UCurveFloat* MoveBlockCurve;
	//
	// UFUNCTION()
	// void HandleMoveProgress(float value);
	//
	// UFUNCTION()
	// void HandleMoveFinished();
	//
	// FVector InitialLocation;
	// FVector TargetLocation;

private:
	FVector OverlapLocationVector;
	FVector OverlapExtentVector;

	// bool IsOverlapped = false;
};
