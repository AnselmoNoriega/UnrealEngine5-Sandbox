// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPlayerBase.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class UCharacterSelectionWidgetBase;

UCLASS()
class UI_TEST_API ATestPlayerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyControllerChanged() override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void TogglCardScreen(const FInputActionValue& Value);

protected:
	// For the inputs =========
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ToggleCardsMenu;

	// For the screen =========
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCharacterSelectionWidgetBase> CharacterSelectClass;

private:
	UCharacterSelectionWidgetBase* mCharacterSelectWidget;

	bool mIsMenuActive = false;
};
