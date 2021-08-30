// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditableTextBox.h"
#include "MultiLineEditableTextBox.h"
#include "VerticalBox.h"
#include "TextBlock.h"
#include "WidgetManager.h"
#include "TemplateRuneElement.h"
#include "../../Game/SingleProgress/ShadowActor.h"
#include "TCardCombineListMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTCardCombineListMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();
	
	void SwitchDomain(uint8 domain);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Search(FString searchStr);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	void LoadShadowActorCards();

	UWidgetManager* m_pWidgetManager;

	TArray<UMultiLineEditableTextBox*> m_pCombineList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pOverivewDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UMultiLineEditableTextBox* m_pCardDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UEditableTextBox* m_pSearchText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pAllCombineInfoTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pExploreCombineInfoTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pCommunicationCombineInfoTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pForgeCombineInfoTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pResearchCombineInfoTitle;

	FSlateFontInfo m_combineInfoFont;

	TArray<UTemplateRuneElement*> m_pSACardElements;

	/** 描述当前显示的合成公式范围
	* 0 - 所有
	* 1 - 探索公式
	* 2 - 交流公式
	* 3 - 锻造公式
	* 4 - 研究公式
	*/
	uint8 m_domain = -1;

	TArray<FString> m_transformOverviews;

	TMap<FString, FString> m_shadowActorOvervieMap;

	TMap<FString, FOverallIndexValueInfo> m_shadowActorCost;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_elementPadding;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pConsumeTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pLifeTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pEnergyTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pMoneyTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pMentalityTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pSuppressionTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pActivityTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pDarknessTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pFlameFaithTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pSunFaithTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pLife;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pEnergy;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pMoney;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pMentality;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pSuppression;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pActivity;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pDarkness;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pFlameFaith;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pSunFaith;
};
