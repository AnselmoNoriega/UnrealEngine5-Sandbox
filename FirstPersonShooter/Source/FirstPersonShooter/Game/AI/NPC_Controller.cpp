// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Controller.h"
#include "FirstPersonShooter/Game/AI/NPC.h"

ANPC_Controller::ANPC_Controller(FObjectInitializer const& objectInitializer)
{
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
