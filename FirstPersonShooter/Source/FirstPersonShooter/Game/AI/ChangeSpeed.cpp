// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FirstPersonShooter/Game/AI/NPC.h"

UChangeSpeed::UChangeSpeed()
{
    bNotifyBecomeRelevant = true;
    NodeName = TEXT("Change Speed");
}

void UChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    Super::OnBecomeRelevant(owner, nodeMemory);

    if (const auto* controller = owner.GetAIOwner())
    {
        if (auto* npc = Cast<ANPC>(controller->GetPawn()))
        {
            npc->GetCharacterMovement()->MaxWalkSpeed = mSpeed;
        }
    }
}
