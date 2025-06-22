// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UGridHandlerBase::AddItemFromEditor()
{
    if (!TestItem)
    {
        UE_LOG(LogTemp, Warning, TEXT("TestItem is null."));
        return;
    }

    auto t = CreateWidget<>(this, TestItem.Get());
    AddItem(t, TestLayerIndex);
}

void UGridHandlerBase::ClearItemFromEditor()
{
    ClearItems();
}

void UGridHandlerBase::AddItem(UWidget* item, int32 layerIndex)
{
    if (mCurrentRow->GetChildrenCount() >= MaxColumns)
    {
        mCurrentRow = NewObject<UHorizontalBox>(this);
        MainGrid->AddChild(mCurrentRow);
    }

    UHorizontalBoxSlot* hSlot = Cast<UHorizontalBoxSlot>(mCurrentRow->AddChildToHorizontalBox(item));
    hSlot->SetPadding(ItemPadding);

    //========================================
    //mLayeredItems[layerIndex].Add(item);
    //
    //if (mCurrentLayer != layerIndex)
    //{
    //    item->SetIsEnabled(false);
    //    item->SetRenderOpacity(0.0);
    //}
}

void UGridHandlerBase::ClearLayer(int32 layerIndex)
{
    //if (TArray<UUniformGridSlot*>* items = mLayeredItems.Find(layerIndex))
    //{
    //    for (UUniformGridSlot* item : *items)
    //    {
    //        if (item)
    //        {
    //            item->ConditionalBeginDestroy();
    //        }
    //    }
    //
    //    items->Empty();
    //}
}

void UGridHandlerBase::ClearItems()
{
    MainGrid->ClearChildren();
    GetLastRow();
    mLayeredItems.Empty();
}

void UGridHandlerBase::ChangeLayer(int32 layerIndex)
{
    for (auto* item : mLayeredItems[mCurrentLayer])
    {
        //item->Content->SetIsEnabled(false);
        //item->Content->SetRenderOpacity(0.0);
    }

    mCurrentLayer = layerIndex;
    for (auto* item : mLayeredItems[mCurrentLayer])
    {
        //item->Content->SetIsEnabled(true);
        //item->Content->SetRenderOpacity(1.0);
    }
}

void UGridHandlerBase::GetLastRow()
{
    mCurrentRow = nullptr;
    
    int32 count = MainGrid->GetChildrenCount();
    if (count <= 0)
    {
        mCurrentRow = FirstRow;
        return;
    }

    for (int i = count - 1; i >= 0; --i)
    {
        if (UHorizontalBox* row = Cast<UHorizontalBox>(MainGrid->GetChildAt(i)))
        {
            mCurrentRow = row;
            break;
        }
    }
}
