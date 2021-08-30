// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SizeBox.h"
#include "Spacer.h"
#include "TextBlock.h"
#include "TemplateTextLine.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateTextLine : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void InitialTemplateTextLine(USizeBox* pSizeBox, USpacer* pLeftSpacer, USpacer* pRightSpacer, UTextBlock* pText);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pLeftSpacer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pRightSpacer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pTextBlock;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_text;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_chineseText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;
};
