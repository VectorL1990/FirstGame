// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiLineEditableTextBox.h"
#include "GridPanel.h"
#include "TemplateRuneElement.h"
#include "WidgetManager.h"
#include "TextBlock.h"
#include "Button.h"
#include "TSkillSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTSkillSelectMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTexts(TArray<UTextBlock*> pTextBlocks);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DropSelectCard(UTemplateRuneElement* pSource);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void InitialTitleTexts();


	void UpdateSkillCapacityText();
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pSkillDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pSkillGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pSelectSkillGridPanel;

	TMap<int32, UTemplateRuneElement*> m_pAllAvailableSkills;

	UWidgetManager* m_pWidgetManager;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxCol = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_gridMargin;

	UTemplateRuneElement* m_pCurSelectSkillButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_defaultStrs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> m_defaultChStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxSelectSkillCol = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_selectSkillMargin;

	TMap<int32, UTemplateRuneElement*> m_pAllSelectSkillCards;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_skillCapacity;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pLeftSkillSelectNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitles;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pTutorialButton;
};
