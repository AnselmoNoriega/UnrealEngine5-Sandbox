// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Service_PlayerIsInRange.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UService_PlayerIsInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UService_PlayerIsInRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* nodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "yes"))
	float mMeleeRange = 2.5f;
};
