// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "EnermyGroup.h"




void UEnermyGroup::CorrectEnermyGroup(const FEnermyGroupCorrectInfo& groupInfo)
{
	isValid = groupInfo.isValid;
	m_pTrigger->m_isTriggerOnFlag = groupInfo.isTriggerOn;
	int32 preTotalSpawnPointNum = m_spawnPoints.Num();
	TArray<int32> foundSpawnPointNbs;
	for (int32 i = 0; i < groupInfo.spawnPointInfoList.Num(); i++)
	{
		bool foundSpawnPoint = false;
		for (int32 j = 0; j < m_spawnPoints.Num(); j++)
		{
			if (groupInfo.spawnPointInfoList[i].spawnPointNb == m_spawnPoints[j]->m_spawnPointNb)
			{
				foundSpawnPoint = true;
				foundSpawnPointNbs.Add(m_spawnPoints[j]->m_spawnPointNb);
				m_spawnPoints[j]->CorrectSpawnPoint(groupInfo.spawnPointInfoList[i]);
				break;
			}
		}
		if (!foundSpawnPoint)
		{
			//说明要加上对应的技能了，新技能都add在队列末端
			USpawnPoint* pNewPoint = NewObject<USpawnPoint>();
			m_spawnPoints.Add(pNewPoint);
			pNewPoint->CorrectSpawnPoint(groupInfo.spawnPointInfoList[i]);
		}
	}
	if (foundSpawnPointNbs.Num() != preTotalSpawnPointNum)
	{
		//说明原本有的组合多出来了
		int32 i = 0;
		while (i < m_spawnPoints.Num())
		{
			if (!foundSpawnPointNbs.Contains(m_spawnPoints[i]->m_spawnPointNb))
			{
				m_spawnPoints.RemoveAt(i);
			}
			else i++;
		}
	}
}
