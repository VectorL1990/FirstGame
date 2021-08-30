// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "TextBlock.h"
#include "VerticalBox.h"
#include "HorizontalBox.h"
#include "CanvasPanel.h"
#include "MultiLineEditableTextBox.h"
#include "TActionCard.h"
#include "TemplateRuneElement.h"
#include "GridPanel.h"
#include "TEnergyBall.h"
#include "Button.h"
#include "TBattleLineMenu.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTBattleLineMenu : public UUserWidget
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

	void LoadAvailableSkills();

	/** 展示字样
	*0 = Start开具字样
	*2 = 系统运算字样
	*3 = 系统掷骰没有判定中的字样
	*4 = 玩家胜利字样
	*5 = 玩家失败字样
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDemonstrateText(uint8 demoWordNb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupTextBlockStrs();

	void InitialMenuParam(int32 targetScore, int32 time);

	void UpdateTime(float time);

	void UpdateLifeText(int32 life);

	void UpdateScoreText(int32 score);

	/** type标识要播放的动画类型
	* 0. 得分动画
	* 1. 损失生命动画
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShowDemoImage(uint8 type);

	void UpdateResetTimes(int32 times);

	void AddDiceSkillImage(FString diceSkillName, int32 skillNb);

	void DeleteDiceSkillImage(int32 diceSkillNb);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UWidgetManager* m_pWidgetManager;
		
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Widget")
	FString m_menuName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_chineseTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_englishTitle;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pEnsureButtonText;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCurTimeText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pTimeCountImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pTotalTimeText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCurScoreNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pScoreImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTargetScoreNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCurLifeNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCurResetNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTextBlock*> m_pTextBlocks;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UMultiLineEditableTextBox* m_pDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pSkillVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pSkillCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pLifeCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UCanvasPanel* m_pResetCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pAppendSkillGridPanel;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTActionCard> m_pDiceSkillCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_skillCardInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chMenuStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_menuStrs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_skillCardSize;

	TMap<UTemplateRuneElement*, int32> m_pAllDiceSkillDemoCards;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_skillCardColNb = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_appendSkillMargin;

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

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pTutorialButton;

	float m_maxTime;

	float m_targetScore;
};
