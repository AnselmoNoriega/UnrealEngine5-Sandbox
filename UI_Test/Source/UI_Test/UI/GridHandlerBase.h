// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridHandlerBase.generated.h"

/**
 * 
 */
class UVerticalBox;

UCLASS()
class UI_TEST_API UGridHandlerBase : public UUserWidget
{
	GENERATED_BODY()

public:
    /* Set who the items parent is going to be */
    void SetMainLayer(UVerticalBox* layer) { mMainLayer = layer; }

    void AddItem(UWidget* item);
    void ClearItems();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    int32 MaxColumns = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FMargin ItemPadding;

private:
    UVerticalBox* mMainLayer;
};
