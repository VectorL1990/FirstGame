// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplateRuneElement.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UTemplateRuneElement : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void NotifyPress();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void NotifyRecover();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ButtonClick();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void AppendButtonClick(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyChangeButtonImageAndText(const FString& buttonName, bool chOrEn);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifySetTimer();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void Fade();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void ClearFadeTimer();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifySetUnlockText(const FString& curUnlockPt, const FString& maxUnlockPt);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pRuneImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pRuneName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_buttonFunction;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_fadeTotalTime;

	float m_curFadeTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FTimerHandle m_timerHandler;
};
