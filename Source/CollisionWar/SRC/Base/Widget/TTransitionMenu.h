// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiLineEditableTextBox.h"
#include "WidgetManager.h"
#include "ProgressBar.h"
#include "Image.h"
#include "MediaSource.h"
#include "MediaPlayer.h"
#include "TextBlock.h"
#include "TTransitionMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTTransitionMenu : public UUserWidget
{
	GENERATED_BODY()
public:

	void InitialTransitionMenu();

	void UpdateProgressBar();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FadeOutEnd();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialCalenderData();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CollisionWar")
	FString ReadCalenderDemoText(bool chOrEn);

	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTitleText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UProgressBar* m_pProgressBar;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pProgressImage;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chDescriptions;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_enDescriptions;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<UMediaSource*> m_pAllMediaSources;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMediaPlayer* m_pMediaPlayer;

	int32 m_curDescriptionNb = 0;

	int32 m_curLoadProgress = 0;

	TArray<uint8> m_asyncLoadDoneState;

	/** transitionMenu����3���ط�
	*0. ��ȡ����
	*1. Logo����
	*2. ����۽��ܽ���
	*����������Ҫ����Ƶ����ͬ��Ҫ���ݽ���ѡ����ʲô��Ƶ
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_type = 0;
};
