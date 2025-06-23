// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterGroupWidgetBase.h"

#include "FilterWidgetBase.h"

#include "Components/VerticalBox.h"

void UFilterGroupWidgetBase::InitFilterGroupLogic()
{
    if (mFilters.IsEmpty())
    {
        return;
    }

    /* Set a selected filter and events so it can't be unselected
       or change selection when otherone is pressed */
    mSelectedFilter = mFilters[0];
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

void UFilterGroupWidgetBase::AddFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index)
{
    if (!FiltersBox)
    {
        UE_LOG(LogTemp, Warning, TEXT("FiltersBox not found in FilterGroup!"));
        return;
    }

    if (FiltersBox->GetChildrenCount() <= index)
    {
        UE_LOG(LogTemp, Warning, TEXT("Requested filter index %d is out of range. Total filters: %d"), index, FiltersBox->GetChildrenCount());
        return;
    }

    /* Add Event after checking the Filter exists */
    UWidget* widget = FiltersBox->GetChildAt(index);
    if (UFilterWidgetBase* filter = Cast<UFilterWidgetBase>(widget))
    {
        filter->AddClickEvent(clickEvent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You shouldn't have items that are not relative to FilterWidgetBase inside FiltersBox!"));
    }
}