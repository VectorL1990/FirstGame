// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TActionCard.h"
#include "WidgetManager.h"
#include "UniformGridPanel.h"
#include "CanvasPanel.h"
#include "TDrawCardMenu.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTDrawCardMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDemonstrateString(uint8 demoNb);

	void AddDrawCardToMenu(int32 drawCardNb, uint8 drawCardColor, int32 row, int32 col);

	void AddPlayerCardToMenu(int32 drawCardNb, uint8 drawCardColor);

	UPROPERTY()
	UWidgetManager* m_pWidgetManager;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UTActionCard> m_drawCardBackClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxColPerRow = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_playerDrawCardPos;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pDrawCardMat;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UUniformGridPanel* m_pCardGridPanel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UCanvasPanel* m_pCanvasPanel;
};
