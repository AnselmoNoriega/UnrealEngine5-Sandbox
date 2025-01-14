// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloUE5PickUpComponent.h"

UHelloUE5PickUpComponent::UHelloUE5PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UHelloUE5PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UHelloUE5PickUpComponent::OnSphereBeginOverlap);
}

void UHelloUE5PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AHelloUE5Character* Character = Cast<AHelloUE5Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
