// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionUtils.h"

void UFunctionUtils::MovePosition(FVector startPos, AActor* actor, const FVector timePosition)
{
    actor->SetActorLocation(startPos + timePosition);
}
