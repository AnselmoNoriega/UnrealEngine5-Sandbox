// Fill out your copyright notice in the Description page of Project Settings.


#include "Service_PlayerIsInRange.h"

#include "FirstPersonShooter/Game/AI/NPC_Controller.h"
#include "FirstPersonShooter/Game/AI/NPC.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include"Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UService_PlayerIsInRange::UService_PlayerIsInRange()
{
    bNotifyBecomeRelevant = true;
    NodeName = TEXT("Is In Melee Range");
}

void UService_PlayerIsInRange::OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* nodeMemory)
{
    const auto* const controller = Cast<ANPC_Controller>(owner.GetAIOwner());
    const auto* const npc = Cast<ANPC>(controller->GetPawn());

    const auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    owner.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), npc->GetDistanceTo(player) <= mMeleeRange);
}
