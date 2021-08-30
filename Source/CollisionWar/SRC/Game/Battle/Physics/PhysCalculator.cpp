// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Battle/RoguelikeBattleGameMode.h"
#include "../../../Base/Battle/BattleLevelPlayerController.h"
#include "../../../Common/EffectFunLib.h"
#include "../../../Base/CollisionWarGameInstance.h"
#include "../../../Common/CollisionWarSingleton.h"
#include "PhysCalculator.h"

// Sets default values
APhysCalculator::APhysCalculator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_initialPhys = false;
}

// Called when the game starts or when spawned
void APhysCalculator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
/*
void APhysCalculator::Tick( float DeltaTime )
{
Super::Tick( DeltaTime );

if (m_initialPhys && !m_isAnalyzingFlag)
{
m_isAnalyzingFlag = true;
if (m_isPVPFlag)
{
BlockAnalysis(m_pAttackTeamAI);
BlockAnalysis(m_pDefendTeamAI);
PaoLineAnalysis();
}
UpdateGeoPair();
for (int32 i=0; i<m_pPhysActors.Num(); i++)
{
DrawDebugPoint(GetWorld(), m_pPhysActors[i]->GetActorLocation(), 10, FColor::Yellow, false, 0.1);
}
m_isAnalyzingFlag = false;
}
}*/

void APhysCalculator::AddPlayerToList(ABaseCharacter* pCharacter)
{
	//pCharacter->m_characterDeleteGeoDelegate.AddDynamic(this, &APhysCalculator::CharacterCallDeleteGeo);
	//pCharacter->m_characterCollectPhysActorDelegate.AddDynamic(this, &APhysCalculator::CharacterCallCollectPhysActor);
	m_pCharacterList.Add(pCharacter);
}

void APhysCalculator::InitialPhys()
{
	m_initialPhys = true;
	ReadAllPreAssignEffectParams();
	ReadDefaultAttributeReactionInfos();
}

void APhysCalculator::AddStateToCharacter(ABaseCharacter* pCharacter, FString stateName)
{
	UEffectFunLib::AddStateToCharacter(pCharacter, stateName);
}

void APhysCalculator::ReadDefaultAttributeReactionInfos_Implementation()
{

}

void APhysCalculator::ReadAllPreAssignEffectParams_Implementation()
{

}

void APhysCalculator::ReqCombineItem()
{
	if (!m_pRGM || !m_pRGM->m_pPlayerCharacter) return;
	if (m_pRGM->m_playerOperation.actionName != "NULL") return;
	m_pRGM->m_playerOperation.actionName = TEXT("CombineItem");
}

void APhysCalculator::ActivatePassiveEffects(UEffect* pIntroEffect, ABaseCharacter* pCharacter)
{
	if (!pCharacter || !pIntroEffect) return;
	TArray<FString> introEffectAppendNames;
	//将主动效果连带附加的效果名称全部集中在一个数组中
	introEffectAppendNames.Add(pIntroEffect->m_effectName);
	for (int32 i=0; i<pIntroEffect->m_appendEffectList.Num(); i++)
	{
		introEffectAppendNames.Add(pIntroEffect->m_appendEffectList[i].effectName);
	}
	//再对目标角色的被动技能逐个进行判断，看每个被动效果的前提技能名数组是否都包含上述主动效果的所有效果名
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectType != "PassiveActivate" || pCharacter->m_pEffects[i]->m_isOnTimeEffectDone) continue;
		bool isActive = true;
		for (int32 j=0; j< pCharacter->m_pEffects[i]->m_preconditionEffects.Num(); j++)
		{
			for (int32 k=0; k< pCharacter->m_pEffects[i]->m_preconditionEffects[j].effectNameList.Num(); k++)
			{
				if (!introEffectAppendNames.Contains(pCharacter->m_pEffects[i]->m_preconditionEffects[j].effectNameList[k]))
				{
					isActive = false;
					break;
				}
			}
		}
	}
}

void APhysCalculator::AppendSuperpositionEffects(ABasePhysGeo* pIntroGeo)
{
	if (!pIntroGeo || !pIntroGeo->m_pHost) return;
	//将主动效果连带附加的效果名称全部集中在一个数组中
	TArray<FString> introGeoAppendEffectNameList;
	//TArray<FEffectParams> pIntroGeo->m_effectParamList;
	/*if (pIntroGeo->m_enhanceType == -1) effectParamList = pIntroGeo->m_effectParamList;
	else
	{
		if (pIntroGeo->m_mutationEffectParamList.Contains((uint8)pIntroGeo->m_enhanceType))
			effectParamList = pIntroGeo->m_mutationEffectParamList[(uint8)pIntroGeo->m_enhanceType];
	}*/
	for (int32 i=0; i<pIntroGeo->m_effectParamList.Num(); i++)
	{
		introGeoAppendEffectNameList.Add(pIntroGeo->m_effectParamList[i].effectName);
		for (uint8 j=0; j<pIntroGeo->m_effectParamList[i].appendEffectList.Num(); j++)
		{
			introGeoAppendEffectNameList.Add(pIntroGeo->m_effectParamList[i].appendEffectList[j].effectName);
		}

		/*for (int32 j = 0; j < pIntroGeo->m_pHost->m_pEffects.Num(); j++)
		{
			if (pIntroGeo->m_pHost->m_pEffects[j]->m_effectType != "SuperposeEffect") continue;
			bool isActive = false;
			for (int32 k = 0; k < pIntroGeo->m_pHost->m_pEffects[j]->m_preconditionEffects.Num(); k++)
			{
				bool isContain = true;
				for (int32 l = 0; l < pIntroGeo->m_pHost->m_pEffects[j]->m_preconditionEffects[k].effectNameList.Num(); l++)
				{
					if (!introGeoAppendEffectNameList.Contains(pIntroGeo->m_pHost->m_pEffects[j]->m_preconditionEffects[k].effectNameList[l]))
					{
						isContain = false;
						break;
					}
				}
				if (!isContain) continue;
				isActive = true;
				break;
			}
			if (isActive)
			{
				if (pIntroGeo->m_pHost->m_pEffects[j]->m_functionNames.Contains("SuperposeAttribute"))
				{
					UEffectFunLib::SuperposeAttribute(pIntroGeo->m_pHost->m_pEffects[j], pIntroGeo, i);
				}
			}
		}*/

		introGeoAppendEffectNameList.Empty();
	}

	//再对目标角色的被动技能逐个进行判断，看每个被动效果的前提技能名数组是否都包含上述主动效果的所有效果名
	
}

void APhysCalculator::ActivateEmbeddedEffects(UEffect* pIntroEffect, ABaseCharacter* pCharacter)
{
	if (!pCharacter) return;
	//将主动效果连带附加的效果名称全部集中在一个数组中
	//例如附加火伤害是附加在一般的普攻Effect上，这时如果被攻击者身上带有FireBenefit或者FireResist，那么被动效果将发动作用
	//例如FireBenefit的functionNames为RecoverByHurt，FireResist的functionNames为AtkSub
	TArray<FString> introEffectAppendNames;
	introEffectAppendNames.Add(pIntroEffect->m_effectName);
	for (int32 i = 0; i < pIntroEffect->m_appendEffectList.Num(); i++)
	{
		introEffectAppendNames.Add(pIntroEffect->m_appendEffectList[i].effectName);
	}
	//再对目标角色的被动技能逐个进行判断，看每个被动效果的前提技能名数组是否都包含上述主动效果的所有效果名
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i] == pIntroEffect) continue;
		if (pCharacter->m_pEffects[i]->m_effectType != "PassiveEffect") continue;
		bool isActive = true;
		for (int32 j = 0; j < pCharacter->m_pEffects[i]->m_preconditionEffects.Num(); j++)
		{
			for (int32 k = 0; k < pCharacter->m_pEffects[i]->m_preconditionEffects[j].effectNameList.Num(); k++)
			{
				if (!introEffectAppendNames.Contains(pCharacter->m_pEffects[i]->m_preconditionEffects[j].effectNameList[k]))
				{
					isActive = false;
					break;
				}
			}
			if (isActive)
			{

			}
		}
	}
}

void APhysCalculator::ActivateJudgeEffect(int32& judgeColor, int32& judgeNb, ABaseCharacter* pTargetCharacter)
{
	if (!pTargetCharacter) return;
	//再对目标角色的被动技能逐个进行判断，看每个被动效果的前提技能名数组是否都包含上述主动效果的所有效果名
	for (int32 i = 0; i < pTargetCharacter->m_pEffects.Num(); i++)
	{
		if (pTargetCharacter->m_pEffects[i]->m_effectType != "JudgeActivatedTarget") continue;
		if (!pTargetCharacter->m_pEffects[i]->m_hitColors.Contains(judgeColor) || !pTargetCharacter->m_pEffects[i]->m_hitNbs.Contains(judgeNb)) continue;
		if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("RecoverByJudge"))
			UEffectFunLib::RecoverByJudge(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("RecoverByJudgeSource"))
			UEffectFunLib::RecoverByJudgeSource(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByRepeatJudgeNb"))
			UEffectFunLib::ChangeJudgeFromRedToBlack(pTargetCharacter->m_pEffects[i], judgeColor, pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("ExtraHurtByJudge"))
			UEffectFunLib::ExtraHurtByJudge(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("FreezeByJudgeActivate"))
			UEffectFunLib::FreezeByJudgeActivate(pTargetCharacter->m_pEffects[i], pTargetCharacter);
	}
}

void APhysCalculator::ActivateAccumulateJudgeEffect(ABaseCharacter* pCharacter)
{
	if (!pCharacter) return;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectType != "AccumulateJudgeEffect") continue;
		if (pCharacter->m_allJudgeCardInfos.Num() != pCharacter->m_pEffects[i]->m_effectOnIntervalList.Num()) continue;;
		bool isEffectOn = true;
		for (int32 j = 0; j < pCharacter->m_pEffects[i]->m_effectOnIntervalList.Num(); j++)
		{
			if (pCharacter->m_pEffects[i]->m_effectOnIntervalList[j] == pCharacter->m_allJudgeCardInfos[j]) continue;
			isEffectOn = false;
			break;
		}
		if (!isEffectOn) continue;;
		pCharacter->UpdateJudgeCardList(-1);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		/*if (pBattlePC->m_pCharacterStatusMenu)
			pBattlePC->m_pCharacterStatusMenu->UpdateJudgeInfoList();*/

		if (pCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByJudgeList"))
			UEffectFunLib::HurtByJudgeList(pCharacter->m_pEffects[i], pCharacter);
		else if (pCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByLostHpAndJudgeList"))
			UEffectFunLib::HurtByLostHpAndJudgeList(pCharacter->m_pEffects[i], pCharacter);
		else if (pCharacter->m_pEffects[i]->m_functionNames.Contains("RecoverByJudgeList"))
			UEffectFunLib::RecoverByJudgeList(pCharacter->m_pEffects[i], pCharacter);

		/*if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("RecoverByJudge"))
			UEffectFunLib::RecoverByJudge(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("RecoverByJudgeSource"))
			UEffectFunLib::RecoverByJudgeSource(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByRepeatJudgeNb"))
			UEffectFunLib::HurtByRepeatJudgeNb(pTargetCharacter->m_pEffects[i], pTargetCharacter, judgeNb, m_damageCoeK1, m_damageCoeK2);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByRepeatJudgeNb"))
			UEffectFunLib::ChangeJudgeFromRedToBlack(pTargetCharacter->m_pEffects[i], judgeColor, pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("ExtraHurtByJudge"))
			UEffectFunLib::ExtraHurtByJudge(pTargetCharacter->m_pEffects[i], pTargetCharacter);
		else if (pTargetCharacter->m_pEffects[i]->m_functionNames.Contains("FreezeByJudgeActivate"))
			UEffectFunLib::FreezeByJudgeActivate(pTargetCharacter->m_pEffects[i], pTargetCharacter);*/
		pCharacter->m_pEffects[i]->m_isOnTimeEffectDone = true;
		break;
	}

}

void APhysCalculator::ActivateSourceJudgeEffect(const int32& judgeColor, const int32& judgeNb, ABaseCharacter* pSourceCharacter)
{
	if (pSourceCharacter->m_judgeInfo.availableJudgeColors.Contains(judgeColor) && pSourceCharacter->m_judgeInfo.availableJudgeNbs.Contains(judgeNb))
	{

	}
}

void APhysCalculator::ActivateEffectDeleteEffect(UEffect* pDeleteEffect, ABaseCharacter* pCharacter)
{
	if (!pCharacter || pDeleteEffect->m_effectType == "OneTimeEffect") return;
	//再对目标角色的被动技能逐个进行判断，看每个被动效果的前提技能名数组是否都包含上述主动效果的所有效果名
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectType != "EffectDeleteEffect") continue;
		if (pCharacter->m_pEffects[i]->m_functionNames.Contains("HurtByEffectDelete"))
			UEffectFunLib::HurtByEffectDelete(pCharacter->m_pEffects[i], pCharacter);
	}
}

int32 APhysCalculator::ActivateHurtPassiveEffect(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget)
{
	if (!pHurtTarget) return 0;
	TArray<FString> introEffectAppendNames;
	//将主动效果连带附加的效果名称全部集中在一个数组中
	introEffectAppendNames.Add(pHurtEffect->m_effectName);
	for (int32 i = 0; i < pHurtEffect->m_appendEffectList.Num(); i++)
	{
		introEffectAppendNames.Add(pHurtEffect->m_appendEffectList[i].effectName);
	}
	int32 modifyHurtVal = hurtVal;
	for (int32 i=0; i<pHurtTarget->m_pEffects.Num(); i++)
	{
		if (!pHurtTarget->m_pEffects[i] || 
			(pHurtTarget->m_pEffects[i]->m_effectType != "HurtPassiveActivate" &&
			pHurtTarget->m_pEffects[i]->m_effectType != "AttributeReactionEffect" &&
			pHurtTarget->m_pEffects[i]->m_effectType != "AttributeReactionEffect_InstrinsicPassive")) continue;
		//如前提效果的数量大于0，要判断是否满足所有前提条件，如为0说明不需要前提条件
		if (pHurtTarget->m_pEffects[i]->m_preconditionEffects.Num() > 0)
		{
			bool isActive = true;
			for (int32 j = 0; j < pHurtTarget->m_pEffects[i]->m_preconditionEffects.Num(); j++)
			{
				for (int32 k = 0; k < pHurtTarget->m_pEffects[i]->m_preconditionEffects[j].effectNameList.Num(); k++)
				{
					if (!introEffectAppendNames.Contains(pHurtTarget->m_pEffects[i]->m_preconditionEffects[j].effectNameList[k]))
					{
						isActive = false;
						break;
					}
				}
			}
			if (!isActive) continue;
		}

		if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("Invincible"))
		{
			//必须放在最开头，因为例如伤害转移、放大伤害这些都是即时扣血的
			modifyHurtVal = UEffectFunLib::Invincible(pHurtTarget->m_pEffects[i], pHurtEffect, pHurtTarget, modifyHurtVal);
		}
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("InvincibleIfNoCards"))
			modifyHurtVal = UEffectFunLib::InvincibleIfNoCards(pHurtTarget->m_pEffects[i], pHurtEffect->m_isPhysOrMag, pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("Undead"))
		{
			//必须放在无敌之后，因为例如伤害转移、放大伤害这些都是即时扣血的
			modifyHurtVal = UEffectFunLib::Undead(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		}
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtTransfer"))
			modifyHurtVal = UEffectFunLib::HurtTransfer(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("SortByEvenOdd"))
			UEffectFunLib::SortByEvenOdd(pHurtTarget->m_pEffects[i], modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtToRecover"))
			modifyHurtVal = UEffectFunLib::HurtToRecover(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("ResistHurt"))
			modifyHurtVal = UEffectFunLib::ResistHurt(pHurtTarget->m_pEffects[i], pHurtEffect, pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtAmplified"))
			modifyHurtVal = UEffectFunLib::HurtAmplified(pHurtTarget->m_pEffects[i], pHurtEffect, pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtAmplifiedByAttribute"))
			modifyHurtVal = UEffectFunLib::HurtAmplifiedByAttribute(pHurtTarget->m_pEffects[i], pHurtEffect, pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("AmplifyOrExemptHurtByOddOrEven"))
			modifyHurtVal = UEffectFunLib::AmplifyOrExemptHurtByOddOrEven(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtAmplifyByAttackTimes"))
			modifyHurtVal = UEffectFunLib::HurtAmplifyByAttackTimes(pHurtTarget->m_pEffects[i], pHurtEffect, modifyHurtVal, pHurtTarget);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("ShareHurt"))
			modifyHurtVal = UEffectFunLib::ShareHurt(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("HurtReflect"))
			UEffectFunLib::HurtReflect(pHurtTarget->m_pEffects[i],pHurtEffect,pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("InvincibleIfCoverActorTag"))
			modifyHurtVal = UEffectFunLib::InvincibleIfCoverActorTag(pHurtTarget->m_pEffects[i], pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_functionNames.Contains("ExemptHurtIfEffectAppendString"))
			modifyHurtVal = UEffectFunLib::ExemptHurtIfEffectAppendString(pHurtTarget->m_pEffects[i], pHurtEffect, pHurtTarget, modifyHurtVal);
		else if (pHurtTarget->m_pEffects[i]->m_effectName.Contains("SpawnGeoByName"))
		{
			FString geoName = pHurtTarget->m_pEffects[i]->m_effectName.RightChop(15);
			UEffectFunLib::SpawnGeoByName(pHurtTarget, geoName, pHurtTarget->GetActorLocation(), pHurtTarget->GetActorRotation());
		}
		//break;
	}
	return modifyHurtVal;
}

int32 APhysCalculator::ActivateRecoverPassiveEffect(int32 recoverVal, UEffect* pRecoverEffect, ABaseCharacter* pRecoverTarget)
{
	if (!pRecoverTarget) return 0;
	int32 modifyRecoverVal = recoverVal;
	for (int32 i = 0; i < pRecoverTarget->m_pEffects.Num(); i++)
	{
		if (!pRecoverTarget->m_pEffects[i] || pRecoverTarget->m_pEffects[i]->m_effectType != "RecoverPassiveActivate") continue;
		if (pRecoverTarget->m_pEffects[i]->m_functionNames.Contains("RecoverToHurt"))
			modifyRecoverVal = UEffectFunLib::RecoverToHurt(pRecoverTarget->m_pEffects[i], pRecoverTarget, recoverVal);
		break;
	}
	return modifyRecoverVal;
}

void APhysCalculator::ActivateDeadEffect(ABaseCharacter* pCharacter)
{
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectType != "DeadActivate") continue;
		if (pCharacter->m_pEffects[i]->m_functionNames.Contains("DeadSpawnGeo_"))
			UEffectFunLib::DeadSpawnGeo(pCharacter->m_pEffects[i], pCharacter);
		else if (pCharacter->m_pEffects[i]->m_functionNames.Contains("HostDieTogether"))
			UEffectFunLib::HostDieTogether(pCharacter->m_pEffects[i], pCharacter);
	}
}

void APhysCalculator::EffectPlayFxByName_Implementation(const FString& geoName, const FString& effectName, ABaseCharacter* pCharacter)
{

}

