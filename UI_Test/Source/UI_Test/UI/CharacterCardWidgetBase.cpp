// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCardWidgetBase.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCharacterCardWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    Foreground->SetBrushResourceObject(mIsLocked ? ForegroundLockedDefault : ForegroundDefault);

    /* Change foreground when checked 
       could also uncheck it but since events don't run when SetButtonSelected
       is called i'll do that part manually */
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
    CharacterIcon->SetBrushResourceObject(characterImage);

    CharacterName->SetText(characterName);

    FString characterCountText = FString::Printf(TEXT("%d/ %d"), characterCount, MaxCharacterCount);
    CountTextBlock->SetText(FText::FromString(characterCountText));

    mCharacterType = type;
    CharacterTypeIcon->SetBrushResourceObject(TypeIcons[type]);

    mIsLocked = isLocked;
    Foreground->SetBrushResourceObject(mIsLocked ? ForegroundLockedDefault : ForegroundDefault);
    SetRenderOpacity(isLocked ? OpacityForLockedItem : 1.0f);
}

void UCharacterCardWidgetBase::SetCardForegroundSelected(bool selected)
{
    /* Change foreground based on lock and selected state */
    UTexture2D* newForeground{};
    if (selected)
    {
        newForeground = mIsLocked ? ForegroundLockedSelected : ForegroundSelected;
    }
    else
    {
        newForeground = mIsLocked ? ForegroundLockedDefault : ForegroundDefault;
    }

    Foreground->SetBrushResourceObject(newForeground);
}
