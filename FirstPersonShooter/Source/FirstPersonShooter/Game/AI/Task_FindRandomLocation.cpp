// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FirstPersonShooter/Game/AI/NPC_Controller.h"

UTask_FindRandomLocation::UTask_FindRandomLocation(FObjectInitializer const& objectInitializer)
{
    NodeName = "Find Random Location";
}

EBTNodeResult::Type UTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    if (const ANPC_Controller* controller = Cast<ANPC_Controller>(owner.GetAIOwner()))
    {
        if (const auto* npc = controller->GetPawn())
        {
            if (const auto* navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                const auto origin = npc->GetActorLocation();

                FNavLocation navlocation;
                if (navSystem->GetRandomPointInNavigableRadius(origin, mSearchRadius, navlocation))
                {
                    owner.GetBlackboardComponent()->SetValueAsVector(
                        GetSelectedBlackboardKey(),
                        navlocation.Location
                    );

                    FinishLatentTask(owner, EBTNodeResult::Succeeded);
                    return EBTNodeResult::Succeeded;
                }
            }
        }
    }

    return EBTNodeResult::Failed;
}
