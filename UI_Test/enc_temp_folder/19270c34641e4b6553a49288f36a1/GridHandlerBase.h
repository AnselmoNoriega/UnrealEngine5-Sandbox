// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridHandlerBase.generated.h"

/**
 * 
 */
UCLASS()
class UI_TEST_API UGridHandlerBase : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(CallInEditor, Category = "Test")
    void AddItemFromEditor();
    UFUNCTION(CallInEditor, Category = "Test")
    void ClearItemFromEditor();
    UPROPERTY(EditAnywhere, Category = "Test")
    TSubclassOf<UWidget> TestItem;

    UPROPERTY(EditAnywhere, Category = "Test")
    int32 TestLayerIndex = 0;


    void AddItem(UWidget* item, int32 layerIndex);
    void ClearLayer(int32 layerIndex);
    void ClearItems();

    void ChangeLayer(int32 layerIndex);

protected:
    void SynchronizeProperties() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    int32 MaxColumns = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    FMargin ItemPadding;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* RootCanvas;

private:
    TMap<int32, class UVerticalBox*> mLayeredItems;

    int32 mCurrentLayer = 0;
};
