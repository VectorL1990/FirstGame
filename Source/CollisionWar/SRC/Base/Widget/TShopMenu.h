// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniformGridPanel.h"
#include "TextBlock.h"
#include "TActionCard.h"
#include "WidgetManager.h"
#include "MultiLineEditableTextBox.h"
#include "VerticalBox.h"
#include "TShopMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTShopMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxColPerRow = 10;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UUniformGridPanel* m_pUniformGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVContentBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pMoneyText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTitle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pShopCardDescriptionBox;

	UPROPERTY()
	TArray<UTActionCard*> m_pActionCards;

	UPROPERTY()
	UTActionCard* m_pCurSelectActionCard;

	UPROPERTY()
	TArray<FString> m_usedCardNames;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_margin;
};
