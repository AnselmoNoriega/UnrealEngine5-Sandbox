// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UTask_FindPlayerLocation::UTask_FindPlayerLocation(FObjectInitializer const& objectInitializer)
{
    NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    if (const auto* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        auto const playerLocation = player->GetActorLocation();
        if (mSearchRandom)
        {
            FNavLocation navLocation;
            if (const auto* navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                if (navSystem->GetRandomPointInNavigableRadius(playerLocation, mSearchRadius, navLocation))
                {
                    owner.GetBlackboardComponent()->SetValueAsVector(
                        GetSelectedBlackboardKey(),
                        navLocation.Location
                    );

                    FinishLatentTask(owner, EBTNodeResult::Succeeded);
                    return EBTNodeResult::Succeeded;
                }
            }
        }
        else
        {
            owner.GetBlackboardComponent()->SetValueAsVector(
                GetSelectedBlackboardKey(),
                playerLocation
            );

            FinishLatentTask(owner, EBTNodeResult::Succeeded);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
