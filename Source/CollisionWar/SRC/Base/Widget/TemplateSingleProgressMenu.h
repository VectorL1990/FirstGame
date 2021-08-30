// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "WidgetManager.h"
#include "MultiLineEditableTextBox.h"
#include "ProgressBar.h"
#include "TextBlock.h"
#include "../../Game/SingleProgress/PlayCard.h"
#include "TemplateRuneElement.h"
#include "TEnergyBall.h"
#include "GridPanel.h"
#include "Image.h"
#include "HorizontalBox.h"
#include "TemplateMenuTitle.h"
#include "CanvasPanel.h"
#include "TSkillTree.h"
#include "TSkillSelectIcon.h"
#include "SizeBox.h"
#include "TemplateSingleProgressMenu.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSingleprogressButtonClickDelegate, const FString&, buttonFunction);


UCLASS()
class COLLISIONWAR_API UTemplateSingleProgressMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick(const FString& buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShowCardFunctionList();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyHideCardFunctionList();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateCardNbText();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShowMissionArrow();

	void UpdateSPProgressImage(int32 curProgress, int32 curProgressLayer);

	void AddBossBattleProgressBall();

	void ShowDemoText(const FString& demoText);


	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyShowEventCardDescription();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyHideEventCardDescription();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_showCardFunctionMenuState = 0;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDesktopDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pMoneyBar;

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pPauseText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UTextBlock* m_pDemoText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pDemoTextCanvasPanel;

	TMap<int32, UTemplateMenuTitle*> m_pDemoTexts;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTEnergyBall*> m_pProgressBalls;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TArray<UTEnergyBall*> m_pLayerProgressBalls;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UGridPanel* m_pCursedCardGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UMultiLineEditableTextBox* m_pCardFunctionDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UUserWidget* m_pMissionArrow;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSPProgressBarImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UHorizontalBox* m_pProgressBoxHBox;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UTexture* m_pLayerProgressBallTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pProgressBallTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UTexture* m_pDefaultProgressBallTexture;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTEnergyBall> m_pProgressBallClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TSubclassOf<class UTemplateMenuTitle> m_pDemoTextClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_demoTextSize;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_demoTextInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_allChTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_allEnTitleTexts;

	TArray<UTemplateRuneElement*> m_pAllCardFunctionElements;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<UTexture*> m_pDemoTextures;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pTutorialButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pEventNodeDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pRewardDescriptionBox;

	bool m_isSkillTreeShown = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTSkillTree* m_pSkillTree;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_pAttributeTextures;

	UTSkillSelectIcon* m_pCurHighLightSkillSelectIcon;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTSkillSelectIcon*> m_pChopSkillIcons;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTSkillSelectIcon*> m_pDodgeSkillIcons;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTSkillSelectIcon*> m_pBlockSkillIcons;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTSkillSelectIcon*> m_pNormalSkillIcons;
};
