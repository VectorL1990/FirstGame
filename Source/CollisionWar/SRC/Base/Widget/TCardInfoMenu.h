// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "SizeBox.h"
#include "WidgetManager.h"
#include "TSkillTree.h"
#include "CanvasPanel.h"
#include "TextBlock.h"
#include "TCardInfoMenu.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardInfoMenuButtonClickDelegate, const FString&, buttonFunction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCardInfoMenuFadeOutDelegate, FString, menuName);

UCLASS()
class COLLISIONWAR_API UTCardInfoMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick(FString buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void FadeOutDone(FString menuName);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UButton* m_pBasicCardInfoButton;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pEventCardInfoButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pItemCardInfoButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pSpecialSkillCardInfoButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		UButton* m_pAttributeCardInfoButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	USizeBox* m_pSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pTitleText;

	FCardInfoMenuButtonClickDelegate m_buttonClickDelegate;
	FCardInfoMenuFadeOutDelegate m_menuFadeOutDelegate;
};
