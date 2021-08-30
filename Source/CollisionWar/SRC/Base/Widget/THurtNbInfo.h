// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "THurtNbInfo.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTHurtNbInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitial();

	void SetupNb(int32 nb);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeOut();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextBlock* m_pNbText;
};
