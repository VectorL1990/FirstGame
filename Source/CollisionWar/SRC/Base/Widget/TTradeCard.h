// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TemplateItemElement.h"
#include "Image.h"
#include "TextBlock.h"
#include "TTradeCard.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTTradeCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick();

	void ClearTradeCard(UTexture* pBlackTexture);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pColorImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pNbText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_buttonFunction;

	FString m_cardName;

	UPROPERTY()
	int32 m_itemSelectID = -1;
};
