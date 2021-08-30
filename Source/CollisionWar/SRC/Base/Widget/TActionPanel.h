// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "MultiLineEditableTextBox.h"
#include "TemplateRuneElement.h"
#include "../../Game/SingleProgress/EventCard.h"
#include "../../Game/SingleProgress/AnimBook.h"
#include "../../Game/SingleProgress/EventNodeManager.h"
#include "VerticalBox.h"
#include "TActionPanel.generated.h"

/**
 * 
 */


UCLASS()
class COLLISIONWAR_API UTActionPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	void UpdateActionPanelInfo(UEventNodeManager* pEventNodeManager);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton(const FString& buttonFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyPlaySwitchContextAnim();

	void ShowActionWords(FString words);

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UVerticalBox* m_pVBox;

	TArray<UTemplateRuneElement*> m_pChoiceButtons;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FMargin m_vboxMargin;
};
