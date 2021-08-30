// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Base/Widget/WidgetManager.h"
#include "LoginWidgetManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API ULoginWidgetManager : public UWidgetManager
{
	GENERATED_BODY()
public:
	virtual void InputTextCommitCallback(FString text, FString function);
	
	
};
