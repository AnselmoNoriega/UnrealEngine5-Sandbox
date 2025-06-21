// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHelperBase.h"

#include "Blueprint/UserWidget.h"

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

	mCharacterSelectWidget = CreateWidget<UUserWidget>(pc, CharacterSelectClass);

	mCharacterSelectWidget->AddToViewport();
}

// Called every frame
void ATestHelperBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

