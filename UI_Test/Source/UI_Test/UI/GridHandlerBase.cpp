// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#if WITH_EDITOR
void UGridHandlerBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
}
#endif

void UGridHandlerBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();
}

void UGridHandlerBase::AddCards()
{
}

void UGridHandlerBase::AddItem(UWidget* item)
{
    if (!mMainLayer)
    {
        return;
    }

    UWidget* columnWidget = mMainLayer->GetChildAt(mMainLayer->GetChildrenCount() - 1);
    UHorizontalBox* columnBox = Cast<UHorizontalBox>(columnWidget);
    if (columnBox)
    {
        if (columnBox->GetChildrenCount() >= MaxColumns)
        {
            columnBox = NewObject<UHorizontalBox>(this);
            mMainLayer->AddChildToVerticalBox(columnBox);
        }
    }
    else
    {
        columnBox = NewObject<UHorizontalBox>(this);
        mMainLayer->AddChildToVerticalBox(columnBox);
    }

    UHorizontalBoxSlot* hSlot = Cast<UHorizontalBoxSlot>(columnBox->AddChildToHorizontalBox(item));
    hSlot->SetPadding(ItemPadding);
}

void UGridHandlerBase::ClearItems()
{
    if (mMainLayer)
    {
        mMainLayer->ClearChildren();
    }
}