void APhysCalculator::PolygonEffectPreCalculate(APhysPolygon* pPolygon, TArray<FEffectParams>& effectParamList)
{
	if (!pPolygon || pPolygon->m_hasSpawnSonGeo) return;
	//TArray<FEffectParams> pGeo->m_effectParamList;
	/*if (pGeo->m_enhanceType == -1) effectParamList = pGeo->m_effectParamList;
	else
	{
		if (pGeo->m_mutationEffectParamList.Contains((uint8)pGeo->m_enhanceType))
			effectParamList = pGeo->m_mutationEffectParamList[(uint8)pGeo->m_enhanceType];
	}*/
	for (int32 i=0; i< effectParamList.Num(); i++)
	{
		if (!effectParamList[i].isCalculateInPreStage) continue;
		pPolygon->m_hasSpawnSonGeo = true;
		if (effectParamList[i].functionNames[0] == "Oppress")
		{
			if (!pPolygon->m_pHost) continue;
			TArray<ABaseCharacter*> pOppSideCharacters;
			TArray<ABaseCharacter*> pSameSideCharacters;
			for (int32 j=0; j< pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag == pPolygon->m_pHost->m_campFlag)
					pOppSideCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
				else pSameSideCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			int32 oppSideDif = FMath::Abs(pSameSideCharacters.Num() - pOppSideCharacters.Num());
			effectParamList[i].effectValues[0] = oppSideDif;
			for (int32 j = 0; j < pOppSideCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pOppSideCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtAccordCompanionNb")
		{
			int32 companionNb = 0;
			TArray<ABaseCharacter*> pOppCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_grade == effectParamList[i].effectValues[0])
					companionNb += 1;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag) pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			effectParamList[i].effectValues[1] = companionNb;
			for (int32 j = 0; j < pOppCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pOppCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtByDifCampFlag")
		{
			int32 difCampFlagNb = 0;
			int32 sameCampFlagNb = 0;
			TArray<ABaseCharacter*> pOppCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag)
				{
					difCampFlagNb += 1;
					pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
				}
				else
				{
					if (pPolygon->m_pHost && pPolygon->m_pOverlapCharacters[j] != pPolygon->m_pHost)
						sameCampFlagNb += 1;
				}
			}
			effectParamList[i].effectValues[2] = difCampFlagNb;
			effectParamList[i].effectValues[3] = sameCampFlagNb;
			for (int32 j = 0; j < pOppCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pOppCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtAmplifiedByDifSameFlag")
		{
			int32 sameCampFlagNb = 0;
			TArray<ABaseCharacter*> pOppCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag == pPolygon->m_campFlag)
					sameCampFlagNb += 1;
				else
					pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			effectParamList[i].effectValues[0] = effectParamList[i].effectValues[0] * (100 + sameCampFlagNb * effectParamList[i].effectValues[1]) / 100;
			for (int32 j = 0; j < pOppCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pOppCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "IncreaseCDByCharacterAppendString")
		{
			FString appendString = effectParamList[i].effectName.RightChop(27);
			TArray<ABaseCharacter*> pOppCharacters;
			int32 containStringNb = 0;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				for (int32 k=0; k<pPolygon->m_pOverlapCharacters[j]->m_pEffects.Num(); k++)
				{
					if (!pPolygon->m_pOverlapCharacters[j]->m_pEffects[k]->m_effectName.Contains(appendString)) continue;
					containStringNb += 1;
					break;
				}
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag && pPolygon->m_pOverlapCharacters[j]->m_characterType == 1) pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			effectParamList[i].effectValues[0] = containStringNb;
			for (int32 j = 0; j < pOppCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pOppCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "IncreaseCDByCoverCharacterAppendString")
		{
			FString appendString = effectParamList[i].effectName.RightChop(32);
			TArray<ABaseCharacter*> pExertCharacters;
			int32 totalStringNb = 0;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag) pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
				for (int32 k = 0; k < pPolygon->m_pOverlapCharacters[j]->m_pEffects.Num(); k++)
				{
					if (!pPolygon->m_pOverlapCharacters[j]->m_pEffects[k]->m_effectName.Contains(appendString)) continue;
					totalStringNb += 1;
					break;
				}
			}
			effectParamList[i].effectValues[0] = totalStringNb * effectParamList[i].effectValues[0];
			for (int32 j = 0; j < pExertCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtShareByCharacterAppendString")
		{
			FString appendString = effectParamList[i].effectName.RightChop(26);
			TArray<ABaseCharacter*> pExertCharacters;
			int32 exertCharacterNb = 0;
			bool isContainPlayerCharacter = false;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 1)
				{
					isContainPlayerCharacter = true;
					pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
					exertCharacterNb += 1;
				}
				else
				{
					for (int32 k = 0; k < pPolygon->m_pOverlapCharacters[j]->m_pEffects.Num(); k++)
					{
						if (!pPolygon->m_pOverlapCharacters[j]->m_pEffects[k]->m_effectName.Contains(appendString)) continue;
						pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
						exertCharacterNb += 1;
						break;
					}
				}
			}
			if (isContainPlayerCharacter)
			{
				effectParamList[i].effectValues[0] = effectParamList[i].effectValues[0] / exertCharacterNb;
				for (int32 j = 0; j < pExertCharacters.Num(); j++)
				{
					SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
				}
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtByCompanionHpLess")
		{
			if (!m_pRGM) continue;
			int32 lessHpNb = 0;
			TArray<ABaseCharacter*> pExertCharacters;
			for (int32 j = 0; j < m_pRGM->m_pAllCharacters.Num(); i++)
			{
				if (!m_pRGM->m_pAllCharacters[j]) continue;
				int32 hpPercent = m_pRGM->m_pAllCharacters[j]->m_Hp * 100 / m_pRGM->m_pAllCharacters[j]->m_originHp;
				if (hpPercent <= effectParamList[i].effectValues[0]) lessHpNb += 1;
				pExertCharacters.Add(m_pRGM->m_pAllCharacters[j]);
			}
			effectParamList[i].effectValues[1] = lessHpNb;
			for (int32 j=0; j<pExertCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtByAverageDefPercent")
		{
			int32 coverCharacterNb = 0;
			int32 totalDef = 0;
			TArray<ABaseCharacter*> pExertCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				totalDef += pPolygon->m_pOverlapCharacters[j]->m_DFC;
				coverCharacterNb += 1;
				pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			if (coverCharacterNb == 0) effectParamList[i].effectValues[0] = 0;
			else effectParamList[i].effectValues[0] = totalDef/coverCharacterNb;
			for (int32 j = 0; j < pExertCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtByAverageAtkPercent")
		{
			int32 coverCharacterNb = 0;
			int32 totalAtkAddition = 0;
			TArray<ABaseCharacter*> pExertCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				totalAtkAddition += pPolygon->m_pOverlapCharacters[j]->m_ATKAddition;
				coverCharacterNb += 1;
				pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			if (coverCharacterNb == 0) effectParamList[i].effectValues[0] = 0;
			else effectParamList[i].effectValues[0] = totalAtkAddition / coverCharacterNb;
			for (int32 j = 0; j < pExertCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "HurtByCoverCharacterGrade")
		{
			int32 coverCharacterNb = 0;
			TArray<ABaseCharacter*> pExertCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag)
					pExertCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
				if (!pPolygon->m_pOverlapCharacters[j] || pPolygon->m_pOverlapCharacters[j]->m_grade != effectParamList[i].effectValues[1]) continue;
				coverCharacterNb += 1;
			}
			effectParamList[i].effectValues[0] = effectParamList[i].effectValues[0] * (1 + coverCharacterNb * effectParamList[i].effectValues[2] / 100);
			for (int32 j = 0; j < pExertCharacters.Num(); j++)
			{
				SpawnEffectOnCharacter(pPolygon, pExertCharacters[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "SwitchHpPercentByOrder")
		{
			int32 topDefPercent = -1;
			int32 bottomDefPercent = -1;
			bool containPlayer = false;
			ABaseCharacter* pTopDefCharacter = NULL;
			ABaseCharacter* pBottomDefCharacter = NULL;
			TMap<int32, ABaseCharacter*> characterHpPercentOrderMap;

			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 1) containPlayer = true;
				int32 hpPercent = pPolygon->m_pOverlapCharacters[j]->m_Hp * 100 / pPolygon->m_pOverlapCharacters[j]->m_originHp;
				if (hpPercent < effectParamList[i].effectValues[0]) continue;
				characterHpPercentOrderMap.Add(hpPercent, pPolygon->m_pOverlapCharacters[j]);
			}
			characterHpPercentOrderMap.KeySort([](int32 A, int32 B) {return A < B;});

			if (characterHpPercentOrderMap.Num() <= 1) continue;
			TArray<ABaseCharacter*> pCharacterOrderList;
			TArray<int32> characterHpPercentList;
			for (TMap<int32, ABaseCharacter*>::TConstIterator iter = characterHpPercentOrderMap.CreateConstIterator(); iter; ++iter)
			{
				pCharacterOrderList.Add(iter->Value);
				characterHpPercentList.Add(iter->Key);
			}
			uint8 totalNb = pCharacterOrderList.Num();
			for (uint8 j=0; j<pCharacterOrderList.Num(); j++)
			{
				pCharacterOrderList[j]->m_Hp = pCharacterOrderList[j]->m_originHp * characterHpPercentList[totalNb - j - 1];
				SpawnEffectOnCharacter(pPolygon, pCharacterOrderList[j]);
			}
		}
		else if (effectParamList[i].functionNames[0] == "ExtraHurtByCompareCardAndCharacterNb")
		{
			int32 oppCharacterNb = 0;
			ABaseCharacter* pPlayerCharacter = NULL;
			for (int32 j=0; j<pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag) oppCharacterNb += 1;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 1 && pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag)
					pPlayerCharacter = pPolygon->m_pOverlapCharacters[j];
			}
			if (!pPlayerCharacter) continue;
			effectParamList[i].effectValues[0] = oppCharacterNb;
			SpawnEffectOnCharacter(pPolygon, pPlayerCharacter);
		}
		else if (effectParamList[i].functionNames[0] == "ExtraHurtIfEvenCharacters")
		{
			int32 characterNb = 0;
			ABaseCharacter* pPlayerCharacter = NULL;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 0) characterNb += 1;
				else pPlayerCharacter = pPolygon->m_pOverlapCharacters[j];
			}
			if (!pPlayerCharacter) continue;
			if (characterNb % 2 == 0) effectParamList[i].effectValues[0] = effectParamList[i].effectValues[1];
			SpawnEffectOnCharacter(pPolygon, pPlayerCharacter);
		}
		else if (effectParamList[i].effectName == "HurtByCoverCharacterAverageAtk")
		{
			int32 totalAtkAddition = 0;
			int32 coverCharacterNb = 0;
			TArray<ABaseCharacter*> pOppCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				totalAtkAddition += pPolygon->m_pOverlapCharacters[j]->m_ATKAddition;
				coverCharacterNb += 1;
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag != pPolygon->m_campFlag) pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			if (coverCharacterNb > 0)
			{
				int32 averageAtkPercent = totalAtkAddition / coverCharacterNb;
				effectParamList[i].effectValues[0] = effectParamList[i].effectValues[0] + averageAtkPercent;
				for (int32 j = 0; j < pOppCharacters.Num(); j++)
				{
					SpawnEffectOnCharacter(pPolygon, pOppCharacters[j]);
				}
			}
		}
		else if (effectParamList[i].effectName == "ExtractCompanyLifeToAttack")
		{
			TArray<ABaseCharacter*> pOverlapCharacters;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j] || pPolygon->m_pOverlapCharacters[j]->m_characterType != 0 || 
					pPolygon->m_pOverlapCharacters[j]->m_grade != effectParamList[i].effectValues[0]) continue;
				pOverlapCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			SpawnPolyPreCalculateEffect(pPolygon, effectParamList[i].effectName, effectParamList[i], pPolygon->m_pHost, pOverlapCharacters);
		}
		else if (effectParamList[i].effectName == "ExtraHurtByCompareCardAndDifTagNb")
		{
			ABaseCharacter* pPlayerCharacter = NULL;
			TArray<ABaseCharacter*> pSameTagCharacters;
			int32 hurtVal = 0;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 1 && pPolygon->m_campFlag != pPolygon->m_pOverlapCharacters[j]->m_campFlag)
					pPlayerCharacter = pPolygon->m_pOverlapCharacters[j];
				else if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 0 && pPolygon->m_pOverlapCharacters[j]->m_campFlag == pPolygon->m_campFlag)
					pSameTagCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			if (!pPlayerCharacter) continue;
			if (pPlayerCharacter->m_pBaseEquipment->m_pSkills.Num() < pSameTagCharacters.Num()) effectParamList[i].effectValues[0] = 0;
			SpawnEffectOnCharacter(pPolygon, pPlayerCharacter);
		}
		else if (effectParamList[i].effectName == "AbsorbSameTagHurtToPlayer")
		{
			ABaseCharacter* pPlayerCharacter = NULL;
			int32 hurtVal = 0;
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j]) continue;
				if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 1 && pPolygon->m_campFlag != pPolygon->m_pOverlapCharacters[j]->m_campFlag)
					pPlayerCharacter = pPolygon->m_pOverlapCharacters[j];
				else if (pPolygon->m_pOverlapCharacters[j]->m_characterType == 0 && pPolygon->m_pOverlapCharacters[j]->m_campFlag == pPolygon->m_campFlag)
				{
					int32 hurt = pPolygon->m_pOverlapCharacters[j]->m_originHp - pPolygon->m_pOverlapCharacters[j]->m_Hp;
					hurtVal += hurt;
				}
			}
			if (!pPlayerCharacter) continue;
			effectParamList[i].effectValues[0] = hurtVal * effectParamList[i].effectValues[1] / 100;
			SpawnEffectOnCharacter(pPolygon, pPlayerCharacter);
		}
		else if (effectParamList[i].functionNames[0] == "DrainStars")
		{
			TArray<ABaseCharacter*> pOppCharacters;
			for (int32 j=0; j<pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (pPolygon->m_pOverlapCharacters[j]->m_campFlag == pPolygon->m_campFlag) continue;
				pOppCharacters.Add(pPolygon->m_pOverlapCharacters[j]);
			}
			if (pOppCharacters.Num() == 0) continue;
			TArray<uint8> attributeList;
			for (int32 j=0; j< effectParamList[i].effectOnIntervalList.Num(); j++)
			{
				attributeList.Add((uint8)effectParamList[i].effectOnIntervalList[j]);
			}
			//if (attributeList.Num() == 0) continue;
			bool activateEffect = false;
			for (int32 j = 0; j < pPolygon->m_pOverlapGeos.Num(); j++)
			{
				if (attributeList.Num() == 0)
				{
					activateEffect = true;
					break;
				}
				if (!pPolygon->m_pOverlapGeos[j]) continue;
				int32 k = 0;
				while (k < attributeList.Num())
				{
					if (!pPolygon->m_pOverlapGeos[j]->m_attributeList.Contains(attributeList[k]))
					{
						k += 1;
						continue;
					}
					attributeList.RemoveAt(k);
				}
			}
			if (!activateEffect) continue;
			TArray<ABaseCharacter*> pSubHosts;
			for (int32 j=0; j<pOppCharacters.Num(); j++)
			{
				SpawnPolyPreCalculateEffect(pPolygon, effectParamList[i].functionNames[1], effectParamList[i], pOppCharacters[j], pSubHosts);
			}
		}
		else if (effectParamList[i].functionNames[0] == "InvincibleIfCoverActorTag")
		{
			int32 satisfiedActorNb = 0;
			FString targetTag = effectParamList[i].effectName.RightChop(25);
			FName targetTagName = FName(*targetTag);
			for (int32 j = 0; j < pPolygon->m_pOverlapGeos.Num(); j++)
			{
				if (!pPolygon->m_pOverlapGeos[j] || !pPolygon->m_pOverlapGeos[j]->m_attributeTags.Contains(targetTagName)) continue;
				satisfiedActorNb += 1;
			}
			effectParamList[i].effectValues[1] = satisfiedActorNb;
			SpawnEffectOnCharacter(pPolygon, pPolygon->m_pHost);
		}
		else if (effectParamList[i].functionNames[0] == "HurtByCoverActorTag")
		{
			int32 satisfiedActorNb = 0;
			FString targetTag = effectParamList[i].effectName.RightChop(19);
			FName targetTagName = FName(*targetTag);
			for (int32 j = 0; j < pPolygon->m_pOverlapGeos.Num(); j++)
			{
				if (!pPolygon->m_pOverlapGeos[j] || !pPolygon->m_pOverlapGeos[j]->m_attributeTags.Contains(targetTagName)) continue;
				satisfiedActorNb += 1;
			}
			effectParamList[i].effectValues[1] = satisfiedActorNb;
			SpawnEffectOnCharacter(pPolygon, pPolygon->m_pHost);
		}
		else if (effectParamList[i].functionNames[0] == "SpawnAppendGeoByName")
		{
			FString targetTag = effectParamList[i].effectName.RightChop(20);
			FName targetTagName = FName(*targetTag);
			for (int32 j = 0; j < pPolygon->m_pOverlapGeos.Num(); j++)
			{
				if (!pPolygon->m_pOverlapGeos[j] || !pPolygon->m_pOverlapGeos[j]->m_attributeTags.Contains(targetTagName)) continue;
				UEffectFunLib::SpawnAppendGeoByName(pPolygon, effectParamList[i].functionNames[1], pPolygon->m_pOverlapGeos[j]->GetActorLocation());
			}
		}
		else if (effectParamList[i].functionNames[0] == "SpawnAppendGeoByStuffName")
		{
			FString targetTag = effectParamList[i].effectName.RightChop(25);
			FName targetTagName = FName(*targetTag);
			for (int32 j = 0; j < pPolygon->m_pOverlapCharacters.Num(); j++)
			{
				if (!pPolygon->m_pOverlapCharacters[j] || !pPolygon->m_pOverlapCharacters[j]->m_characterClassName.Contains(targetTag)) continue;
				UEffectFunLib::SpawnAppendGeoByName(pPolygon, effectParamList[i].functionNames[1], pPolygon->m_pOverlapCharacters[j]->GetActorLocation());
			}
			for (int32 j = 0; j < pPolygon->m_pOverlapGeos.Num(); j++)
			{
				if (!pPolygon->m_pOverlapGeos[j] || !pPolygon->m_pOverlapGeos[j]->m_attributeTags.Contains(targetTagName)) continue;
				UEffectFunLib::SpawnAppendGeoByName(pPolygon, effectParamList[i].functionNames[1], pPolygon->m_pOverlapGeos[j]->GetActorLocation());
			}
		}
	}
}


/*
TSubclassOf<class UEffect> APhysCalculator::FindEffectClassByName(FString effectName)
{
	if (!m_effectClassMap.Contains(effectName)) return NULL;
	return m_effectClassMap[effectName];
}*/

/*
void APhysCalculator::Move(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	FLogicVec2D normalizeForwardDir = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(pCharacter->m_curLogicForwardDir, 100);
	FLogicVec2D forwardDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(normalizeForwardDir, FLogicVec2D(0, 0), pEffect->m_effectValues[0]);
	int32 expandDeltaX = forwardDir.X * pEffect->m_effectValues[1];
	int32 deltaX = expandDeltaX;
	int32 expandDeltaY = forwardDir.Y * pEffect->m_effectValues[1];
	int32 deltaY = expandDeltaY;
	FLogicVec2D nextLogicLoc(pCharacter->m_logicPos2D.X + deltaX, pCharacter->m_logicPos2D.Y + deltaY);
	if (nextLogicLoc == pCharacter->m_logicPos2D) return;
	FLogicVec2D offset(deltaX, deltaY);
	FLogicVec2D offsetPerpendicularVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(FLogicVec2D(-deltaY, deltaX), pCharacter->m_characterRadius);
	FLogicVec2D offsetNormalizeVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(offset, pCharacter->m_characterRadius);
	TArray<FLogicVec2D> coverPts;
	coverPts.Add(pCharacter->m_logicPos2D + offsetPerpendicularVec);
	coverPts.Add(pCharacter->m_logicPos2D - offsetPerpendicularVec);
	coverPts.Add(nextLogicLoc - offsetPerpendicularVec + offsetNormalizeVec);
	coverPts.Add(nextLogicLoc + offsetPerpendicularVec + offsetNormalizeVec);

	FVector nextLoc(nextLogicLoc.X, nextLogicLoc.Y, pCharacter->m_defaultHeight + pCharacter->m_relativeHeight);

	FVector startPoint(pCharacter->m_logicPos2D.X, pCharacter->m_logicPos2D.Y, pCharacter->m_defaultHeight);
	FVector lineTraceEndPt(nextLogicLoc.X + offsetNormalizeVec.X, nextLogicLoc.Y + offsetNormalizeVec.Y, pCharacter->m_defaultHeight);
	TArray<FHitResult> hitResults;
	FCollisionResponseParams responseParams;
	responseParams.CollisionResponse.SetAllChannels(ECR_Overlap);
	GetWorld()->SweepMultiByChannel(hitResults, startPoint, lineTraceEndPt, FQuat::Identity, COLLISION_OBSTACLE_FINDING,
		FCollisionShape::MakeSphere(pCharacter->m_characterRadius + 2), FCollisionQueryParams::DefaultQueryParam, responseParams);
	bool canMove = true;
	for (int32 i = 0; i < hitResults.Num(); i++)
	{
		if (hitResults[i].GetActor() == this || !hitResults[i].GetActor()) continue;
		if (!hitResults[i].GetComponent()) continue;
		if (!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysGeo"))) &&
			!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("DumpActor")))) continue;
		if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysGeo"))) &&
			!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("Boundary")))) continue;

		if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysPolygon"))))
		{
			APhysPolygon* pPolygon = Cast<APhysPolygon>(hitResults[i].GetActor());
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyPolyIntercept(coverPts, pPolygon->m_logicFixPts);
			if (isIntercept)
			{
				canMove = false;
				break;
			}
		}
		else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysActor"))))
		{
			ABasePhysActor* pActor = Cast<ABasePhysActor>(hitResults[i].GetActor());
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyCircleIntercept(coverPts, pActor->m_logicPos2D, pActor->m_actorRadius);
			if (isIntercept)
			{
				canMove = false;
				break;
			}
		}
		else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("DumpActor"))))
		{
			ADumpPhysActor* pActor = Cast<ADumpPhysActor>(hitResults[i].GetActor());
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyCircleIntercept(coverPts, pActor->m_logicPos2D, pActor->m_actorRadius);
			if (isIntercept)
			{
				canMove = false;
				break;
			}
		}
		else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysLine"))))
		{
			APhysLine* pLine = Cast<APhysLine>(hitResults[i].GetActor());
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsSegmentsIntersect_Int(pLine->m_logicStartPoint, pLine->m_logicEndPoint,
				pCharacter->m_logicPos2D, nextLogicLoc);
			if (isIntercept)
			{
				canMove = false;
				break;
			}
		}
	}
	//DrawDebugPoint(GetWorld(), FVector(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight), 20, FColor::Red, false, 0.1);

	pCharacter->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	pCharacter->m_pBaseAnimInstance->m_speed = 0;
	pCharacter->m_logicPos2D = nextLogicLoc;
	pCharacter->SetActorLocation(nextLoc);

	if (pEffect->m_pOriginGeo)
		EffectPlayFxByName(pEffect->m_pOriginGeo->m_className, pEffect->m_effectName, pCharacter);
	else
		EffectPlayFxByName("NULL", pEffect->m_effectName, pCharacter);
}
*/

ABasePhysGeo* APhysCalculator::FindEntity(int32 entityNb)
{
	for (int32 i = 0; i<m_pPhysActors.Num(); i++)
	{
		if (m_pPhysActors[i]->m_entityID == entityNb) return m_pPhysActors[i];
	}
	for (int32 i = 0; i<m_pPoints.Num(); i++)
	{
		if (m_pPoints[i]->m_entityID == entityNb) return m_pPoints[i];
	}
	for (int32 i = 0; i < m_pLines.Num(); i++)
	{
		if (m_pLines[i]->m_entityID == entityNb) return m_pLines[i];
	}
	for (int32 i = 0; i < m_pPolygons.Num(); i++)
	{
		if (m_pPolygons[i]->m_entityID == entityNb) return m_pPolygons[i];
	}
	return NULL;
}

/*
int32 APhysCalculator::GenerateUnOccupiedPairID()
{
	int32 i = 0;
	while (true)
	{
		if (i >= 2147483647) return -1;
		if (m_occupyPairIDs.Contains(i)) i++;
		else
		{
			m_occupyPairIDs.Add(i);
			return i;
		}
	}
}*/

int32 APhysCalculator::GenerateUnOccupiedGeoID()
{
	int32 i = 0;
	while (true)
	{
		if (i >= 2147483647) return -1;
		if (m_occupyGeoIDs.Contains(i)) i++;
		else
		{
			//m_occupyGeoIDs.Add(i);
			return i;
		}
	}
}
/*

void APhysCalculator::UpdateReactionGeoPair()
{
	int32 i = 0;
	while (i < m_reactionPairs.Num())
	{
		if (!m_reactionPairs[i].pReactionActor1 || !m_reactionPairs[i].pReactionActor2 || !m_reactionPairs[i].isPairValid ||
			m_reactionPairs[i].pReactionActor1->m_pRootGeos.Contains(m_reactionPairs[i].pReactionActor2) ||
			m_reactionPairs[i].pReactionActor2->m_pRootGeos.Contains(m_reactionPairs[i].pReactionActor1))
		{
			if (m_reactionPairs[i].pSonGeo) m_reactionPairs[i].pSonGeo->m_isGeoValid = false;
			m_occupyPairIDs.Remove(m_reactionPairs[i].reactionPairID);
			m_reactionPairs.RemoveAt(i);
			continue;
		}

		if (m_reactionPairs[i].hasReactionOccur || !m_reactionPairs[i].pReactionActor1->m_isInitial ||
			!m_reactionPairs[i].pReactionActor2->m_isInitial)
		{
			i += 1;
			continue;
		}

		/ *************************************** /
		//begin to tell which kind of reaction it is
		/ *************************************** /
		if (m_reactionPairs[i].pariReactionInfo.reactionType == EReactionType::PRT_Transform)
			ReactionGeoTransform(m_reactionPairs[i].pReactionActor1, m_reactionPairs[i].pReactionActor2, m_reactionPairs[i].pariReactionInfo);
		else if (m_reactionPairs[i].pariReactionInfo.reactionType == EReactionType::PRT_AddTag)
		{
			ReactionGeoAddTag(m_reactionPairs[i].pReactionActor1, m_reactionPairs[i].pReactionActor2, m_reactionPairs[i].pariReactionInfo, i);
			AwakeReactionPair(i, m_reactionPairs[i].pReactionActor1, m_reactionPairs[i].pReactionActor2);
		}
		else if (m_reactionPairs[i].pariReactionInfo.reactionType == EReactionType::PRT_SubtractTag)
		{
			ReactionGeoSubtractTag(m_reactionPairs[i].pReactionActor1, m_reactionPairs[i].pReactionActor2, m_reactionPairs[i].pariReactionInfo, i);
			AwakeReactionPair(i, m_reactionPairs[i].pReactionActor1, m_reactionPairs[i].pReactionActor2);
		}
		else if (m_reactionPairs[i].pariReactionInfo.reactionType == EReactionType::PRT_NULL)
		{
			DetermineReactionType(i);
		}
		i++;
	}
}*/

void APhysCalculator::CollectAllNewPhysGeos()
{
	for (int32 i = 0; i<m_pCharacterList.Num(); i++)
	{
		while (m_pCharacterList[i]->m_pNewSpawnPhysGeos.Num() > 0)
		{
			ABasePhysGeo* pLastPhysGeo = m_pCharacterList[i]->m_pNewSpawnPhysGeos.Last();
			AddPhysGeo(pLastPhysGeo, m_pCharacterList[i], m_pCharacterList[i]->m_campFlag);
			pLastPhysGeo->m_hierachy = 0;
			m_pCharacterList[i]->m_pNewSpawnPhysGeos.Pop();
		}
	}
}

