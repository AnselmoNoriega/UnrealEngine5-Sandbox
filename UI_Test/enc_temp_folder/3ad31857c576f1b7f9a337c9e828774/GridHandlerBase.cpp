// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UGridHandlerBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();
}

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
    UVerticalBox* itemsInLayer = *mLayeredItems.Find(layerIndex);
    if (!itemsInLayer)
    {
        itemsInLayer = mLayeredItems.Add(layerIndex);
        itemsInLayer = NewObject<UVerticalBox>(this);
        RootCanvas->AddChild(itemsInLayer);

        UHorizontalBox* firstColumn = NewObject<UHorizontalBox>(this);
        itemsInLayer->AddChildToVerticalBox(firstColumn);
    }

    UWidget* columnWidget = itemsInLayer->GetChildAt(itemsInLayer->GetChildrenCount() - 1);
    UHorizontalBox* columnBox = Cast<UHorizontalBox>(columnWidget);
    if (columnBox)
    {
        if (columnBox->GetChildrenCount() >= MaxColumns)
        {
            columnBox = NewObject<UHorizontalBox>(this);
            itemsInLayer->AddChildToVerticalBox(columnBox);
        }
    }
    else
    {
        columnBox = NewObject<UHorizontalBox>(this);
        itemsInLayer->AddChildToVerticalBox(columnBox);
    }

    UHorizontalBoxSlot* hSlot = Cast<UHorizontalBoxSlot>(columnBox->AddChildToHorizontalBox(item));
    hSlot->SetPadding(ItemPadding);

    if (mCurrentLayer != layerIndex)
    {
        item->SetIsEnabled(false);
        item->SetRenderOpacity(0.0);
    }
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
    if (RootCanvas)
    {
        RootCanvas->ClearChildren();
    }
    
    mCurrentLayer = 0;
    mLayeredItems.Empty();
}

void UGridHandlerBase::ChangeLayer(int32 layerIndex)
{
    //for (auto* item : mLayeredItems[mCurrentLayer])
    {
        //item->Content->SetIsEnabled(false);
        //item->Content->SetRenderOpacity(0.0);
    }

    mCurrentLayer = layerIndex;
    //for (auto* item : mLayeredItems[mCurrentLayer])
    {
        //item->Content->SetIsEnabled(true);
        //item->Content->SetRenderOpacity(1.0);
    }
}
