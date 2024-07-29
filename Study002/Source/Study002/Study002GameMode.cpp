// Copyright Epic Games, Inc. All Rights Reserved.

#include "Study002GameMode.h"
#include "Study002Character.h"
#include "UObject/ConstructorHelpers.h"

AStudy002GameMode::AStudy002GameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}
