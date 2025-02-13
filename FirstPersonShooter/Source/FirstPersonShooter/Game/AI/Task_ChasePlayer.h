// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UTask_ChasePlayer(FObjectInitializer const& objectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory) override;
};
