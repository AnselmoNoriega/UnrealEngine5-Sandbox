// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimMontage.h"
#include "FirstPersonShooter/Game/AI/AIHelper.h"

#include "BehaviorTree/BehaviorTree.h"

#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API ANPC : public ACharacter, public IAIHelper
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UBehaviorTree* GetBehaviorTree() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* mBehaviorTree;

	int MeleeAttack_Implementation() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAnimMontage* GetMontage() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void GetDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void IsDead();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* mMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float mHealth = 100.0f;
};
