// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstGameMode.generated.h"

/**
 *
 */
UCLASS()
class HELLOUE5_API AFirstGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    AFirstGameMode();

    void BeginPlay() override;
};
