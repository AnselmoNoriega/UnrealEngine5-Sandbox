// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCardWidgetBase.h"

#include "Components/Image.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UCharacterCardWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    Foreground->Brush.SetResourceObject(mIsLocked ? ForegroundLockedDefault : ForegroundDefault);

    mStateChangeEvents.Add([this](bool isChecked)
        {
            UTexture2D* newForeground{};
            if (isChecked)
            {
                newForeground = mIsLocked ? ForegroundLockedSelected : ForegroundSelected;
            }
            else
            {
                newForeground = mIsLocked ? ForegroundLockedDefault : ForegroundDefault;
            }

            Foreground->Brush.SetResourceObject(newForeground);
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