void APhysCalculator::UpdateAllPhysGeos()
{
	//CollectReactionPair();
	DeleteInValidGeos();
	/*for (int32 i = 0; i<m_pLines.Num(); i++)
	{
		if (!m_pLines[i] || !m_pLines[i]->m_isGeoValid) continue;
		m_pLines[i]->TickLine();
		for (int32 j=0; j< m_pLines[i]->m_effectParamList.Num(); j++)
		{
			if (!m_pLines[i]->m_pHitCharacter || m_pLines[i]->m_effectParamList[j].effectName == "NULL") continue;
			SpawnEffectOnCharacter(m_pLines[i], m_pLines[i]->m_pHitCharacter);
		}
	}*/
	//TArray<FEffectParams> pGeo->m_effectParamList;
	/*if (pGeo->m_enhanceType == -1) effectParamList = pGeo->m_effectParamList;
	else
	{
		if (pGeo->m_mutationEffectParamList.Contains((uint8)pGeo->m_enhanceType))
			effectParamList = pGeo->m_mutationEffectParamList[(uint8)pGeo->m_enhanceType];
	}*/
	for (int32 i = 0; i<m_pPoints.Num(); i++)
	{
		if (!m_pPoints[i] || !m_pPoints[i]->m_isGeoValid) continue;
		//m_pPoints[i]->TickPoint();
		bool isHit = false;
		for (int32 j=0; j < m_pPoints[i]->m_pOverlapCharacters.Num(); j++)
		{
			if (!m_pPoints[i]->m_pOverlapCharacters[j]) continue;
			TArray<FActiveAttributeReactionInfo> flashEffects;
			CalCharacterAttributeReaction(m_pPoints[i]->m_pOverlapCharacters[j], m_pPoints[i]->m_attributeList, flashEffects);
			for (int32 k = 0; k < flashEffects.Num(); k++)
			{
				AddAttributeReactionEffect(m_pPoints[i]->m_pOverlapCharacters[j], flashEffects[k], m_pPoints[i]);
			}

			//当被击中者的特殊被攻击tag不为空时，说明只有特定的物体才会造成大伤害，否则的话对伤害进行削减
			if (m_pPoints[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num() > 0 ||
				m_pPoints[i]->m_pOverlapCharacters[j]->m_resistHurtTag.Num() > 0)
			{
				//先判断是否包含有放大伤害的tag，例如某些敌人对reflect标签的抵御力弱，用以逼使玩家专门使用反射类技能
				//0 = no effect, 2 = resist, 1 = amplified
				uint8 amplifiedTag = 0;
				if (m_pPoints[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num() > 0) amplifiedTag = 2;
				for (int32 k = 0; k < m_pPoints[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num(); k++)
				{
					if (m_pPoints[i]->m_pBasicComponent->ComponentHasTag(m_pPoints[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag[k]))
					{
						amplifiedTag = 1;
						break;
					}
				}
				//再判断是否包含了减少伤害的tag，例如某些敌人对chop的抵御力强
				if (amplifiedTag == 0)
				{
					for (int32 k = 0; k < m_pPoints[i]->m_pOverlapCharacters[j]->m_resistHurtTag.Num(); k++)
					{
						if (m_pPoints[i]->m_pBasicComponent->ComponentHasTag(m_pPoints[i]->m_pOverlapCharacters[j]->m_resistHurtTag[k]))
						{
							amplifiedTag = 2;
							break;
						}
					}
				}
				if (amplifiedTag == 2)
					AddSpecificTagScaleEffect(m_pPoints[i]->m_pOverlapCharacters[j], m_pPoints[i]);
			}

			for (int32 k = 0; k < m_pPoints[i]->m_effectParamList.Num(); k++)
			{
				if (m_pPoints[i]->m_effectParamList[k].effectName == "NULL") continue;
				bool hitFlag = SpawnEffectOnCharacter(m_pPoints[i], m_pPoints[i]->m_pOverlapCharacters[j]);
				if (hitFlag) isHit = true;
			}
		}
		if (isHit) m_pPoints[i]->m_hitSolid = true;
		if (m_pPoints[i]->m_isGeoValid && m_pPoints[i]->m_hitSolid)
		{
			PlayHitParticle(m_pPoints[i], m_pPoints[i]->GetActorLocation());
			m_pPoints[i]->m_isGeoValid = false;
		}
	}
	for (int32 i = 0; i<m_pPolygons.Num(); i++)
	{
		if (!m_pPolygons[i] || !m_pPolygons[i]->m_isGeoValid) continue;
		//m_pPolygons[i]->TickPolygon();
		PolygonEffectPreCalculate(m_pPolygons[i], m_pPolygons[i]->m_effectParamList);
		for (int32 j = 0; j < m_pPolygons[i]->m_pOverlapCharacters.Num(); j++)
		{
			if (!m_pPolygons[i]->m_pOverlapCharacters[j]) continue;
			TArray<FActiveAttributeReactionInfo> flashEffects;
			CalCharacterAttributeReaction(m_pPolygons[i]->m_pOverlapCharacters[j], m_pPolygons[i]->m_attributeList, flashEffects);
			for (int32 k = 0; k < flashEffects.Num(); k++)
			{
				AddAttributeReactionEffect(m_pPolygons[i]->m_pOverlapCharacters[j], flashEffects[k], m_pPolygons[i]);
			}

			//当被击中者的特殊被攻击tag不为空时，说明只有特定的物体才会造成大伤害，否则的话对伤害进行削减
			if (m_pPolygons[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num() > 0 || 
				m_pPolygons[i]->m_pOverlapCharacters[j]->m_resistHurtTag.Num() > 0)
			{
				//先判断是否包含有放大伤害的tag，例如某些敌人对reflect标签的抵御力弱，用以逼使玩家专门使用反射类技能
				//0 = no effect, 2 = resist, 1 = amplified
				uint8 amplifiedTag = 0;
				if (m_pPolygons[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num() > 0) amplifiedTag = 2;
				for (int32 k = 0; k < m_pPolygons[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag.Num(); k++)
				{
					if (m_pPolygons[i]->m_pBasicComponent->ComponentHasTag(m_pPolygons[i]->m_pOverlapCharacters[j]->m_amplifiedHurtTag[k]))
					{
						amplifiedTag = 1;
						break;
					}
				}
				//再判断是否包含了减少伤害的tag，例如某些敌人对chop的抵御力强
				if (amplifiedTag == 0)
				{
					for (int32 k = 0; k < m_pPolygons[i]->m_pOverlapCharacters[j]->m_resistHurtTag.Num(); k++)
					{
						if (m_pPolygons[i]->m_pBasicComponent->ComponentHasTag(m_pPolygons[i]->m_pOverlapCharacters[j]->m_resistHurtTag[k]))
						{
							amplifiedTag = 2;
							break;
						}
					}
				}
				//如果没有没有放大tag同时又有抵御tag，才加这个effect
				if (amplifiedTag == 2)
					AddSpecificTagScaleEffect(m_pPolygons[i]->m_pOverlapCharacters[j], m_pPolygons[i]);
			}

			bool isHit = false;
			for (int32 k = 0; k < m_pPolygons[i]->m_effectParamList.Num(); k++)
			{
				if (m_pPolygons[i]->m_effectParamList[k].effectName == "NULL" || m_pPolygons[i]->m_effectParamList[k].isCalculateInPreStage) continue;
				bool hitFlag = SpawnEffectOnCharacter(m_pPolygons[i], m_pPolygons[i]->m_pOverlapCharacters[j]);
				if (hitFlag) isHit = true;
			}
			if (m_pPolygons[i]->m_campFlag != m_pPolygons[i]->m_pOverlapCharacters[j]->m_campFlag && isHit)
			{
				PlayHitParticle(m_pPolygons[i], m_pPolygons[i]->m_pOverlapCharacters[j]->GetActorLocation());
				UGameplayStatics::PlaySoundAtLocation(this, m_pPolygons[i]->m_pHitSound, m_pPolygons[i]->m_pOverlapCharacters[j]->GetActorLocation());
			}
		}
	}
	UpdateCharacterEffects();
}

void APhysCalculator::UpdateBindPS()
{
	for (TMap<UParticleSystemComponent*, FBindPSInformation>::TConstIterator iter = m_bindPSMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Key || !iter->Value.pEffect || !iter->Value.pGuest || !iter->Value.pHost)
		{
			m_bindPSMap.Remove(iter->Key);
		}
	}
}

void APhysCalculator::UpdateCharacterEffects()
{

	for (int32 i = 0; i < m_pCharacterList.Num(); i++)
	{
		if (!m_pCharacterList[i]) continue;
		int32 j = 0;
		while (j < m_pCharacterList[i]->m_pEffects.Num())
		{
			if (!m_pCharacterList[i]->m_pEffects[j])
			{
				m_pCharacterList[i]->m_pEffects.RemoveAt(j);
				continue;
			}

			bool shouldDeleteEffect = false;
			//这个isEffectOn局部变量主要针对间歇性效果设置的，即例如有些效果是第1、3、9帧发动效果，只有当计时器等于这些特殊的
			//	时间点才会发动
			bool isEffectOn = true;
			//Effect可分为以下几种
			//1. ContinuousEffect，即主体几何体存在的每一帧都会起作用
			//2. TickEffect，与Continuous的区别是脱离几何体，在规定时长的每一帧都会起作用
			//3. IntervalEffect, 只在某些规定的帧号发动，可循环，不可脱离几何体
			//4. OneTimeEffect，顾名思义只作用一次，例如劈砍
			if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "ContinuousEffect")
			{
				if ((!m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo || !m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_isGeoValid) &&
					!m_pCharacterList[i]->m_pEffects[j]->m_isPermenant)
				{
					shouldDeleteEffect = true;
				}
				else
				{
					if (m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_physGeoType == EPhysGeoType::PGT_Line)
					{
						APhysLine* pLine = Cast<APhysLine>(m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo);
						if (pLine->m_pHitCharacter != m_pCharacterList[i]) shouldDeleteEffect = true;
					}
					else if (m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_physGeoType == EPhysGeoType::PGT_Poly)
					{
						APhysPolygon* pPoly = Cast<APhysPolygon>(m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo);
						if (!pPoly->m_pOverlapCharacters.Contains(m_pCharacterList[i]) && m_pCharacterList[i]->m_pEffects[j]->m_launchType == 0)
							shouldDeleteEffect = true;
					}
					else if (m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_physGeoType == EPhysGeoType::PGT_Point)
					{
						APhysPoint* pPoint = Cast<APhysPoint>(m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo);
						if (!pPoint->m_pOverlapCharacters.Contains(m_pCharacterList[i])) shouldDeleteEffect = true;
					}
					else if (m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_physGeoType == EPhysGeoType::PGT_Actor || 
						m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_physGeoType == EPhysGeoType::PGT_DetonationActor)
					{
						ABasePhysActor* pActor = Cast<ABasePhysActor>(m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo);
						if (!pActor->m_pOverlapCharacters.Contains(m_pCharacterList[i])) shouldDeleteEffect = true;
					}
				}
			}
			else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "TickEffect")
			{
				if (m_pCharacterList[i]->m_pEffects[j]->m_curTickTime >= m_pCharacterList[i]->m_pEffects[j]->m_duration &&
					!m_pCharacterList[i]->m_pEffects[j]->m_isPermenant)
					shouldDeleteEffect = true;
				else m_pCharacterList[i]->m_pEffects[j]->m_curTickTime += 1;
			}
			else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "IntervalEffect")
			{
				if (m_pCharacterList[i]->m_pEffects[j]->m_curTickTime >= m_pCharacterList[i]->m_pEffects[j]->m_duration && 
					!m_pCharacterList[i]->m_pEffects[j]->m_isPermenant)
					shouldDeleteEffect = true;
				else
				{
					if (!m_pCharacterList[i]->m_pEffects[j]->m_effectOnIntervalList.Contains(m_pCharacterList[i]->m_pEffects[j]->m_curTickTime))
						isEffectOn = false;
					m_pCharacterList[i]->m_pEffects[j]->m_curTickTime += 1;
				}
			}
			else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "OneTimeEffect")
			{
				if (m_pCharacterList[i]->m_pEffects[j]->m_launchType == 0)
				{
					if (m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone && (!m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo || !m_pCharacterList[i]->m_pEffects[j]->m_pOriginGeo->m_isGeoValid))
						shouldDeleteEffect = true;
				}
				else
				{
					if (m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone)
						shouldDeleteEffect = true;
				}
			}
			else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AttributeReactionEffect" ||
				m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AttributeReactionEffect_InstrinsicActive" ||
				m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AttributeReactionEffect_InstrinsicPassive")
			{
				if (m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone)
					shouldDeleteEffect = true;
				else
				{
					if (!m_pCharacterList[i]->m_pEffects[j]->m_effectOnIntervalList.Contains(m_pCharacterList[i]->m_pEffects[j]->m_curTickTime))
						isEffectOn = false;
					m_pCharacterList[i]->m_pEffects[j]->m_curTickTime += 1;
				}
			}
			else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AccumulateJudgeEffect")
			{
				if ((m_pCharacterList[i]->m_pEffects[j]->m_curTickTime >= m_pCharacterList[i]->m_pEffects[j]->m_duration || 
					m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone) && !m_pCharacterList[i]->m_pEffects[j]->m_isPermenant)
					shouldDeleteEffect = true;
				else m_pCharacterList[i]->m_pEffects[j]->m_curTickTime += 1;
			}
			else
			{
				if (!m_pCharacterList[i]->m_pEffects[j]->m_isPermenant)
				{
					if (m_pCharacterList[i]->m_pEffects[j]->m_curTickTime >= m_pCharacterList[i]->m_pEffects[j]->m_duration)
						shouldDeleteEffect = true;
					else m_pCharacterList[i]->m_pEffects[j]->m_curTickTime += 1;
				}
			}

			if (shouldDeleteEffect)
			{
				APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
				ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
				UEffect* pEffect = m_pCharacterList[i]->m_pEffects[j];
				if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == m_pCharacterList[i])
					pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pEffect, false);
				EffectEndCharacter(pEffect, m_pCharacterList[i]);
				//m_pCharacterList[i]->NotifyRemoveCharacterState(pEffect->m_effectName);
				DestroyEffect(pEffect);
				m_pCharacterList[i]->m_pEffects.RemoveAt(j);
				
				//m_pCharacterList[i]->m_pEffects.RemoveAt(j);
				//m_pCharacterList[i]->m_pEffects[j]->EffectEndCharacter(m_pCharacterList[i]);
				//pEffect->ConditionalBeginDestroy();
				continue;
			}

			if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "OneTimeEffect")
			{
				if (!m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone)
				{
					//m_pCharacterList[i]->m_pEffects[j]->EffectOnCharacter(m_pCharacterList[i]);
					EffectOnCharacter(m_pCharacterList[i]->m_pEffects[j], m_pCharacterList[i]);
					m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone = true;
				}
			}
			else
			{
				if (!isEffectOn || m_pCharacterList[i]->m_pEffects[j]->m_effectType == "PassiveEffect" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "PassiveActivate" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "SuperposeEffect" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "JudgeActivatedTarget" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "JudgeActivatedSource" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "HurtPassiveActivate" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "RecoverPassiveActivate" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AccumulateJudgeEffect" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "DiscardActivate" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "EffectDeleteEffect" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "DeadActivate" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AttributeReactionEffect")
				{
					j += 1;
					continue;
				}
				if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "ContinuousEffect" ||
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "TickEffect")
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "PhysCalculator::UpdateCharacterEffect launch IntervalEffect");
					EffectOnCharacter(m_pCharacterList[i]->m_pEffects[j], m_pCharacterList[i]);
					//m_pCharacterList[i]->m_pEffects[j]->m_isOnTimeEffectDone = true;
				}
				else if (m_pCharacterList[i]->m_pEffects[j]->m_effectType == "IntervalEffect" || 
					m_pCharacterList[i]->m_pEffects[j]->m_effectType == "AttributeReactionEffect_InstrinsicActive")
				{
					if (isEffectOn)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "PhysCalculator::UpdateCharacterEffect launch IntervalEffect");
						EffectOnCharacter(m_pCharacterList[i]->m_pEffects[j], m_pCharacterList[i]);
					}
				}
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "PhysCalculator::UpdateCharacterEffect launch IntervalEffect");
					EffectOnCharacter(m_pCharacterList[i]->m_pEffects[j], m_pCharacterList[i]);
				}
			}
			j += 1;
		}
	}
}

void APhysCalculator::AddPhysGeo(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter, int32 campFlag)
{
	pGeo->m_pPhysCalculator = this;
	if (pGeo->m_entityID == -1)
	{
		int32 geoID = GenerateUnOccupiedGeoID();
		pGeo->m_entityID = geoID;
		m_occupyGeoIDs.Add(geoID, pGeo);
	}
	/*for (int32 i = 0; i<pGeo->m_defaultReactionInfoNbs.Num(); i++)
	{
		for (int32 j = 0; j<m_reactionInfoCaches.Num(); j++)
		{
			if (pGeo->m_defaultReactionInfoNbs[i] == m_reactionInfoCaches[j].reactionNb)
			{
				pGeo->m_reactionInfos.Add(m_reactionInfoCaches[j]);
				break;
			}
		}
	}*/
	if (pGeo->m_physGeoType == EPhysGeoType::PGT_Actor || pGeo->m_physGeoType == EPhysGeoType::PGT_DetonationActor)
	{
		if (pGeo->m_physGeoType == EPhysGeoType::PGT_DetonationActor)
		{
			ADetonationActor* pDetonationActor = Cast<ADetonationActor>(pGeo);
			pDetonationActor->InitialDetonationActor();
			pDetonationActor->InitialPhysActor(campFlag, pCharacter, m_defaultSpawnHeight);
			m_pPhysActors.Add(pDetonationActor);
			pDetonationActor->m_isInitial = true;
		}
		else
		{
			ABasePhysActor* pActor = Cast<ABasePhysActor>(pGeo);
			pActor->InitialPhysActor(campFlag, pCharacter, m_defaultSpawnHeight);
			m_pPhysActors.Add(pActor);
			pActor->m_isInitial = true;
		}
		
	}
	else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Point)
	{
		APhysPoint* pPoint = Cast<APhysPoint>(pGeo);
		pPoint->InitialPoint(pCharacter, campFlag, m_geoActionTimesPerTick);
		m_pPoints.Add(pPoint);
		pPoint->m_isInitial = true;
	}
	/*else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Line)
	{
		APhysLine* pLine = Cast<APhysLine>(pGeo);
		if (pCharacter)
		{
			FLogicVec2D spawnPoint = pCharacter->m_logicSpawnPoint;
			pLine->InitialLine(spawnPoint, pCharacter, campFlag, pCharacter->m_curLogicForwardDir, m_defaultSpawnHeight);
		}
		m_pLines.Add(pLine);
		pLine->m_isInitial = true;
	}*/
	else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Poly)
	{
		APhysPolygon* pPolygon = Cast<APhysPolygon>(pGeo);
		pPolygon->InitialPolygon(pCharacter, campFlag, m_defaultSpawnHeight);
		m_pPolygons.Add(pPolygon);
		pPolygon->m_isInitial = true;
	}
	/*for (int32 i = 0; i<pGeo->m_pBasicComponent->ComponentTags.Num(); i++)
	{
		AddReactionInfoAccordingToTag(pGeo->m_pBasicComponent->ComponentTags[i], pGeo);
	}*/
	//如pGeo的主人指针不为空，说明该几何体是由角色发出，这时要检测角色的Superpose效果，例如附带火攻击，根据几何体附带的特殊字段判断，此时进行如下操作
	//1. 根据附带效果给几何体添加AppendEffect
	//2. 如有需要依附于骨骼插槽的特效，生成特效
	//3. 如需要为几何体附加新一层特效，此时激活几何体附加特效（因为考虑到每个几何体的附加特效不同，例如蜉蝣和至柔都能遇火变异，但特效是不同的，具体PS储存在几何体的一个Map内）
	//4. 一个几何体可能触发多个附加效果，这时只取
	if (pGeo->m_physGeoType != EPhysGeoType::PGT_Actor && pGeo->m_physGeoType != EPhysGeoType::PGT_DetonationActor)
		AppendSuperpositionEffects(pGeo);
	m_pPhysGeos.Add(pGeo);
}

void APhysCalculator::PlayHitParticle(ABasePhysGeo* pGeo, FVector loc)
{
	if (!pGeo) return;
	UParticleSystem* pHitParticle = NULL;
	if (pGeo->m_pHitParticleSystem) pHitParticle = pGeo->m_pHitParticleSystem;
	else
	{
		if (pGeo->m_attributeList.Num() == 0) pHitParticle = m_pAttributeHitPSMap[-1];
		else
		{
			if (!m_pAttributeHitPSMap.Contains(pGeo->m_attributeList.Last())) pHitParticle = m_pAttributeHitPSMap[-1];
			else pHitParticle = m_pAttributeHitPSMap[pGeo->m_attributeList.Last()];
		}
	}
	if (pHitParticle) UGameplayStatics::SpawnEmitterAtLocation(this, pHitParticle, loc);
}

void APhysCalculator::DeletePhysGeo(ABasePhysGeo* pGeo)
{
	if (!pGeo) return;
	m_occupyGeoIDs.Remove(pGeo->m_entityID);
	if (m_spawnMutateActorPSMap.Contains(pGeo))
	{
		m_spawnMutateActorPSMap[pGeo]->DeactivateSystem();
		m_spawnMutateActorPSMap.Remove(pGeo);
	}
	if (m_spawnMutateActorMap.Contains(pGeo))
	{
		if (m_spawnMutateActorMap[pGeo])
		{
			m_spawnMutateActorMap[pGeo]->Destroy();
			m_spawnMutateActorMap[pGeo]->ConditionalBeginDestroy();
		}
		m_spawnMutateActorMap.Remove(pGeo);
	}
	if (pGeo->m_physGeoType == EPhysGeoType::PGT_Actor || pGeo->m_physGeoType == EPhysGeoType::PGT_DetonationActor)
	{
		ABasePhysActor* pActor = Cast<ABasePhysActor>(pGeo);
		pActor->DeleteTempObstacleFromRecastNav();
		m_pPhysActors.Remove(pActor);
		m_pPhysGeos.Remove(pActor);
		if (pActor && pActor->IsValidLowLevel())
		{
			pActor->Destroy();
			pActor->ConditionalBeginDestroy();
		}
	}
	else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Point)
	{
		APhysPoint* pPoint = Cast<APhysPoint>(pGeo);
		m_pPoints.Remove(pPoint);
		m_pPhysGeos.Remove(pPoint);
		if (pPoint && pPoint->IsValidLowLevel())
		{
			pPoint->Destroy();
			pPoint->ConditionalBeginDestroy();
		}
	}
	else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Line)
	{
		APhysLine* pLine = Cast<APhysLine>(pGeo);
		m_pLines.Remove(pLine);
		m_pPhysGeos.Remove(pLine);
		if (pLine && pLine->IsValidLowLevel())
		{
			pLine->Destroy();
			pLine->ConditionalBeginDestroy();
		}
	}
	else if (pGeo->m_physGeoType == EPhysGeoType::PGT_Poly)
	{
		APhysPolygon* pPolygon = Cast<APhysPolygon>(pGeo);
		m_pPolygons.Remove(pPolygon);
		m_pPhysGeos.Remove(pPolygon);
		if (pPolygon && pPolygon->IsValidLowLevel())
		{
			pPolygon->Destroy();
			pPolygon->ConditionalBeginDestroy();
		}
	}
}

