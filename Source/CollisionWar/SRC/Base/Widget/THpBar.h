// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "ProgressBar.h"
#include "THpBar.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTHpBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	void SetHp(float percent, int32 curHp, int32 maxHp, int32 curDFC, int32 maxDFC);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UProgressBar* m_pProgressBar;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pHpBar;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pHpText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pDFCText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pATKText;
};
