// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "Button.h"
#include "ProgressBar.h"
#include "TBattleCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTBattleCard : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION()
	void ShowCard();

	UFUNCTION()
	void HideCard();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton();

	UFUNCTION()
	void SwitchImage(UTexture* pSkillTexture, const FString& cardName);

	void UpdateCoolDown(float percentage);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void CopyFromBattleCard(UTBattleCard* pSourceCard);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnCardDrop(UUserWidget* pDropCard);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySetUpdateTimer();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void UpdateTimer();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ClearFadeTimer();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyPlaySlideAnimation(uint8 slideType);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pFrameImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSkillImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_cardName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pCardName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UProgressBar* m_pMask;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_buttonFunction;

	bool m_isShow = false;

	int32 m_curUpdateTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_totalUpdateTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_updateRange;

	UTexture* m_pCurTexture;

	//int32 m_curSlidePos;

	int32 m_slideTimes = 0;
};
