// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "LogicFrameInfo.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API ULogicFrameInfo : public UObject
{
	GENERATED_BODY()

public:
	int32 m_frameNb = 0;
	int32 m_roundNb = 0;
	TArray<FPlayerOperationInfo> m_playerOperationList;
	TArray<FAICharacterOperationInfo> m_AIOperationList;
};
