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
    void SetData(class UTexture2D* icon, const FText& filterName);

    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* NormalImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* HoveredImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* SelectedImage;

    UPROPERTY(meta = (BindWidget))
    UImage* Background;

    UPROPERTY(meta = (BindWidget))
    UImage* Icon;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* FilterName;

private:
    bool bIsSelected = false;
};
