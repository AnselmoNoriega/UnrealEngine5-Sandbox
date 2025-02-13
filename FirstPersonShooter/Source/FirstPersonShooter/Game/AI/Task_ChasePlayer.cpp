// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_ChasePlayer.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FirstPersonShooter/Game/AI/NPC_Controller.h"

UTask_ChasePlayer::UTask_ChasePlayer(FObjectInitializer const& objectInitializer)
{
    NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    if (ANPC_Controller* controller = Cast<ANPC_Controller>(owner.GetAIOwner()))
    {
        const auto playerLocation = owner.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

        UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerLocation);

        FinishLatentTask(owner, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
