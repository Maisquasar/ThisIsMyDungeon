// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThisIsMyDungeonGameMode.h"
#include "ThisIsMyDungeonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThisIsMyDungeonGameMode::AThisIsMyDungeonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
