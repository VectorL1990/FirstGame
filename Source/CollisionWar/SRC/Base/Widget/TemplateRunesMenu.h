// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "VerticalBox.h"
#include "TextBlock.h"
#include "Button.h"
#include "MultiLineEditableTextBox.h"
#include "TemplateRuneElement.h"
#include "HorizontalBox.h"
#include "../CollisionWarGameInstance.h"
#include "GridPanel.h"
#include "ScrollBox.h"
#include "TemplateRunesMenu.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTemplateRunesMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ButtonClick(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SwitchCurRuneElement(UTemplateRuneElement* pSelectElement);

	void UpdateUnlockCardNbText();

	void SwitchDomain();

	void UpdateAttributeValue();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FCharacterAttributeInfo ReadCharacterAttributeInfo(const FString& characterName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTitleTexts();
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pFCButtonTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pAttributeIncreaseNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pLifeNbTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pAtkNbTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pDfcNbTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pLifeNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pAtkNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pDfcNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCurMentalityNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pCurAvailableSkillSlotNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitleTexts;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pContentBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	/** 记录当前显示信息
	* 0 - 刚创建，什么都没有
	* 1 - 技能表
	* 2 - 虫魂表
	* 3 - 合成公示表
	* 4 - 数值表
	*/
	uint8 m_curDomain = 0;

	uint8 m_targetDomain = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UTemplateRuneElement*> m_pRuneElementMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTemplateRuneElement*> m_pUnlockCardTitles;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateRuneElement* m_pUnlockCardTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTemplateRuneElement* m_pCurSelectElement;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UScrollBox* m_pScrollBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pEquipGridPanel;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FLinearColor m_inAvailableRuneColor;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pDefaultCardCombineTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_switchDelayTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_fcUnlockTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chFCUnlockTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_appearanceUnlockTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chAppearanceUnlockTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_attributeIncreaseTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chAttributeIncreaseTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chLifeTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chAtkTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_chDfcTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_lifeTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_atkTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FString m_dfcTitle;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_increaseAttributeName;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_elementPadding;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxGridColNb = 5;

	FTimerHandle m_switchTimerHandler;

	FString m_curAppearanceName;

	int32 m_curUnlockNb = 0;
};