void APhysCalculator::CharacterCallDeleteGeo(ABaseCharacter* pCharacter)
{
	for (int32 i = 0; i < m_pLines.Num(); i++)
	{
		if (m_pLines[i]->m_pHost == pCharacter)
		{
			m_pLines[i]->m_isGeoValid = false;
		}
	}
	for (int32 i = 0; i < m_pPolygons.Num(); i++)
	{
		if (m_pPolygons[i]->m_pHost == pCharacter)
		{
			m_pPolygons[i]->m_isGeoValid = false;
		}
	}
}
/*

void APhysCalculator::ReactionGeoTransform(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo)
{
	if (!pGeo1 || !pGeo2) return;
	ABasePhysGeo* pTransformGeo1 = NULL;
	ABasePhysGeo* pTransformGeo2 = NULL;
	int32 originalCampFlag1 = pGeo1->m_campFlag;
	FVector geoLoc1 = pGeo1->GetActorLocation();
	FRotator geoRot1 = pGeo1->GetActorRotation();
	int32 originalCampFlag2 = pGeo2->m_campFlag;
	FVector geoLoc2 = pGeo2->GetActorLocation();
	FRotator geoRot2 = pGeo2->GetActorRotation();

	if (reactionInfo.BPTransformActor1Class && !pGeo1->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))))
	{
		pTransformGeo1 = GetWorld()->SpawnActor<ABasePhysGeo>(reactionInfo.BPTransformActor1Class, geoLoc1, geoRot1);
	}
	if (reactionInfo.BPTransformActor2Class && !pGeo2->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))))
	{
		pTransformGeo2 = GetWorld()->SpawnActor<ABasePhysGeo>(reactionInfo.BPTransformActor2Class, geoLoc2, geoRot2);
	}
	if (pTransformGeo1)
	{
		for (int32 i = 0; i < pGeo1->m_pRootGeos.Num(); i++)
		{
			//说明互为rootGeo，那么由于pGeo1即将被删除，所以将pTransformGeo1添加到所有互为RootGeo中，避免重复反应
			if (pGeo1->m_pRootGeos[i] && pGeo1->m_pRootGeos[i]->m_pRootGeos.Contains(pGeo1) &&
				!pGeo1->m_pRootGeos[i]->m_pRootGeos.Contains(pTransformGeo1))
				pGeo1->m_pRootGeos[i]->m_pRootGeos.Add(pTransformGeo1);
			if (pGeo1->m_pRootGeos[i]) pTransformGeo1->m_pRootGeos.Add(pGeo1->m_pRootGeos[i]);
		}
	}
	if (pTransformGeo2)
	{
		for (int32 i = 0; i < pGeo2->m_pRootGeos.Num(); i++)
		{
			//说明互为rootGeo，那么由于pGeo1即将被删除，所以将pTransformGeo1添加到所有互为RootGeo中，避免重复反应
			if (pGeo2->m_pRootGeos[i] && pGeo2->m_pRootGeos[i]->m_pRootGeos.Contains(pGeo2) &&
				!pGeo2->m_pRootGeos[i]->m_pRootGeos.Contains(pTransformGeo2))
				pGeo2->m_pRootGeos[i]->m_pRootGeos.Add(pTransformGeo2);
			if (pGeo2->m_pRootGeos[i]) pTransformGeo2->m_pRootGeos.Add(pGeo2->m_pRootGeos[i]);
		}
	}
	if (pTransformGeo1)
	{
		if (!pTransformGeo1->m_pRootGeos.Contains(pGeo1)) pTransformGeo1->m_pRootGeos.Add(pGeo1);
		if (!pTransformGeo1->m_pRootGeos.Contains(pGeo2)) pTransformGeo1->m_pRootGeos.Add(pGeo2);
	}
	if (pTransformGeo2)
	{
		if (!pTransformGeo2->m_pRootGeos.Contains(pGeo1)) pTransformGeo2->m_pRootGeos.Add(pGeo1);
		if (!pTransformGeo2->m_pRootGeos.Contains(pGeo2)) pTransformGeo2->m_pRootGeos.Add(pGeo2);
	}
	if (pTransformGeo1 && pTransformGeo2)
	{
		if (!pTransformGeo1->m_pRootGeos.Contains(pTransformGeo2))
			pTransformGeo1->m_pRootGeos.Add(pTransformGeo2);
		if (!pTransformGeo2->m_pRootGeos.Contains(pTransformGeo1))
			pTransformGeo2->m_pRootGeos.Add(pTransformGeo1);
	}

	if (pGeo1 && pGeo2)
	{
		int32 pairNb = FindReactionPair(pGeo1, pGeo2);
		if (pairNb != -1) m_reactionPairs[pairNb].hasReactionOccur = true;
	}
	if (pGeo1 && pTransformGeo1)
	{
		pTransformGeo1->m_moveOrder = pGeo1->m_moveOrder;
		pTransformGeo1->m_rotateOrder = pGeo1->m_rotateOrder;
		pTransformGeo1->m_logicPos2D = pGeo1->m_logicPos2D;
		pTransformGeo1->m_logicForwardDir = pGeo1->m_logicForwardDir;
		if (pTransformGeo1->m_physGeoType == EPhysGeoType::PGT_Point)
		{
			APhysPoint* pTransformPoint = Cast<APhysPoint>(pTransformGeo1);
			if (pGeo1->m_physGeoType == EPhysGeoType::PGT_Point)
			{
				APhysPoint* pOriginPoint = Cast<APhysPoint>(pGeo1);
				pTransformPoint->m_logicFireDir = pOriginPoint->m_logicFireDir;
			}
			else
			{
				pTransformPoint->m_logicFireDir.X = pGeo1->m_logicForwardDir.X;
				pTransformPoint->m_logicFireDir.Y = pGeo1->m_logicForwardDir.Y;
			}
		}
		if (pGeo1->m_pHost)
		{
			pTransformGeo1->m_pHost = pGeo1->m_pHost;
			pGeo1->m_pHost->m_pControlPhysGeos.Add(pTransformGeo1);
		}
		pTransformGeo1->m_curMovePointNb = pGeo1->m_curMovePointNb;
		pTransformGeo1->m_curRotateNb = pGeo1->m_curRotateNb;
		pTransformGeo1->m_curRandTarget = pGeo1->m_curRandTarget;
		pGeo1->ReactionParticleEmit("Transform", reactionInfo.reactionTag);
		DeletePhysGeo(pGeo1);
	}
	if (pGeo2 && pTransformGeo2)
	{
		pTransformGeo2->m_moveOrder = pGeo2->m_moveOrder;
		pTransformGeo2->m_rotateOrder = pGeo2->m_rotateOrder;
		pTransformGeo2->m_logicPos2D = pGeo2->m_logicPos2D;
		pTransformGeo2->m_logicForwardDir = pGeo2->m_logicForwardDir;
		if (pTransformGeo2->m_physGeoType == EPhysGeoType::PGT_Point)
		{
			APhysPoint* pTransformPoint = Cast<APhysPoint>(pTransformGeo2);
			if (pGeo2->m_physGeoType == EPhysGeoType::PGT_Point)
			{
				APhysPoint* pOriginPoint = Cast<APhysPoint>(pGeo2);
				pTransformPoint->m_logicFireDir = pOriginPoint->m_logicFireDir;
			}
			else
			{
				pTransformPoint->m_logicFireDir.X = pGeo2->m_logicForwardDir.X;
				pTransformPoint->m_logicFireDir.Y = pGeo2->m_logicForwardDir.Y;
			}
		}
		if (pGeo2->m_pHost)
		{
			pTransformGeo2->m_pHost = pGeo2->m_pHost;
			pGeo2->m_pHost->m_pControlPhysGeos.Add(pTransformGeo2);
		}
		pTransformGeo2->m_curMovePointNb = pGeo2->m_curMovePointNb;
		pTransformGeo2->m_curRotateNb = pGeo2->m_curRotateNb;
		pTransformGeo2->m_curRandTarget = pGeo2->m_curRandTarget;
		pGeo2->ReactionParticleEmit("Transform", reactionInfo.HostTag);
		DeletePhysGeo(pGeo2);
	}

	if (pTransformGeo1) AddPhysGeo(pTransformGeo1, pGeo1->m_pHost, originalCampFlag1);
	if (pTransformGeo2) AddPhysGeo(pTransformGeo2, pGeo2->m_pHost, originalCampFlag2);

	if (pTransformGeo1 && pTransformGeo2)
	{
		int32 pairNb = GenerateUnOccupiedPairID();
		FReactionPair newPair(pairNb, pTransformGeo1, pTransformGeo2, NULL, reactionInfo, FLogicVec2D(0, 0), 0);
		newPair.hasReactionOccur = true;
		m_reactionPairs.Add(newPair);
	}
	/ *if (pTransformGeo1) pTransformGeo1->m_motionType = EPhysActorMotionType::PAMT_Normal;
	if (pTransformGeo2) pTransformGeo2->m_motionType = EPhysActorMotionType::PAMT_Normal;
	if (pGeo1) pGeo1->m_motionType = EPhysActorMotionType::PAMT_Normal;
	if (pGeo2) pGeo2->m_motionType = EPhysActorMotionType::PAMT_Normal;* /
}*/
/*

bool APhysCalculator::DetermineReactionType(int32 pairNb)
{
	bool matchFlag = false;
	for (int32 i = 0; i<m_reactionPairs[pairNb].pReactionActor1->m_reactionInfos.Num(); i++)
	{
		if (m_reactionPairs[pairNb].pReactionActor2->m_pBasicComponent->ComponentHasTag(m_reactionPairs[pairNb].pReactionActor1->m_reactionInfos[i].reactionTag) &&
			m_reactionPairs[pairNb].pReactionActor1->m_reactionInfos[i].reactionType != EReactionType::PRT_ReflectRefract &&
			m_reactionPairs[pairNb].pReactionActor1->m_reactionInfos[i].reactionType != EReactionType::PRT_BlockLine)
		{
			m_reactionPairs[pairNb].pariReactionInfo = m_reactionPairs[pairNb].pReactionActor1->m_reactionInfos[i];
			matchFlag = true;
			break;
		}
	}
	if (!matchFlag)
	{
		for (int32 i = 0; i<m_reactionPairs[pairNb].pReactionActor2->m_reactionInfos.Num(); i++)
		{
			if (m_reactionPairs[pairNb].pReactionActor1->m_pBasicComponent->ComponentHasTag(m_reactionPairs[pairNb].pReactionActor2->m_reactionInfos[i].reactionTag) &&
				m_reactionPairs[pairNb].pReactionActor2->m_reactionInfos[i].reactionType != EReactionType::PRT_ReflectRefract &&
				m_reactionPairs[pairNb].pReactionActor2->m_reactionInfos[i].reactionType != EReactionType::PRT_BlockLine)
			{
				m_reactionPairs[pairNb].pariReactionInfo = m_reactionPairs[pairNb].pReactionActor2->m_reactionInfos[i];
				ABasePhysGeo* tempGeo = m_reactionPairs[pairNb].pReactionActor2;
				m_reactionPairs[pairNb].pReactionActor2 = m_reactionPairs[pairNb].pReactionActor1;
				m_reactionPairs[pairNb].pReactionActor1 = tempGeo;
				matchFlag = true;
				break;
			}
		}
	}
	if (!matchFlag)
	{
		return false;
	}
	return true;

}*/
/*

void APhysCalculator::ReactionGeoAddTag(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo, const int32& pairNb)
{
	if (!pGeo1 || !pGeo2) return;
	if (m_reactionPairs[pairNb].hasReactionOccur) return;
	if (pGeo1->m_pRootGeos.Contains(pGeo2) || pGeo2->m_pRootGeos.Contains(pGeo1) ||
		pGeo1->m_pSonGeos.Contains(pGeo2) || pGeo2->m_pSonGeos.Contains(pGeo1))
		return;

	if (reactionInfo.modifyTag1 != FName(TEXT("NULL")) && !pGeo1->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))))
	{
		bool isReactionTagBelongToAttachment = false;
		if (pGeo1->m_pAttachEquipInfo && pGeo1->m_pAttachEquipInfo->m_actorTags.Contains(reactionInfo.HostTag))
			isReactionTagBelongToAttachment = true;
		if (isReactionTagBelongToAttachment && !pGeo1->m_pAttachEquipInfo->m_actorTags.Contains(reactionInfo.modifyTag1))
			pGeo1->m_pAttachEquipInfo->m_actorTags.Add(reactionInfo.modifyTag1);
		if (!pGeo1->m_pBasicComponent->ComponentHasTag(reactionInfo.modifyTag1))
		{
			pGeo1->m_pBasicComponent->ComponentTags.Add(reactionInfo.modifyTag1);
			pGeo1->ReactionParticleEmit("AddTag", reactionInfo.reactionTag);
			AddReactionInfoAccordingToTag(reactionInfo.modifyTag1, pGeo1);
		}
	}
	if (reactionInfo.modifyTag2 != FName(TEXT("NULL")) && !pGeo2->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))))
	{
		bool isReactionTagBelongToAttachment = false;
		if (pGeo2->m_pAttachEquipInfo && pGeo2->m_pAttachEquipInfo->m_actorTags.Contains(reactionInfo.reactionTag))
			isReactionTagBelongToAttachment = true;
		if (isReactionTagBelongToAttachment && !pGeo2->m_pAttachEquipInfo->m_actorTags.Contains(reactionInfo.modifyTag2))
			pGeo2->m_pAttachEquipInfo->m_actorTags.Add(reactionInfo.modifyTag2);
		if (!pGeo2->m_pBasicComponent->ComponentHasTag(reactionInfo.modifyTag2))
		{
			pGeo2->m_pBasicComponent->ComponentTags.Add(reactionInfo.modifyTag2);
			pGeo2->ReactionParticleEmit("AddTag", reactionInfo.HostTag);
			AddReactionInfoAccordingToTag(reactionInfo.modifyTag2, pGeo2);
		}
	}
}

void APhysCalculator::ReactionGeoSubtractTag(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo, const int32& pairNb)
{
	if (!pGeo1 || !pGeo2) return;
	if (m_reactionPairs[pairNb].hasReactionOccur) return;
	if (pGeo1->m_pRootGeos.Contains(pGeo2) || pGeo2->m_pRootGeos.Contains(pGeo1) ||
		pGeo1->m_pSonGeos.Contains(pGeo2) || pGeo2->m_pSonGeos.Contains(pGeo1))
		return;

	if (reactionInfo.modifyTag1 != FName(TEXT("NULL")) &&
		!pGeo1->m_pBasicComponent->ComponentHasTag(FName(TEXT("BaseSkill"))) &&
		!pGeo1->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))) &&
		pGeo1->m_level <= pGeo2->m_level &&
		pGeo1->m_physGeoType != EPhysGeoType::PGT_Line &&
		pGeo1->m_physGeoType != EPhysGeoType::PGT_Point)
	{
		bool isReactionTagBelongToAttachment = false;
		if (pGeo1->m_pAttachEquipInfo)
		{
			for (int32 i = 0; i < pGeo1->m_pAttachEquipInfo->m_actorTags.Num(); i++)
			{
				if (pGeo1->m_pAttachEquipInfo->m_actorTags[i] == reactionInfo.HostTag)
				{
					isReactionTagBelongToAttachment = true;
					break;
				}
			}
		}
		if (isReactionTagBelongToAttachment)
		{
			for (int32 i = 0; i < pGeo1->m_pAttachEquipInfo->m_actorTags.Num(); i++)
			{
				if (pGeo1->m_pAttachEquipInfo->m_actorTags[i] == reactionInfo.modifyTag1)
				{
					pGeo1->m_pAttachEquipInfo->m_actorTags.RemoveAt(i);
					break;
				}
			}
		}
		if (pGeo1->m_pBasicComponent->ComponentHasTag(reactionInfo.modifyTag1))
		{
			pGeo1->m_pBasicComponent->ComponentTags.Remove(reactionInfo.modifyTag1);
			pGeo1->ReactionParticleEmit("SubtractTag", reactionInfo.reactionTag);
			SubtractReactionInfoAccordingToTag(reactionInfo.modifyTag1, pGeo1);
		}
	}
	if (reactionInfo.modifyTag2 != FName(TEXT("NULL")) &&
		!pGeo2->m_pBasicComponent->ComponentHasTag(FName(TEXT("BaseSkill"))) &&
		!pGeo2->m_pBasicComponent->ComponentHasTag(FName(TEXT("BigPoly"))) &&
		pGeo2->m_level <= pGeo1->m_level &&
		pGeo2->m_physGeoType != EPhysGeoType::PGT_Line &&
		pGeo2->m_physGeoType != EPhysGeoType::PGT_Point)
	{
		bool isReactionTagBelongToAttachment = false;
		if (pGeo2->m_pAttachEquipInfo)
		{
			for (int32 i = 0; i < pGeo2->m_pAttachEquipInfo->m_actorTags.Num(); i++)
			{
				if (pGeo2->m_pAttachEquipInfo->m_actorTags[i] == reactionInfo.reactionTag)
				{
					isReactionTagBelongToAttachment = true;
					break;
				}
			}
		}
		if (isReactionTagBelongToAttachment)
		{
			for (int32 i = 0; i < pGeo2->m_pAttachEquipInfo->m_actorTags.Num(); i++)
			{
				if (pGeo2->m_pAttachEquipInfo->m_actorTags[i] == reactionInfo.modifyTag2)
				{
					pGeo2->m_pAttachEquipInfo->m_actorTags.RemoveAt(i);
					break;
				}
			}
		}
		if (pGeo2->m_pBasicComponent->ComponentHasTag(reactionInfo.modifyTag2))
		{
			pGeo2->m_pBasicComponent->ComponentTags.Remove(reactionInfo.modifyTag2);
			pGeo2->ReactionParticleEmit("SubtractTag", reactionInfo.HostTag);
			SubtractReactionInfoAccordingToTag(reactionInfo.modifyTag2, pGeo2);
		}
	}
}*/
/*

void APhysCalculator::AddReactionInfoCache(FReactionInfo reactionInfo)
{
	m_reactionInfoCaches.Add(reactionInfo);
}*/

/*
void APhysCalculator::AddReactionInfoAccordingToTag(FName tag, ABasePhysGeo* pGeo)
{
	for (int32 i = 0; i<pGeo->m_reactionInfos.Num(); i++)
	{
		if (pGeo->m_reactionInfos[i].HostTag == tag) return;
	}
	for (int32 i = 0; i<m_reactionInfoCaches.Num(); i++)
	{
		if (m_reactionInfoCaches[i].HostTag == tag)
		{
			pGeo->m_reactionInfos.Add(m_reactionInfoCaches[i]);
			return;
		}
	}
}*/

/*
void APhysCalculator::SubtractReactionInfoAccordingToTag(FName tag, ABasePhysGeo* pGeo)
{
	for (int32 i = 0; i<pGeo->m_reactionInfos.Num(); i++)
	{
		if (pGeo->m_reactionInfos[i].HostTag == tag)
		{
			pGeo->m_reactionInfos.RemoveAt(i);
			return;
		}
	}
}*/
/*

void APhysCalculator::CollectReactionPair()
{
	for (int32 i = 0; i<m_pPhysGeos.Num(); i++)
	{
		if (!m_pPhysGeos[i]) continue;
		for (int32 j = 0; j<m_pPhysGeos[i]->m_preReactionPairs.Num(); j++)
		{
			ABasePhysGeo* pGeo1 = FindEntity(m_pPhysGeos[i]->m_preReactionPairs[j].geo1ID);
			ABasePhysGeo* pGeo2 = FindEntity(m_pPhysGeos[i]->m_preReactionPairs[j].geo2ID);
			if (!pGeo1 || !pGeo2 || pGeo1 == pGeo2) continue;
			int32 pairNb = FindReactionPair(pGeo1, pGeo2);
			if (pairNb != -1) continue;
			FReactionPair newPair;
			newPair.pReactionActor1 = pGeo1;
			newPair.pReactionActor2 = pGeo2;
			newPair.hasReactionOccur = false;
			int32 newPairNb = GenerateUnOccupiedPairID();
			newPair.reactionPairID = newPairNb;
			m_reactionPairs.Add(newPair);
		}
		for (int32 j = 0; j<m_pPhysGeos[i]->m_reactionSpawnPairs.Num(); j++)
		{
			ABasePhysGeo* pGeo1 = FindEntity(m_pPhysGeos[i]->m_reactionSpawnPairs[j].geo1ID);
			ABasePhysGeo* pGeo2 = FindEntity(m_pPhysGeos[i]->m_reactionSpawnPairs[j].geo2ID);
			if (!pGeo1 || !pGeo2) continue;
			int32 pairNb = FindReactionPair(pGeo1, pGeo2);
			if (pairNb != -1)
			{
				if (m_reactionPairs[pairNb].hasReactionOccur) continue;
				if (pGeo1->m_pRootGeos.Contains(pGeo2) || pGeo2->m_pRootGeos.Contains(pGeo1))
				{
					m_reactionPairs[pairNb].hasReactionOccur = true;
					continue;
				}
			}
			FVector spawnLocVec(m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.X,
				m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.Y,
				m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.Z);
			int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnDir);
			FRotator spawnRot(0, yaw, 0);
			ABasePhysGeo* pSpawnGeo = GetWorld()->SpawnActor<ABasePhysGeo>(
				m_pPhysGeos[i]->m_reactionSpawnPairs[j].reactionInfo.BPSpawnActorClass, spawnLocVec, spawnRot);
			pSpawnGeo->m_logicPos2D = FLogicVec2D(m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.X,
				m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.Y);
			if (pSpawnGeo->m_physGeoType == EPhysGeoType::PGT_Line)
			{
				APhysLine* pLine = Cast<APhysLine>(pSpawnGeo);
				pLine->m_logicForwardDir = m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnDir;
				pLine->m_campFlag = m_pPhysGeos[i]->m_reactionSpawnPairs[j].campFlag;
				pLine->m_logicLineLength = 0;
				pLine->m_defaultHeight = pGeo1->m_defaultHeight;
			}
			for (int32 k = 0; k < pGeo1->m_pRootGeos.Num(); k++)
			{
				if (!pSpawnGeo->m_pRootGeos.Contains(pGeo1->m_pRootGeos[k])) pSpawnGeo->m_pRootGeos.Add(pGeo1->m_pRootGeos[k]);
			}
			for (int32 k = 0; k < pGeo2->m_pRootGeos.Num(); k++)
			{
				if (!pSpawnGeo->m_pRootGeos.Contains(pGeo2->m_pRootGeos[k])) pSpawnGeo->m_pRootGeos.Add(pGeo2->m_pRootGeos[k]);
			}
			pSpawnGeo->m_pRootGeos.Add(pGeo1);
			pSpawnGeo->m_pRootGeos.Add(pGeo2);
			AddPhysGeo(pSpawnGeo, NULL, 0);
			int32 maxHierachy = FMath::Max(pGeo1->m_hierachy, pGeo2->m_hierachy);
			pSpawnGeo->m_hierachy = maxHierachy + 1;
			pGeo1->m_pSonGeos.Add(pSpawnGeo);
			pGeo2->m_pSecondarySonGeos.Add(pSpawnGeo);
			if (pairNb == -1)
			{
				int32 tempPairNb = GenerateUnOccupiedPairID();
				int32 tempYaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnDir);
				FReactionPair newPair(tempPairNb, pGeo1, pGeo2, pSpawnGeo,
					m_pPhysGeos[i]->m_reactionSpawnPairs[j].reactionInfo,
					FLogicVec2D(m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.X, m_pPhysGeos[i]->m_reactionSpawnPairs[j].logicSpawnLoc.Y), tempYaw);
				newPair.hasReactionOccur = true;
				m_reactionPairs.Add(newPair);
			}
			else
			{
				m_reactionPairs[pairNb].pSonGeo = pSpawnGeo;
				m_reactionPairs[pairNb].hasReactionOccur = true;
			}
		}
		for (int32 j = 0; j<m_pPhysGeos[i]->m_seperatePairs.Num(); j++)
		{
			for (int32 k = 0; k<m_reactionPairs.Num(); k++)
			{
				if ((m_reactionPairs[k].pReactionActor1->m_entityID == m_pPhysGeos[i]->m_seperatePairs[j].geo1ID &&
					m_reactionPairs[k].pReactionActor2->m_entityID == m_pPhysGeos[i]->m_seperatePairs[j].geo2ID)
					||
					(m_reactionPairs[k].pReactionActor1->m_entityID == m_pPhysGeos[i]->m_seperatePairs[j].geo2ID &&
						m_reactionPairs[k].pReactionActor2->m_entityID == m_pPhysGeos[i]->m_seperatePairs[j].geo1ID))
				{
					if (m_reactionPairs[k].pSonGeo) m_reactionPairs[k].pSonGeo->m_isGeoValid = false;
					m_reactionPairs[k].isPairValid = false;
					break;
				}
			}
		}
		m_pPhysGeos[i]->m_preReactionPairs.Empty();
		m_pPhysGeos[i]->m_seperatePairs.Empty();
		m_pPhysGeos[i]->m_reactionSpawnPairs.Empty();
	}
}*/

