// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "MultiLineEditableTextBox.h"
#include "Button.h"
#include "VerticalBox.h"
#include "SizeBox.h"
#include "TSkillTreeIcon.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillTreeIconButtonDelegate, const FString&, buttonFunction);

UCLASS()
class COLLISIONWAR_API UTSkillTreeIcon : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_skillIconName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVerticalBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pSkillImage;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pContentTextBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pButton;

	FString m_chineseText;

	FString m_englishText;

	FSkillTreeIconButtonDelegate m_buttonClickDelegate;
};
