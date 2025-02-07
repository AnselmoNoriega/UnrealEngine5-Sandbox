// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_FirstPersonGameMode.h"
#include "AI_FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_FirstPersonGameMode::AAI_FirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
