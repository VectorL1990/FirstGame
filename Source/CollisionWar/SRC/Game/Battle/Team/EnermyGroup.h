// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "SpawnPoint.h"
#include "../Physics/Trigger/BaseTrigger.h"
#include "../../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "EnermyGroup.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UEnermyGroup : public UObject
{
	GENERATED_BODY()
public:
	/************************************************************************/
	/* ��ʼ���ؿ�ʱ�ɷ��ı���
	/************************************************************************/
	UPROPERTY()
	int32 m_campFlag;

	UPROPERTY()
	int32 m_groupNb;

	UPROPERTY()
	FString m_spawnType;

	/************************************************************************/
	/* �����ڲ��ϱ仯�ı���
	/************************************************************************/
	UPROPERTY()
	ABaseTrigger* m_pTrigger;

	UPROPERTY()
	bool isValid = true;

	UPROPERTY()
	TArray<USpawnPoint*> m_spawnPoints;


	TArray<ABaseCharacter*> m_pCounterCharacters;
};
