// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloUE5GameMode.h"
#include "HelloUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AHelloUE5GameMode::AHelloUE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
