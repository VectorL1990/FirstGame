// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TGeneralCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTGeneralCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton();

	void ClearCard();

	void AssignGeneralCardInfo(FString cardName);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSkillImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCardNameTextBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pNumericNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UTexture* m_pDefaultSkillTexture;

	FString m_cardName;

	FString m_chCardName;

	/** domain标识GeneralCard的归类
	* 0 - 说明此时为介绍界面
	* 1 - 说明此时为交易界面
	* 2 - 说明此时为卡牌复制界面
	* 3 - 说明此时为事件触发界面
	*/
	uint8 m_domain;
};
