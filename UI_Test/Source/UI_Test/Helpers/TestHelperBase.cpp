// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHelperBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "UI_Test/UI/CharacterSelectionWidgetBase.h"

// Sets default values
ATestHelperBase::ATestHelperBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestHelperBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	pc->SetInputMode(FInputModeUIOnly());
	pc->bShowMouseCursor = true;

    // Set mapping context to open and close cards menu
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

    /* Set input events(not working since there is no player but just in case
       I'm leaving it */
    if (UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(InputComponent))
    {
        eic->BindAction(ToggleCardsMenu, ETriggerEvent::Triggered, this, &ATestHelperBase::TogglCardScreen);
    }

	mCharacterSelectWidget = CreateWidget<UCharacterSelectionWidgetBase>(pc, CharacterSelectClass);
	mCharacterSelectWidget->AddToViewport();

	mCharacterSelectWidget->EnableCardScreen();
    mIsMenuActive = true;
}

void ATestHelperBase::TogglCardScreen(const FInputActionValue& Value)
{
    APlayerController* pc = GetWorld()->GetFirstPlayerController();

    if (mIsMenuActive)
    {
        pc->SetInputMode(FInputModeGameOnly());
    }
    else
    {
        pc->SetInputMode(FInputModeUIOnly());
    }

    mIsMenuActive = !mIsMenuActive;
    mCharacterSelectWidget->EnableCardScreen(mIsMenuActive);
    pc->bShowMouseCursor = mIsMenuActive;
}
