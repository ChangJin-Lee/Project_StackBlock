// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Actor.h"

// Sets default values
ABase_Actor::ABase_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ABase_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

