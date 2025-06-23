// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UGridHandlerBase::AddItem(UWidget* item)
{
    if (!mMainLayer)
    {
        return;
    }

    /* Check if main widget has children and if they are UHorizontalBox type
       else create one */
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

    UHorizontalBoxSlot* hSlot = columnBox->AddChildToHorizontalBox(item);
    hSlot->SetPadding(ItemPadding);
}

void UGridHandlerBase::ClearItems()
{
    if (mMainLayer)
    {
        /* Remove and delete children 
           (I tried keeping them alive and reparenting when needed
            but that caused crashes because reparenting takes time to remove and add
            and a widget can't be reparent if it has a parent already)
            TODO: trying to improve this by fixing this limitation */
        mMainLayer->ClearChildren();
    }
}