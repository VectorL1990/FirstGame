// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../BattleLevelGameModeBase.h"
#include "AIManager.h"


int32 UAIManager::GetExpectCrisisGrade(bool isMainPeak, int32 curProgress)
{
	if (isMainPeak)
	{
		if (curProgress <= 20) return 2;
		else if (curProgress <= 40) return 3;
		else if (curProgress <= 80) return 4;
		else return 5;
	}
	else return 1;
}

void UAIManager::InitialAIManager(TArray<int32> campFlags, int32 curProgress, uint8 difficulty)
{
	m_curProgress = curProgress;
	m_firstMiniPeakInterval = m_battleInfo.firstMiniPeakInterval;
	m_firstPeakInterval = m_battleInfo.firstPeakInterval;
	m_miniPeakInterval = m_battleInfo.miniPeakInterval;
	m_peakInterval = m_battleInfo.peakInterval;
	m_peakIntervalList = m_battleInfo.intervalList;
	m_difficulty = difficulty;
	for (int32 i=0; i<campFlags.Num(); i++)
	{
		FGradingExpectToSpawnInfo newExpectSpawnInfo;
		newExpectSpawnInfo.campFlag = campFlags[i];
		m_expectToSpawnList.Add(newExpectSpawnInfo);
	}
	GetSpecialStateNames();
}

void UAIManager::InitialGradingNameList_Implementation()
{

}

void UAIManager::GetSpawnNameListAccordToCrisisGrade(int32 groupNb, int32 expectCrisisGrade)
{
	/**
	* 先根据随机出来的危机等级确定要生成的对应Level的组数，例如危机等级5要生成3级敌人组3个
	* 这时要进行判断，判断预定信息中是否包含规定的生成信息，例如预定信息中规定危机等级5只能生成2个3个敌人组
	*/
	/*FGradingEnermySpawnInfo gradingEnermySpawnInfo;
	bool getFixGradeInfo = false;
	for (int32 i=0; i<m_battleInfo.fixGradingList.Num(); i++)
	{
		if (m_battleInfo.fixGradingList[i].grade != expectCrisisGrade) continue;
		gradingEnermySpawnInfo = m_battleInfo.fixGradingList[i];
		getFixGradeInfo = true;
		break;
	}*/
	/*if (!getFixGradeInfo)
	{
		for (int32 i = 0; i < m_enermySpawnListInfo.Num(); i++)
		{
			if (m_enermySpawnListInfo[i].grade == expectCrisisGrade)
			{
				gradingEnermySpawnInfo = m_enermySpawnListInfo[i];
				break;
			}
		}
	}*/

	/** 在这里需要先判断危机等级，如危机等级为1，说明是小高峰，
	*如危机等级大于1，说明是大高峰，这时先根据生成轮数对规定必须生成的敌人进行判断，例如规定在危机1级生成陆行鸟组别，这时现将陆行鸟加入到生成队列中
	*/
	//TMap<int32, int32> fixEnermyGroupNbMap;
	if (m_curPeakNb - 1 < m_battleInfo.fixEnermyGroupGradeList.Num())
	{
		if (m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList.Num() <= 0) return;
		int32 randNb = FMath::RandRange(0, m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList.Num() - 1);
		for (int32 i=0; i< m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list.Num(); i++)
		{
			if (!m_allLevelCharacterGroups.Contains(m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].characterGroupName)) continue;
			int32 scaleNb = m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].Nb;
			for (int32 j = 0; j < m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].characterGroupName].characterNameList.Num(); j++)
			{
				FCharacterSpawnInfo spawnInfo;
				spawnInfo.characterName = m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].characterGroupName].characterNameList[j];
				spawnInfo.spawnNb = (m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].characterGroupName].numList[j] * scaleNb * m_spawnAmplificationCoe) / 100 +
					m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeList[m_curPeakNb - 1].possibleList[randNb].list[i].characterGroupName].numList[j] * scaleNb;
				m_expectToSpawnList[groupNb].expectSpawnNameList.Add(spawnInfo);
				/*if (fixEnermyGroupNbMap.Contains(m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeMap[expectCrisisGrade].list[i].characterGroupName].level))
					fixEnermyGroupNbMap[m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeMap[expectCrisisGrade].list[i].characterGroupName].level] += 1;
				else
					fixEnermyGroupNbMap.Add(m_allLevelCharacterGroups[m_battleInfo.fixEnermyGroupGradeMap[expectCrisisGrade].list[i].characterGroupName].level, 1);*/
			}
		}
	}
	/*for (int32 i=0; i< gradingEnermySpawnInfo.levelList.Num(); i++)
	{
		TArray<FCharacterGroup> characterGroups;
		for (TMap<FString, FCharacterGroup>::TConstIterator iter = m_allLevelCharacterGroups.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.level == gradingEnermySpawnInfo.levelList[i] && iter->Value.suitableProgress == m_curProgress)
				characterGroups.Add(iter->Value);
		}
		int32 groupNb = gradingEnermySpawnInfo.groupNbList[i];
		if (fixEnermyGroupNbMap.Contains(gradingEnermySpawnInfo.levelList[i]))
			groupNb -= fixEnermyGroupNbMap[gradingEnermySpawnInfo.levelList[i]];
		for (int32 j=0; j<groupNb; j++)
		{
			int32 randGroupNb = FMath::RandRange(0, characterGroups.Num() - 1);
			for (int32 k = 0; k < characterGroups[randGroupNb].characterNameList.Num(); k++)
			{
				FCharacterSpawnInfo spawnInfo;
				spawnInfo.characterName = characterGroups[randGroupNb].characterNameList[k];
				spawnInfo.spawnNb = (characterGroups[randGroupNb].numList[k] * m_spawnAmplificationCoe)/100 + characterGroups[randGroupNb].numList[k];
				m_expectToSpawnList[groupNb].expectSpawnNameList.Add(spawnInfo);
			}
		}
	}*/
}

