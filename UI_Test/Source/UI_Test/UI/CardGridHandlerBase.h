// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardGridHandlerBase.generated.h"

/**
 *
 */
UCLASS()
class UI_TEST_API UCardGridHandlerBase : public UUserWidget
{
    GENERATED_BODY()

public:
    void AddItem(UWidget* item);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    int32 MaxColumns = 5;

    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* CardsGrid;

private:
    class UUniformGridSlot* mLastItem{};
};
