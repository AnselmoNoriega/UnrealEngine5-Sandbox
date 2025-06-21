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
    void NativeConstruct();

    void SetButtonSelected(bool selected = true);
    void SetClickEvent(const std::function<void()>& clickEvent) { mClickEvent = clickEvent; };

private:
    UFUNCTION()
    void TriggerClickEvent(bool isChecked);

protected:
    UPROPERTY(meta = (BindWidget))
    class UCheckBox* BackgroundCheckBox;

    std::function<void()> mClickEvent = []() {};
};
