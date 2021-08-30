// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "SizeBox.h"
#include "TextBlock.h"
#include "GridPanel.h"
#include "Button.h"
#include "ScrollBox.h"
#include "WidgetManager.h"
#include "GridSlot.h"
#include "TemplateMenuTitle.h"
#include "TemplateItemElement.h"
#include "ItemMenu.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemMenuFadeOutDoneDelegate, FString, menuName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResumeButtonClickDelegate, const FString&, buttonFunction);

UCLASS()
class COLLISIONWAR_API UItemMenu : public UUserWidget
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void InitialItemMenu(USizeBox* pContentSizeBox, UGridPanel* pGridPanel, UButton* pResumeButton);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void ClickResumeButton(FString buttonName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
		void MenuFadeOutDone();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
		void AskFadeOut();


	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		USizeBox* m_pContentSizeBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UGridPanel* m_pGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UButton* m_pResumeButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UTemplateMenuTitle* m_pMenuTitle;

	/** Elements
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateItemElement*> m_pItems;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateItemElement*> m_pSelectItems;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<UTemplateItemElement*> m_pEquipItems;
	/** General members
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_menuName;

	FItemMenuFadeOutDoneDelegate m_fadeOutDoneDelegate;

	FResumeButtonClickDelegate m_resumeButtonClickDelegate;
};