void APhysCalculator::DeleteInValidGeos()
{
	int32 i = 0;
	while (i < m_pPolygons.Num())
	{
		if (!m_pPolygons[i]) m_pPolygons.RemoveAt(i);
		else if (!m_pPolygons[i]->m_isGeoValid)
		{
			FEffectParams param;
			m_pRGM->UpdateFullFieldStates(false, m_pPolygons[i], param);
			DeletePhysGeo(m_pPolygons[i]);
		}
		else i++;
	}
	i = 0;
	while (i < m_pPoints.Num())
	{
		if (!m_pPoints[i]) m_pPoints.RemoveAt(i);
		else if (!m_pPoints[i]->m_isGeoValid)
		{
			FEffectParams param;
			m_pRGM->UpdateFullFieldStates(false, m_pPoints[i], param);
			DeletePhysGeo(m_pPoints[i]);
		}
		else i++;
	}
	i = 0;
	while (i < m_pPhysActors.Num())
	{
		if (!m_pPhysActors[i]) m_pPhysActors.RemoveAt(i);
		else if (!m_pPhysActors[i]->m_isGeoValid)
		{
			FEffectParams param;
			m_pRGM->UpdateFullFieldStates(false, m_pPhysActors[i], param);
			DeletePhysGeo(m_pPhysActors[i]);
		}
		else i++;
	}
}

/*
int32 APhysCalculator::FindReactionPair(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2)
{
	if (!pGeo1 || !pGeo2) return -1;
	for (int32 i = 0; i < m_reactionPairs.Num(); i++)
	{
		if (((m_reactionPairs[i].pReactionActor1 == pGeo1 && m_reactionPairs[i].pReactionActor2 == pGeo2) ||
			(m_reactionPairs[i].pReactionActor2 == pGeo1 && m_reactionPairs[i].pReactionActor1 == pGeo2)))
		{
			return i;
		}
	}
	return -1;
}*/

ABasePhysGeo* APhysCalculator::SpawnPhysGeo(TSubclassOf<class UObject> spawnClass, FVector spawnLoc, FRotator spawnRot)
{
	ABasePhysGeo* pSpawnGeo = GetWorld()->SpawnActor<ABasePhysGeo>(spawnClass, spawnLoc, spawnRot);
	return pSpawnGeo;
}

void APhysCalculator::SpawnActorEmitter(ABasePhysGeo* pHost, AActor* pActor, uint8 type)
{
	if (!m_pActorPSMap.Contains(type) || !pHost) return;
	UParticleSystemComponent* pPSComponent = UGameplayStatics::SpawnEmitterAttached(m_pActorPSMap[type], pActor->GetRootComponent(),FName("NULL"), 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	FParticleSysParam psParam;
	psParam.Name = "VertSurfaceActor";
	psParam.ParamType = EParticleSysParamType::PSPT_Actor;
	psParam.Actor = pActor;
	pPSComponent->InstanceParameters.Add(psParam);
	m_spawnMutateActorPSMap.Add(pHost, pPSComponent);
}

/*
void APhysCalculator::CopyReactionInfo(FReactionInfo& originInfo, FReactionInfo& targetInfo)
{
	targetInfo.reactionType = originInfo.reactionType;
	targetInfo.reactionTag = originInfo.reactionTag;
	targetInfo.BPSpawnActorClass = originInfo.BPSpawnActorClass;
	targetInfo.BPTransformActor1Class = originInfo.BPTransformActor1Class;
	targetInfo.BPTransformActor2Class = originInfo.BPTransformActor2Class;
	targetInfo.HostTag = originInfo.HostTag;
	targetInfo.modifyTag1 = originInfo.modifyTag1;
	targetInfo.modifyTag2 = originInfo.modifyTag2;
}*/
/*

void APhysCalculator::AwakeReactionPair(int32 pairNb, ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2)
{
	m_reactionPairs[pairNb].hasReactionOccur = true;
	m_reactionPairs[pairNb].pariReactionInfo.reactionType = EReactionType::PRT_NULL;
	for (int32 i = 0; i<m_reactionPairs.Num(); i++)
	{
		if (m_reactionPairs[i].hasReactionOccur && i != pairNb)
		{
			if (m_reactionPairs[i].pReactionActor1 == pGeo1 || m_reactionPairs[i].pReactionActor2 == pGeo2 ||
				m_reactionPairs[i].pReactionActor1 == pGeo2 || m_reactionPairs[i].pReactionActor2 == pGeo1)
			{
				m_reactionPairs[i].hasReactionOccur = false;
			}
		}
	}
}*/

bool APhysCalculator::SpawnEffectOnCharacter(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter)
{
	if (!pGeo || !pCharacter || !pGeo->m_isGeoValid) return false;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);

	//是否添加Effect取决于character的effect的性质
	//首先判断该effect是否为直接伤害类型技能
	//如是则可叠加effect在character身上
	//如不是则不能叠加在character身上
	bool canExert = true;
	//要判断该角色当前已存在的effect当中是否已经有该geo生成的effect
	bool isContainEffect = false;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_launchType == 1 || pCharacter->m_pEffects[i]->m_launchType == 2) continue;
		if (pCharacter->m_pEffects[i]->m_pOriginGeo == pGeo)
		{
			isContainEffect = true;
			break;
		}
	}
	if (isContainEffect) canExert = false;
	if (!canExert) return false;
	
	bool isHitCharacter = false;
	//TArray<FEffectParams> pGeo->m_effectParamList;
	/*if (pGeo->m_enhanceType == -1) effectParamList = pGeo->m_effectParamList;
	else
	{
		if (pGeo->m_mutationEffectParamList.Contains((uint8)pGeo->m_enhanceType))
			effectParamList = pGeo->m_mutationEffectParamList[(uint8)pGeo->m_enhanceType];
	}*/
	for (int32 i=0; i<pGeo->m_effectParamList.Num(); i++)
	{
		if (!pGeo->m_effectParamList[i].canOverlap)
		{
			//说明该Effect是不能重复施加的，所以要判断角色是否包含这种Effect
			isContainEffect = false;
			for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
			{
				if (pCharacter->m_pEffects[j]->m_effectName == pGeo->m_effectParamList[i].effectName)
				{
					isContainEffect = true;
					break;
				}
			}
			if (isContainEffect) continue;
		}
		if (pGeo->m_effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == pCharacter->m_campFlag) continue;
		else if (pGeo->m_effectParamList[i].effectExertType == 2 && pGeo->m_campFlag != pCharacter->m_campFlag) continue;
		else if (pGeo->m_effectParamList[i].effectExertType == 3 && (pGeo->m_campFlag != pCharacter->m_campFlag || pCharacter->m_characterClassName == pGeo->m_pHost->m_characterClassName)) continue;

		FString effectName = pGeo->m_effectParamList[i].functionNames[0];
		TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		/*if (!canExert && pNewEffect->m_effectType != "ContinuousEffect")
		{
			//说明这个geo已经对这个角色施加过effect，如果这个effect不是ContinuousEffect的话，则忽略
			continue;
		}*/
		pNewEffect->m_effectDefaultParam = pGeo->m_effectParamList[i];
		pNewEffect->m_pOriginGeo = pGeo;
		pNewEffect->m_pHost = pGeo->m_pHost;
		pNewEffect->m_duration = pGeo->m_effectParamList[i].duration;
		pNewEffect->m_effectName = pGeo->m_effectParamList[i].effectName;
		pNewEffect->m_effectValues = pGeo->m_effectParamList[i].effectValues;
		pNewEffect->m_functionNames = pGeo->m_effectParamList[i].functionNames;
		pNewEffect->m_effectOnIntervalList = pGeo->m_effectParamList[i].effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = pGeo->m_effectParamList[i].isIntervalLoop;
		pNewEffect->m_isPhysOrMag = pGeo->m_effectParamList[i].isPhysOrMag;
		pNewEffect->m_isJudgeEffect = pGeo->m_effectParamList[i].isJudgeEffect;
		pNewEffect->m_hitColors = pGeo->m_effectParamList[i].hitColors;
		pNewEffect->m_hitNbs = pGeo->m_effectParamList[i].hitNbs;
		pNewEffect->m_isPermenant = pGeo->m_effectParamList[i].isPermenant;
		pNewEffect->m_canOverlap = pGeo->m_effectParamList[i].canOverlap;
		pNewEffect->m_appendEffectList = pGeo->m_effectParamList[i].appendEffectList;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = pGeo->m_effectParamList[i].chDescription;
			else
				pNewEffect->m_description = pGeo->m_effectParamList[i].enDescription;
		}
		pCharacter->m_pEffects.Add(pNewEffect);
		if (pCharacter->m_characterType == 1)
		{
			if (pNewEffect->m_effectName.Contains("RestrictMove"))
			{
				AKing* pKing = Cast<AKing>(pCharacter);
				int32 restrictGeoNb = 0;
				while (pKing->m_pRestrictMoveEffect.Contains(restrictGeoNb))
				{
					restrictGeoNb += 1;
				}
				pKing->m_pRestrictMoveEffect.Add(restrictGeoNb, pGeo);
			}
		}

		//进行蓄力操作
		if (pCharacter->m_characterType != 1 && pGeo->m_pHost && pGeo->m_pHost->m_characterType == 1)
		{
			/*if (pGeo->m_className == "Polygon_Chop")
			{
				AKing* pPlayerCharacter = Cast<AKing>(pGeo->m_pHost);
				pPlayerCharacter->m_forceAccumulation += pPlayerCharacter->m_forceAccumulateStep;
				if (pPlayerCharacter->m_forceAccumulation >= pPlayerCharacter->m_skillAccumulationLimit)
					pPlayerCharacter->m_forceAccumulation = pPlayerCharacter->m_skillAccumulationLimit;
				float forceAccumulatePercent = (float)pPlayerCharacter->m_forceAccumulation / (float)pPlayerCharacter->m_skillAccumulationLimit;
				if (pBattlePC->m_pBattleMenu)
				{
					UMaterialInstanceDynamic* pDMI = pBattlePC->m_pBattleMenu->m_pForceAccumulateImage->GetDynamicMaterial();
					pDMI->SetScalarParameterValue(FName("Progress"), forceAccumulatePercent);
				}
			}*/
		}
		
		if (pNewEffect->m_effectType != "OneTimeEffect")
		{
			AddStateToCharacter(pCharacter, pGeo->m_effectParamList[i].effectName);
			
			if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
				pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		}
		if (pNewEffect->m_effectType == "AccumulateJudgeEffect")
			ActivateAccumulateJudgeEffect(pCharacter);
		isHitCharacter = true;
	}

	/*if (pGeo->m_enhanceType == -1 || !pGeo->m_mutationEffectParamList.Contains(pGeo->m_enhanceType))
	{
		if (isHitCharacter) return true;
		else return false;
	}
	int32 enhanceType = pGeo->m_enhanceType;

	for (int32 i=0; i<pGeo->m_mutationEffectParamList[enhanceType].effectParamList.Num(); i++)
	{
		if (!pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].canOverlap)
		{
			//说明该Effect是不能重复施加的，所以要判断角色是否包含这种Effect
			isContainEffect = false;
			for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
			{
				if (pCharacter->m_pEffects[j]->m_effectName == pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectName)
				{
					isContainEffect = true;
					break;
				}
			}
			if (isContainEffect) continue;
		}
		if (pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == pCharacter->m_campFlag) return true;
		else if (pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectExertType == 2 && pGeo->m_campFlag != pCharacter->m_campFlag) return true;

		FString effectName = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].functionNames[0];
		TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
		if (!effectClass) return true;
		UEffect* pEnhanceEffect = NewObject<UEffect>(pCharacter, effectClass);
		pEnhanceEffect->m_effectDefaultParam = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i];
		pEnhanceEffect->m_pOriginGeo = pGeo;
		pEnhanceEffect->m_pHost = pGeo->m_pHost;
		pEnhanceEffect->m_duration = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].duration;
		pEnhanceEffect->m_effectName = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectName;
		pEnhanceEffect->m_effectValues = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectValues;
		pEnhanceEffect->m_functionNames = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].functionNames;
		pEnhanceEffect->m_effectOnIntervalList = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectOnIntervalList;
		pEnhanceEffect->m_isIntervalLoop = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].isIntervalLoop;
		pEnhanceEffect->m_isPhysOrMag = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].isPhysOrMag;
		pEnhanceEffect->m_isJudgeEffect = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].isJudgeEffect;
		pEnhanceEffect->m_hitColors = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].hitColors;
		pEnhanceEffect->m_hitNbs = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].hitNbs;
		pEnhanceEffect->m_isPermenant = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].isPermenant;
		pEnhanceEffect->m_canOverlap = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].canOverlap;
		pEnhanceEffect->m_appendEffectList = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].appendEffectList;
		pEnhanceEffect->m_enhanceType = pGeo->m_enhanceType;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pEnhanceEffect->m_description = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].chDescription;
			else
				pEnhanceEffect->m_description = pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].enDescription;
		}
		pCharacter->m_pEffects.Add(pEnhanceEffect);
		if (pEnhanceEffect->m_effectType != "OneTimeEffect")
		{
			UEffectFunLib::AddStateToCharacter(pCharacter, pGeo->m_mutationEffectParamList[enhanceType].effectParamList[i].effectName);
			if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
				pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pEnhanceEffect, true);
		}
		if (pEnhanceEffect->m_effectType == "AccumulateJudgeEffect")
			ActivateAccumulateJudgeEffect(pCharacter);
	}*/

	return true;
}

void APhysCalculator::AddEnhanceEffectToCharacter(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter, int32 enhanceType)
{
	for (int32 i = 0; i < pGeo->m_enhanceEffectParamList[enhanceType].effectParamList.Num(); i++)
	{
		if (pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectName == "NULL" || 
			pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].isCalculateInPreStage) continue;
		//bool hitFlag = m_pPhysCalculator->SpawnEffectOnCharacter(this, m_pOverlapCharacters[i], hurtScale);
		//if (hitFlag) isHit = true;
		//if (!m_isGeoValid) return;

		//是否添加Effect取决于character的effect的性质
		//首先判断该effect是否为直接伤害类型技能
		//如是则可叠加effect在character身上
		//如不是则不能叠加在character身上
		bool canExert = true;
		//要判断该角色当前已存在的effect当中是否已经有该geo生成的effect
		bool isContainEffect = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (pCharacter->m_pEffects[j]->m_launchType == 1 || pCharacter->m_pEffects[j]->m_launchType == 2) continue;
			if (pCharacter->m_pEffects[j]->m_pOriginGeo == pGeo &&
				pCharacter->m_pEffects[j]->m_effectName == pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectName)
			{
				isContainEffect = true;
				break;
			}
		}
		if (isContainEffect) canExert = false;
		if (!canExert) continue;

		bool isHitCharacter = false;
		if (pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == pCharacter->m_campFlag) continue;
		else if (pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectExertType == 2 && pGeo->m_campFlag != pCharacter->m_campFlag) continue;
		else if (pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectExertType == 3 && (pGeo->m_campFlag != pCharacter->m_campFlag || pCharacter->m_characterClassName == pGeo->m_pHost->m_characterClassName)) continue;

		FString effectName = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].functionNames[0];
		TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		/*if (!canExert && pNewEffect->m_effectType != "ContinuousEffect")
		{
			//说明这个geo已经对这个角色施加过effect，如果这个effect不是ContinuousEffect的话，则忽略
			continue;
		}*/
		pNewEffect->m_effectDefaultParam = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i];
		pNewEffect->m_pOriginGeo = pGeo;
		pNewEffect->m_pHost = pGeo->m_pHost;
		pNewEffect->m_duration = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].duration;
		pNewEffect->m_effectName = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectName;
		pNewEffect->m_effectValues = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectValues;
		pNewEffect->m_functionNames = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].functionNames;
		pNewEffect->m_effectOnIntervalList = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].isIntervalLoop;
		pNewEffect->m_isPhysOrMag = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].isPhysOrMag;
		pNewEffect->m_isJudgeEffect = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].isJudgeEffect;
		pNewEffect->m_hitColors = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].hitColors;
		pNewEffect->m_hitNbs = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].hitNbs;
		pNewEffect->m_isPermenant = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].isPermenant;
		pNewEffect->m_canOverlap = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].canOverlap;
		pNewEffect->m_appendEffectList = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].appendEffectList;
		pNewEffect->m_launchType = 2;
		if (m_pRGM->m_pBPC->m_pBattleMenu)
		{
			if (m_pRGM->m_pBPC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].chDescription;
			else
				pNewEffect->m_description = pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].enDescription;
		}
		pCharacter->m_pEffects.Add(pNewEffect);
		if (pCharacter->m_characterType == 1)
		{
			if (pNewEffect->m_effectName.Contains("RestrictMove"))
			{
				AKing* pKing = Cast<AKing>(pCharacter);
				int32 restrictGeoNb = 0;
				while (pKing->m_pRestrictMoveEffect.Contains(restrictGeoNb))
				{
					restrictGeoNb += 1;
				}
				pKing->m_pRestrictMoveEffect.Add(restrictGeoNb, pGeo);
			}
		}

		//进行蓄力操作
		/*if (pCharacter->m_characterType != 1 && pGeo->m_pHost && pGeo->m_pHost->m_characterType == 1)
		{
			/ *if (pGeo->m_className == "Polygon_Chop")
			{
				AKing* pPlayerCharacter = Cast<AKing>(pGeo->m_pHost);
				pPlayerCharacter->m_forceAccumulation += pPlayerCharacter->m_forceAccumulateStep;
				if (pPlayerCharacter->m_forceAccumulation >= pPlayerCharacter->m_skillAccumulationLimit)
					pPlayerCharacter->m_forceAccumulation = pPlayerCharacter->m_skillAccumulationLimit;
				float forceAccumulatePercent = (float)pPlayerCharacter->m_forceAccumulation / (float)pPlayerCharacter->m_skillAccumulationLimit;
				if (pBattlePC->m_pBattleMenu)
				{
					UMaterialInstanceDynamic* pDMI = pBattlePC->m_pBattleMenu->m_pForceAccumulateImage->GetDynamicMaterial();
					pDMI->SetScalarParameterValue(FName("Progress"), forceAccumulatePercent);
				}
			}* /
		}*/

		if (pNewEffect->m_effectType != "OneTimeEffect")
		{
			AddStateToCharacter(pCharacter, pGeo->m_enhanceEffectParamList[enhanceType].effectParamList[i].effectName);

			if (m_pRGM->m_pBPC->m_pCharacterStatusMenu && m_pRGM->m_pBPC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
				m_pRGM->m_pBPC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		}
		if (pNewEffect->m_effectType == "AccumulateJudgeEffect")
			ActivateAccumulateJudgeEffect(pCharacter);
		isHitCharacter = true;
	}
}

void APhysCalculator::SpawnPolyPreCalculateEffect(ABasePhysGeo* pGeo, FString functionName, const FEffectParams& effectParam, ABaseCharacter* pCharacter, TArray<ABaseCharacter*> pSubHosts)
{
	if (!pGeo || !pCharacter || !pGeo->m_isGeoValid) return;
	//是否添加Effect取决于character的effect的性质
	//首先判断该effect是否为直接伤害类型技能
	//如是则可叠加effect在character身上
	//如不是则不能叠加在character身上
	//要判断该角色当前已存在的effect当中是否已经有该geo生成的effect
	bool isContainEffect = false;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_pOriginGeo == pGeo)
		{
			isContainEffect = true;
			break;
		}
	}
	if (isContainEffect) return;

	if (!effectParam.canOverlap)
	{
		//说明该Effect是不能重复施加的，所以要判断角色是否包含这种Effect
		isContainEffect = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (pCharacter->m_pEffects[j]->m_effectName == effectParam.effectName)
			{
				isContainEffect = true;
				break;
			}
		}
		if (isContainEffect) return;
	}
	if (effectParam.effectExertType == 0 && pGeo->m_campFlag == pCharacter->m_campFlag) return;
	else if (effectParam.effectExertType == 2 && pGeo->m_campFlag != pCharacter->m_campFlag) return;
	else if (effectParam.effectExertType == 3 && (pGeo->m_campFlag != pCharacter->m_campFlag || pCharacter->m_characterClassName == pGeo->m_pHost->m_characterClassName)) return;

	//FString effectName = effectParam.functionNames[0];
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(functionName);
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
	pNewEffect->m_effectDefaultParam = effectParam;
	pNewEffect->m_pOriginGeo = pGeo;
	pNewEffect->m_pHost = pGeo->m_pHost;
	pNewEffect->m_duration = effectParam.duration;
	pNewEffect->m_effectName = effectParam.effectName;
	pNewEffect->m_effectValues = effectParam.effectValues;
	pNewEffect->m_functionNames = effectParam.functionNames;
	pNewEffect->m_effectOnIntervalList = effectParam.effectOnIntervalList;
	pNewEffect->m_isIntervalLoop = effectParam.isIntervalLoop;
	pNewEffect->m_isPhysOrMag = effectParam.isPhysOrMag;
	pNewEffect->m_isJudgeEffect = effectParam.isJudgeEffect;
	pNewEffect->m_hitColors = effectParam.hitColors;
	pNewEffect->m_hitNbs = effectParam.hitNbs;
	pNewEffect->m_isPermenant = effectParam.isPermenant;
	pNewEffect->m_canOverlap = effectParam.canOverlap;
	pNewEffect->m_appendEffectList = effectParam.appendEffectList;
	pNewEffect->m_pSubHost = pSubHosts;
	if (pBattlePC->m_pBattleMenu)
	{
		if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
			pNewEffect->m_description = effectParam.chDescription;
		else
			pNewEffect->m_description = effectParam.enDescription;
	}
	pCharacter->m_pEffects.Add(pNewEffect);
	
	if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
		pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
	if (pNewEffect->m_effectType != "OneTimeEffect")
		AddStateToCharacter(pCharacter, effectParam.effectName);
	if (pNewEffect->m_effectType == "AccumulateJudgeEffect")
		ActivateAccumulateJudgeEffect(pCharacter);

	/*if (pGeo->m_enhanceType == -1 || pGeo->m_enhanceEffectParamList.Contains(pGeo->m_enhanceType))
	{
		//pCharacter->m_beAttackedNb += 1;
		return;
	}
	int32 enhanceType = pGeo->m_enhanceType;
	if (!pGeo->m_enhanceEffectParamList[enhanceType].canOverlap)
	{
		//说明该Effect是不能重复施加的，所以要判断角色是否包含这种Effect
		isContainEffect = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (pCharacter->m_pEffects[j]->m_effectName == pGeo->m_enhanceEffectParamList[enhanceType].effectName)
			{
				isContainEffect = true;
				break;
			}
		}
		if (isContainEffect) return;
	}*/
}

