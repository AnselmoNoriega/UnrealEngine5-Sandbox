// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UI_Test/Interfaces/SyncTargetInterface.h"

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
    void SetMainLayer(UVerticalBox* layer) { mMainLayer = layer; }

    void AddCards();
    void AddItem(UWidget* item);
    void ClearItems();

protected:
#if WITH_EDITOR
    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    void SynchronizeProperties() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    int32 MaxColumns = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FMargin ItemPadding;

private:
    UVerticalBox* mMainLayer;
};
