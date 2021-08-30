// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "TextBlock.h"
#include "VerticalBox.h"
#include "TemplateRuneElement.h"
#include "TemplateRow.h"
#include "TemplateProgressSlider.h"
#include "TemplateComboBox.h"
#include "SimpleMenu.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FSimpleMenuPhaseButtonInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> buttonFunctions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> chTexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enTexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FSliderDefaultInfo> sliderInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FComboBoxDefaultInfo> comboBoxInfos;
};

UCLASS()
class COLLISIONWAR_API USimpleMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(const FString& buttonFunction);
	
	/** Ask simple menu to fade out
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void AskMenuFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyFirstSwitchPhase();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SwitchPhase();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyVBoxFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyVBoxFadeInt(uint8 phase);

	UWidgetManager* m_pWidgetManager;

	uint8 m_curPhase;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_domain = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_defaultVBoxMargin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_defaultSlotVBoxMargin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, FSimpleMenuPhaseButtonInfo> m_phaseInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pSlotVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pSaveSlotDescription;

	TArray<UTemplateRuneElement*> m_pButtons;

	TArray<UTemplateProgressSlider*> m_pSliders;

	TArray<UTemplateComboBox*> m_pComboBoxes;

	TArray<UTemplateRow*> m_pRows;

	FString m_selectSlotName;
};
