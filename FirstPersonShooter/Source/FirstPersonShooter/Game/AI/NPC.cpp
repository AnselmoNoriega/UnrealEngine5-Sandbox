// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return mBehaviorTree;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

}

int ANPC::MeleeAttack_Implementation()
{
	if (mMontage)
	{
		PlayAnimMontage(mMontage);
	}

	return 0;
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAnimMontage* ANPC::GetMontage() const
{
	return mMontage;
}

void ANPC::GetDamage(float DamageAmount)
{
	mHealth -= DamageAmount;
}

void ANPC::IsDead()
{
	if (mHealth <= 0.0f)
	{
		Destroy();
	}
}

