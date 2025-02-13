// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "FirstPersonShooter/Game/AI/NPC.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Task_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UTask_MeleeAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory) override;

private:
	bool IsMontageFinished(const ANPC* npc);
};
