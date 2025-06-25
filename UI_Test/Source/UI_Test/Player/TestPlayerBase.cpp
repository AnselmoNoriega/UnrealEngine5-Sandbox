// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "UI_Test/UI/CharacterSelectionWidgetBase.h"

// Sets default values
ATestPlayerBase::ATestPlayerBase()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestPlayerBase::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* pc = GetWorld()->GetFirstPlayerController();
    EnableInput(pc);
    pc->SetInputMode(FInputModeGameAndUI());
    pc->bShowMouseCursor = true;

    mCharacterSelectWidget = CreateWidget<UCharacterSelectionWidgetBase>(pc, CharacterSelectClass);
    mCharacterSelectWidget->AddToViewport();

    mCharacterSelectWidget->EnableCardScreen();
    mIsMenuActive = true;
}

void ATestPlayerBase::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    // Add Input Mapping Context
    if (APlayerController* playerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
        {
            subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

// Called to bind functionality to input
void ATestPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (!EIC)
    {
        return;
    }

    EIC->BindAction(ToggleCardsMenu, ETriggerEvent::Started, this, &ATestPlayerBase::TogglCardScreen);
}

void ATestPlayerBase::TogglCardScreen(const FInputActionValue& Value)
{
    if (!mCharacterSelectWidget->EnableCardScreen(!mIsMenuActive))
    {
        return;
    }

    mIsMenuActive = !mIsMenuActive;
}

