// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "TemplatePlayerDetail.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplatePlayerDetail : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateDetail(UImage* pDarkBG, UTextBlock* pPlayerNameCaption, UTextBlock* pPlayerNameText,
		UTextBlock* pTotalWinCaption, UTextBlock* pTotalWinNbText);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage * m_pDarkBG;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pPlayerNameCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pPlayerNameText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTotalWinCaption;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTotalWinNbText;

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_playerName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_playerTotalWinNbText;
};
