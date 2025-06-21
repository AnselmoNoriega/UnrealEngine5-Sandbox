// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGridHandlerBase.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UCardGridHandlerBase::AddItem(UWidget* item)
{
    int32 column = 0;
    int32 row = 0;

    if (mLastItem && mLastItem->Column >= MaxColumns - 1)
    {
        row = mLastItem->Row + 1;
    }
    else if (mLastItem)
    {
        column = mLastItem->Column + 1;
    }

    UUniformGridSlot* itemSlot = CardsGrid->AddChildToUniformGrid(item, column, row);
    mLastItem = itemSlot;
}
