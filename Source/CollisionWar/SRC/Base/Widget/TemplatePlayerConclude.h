// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SizeBox.h"
#include "TextBlock.h"
#include "TemplatePlayerConclude.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplatePlayerConclude : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplatePlayerConclude(USizeBox* pSizeBox, UTextBlock* pPlayerName, UTextBlock* pCaption1, UTextBlock* pContent1,
		UTextBlock* pCaption2, UTextBlock* pContent2, UTextBlock* pCaption3, UTextBlock* pContent3, UTextBlock* pCaption4, UTextBlock* pContent4);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pPlayerNameText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCaption1;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pContent1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCaption2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pContent2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCaption3;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pContent3;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pCaption4;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UTextBlock* m_pContent4;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_playerName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_caption1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_content1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_caption2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_content2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_caption3;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_content3;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_caption4;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_content4;
};
