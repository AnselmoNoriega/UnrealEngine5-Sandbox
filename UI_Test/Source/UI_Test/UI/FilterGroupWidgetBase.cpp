// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterGroupWidgetBase.h"

#include "FilterWidgetBase.h"

#include "Components/GridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"
#include "Blueprint/WidgetTree.h"

#if WITH_EDITOR
void UFilterGroupWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    static const FName filtersPropertyName = GET_MEMBER_NAME_CHECKED(UFilterGroupWidgetBase, Filters);

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    /* Attempted to check the only edited index and update it, but
       I didn't find a clean way to do so. */
    if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName ||
        PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct() ||
        PropertyChangedEvent.Property->GetFName() == "ItemsPadding")
    {
        ResetFilterList();
    }
}
#endif

void UFilterGroupWidgetBase::ResetFilterList()
{
    if (!mFiltersBox)
    {
        GetPanels();
        if (!mFiltersBox)
        {
            UE_LOG(LogTemp, Warning, TEXT("FiltersBox not found in FilterGroup!"));
            return;
        }
    }

    mFiltersBox->ClearChildren();

    for (const FFilterWidgetData& data : Filters)
    {
        UFilterWidgetBase* filterWidget = CreateWidget<UFilterWidgetBase>(this, FilterClass);
        mFiltersBox->AddChildToVerticalBox(filterWidget);

        FMargin padding = filterWidget->GetPadding();
        padding.Bottom = ItemsPadding;
        filterWidget->SetPadding(padding);
        filterWidget->SetData(data.FilterIcon, data.FilterName);
    }
}

void UFilterGroupWidgetBase::GetPanels()
{
    mFiltersBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("FiltersBox")));
    mGlobalFilterCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("GlobalFilter")));
}

void UFilterGroupWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    ResetFilterList();
}

void UFilterGroupWidgetBase::SetFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index)
{
    if (!mFiltersBox)
    {
        GetPanels();
        if (!mFiltersBox)
        {
            UE_LOG(LogTemp, Warning, TEXT("FiltersBox not found in FilterGroup!"));
            return;
        }
    }

    if (mFiltersBox->GetChildrenCount() <= index)
    {
        UE_LOG(LogTemp, Warning, TEXT("Requested filter index %d is out of range. Total filters: %d"), index, mFiltersBox->GetChildrenCount());
        return;
    }

    UWidget* widget = mFiltersBox->GetChildAt(index);
    if (UFilterWidgetBase* filter = Cast<UFilterWidgetBase>(widget))
    {
        filter->AddClickEvent(clickEvent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("You shouldn't have items that are not relative to FilterWidgetBase inside FiltersBox!"));
    }
}