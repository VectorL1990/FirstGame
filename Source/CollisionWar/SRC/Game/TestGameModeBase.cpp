// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Common/CollisionWarBpFunctionLibrary.h"
#include "Battle/Physics/BasePhysGeo.h"
#include "Battle/Physics/DumpPhysActor.h"
#include "TestGameModeBase.h"




void ATestGameModeBase::DrawAllTiles()
{
	/*if (!m_pMapGenerator) return;
	if (m_pMapGenerator->m_pTiles.Num() == 0) return;
	for (int32 i=0; i<m_pMapGenerator->m_pTiles.Num(); i++)
	{
		float ldX = m_pMapGenerator->m_leftDownCornerCoord.X + m_pMapGenerator->m_pTiles[i]->X*m_pMapGenerator->m_tileWidth;
		float ldY = m_pMapGenerator->m_leftDownCornerCoord.Y + m_pMapGenerator->m_pTiles[i]->Y*m_pMapGenerator->m_tileHeight;
		float rtX = m_pMapGenerator->m_leftDownCornerCoord.X + (m_pMapGenerator->m_pTiles[i]->X + 1)*m_pMapGenerator->m_tileWidth;
		float rtY = m_pMapGenerator->m_leftDownCornerCoord.Y + (m_pMapGenerator->m_pTiles[i]->Y + 1)*m_pMapGenerator->m_tileHeight;
		FVector ldPt(ldX, ldY, m_defaultHeight);
		FVector rtPt(rtX, rtY, m_defaultHeight);
		if (m_pMapGenerator->m_pTiles[i]->m_landBlockType == "junction")
		{
			DrawDebugLine(GetWorld(), ldPt, rtPt, FColor::Blue, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(ldX, rtY, m_defaultHeight), FColor::Blue, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Blue, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Blue, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, rtY, m_defaultHeight), FColor::Blue, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(rtX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Blue, false, 100, 0, 10);
		}
		else if (m_pMapGenerator->m_pTiles[i]->m_landBlockType == "connect")
		{
			DrawDebugLine(GetWorld(), ldPt, rtPt, FColor::Green, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(ldX, rtY, m_defaultHeight), FColor::Green, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Green, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Green, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, rtY, m_defaultHeight), FColor::Green, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(rtX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Green, false, 100, 0, 10);
		}
		else if (m_pMapGenerator->m_pTiles[i]->m_landBlockType == "specified")
		{
			DrawDebugLine(GetWorld(), ldPt, rtPt, FColor::Red, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(ldX, rtY, m_defaultHeight), FColor::Red, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Red, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Red, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, rtY, m_defaultHeight), FColor::Red, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(rtX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Red, false, 100, 0, 10);
		}
		else if (m_pMapGenerator->m_pTiles[i]->m_landBlockType == "special")
		{
			DrawDebugLine(GetWorld(), ldPt, rtPt, FColor::Yellow, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(ldX, rtY, m_defaultHeight), FColor::Yellow, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Yellow, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Yellow, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, rtY, m_defaultHeight), FColor::Yellow, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(rtX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::Yellow, false, 100, 0, 10);
		}
		else if (m_pMapGenerator->m_pTiles[i]->m_landBlockType == "Barrier")
		{
			DrawDebugLine(GetWorld(), ldPt, rtPt, FColor::White, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(ldX, rtY, m_defaultHeight), FColor::White, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, ldY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::White, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::White, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(ldX, rtY, m_defaultHeight), FVector(rtX, rtY, m_defaultHeight), FColor::White, false, 100, 0, 10);
			DrawDebugLine(GetWorld(), FVector(rtX, rtY, m_defaultHeight), FVector(rtX, ldY, m_defaultHeight), FColor::White, false, 100, 0, 10);
		}
	}*/
}

void ATestGameModeBase::GenRogueMap()
{
	/*if (!m_pMapGenerator) return;
	m_pMapGenerator->InitialMapGeneratorFromBlueprint();
	m_pMapGenerator->GenerateRandomMap();
	for (int32 i=0; i<m_pMapGenerator->m_pTiles.Num(); i++)
	{
		for (int32 j=0; j<m_pMapGenerator->m_pTiles[i]->m_physActorNames.Num(); j++)
		{
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].Y, m_defaultHeight);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_physActorSpawnYaws[j], 0);
			UClass* geoClass = UCollisionWarBpFunctionLibrary::GetPhysGeoBlueprintClassDynamic(m_pMapGenerator->m_pTiles[i]->m_physActorNames[j]);
			ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(geoClass, spawnLoc, spawnRot);
		}
		for (int32 j = 0; j < m_pMapGenerator->m_pTiles[i]->m_dumpActorNames.Num(); j++)
		{
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].Y, m_defaultHeight);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnYaws[j], 0);
			UClass* geoClass = UCollisionWarBpFunctionLibrary::GetDumpActorBlueprintClassDynamic(m_pMapGenerator->m_pTiles[i]->m_dumpActorNames[j]);
			ADumpPhysActor* pGeo = GetWorld()->SpawnActor<ADumpPhysActor>(geoClass, spawnLoc, spawnRot);
		}
	}*/
}
