// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TActionCardInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTActionCardInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDemoWords(const FString& demoWords);

	void SetLoadProgress(float percent);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pLoadImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pLoadTime;
};
