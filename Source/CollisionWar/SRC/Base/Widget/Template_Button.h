// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "SizeBox.h"
#include "Spacer.h"
#include "TextBlock.h"
#include "Template_Button.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonClickDelegate,const FString&, buttonFunction);

UCLASS()
class COLLISIONWAR_API UTemplate_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialButton(UButton* pButton, USizeBox* pSizeBox, USpacer* pLeftSpacer, USpacer* pRightSpacer, UTextBlock* pCaption, UImage* pBGImage);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickButton();
	/** Elements
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton* m_pButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pLeftSpacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pRightSpacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCaption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	UImage* m_pBorderImage;

	/** General properties
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_caption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_chineseCaption;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_buttonFunction;

	FButtonClickDelegate m_buttonClickDelegate;
};
