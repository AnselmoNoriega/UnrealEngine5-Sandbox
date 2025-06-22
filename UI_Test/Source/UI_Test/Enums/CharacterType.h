// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterType.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
    NONE        = 0 UMETA(DisplayName = "NONE"),
    ALL         = 1 UMETA(DisplayName = "All"),
    SUPPORT     = 2 UMETA(DisplayName = "Support"),
    TANK        = 3 UMETA(DisplayName = "Tank"),
    BRAWLER     = 4 UMETA(DisplayName = "Brawler"),
    ASSASSIN    = 5 UMETA(DisplayName = "Assassin")
};
