// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TJudgeInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTJudgeInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pJudgeNb;

	FString m_buttonFunction;

	FString m_description;
};
