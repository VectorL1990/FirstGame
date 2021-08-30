// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../Character/BaseCharacter.h"
#include "BaseSkill.h"




UBaseSkill::UBaseSkill(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	m_canImplementFlag = true;
	m_pDetectComponent = NULL;
}

void UBaseSkill::InitialSkill()
{
	
}

void UBaseSkill::CorrectSkill(const FSkillInfo& skillInfo)
{
	/*m_canImplementFlag = skillInfo.canImplement;
	m_skillFrameCount = skillInfo.curFreezeFrame;
	m_hasSpawnGeo = skillInfo.hasSpawnGeo;*/
}

FSkillInfo UBaseSkill::ConstructSkillInfo()
{
	FSkillInfo info;
	info.skillName = m_skillName;
	info.canImplement = m_canImplementFlag;
	info.curFreezeFrame = m_skillFrameCount;
	info.hasSpawnGeo = m_hasSpawnGeo;
	return info;
}

