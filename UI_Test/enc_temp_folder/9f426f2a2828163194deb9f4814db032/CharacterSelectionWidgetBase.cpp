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
    {
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

    if (PropertyChangedEvent.Property->GetFName() == cardListPropertyName)
    {
        SetCardsInDeck();
    }
    else if (PropertyChangedEvent.Property->GetOwnerStruct() == FCharacterCardInfo::StaticStruct())
    {
        const FProperty* inProperty = PropertyChangedEvent.Property->PropertyLinkNext;

        if (inProperty && inProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, CharacterCards))
        {
            //UpdateCard(inProperty->);
        }
    }
    else if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName)
    {
        SetFilters();
    }
    else if (PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct())
    {
        SetFilters();
    }

    mShouldRebuildUI = false;

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UCharacterSelectionWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    if (mShouldRebuildUI)
    {
        SetFilters();
        SetCardsInDeck();
    }
    mShouldRebuildUI = true;
}

void UCharacterSelectionWidgetBase::SetFilters()
{
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
    mCardsHolded.Empty();
    for (auto& item : CharacterCards)
    {
        UCharacterCardWidgetBase* newCard = CreateWidget<UCharacterCardWidgetBase>(this, CardClass.Get());
        newCard->SetData(
            item.CharacterImage,
            item.CharacterName,
            item.CharacterCount,
            item.Type,
            item.isCardLocked
        );

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
    }

    OrderDeck();
}

void UCharacterSelectionWidgetBase::OrderDeck()
{
    if (!GridHandlerWidget)
    {
        return;
    }

    GridHandlerWidget->SetMainLayer(CardsVerticalBox);
    GridHandlerWidget->ClearItems();

    UCharacterCardWidgetBase* firstItemInList = nullptr;
    for (auto* card : mCardsHolded)
    {
        if (!mShowLockedItems && card->IsLocked())
        {
            continue;
        }

        if (mCurrentLayer == ECharacterType::ALL || card->GetType() == mCurrentLayer)
        {
            GridHandlerWidget->AddItem(card);

            if (!firstItemInList)
            {
                mSelectedCard = firstItemInList;
                mSelectedCard->SetButtonSelected();
                mSelectedCard->SetCardForegroundSelected();
            }
        }
    }

    if (!mCardsHolded.IsEmpty())
    {
        mSelectedCard = mCardsHolded[0];
        mSelectedCard->SetButtonSelected();
        mSelectedCard->SetCardForegroundSelected();
    }
}

void UCharacterSelectionWidgetBase::LockedCheckBoxChange(bool isChecked)
{
    mShowLockedItems = isChecked;
    SetCardsInDeck();
}
