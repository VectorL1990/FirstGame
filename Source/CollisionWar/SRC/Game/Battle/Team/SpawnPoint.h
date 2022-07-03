// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../Character/BaseCharacter.h"
#include "../../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API USpawnPoint : public UObject
{
	GENERATED_BODY()
public:

	/************************************************************************/
	/* ��ʼ������
	/************************************************************************/
	UPROPERTY()
	int32 m_spawnPointNb;

	UPROPERTY()
	FLogicVec2D m_logicDefLoc;

	UPROPERTY()
	int32 m_logicYaw = 0;

	UPROPERTY()
	int32 m_defendRadius = 0;

	UPROPERTY()
	TArray<FString> m_spawnTypes;

	UPROPERTY()
	bool m_isCirculate = false;

	UPROPERTY()
	int32 m_frameInterval = 0;
	/************************************************************************/
	/* ���ڲ��ϱ仯����
	/************************************************************************/
	UPROPERTY()
	int32 m_curSpawnRound = 0;

	UPROPERTY()
	int32 m_curFrame = 0;

	UPROPERTY()
	ABaseCharacter* m_pCurSpawnCharacter = NULL;
	/************************************************************************/
	/* У����ʱ����
	/************************************************************************/
	UPROPERTY()
	int32 m_curSpawnCharacterID;
};
