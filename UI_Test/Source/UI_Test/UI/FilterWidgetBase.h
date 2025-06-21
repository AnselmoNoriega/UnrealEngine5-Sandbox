// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterWidgetBase.generated.h"

/**
 *
 */
class UImage;

UCLASS()
class UI_TEST_API UFilterWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    void NativeConstruct();
    
    void SetData(class UTexture2D* icon, const FText& filterName);

    void SetButtonSelected(bool selected = true);
    void SetClickEvent(const std::function<void()>& clickEvent) { mClickEvent = clickEvent; };

private:
    void TriggerClickEvent();

protected:
    UPROPERTY(meta = (BindWidget))
    class UCheckBox* BackgroundCheckBox;

    UPROPERTY(meta = (BindWidget))
    UImage* Icon;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* FilterName;

private:
    std::function<void()> mClickEvent = []() {};
};
