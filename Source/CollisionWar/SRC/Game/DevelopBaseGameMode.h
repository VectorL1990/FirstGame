// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/CWBaseGameMode.h"
#include "DevelopBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ADevelopBaseGameMode : public ACWBaseGameMode
{
	GENERATED_BODY()
	
public:
	//virtual void BeginePlay() override;

	virtual void Destroyed() override;

	//virtual void installEvents() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onDevelopEvent1(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
	void onDevelopEvent2(const UKBEventData* pEventData);
};
