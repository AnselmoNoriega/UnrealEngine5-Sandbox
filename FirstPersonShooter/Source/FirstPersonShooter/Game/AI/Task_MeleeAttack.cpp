// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_MeleeAttack.h"

#include "FirstPersonShooter/Game/AI/AIHelper.h"

#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UTask_MeleeAttack::UTask_MeleeAttack()
{
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    auto const isOutOfRange = !owner.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (isOutOfRange)
    {
        FinishLatentTask(owner, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }

    auto const* const controller = owner.GetAIOwner();
    auto* const npc = Cast<ANPC>(controller->GetPawn());

    if (auto* const icombat = Cast<IAIHelper>(npc))
    {
        if (IsMontageFinished(npc))
        {
            icombat->Execute_MeleeAttack(npc);
        }
    }

    FinishLatentTask(owner, EBTNodeResult::Succeeded);
    return EBTNodeResult::Type();
}

bool UTask_MeleeAttack::IsMontageFinished(const ANPC* npc)
{
    return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
