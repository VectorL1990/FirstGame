// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "TActionCard.h"
#include "CanvasPanel.h"
#include "MultiLineEditableTextBox.h"
#include "TextBlock.h"
#include "TCardSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTCardSelectMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	/** 这个函数的意思是因为奖励机制是这样的，分为必奖系列和随机奖系列，必奖的话系统又会生成几张卡让玩家选，玩家选择后会自动切换到随机奖励
	* 所以这里要有一个切换卡牌内容的函数，将那几张必奖卡牌撤下，然后切换到随机奖的卡牌
	*/
	void StartSwitchDomain();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SwitchDomain();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifySetTimer();

	/** 这个函数的作用是把奖励卡牌添加上到选卡菜单中
	* domain - 标记是哪个范畴的奖励卡牌，0代表必奖卡牌，1代表随机奖励卡牌
	*/
	void AddActionCardToPanel(uint8 domain);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTitles();

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pBonusCanvas;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pInstructionText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_cardInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTActionCard> m_pBonusCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_bonusCardSize;

	TArray<FString> m_allBonusCardNames;

	UPROPERTY()
	TArray<UTActionCard*> m_pAllBonusCards;

	UTActionCard* m_pCurSelectCard;

	int32 m_curDomainNb = 0;

	TArray<FString> m_mustBonusCards;

	uint8 m_bonusType = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chInstruction;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enInstruction;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_chTitles;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitles;
};
