// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TEnergyBall.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTEnergyBall : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "CollisionWar")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetEnergyBallTexture(uint8 type);
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UImage* m_pImage;

	uint8 m_type;
};
