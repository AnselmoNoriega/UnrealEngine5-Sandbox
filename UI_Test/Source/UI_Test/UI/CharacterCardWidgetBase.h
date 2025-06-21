// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCardWidgetBase.generated.h"

/**
 * 
 */
class UImage;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
    SUPPORT     UMETA(DisplayName = "Support"),
    TANK        UMETA(DisplayName = "Tank"),
    BRAWLER     UMETA(DisplayName = "Brawler"),
    ASSASIN     UMETA(DisplayName = "Assasin")
};

USTRUCT(BlueprintType)
struct FCharacterTypeIcons
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
    ECharacterType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type")
    UTexture2D* TypeIcon;
};

UCLASS()
class UI_TEST_API UCharacterCardWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetButtonSelected(bool selected = true);

protected:
    UPROPERTY(meta = (BindWidget))
    class UCheckBox* BackgroundCheckBox;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CharacterName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CountTextBlock;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
    TArray<FCharacterTypeIcons> Icons;

private:
    bool mIsSelected = false;

    ECharacterType mCharacterType;
};
