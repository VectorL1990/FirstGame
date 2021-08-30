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
	* �ȸ������������Σ���ȼ�ȷ��Ҫ���ɵĶ�ӦLevel������������Σ���ȼ�5Ҫ����3��������3��
	* ��ʱҪ�����жϣ��ж�Ԥ����Ϣ���Ƿ�����涨��������Ϣ������Ԥ����Ϣ�й涨Σ���ȼ�5ֻ������2��3��������
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

	/** ��������Ҫ���ж�Σ���ȼ�����Σ���ȼ�Ϊ1��˵����С�߷壬
	*��Σ���ȼ�����1��˵���Ǵ�߷壬��ʱ�ȸ������������Թ涨�������ɵĵ��˽����жϣ�����涨��Σ��1������½���������ʱ�ֽ�½������뵽���ɶ�����
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
	/** ��GameModeֱ�ӵ���
	* �Ƿ��������Σ���з�ֵ��ֻ������Ϸ���̾�������ʵ��Σ���ȼ��޹�
	* //��Σ���з�ֵ���Ƿ������ʵ��Σ���ȼ���Ԥ����СΣ���ڹ�ͬ����
	*/
	//��m_expectToPeakΪfalse��˵��Σ���еȼ���ߵ���Ҵ�ʱ������ƽ���ڣ�����Ҫ�����κε���
	if (m_curPeakNb >= m_peakIntervalList.Num()) return;
	if (!m_expectToPeak)
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
		if (pBLGM->m_curLogicFrameNb >= m_peakIntervalList[m_curPeakNb])
		{
			//��ʱ����Ѿ��ȹ�ƽ���ڣ���Ҫ����Σ���з�ֵ�ڣ����ü�ʱ��
			ResetAllParams();
			m_expectToPeak = true;
			//m_isFirstSpawnDone = true;
			m_curPeakNb += 1;
			//m_curPeakIntervalFrameCount += 1;
		}
	}
	

	/**
	* ˵����ʱ��ֵ�ڸտ�ʼ���ȼ�������͵�����Ҫ���ɵ�����
	* �ٸ������ɼ���������������η���
	*/
	if ((m_expectToPeak && m_curPeakFrameCount == 0))
	{
		//m_curMiniPeakIntervalFrameCount = 0;
		int32 curProgress = curFrame * 100 / maxFrame;
		//��������Σ���еȼ�
		int32 expectCrisisGrade = GetExpectCrisisGrade(m_expectToPeak, curProgress);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::FromInt(expectCrisisGrade));
		m_curSpawnIntervalFrameCount = m_spawnInterval;
		/**
		* һ��ս���ڿ��ܴ��ڶ�֧���飬Ҫ����ÿ֧�������е������Լ��涨���������ޣ�������ÿ֧���黹Ҫ���ɶ��ٸ���ͬ���Ľ�ɫ
		* ��Ҫ����������Σ���еȼ������㣬����3��Σ������2��Σ����Ҫ�����ɵĽ�ɫ�����ǲ�һ����
		*/
		for (int32 i=0; i<m_expectToSpawnList.Num(); i++)
		{
			GetSpawnNameListAccordToCrisisGrade(i,expectCrisisGrade);
		}
	}

	if ((m_expectToPeak && m_curPeakFrameCount >= m_peakFrameSpan))
	{
		/**
		* ֻ�е���ǰ��ֵ�ڼ�ʱ����Ԥ������ʱ����������Σ���з�ֵ�ڽ�������ʼ�ȴ���һ�η�ֵ��
		* �绹����Σ���з�ֵ�ڣ�������������ж�
		* ���Ѿ�������ֵ�ڿ�ȣ���������������б�
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
	* �����ÿ֧������Ҫ���ɵĽ�ɫ�����󣬼��ɿ�ʼ��ʱ���������ɽ�ɫ
	* �����ɼ�����̣��п��ܳ���һ������û������ʱ������������һ�����ˣ���ʱ����᲻�����ɵ���
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

