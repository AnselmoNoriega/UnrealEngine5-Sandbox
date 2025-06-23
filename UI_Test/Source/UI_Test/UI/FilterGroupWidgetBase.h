// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterGroupWidgetBase.generated.h"

/**
 * 
 */
class UFilterWidgetBase;

UCLASS()
class UI_TEST_API UFilterGroupWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitFilterGroupLogic();

	void AddFilter(UTexture2D* icon, const FText& lable);
	void ClearFilters();

	void AddFunctionEventToFilter(const std::function<void()>& clickEvent, int32 index);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Filters")
	TSubclassOf<UFilterWidgetBase> FilterClass;

	UPROPERTY(EditAnywhere, Category = "Filters")
	float ItemsPadding;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* FiltersBox;

private:
	UFilterWidgetBase* mSelectedFilter;

	TArray<UFilterWidgetBase*> mFilters;
};
