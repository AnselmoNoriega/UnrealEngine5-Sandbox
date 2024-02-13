#include "MainController.h"
#include "MainCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AMainController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	playerCharacter = Cast<AMainCharacter>(aPawn);
	checkf(playerCharacter, TEXT("Wrong type of pawn."));

	mInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(mInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent."));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	checkf(InputMappingContent, TEXT("InputMappingContent was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContent, 0);

	if (ActionMove)
	{
		mInputComponent->BindAction
		(
			ActionMove, 
			ETriggerEvent::Triggered, 
			this,
			&AMainController::HandleMove
		);
	}

	if (ActionLook)
	{
		mInputComponent->BindAction
		(
			ActionLook, 
			ETriggerEvent::Triggered, 
			this,
			&AMainController::HandleLook
		);
	}

	if (ActionJump)
	{
		mInputComponent->BindAction
		(
			ActionJump, 
			ETriggerEvent::Triggered, 
			this,
			&AMainController::HandleJump
		);
	}
}

void AMainController::OnUnPossess()
{
	mInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void AMainController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AMainController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (playerCharacter)
	{
		playerCharacter->AddMovementInput(playerCharacter->GetActorForwardVector(), MovementVector.Y);
		playerCharacter->AddMovementInput(playerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void AMainController::HandleJump()
{
	if (playerCharacter)
	{
		playerCharacter->UnCrouch();
		playerCharacter->Jump();
	}
}