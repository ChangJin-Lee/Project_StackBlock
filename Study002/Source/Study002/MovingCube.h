// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Actor.h"
#include "MovingCube.generated.h"

UCLASS()
class STUDY002_API AMovingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, Category="Moving Cube")
	UCurveVector* MovementCurve;

	FOnTimelineVector TimelineCallback;
	FTimeline CurveTimeline;
	FVector InitialPosition;

	UFUNCTION()
	void MovePosition(FVector Value);
};
