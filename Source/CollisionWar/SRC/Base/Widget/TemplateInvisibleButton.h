// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SizeBox.h"
#include "Spacer.h"
#include "Button.h"
#include "TextBlock.h"
#include "WidgetManager.h"
#include "TemplateInvisibleButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInvisibleButtonClickDelegate, FString, buttonFunction, EInvisibleButtonLocation, buttonLocation);

UCLASS()
class COLLISIONWAR_API UTemplateInvisibleButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialInvisibleButton(USpacer* pLeftSpacer, USpacer* pRightSpacer, UButton* pButton, UTextBlock* pTextBlock, USizeBox* pSizeBox);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InvisibleButtonClick(FString function);
	/** active select button
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetActive();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void SetDeactive();

	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_caption;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_chineseCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString m_englishCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString  m_buttonFunction;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	EInvisibleButtonLocation m_buttonLocation;

	/** components
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pButtonText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pLeftSpacer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pRightSpacer;

	FInvisibleButtonClickDelegate m_buttonClickDelegate;
};
