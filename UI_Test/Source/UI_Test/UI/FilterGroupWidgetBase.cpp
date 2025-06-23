// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterGroupWidgetBase.h"

#include "FilterWidgetBase.h"

#include "Components/VerticalBox.h"

void UFilterGroupWidgetBase::InitFilterGroupLogic(int32 setSelectedIndex)
{
    if (mFilters.IsEmpty())
    {
        return;
    }

    /* Set a selected filter and events so it can't be unselected
       or change selection when otherone is pressed */
    mSelectedFilter = mFilters[setSelectedIndex];
    mSelectedFilter->SetButtonSelected();
    // document whats happening && check cpp then add anim or anim first
    for (UFilterWidgetBase* filter : mFilters)
    {
        filter->AddClickEvent([this, filter]() {
            if (mSelectedFilter != filter)
            {
                mSelectedFilter->SetButtonSelected(false);
                mSelectedFilter = filter;
            }
            });
        filter->AddStateChangeEvent([this, filter](bool isChecked) {
            if (!isChecked && mSelectedFilter == filter)
            {
                mSelectedFilter->SetButtonSelected();
            }
            });
    }
}

void UFilterGroupWidgetBase::AddFilter(UTexture2D* icon, const FText& lable)
{
    if (!FiltersBox)
    {
        UE_LOG(LogTemp, Warning, TEXT("FiltersBox not found in FilterGroup!"));
        return;
    }

    /* Create and add Filter to the vertical box */
    UFilterWidgetBase* filterWidget = CreateWidget<UFilterWidgetBase>(this, FilterClass);
    FiltersBox->AddChildToVerticalBox(filterWidget);
    mFilters.Add(filterWidget);

    /* Set padding */
    FMargin padding = filterWidget->GetPadding();
    padding.Bottom = ItemsPadding;
    filterWidget->SetPadding(padding);
    filterWidget->SetData(icon, lable);
}

void UFilterGroupWidgetBase::ClearFilters()
{
    if (!FiltersBox)
    {
        UE_LOG(LogTemp, Warning, TEXT("FiltersBox not found in FilterGroup!"));
        return;
    }

    /* Clear children and references so it gets cleaned */
    FiltersBox->ClearChildren();
    mFilters.Empty();
}

void UFilterGroupWidgetBase::UpdateFilter(UTexture2D* icon, const FText& lable, int index)
{
    if (mFilters.Num() <= index)
    {
        UE_LOG(LogTemp, Warning, TEXT("Requested filter index %d is out of range. Total filters: %d"), index, FiltersBox->GetChildrenCount());
        return;
    }

    mFilters[index]->SetData(icon, lable);
}

void UFilterGroupWidgetBase::AddFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index)
{
    if (mFilters.Num() <= index)
    {
        UE_LOG(LogTemp, Warning, TEXT("Requested filter index %d is out of range. Total filters: %d"), index, FiltersBox->GetChildrenCount());
        return;
    }

    mFilters[index]->AddClickEvent(clickEvent);
}