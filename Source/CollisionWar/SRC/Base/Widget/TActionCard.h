// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "../../Game/SingleProgress/PlayCard.h"
#include "TActionCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTActionCard : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialActionCard(int32 cardNb, uint8 color, FString cardName, UTexture* pTexture);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnCardDrag();

	void SetupFadeInTimer(uint8 fadeOrHighLight, bool fadeInOrOut);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySetTimer(uint8 fadeType);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ClearFadeTimer();

	void SetFadeType(bool flipOrFade, bool frontOrBack);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Fade();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void HighLight();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OnHoverStart(uint8 cardType);

	/** cardType标识ActionCard的种类，如为0表示是DiceSkillCard，如为1表示是TheorizeSkillCard
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FadeOutEnd(uint8 cardType);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyChangeColor(uint8 type);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void Hover();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void HoverEnd();
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_fadeTotalTime;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pPlayCardImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	APlayCard* m_pPlayCard;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_cardName;

	FString m_chDescription;

	FString m_enDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_nb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_color;

	int32 m_curFadeTime;

	float m_curHighLightProgress = 0.f;

	bool m_highHightFlag = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_highLightStep = 0.1f;

	bool m_fadeInOrOut = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTimerHandle m_timerHandle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTimerHandle m_highLightTimerHandle;
};
