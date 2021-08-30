// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Button.h"
#include "TBattleCard.h"
#include "ScrollBox.h"
#include "TEnermyCard.h"
#include "WidgetManager.h"
#include "ProgressBar.h"
#include "MultiLineEditableTextBox.h"
#include "DialogTextMenu.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "CanvasPanel.h"
#include "TTradeCard.h"
#include "GridPanel.h"
#include "TemplateBattleElementSystem.generated.h"

/**
 * 
 */

USTRUCT()
struct FEnermyCardInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString cardName;

	UPROPERTY()
		TArray<FString> stateNameList;

	UPROPERTY()
	UTEnermyCard* pEnermyCard;

	UPROPERTY()
	int32 enermyNb;
};

UCLASS()
class COLLISIONWAR_API UTemplateBattleElementSystem : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	void DeleteSkillFromMenu(int32 cardNb);

	void SwitchSkillCard(int32 cardNb, FString newCardName, FString supplementSkillName);

	void DeleteEquipFromMenu(int32 slotNb);

	UFUNCTION()
	void SwitchSkillAndBuildDomain(bool switchToSkillDomain);

	UFUNCTION()
	void SwitchFCMenuPhase(bool upOrDownPage);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateResourcesAmout(uint8 resourceID, int32 resourceNb);
	
	void UpdateSkillCoolDownPercentage(uint8 skillNb, float coolDownPercent);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShakeHitText(int32 scoreLevel);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyHurtLevelChange(int32 lv1, int32 lv2, int32 lv3, int32 lv4, int32 lv5);

	void SetEquipCard(uint8 cardNb, UTexture* pTexture, FString cardName);

	void UpdateCombineKeyList(const FString& combineKeyList);

	void UpdateCurFrameCount(int32 curFrame, int32 maxFrame, uint8 type);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void AskFadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateReloadTime(float dT);

	void StopReload();

	void SlidePreBattleCards(FString supplementSkill);

	bool AddNNumericCardToPanel(FString cardName, int32 ID);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTitleTexts();
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pReloadBar;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pReloadLeftTime;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pFirstResourceText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pSecondResourceText;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pThirdResourceText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pFourthResourceText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pFifthResourceText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pSwitchToSkillButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pSwitchToFCButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pPageUpButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pPageDownButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pInfoButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pPauseButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pShowSkillTreeButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pTutorialButton;
/*

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UScrollBox* m_pScrollBox;*/

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTBattleCard*> m_pSkillBattleCardList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTBattleCard*> m_pEquipBattleCardList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UProgressBar* m_pHurtScoreBar;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCurKillText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pTargetKillText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pSkillDescription;

	UPROPERTY()
	UDialogTextMenu* m_pMissionMenu;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCurLeftTime;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitleTexts;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pCurLeftTimeImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pForceAccumulateImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pNumericGridPanel;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxCombatDescNb = 10;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_combineKeyStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_curLeftTimeTitleStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chCurLeftTimeTitleStr;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pBattleCardMat;
	
	UPROPERTY()
	TArray<FEnermyCardInfo> m_enermyCardInfoList;

	bool m_isInSkillDomain = true;

	int32 m_curFCMenuPhase = 0;

	TArray<int32> m_firstAddFinishSkillSlotNbs;

	float m_curReloadTime;

	float m_reloadTime;

	bool m_shouldReload;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_numericGridPanelCol = 2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_numericGridPanelRow = 7;

	TMap<int32, UTTradeCard*> m_pNumericCards;

	TArray<UTTradeCard*> m_pAllNumericCards;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FVector2D> m_preBattleCardLocs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pDefaultNumericCardText;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pNumericCardMat;

	TArray<FString> m_curTempSwitchDomainSkillCardNames;

	int32 m_curKillEnermyNb = 0;

	int32 m_targetKillEnermyNb = 0;

	
};
