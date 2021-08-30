// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TemplateNotificationShowUpButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotificationShowUpButtonDelegate, const FString&, buttonName);

UCLASS()
class COLLISIONWAR_API UTemplateNotificationShowUpButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateNotificationShowUpButton(UButton* pButton);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ClickShowUpButton();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	UButton * m_pButton;
	
	FNotificationShowUpButtonDelegate m_clickShowUpButtonDelegate;
};
