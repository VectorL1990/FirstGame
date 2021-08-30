// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CanvasPanel.h"
#include "PhysActorPopButton.h"
#include "WidgetManager.h"
#include "TPhysActorPopMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTPhysActorPopMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void InitialPopMenu(UCanvasPanel* pPanel, UPhysActorPopButton* pBuildButton, UPhysActorPopButton* pInfoButton);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UPhysActorPopButton* m_pBuildButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UPhysActorPopButton* m_pInfoButton;
};
