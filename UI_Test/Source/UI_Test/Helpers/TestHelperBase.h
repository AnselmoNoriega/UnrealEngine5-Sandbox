// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestHelperBase.generated.h"

struct FInputActionValue;

class UCharacterSelectionWidgetBase;

UCLASS()
class UI_TEST_API ATestHelperBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestHelperBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void TogglCardScreen(const FInputActionValue& Value);

protected:
	// For the screen =========
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UCharacterSelectionWidgetBase> CharacterSelectClass;

	// For the inputs =========
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ToggleCardsMenu;

private:
	UCharacterSelectionWidgetBase* mCharacterSelectWidget;

	bool mIsMenuActive = false;
};
