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

    if (lastItem && lastItem->Column >= MaxColumns - 1)
    {
        row = lastItem->Row + 1;
    }
    else if (lastItem)
    {
        column = lastItem->Column + 1;
    }

    UUniformGridSlot* itemSlot = MainGrid->AddChildToUniformGrid(item, column, row);
    mLayeredItems[layerIndex].Add(itemSlot);

    if (mCurrentLayer != layerIndex)
    {
        item->SetIsEnabled(false);
        item->SetRenderOpacity(0.0);
    }
}

void UGridHandlerBase::ChangeLayer(int32 layerIndex)
{
    //TODO
}
