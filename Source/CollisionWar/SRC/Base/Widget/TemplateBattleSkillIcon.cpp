// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateBattleSkillIcon.h"




void UTemplateBattleSkillIcon::InitialSkillIcon(const FString& skillName, UImage* pMask)
{
	m_skillName = skillName;
	m_pMask = pMask;
}

void UTemplateBattleSkillIcon::UpdateSkillState()
{
	if (!m_pRelateSkill || !m_pMask) return;
	if (m_pRelateSkill->m_canImplementFlag) m_pMask->SetRenderOpacity(0);
	else m_pMask->SetRenderOpacity(1);
}
