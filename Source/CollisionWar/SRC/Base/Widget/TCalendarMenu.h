// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetManager.h"
#include "MultiLineEditableTextBox.h"
#include "TCalendarMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTCalendarMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();
	
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void FadeOut();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick(const FString& buttonFunction);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pEventDescriptionTextBox;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pRewardDescriptionTextBox;

	UWidgetManager* m_pWidgetManager;
};
