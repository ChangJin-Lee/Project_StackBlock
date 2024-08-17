// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "BlockSpawner.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CoreMinimal.h"
#include "DefaultGameInstance.h"
#include "DefaultPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABase_Player::ABase_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = InitialLength = 1200.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SetWorldRotation(FRotator(-10.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	if (UCharacterMovementComponent* MyCharacterMovement = GetCharacterMovement())
	{
		// 이동 모드를 Flying으로 설정
		MyCharacterMovement->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
		MyCharacterMovement->MovementMode = EMovementMode::MOVE_Flying; // 현재 이동 모드도 Flying으로 설정
		MyCharacterMovement->MaxFlySpeed = 6000;
		MyCharacterMovement->MaxAcceleration = 10000;
		MyCharacterMovement->BrakingFriction = 200;
	}
}

// Called when the game starts or when spawned
void ABase_Player::BeginPlay()
{
	Super::BeginPlay();
	
	InitialHeight = GetActorLocation().Z;
}

// Called to bind functionality to input
void ABase_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &ABase_Player::MoveCamera);
		EnhancedInputComponent->BindAction(DropBlockAction, ETriggerEvent::Triggered, this, &ABase_Player::DropBlock);
	}
}

void ABase_Player::MoveCamera(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(InputVector.X);
		
		float CurrentHeight = GetActorLocation().Z;
		if(!(InitialHeight > CurrentHeight && InputVector.Y < 0))
		{
			AddMovementInput(FVector::UpVector, InputVector.Y);
		}
	}
}


void ABase_Player::DropBlock()
{
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->OnDropBlock();
	}
}


