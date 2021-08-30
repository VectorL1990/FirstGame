// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "Spacer.h"
#include "EditableTextBox.h"
#include "SizeBox.h"
#include "HorizontalBoxSlot.h"
#include "TemplateInputText.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommitInputTextDelegate, FString, text, FString, function);

UCLASS()
class COLLISIONWAR_API UTemplateInputText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateInputText(UTextBlock* pCaption, USpacer* pSpacer, UEditableTextBox* pEditBox, USizeBox* pSizeBox);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyIntial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InputTextCommit();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTextBlock* m_pCaption;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pSpacer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UEditableTextBox* m_pEditBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_caption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_chineseCaption;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_hintText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_chineseHintText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_inputText;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_function;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	float m_lineHeight;

	FCommitInputTextDelegate m_commitTextDelegate;
};
