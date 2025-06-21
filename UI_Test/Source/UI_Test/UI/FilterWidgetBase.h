// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Test/UI/Abstract/CheckBoxHandlerWidgetBase.h"
#include "FilterWidgetBase.generated.h"

/**
 *
 */
class UImage;

UCLASS()
class UI_TEST_API UFilterWidgetBase : public UCheckBoxHandlerWidgetBase
{
    GENERATED_BODY()

public:
    void SetData(class UTexture2D* icon, const FText& filterName);

protected:
    UPROPERTY(meta = (BindWidget))
    UImage* Icon;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* FilterName;
};
