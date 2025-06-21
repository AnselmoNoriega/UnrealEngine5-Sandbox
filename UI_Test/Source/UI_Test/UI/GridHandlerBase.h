// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridHandlerBase.generated.h"

/**
 * 
 */
UCLASS()
class UI_TEST_API UGridHandlerBase : public UUserWidget
{
	GENERATED_BODY()

public:
    void AddItem(UWidget* item, int32 layerIndex);

    void ChangeLayer(int32 layerIndex);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    int32 MaxColumns = 5;

    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* MainGrid;

private:
    TMap<int32, TArray<class UUniformGridSlot*>> mLayeredItems;

    int32 mCurrentLayer = 0;
};
