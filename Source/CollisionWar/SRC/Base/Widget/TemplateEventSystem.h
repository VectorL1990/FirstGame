// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiLineEditableTextBox.h"
#include "TemplateEventSystem.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateEventSystem : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ButtonClick(const FString& buttonFunction);

	void LoadMissionText(const FString& text);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMultiLineEditableTextBox* m_pDescriptionBox;

	uint8 m_domain = 1;
};
