// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Controller.h"
#include "FirstPersonShooter/Game/AI/NPC.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "FirstPersonShooter/FirstPersonShooterCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

ANPC_Controller::ANPC_Controller(const FObjectInitializer& objectInitializer)
{
    SetupPerceptionSystem();
}

void ANPC_Controller::OnPossess(APawn* pawn)
{
    Super::OnPossess(pawn);
    if (const ANPC* npc = Cast<ANPC>(pawn))
    {
        if (UBehaviorTree* tree = npc->GetBehaviorTree())
        {
            UBlackboardComponent* blackboard;
            UseBlackboard(tree->BlackboardAsset, blackboard);
            Blackboard = blackboard;
            RunBehaviorTree(tree);
        }
    }
}

void ANPC_Controller::SetupPerceptionSystem()
{
    mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

    if (mSightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
        mSightConfig->SightRadius = 500.0f;
        mSightConfig->LoseSightRadius = mSightConfig->SightRadius + 25.0f;
        mSightConfig->PeripheralVisionAngleDegrees = 90.0f;
        mSightConfig->SetMaxAge(5.0f);
        mSightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
        mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
        mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*mSightConfig->GetSenseImplementation());

        FScriptDelegate perceptionDelegate;
        perceptionDelegate.BindUFunction(this, FName("OnTargetDetected"));
        GetPerceptionComponent()->OnTargetPerceptionUpdated.Add(perceptionDelegate);
        GetPerceptionComponent()->ConfigureSense(*mSightConfig);
    }
}

void ANPC_Controller::OnTargetDetected(AActor* actor, const FAIStimulus stimulus)
{
    if (const auto* character = Cast<AFirstPersonShooterCharacter>(actor))
    {
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", stimulus.WasSuccessfullySensed());
    }
}
