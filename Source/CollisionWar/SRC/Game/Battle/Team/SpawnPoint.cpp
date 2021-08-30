// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "SpawnPoint.h"




void USpawnPoint::CorrectSpawnPoint(const FEnermySpawnPointCorrectInfo& enermySpawnPointInfo)
{
	m_curFrame = enermySpawnPointInfo.curFrame;
	m_curSpawnCharacterID = enermySpawnPointInfo.curSpawnCharacterID;
	m_curSpawnRound = enermySpawnPointInfo.curSpawnRound;
}
