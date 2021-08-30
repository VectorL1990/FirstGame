// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SizeBox.h"
#include "TextBlock.h"
#include "Spacer.h"
#include "CheckBox.h"
#include "TemplateCheckBox.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCheckBoxClickDelegate, FString, checkBoxFunction, bool, isCheck);

UCLASS()
class COLLISIONWAR_API UTemplateCheckBox : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateCheckBox(USizeBox* pSizeBox, UTextBlock* pCaption, USpacer* pSpacer, UCheckBox* pCheckBox);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void CheckBoxClick();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pSpacer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UCheckBox* m_pCheckBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_caption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_function;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	bool m_isCheck;

	FCheckBoxClickDelegate m_checkBoxDelegate;
};
