// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spacer.h"
#include "Blueprint/UserWidget.h"
#include "TemplateSpacer.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UTemplateSpacer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Widget")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Widget")
	void InitialTemplateSpacer(USpacer* pSpacer);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	USpacer* m_pSpacer;
	
	
};
