// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectFDGameMode.h"
#include "ProjectFDCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectFDGameMode::AProjectFDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
