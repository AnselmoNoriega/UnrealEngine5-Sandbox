// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidgetBase.h"

#include "FilterGroupWidgetBase.h"
#include "GridHandlerBase.h"
#include "CharacterCardWidgetBase.h"

void UCharacterSelectionWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCharacterSelectionWidgetBase::SyncData_Implementation()
{
    SetCardsInDeck();
}

#if WITH_EDITOR
void UCharacterSelectionWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    static const FName filtersPropertyName = GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, CharacterCards);

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    /* Attempted to check the only edited index and update it, but
       I didn't find a clean way to do so. */
    if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName ||
        PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct())
    {
        SetCardsInDeck();
    }
}
#endif

void UCharacterSelectionWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    SetCardsInDeck();
}

void UCharacterSelectionWidgetBase::SetCardsInDeck()
{
    mCardsHolded.Empty();
    for (auto& item : CharacterCards)
    {
        UCharacterCardWidgetBase* newCard = CreateWidget<UCharacterCardWidgetBase>(this, CardClass.Get());
        newCard->SetData(
            item.CharacterName,
            item.CharacterCount,
            item.Type,
            item.isCardLocked
        );
        mCardsHolded.Add(newCard);
    }

    if (!GridHandlerWidget)
    {
        return;
    }

    GridHandlerWidget->ClearItems();
    for (auto& card : mCardsHolded)
    {
        if (EnumHasAnyFlags(card->GetType(), mCurrentLayer))
        {
            GridHandlerWidget->AddItem(card);
        }
    }
}
