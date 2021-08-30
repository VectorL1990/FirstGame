// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "PlanSpawnPoint.h"
#include "LandBlockTile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API ULandBlockTile : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetTileInfos(FString blockName, TArray<FString> physActorNames, TArray<int32> physActorXs,
		TArray<int32> physActorYs, TArray<int32> physActorYaws, TArray<FString> dumpActorNames, TArray<int32> dumpActorXs,
		TArray<int32> dumpActorYs, TArray<int32> dumpActorYaws, TArray<FString> spawnPointNames, TArray<int32> spawnPoinXs,
		TArray<int32> spawnPointYs, TArray<int32> spawnPointYaws, TArray<FString> staticMeshNames, TArray<int32> staticMeshXs,
		TArray<int32> staticMeshYs, TArray<int32> staticMeshZs, TArray<int32> staticMeshYaws, TArray<float> staticMeshScales);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 X;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 Y;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	bool m_isOccupied = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_landBlockName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	FString m_landBlockType;

	/************************************************************************/
	/* physActor的所有生成信息                                                                     */
	/************************************************************************/

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FString> m_physActorNames;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FLogicVec2D> m_physActorSpawnLocs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<int32> m_physActorSpawnYaws;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_physActorSpawnLocInWorldSpace;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	int32 m_actorSpawnYaw;

	/************************************************************************/
	/* dumpActor的所有生成信息                                                                     */
	/************************************************************************/

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_dumpActorNames;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_dumpActorSpawnLocs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<int32> m_dumpActorSpawnYaws;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_dumpActorSpawnLocInWorldSpace;
	/************************************************************************/
	/* dumpActor的所有生成信息                                                                     */
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_planSpawnPointNames;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_planSpawnPointLocs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<int32> m_planSpawnPointYaws;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_planSpawnPointLocInWorldSpace;
	/************************************************************************/
	/* SpawnPoint列表信息
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<APlanSpawnPoint*> m_pSpawnPoints;

	/************************************************************************/
	/* staticMeshActor的所有生成信息                                                                     */
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> m_staticMeshActorNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec3D> m_staticMeshLocs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<int32> m_staticMeshYaws;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<float> m_staticMeshScales;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FLogicVec2D> m_staticMeshLocInWorldSpace;
};
