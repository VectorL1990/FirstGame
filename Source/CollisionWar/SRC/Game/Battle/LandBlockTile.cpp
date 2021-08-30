// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "LandBlockTile.h"




void ULandBlockTile::SetTileInfos(FString blockName, TArray<FString> physActorNames, 
	TArray<int32> physActorXs, TArray<int32> physActorYs, TArray<int32> physActorYaws, TArray<FString> dumpActorNames, 
	TArray<int32> dumpActorXs, TArray<int32> dumpActorYs, TArray<int32> dumpActorYaws, TArray<FString> spawnPointNames, TArray<int32> spawnPoinXs,
	TArray<int32> spawnPointYs, TArray<int32> spawnPointYaws, TArray<FString> staticMeshNames, TArray<int32> staticMeshXs,
	TArray<int32> staticMeshYs, TArray<int32> staticMeshZs, TArray<int32> staticMeshYaws,TArray<float> staticMeshScales)
{
	m_landBlockName = blockName;
	m_physActorNames = physActorNames;
	for (int32 i=0; i<physActorXs.Num(); i++)
	{
		FLogicVec2D loc(physActorXs[i], physActorYs[i]);
		m_physActorSpawnLocs.Add(loc);
	}
	m_physActorSpawnYaws = physActorYaws;
	m_dumpActorNames = dumpActorNames;
	for (int32 i=0; i<dumpActorXs.Num(); i++)
	{
		FLogicVec2D loc(dumpActorXs[i], dumpActorYs[i]);
		m_dumpActorSpawnLocs.Add(loc);
	}
	m_dumpActorSpawnYaws = dumpActorYaws;
	m_planSpawnPointNames = spawnPointNames;
	for (int32 i=0; i<spawnPoinXs.Num(); i++)
	{
		FLogicVec2D loc(spawnPoinXs[i], spawnPointYs[i]);
		m_planSpawnPointLocs.Add(loc);
	}
	m_planSpawnPointYaws = spawnPointYaws;
	m_staticMeshActorNameList = staticMeshNames;
	for (int32 i = 0; i < staticMeshXs.Num(); i++)
	{
		FLogicVec3D loc(staticMeshXs[i], staticMeshYs[i], staticMeshZs[i]);
		m_staticMeshLocs.Add(loc);
	}
	m_staticMeshYaws = staticMeshYaws;
	m_staticMeshScales = staticMeshScales;
}
