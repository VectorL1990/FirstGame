// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Battle/MapGenerator.h"
#include "TestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONWAR_API ATestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void DrawAllTiles();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void GenRogueMap();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMapGenerator * m_pMapGenerator;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_defaultHeight;
};
