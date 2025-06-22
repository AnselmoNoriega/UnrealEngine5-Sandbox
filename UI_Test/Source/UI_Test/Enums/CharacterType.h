// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterType.generated.h"

/**
 * 
 */

UENUM(BlueprintType, meta = (Bitflags))
enum class ECharacterType : uint8
{
    NONE        = 0 << 0 UMETA(DisplayName = "NONE"),
    ALL         = 0xFF   UMETA(DisplayName = "All"),
    SUPPORT     = 1 << 0 UMETA(DisplayName = "Support"),
    TANK        = 1 << 1 UMETA(DisplayName = "Tank"),
    BRAWLER     = 1 << 2 UMETA(DisplayName = "Brawler"),
    ASSASSIN     = 1 << 3 UMETA(DisplayName = "Assassin")
};
ENUM_CLASS_FLAGS(ECharacterType)
