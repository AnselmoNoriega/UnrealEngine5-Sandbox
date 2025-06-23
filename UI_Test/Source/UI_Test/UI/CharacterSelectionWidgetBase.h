// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UI_Test/Enums/CharacterType.h"

#include "CharacterSelectionWidgetBase.generated.h"

/**
 * 
 */
class UCharacterCardWidgetBase;

USTRUCT(BlueprintType)
struct FCharacterCardInfo
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    UTexture2D* CharacterImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    int32 CharacterCount{};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    ECharacterType Type{};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    bool isCardLocked = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FText CharacterName{};
};

USTRUCT(BlueprintType)
struct FFilterWidgetData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filter")
    UTexture2D* FilterIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filter")
    FText FilterName;
};

UCLASS()
class UI_TEST_API UCharacterSelectionWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

protected:
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void SynchronizeProperties() override;

private:
	void SetFilters();
	void SetCardsInDeck();
	void UpdateCardsInfo();

    UFUNCTION()
    void LockedCheckBoxChange(bool isChecked);

protected:
	UPROPERTY(meta = (BindWidget))
	class UFilterGroupWidgetBase* CharactersFilterWidget;

	UPROPERTY(meta = (BindWidget))
	class UGridHandlerBase* GridHandlerWidget;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox* ShowLockedCheckBox;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox* CardsVerticalBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
    TArray<FCharacterCardInfo> CharacterCards;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Values")
    TSubclassOf<UCharacterCardWidgetBase> CardClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
    TArray<FFilterWidgetData> Filters;

private:
    TArray<UCharacterCardWidgetBase*> mCardsHolded;

    ECharacterType mCurrentLayer = ECharacterType::ALL;
    UCharacterCardWidgetBase* mSelectedCard{};

    bool mShowLockedItems = true;

    bool mShouldRebuildUI = true;
};
