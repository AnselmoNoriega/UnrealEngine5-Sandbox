// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckBoxHandlerWidgetBase.h"

#include "Components/CheckBox.h"

void UCheckBoxHandlerWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    FScriptDelegate sd;
    sd.BindUFunction(this, "TriggerClickEvent");
    BackgroundCheckBox->OnCheckStateChanged.AddDynamic(this, &UCheckBoxHandlerWidgetBase::TriggerClickEvent);
}

void UCheckBoxHandlerWidgetBase::SetButtonSelected(bool selected)
{
    BackgroundCheckBox->SetIsChecked(false);
}

void UCheckBoxHandlerWidgetBase::TriggerClickEvent(bool isChecked)
{
    for (auto& stateChangeEvent : mStateChangeEvents)
    {
        stateChangeEvent(isChecked);
    }

    if (isChecked)
    {
        for (auto& clickEvent : mClickEvents)
        {
            clickEvent();
        }
    }
}