// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstClass.generated.h"

UCLASS()
class TESTPROJECT_API AFirstClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing") int Value;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Testing") int Value;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
