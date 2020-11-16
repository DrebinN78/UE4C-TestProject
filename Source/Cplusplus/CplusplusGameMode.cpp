// Copyright Epic Games, Inc. All Rights Reserved.

#include "CplusplusGameMode.h"
#include "CplusplusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACplusplusGameMode::ACplusplusGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
