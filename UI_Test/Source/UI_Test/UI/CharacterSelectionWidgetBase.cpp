// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidgetBase.h"

#include "FilterGroupWidgetBase.h"
#include "GridHandlerBase.h"
#include "CharacterCardWidgetBase.h"

#include "Components/VerticalBox.h"
#include "Components/CheckBox.h"

void UCharacterSelectionWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    SetFilters();
    SetCardsInDeck();

    if (ShowLockedCheckBox)
    {// maybe put this on post edit too
        ShowLockedCheckBox->OnCheckStateChanged.AddDynamic(this, &UCharacterSelectionWidgetBase::LockedCheckBoxChange);
    }
}

#if WITH_EDITOR
void UCharacterSelectionWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    static const FName cardListPropertyName = GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, CharacterCards);
    static const FName filtersPropertyName = GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, Filters);

    if (!PropertyChangedEvent.Property)
    {
        Super::PostEditChangeProperty(PropertyChangedEvent);
        return;
    }

    /* Update or remake specific UI depending on which prperty changed */
    if (PropertyChangedEvent.Property->GetFName() == cardListPropertyName)
    {
        SetCardsInDeck();
    }
    else if (PropertyChangedEvent.Property->GetOwnerStruct() == FCharacterCardInfo::StaticStruct())
    {
        UpdateCardsInfo();
    }
    else if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName)
    {
        SetFilters();
    }
    else if (PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct())
    {
        SetFilters(); // Update not set and maybe make filter toggable in inspector
    }

    mShouldRebuildUI = false;

    /* At the end because this runs SynchronizeProperties which I 
       already did manually */
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UCharacterSelectionWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    /* Only update if saved, compile or none of the main UI properties got changed*/
    if (mShouldRebuildUI)
    {
        SetFilters();
        SetCardsInDeck();
    }
    mShouldRebuildUI = true;
}

void UCharacterSelectionWidgetBase::SetFilters()
{
    /* Add the filters based on array of data */
    CharactersFilterWidget->ClearFilters();
    int32 index = 0;
    for (auto& filter : Filters)
    {
        CharactersFilterWidget->AddFilter(filter.FilterIcon, filter.FilterName);

        ECharacterType newType = ECharacterType(index + 1);
        CharactersFilterWidget->AddFunctionEventToFilter([this, newType]()
            {
                mCurrentLayer = newType;
                SetCardsInDeck();
            }, index);

        ++index;
    }

    CharactersFilterWidget->InitFilterGroupLogic();
}

void UCharacterSelectionWidgetBase::SetCardsInDeck()
{
    if (!GridHandlerWidget)
    {
        return;
    }

    /* Clean Deck */
    GridHandlerWidget->SetMainLayer(CardsVerticalBox);
    GridHandlerWidget->ClearItems();
    mCardsHolded.Empty();

    /* Create and add only needed widgets */
    /* Note: I tried reusing them but I couldn't find a way to reparent without
       crashing the game */
    mSelectedCard = nullptr;
    for (auto& item : CharacterCards)
    {
        if (mCurrentLayer != ECharacterType::ALL && item.Type != mCurrentLayer)
        {
            continue;
        }
        else if (!mShowLockedItems && item.isCardLocked)
        {
            continue;
        }

        UCharacterCardWidgetBase* newCard = CreateWidget<UCharacterCardWidgetBase>(this, CardClass.Get());
        newCard->SetData(
            item.CharacterImage,
            item.CharacterName,
            item.CharacterCount,
            item.Type,
            item.isCardLocked
        );

        /* Set events so only one card is active and you can't uncheck 
           current selected card */
        newCard->AddClickEvent([this, newCard]() {
            if (newCard != mSelectedCard)
            {
                mSelectedCard->SetButtonSelected(false);
                mSelectedCard->SetCardForegroundSelected(false);
                mSelectedCard = newCard;
            }
            });
        newCard->AddStateChangeEvent([this, newCard](bool isChecked) {
            if (!isChecked && newCard == mSelectedCard)
            {
                mSelectedCard->SetButtonSelected();
            }
            });

        mCardsHolded.Add(newCard);
        GridHandlerWidget->AddItem(newCard);

        /* Set selected card if there's non selected */
        if (!mSelectedCard)
        {
            mSelectedCard = newCard;
            mSelectedCard->SetButtonSelected();
            mSelectedCard->SetCardForegroundSelected();
        }
    }
}

void UCharacterSelectionWidgetBase::UpdateCardsInfo()
{
    /* Only Update Deck if theres more data to be changed (mCardsHolded) than 
       data (CharacterCards) */
    if (CharacterCards.Num() > mCardsHolded.Num())
    {
        return;
    }

    for (int i = 0; i < CharacterCards.Num(); ++i)
    {
        mCardsHolded[i]->SetData(
            CharacterCards[i].CharacterImage,
            CharacterCards[i].CharacterName,
            CharacterCards[i].CharacterCount,
            CharacterCards[i].Type,
            CharacterCards[i].isCardLocked
        );
    }
}

void UCharacterSelectionWidgetBase::LockedCheckBoxChange(bool isChecked)
{
    /* Change filter and reset deck */
    mShowLockedItems = isChecked;
    SetCardsInDeck();
}
