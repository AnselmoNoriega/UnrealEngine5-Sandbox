// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCardWidgetBase.h"

#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

int32 UCharacterCardWidgetBase::sMaxCharacterCount{};

void UCharacterCardWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    mStateChangeEvents.Add([this](bool isChecked) 
        {
            UTexture2D* newForeground = isChecked ? ForegroundSelected : ForegroundDefault;
            Foreground->Brush.SetResourceObject(newForeground);
        });
}

void UCharacterCardWidgetBase::SetData(const FText& characterName, uint32 characterCount, ECharacterType type)
{
    CharacterName->SetText(characterName);

    FString characterCountText = FString::Printf(TEXT("%d/ %d"), characterCount, sMaxCharacterCount);
    CountTextBlock->SetText(FText::FromString(characterCountText));

    mCharacterType = type;
    CharacterTypeIcon->Brush.SetResourceObject(TypeIcons[type]);
}
