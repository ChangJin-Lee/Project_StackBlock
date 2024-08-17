// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "DynamicBlockActor.generated.h"


class UTimelineComponent;
class ABlockSpawner;
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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InitialIzeBlock();
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
private:
	UFUNCTION()
	void OnBlockStacked(bool IsStacked) const;
	UFUNCTION()
	void OnBlockUpdateLocation(const FVector& NewBlockLocation) const;
	UFUNCTION()
	void OnDropBlock();
	
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

	void RemoveOverlappingArea();

	
	// UTimelineComponent* MoveBlockTimelineComponent;
	FTimeline Timeline;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* MoveBlockCurve;

	bool bIsBlockMoving;	
	bool bIsStacked;
	bool IsOverlapped = false;
	
	
	UFUNCTION()
	void HandleMoveProgress(float Value);

	UFUNCTION()
	void StopMovement();
	
	UFUNCTION()
	void HandleMoveFinished();

	UFUNCTION()
	void ChangeBlockDirection(const FVector& NewTarget);
	
	void SetTargetLocation(const FVector& Value) { TargetLocation = Value;};

private:
	FVector OverlapLocationVector;
	FVector OverlapExtentVector;

	FVector InitialLocation;
	FVector TargetLocation;
};
