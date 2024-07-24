// Fill out your copyright notice in the Description page of Project Settings.
// 
// 그냥 테스트 용 주석입니다. 무시하세요.

#include "MovingCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveVector.h"

// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;
}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetActorLocation();
	IsSetCurve = false;
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsCubeMove && IsSetCurve)
	{
		CurveTimeline.TickTimeline(DeltaTime);
	}
}

void AMovingCube::SetCurve(float index)
{
	if(index > MovementCurve.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("No Curve!"));
		return;
	}
	
	if(!MovementCurve.IsEmpty())
	{
		TimelineCallback.BindDynamic(this, &AMovingCube::MovePosition);
		CurveTimeline.AddInterpVector(MovementCurve[index], TimelineCallback);
		CurveTimeline.SetLooping(true);
		CurveTimeline.PlayFromStart();

		IsSetCurve = true;
	}
}

void AMovingCube::MovePosition(FVector Value)
{
	if(!MovementCurve.IsEmpty())
	{
		FVector curPos = InitialPosition + Value * 100.f;
		SetActorLocation(curPos);
	}
}


