// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionUtils.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUE5_API UFunctionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "VALUE- Exatly Anselmo", CompactNodeTitle = "ChangePos"))
	static void MovePosition(FVector StartPos, AActor* Actor, const FVector timePosition);
};
