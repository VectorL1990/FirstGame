// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TemplateMenuTitle.h"
#include "WidgetManager.h"
#include "Button.h"
#include "UniformGridPanel.h"
#include "TextBlock.h"
#include "CanvasPanel.h"
#include "TemplateRuneElement.h"
#include "Image.h"
#include "GridPanel.h"
#include "MultiLineEditableTextBox.h"
#include "TDecipherMenu.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTDecipherMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void MenuFadeInDoneCallaback(FString menuName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDemonstrateString(uint8 textNb);

	void InitialDecipherMenu();

	void UpdateAllParam();

	/** type标识要播放的动画类型
	* 0. 得分动画
	* 1. 损失生命动画
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyShowDemoImage(uint8 type);

	void LoadTheorizeSkills();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupTextBlockStrs();

	void AddTheorizeSkillImage(FString theorizeSkillName, int32 skillNb);

	void DeleteTheorizeSkillImage(int32 skillNb);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
		TSubclassOf<class UTActionCard> m_numberCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TSubclassOf<class UTActionCard> m_pTheorizeSkillCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	int32 m_columnPerRow;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTemplateMenuTitle* m_pMenuTitle;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_chineseTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_englishTitle;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UUniformGridPanel* m_pNumberCardGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTargetScoreText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCurScoreText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pScoreImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pLifeText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCompareText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pResetText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UCanvasPanel* m_pSkillCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pLifeCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UCanvasPanel* m_pResetCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UCanvasPanel* m_pCompareCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_skillCardInterval;

	TArray<UTActionCard*> m_pNumberCardList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chMenuStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_menuStrs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTextBlocks;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pSkillDemoCardGridPanel;

	TMap<UTemplateRuneElement*, int32> m_pAllTheorizeSkillDemoCards;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_skillCardColNb = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FMargin m_appendSkillMargin;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_skillCardSize;


	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TSubclassOf<class UTEnergyBall> m_pLifeBallClass;

	TArray<UTEnergyBall*> m_pLifeBalls;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector2D m_lifeBallDefaultSize;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_lifeBallInterval = 50;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TSubclassOf<class UTEnergyBall> m_pResetBallClass;

	TArray<UTEnergyBall*> m_pResetBalls;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector2D m_resetBallDefaultSize;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_resetBallInterval = 50;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TSubclassOf<class UTEnergyBall> m_pCompareBallClass;

	TArray<UTEnergyBall*> m_pCompareBalls;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector2D m_compareBallDefaultSize;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_compareBallInterval = 50;

	int32 m_targetScore = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pTutorialButton;
};
