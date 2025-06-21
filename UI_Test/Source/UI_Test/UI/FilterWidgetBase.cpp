// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterWidgetBase.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UFilterWidgetBase::SetData(UTexture2D* icon, const FText& filterName)
{
    Icon->Brush.SetResourceObject(icon);
    Icon->SynchronizeProperties();

    FilterName->SetText(filterName);
}
