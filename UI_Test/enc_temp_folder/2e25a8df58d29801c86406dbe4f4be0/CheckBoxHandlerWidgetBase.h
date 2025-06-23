// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckBoxHandlerWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UI_TEST_API UCheckBoxHandlerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
    void NativeConstruct() override;

    bool IsButtonSelected();
    void SetButtonSelected(bool selected = true);

    void AddClickEvent(const std::function<void()>& clickEvent) { mClickEvents.Add(clickEvent); };
    void RemoveClickEvent(int32 index) { mClickEvents.RemoveAt(index); };

    void AddStateChangeEvent(const std::function<void(bool)>& clickEvent) { mStateChangeEvents.Add(clickEvent); };
    void RemoveStateChangeEvent(int32 index) { mStateChangeEvents.RemoveAt(index); };

private:
    UFUNCTION()
    void TriggerClickEvent(bool isChecked);

protected:
    UPROPERTY(meta = (BindWidget))
    class UCheckBox* BackgroundCheckBox;

    TArray<std::function<void()>> mClickEvents;
    TArray<std::function<void(bool)>> mStateChangeEvents;
};
