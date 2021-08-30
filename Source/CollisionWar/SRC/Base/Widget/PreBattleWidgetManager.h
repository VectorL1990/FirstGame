// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Base/Widget/WidgetManager.h"
#include "PreBattleWidgetManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UPreBattleWidgetManager : public UWidgetManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void ScrollBoxFadeOutDoneCallback(FString caption);
	
	virtual void InvisibleButtonClickCallback(FString buttonFunction, EInvisibleButtonLocation location) override;
};
