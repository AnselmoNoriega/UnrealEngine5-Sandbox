// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include "Kismet/KismetSystemLibrary.h" // For logging in Unreal

AFirstGameMode::AFirstGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
    DefaultPawnClass = DefaultPawnClassFinder.Class;
}

void AFirstGameMode::BeginPlay()
{
    // Call parent's Begin play
    Super::BeginPlay();
    UKismetSystemLibrary::PrintString(this, TEXT("BeginPlay has been called!"), true, true, FLinearColor::Green, 2.0f);
}
