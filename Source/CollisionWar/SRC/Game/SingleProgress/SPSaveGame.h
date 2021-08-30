// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayCard.h"
#include "EventCard.h"
#include "ShadowActor.h"
#include "SPSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FEventCardSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FVector loc;

	UPROPERTY()
		uint8 cardType;

	UPROPERTY()
		FEventCardInfo cardInfo;

	UPROPERTY()
	int32 id;
};

UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API USPSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	void Reset();

	UPROPERTY()
	TArray<FActionNodeBriefInfoList> m_actionNodeList;

	UPROPERTY()
	int32 m_curEventNodeNb;

	UPROPERTY()
	int32 m_curEventNodeLayerNb;

	UPROPERTY()
	TArray<FEventCardSaveInfo> m_eventCardSaveInfos;

	UPROPERTY()
	bool m_isInBossBattleLayer = false;

	UPROPERTY()
		TArray<int32> m_curAvailableNodeIDs;

	UPROPERTY()
	int32 m_curDayNb;
};
