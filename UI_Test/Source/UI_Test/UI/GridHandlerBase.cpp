// Fill out your copyright notice in the Description page of Project Settings.


#include "GridHandlerBase.h"

#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UGridHandlerBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
}

void UGridHandlerBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    if (SyncTarget)
    {
        SyncTarget->Execute_SyncData(SyncTarget.GetObject());
    }
}

void UGridHandlerBase::AddCards()
{
}

void UGridHandlerBase::AddItem(UWidget* item)
{
    if (!MainLayer)
    {
        return;
    }

    UWidget* columnWidget = MainLayer->GetChildAt(MainLayer->GetChildrenCount() - 1);
    UHorizontalBox* columnBox = Cast<UHorizontalBox>(columnWidget);
    if (columnBox)
    {
        if (columnBox->GetChildrenCount() >= MaxColumns)
        {
            columnBox = NewObject<UHorizontalBox>(this);
            MainLayer->AddChildToVerticalBox(columnBox);
        }
    }
    else
    {
        columnBox = NewObject<UHorizontalBox>(this);
        MainLayer->AddChildToVerticalBox(columnBox);
    }

    UHorizontalBoxSlot* hSlot = Cast<UHorizontalBoxSlot>(columnBox->AddChildToHorizontalBox(item));
    hSlot->SetPadding(ItemPadding);
}

void UGridHandlerBase::ClearItems()
{
    if (MainLayer)
    {
        MainLayer->ClearChildren();
    }
}

void UGridHandlerBase::AddItemFromEditor()
{
    if (!TestItem)
    {
        UE_LOG(LogTemp, Warning, TEXT("TestItem is null."));
        return;
    }

    auto t = CreateWidget<>(this, TestItem.Get());
    AddItem(t);
}

void UGridHandlerBase::ClearItemFromEditor()
{
    ClearItems();
}
