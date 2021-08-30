// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Game/Battle/Physics/Effect.h"
#include "../Game/Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "../Game/Battle/RoguelikeBattleGameMode.h"
#include "EventSystemFunLib.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API UEventSystemFunLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	static void SpawnEffectToPlayer(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);

	static void SpawnGeo(FEffectParams& param, ABasePhysActor* pPhysActor);

	static void SpawnEffectToType(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);

	static void GetResources(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);

	static void IncreaseEquipCardNbByAppendString(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);

	static void GetResourcesByEquipCardAppendString(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);

	static void TradeDiscount(FEffectParams& param, ARoguelikeBattleGameMode* pRGM);
};
