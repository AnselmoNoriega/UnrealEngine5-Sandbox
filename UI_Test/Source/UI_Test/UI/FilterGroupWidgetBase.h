// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterGroupWidgetBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FFilterWidgetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filter")
	FText FilterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filter")
	UTexture2D* FilterIcon;
};

UCLASS()
class UI_TEST_API UFilterGroupWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index);

protected:
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void SynchronizeProperties() override;

private:
	void ResetFilterList();

	void GetPanels();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Filters")
	TArray<FFilterWidgetData> Filters;

	UPROPERTY(EditDefaultsOnly, Category = "Filters")
	TSubclassOf<class UFilterWidgetBase> FilterClass;

	UPROPERTY(EditAnywhere, Category = "Filters")
	float ItemsPadding;

private:
	class UVerticalBox* mFiltersBox;
	class UCheckBox* mGlobalFilterCheckBox;
};
