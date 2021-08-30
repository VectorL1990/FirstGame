// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "VerticalBox.h"
#include "TActionCard.h"
#include "Button.h"
#include "MultiLineEditableTextBox.h"
#include "../../Game/SingleProgress/PlayCard.h"
#include "WidgetManager.h"
#include "TShadowModeMenu.generated.h"

/**
 * 
 */
USTRUCT()
struct FPlayCardTActionCardMapInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		APlayCard* pPlayCard;

		UPROPERTY()
		UTActionCard* pActionCard;
};

UCLASS()
class COLLISIONWAR_API UTShadowModeMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	void ReadAllShadowCards();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void FadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetTextBlockTexts();

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVerticalBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pDeleteSAButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY()
	UTActionCard* m_pCurSelectSACard;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FSlateFontInfo m_defaultFontInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTextBlocks;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_textBlockTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_chTextBlockTexts;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pTutorialButton;
};