void UAIManager::GetSpawnNameList(int32 curFrame, int32 maxFrame, TArray<FGradingExpectToSpawnInfo>& allTeamExpectSpawnList, int32 mainCampFlag)
{
	/** 由GameMode直接调用
	* 是否进入期望危机感峰值期只能由游戏进程决定，跟实际危机等级无关
	* //但危机感峰值期是否结束由实际危机等级和预设最小危机期共同决定
	*/
	//如m_expectToPeak为false，说明危机感等级最高的玩家此时还处于平静期，不需要生成任何敌人
	if (m_curPeakNb >= m_peakIntervalList.Num()) return;
	if (!m_expectToPeak)
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
		if (pBLGM->m_curLogicFrameNb >= m_peakIntervalList[m_curPeakNb])
		{
			//此时玩家已经度过平静期，需要进入危机感峰值期，重置计时器
			ResetAllParams();
			m_expectToPeak = true;
			//m_isFirstSpawnDone = true;
			m_curPeakNb += 1;
			//m_curPeakIntervalFrameCount += 1;
		}
	}
	

	/**
	* 说明这时峰值期刚开始，先计算各类型敌人需要生成的总数
	* 再根据生成间隔计算敌人生成如何分配
	*/
	if ((m_expectToPeak && m_curPeakFrameCount == 0))
	{
		//m_curMiniPeakIntervalFrameCount = 0;
		int32 curProgress = curFrame * 100 / maxFrame;
		//计算期望危机感等级
		int32 expectCrisisGrade = GetExpectCrisisGrade(m_expectToPeak, curProgress);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::FromInt(expectCrisisGrade));
		m_curSpawnIntervalFrameCount = m_spawnInterval;
		/**
		* 一场战斗内可能存在多支队伍，要根据每支队伍现有的人数以及规定的人数上限，来计算每支队伍还要生成多少个不同类别的角色
		* 还要根据期望的危机感等级来计算，例如3级危机感与2级危机感要求生成的角色数量是不一样的
		*/
		for (int32 i=0; i<m_expectToSpawnList.Num(); i++)
		{
			GetSpawnNameListAccordToCrisisGrade(i,expectCrisisGrade);
		}
	}

	if ((m_expectToPeak && m_curPeakFrameCount >= m_peakFrameSpan))
	{
		/**
		* 只有当当前峰值期计时超过预定长度时，才能宣布危机感峰值期结束，开始等待下一次峰值期
		* 如还处于危机感峰值期，忽略以下这个判断
		* 如已经超过峰值期跨度，则清空所有生成列表
		*/
		m_expectToPeak = false;
		//m_expectToMiniPeak = false;
		m_curPeakFrameCount = 0;
		m_curSpawnIntervalFrameCount = 0;
		for (int32 i = 0; i < m_expectToSpawnList.Num(); i++)
		{
			m_expectToSpawnList[i].expectSpawnNameList.Empty();
		}
		m_peakCount += 1;
		return;
	}
	m_curPeakFrameCount += 1;
	
	
	/**
	* 当获得每支队伍需要生成的角色名单后，即可开始分时间间隔段生成角色
	* 如生成间隔过短，有可能出现一波敌人没生成完时接下来又生成一波敌人，此时按理会不断生成敌人
	*/
	if (m_curSpawnIntervalFrameCount >= m_spawnInterval)
	{
		for (int32 j = 0; j < m_expectToSpawnList.Num(); j++)
		{
			FGradingExpectToSpawnInfo expectSpawnInfo;
			expectSpawnInfo.campFlag = m_expectToSpawnList[j].campFlag;
			int32 i = 0;
			while (m_expectToSpawnList[j].expectSpawnNameList.Num() > 0)
			{
				if (i >= m_maxSpawnEnermyNb) break;
				expectSpawnInfo.expectSpawnNameList.Add(m_expectToSpawnList[j].expectSpawnNameList[0]);
				m_expectToSpawnList[j].expectSpawnNameList.RemoveAt(0);
				//i += 1;
			}
			allTeamExpectSpawnList.Add(expectSpawnInfo);
		}
		m_curSpawnIntervalFrameCount = 0;
	}
	else m_curSpawnIntervalFrameCount += 1;
}

