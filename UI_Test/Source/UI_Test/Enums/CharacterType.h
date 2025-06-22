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
    SUPPORT     UMETA(DisplayName = "Support"),
    TANK        UMETA(DisplayName = "Tank"),
    BRAWLER     UMETA(DisplayName = "Brawler"),
    ASSASIN     UMETA(DisplayName = "Assasin")
};
