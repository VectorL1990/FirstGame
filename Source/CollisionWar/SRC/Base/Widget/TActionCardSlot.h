// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TActionCardSlot.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTActionCardSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ClickButton();
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DropToSlot();
};
