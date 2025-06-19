// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseCharacterFilterWidget.generated.h"

/**
 *
 */
UCLASS()
class UI_TEST_API UBaseCharacterFilterWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetSelected(bool bIsSelected = true);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* NormalImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* HoveredImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* SelectedImage;

private:
    void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
