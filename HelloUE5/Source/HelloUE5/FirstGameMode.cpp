// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include "Kismet/KismetSystemLibrary.h" // For logging in Unreal

FTimerHandle TimerHandle;

AFirstGameMode::AFirstGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
    DefaultPawnClass = DefaultPawnClassFinder.Class;
    PrimaryActorTick.bCanEverTick = true;
}

void AFirstGameMode::BeginPlay()
{
    // Call parent's Begin play
    Super::BeginPlay();
    UKismetSystemLibrary::PrintString(this, TEXT("BeginPlay has been called!"), true, true, FLinearColor::Blue, 2.0f);
    
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFirstGameMode::PrintMessage, 5.0f, false);
}

void AFirstGameMode::Tick(float dt)
{
    Super::Tick(dt);/*
    UKismetSystemLibrary::PrintString(this, TEXT("Update!"), true, true, FLinearColor::Blue, 2.0f);
    
    FString out = FString::Printf(TEXT("DeltaTime: %.2f"), dt);
    UKismetSystemLibrary::PrintString(this, out, true, true, FLinearColor::Green, 2.0f);*/
}

void AFirstGameMode::PrintMessage()
{
    UKismetSystemLibrary::PrintString(this, TEXT("Yes=========!"), true, true, FLinearColor::Blue, 2.0f);
}
