// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstGameMode.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class HELLOUE5_API AFirstGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    AFirstGameMode();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameModeChimichanga")
    TSubclassOf<APawn> PawnForClass;

    void BeginPlay() override;
    void Tick(float dt) override;

private:
    void PrintMessage();
};
