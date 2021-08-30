// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VerticalBox.h"
#include "TemplateProgressSlider.h"
#include "TemplateComboBox.h"
#include "TemplateMainMenu.generated.h"

/**
 * 
 */



UCLASS()
class COLLISIONWAR_API UTemplateMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton(FString buttonFunction);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pSliderVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pComboboxVBox;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FSliderDefaultInfo> m_sliderInfos;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FComboBoxDefaultInfo> m_comboboxInfos;

	TArray<UTemplateProgressSlider*> m_pSliders;

	TArray<UTemplateComboBox*> m_pComboboxes;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_sliderMargin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_comboboxMargin;
};
