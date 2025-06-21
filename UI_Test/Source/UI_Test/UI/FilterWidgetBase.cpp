// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterWidgetBase.h"

#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UFilterWidgetBase::NativeConstruct()
{
    FScriptDelegate sd;
    sd.BindUFunction(this, "TriggerClickEvent");
    BackgroundCheckBox->OnCheckStateChanged.Add(sd); 

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hello, screen!"));
}

void UFilterWidgetBase::SetData(UTexture2D* icon, const FText& filterName)
{
    Icon->Brush.SetResourceObject(icon);
    Icon->SynchronizeProperties();

    FilterName->SetText(filterName);
}

void UFilterWidgetBase::SetButtonSelected(bool selected)
{
}

void UFilterWidgetBase::TriggerClickEvent()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hello, screen!"));
}
