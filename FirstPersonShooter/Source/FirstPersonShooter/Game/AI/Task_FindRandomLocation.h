// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UTask_FindRandomLocation(FObjectInitializer const& objectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner, uint8* nodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	float mSearchRadius = 1500.0f;
};
