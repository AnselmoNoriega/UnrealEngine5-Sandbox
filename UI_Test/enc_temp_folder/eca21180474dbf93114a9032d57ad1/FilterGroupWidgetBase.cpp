// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterGroupWidgetBase.h"

#include "FilterWidgetBase.h"

#include "Components/GridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"
#include "Blueprint/WidgetTree.h"

void UFilterGroupWidgetBase::NativeConstruct()
{
    if (mFilters.IsEmpty())
    {
        return;
    }

    mSelectedFilter = mFilters[0];
    mSelectedFilter->SetButtonSelected();

    for (UFilterWidgetBase* filter : mFilters)
    {
        filter->AddClickEvent([this, filter]() {
            mSelectedFilter->SetButtonSelected(false);
            mSelectedFilter = filter;
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

    UFilterWidgetBase* filterWidget = CreateWidget<UFilterWidgetBase>(this, FilterClass);
    FiltersBox->AddChildToVerticalBox(filterWidget);
    mFilters.Add(filterWidget);

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

    FiltersBox->ClearChildren();
    mFilters.Empty();
}

#if WITH_EDITOR
void UFilterGroupWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UFilterGroupWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();
}

void UFilterGroupWidgetBase::SetFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index)
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