// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SizeBox.h"
#include "VerticalBox.h"
#include "TextBlock.h"
#include "ScrollBox.h"
#include "TemplatePlayerTag.h"
#include "TemplateRankInfo.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRankInfoFadeOutDelegate, FString, caption);

UCLASS()
class COLLISIONWAR_API UTemplateRankInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateRankInfo(USizeBox* pSizeBox, UVerticalBox* pSingleVBox, UTextBlock* pSingleRankBoxCaption, UScrollBox* pSingleScrollBox,
		UVerticalBox* pOneOneVBox, UTextBlock* pOneOneRankBoxCaption, UScrollBox* pOneOneScrollBox,
		UVerticalBox* pTwoTwoVBox, UTextBlock* pTwoTwoRankBoxCaption, UScrollBox* pTwoTwoScrollBox,
		UVerticalBox* pThreeThreeVBox, UTextBlock* pThreeThreeRankBoxCaption, UScrollBox* pThreeThreeScrollBox);


	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void AskFadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void RankInfoFadeOutDone();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox * m_pSizeBox;
	
	/** Single single rank components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pSingleVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pSingleRankBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pSingleScrollBox;

	/** One one rank components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pOneOneVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pOneOneRankBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pOneOneScrollBox;

	/** Two two rank components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pTwoTwoVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTwoTwoRankBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pTwoTwoScrollBox;

	/** Three three rank components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UVerticalBox* m_pThreeThreeVBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pThreeThreeRankBoxCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UScrollBox* m_pThreeThreeScrollBox;

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_textLineInterval;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_textTopPadding;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_mapType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_singleCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_oneOneCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_twoTwoCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_threeThreeCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FString> m_singlePlayerNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_oneOnePlayerNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_twoTwoPlayerNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_threeThreePlayerNameList;

	/** Elements
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplatePlayerTag*> m_pSinglePlayerTags;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplatePlayerTag*> m_pOneOnePlayerTags;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplatePlayerTag*> m_pTwoTwoPlayerTags;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplatePlayerTag*> m_pThreeThreePlayerTags;

	FRankInfoFadeOutDelegate m_rankInfoFadeOutDelegate;
};
