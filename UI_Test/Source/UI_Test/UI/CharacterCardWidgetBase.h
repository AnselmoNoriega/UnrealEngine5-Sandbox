// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_Test/UI/Abstract/CheckBoxHandlerWidgetBase.h"
#include "CharacterCardWidgetBase.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;

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
class UI_TEST_API UCharacterCardWidgetBase : public UCheckBoxHandlerWidgetBase
{
	GENERATED_BODY()

public:
    void NativeConstruct() override;

    void SetData(const FText& characterName, uint32 characterCount, ECharacterType type);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* CharacterName;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CountTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* CharacterIcon;

    UPROPERTY(meta = (BindWidget))
    UImage* Foreground;

    UPROPERTY(meta = (BindWidget))
    UImage* CharacterTypeIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* ForegroundDefault;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UTexture2D* ForegroundSelected;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    TMap<ECharacterType, UTexture2D*> TypeIcons;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    int32 MaxCharacterCount = 12;

private:
    ECharacterType mCharacterType;

    static int32 sMaxCharacterCount;
};
