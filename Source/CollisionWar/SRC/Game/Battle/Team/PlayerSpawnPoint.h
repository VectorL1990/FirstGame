// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "PlayerSpawnPoint.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UPlayerSpawnPoint : public UObject
{
	GENERATED_BODY()
public:
	
	FLogicVec2D m_logicSpawnLoc;

	int32 m_logicSpawnYaw = 0;

	int32 m_spawnPointNb = 0;

	int32 m_campFlag = 0;
};
