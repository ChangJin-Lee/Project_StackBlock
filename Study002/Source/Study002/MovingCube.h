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
	TArray <UCurveVector*> MovementCurve;
	
public:
	UFUNCTION(BlueprintCallable, Category="Moving Cube")
	void MovePosition(FVector Value);

	UFUNCTION(BlueprintCallable, Category="Moving Cube")
	void SetCurve(float index);	

	UPROPERTY(BlueprintReadWrite, Category="Moving Cube")
	bool IsCubeMove;

	UPROPERTY(EditAnywhere, Category="Moving Cube")
	bool IsLooping;

private:
	FOnTimelineVector TimelineCallback;
	FTimeline CurveTimeline;
	FVector InitialPosition;
	FVector TargetPosition;
	FVector2D TargetXY;
	FVector TargetDirection;

	float TimeElapsed = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	bool IsSetCurve;

	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	AActor* TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	float MoveRange = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	float EscapeSpeed = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	float LerpDuration = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	float HeightOffset = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moving Cube", meta=(AllowPrivateAccess = "true"))
	float DistanceToTargetLimit = 100.f;
};
