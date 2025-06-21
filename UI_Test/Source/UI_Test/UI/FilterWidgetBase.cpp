// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterWidgetBase.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UFilterWidgetBase::SetData(UTexture2D* icon, const FText& filterName)
{
    Icon->Brush.SetResourceObject(icon);
    Icon->SynchronizeProperties();

    FilterName->SetText(filterName);
}

void UFilterWidgetBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (!bIsSelected)
        Background->SetBrushFromTexture(HoveredImage);
}

void UFilterWidgetBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    if (!bIsSelected)
        Background->SetBrushFromTexture(NormalImage);
}

FReply UFilterWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    bIsSelected = true;
    Background->SetBrushFromTexture(SelectedImage);

    // Inform parent that this one is selected (so others can deselect)
    //OnSelectedDelegate.ExecuteIfBound(this); // optional

    return FReply::Handled();
}
