// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "OverallSaveGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UOverallSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FPlayerSingleProgressInfo> m_allProgressInfos;

	UPROPERTY()
	TArray<FString> m_doneTutorialSteps;
};
