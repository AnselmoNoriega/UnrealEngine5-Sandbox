// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UGridHandlerBase::AddItem(UWidget* item, int32 layerIndex)
{
    int32 column = 0;
    int32 row = 0;

    UUniformGridSlot* lastItem = nullptr;
    if (const TArray<UUniformGridSlot*>* items = mLayeredItems.Find(layerIndex))
    {
        lastItem = items->IsEmpty() ? nullptr : items->Last();
    }
    else
    {
        mLayeredItems.Add(layerIndex);
    }

    if (lastItem && lastItem->Column >= MaxColumns - 1)
    {
        row = lastItem->Row + 1;
    }
    else if (lastItem)
    {
        column = lastItem->Column + 1;
        row = lastItem->Row;
    }

    UUniformGridSlot* itemSlot = MainGrid->AddChildToUniformGrid(item, row, column);
    itemSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
    itemSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

    mLayeredItems[layerIndex].Add(itemSlot);

    if (mCurrentLayer != layerIndex)
    {
        item->SetIsEnabled(false);
        item->SetRenderOpacity(0.0);
    }
}

void UGridHandlerBase::ClearLayer(int32 layerIndex)
{
    if (TArray<UUniformGridSlot*>* items = mLayeredItems.Find(layerIndex))
    {
        for (UUniformGridSlot* item : *items)
        {
            if (item)
            {
                item->ConditionalBeginDestroy();
            }
        }

        items->Empty();
    }
}

void UGridHandlerBase::ClearItems()
{
    MainGrid->ClearChildren();
    mLayeredItems.Empty();
}

void UGridHandlerBase::ChangeLayer(int32 layerIndex)
{
    for (auto* item : mLayeredItems[mCurrentLayer])
    {
        item->Content->SetIsEnabled(false);
        item->Content->SetRenderOpacity(0.0);
    }

    mCurrentLayer = layerIndex;
    for (auto* item : mLayeredItems[mCurrentLayer])
    {
        item->Content->SetIsEnabled(true);
        item->Content->SetRenderOpacity(1.0);
    }
}
