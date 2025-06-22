// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UI_Test/Enums/CharacterType.h"

#include "CharacterSelectionWidgetBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterCardInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FText CharacterName{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 CharacterCount{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType Type{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool isCardLocked = false;
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
	void SetCardsInDeck();

protected:
	UPROPERTY(meta = (BindWidget))
	class UFilterGroupWidgetBase* CharactersFilterWidget;

	UPROPERTY(meta = (BindWidget))
	class UGridHandlerBase* GridHandlerWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Values")
	TSubclassOf<class UCharacterCardWidgetBase> CardClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Values")
	TArray<FCharacterCardInfo> CharacterCards;
};
