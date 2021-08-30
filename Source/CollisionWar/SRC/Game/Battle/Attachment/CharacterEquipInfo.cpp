// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../BattleLevelGameModeBase.h"
#include "CharacterEquipInfo.h"



void UCharacterEquipInfo::CorrectEquipment(const FEquipmentInfo& equipInfo)
{
	for (int32 i=0; i<equipInfo.skillInfoList.Num(); i++)
	{
		for (int32 j=0; j<m_pSkills.Num(); j++)
		{
			if (equipInfo.skillInfoList[i].skillName == m_pSkills[j]->m_skillName)
			{
				m_pSkills[j]->CorrectSkill(equipInfo.skillInfoList[i]);
				break;
			}
		}
	}
}

void UCharacterEquipInfo::InitialEquipInfo(bool isPlayerCharacter)
{
	if (!isPlayerCharacter)
	{
		for (TMap<FString, TSubclassOf<class UBaseSkill> >::TConstIterator iter = m_skillClassMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			UBaseSkill* pSkill = NewObject<UBaseSkill>(this, iter->Value);
			pSkill->InitialSkill();
			m_pSkills.Add(pSkill);
		}
	}
	else
	{
		for (TMap<FString, TSubclassOf<class UBaseSkill> >::TConstIterator iter = m_skillClassMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			UBaseSkill* pSkill = NewObject<UBaseSkill>(this, iter->Value);
			pSkill->InitialSkill();
			m_pSkills.Add(pSkill);
			break;
		}
		for (int32 i=0; i<m_maxCardNb; i++)
		{
			m_pSkills.Add(NULL);
		}
	}
}

FEquipmentInfo UCharacterEquipInfo::ConstructEquipInfo()
{
	FEquipmentInfo info;
	info.equipmentName = m_equipmentName;
	for (int32 i=0; i<m_pSkills.Num(); i++)
	{
		FSkillInfo skillInfo = m_pSkills[i]->ConstructSkillInfo();
		info.skillInfoList.Add(skillInfo);
		if (skillInfo.skillName == "") skillInfo.skillName = "NULL";
	}
	if (info.equipmentName == "") info.equipmentName = "NULL";
	return info;
}

void UCharacterEquipInfo::AddSkill(FString skillName, int32 insertLoc, bool needToAddExtraCD)
{
	/*if (!m_skillClassMap.Contains(skillName) || !m_skillClassMap[skillName]) return;
	if (insertLoc < m_pSkills.Num() && !m_pSkills[insertLoc])
	{
		UBaseSkill* pSkill = NewObject<UBaseSkill>(this, m_skillClassMap[skillName]);
		pSkill->NotifyInitial();
		m_pSkills[insertLoc] = pSkill;
	}
	else if (insertLoc < m_pSkills.Num() && m_pSkills[insertLoc])
	{
		if (m_pSkills[insertLoc]->IsValidLowLevel())
		{
			m_pSkills[insertLoc]->ConditionalBeginDestroy();
		}
	}
	//m_pSkills.Insert(pSkill, insertLoc);
	if (needToAddExtraCD)
	{
		pSkill->m_canImplementFlag = false;
		AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
		pSkill->m_skillFrameCount -= pBattleGameMode->m_extraCDWhenSwitchSkill;
	}*/
}
