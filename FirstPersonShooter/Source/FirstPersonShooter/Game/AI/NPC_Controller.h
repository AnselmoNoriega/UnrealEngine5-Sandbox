// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Controller.generated.h"

/**
 *
 */
UCLASS()
class FIRSTPERSONSHOOTER_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()

public:
	explicit ANPC_Controller(FObjectInitializer const& objectInitializer);

	void OnPossess(APawn* pawn) override;
};
