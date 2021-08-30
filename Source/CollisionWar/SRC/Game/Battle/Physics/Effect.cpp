// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "PhysCalculator.h"
#include "Effect.h"





void UEffect::RecoverDefaultValues()
{
	m_duration = m_effectDefaultParam.duration;
	m_effectName = m_effectDefaultParam.effectName;
	m_effectValues = m_effectDefaultParam.effectValues;
	m_effectOnIntervalList = m_effectDefaultParam.effectOnIntervalList;
	m_isIntervalLoop = m_effectDefaultParam.isIntervalLoop;
	m_isPhysOrMag = m_effectDefaultParam.isPhysOrMag;
	m_isJudgeEffect = m_effectDefaultParam.isJudgeEffect;
	m_hitColors = m_effectDefaultParam.hitColors;
	m_hitNbs = m_effectDefaultParam.hitNbs;
	m_isPermenant = m_effectDefaultParam.isPermenant;
	m_canOverlap = m_effectDefaultParam.canOverlap;
	m_functionNames = m_effectDefaultParam.functionNames;
	m_isOnByEmbeddedEffect = true;
}

void UEffect::Copy(UEffect* pTargetEffect)
{
	if (!pTargetEffect) return;
	pTargetEffect->m_appendEffectList = m_appendEffectList;
	pTargetEffect->m_canOverlap = m_canOverlap;
	pTargetEffect->m_duration = m_duration;
	pTargetEffect->m_effectDefaultParam = m_effectDefaultParam;
	pTargetEffect->m_effectName = m_effectName;
	pTargetEffect->m_effectOnIntervalList = m_effectOnIntervalList;
	pTargetEffect->m_effectType = m_effectType;
	pTargetEffect->m_effectValues = m_effectValues;
	pTargetEffect->m_functionNames = m_functionNames;
	pTargetEffect->m_hitColors = m_hitColors;
	pTargetEffect->m_hitNbs = m_hitNbs;
	pTargetEffect->m_launchType = m_launchType;
	pTargetEffect->m_isIntervalLoop = m_isIntervalLoop;
	pTargetEffect->m_isJudgeEffect = m_isJudgeEffect;
	pTargetEffect->m_isPermenant = m_isPermenant;
	pTargetEffect->m_isPhysOrMag = m_isPhysOrMag;
	pTargetEffect->m_preconditionEffects = m_preconditionEffects;
	pTargetEffect->m_description = m_description;
}

