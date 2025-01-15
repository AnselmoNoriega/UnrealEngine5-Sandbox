// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstGameMode.h"
#include "Kismet/KismetSystemLibrary.h" // For logging in Unreal

void AFirstGameMode::BeginPlay()
{
    // Call parent's Begin play
    Super::BeginPlay();
    UKismetSystemLibrary::PrintString(this, TEXT("BeginPlay has been called!"), true, true, FLinearColor::Green, 2.0f);
}
