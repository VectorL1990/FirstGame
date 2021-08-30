// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFlipImage.h"
#include "MultiLineEditableTextBox.h"
#include "CanvasPanel.h"
#include "WidgetManager.h"
#include "TextBlock.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "TTutorialMenu.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FTutorialStepInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	UMediaSource* pMediaSource;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> chDescriptions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enDescriptions;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTutorialStepSerial : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		FString serialName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FTutorialStepInfo> tutorialSteps;
};

UCLASS()
class COLLISIONWAR_API UTTutorialMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialTitleTexts();

	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTFlipImage* m_pTutorialImage;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	UMediaPlayer* m_pMediaPlayer;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_FlipImageSize;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_FlipImagePos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<UTextBlock*> m_pTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chTitleTexts;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enTitleTexts;

	UPROPERTY()
	FTutorialStepSerial m_tutorialSerial;

	int32 m_curTutorialMiniStep = 0;

	int32 m_curTutorialStep = 0;

	uint8 m_type;
};
