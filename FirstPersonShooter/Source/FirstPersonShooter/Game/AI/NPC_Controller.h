// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionTypes.h"

#include "NPC_Controller.generated.h"

/**
 *
 */
UCLASS()
class FIRSTPERSONSHOOTER_API ANPC_Controller : public AAIController
{
    GENERATED_BODY()

public:
    explicit ANPC_Controller(const FObjectInitializer& objectInitializer);

protected:
    void OnPossess(APawn* pawn) override;

private:
    void SetupPerceptionSystem();

    UFUNCTION()
    void OnTargetDetected(AActor* actor, const FAIStimulus stimulus);

private:
    class UAISenseConfig_Sight* mSightConfig;
};
