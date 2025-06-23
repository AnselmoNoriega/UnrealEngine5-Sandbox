// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCardWidgetBase.h"

#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UCharacterCardWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    Foreground->Brush.SetResourceObject(mIsLocked ? ForegroundLockedDefault : ForegroundDefault);

    mClickEvents.Add([this]()
        {
            SetCardForegroundSelected();
        });
}

void UCharacterCardWidgetBase::SetData(
    UTexture2D* characterImage,
    const FText& characterName,
    uint32 characterCount,
    ECharacterType type,
    bool isLocked
)
{
    CharacterIcon->Brush.SetResourceObject(characterImage);

    CharacterName->SetText(characterName);

    FString characterCountText = FString::Printf(TEXT("%d/ %d"), characterCount, MaxCharacterCount);
    CountTextBlock->SetText(FText::FromString(characterCountText));

    mCharacterType = type;
    CharacterTypeIcon->Brush.SetResourceObject(TypeIcons[type]);

    mIsLocked = isLocked;
    Foreground->Brush.SetResourceObject(mIsLocked ? ForegroundLockedDefault : ForegroundDefault);
    SetRenderOpacity(isLocked ? OpacityForLockedItem : 1.0f);
}

void UCharacterCardWidgetBase::SetButtonSelected(bool selected)
{
    Super::SetButtonSelected(selected);

    //SetCardForegroundSelected(selected);
}

void UCharacterCardWidgetBase::SetCardForegroundSelected(bool selected)
{
    UTexture2D* newForeground{};
    if (selected)
    {
        newForeground = mIsLocked ? ForegroundLockedSelected : ForegroundSelected;
    }
    else
    {
        newForeground = mIsLocked ? ForegroundLockedDefault : ForegroundDefault;
    }

    Foreground->Brush.SetResourceObject(newForeground);
}
