// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidgetBase.h"

#include "FilterGroupWidgetBase.h"
#include "GridHandlerBase.h"
#include "CharacterCardWidgetBase.h"

void UCharacterSelectionWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    //CharactersFilterWidget->SetFunctionEventToFilter([]() {
        //
        //}, 0);

    //SetFilters();
    //SetCardsInDeck();
}

void UCharacterSelectionWidgetBase::SyncData_Implementation()
{
    SetCardsInDeck();
}

#if WITH_EDITOR
void UCharacterSelectionWidgetBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    static const FName cardListPropertyName = GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, CharacterCards);
    static const FName filtersPropertyName = GET_MEMBER_NAME_CHECKED(UCharacterSelectionWidgetBase, Filters);

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    if (PropertyChangedEvent.Property->GetFName() == cardListPropertyName ||
        PropertyChangedEvent.Property->GetOwnerStruct() == FCharacterCardInfo::StaticStruct())
    {
        SetCardsInDeck();
    }
    else if (PropertyChangedEvent.Property->GetFName() == filtersPropertyName ||
        PropertyChangedEvent.Property->GetOwnerStruct() == FFilterWidgetData::StaticStruct())
    {
        SetFilters();
    }
}
#endif

void UCharacterSelectionWidgetBase::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    SetFilters();
    SetCardsInDeck();
}

void UCharacterSelectionWidgetBase::SetFilters()
{
    CharactersFilterWidget->ClearFilters();
    for (auto& filter : Filters)
    {
        CharactersFilterWidget->AddFilter(filter.FilterIcon, filter.FilterName);
    }
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