void APhysCalculator::SpawnEventEffect(const FEffectParams& effectParam, uint8 exertType, FString eventName)
{
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectParam.functionNames[0]);
	if (!effectClass) return;

	/** 用于描述这个效果的施加范围
	* 0即只施加于不同阵营的人
	* 1为施加于所有阵营的人
	* 2为施加于己方阵营的人
	* 3为施加于所有虫魂角色
	*/
	if (!m_pRGM->m_pPlayerCharacter) return;
	TArray<ABaseCharacter*> pExertCharacters;

	if (exertType == 1)
		pExertCharacters = m_pRGM->m_pAllCharacters;
	else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToPlayer"))
		pExertCharacters.Add(m_pRGM->m_pPlayerCharacter);
	else
	{
		for (int32 i = 0; i < m_pRGM->m_pAllCharacters.Num(); i++)
		{
			if (exertType == 0)
			{
				if (m_pRGM->m_pAllCharacters[i]->m_campFlag != m_pRGM->m_pPlayerCharacter->m_campFlag)
				{
					if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToBeast"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 2)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToHuman"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 0)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToDevil"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 1)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToGoblin"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 4)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToDragon"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 3)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToGhost"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 6)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else
						pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
				}
			}
			else if (exertType == 2)
			{
				if (m_pRGM->m_pAllCharacters[i]->m_campFlag == m_pRGM->m_pPlayerCharacter->m_campFlag)
				{
					if (effectParam.functionNames.Num() > 1 && effectParam.functionNames[1].Contains("ToWorm"))
					{
						if (m_pRGM->m_pAllCharacters[i]->m_characterRace == 5)
							pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
					}
					else
						pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
				}
			}
		}
	}
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pExertCharacters.Num(); i++)
	{
		UEffect* pNewEffect = NewObject<UEffect>(pExertCharacters[i], effectClass);
		pNewEffect->m_effectDefaultParam = effectParam;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = m_pRGM->m_pPlayerCharacter;
		pNewEffect->m_duration = effectParam.duration;
		pNewEffect->m_effectName = effectParam.effectName;
		pNewEffect->m_effectValues = effectParam.effectValues;
		pNewEffect->m_functionNames = effectParam.functionNames;
		pNewEffect->m_effectOnIntervalList = effectParam.effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = effectParam.isIntervalLoop;
		pNewEffect->m_isPhysOrMag = effectParam.isPhysOrMag;
		pNewEffect->m_isJudgeEffect = effectParam.isJudgeEffect;
		pNewEffect->m_hitColors = effectParam.hitColors;
		pNewEffect->m_hitNbs = effectParam.hitNbs;
		pNewEffect->m_isPermenant = effectParam.isPermenant;
		pNewEffect->m_canOverlap = effectParam.canOverlap;
		pNewEffect->m_appendEffectList = effectParam.appendEffectList;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = effectParam.chDescription;
			else
				pNewEffect->m_description = effectParam.enDescription;
		}
		//pNewEffect->m_pSubHost = pSubHosts;
		pExertCharacters[i]->m_pEffects.Add(pNewEffect);
		if (pNewEffect->m_effectType != "OneTimeEffect")
		{
			AddStateToCharacter(pExertCharacters[i], effectParam.effectName);
			
			if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pExertCharacters[i])
				pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		}
		if (pNewEffect->m_effectType == "AccumulateJudgeEffect")
			ActivateAccumulateJudgeEffect(pExertCharacters[i]);
		if (!m_pRGM->m_cardCombinePSMap.Contains(eventName)) continue;
	}
}

void APhysCalculator::SpawnOverallEffect(const FEffectParams& effectParam, ABasePhysGeo* pGeo)
{
	FString chopEffectName;
	if (effectParam.functionNames[0].Contains("FullField_"))
		chopEffectName = effectParam.functionNames[0].RightChop(19);
	else
		chopEffectName = effectParam.functionNames[0].RightChop(23);
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(chopEffectName);
	if (!effectClass) return;

	if (!m_pRGM->m_pPlayerCharacter) return;
	TArray<ABaseCharacter*> pExertCharacters;

	if (effectParam.functionNames[0].Contains("ToPlayer"))
		pExertCharacters.Add(m_pRGM->m_pPlayerCharacter);
	else if (effectParam.functionNames[0].Contains("ToEnermy"))
	{
		for (int32 i = 0; i < m_pRGM->m_pAllCharacters.Num(); i++)
		{
			if (m_pRGM->m_pAllCharacters[i]->m_characterType == 0)
				pExertCharacters.Add(m_pRGM->m_pAllCharacters[i]);
		}
	}
	else if (effectParam.functionNames[0].Contains("ToPartEnermy"))
	{
		int32 exertCharacterNb = effectParam.effectValues[0];
		if (exertCharacterNb > m_pRGM->m_pAICharacters.Num())
			exertCharacterNb = m_pRGM->m_pAICharacters.Num();
		TArray<int32> chosenCharacterNbs;
		TArray<int32> availableCharacterNbList;
		for (int32 i=0; i<m_pRGM->m_pAICharacters.Num(); i++)
		{
			availableCharacterNbList.Add(i);
		}
		for (int32 i=0; i<exertCharacterNb; i++)
		{
			int32 randNb = FMath::RandRange(0, availableCharacterNbList.Num() - 1);
			chosenCharacterNbs.Add(availableCharacterNbList[randNb]);
			availableCharacterNbList.RemoveAt(randNb);
		}
		for (int32 i=0; i<chosenCharacterNbs.Num(); i++)
		{
			pExertCharacters.Add(m_pRGM->m_pAICharacters[chosenCharacterNbs[i]]);
		}
	}
	else if (effectParam.functionNames[0].Contains("ToPartEnermyExceptOwn"))
	{
		int32 exertCharacterNb = effectParam.effectValues[0];
		if (exertCharacterNb > m_pRGM->m_pAICharacters.Num())
			exertCharacterNb = m_pRGM->m_pAICharacters.Num();
		TArray<int32> chosenCharacterNbs;
		TArray<int32> availableCharacterNbList;
		for (int32 i = 0; i < m_pRGM->m_pAICharacters.Num(); i++)
		{
			if (m_pRGM->m_pAICharacters[i] == pGeo->m_pHost) continue;
			availableCharacterNbList.Add(i);
		}
		for (int32 i = 0; i < exertCharacterNb; i++)
		{
			int32 randNb = FMath::RandRange(0, availableCharacterNbList.Num() - 1);
			chosenCharacterNbs.Add(availableCharacterNbList[randNb]);
			availableCharacterNbList.RemoveAt(randNb);
		}
		for (int32 i = 0; i < chosenCharacterNbs.Num(); i++)
		{
			pExertCharacters.Add(m_pRGM->m_pAICharacters[chosenCharacterNbs[i]]);
		}
	}
	m_pRGM->m_fullFieldStates.Add(pGeo->m_entityID, effectParam.effectValues.Last());

	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i = 0; i < pExertCharacters.Num(); i++)
	{
		UEffect* pNewEffect = NewObject<UEffect>(pExertCharacters[i], effectClass);
		pNewEffect->m_effectDefaultParam = effectParam;
		pNewEffect->m_pOriginGeo = pGeo;
		pNewEffect->m_pHost = pGeo->m_pHost;
		pNewEffect->m_duration = effectParam.duration;
		pNewEffect->m_effectName = effectParam.effectName;
		pNewEffect->m_effectValues = effectParam.effectValues;
		pNewEffect->m_functionNames = effectParam.functionNames;
		pNewEffect->m_effectOnIntervalList = effectParam.effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = effectParam.isIntervalLoop;
		pNewEffect->m_isPhysOrMag = effectParam.isPhysOrMag;
		pNewEffect->m_isJudgeEffect = effectParam.isJudgeEffect;
		pNewEffect->m_hitColors = effectParam.hitColors;
		pNewEffect->m_hitNbs = effectParam.hitNbs;
		pNewEffect->m_isPermenant = effectParam.isPermenant;
		pNewEffect->m_canOverlap = effectParam.canOverlap;
		pNewEffect->m_appendEffectList = effectParam.appendEffectList;
		pNewEffect->m_launchType = 1;

		pExertCharacters[i]->m_pEffects.Add(pNewEffect);
		if (pNewEffect->m_effectType != "OneTimeEffect")
		{
			AddStateToCharacter(pExertCharacters[i], effectParam.effectName);

			if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pExertCharacters[i])
				pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		}
		if (pNewEffect->m_effectType == "AccumulateJudgeEffect")
			ActivateAccumulateJudgeEffect(pExertCharacters[i]);

		//展示特效
		if (effectParam.functionNames[0].Contains("FullFieldLink_"))
		{
			FVector spawnLoc = (pExertCharacters[i]->GetActorLocation() + pGeo->m_pHost->GetActorLocation()) / 2.f;
			UParticleSystemComponent* pParticleComponent = NULL;
			pParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(pGeo->m_pHost, pGeo->m_pHitParticleSystem, spawnLoc);
			if (pGeo->m_isHitParticleBindtoEffect)
			{
				FBindPSInformation BindPSInformation(pExertCharacters[i], pGeo->m_pHost, pNewEffect);
				m_bindPSMap.Add(pParticleComponent, BindPSInformation);
			}
			FParticleSysParam soureParam;
			soureParam.Name = "BeamSource";
			soureParam.ParamType = EParticleSysParamType::PSPT_Actor;
			soureParam.Scalar = 0.f;
			soureParam.Scalar_Low = 0.f;
			soureParam.Vector = FVector::ZeroVector;
			soureParam.Vector_Low = FVector::ZeroVector;
			soureParam.Actor = pExertCharacters[i];
			FParticleSysParam targetParam;
			targetParam.Name = "BeamTarget";
			targetParam.ParamType = EParticleSysParamType::PSPT_Actor;
			targetParam.Scalar = 0.f;
			targetParam.Scalar_Low = 0.f;
			targetParam.Vector = FVector::ZeroVector;
			targetParam.Vector_Low = FVector::ZeroVector;
			targetParam.Actor = pGeo->m_pHost;
			pParticleComponent->InstanceParameters.Add(soureParam);
			pParticleComponent->InstanceParameters.Add(targetParam);
		}
	}
}