void UAIManager::AssignSpecialEffectToCharacters(const TArray<FString>& spawnNameList, TMap<int32, FPreAssignEffectList>& effectNameList)
{
	if (spawnNameList.Num() == 0) return;
	int32 assignCharacterNum = spawnNameList.Num() * m_specialEffectPercent / 100;
	if (assignCharacterNum <= 0) assignCharacterNum = spawnNameList.Num();
	TArray<int32> characterNbList;
	for (int32 i=0; i<spawnNameList.Num(); i++)
	{
		characterNbList.Add(i);
	}
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
	for (int32 i=0; i<assignCharacterNum; i++)
	{
		if (characterNbList.Num() <= 0) break;
		int32 randPickNb = FMath::RandRange(0, characterNbList.Num() - 1);
		characterNbList.RemoveAt(randPickNb);
		TArray<FString> availableEffectNames;
		for (int32 j=0; j<m_permenantSpecialEffectNames.Num(); j++)
		{
			/*if (m_permenantSpecialEffectNames[j].lowGrade > pBLGM->m_allCharacterInfo[spawnNameList[randPickNb]].grade ||
				m_permenantSpecialEffectNames[j].upGrade < pBLGM->m_allCharacterInfo[spawnNameList[randPickNb]].grade)
				continue;*/
			availableEffectNames.Add(m_permenantSpecialEffectNames[j].stateName);
		}

		int32 preAssignEffectNb = FMath::RandRange(1, m_maxPreAssignEffectNb);
		FPreAssignEffectList effectList;
		for (int32 j=0; j<preAssignEffectNb; j++)
		{
			if (availableEffectNames.Num() <= 0) break;
			int32 randSpecialStateNb = FMath::RandRange(0, availableEffectNames.Num() - 1);
			FString randSpecialEffectName = availableEffectNames[randSpecialStateNb];
			effectList.list.Add(randSpecialEffectName);
			availableEffectNames.RemoveAt(randSpecialStateNb);
		}
		if (effectList.list.Num() > 0)
			effectNameList.Add(randPickNb, effectList);
	}
}

void UAIManager::ResetAllParams()
{
	//m_curPeakIntervalFrameCount = 0;
	m_curMiniPeakIntervalFrameCount = 0;
	m_expectToPeak = false;
	m_expectToMiniPeak = false;
	m_curPeakFrameCount = 0;
	m_curSpawnIntervalFrameCount = 0;
	for (int32 i = 0; i < m_expectToSpawnList.Num(); i++)
	{
		m_expectToSpawnList[i].expectSpawnNameList.Empty();
	}
}

