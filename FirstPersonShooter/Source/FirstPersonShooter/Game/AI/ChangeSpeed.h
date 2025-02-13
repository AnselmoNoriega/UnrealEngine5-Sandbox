// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API UChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public: 
	UChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner, uint8* nodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="yes"))
	float mSpeed = 600.0f;
};
