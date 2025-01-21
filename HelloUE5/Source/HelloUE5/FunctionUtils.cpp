// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionUtils.h"

FVector UFunctionUtils::startPos;

void UFunctionUtils::MovePosition(AActor* Actor, const FVector timePosition)
{
    Actor->SetActorLocation(startPos + timePosition);
}

void UFunctionUtils::StartPosition(AActor* Actor)
{
    startPos = Actor->GetActorLocation();
}
