// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterGroupWidgetBase.h"

#include "FilterWidgetBase.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"
#include "Blueprint/WidgetTree.h"

#if WITH_EDITOR
void UFilterGroupWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

}

void UFilterGroupWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!mGridPanel || !mFiltersBox || !mGlobalFilterCheckBox)
    {
        GetPanels();
    }

    static const FName filtersPropertyName = GET_MEMBER_NAME_CHECKED(UFilterGroupWidgetBase, Filters);

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    /* Attempted to check the only edited index and update it, but
       I didn't find a clean way to do so. */
    if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName ||
        PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct())
    {
        ResetFilterList();
    }
}
#endif

void UFilterGroupWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    ResetFilterList();
}

void UFilterGroupWidgetBase::ResetFilterList()
{
    if (!mFiltersBox)
    {
        GetPanels();
        if (!mFiltersBox)
        {
            return;
        }
    }

    mFiltersBox->ClearChildren();

    for (const FFilterWidgetData& data : Filters)
    {
        UFilterWidgetBase* filterWidget = CreateWidget<UFilterWidgetBase>(this, FilterClass);
        mFiltersBox->AddChildToVerticalBox(filterWidget);

        filterWidget->SetData(data.FilterIcon, data.FilterName);
    }
}

void UFilterGroupWidgetBase::GetPanels()
{
    mGridPanel = Cast<UGridPanel>(GetWidgetFromName(TEXT("GridPanel")));
    mFiltersBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("FiltersBox")));
    mGlobalFilterCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("GlobalFilter")));
}