void APhysCalculator::EffectOnCharacter(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	/*if (!pEffect || !pCharacter) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode) return;*/
	//AppendSuperpositionEffects(pEffect);
	ActivateEmbeddedEffects(pEffect, pCharacter);
	if (pEffect->m_isOnByEmbeddedEffect)
	{
		if (pEffect->m_functionNames.Contains("Hurt"))
			UEffectFunLib::Hurt(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtAmplifiedByJudge"))
			UEffectFunLib::HurtAmplifiedByJudge(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtAmplifiedByAppendString"))
			UEffectFunLib::HurtAmplifiedByAppendString(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("CopyJudgeActivateTargetEffect"))
			UEffectFunLib::CopyJudgeActivateTargetEffect(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("PureJudge"))
			UEffectFunLib::PureJudge(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("Vampire"))
			UEffectFunLib::Vampire(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("VampireRevert"))
			UEffectFunLib::VampireRevert(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ClearResistByJudge"))
			UEffectFunLib::ClearResistByJudge(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("IncreaseCDByCharacterAppendString"))
			UEffectFunLib::IncreaseCDByCharacterAppendString(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("IncreaseCDByCharacterHp"))
			UEffectFunLib::IncreaseCDByCharacterHp(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtShareByCharacterAppendString"))
			UEffectFunLib::HurtShareByCharacterAppendString(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByCompanionHpLess"))
			UEffectFunLib::HurtByCompanionHpLess(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtByCardNumber"))
			UEffectFunLib::HurtByCardNumber(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtByLeftCardNumber"))
			UEffectFunLib::HurtByLeftCardNumber(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DefenceIncrease"))
			UEffectFunLib::DefenceIncrease(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttackDrop"))
			UEffectFunLib::AttackDrop(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByDifCampFlag"))
			UEffectFunLib::HurtByDifCampFlag(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("Universe"))
			UEffectFunLib::Universe(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("Eclosion"))
			UEffectFunLib::Eclosion(pEffect, pCharacter);
		/*else if (pEffect->m_functionNames.Contains("LimitAllImplementedCD"))
			UEffectFunLib::LimitAllImplementedCD(pEffect, pCharacter);*/
		else if (pEffect->m_functionNames.Contains("DefenceDecreaseByAttribute"))
			UEffectFunLib::DefenceDecreaseByAttribute(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttackDecreaseByAttribute"))
			UEffectFunLib::AttackDecreaseByAttribute(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttributeWeak"))
			UEffectFunLib::AttributeWeak(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttributeWeakByHostHp"))
			UEffectFunLib::AttributeWeakByHostHp(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ExtraHurtByAppendString"))
			UEffectFunLib::ExtraHurtByAppendString(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DefenceDecreaseByHpPercent"))
			UEffectFunLib::DefenceDecreaseByHpPercent(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DefSubByCharacterNb"))
			UEffectFunLib::DefSubByCharacterNb(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RestrictJudgeNumber"))
			UEffectFunLib::RestrictJudgeNumber(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByCoverCharacterGrade"))
			UEffectFunLib::HurtByCoverCharacterGrade(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("DefenceDecreaseByCD"))
			UEffectFunLib::DefenceDecreaseByCD(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("IncreaseCDByCoverCharacterAppendString"))
			UEffectFunLib::IncreaseCDByCoverCharacterAppendString(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AtkSubByNoneAtkCardNb"))
			UEffectFunLib::AtkSubByNoneAtkCardNb(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByCompareDfc"))
			UEffectFunLib::HurtByCompareDfc(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtByCompareAttack"))
			UEffectFunLib::HurtByCompareAttack(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("FireWoodSwitch"))
			UEffectFunLib::FireWoodSwitch(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtBySpecificGradeNumber"))
			UEffectFunLib::HurtBySpecificGradeNumber(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("AtkSubByDef"))
			UEffectFunLib::AtkSubByDef(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByCoverCharacterAverageAtk"))
			UEffectFunLib::HurtByCoverCharacterAverageAtk(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("HurtAmplifiedByDifSameFlag"))
			UEffectFunLib::HurtAmplifiedByDifSameFlag(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("AttributeWeakByTargetHp"))
			UEffectFunLib::AttributeWeakByTargetHp(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RecoverIfTargetAtkCardMoreThanNoneAtkCard"))
			UEffectFunLib::RecoverIfTargetAtkCardMoreThanNoneAtkCard(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ExtraHurtByCardNumber"))
			UEffectFunLib::ExtraHurtByCardNumber(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RecoverOrContinuousHurtByJudge"))
			UEffectFunLib::RecoverOrContinuousHurtByJudge(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ContinuousHurt"))
			UEffectFunLib::ContinuousHurt(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtAmplifiedIfFoundationType"))
			UEffectFunLib::HurtAmplifiedIfFoundationType(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("ExtractCompanyLifeToAttack"))
			UEffectFunLib::ExtractCompanyLifeToAttack(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ResourcesSub"))
			UEffectFunLib::ResourcesSub(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("SwitchHpPercentByOrder"))
			UEffectFunLib::SwitchHpPercentByOrder(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RecoverByAppendString"))
			UEffectFunLib::RecoverByAppendString(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DefSubByAtkCardNb"))
			UEffectFunLib::DefSubByAtkCardNb(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ClearAllAppendEffects"))
			UEffectFunLib::ClearAllAppendEffects(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ExtraHurtByCompareCardAndDifTagNb"))
			UEffectFunLib::ExtraHurtByCompareCardAndDifTagNb(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("FreezeByJudgeActivate"))
			UEffectFunLib::FreezeByJudgeActivate(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByLeftHp"))
			UEffectFunLib::HurtByLeftHp(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("ExtraHurtIfEvenCharacters"))
			UEffectFunLib::ExtraHurtIfEvenCharacters(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ShareHurt"))
			UEffectFunLib::ShareHurt(pEffect, pCharacter, 0);
		else if (pEffect->m_functionNames.Contains("AbsorbSameTagHurtToPlayer"))
			UEffectFunLib::AbsorbSameTagHurtToPlayer(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ExtraHurtByCompareAtk"))
			UEffectFunLib::ExtraHurtByCompareAtk(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("CopyPlayerAppendEffect"))
			UEffectFunLib::CopyPlayerAppendEffect(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ClearAllAppendEffectsByJudge"))
			UEffectFunLib::ClearAllAppendEffectsByJudge(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("FourColorWish"))
			UEffectFunLib::FourColorWish(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("Slow"))
			UEffectFunLib::Slow(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("ContinuousSlow"))
		UEffectFunLib::ContinuousSlow(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttackIncrease"))
			UEffectFunLib::AttackIncrease(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtQuattuorByJudge"))
			UEffectFunLib::HurtQuattuorByJudge(pEffect, pCharacter, m_damageCoeK1, m_damageCoeK2);
		else if (pEffect->m_functionNames.Contains("Assimilation"))
			UEffectFunLib::Assimilation(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("SubCD"))
			UEffectFunLib::SubCD(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DefSub"))
			UEffectFunLib::DefSub(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AttackDecrease"))
			UEffectFunLib::AttackDecrease(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AbsortState"))
			UEffectFunLib::AbsortState(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("CopyDefence"))
			UEffectFunLib::CopyDefence(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("BroadcastStates"))
			UEffectFunLib::BroadcastStates(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("IncreaseATKAndDecreaseDFC"))
			UEffectFunLib::IncreaseATKAndDecreaseDFC(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DiseaseInfection"))
			UEffectFunLib::DiseaseInfection(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("Poison"))
			UEffectFunLib::Poison(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("IncreasePoison"))
			UEffectFunLib::IncreasePoison(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByJudgeList"))
			UEffectFunLib::HurtByJudgeList(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByLostHpAndJudgeList"))
			UEffectFunLib::HurtByLostHpAndJudgeList(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RecoverByJudgeList"))
			UEffectFunLib::RecoverByJudgeList(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByDefence"))
			UEffectFunLib::HurtByDefence(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtPiercing"))
			UEffectFunLib::HurtPiercing(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByDeleteJudgeList"))
			UEffectFunLib::HurtByDeleteJudgeList(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AddSpecificJudgeCard"))
			UEffectFunLib::AddSpecificJudgeCard(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtAndRecoverByEquipmentName"))
			UEffectFunLib::HurtAndRecoverByEquipmentName(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("JudgeToRecover"))
			UEffectFunLib::JudgeToRecover(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("JudgeToIncreaseDefence"))
			UEffectFunLib::JudgeToIncreaseDefence(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("DoubleAttack"))
			UEffectFunLib::DoubleAttack(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("RecoverByItemCard"))
			UEffectFunLib::RecoverByItemCard(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtTransfer"))
			UEffectFunLib::HurtTransfer(pEffect, pCharacter, 0);
		else if (pEffect->m_functionNames.Contains("HurtByCoverActorTag"))
			UEffectFunLib::HurtByCoverActorTag(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtNoHost"))
			UEffectFunLib::HurtNoHost(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("HurtByAttackCardNb"))
			UEffectFunLib::HurtByAttackCardNb(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("AmplifyOrExemptHurtByJudge"))
			UEffectFunLib::AmplifyOrExemptHurtByJudge(pEffect, pCharacter);
		else if (pEffect->m_functionNames.Contains("Recover"))
			UEffectFunLib::Recover(pEffect, pCharacter);
		else if (pEffect->m_functionNames[0].Contains("ContinuousHurtIfUnderDark"))
			UEffectFunLib::ContinuousHurtIfUnderDark(pEffect, pCharacter);
		else if (pEffect->m_functionNames[0].Contains("HostDieTogether"))
			UEffectFunLib::HostDieTogether(pEffect, pCharacter);
	}
	pEffect->RecoverDefaultValues();
	ActivatePassiveEffects(pEffect, pCharacter);
}

void APhysCalculator::EffectEndCharacter(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	/*AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode) return;*/
	/*if (pEffect->m_functionNames[0] == "DefAdd")
		UEffectFunLib::DefAdd_End(pEffect, pCharacter);*/
	ActivateEffectDeleteEffect(pEffect, pCharacter);

	if (pEffect->m_functionNames[0] == "AttackIncrease")
		UEffectFunLib::AtkAdd_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "AttackDrop")
		UEffectFunLib::AttackDrop_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "RestrictJudgeColor")
		UEffectFunLib::RestrictJudgeColor_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "RestrictJudgeNumber")
		UEffectFunLib::RestrictJudgeNumber_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "AtkSubByNoneAtkCardNb")
		UEffectFunLib::AtkSubByNoneAtkCardNb_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "AtkSubByDef")
		UEffectFunLib::AtkSubByDef_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "SwitchHpPercentByOrder")
		UEffectFunLib::SwitchHpPercentByOrder_End(pEffect, pCharacter);
	/*else if (pEffect->m_functionNames[0] == "DefSubByAtkCardNb")
		UEffectFunLib::DefSubByAtkCardNb_End(pEffect, pCharacter);*/
	else if (pEffect->m_functionNames[0] == "FreezeByJudgeActivate")
		UEffectFunLib::FreezeByJudgeActivate_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "Assimilation")
		UEffectFunLib::Assimilation_End(pEffect, pCharacter);
	/*else if (pEffect->m_functionNames[0] == "DefSub")
		UEffectFunLib::DefSub_End(pEffect, pCharacter);*/
	else if (pEffect->m_functionNames[0] == "AttackDecrease")
		UEffectFunLib::AttackDecrease_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "AttackDecreaseByAttribute")
		UEffectFunLib::AttackDecreaseByAttribute_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "DoubleAttack")
		UEffectFunLib::DoubleAttack_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "ExtractCompanyLifeToAttack")
		UEffectFunLib::ExtractCompanyLifeToAttack_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "IncreaseATKAndDecreaseDFC")
		UEffectFunLib::IncreaseATKAndDecreaseDFC_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "Eclosion")
		UEffectFunLib::Eclosion_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "ContinuousSlow")
		UEffectFunLib::ContinuousSlow_End(pEffect, pCharacter);
	else if (pEffect->m_functionNames[0] == "Slow")
		UEffectFunLib::Slow_End(pEffect, pCharacter);
	/*else if (pEffect->m_functionNames[0] == "CopyDefence")
		UEffectFunLib::CopyDefence_End(pEffect, pCharacter);*/
	/*else if (pEffect->m_functionNames[0] == "DefenceDecreaseByCD")
		UEffectFunLib::DefenceDecreaseByCD_End(pEffect, pCharacter);*/
}

void APhysCalculator::AddPermenantEffectOnCharacter(FString effectName, ABaseCharacter* pCharacter)
{
	bool isContainEffect = false;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectName == effectName)
		{
			isContainEffect = true;
			break;
		}
	}
	if (isContainEffect) return;
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i<m_permenantEffectParams.Num(); i++)
	{
		if (m_permenantEffectParams[i].effectName == pNewEffect->m_effectName)
		{
			pNewEffect->m_effectDefaultParam = m_permenantEffectParams[i];
			pNewEffect->m_duration = m_permenantEffectParams[i].duration;
			pNewEffect->m_preconditionEffects = m_permenantEffectParams[i].preconditionEffects;
			pNewEffect->m_functionNames = m_permenantEffectParams[i].functionNames;
			pNewEffect->m_effectValues = m_permenantEffectParams[i].effectValues;
			pNewEffect->m_effectOnIntervalList = m_permenantEffectParams[i].effectOnIntervalList;
			pNewEffect->m_appendEffectList = m_permenantEffectParams[i].appendEffectList;
			pNewEffect->m_isIntervalLoop = m_permenantEffectParams[i].isIntervalLoop;
			pNewEffect->m_isPhysOrMag = m_permenantEffectParams[i].isPhysOrMag;
			pNewEffect->m_isJudgeEffect = m_permenantEffectParams[i].isJudgeEffect;
			pNewEffect->m_hitColors = m_permenantEffectParams[i].hitColors;
			pNewEffect->m_hitNbs = m_permenantEffectParams[i].hitNbs;
			pNewEffect->m_isPermenant = m_permenantEffectParams[i].isPermenant;
			pNewEffect->m_canOverlap = m_permenantEffectParams[i].canOverlap;
			if (pCWGI->m_language == "Chinese")
				pNewEffect->m_description = m_permenantEffectParams[i].chDescription;
			else
				pNewEffect->m_description = m_permenantEffectParams[i].enDescription;
			break;
		}
	}
	pNewEffect->m_pOriginGeo = NULL;
	pNewEffect->m_pHost = pCharacter;
	pNewEffect->m_isPermenant = true;
	pCharacter->m_pEffects.Add(pNewEffect);
	
	if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
		pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
	AddStateToCharacter(pCharacter, effectName);
}

void APhysCalculator::NotifySpawnEffectParticle_Implementation(const FString& geoName, ABaseCharacter* pCharacter)
{

}

void APhysCalculator::DestroyEffect(UEffect* pEffect)
{
	if (!pEffect) return;
	if (!pEffect->IsValidLowLevel()) return;
	pEffect->ConditionalBeginDestroy();
}

void APhysCalculator::CountEffectScore(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	/*if (!pBattleLevelGameMode->m_pLuaActor) return;
	pBattleLevelGameMode->m_pLuaActor->LuaCountEffectScore(pEffect, pCharacter);*/
}

void APhysCalculator::CalGeoReactions()
{
	/*int32 i = 0;
	while (i < m_reactionPairs.Num())
	{
		//这里要包含几个情况
		if (!m_reactionPairs[i].isInitial)
		{
			if (!m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1) || !m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
			{
				//这种情况不用管，因为说明参与反应的几何体还没初始化
				i += 1;
				continue;
			}
			else
			{
				//说明已经完成初始化，可以进行计算了
				m_reactionPairs[i].isInitial = true;
			}
		}
		if (!m_occupyGeoIDs[m_reactionPairs[i].geoID1] || !m_reactionPairs[i].pGeo2 ||
			!m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_isGeoValid || !m_reactionPairs[i].pGeo2->m_isGeoValid)
		{
			m_reactionPairs.RemoveAt(i);
			continue;
		}
		if (m_reactionPairs[i].reactionType == 0 || m_reactionPairs[i].reactionType == 2)
		{
			if (m_reactionPairs[i].reactionName1.Contains("Spawn_") || m_reactionPairs[i].reactionName1.Contains("Reflect_") ||
				m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
			{
				FString spawnName;
				FVector spawnLoc = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation();
				FRotator spawnRot = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorRotation();
				if (m_reactionPairs[i].reactionName1.Contains("Reflect_") || m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
				{
					if (m_reactionPairs[i].reactionName1.Contains("Reflect_"))
					{
						spawnName = m_reactionPairs[i].reactionName1.RightChop(8);
						FVector geo2ForwardVector = m_reactionPairs[i].pGeo2->GetActorForwardVector();
						FVector offset = m_reactionPairs[i].pGeo2->GetActorLocation() - m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation();
						offset.Normalize();
						FVector2D reflectVec(geo2ForwardVector.X, geo2ForwardVector.Y);
						bool successFlag = UCollisionWarBpFunctionLibrary::GetReflectVectorWithDirAndNormalVector(FVector2D(geo2ForwardVector.X, geo2ForwardVector.Y),
							FVector2D(offset.X, offset.Y), reflectVec);
						FVector reflectVec3D(reflectVec.X, reflectVec.Y, 0.f);
						spawnRot = reflectVec3D.Rotation();
					}
					else
					{
						spawnName = m_reactionPairs[i].reactionName1.RightChop(11);
						spawnRot = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorRotation();
					}
					spawnLoc = m_reactionPairs[i].pGeo2->GetActorLocation();
				}
				else
					spawnName = m_reactionPairs[i].reactionName1.RightChop(6);
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_spawnMutateGeo[spawnName], spawnLoc, spawnRot);
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1))
					pPhysGeo->m_pRootGeos.Add(m_occupyGeoIDs[m_reactionPairs[i].geoID1]);
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
					pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo2);
				AddPhysGeo(pPhysGeo, m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pHost, 0);
				if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pSpawnMutatePSActor.Contains(spawnName))
				{
					AActor* pMutateActor = GetWorld()->SpawnActor<AActor>(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pSpawnMutatePSActor[spawnName],
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation(), m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorRotation());
					m_spawnMutateActorMap.Add(pPhysGeo, pMutateActor);
					SpawnActorEmitter(pPhysGeo, pMutateActor, m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_spawnMutateActorPSType[spawnName]);
				}
				if (m_reactionPairs[i].reactionName1.Contains("Reflect_") || m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
					m_reactionPairs[i].pGeo2->m_isGeoValid = false;
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Disapear_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1))
				{
					m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_isGeoValid = false;
					if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS.Contains(0) && m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS[0])
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS[0],
							m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation(), m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorRotation());
				}
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Transform_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1))
				{
					m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_isGeoValid = false;
					if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS.Contains(0) && m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS[0])
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pTransformPS[0],
							m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation(), m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorRotation());
					FString spawnName = m_reactionPairs[i].reactionName1.RightChop(10);
					ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_spawnMutateGeo[spawnName], m_reactionPairs[i].reactionLoc1, m_reactionPairs[i].reactionRot1);
					pPhysGeo->m_pRootGeos = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pRootGeos;
					AddPhysGeo(pPhysGeo, m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_pHost, 0);
				}
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Mutate_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1))
				{
					FString mutateName = m_reactionPairs[i].reactionName1.RightChop(7);
					if (mutateName == "Fire")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 0;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(0);
					}
					else if (mutateName == "Water")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 1;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(1);
					}
					else if (mutateName == "Freeze")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 2;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(2);
					}
					else if (mutateName == "Wood")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 3;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(3);
					}
					else if (mutateName == "Ground")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 4;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(4);
					}
					else if (mutateName == "Dark")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 5;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(5);
					}
					else if (mutateName == "Light")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 6;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(6);
					}
					else if (mutateName == "Wind")
					{
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType = 7;
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_attributeList.Add(7);
					}
					m_occupyGeoIDs[m_reactionPairs[i].geoID1]->AppendEnhanceParticle(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType);

					if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceEffectParamList.Contains(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType))
					{
						if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_physGeoType == EPhysGeoType::PGT_Poly)
						{
							APhysPolygon* pPolygon = Cast<APhysPolygon>(m_occupyGeoIDs[m_reactionPairs[i].geoID1]);
							PolygonEffectPreCalculate(pPolygon, m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceEffectParamList[m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType].effectParamList);
						}
						m_occupyGeoIDs[m_reactionPairs[i].geoID1]->AddEnhanceEffectToOverlapCharacters(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType);
						//跟其他集合类型不一样，点类技能接触被击中者可能只是一瞬间，所以如果当它移动走了到击中下一个角色时，由于它没有执行
						//这个反应计算函数，便无法施加enhance效果，所以点类几何要将enhance效果的paramlist添加到普通effectparamlist中
						if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_physGeoType == EPhysGeoType::PGT_Point)
						{
							if (m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceEffectParamList.Contains(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType))
							{
								for (int32 j = 0; j < m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceEffectParamList[m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType].effectParamList.Num(); j++)
								{
									m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_effectParamList.Add(m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceEffectParamList[m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_enhanceType].effectParamList[j]);
								}
							}
						}
					}
				}
			}
		}
		if (m_reactionPairs[i].reactionType == 1 || m_reactionPairs[i].reactionType == 2)
		{
			if (m_reactionPairs[i].reactionName2.Contains("Spawn_") || m_reactionPairs[i].reactionName2.Contains("Reflect_") ||
				m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
			{
				FString spawnName;
				FVector spawnLoc = m_reactionPairs[i].pGeo2->GetActorLocation();
				FRotator spawnRot = m_reactionPairs[i].pGeo2->GetActorRotation();
				if (m_reactionPairs[i].reactionName2.Contains("Reflect_") || m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
				{
					if (m_reactionPairs[i].reactionName2.Contains("Reflect_"))
					{
						spawnName = m_reactionPairs[i].reactionName2.RightChop(8);
						FVector geo1ForwardVector = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorForwardVector();
						FVector offset = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation() - m_reactionPairs[i].pGeo2->GetActorLocation();
						offset.Normalize();
						FVector2D reflectVec(geo1ForwardVector.X, geo1ForwardVector.Y);
						bool successFlag = UCollisionWarBpFunctionLibrary::GetReflectVectorWithDirAndNormalVector(FVector2D(geo1ForwardVector.X, geo1ForwardVector.Y),
							FVector2D(offset.X, offset.Y), reflectVec);
						FVector reflectVec3D(reflectVec.X, reflectVec.Y, 0.f);
						spawnRot = reflectVec3D.Rotation();
					}
					else
					{
						spawnName = m_reactionPairs[i].reactionName2.RightChop(11);
						spawnRot = m_reactionPairs[i].pGeo2->GetActorRotation();
					}
					spawnLoc = m_occupyGeoIDs[m_reactionPairs[i].geoID1]->GetActorLocation();
				}
				else
					spawnName = m_reactionPairs[i].reactionName2.RightChop(6);
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo2->m_spawnMutateGeo[spawnName], spawnLoc, spawnRot);
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
					pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo2);
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID1))
					pPhysGeo->m_pRootGeos.Add(m_occupyGeoIDs[m_reactionPairs[i].geoID1]);
				AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo2->m_pHost, 0);
				if (m_reactionPairs[i].pGeo2->m_pSpawnMutatePSActor.Contains(spawnName))
				{
					AActor* pMutateActor = GetWorld()->SpawnActor<AActor>(m_reactionPairs[i].pGeo2->m_pSpawnMutatePSActor[spawnName],
						m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
					m_spawnMutateActorMap.Add(pPhysGeo, pMutateActor);
					SpawnActorEmitter(pPhysGeo, pMutateActor, m_reactionPairs[i].pGeo2->m_spawnMutateActorPSType[spawnName]);
				}
				if (m_reactionPairs[i].reactionName2.Contains("Reflect_") || m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
					m_occupyGeoIDs[m_reactionPairs[i].geoID1]->m_isGeoValid = false;
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Disapear_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
				{
					m_reactionPairs[i].pGeo2->m_isGeoValid = false;
					if (m_reactionPairs[i].pGeo2->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo2->m_pTransformPS[0])
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo2->m_pTransformPS[0],
							m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
				}
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Transform_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
				{
					m_reactionPairs[i].pGeo2->m_isGeoValid = false;
					if (m_reactionPairs[i].pGeo2->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo2->m_pTransformPS[0])
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo2->m_pTransformPS[0],
							m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
					FString spawnName = m_reactionPairs[i].reactionName2.RightChop(10);
					ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo2->m_spawnMutateGeo[spawnName], m_reactionPairs[i].reactionLoc2, m_reactionPairs[i].reactionRot2);
					pPhysGeo->m_pRootGeos = m_reactionPairs[i].pGeo2->m_pRootGeos;
					AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo2->m_pHost, 0);
				}
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Mutate_"))
			{
				if (m_occupyGeoIDs.Contains(m_reactionPairs[i].geoID2))
				{
					FString mutateName = m_reactionPairs[i].reactionName2.RightChop(7);
					if (mutateName == "Fire")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 0;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(0);
					}
					else if (mutateName == "Water")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 1;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(1);
					}
					else if (mutateName == "Freeze")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 2;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(2);
					}
					else if (mutateName == "Wood")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 3;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(3);
					}
					else if (mutateName == "Ground")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 4;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(4);
					}
					else if (mutateName == "Dark")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 5;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(5);
					}
					else if (mutateName == "Light")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 6;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(6);
					}
					else if (mutateName == "Wind")
					{
						m_reactionPairs[i].pGeo2->m_enhanceType = 7;
						m_reactionPairs[i].pGeo2->m_attributeList.Add(7);
					}
					m_reactionPairs[i].pGeo2->AppendEnhanceParticle(m_reactionPairs[i].pGeo2->m_enhanceType);

					if (m_reactionPairs[i].pGeo2->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo2->m_enhanceType))
					{
						if (m_reactionPairs[i].pGeo2->m_physGeoType == EPhysGeoType::PGT_Poly)
						{
							APhysPolygon* pPolygon = Cast<APhysPolygon>(m_reactionPairs[i].pGeo2);
							PolygonEffectPreCalculate(pPolygon, m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList);
						}
						m_reactionPairs[i].pGeo2->AddEnhanceEffectToOverlapCharacters(m_reactionPairs[i].pGeo2->m_enhanceType);
						//跟其他集合类型不一样，点类技能接触被击中者可能只是一瞬间，所以如果当它移动走了到击中下一个角色时，由于它没有执行
						//这个反应计算函数，便无法施加enhance效果，所以点类几何要将enhance效果的paramlist添加到普通effectparamlist中
						if (m_reactionPairs[i].pGeo2->m_physGeoType == EPhysGeoType::PGT_Point)
						{
							if (m_reactionPairs[i].pGeo2->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo2->m_enhanceType))
							{
								for (int32 j = 0; j < m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList.Num(); j++)
								{
									m_reactionPairs[i].pGeo2->m_effectParamList.Add(m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList[j]);
								}
							}
						}
					}
				}
			}
		}
		m_reactionPairs.RemoveAt(i);
	}*/

	int32 i = 0;
	while (i < m_reactionPairs.Num())
	{
		if (!m_reactionPairs[i].pGeo1 || !m_reactionPairs[i].pGeo2)
		{
			m_reactionPairs.RemoveAt(i);
			continue;
		}
		if (m_reactionPairs[i].reactionType == 0 || m_reactionPairs[i].reactionType == 2)
		{
			if (m_reactionPairs[i].reactionName1.Contains("Spawn_") || m_reactionPairs[i].reactionName1.Contains("Reflect_") ||
				m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
			{
				FString spawnName;
				FVector spawnLoc = m_reactionPairs[i].pGeo1->GetActorLocation();
				FRotator spawnRot = m_reactionPairs[i].pGeo1->GetActorRotation();
				if (m_reactionPairs[i].reactionName1.Contains("Reflect_") || m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
				{
					if (m_reactionPairs[i].reactionName1.Contains("Reflect_"))
					{
						spawnName = m_reactionPairs[i].reactionName1.RightChop(8);
						FVector geo2ForwardVector = m_reactionPairs[i].pGeo2->GetActorForwardVector();
						FVector offset = m_reactionPairs[i].pGeo2->GetActorLocation() - m_reactionPairs[i].pGeo1->GetActorLocation();
						offset.Normalize();
						FVector2D reflectVec(geo2ForwardVector.X, geo2ForwardVector.Y);
						bool successFlag = UCollisionWarBpFunctionLibrary::GetReflectVectorWithDirAndNormalVector(FVector2D(geo2ForwardVector.X, geo2ForwardVector.Y),
							FVector2D(offset.X, offset.Y), reflectVec);
						FVector reflectVec3D(reflectVec.X, reflectVec.Y, 0.f);
						spawnRot = reflectVec3D.Rotation();
					}
					else
					{
						spawnName = m_reactionPairs[i].reactionName1.RightChop(11);
						spawnRot = m_reactionPairs[i].pGeo1->GetActorRotation();
					}
					spawnLoc = m_reactionPairs[i].pGeo2->GetActorLocation();
				}
				else
					spawnName = m_reactionPairs[i].reactionName1.RightChop(6);
				if (m_reactionPairs[i].pGeo1->m_pTransformPS.Contains(2) && m_reactionPairs[i].pGeo1->m_pTransformPS[2])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo1->m_pTransformPS[2],
						m_reactionPairs[i].pGeo1->GetActorLocation(), m_reactionPairs[i].pGeo1->GetActorRotation());
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo1->m_spawnMutateGeo[spawnName], spawnLoc, spawnRot);
				pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo1);
				pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo2);
				AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo1->m_pHost, 0);
				if (m_reactionPairs[i].pGeo1->m_pSpawnMutatePSActor.Contains(spawnName))
				{
					AActor* pMutateActor = GetWorld()->SpawnActor<AActor>(m_reactionPairs[i].pGeo1->m_pSpawnMutatePSActor[spawnName],
						m_reactionPairs[i].pGeo1->GetActorLocation(), m_reactionPairs[i].pGeo1->GetActorRotation());
					m_spawnMutateActorMap.Add(pPhysGeo, pMutateActor);
					SpawnActorEmitter(pPhysGeo, pMutateActor, m_reactionPairs[i].pGeo1->m_spawnMutateActorPSType[spawnName]);
				}
				if (m_reactionPairs[i].reactionName1.Contains("Reflect_") || m_reactionPairs[i].reactionName1.Contains("ReflectFix_"))
					m_reactionPairs[i].pGeo2->m_isGeoValid = false;
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Disapear_"))
			{
				m_reactionPairs[i].pGeo1->m_isGeoValid = false;
				if (m_reactionPairs[i].pGeo1->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo1->m_pTransformPS[0])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo1->m_pTransformPS[0],
						m_reactionPairs[i].pGeo1->GetActorLocation(), m_reactionPairs[i].pGeo1->GetActorRotation());
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Transform_") || m_reactionPairs[i].reactionName1.Contains("Combine_"))
			{
				m_reactionPairs[i].pGeo1->m_isGeoValid = false;
				if (m_reactionPairs[i].reactionName1.Contains("Combine_")) m_reactionPairs[i].pGeo2->m_isGeoValid = false;
				if (m_reactionPairs[i].pGeo1->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo1->m_pTransformPS[0])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo1->m_pTransformPS[0],
						m_reactionPairs[i].pGeo1->GetActorLocation(), m_reactionPairs[i].pGeo1->GetActorRotation());
				FString spawnName;
				if (m_reactionPairs[i].reactionName1.Contains("Transform_"))
					spawnName = m_reactionPairs[i].reactionName1.RightChop(10);
				else
					spawnName = m_reactionPairs[i].reactionName1.RightChop(8);
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo1->m_spawnMutateGeo[spawnName], m_reactionPairs[i].reactionLoc1, m_reactionPairs[i].reactionRot1);
				pPhysGeo->m_pRootGeos = m_reactionPairs[i].pGeo1->m_pRootGeos;
				AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo1->m_pHost, 0);
			}
			else if (m_reactionPairs[i].reactionName1.Contains("Mutate_"))
			{
				FString mutateName = m_reactionPairs[i].reactionName1.RightChop(7);
				if (mutateName == "Fire")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 0;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(0);
				}
				else if (mutateName == "Water")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 1;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(1);
				}
				else if (mutateName == "Freeze")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 2;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(2);
				}
				else if (mutateName == "Wood")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 3;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(3);
				}
				else if (mutateName == "Ground")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 4;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(4);
				}
				else if (mutateName == "Dark")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 5;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(5);
				}
				else if (mutateName == "Light")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 6;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(6);
				}
				else if (mutateName == "Wind")
				{
					m_reactionPairs[i].pGeo1->m_enhanceType = 7;
					m_reactionPairs[i].pGeo1->m_attributeList.Add(7);
				}
				m_reactionPairs[i].pGeo1->AppendEnhanceParticle(m_reactionPairs[i].pGeo1->m_enhanceType);

				if (m_reactionPairs[i].pGeo1->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo1->m_enhanceType))
				{
					if (m_reactionPairs[i].pGeo1->m_physGeoType == EPhysGeoType::PGT_Poly)
					{
						APhysPolygon* pPolygon = Cast<APhysPolygon>(m_reactionPairs[i].pGeo1);
						PolygonEffectPreCalculate(pPolygon, m_reactionPairs[i].pGeo1->m_enhanceEffectParamList[m_reactionPairs[i].pGeo1->m_enhanceType].effectParamList);
					}
					m_reactionPairs[i].pGeo1->AddEnhanceEffectToOverlapCharacters(m_reactionPairs[i].pGeo1->m_enhanceType);
					//跟其他集合类型不一样，点类技能接触被击中者可能只是一瞬间，所以如果当它移动走了到击中下一个角色时，由于它没有执行
					//这个反应计算函数，便无法施加enhance效果，所以点类几何要将enhance效果的paramlist添加到普通effectparamlist中
					if (m_reactionPairs[i].pGeo1->m_physGeoType == EPhysGeoType::PGT_Point)
					{
						if (m_reactionPairs[i].pGeo1->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo1->m_enhanceType))
						{
							for (int32 j = 0; j < m_reactionPairs[i].pGeo1->m_enhanceEffectParamList[m_reactionPairs[i].pGeo1->m_enhanceType].effectParamList.Num(); j++)
							{
								m_reactionPairs[i].pGeo1->m_effectParamList.Add(m_reactionPairs[i].pGeo1->m_enhanceEffectParamList[m_reactionPairs[i].pGeo1->m_enhanceType].effectParamList[j]);
							}
						}
					}
				}
			}
		}
		if (m_reactionPairs[i].reactionType == 1 || m_reactionPairs[i].reactionType == 2)
		{
			if (m_reactionPairs[i].reactionName2.Contains("Spawn_") || m_reactionPairs[i].reactionName2.Contains("Reflect_") ||
				m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
			{
				FString spawnName;
				FVector spawnLoc = m_reactionPairs[i].pGeo2->GetActorLocation();
				FRotator spawnRot = m_reactionPairs[i].pGeo2->GetActorRotation();
				if (m_reactionPairs[i].reactionName2.Contains("Reflect_") || m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
				{
					if (m_reactionPairs[i].reactionName2.Contains("Reflect_"))
					{
						spawnName = m_reactionPairs[i].reactionName2.RightChop(8);
						FVector geo1ForwardVector = m_reactionPairs[i].pGeo1->GetActorForwardVector();
						FVector offset = m_reactionPairs[i].pGeo1->GetActorLocation() - m_reactionPairs[i].pGeo2->GetActorLocation();
						offset.Normalize();
						FVector2D reflectVec(geo1ForwardVector.X, geo1ForwardVector.Y);
						bool successFlag = UCollisionWarBpFunctionLibrary::GetReflectVectorWithDirAndNormalVector(FVector2D(geo1ForwardVector.X, geo1ForwardVector.Y),
							FVector2D(offset.X, offset.Y), reflectVec);
						FVector reflectVec3D(reflectVec.X, reflectVec.Y, 0.f);
						spawnRot = reflectVec3D.Rotation();
					}
					else
					{
						spawnName = m_reactionPairs[i].reactionName2.RightChop(11);
						spawnRot = m_reactionPairs[i].pGeo2->GetActorRotation();
					}
					spawnLoc = m_reactionPairs[i].pGeo1->GetActorLocation();
				}
				else
					spawnName = m_reactionPairs[i].reactionName2.RightChop(6);
				if (m_reactionPairs[i].pGeo2->m_pTransformPS.Contains(2) && m_reactionPairs[i].pGeo2->m_pTransformPS[2])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo2->m_pTransformPS[2],
						m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo2->m_spawnMutateGeo[spawnName], spawnLoc, spawnRot);
				pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo2);
				pPhysGeo->m_pRootGeos.Add(m_reactionPairs[i].pGeo1);
				AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo2->m_pHost, 0);
				if (m_reactionPairs[i].pGeo2->m_pSpawnMutatePSActor.Contains(spawnName))
				{
					AActor* pMutateActor = GetWorld()->SpawnActor<AActor>(m_reactionPairs[i].pGeo2->m_pSpawnMutatePSActor[spawnName],
						m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
					m_spawnMutateActorMap.Add(pPhysGeo, pMutateActor);
					SpawnActorEmitter(pPhysGeo, pMutateActor, m_reactionPairs[i].pGeo2->m_spawnMutateActorPSType[spawnName]);
				}
				if (m_reactionPairs[i].reactionName2.Contains("Reflect_") || m_reactionPairs[i].reactionName2.Contains("ReflectFix_"))
					m_reactionPairs[i].pGeo1->m_isGeoValid = false;
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Disapear_"))
			{
				m_reactionPairs[i].pGeo2->m_isGeoValid = false;
				if (m_reactionPairs[i].pGeo2->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo2->m_pTransformPS[0])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo2->m_pTransformPS[0],
						m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Transform_") || m_reactionPairs[i].reactionName2.Contains("Combine_"))
			{
				m_reactionPairs[i].pGeo2->m_isGeoValid = false;
				if (m_reactionPairs[i].reactionName2.Contains("Combine_")) m_reactionPairs[i].pGeo1->m_isGeoValid = false;
				if (m_reactionPairs[i].pGeo2->m_pTransformPS.Contains(0) && m_reactionPairs[i].pGeo2->m_pTransformPS[0])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_reactionPairs[i].pGeo2->m_pTransformPS[0],
						m_reactionPairs[i].pGeo2->GetActorLocation(), m_reactionPairs[i].pGeo2->GetActorRotation());
				FString spawnName;
				if (m_reactionPairs[i].reactionName2.Contains("Transform_"))
					spawnName = m_reactionPairs[i].reactionName2.RightChop(10);
				else
					spawnName = m_reactionPairs[i].reactionName2.RightChop(8);
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_reactionPairs[i].pGeo2->m_spawnMutateGeo[spawnName], m_reactionPairs[i].reactionLoc2, m_reactionPairs[i].reactionRot2);
				pPhysGeo->m_pRootGeos = m_reactionPairs[i].pGeo2->m_pRootGeos;
				AddPhysGeo(pPhysGeo, m_reactionPairs[i].pGeo2->m_pHost, 0);
			}
			else if (m_reactionPairs[i].reactionName2.Contains("Mutate_"))
			{
				FString mutateName = m_reactionPairs[i].reactionName2.RightChop(7);
				if (mutateName == "Fire")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 0;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(0);
				}
				else if (mutateName == "Water")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 1;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(1);
				}
				else if (mutateName == "Freeze")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 2;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(2);
				}
				else if (mutateName == "Wood")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 3;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(3);
				}
				else if (mutateName == "Ground")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 4;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(4);
				}
				else if (mutateName == "Dark")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 5;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(5);
				}
				else if (mutateName == "Light")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 6;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(6);
				}
				else if (mutateName == "Wind")
				{
					m_reactionPairs[i].pGeo2->m_enhanceType = 7;
					m_reactionPairs[i].pGeo2->m_attributeList.Add(7);
				}
				m_reactionPairs[i].pGeo2->AppendEnhanceParticle(m_reactionPairs[i].pGeo2->m_enhanceType);

				if (m_reactionPairs[i].pGeo2->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo2->m_enhanceType))
				{
					if (m_reactionPairs[i].pGeo2->m_physGeoType == EPhysGeoType::PGT_Poly)
					{
						APhysPolygon* pPolygon = Cast<APhysPolygon>(m_reactionPairs[i].pGeo2);
						PolygonEffectPreCalculate(pPolygon, m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList);
					}
					m_reactionPairs[i].pGeo2->AddEnhanceEffectToOverlapCharacters(m_reactionPairs[i].pGeo2->m_enhanceType);
					//跟其他集合类型不一样，点类技能接触被击中者可能只是一瞬间，所以如果当它移动走了到击中下一个角色时，由于它没有执行
					//这个反应计算函数，便无法施加enhance效果，所以点类几何要将enhance效果的paramlist添加到普通effectparamlist中
					if (m_reactionPairs[i].pGeo2->m_physGeoType == EPhysGeoType::PGT_Point)
					{
						if (m_reactionPairs[i].pGeo2->m_enhanceEffectParamList.Contains(m_reactionPairs[i].pGeo2->m_enhanceType))
						{
							for (int32 j = 0; j < m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList.Num(); j++)
							{
								m_reactionPairs[i].pGeo2->m_effectParamList.Add(m_reactionPairs[i].pGeo2->m_enhanceEffectParamList[m_reactionPairs[i].pGeo2->m_enhanceType].effectParamList[j]);
							}
						}
					}
				}
			}
		}
		m_reactionPairs.RemoveAt(i);
	}
}

void APhysCalculator::CalCharacterAttributeReaction(ABaseCharacter* pHitCharacter, TArray<uint8> atkAttributes, TArray<FActiveAttributeReactionInfo>& flashEffects)
{
	//bool isOnlyOppCamp = false;
	//TArray<FEffectParams> pGeo->m_effectParamList;
	/*if (pGeo->m_enhanceType == -1) effectParamList = pGeo->m_effectParamList;
	else
	{
		if (pGeo->m_mutationEffectParamList.Contains((uint8)pGeo->m_enhanceType))
			effectParamList = pGeo->m_mutationEffectParamList[(uint8)pGeo->m_enhanceType];
	}*/
	/*if (pGeo->m_effectParamList.Num() > 0)
	{
		if (pGeo->m_effectParamList[0].effectExertType == 0) isOnlyOppCamp = true;
	}*/
	//if (isOnlyOppCamp && pHitCharacter->m_campFlag == pGeo->m_campFlag) return;
	/** 先进行双向元素剔除，例
	* 冰  火  水
	* 水          | 火
	* 双向剔除后剩下
	* 火  水      | 火
	*/
	TArray<uint8> originAtkAttributes = atkAttributes;
	TArray<uint8> dfcAttributes;
	pHitCharacter->m_tempAttributes.GetKeys(dfcAttributes);
	//先对比现有的元素和攻击元素是否完全相等，如是则直接重置防守方的元素时间即可
	if (atkAttributes.Num() == dfcAttributes.Num())
	{
		bool isAllContain = true;
		for (int32 i=0; i<atkAttributes.Num(); i++)
		{
			if (dfcAttributes.Contains(atkAttributes[i]))
			{
				if (m_attributeAttachTimeMap.Contains(atkAttributes[i]))
					pHitCharacter->m_tempAttributes[atkAttributes[i]] = m_attributeAttachTimeMap[atkAttributes[i]];
			}
			isAllContain = false;
		}
		if (isAllContain) return;
	}

	for (int32 i=0; i<atkAttributes.Num(); i++)
	{
		for (int32 j = 0; j < m_defaultAttributeReactionInfos.Num(); j++)
		{
			//当攻击物体是优势元素，同时防御方含有弱势元素时，才可以删除弱势元素，删除时要记录即时效果如造成伤害
			if (m_defaultAttributeReactionInfos[j].advantageAttribute != atkAttributes[i] ||
				!dfcAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute) ||
				m_defaultAttributeReactionInfos[j].continuousType != 0)
				continue;
			FActiveAttributeReactionInfo newAttributeReactionInfo(m_defaultAttributeReactionInfos[j].effectParams, 0, 0);
			flashEffects.Add(newAttributeReactionInfo);
			if (dfcAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute))
				dfcAttributes.Remove(m_defaultAttributeReactionInfos[j].weakAttribute);
			break;
		}
	}
	/** 双向剔除第二步，如防御方元素为优势，剔除进攻方的元素，例如
	* 火  水
	* 水     | 火
	* 双向剔除后剩下
	* 水
	* 水     | 火
	*/
	for (int32 i=0; i<dfcAttributes.Num(); i++)
	{
		for (int32 j = 0; j < m_defaultAttributeReactionInfos.Num(); j++)
		{
			//当防御是优势元素，同时攻击方含有弱势元素时，才可以删除弱势元素，删除时要记录即时效果如造成伤害
			if (m_defaultAttributeReactionInfos[j].advantageAttribute != dfcAttributes[i] ||
				!atkAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute) ||
				m_defaultAttributeReactionInfos[j].continuousType != 0)
				continue;
			FActiveAttributeReactionInfo newAttributeReactionInfo(m_defaultAttributeReactionInfos[j].effectParams, 0, 0);
			flashEffects.Add(newAttributeReactionInfo);
			if (atkAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute))
				atkAttributes.Remove(m_defaultAttributeReactionInfos[j].weakAttribute);
			break;
		}
	}
	/** 进行进攻和防守两方的元素融合
	*/
	TArray<uint8> oldDfcAttributes = dfcAttributes;
	TArray<uint8> newAttributes;
	for (int32 i=0; i<atkAttributes.Num(); i++)
	{
		if (dfcAttributes.Contains(atkAttributes[i])) continue;
		dfcAttributes.Add(atkAttributes[i]);
		newAttributes.Add(atkAttributes[i]);
	}
	/** 然后对现有的所有元素进行元素剔除，例如
	* 冰  火  水
	* 水          | 火
	* 双向剔除后剩下
	* 冰  火  水      | 火
	* 那么临时元素中水和火也应当再进行一次冰灭水，然后火灭冰的剔除
	*/
	TArray<uint8> removeAttributeList;
	for (int32 i=0; i<dfcAttributes.Num(); i++)
	{
		//首先如果被剔除元素包含这个元素，那么不用做检测了，因为这个元素已经不存在的了
		if (removeAttributeList.Contains(dfcAttributes[i])) continue;
		for (int32 j = 0; j < m_defaultAttributeReactionInfos.Num(); j++)
		{
			//当攻击物体是优势元素，同时防御方含有弱势元素时，才可以删除弱势元素，删除时要记录即时效果如造成伤害
			if (m_defaultAttributeReactionInfos[j].advantageAttribute != dfcAttributes[i] ||
				!dfcAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute) ||
				m_defaultAttributeReactionInfos[j].continuousType != 0)
				continue;
			if (!removeAttributeList.Contains(m_defaultAttributeReactionInfos[j].weakAttribute))
				removeAttributeList.Add(m_defaultAttributeReactionInfos[j].weakAttribute);
			break;
		}
	}
	int32 removeNb = 0;
	while (removeNb < dfcAttributes.Num())
	{
		if (removeAttributeList.Contains(dfcAttributes[removeNb]))
			dfcAttributes.RemoveAt(removeNb);
		else removeNb += 1;
	}
	removeNb = 0;
	while (removeNb < newAttributes.Num())
	{
		if (removeAttributeList.Contains(newAttributes[removeNb]))
			newAttributes.RemoveAt(removeNb);
		else removeNb += 1;
	}
	/** 再和固有元素进行比对剔除，例如火鸟原本就有火元素，当临时元素含有冰元素时，应当剔除冰元素
	* 这时临时元素是进攻方，固有元素是防守方
	*/
	for (int32 i=0; i<pHitCharacter->m_intrinsicAttibutes.Num(); i++)
	{
		//先把那些重复的元素先剔除了吧
		if (dfcAttributes.Contains(pHitCharacter->m_intrinsicAttibutes[i]))
		{
			dfcAttributes.Remove(pHitCharacter->m_intrinsicAttibutes[i]);
			if (newAttributes.Contains(pHitCharacter->m_intrinsicAttibutes[i]))
				newAttributes.Remove(pHitCharacter->m_intrinsicAttibutes[i]);
			continue;
		}
		//先看角色本身自身规定的元素反应列表有没有对应的特殊反应
		bool getIntrinsicReaction = false;
		for (int32 j=0; j<pHitCharacter->m_intrinsicAttributeReactionInfos.Num(); j++)
		{
			if (pHitCharacter->m_intrinsicAttributeReactionInfos[j].advantageAttribute == pHitCharacter->m_intrinsicAttibutes[i] &&
				newAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute) &&
				pHitCharacter->m_intrinsicAttributeReactionInfos[j].continuousType == 0)
			{
				FActiveAttributeReactionInfo newAttributeReactionInfo(pHitCharacter->m_intrinsicAttributeReactionInfos[j].effectParams, 0, 0);
				flashEffects.Add(newAttributeReactionInfo);
				if (dfcAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute))
					dfcAttributes.Remove(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute);
				if (newAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute))
					newAttributes.Remove(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute);
				getIntrinsicReaction = true;
				break;
			}
			else if (pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute == pHitCharacter->m_intrinsicAttibutes[i] &&
				newAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].advantageAttribute) &&
				pHitCharacter->m_intrinsicAttributeReactionInfos[j].continuousType == 0)
			{
				// 这里是针对那些即时反应的，例如被攻击者是火属性，然后被水淋湿，那么可能触发禁魔这种长期效果，也可能放大伤害这种短期效果
				//短期这里处理，长期在下面
				FActiveAttributeReactionInfo newAttributeReactionInfo(pHitCharacter->m_intrinsicAttributeReactionInfos[j].effectParams, 0, 0);
				flashEffects.Add(newAttributeReactionInfo);
				if (dfcAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute)) 
					dfcAttributes.Remove(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute);
				if (newAttributes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute))
					newAttributes.Remove(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute);
				getIntrinsicReaction = true;
				break;
			}
		}
		if (getIntrinsicReaction) continue;
		//如角色本身没有对应的特殊反应，则查看默认反应列表
		/*for (int32 j = 0; j < m_defaultAttributeReactionInfos.Num(); j++)
		{
			//当攻击物体是优势元素，同时防御方含有弱势元素时，才可以删除弱势元素，删除时要记录即时效果如造成伤害
			if (m_defaultAttributeReactionInfos[j].advantageAttribute != pHitCharacter->m_intrinsicAttibutes[i] ||
				!dfcAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute) ||
				m_defaultAttributeReactionInfos[j].continuousType != 0)
				continue;
			FActiveAttributeReactionInfo newAttributeReactionInfo(m_defaultAttributeReactionInfos[j].effectParams, false, 0);
			flashEffects.Add(newAttributeReactionInfo);
			if (dfcAttributes.Contains(m_defaultAttributeReactionInfos[j].weakAttribute)) dfcAttributes.Remove(m_defaultAttributeReactionInfos[j].weakAttribute);
			break;
		}*/
	}
	/** 最后形成稳定的元素组合，这时要更新临时元素的剩余时间
	*/
	TArray<uint8> removeTempList;
	for (TMap<uint8, float>::TConstIterator iter = pHitCharacter->m_tempAttributes.CreateConstIterator(); iter; ++iter)
	{
		if (!dfcAttributes.Contains(iter->Key)) removeTempList.Add(iter->Key);
	}
	for (int32 i=0; i<removeTempList.Num(); i++)
	{
		pHitCharacter->m_tempAttributes.Remove(removeTempList[i]);
		pHitCharacter->AddOrRemoveAttachPS(removeTempList[i], false);
	}
	for (int32 i=0; i<dfcAttributes.Num(); i++)
	{
		if (!pHitCharacter->m_tempAttributes.Contains(dfcAttributes[i]))
		{
			bool isTemp = false;
			for (int32 j=0; j<pHitCharacter->m_intrinsicAttributeReactionInfos.Num(); j++)
			{
				if (pHitCharacter->m_intrinsicAttributeReactionInfos[j].advantageAttribute == dfcAttributes[i] &&
					pHitCharacter->m_intrinsicAttributeReactionInfos[j].effectType == 0)
				{
					isTemp = true;
					break;
				}
			}
			if (!isTemp)
			{
				if (m_attributeAttachTimeMap.Contains(dfcAttributes[i]))
				{
					pHitCharacter->m_tempAttributes.Add(dfcAttributes[i], m_attributeAttachTimeMap[dfcAttributes[i]]);
					pHitCharacter->AddOrRemoveAttachPS(dfcAttributes[i], true);
				}
			}
		}
	}
	/*for (int32 i=0; i<dfcAttributes.Num(); i++)
	{
		if (!originAtkAttributes.Contains(dfcAttributes[i]) || !pHitCharacter->m_tempAttributes.Contains(dfcAttributes[i])) continue;
		pHitCharacter->m_tempAttributes[dfcAttributes[i]] = m_attributeAttachTimeMap[dfcAttributes[i]];
		//pHitCharacter->m_tempAttributes[dfcAttributes[i]] = 
	}*/
	/** 原本这里要更新所有临时激活组合，如原本有火烧木的元素组合，由于火元素被剔除，那么对应的这个反应也应该删除，但为了简单，现在
	* 所有临时元素的反应都改成即时性的反应，例如木遇到火就加强攻击就完了
	*/
	/*int32 activeNb = 0;
	while (activeNb < pHitCharacter->m_curTempActiveAttributeInfo.Num())
	{
		if (dfcAttributes.Contains(pHitCharacter->m_curTempActiveAttributeInfo[activeNb].reactionAttribute1) &&
			dfcAttributes.Contains(pHitCharacter->m_curTempActiveAttributeInfo[activeNb].reactionAttribute2))
		{
			activeNb += 1;
			continue;
		}
		pHitCharacter->m_curTempActiveAttributeInfo.RemoveAt(activeNb);
	}*/
	/** 更新所有固有元素组合，例如有水淋湿了火属性的火鸟，导致火鸟无法喷火，现在水属性被去除了，对应的这个反应也要驱除
	*/
	TArray<uint8> removeKeys;
	for (TMap<uint8, FEffectList>::TConstIterator iter = pHitCharacter->m_curIntrinsicActiveAttributeInfo.CreateConstIterator(); iter; ++iter)
	{
		if (dfcAttributes.Contains(iter->Key))
		{
			continue;
		}
		for (int32 i=0; i< iter->Value.Effects.Num(); i++)
		{
			iter->Value.Effects[i]->m_isOnTimeEffectDone = true;
		}
		removeKeys.Add(iter->Key);
	}
	for (int32 i=0; i<removeKeys.Num(); i++)
	{
		pHitCharacter->m_curIntrinsicActiveAttributeInfo.Remove(removeKeys[i]);
	}

	/** 补充那些没有的反应，从atkAttributes入手，因为新增的元素都是atkAttributes来的
	*/
	for (int32 i=0; i<newAttributes.Num(); i++)
	{
		//根据新的元素生成新的固有属性元素反应组合，这时临时元素是进攻方，所以应该对比优势元素
		for (int32 j=0; j<pHitCharacter->m_intrinsicAttributeReactionInfos.Num(); j++)
		{
			if (pHitCharacter->m_intrinsicAttributeReactionInfos[j].advantageAttribute == newAttributes[i] && 
				pHitCharacter->m_intrinsicAttibutes.Contains(pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute) && 
				pHitCharacter->m_intrinsicAttributeReactionInfos[j].continuousType == 1)
			{
				FActiveAttributeReactionInfo newIntrinsicInfo(pHitCharacter->m_intrinsicAttributeReactionInfos[j].effectParams, 
					pHitCharacter->m_intrinsicAttributeReactionInfos[j].effectType, pHitCharacter->m_intrinsicAttributeReactionInfos[j].time);
				newIntrinsicInfo.reactionAttribute1 = pHitCharacter->m_intrinsicAttributeReactionInfos[j].advantageAttribute;
				newIntrinsicInfo.reactionAttribute2 = pHitCharacter->m_intrinsicAttributeReactionInfos[j].weakAttribute;
				flashEffects.Add(newIntrinsicInfo);
			}
		}
	}
}

void APhysCalculator::AddAttributeReactionEffect(ABaseCharacter* pCharacter, const FActiveAttributeReactionInfo& reactionInfo, ABasePhysGeo* pGeo)
{
	if (!pCharacter || !pGeo) return;
	//这种属性反应类的效果不需要判断是否跟原有效果重叠，因为这些效果是要和指定geo绑定的
	//必须要与geo绑定的原因是因为属性反应类的效果不外乎增强该geo的攻击效果、削弱攻击效果、附加伤害、补血这些，那么就必须绑定然后到updateeffects才知道
	//究竟削弱或增强的是哪个geo的攻击效果
	if (reactionInfo.reactionEffectParam.effectExertType == 0 && pGeo->m_campFlag == pCharacter->m_campFlag) return;
	else if (reactionInfo.reactionEffectParam.effectExertType == 2 && pGeo->m_campFlag != pCharacter->m_campFlag) return;
	else if (reactionInfo.reactionEffectParam.effectExertType == 3 && (pGeo->m_campFlag != pCharacter->m_campFlag || pCharacter->m_characterClassName == pGeo->m_pHost->m_characterClassName)) return;

	if (reactionInfo.reactionEffectParam.functionNames.Num() <= 0) return;
	FString effectName = reactionInfo.reactionEffectParam.functionNames[0];
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
	if (!effectClass) return;
	UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
	//必须指定该效果的类型是AttributeReactionEffect，因为AttributeReactionEffect是只一帧有效的，当其标志oneTimeEffectDone就要删除了
	if (reactionInfo.exertType == 2)
		pNewEffect->m_effectType = "AttributeReactionEffect_InstrinsicActive";
	else if (reactionInfo.exertType == 1)
		pNewEffect->m_effectType = "AttributeReactionEffect_InstrinsicPassive";
	else
		pNewEffect->m_effectType = "AttributeReactionEffect";
	pNewEffect->m_launchType = 2;
	pNewEffect->m_effectDefaultParam = reactionInfo.reactionEffectParam;
	pNewEffect->m_pOriginGeo = pGeo;
	pNewEffect->m_pHost = pGeo->m_pHost;
	pNewEffect->m_duration = reactionInfo.reactionEffectParam.duration;
	pNewEffect->m_effectName = reactionInfo.reactionEffectParam.effectName;
	pNewEffect->m_effectValues = reactionInfo.reactionEffectParam.effectValues;
	pNewEffect->m_functionNames = reactionInfo.reactionEffectParam.functionNames;
	pNewEffect->m_effectOnIntervalList = reactionInfo.reactionEffectParam.effectOnIntervalList;
	pNewEffect->m_isIntervalLoop = reactionInfo.reactionEffectParam.isIntervalLoop;
	pNewEffect->m_isPhysOrMag = reactionInfo.reactionEffectParam.isPhysOrMag;
	pNewEffect->m_isJudgeEffect = reactionInfo.reactionEffectParam.isJudgeEffect;
	pNewEffect->m_hitColors = reactionInfo.reactionEffectParam.hitColors;
	pNewEffect->m_hitNbs = reactionInfo.reactionEffectParam.hitNbs;
	pNewEffect->m_isPermenant = reactionInfo.reactionEffectParam.isPermenant;
	pNewEffect->m_canOverlap = reactionInfo.reactionEffectParam.canOverlap;
	pNewEffect->m_appendEffectList = reactionInfo.reactionEffectParam.appendEffectList;
	pCharacter->m_pEffects.Add(pNewEffect);
	if (reactionInfo.exertType)
	{
		//因为在CalCharacterAttributeReaction中已经规定了临时元素是Attribute1，所以可以直接取reactioninfo中的attribute1作为key
		if (pCharacter->m_curIntrinsicActiveAttributeInfo.Contains(reactionInfo.reactionAttribute1))
			pCharacter->m_curIntrinsicActiveAttributeInfo[reactionInfo.reactionAttribute1].Effects.Add(pNewEffect);
		else
		{
			FEffectList newEffectList;
			newEffectList.Effects.Add(pNewEffect);
			pCharacter->m_curIntrinsicActiveAttributeInfo.Add(reactionInfo.reactionAttribute1, newEffectList);
		}
	}
}

void APhysCalculator::AddSpecificTagScaleEffect(ABaseCharacter* pCharacter, ABasePhysGeo* pGeo)
{
	if (!pCharacter || !pGeo) return;
	FString effectName = "ResistHurt";
	TSubclassOf<class UObject> effectClass = m_pCWSingleton->FindEffectClassByName(effectName);
	if (!effectClass) return;
	UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
	//必须指定该效果的类型是AttributeReactionEffect，因为AttributeReactionEffect是只一帧有效的，当其标志oneTimeEffectDone就要删除了
	pNewEffect->m_effectType = "AttributeReactionEffect";
	pNewEffect->m_launchType = 2;
	pNewEffect->m_pOriginGeo = pGeo;
	pNewEffect->m_pHost = pGeo->m_pHost;
	pNewEffect->m_effectName = effectName;
	pNewEffect->m_effectValues.Add(m_specificTagEffectReduction);
	pNewEffect->m_functionNames.Add(effectName);
	pNewEffect->m_effectOnIntervalList.Add(0);
	pNewEffect->m_isIntervalLoop = false;
	pNewEffect->m_isJudgeEffect = false;
	pNewEffect->m_isPermenant = false;
	pNewEffect->m_canOverlap = true;
	pCharacter->m_pEffects.Add(pNewEffect);
}

