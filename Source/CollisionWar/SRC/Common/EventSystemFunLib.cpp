// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Base/Battle/BattleLevelPlayerController.h"
#include "../Game/Battle/RoguelikeBattleGameMode.h"
#include "CollisionWarSingleton.h"
#include "EffectFunLib.h"
#include "EventSystemFunLib.h"




void UEventSystemFunLib::SpawnEffectToPlayer(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	if (!pRGM->m_pPlayerCharacter) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(param.functionNames[1]);
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pRGM, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	UEffect* pNewEffect = NewObject<UEffect>(pRGM->m_pPlayerCharacter, effectClass);
	pNewEffect->m_effectDefaultParam = param;
	pNewEffect->m_pOriginGeo = NULL;
	pNewEffect->m_pHost = NULL;
	pNewEffect->m_duration = param.duration;
	pNewEffect->m_effectName = param.functionNames[2];
	pNewEffect->m_effectValues = param.effectValues;
	pNewEffect->m_functionNames.Add(param.functionNames[1]);
	pNewEffect->m_effectOnIntervalList = param.effectOnIntervalList;
	pNewEffect->m_isIntervalLoop = param.isIntervalLoop;
	pNewEffect->m_isPhysOrMag = param.isPhysOrMag;
	pNewEffect->m_isJudgeEffect = param.isJudgeEffect;
	pNewEffect->m_hitColors = param.hitColors;
	pNewEffect->m_hitNbs = param.hitNbs;
	pNewEffect->m_isPermenant = param.isPermenant;
	pNewEffect->m_canOverlap = param.canOverlap;
	pNewEffect->m_appendEffectList = param.appendEffectList;
	if (pBattlePC->m_pBattleMenu)
	{
		if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
			pNewEffect->m_description = param.chDescription;
		else
			pNewEffect->m_description = param.enDescription;
	}
	pRGM->m_pPlayerCharacter->m_pEffects.Add(pNewEffect);
	
	if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pRGM->m_pPlayerCharacter)
		pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
	if (pNewEffect->m_effectType != "OneTimeEffect")
		UEffectFunLib::AddStateToCharacter(pRGM->m_pPlayerCharacter, param.functionNames[1]);
}

void UEventSystemFunLib::SpawnGeo(FEffectParams& param, ABasePhysActor* pPhysActor)
{
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(pPhysActor);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	if (!pRGM->m_pPlayerCharacter) return;
	ABasePhysGeo* pGeo = pRGM->m_pPhysCalculator->SpawnPhysGeo(pPhysActor->m_producePhysActorClass, pPhysActor->GetActorLocation(), FRotator::ZeroRotator);
	pGeo->m_logicPos2D = pPhysActor->m_logicPos2D;
	pGeo->m_logicForwardDir = FLogicVec2D(0, 0);
	pRGM->m_pPlayerCharacter->m_pNewSpawnPhysGeos.Add(pGeo);*/
}

void UEventSystemFunLib::SpawnEffectToType(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	FString typeName = param.effectName.RightChop(13);
	uint8 type = 0;
	if (typeName == "Human")
		type = 0;
	else if (typeName == "Devil")
		type = 1;
	else if (typeName == "Beast")
		type = 2;
	else if (typeName == "Dragon")
		type = 3;
	else if (typeName == "Goblin")
		type = 4;
	else if (typeName == "Orc")
		type = 5;
	else if (typeName == "Ghost")
		type = 6;
	else if (typeName == "Sant")
		type = 7;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pRGM, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pRGM->m_pAllCharacters.Num(); i++)
	{
		if (!pRGM->m_pAllCharacters[i] || pRGM->m_pAllCharacters[i]->m_characterRace != type || pRGM->m_pAllCharacters[i]->m_characterType != 0) continue;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(param.functionNames[1]);
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pRGM->m_pAllCharacters[i], effectClass);
		pNewEffect->m_effectDefaultParam = param;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = NULL;
		pNewEffect->m_duration = param.duration;
		pNewEffect->m_effectName = param.functionNames[2];
		pNewEffect->m_effectValues = param.effectValues;
		pNewEffect->m_functionNames.Add(param.functionNames[1]);
		pNewEffect->m_effectOnIntervalList = param.effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = param.isIntervalLoop;
		pNewEffect->m_isPhysOrMag = param.isPhysOrMag;
		pNewEffect->m_isJudgeEffect = param.isJudgeEffect;
		pNewEffect->m_hitColors = param.hitColors;
		pNewEffect->m_hitNbs = param.hitNbs;
		pNewEffect->m_isPermenant = param.isPermenant;
		pNewEffect->m_canOverlap = param.canOverlap;
		pNewEffect->m_appendEffectList = param.appendEffectList;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = param.chDescription;
			else
				pNewEffect->m_description = param.enDescription;
		}
		pRGM->m_pAllCharacters[i]->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pRGM->m_pAllCharacters[i])
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		if (pNewEffect->m_effectType != "OneTimeEffect")
			UEffectFunLib::AddStateToCharacter(pRGM->m_pAllCharacters[i], param.functionNames[1]);
	}
}

void UEventSystemFunLib::GetResources(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	FString typeName = param.effectName.RightChop(12);
	if (typeName == "FirstResource")
		pRGM->m_scoreLevelMaps[1] += param.effectValues[0];
	else if (typeName == "SecondResource")
		pRGM->m_scoreLevelMaps[2] += param.effectValues[0];
	else if (typeName == "ThirdResource")
		pRGM->m_scoreLevelMaps[3] += param.effectValues[0];
	else if (typeName == "FourthResource")
		pRGM->m_scoreLevelMaps[4] += param.effectValues[0];
	else if (typeName == "FifthResource")
		pRGM->m_scoreLevelMaps[5] += param.effectValues[0];
}

void UEventSystemFunLib::IncreaseEquipCardNbByAppendString(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	if (!pRGM->m_pPlayerCharacter) return;
	FString appendString = param.effectName.RightChop(27);
	for (int32 i=0; i<pRGM->m_pPlayerCharacter->m_pEquipmentInfos.Num(); i++)
	{
		if (!pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i] || !pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentName.Contains(appendString)) continue;
		pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentNb += pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentNb * param.effectValues[0] / 100;
	}
}

void UEventSystemFunLib::GetResourcesByEquipCardAppendString(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	FString appendString = param.effectName.RightChop(29);
	if (!pRGM->m_pPlayerCharacter) return;
	int32 equipNb = 0;
	for (int32 i=0; i<pRGM->m_pPlayerCharacter->m_pEquipmentInfos.Num(); i++)
	{
		if (!pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i] || !pRGM->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentName.Contains(appendString)) continue;
		equipNb += 1;
	}
	int32 resourceNb = param.effectValues[0] * equipNb;
	int32 type = 0;
	if (param.functionNames[1].Contains("FirstResource"))
		type = 0;
	else if (param.functionNames[1].Contains("SecondResource"))
		type = 1;
	else if (param.functionNames[1].Contains("ThirdResource"))
		type = 2;
	else if (param.functionNames[1].Contains("FourthResource"))
		type = 3;
	else if (param.functionNames[1].Contains("FifthResource"))
		type = 4;
	pRGM->m_scoreLevelMaps[type] += resourceNb;
}

void UEventSystemFunLib::TradeDiscount(FEffectParams& param, ARoguelikeBattleGameMode* pRGM)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pRGM, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	for (TMap<FString, FItemCardInfo>::TConstIterator iter = pBLPC->m_itemCardInfoMap.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.level != param.effectValues[0] || iter->Value.cardType != param.effectValues[1]) continue;
	}
}
