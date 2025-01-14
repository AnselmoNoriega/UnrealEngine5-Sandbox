// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloUE5GameMode.h"
#include "HelloUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AHelloUE5GameMode::AHelloUE5GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
