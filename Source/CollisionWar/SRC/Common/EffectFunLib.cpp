// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Game/Battle/RoguelikeBattleGameMode.h"
#include "../Base/Battle/BattleLevelPlayerController.h"
#include "WidgetBlueprintFunctionLibrary.h"
#include "../Base/Widget/TActivateEffectInfo.h"
#include "../Base/Widget/THurtNbInfo.h"
#include "../Base/CollisionWarGameInstance.h"
#include "EffectFunLib.h"

void UEffectFunLib::AddStateToCharacter(ABaseCharacter* pCharacter, FString stateName)
{
	if (!pCharacter) return;
	if (pCharacter->m_stateNames.Contains(stateName)) return;
	pCharacter->m_stateNames.Add(stateName);
	pCharacter->NotifyAddCharacterState(stateName);
	if (pCharacter->m_characterType != 0) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	/*UWidgetBlueprintFunctionLibrary::AddEnermyInfoToBattleMenu(pCharacter->m_characterRace, pCharacter->m_characterClassName,
		pCharacter->m_stateNames, pBLPC->m_pBattleMenu);*/
}

void UEffectFunLib::PlayHitParticleSystem(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_hasPlayFx) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	FVector spawnLoc = pCharacter->GetActorLocation();
	UParticleSystem* pHitParticle = NULL;
	if (pEffect->m_pOriginGeo) pHitParticle = pEffect->m_pOriginGeo->m_pHitParticleSystem;
	else pHitParticle = pSingleton->FindHitParticleByName(pEffect->m_effectName);
	if (pHitParticle) UGameplayStatics::SpawnEmitterAtLocation(pEffect, pHitParticle, spawnLoc);
	pEffect->m_hasPlayFx = true;
}

/*
void UEffectFunLib::PlaySuperposeParticleSystem(ABasePhysGeo* pGeo, FString superposeAttributeName)
{
	if (!pGeo || !pGeo->m_pSuperposePSMap.Contains(superposeAttributeName) || !pGeo->m_pSuperposePSMap[superposeAttributeName]) return;
	UParticleSystem* pHitParticle = pGeo->m_pSuperposePSMap[superposeAttributeName];
	UGameplayStatics::SpawnEmitterAttached(pHitParticle, pGeo->m_pBasicComponent);
}*/

void UEffectFunLib::UpdateScores(int32 hurtVal, ABaseCharacter* pHurtCharacter, uint8 hurtType)
{
	/*if (!pHurtCharacter || pHurtCharacter->m_characterType != 0) return;
	pHurtCharacter->m_beAttackedNb += 1;

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pHurtCharacter);
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
	if (pBLGM->m_characterHurtOneTickMap.Contains(pHurtCharacter))
	{
		if (hurtType >= 0 && hurtType <= 5) pBLGM->m_characterHurtOneTickMap[pHurtCharacter].hurtType = 1;
		else if (hurtType == 6) pBLGM->m_characterHurtOneTickMap[pHurtCharacter].hurtType = 2;
		pBLGM->m_characterHurtOneTickMap[pHurtCharacter].hurtVal += hurtVal;
	}
	else
	{
		FHurtTypeAndValueInfo info;
		if (hurtType >= 0 && hurtType <= 5) info.hurtType = 1;
		else if (hurtType == 6) info.hurtType = 2;
		info.hurtVal += hurtVal;
		pBLGM->m_characterHurtOneTickMap.Add(pHurtCharacter, info);
	}*/
}

void UEffectFunLib::DemonstrateActivateEffect(UEffect* pEffect, ABaseCharacter* pTarget)
{
	/*if (!pTarget || !pTarget->m_pCharacterInfoWidget) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pEffect, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pWidgetManager) return;
	TSubclassOf<class UTActivateEffectInfo> pClass = pBLPC->m_pBattleMenu->m_pWidgetManager->m_widgetClassMap["ActivateEffectInfo"];
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pBLPC->m_pBattleMenu->m_pWidgetManager);
	UTActivateEffectInfo* pActivateEffectInfo = CreateWidget<UTActivateEffectInfo>(pGI, pClass);
	pActivateEffectInfo->NotifyInitial();
	pActivateEffectInfo->SetupInfo(pEffect->m_effectName);
	UPanelSlot* pSlot = pTarget->m_pCharacterInfoWidget->m_pCanvasPanel->AddChild(pActivateEffectInfo);
	UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
	FAnchors anchors(0.5, 0.5);
	pCanvasSlot->SetAnchors(anchors);
	pCanvasSlot->SetAlignment(FVector2D(0.5, 0.5));
	pCanvasSlot->SetPosition(FVector2D(0, -80));
	//pTarget->m_pCharacterInfoWidget->m_pActivateEffectInfos.Add(pActivateEffectInfo);
	pActivateEffectInfo->m_pParentCharacterInfo = pTarget->m_pCharacterInfoWidget;
	pActivateEffectInfo->NotifyFadeOut();*/
}

void UEffectFunLib::DemonstrateHurtNb(int32 hurtNb, ABaseCharacter* pTarget)
{
	if (!pTarget || !pTarget->m_pCharacterInfoWidget) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pTarget, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pWidgetManager) return;
	TSubclassOf<class UTHurtNbInfo> pClass = pBLPC->m_pBattleMenu->m_pWidgetManager->m_widgetClassMap["HurtNbInfo"];
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pBLPC->m_pBattleMenu->m_pWidgetManager);
	UTHurtNbInfo* pHurtNbInfo = CreateWidget<UTHurtNbInfo>(pGI, pClass);
	pHurtNbInfo->NotifyInitial();
	pHurtNbInfo->SetupNb(hurtNb);
	UPanelSlot* pSlot = pTarget->m_pCharacterInfoWidget->m_pCanvasPanel->AddChild(pHurtNbInfo);
	UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
	FAnchors anchors(0.5, 0.5);
	pCanvasSlot->SetAnchors(anchors);
	pCanvasSlot->SetAlignment(FVector2D(0.5, 0.5));
	pCanvasSlot->SetPosition(FVector2D(0, -80));
	pHurtNbInfo->NotifyFadeOut();
	if (hurtNb >= pBLPC->m_shakeCamHurtThreshold)
		pBLPC->NotifyShakeCamera();
	//pTarget->m_pCharacterInfoWidget->m_pActivateEffectInfos.Add(pActivateEffectInfo);
	//pHurtNbInfo->m_pParentCharacterInfo = pTarget->m_pCharacterInfoWidget;
}

bool UEffectFunLib::OneTimeJudgeListEffect(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return false;
	//if (pCharacter->m_allJudgeCardInfos.Num() != pEffect->m_effectOnIntervalList.Num()) return false;
	TArray<int32> effectActivateList = pEffect->m_effectOnIntervalList;
	TArray<FIntGroup> groups;
	int32 index = effectActivateList.Find(-1);
	while (index != INDEX_NONE)
	{
		FIntGroup newGroup;
		for (int32 i=0; i<index; i++)
		{
			newGroup.group.Add(effectActivateList[0]);
			effectActivateList.RemoveAt(0);
		}
		effectActivateList.RemoveAt(0);
		groups.Add(newGroup);
		index = effectActivateList.Find(-1);
	}
	bool isEffectOn = false;
	for (int32 i=0; i< groups.Num(); i++)
	{
		TArray<int32> allJudgeCardList = pCharacter->m_allJudgeCardInfos;
		bool findList = true;
		for (int32 j = 0; j < groups[i].group.Num(); j++)
		{
			int32 loc = allJudgeCardList.Find(groups[i].group[j]);
			if (loc == INDEX_NONE)
			{
				findList = false;
				break;
			}
			else allJudgeCardList.RemoveAt(loc);
		}
		if (!findList) continue;
		isEffectOn = true;
		break;
	}
	
	if (!isEffectOn) return false;
	pCharacter->UpdateJudgeCardList(-1);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	/*if (pBattlePC->m_pCharacterStatusMenu)
		pBattlePC->m_pCharacterStatusMenu->UpdateJudgeInfoList();*/
	return true;
}

void UEffectFunLib::SpawnAppendGeoByName(ABasePhysGeo* pParentGeo, FString geoName, FVector logicSpawnLoc)
{
	if (!pParentGeo) return;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pParentGeo);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	if (!pRGM->m_pPhysCalculator || !pRGM->m_pPhysCalculator->m_effectAppendGeoClassMap.Contains(geoName)) return;
	TSubclassOf<class ABasePhysGeo> geoClass = pRGM->m_pPhysCalculator->m_effectAppendGeoClassMap[geoName];

	FVector launchLoc(logicSpawnLoc.X, logicSpawnLoc.Y, pParentGeo->m_defaultHeight + pParentGeo->m_relativeHeight);
	ABasePhysGeo* pGeo = pRGM->m_pPhysCalculator->SpawnPhysGeo(pRGM->m_pPhysCalculator->m_effectAppendGeoClassMap[geoName], launchLoc, FRotator::ZeroRotator);
	pParentGeo->m_pRootGeos.Add(pGeo);
	pGeo->m_pRootGeos.Add(pParentGeo);
	pRGM->m_pPhysCalculator->AddPhysGeo(pGeo, NULL, pParentGeo->m_campFlag);
	pGeo->m_hierachy = 0;
}

void UEffectFunLib::SpawnGeoByName(ABaseCharacter* pHost, FString geoName, FVector spawnLoc, FRotator spawnRot)
{
	if (!pHost) return;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pHost);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	if (!pRGM->m_pPhysCalculator) return;
	TArray<TSubclassOf<class ABasePhysGeo> > geoClasses;
	for (int32 i=0; i<pHost->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (geoName != pHost->m_pBaseEquipment->m_pSkills[i]->m_skillName) continue;
		if (pHost->m_pBaseEquipment->m_pSkills[i]->m_mutationGeoClass.Contains(pHost->m_pBaseEquipment->m_pSkills[i]->m_mutationType))
			geoClasses = pHost->m_pBaseEquipment->m_pSkills[i]->m_mutationGeoClass[pHost->m_pBaseEquipment->m_pSkills[i]->m_mutationType].geoClasses;
		for (int32 j = 0; j < geoClasses.Num(); j++)
		{
			if (!geoClasses[j]) continue;
			//int32 halfNb = (pSkill->m_spawnGeoNb[i] - pSkill->m_spawnGeoNb[i] % 2) / 2;
			//geoNb = 0;
			for (int32 k = 0; k < pHost->m_pBaseEquipment->m_pSkills[i]->m_spawnGeoNb[i]; k++)
			{
				
				//这里要根据技能类型来确定生成的位置
				ABasePhysGeo* pGeo = pRGM->m_pPhysCalculator->SpawnPhysGeo(geoClasses[j], spawnLoc, spawnRot);
				
				pHost->m_pNewSpawnPhysGeos.Add(pGeo);
				if (pHost->m_pBaseEquipment->m_pSkills[i]->m_isHostSkill)
					pHost->m_pControlPhysGeos.Add(pGeo);
			}
		}

		break;
	}

	
}

/*

void UEffectFunLib::WriteCombatInfo(UEffect* pEffect)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pEffect, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pWidgetManager) return;
	TSubclassOf<class UTMultiLineTextBlock> pClass = pBLPC->m_pBattleMenu->m_pWidgetManager->m_widgetClassMap["MultiLineTextBlock"];
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pBLPC->m_pBattleMenu->m_pWidgetManager);
	UTMultiLineTextBlock* pMLTB = CreateWidget<UTMultiLineTextBlock>(pGI, pClass);
	pMLTB->NotifyInitial();
	pMLTB->m_pTextBlock->SetText(FText::FromString(pEffect->m_finalCombatDescription));
	pBLPC->m_pBattleMenu->m_pCombatTextScrollBox->AddChild(pMLTB);
	pBLPC->m_pBattleMenu->m_pCombatInfos.Add(pMLTB);
	if (pBLPC->m_pBattleMenu->m_pCombatInfos.Num() > pBLPC->m_pBattleMenu->m_maxCombatDescNb)
	{
		pBLPC->m_pBattleMenu->m_pCombatInfos[0]->RemoveFromParent();
		if (pBLPC->m_pBattleMenu->m_pCombatInfos[0]->IsValidLowLevel())
			pBLPC->m_pBattleMenu->m_pCombatInfos[0]->ConditionalBeginDestroy();
		pBLPC->m_pBattleMenu->m_pCombatInfos.RemoveAt(0);
	}
}
*/

bool UEffectFunLib::Judge(int32& outColor, int32& outNb, UEffect* pJudgeEffect, ABaseCharacter* pTargetCharacter, ABaseCharacter* pSourceCharacter)
{
	if (!pTargetCharacter || !pJudgeEffect) return false;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pTargetCharacter);
	if (!pGameMode) return false;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode) return false;
	if (pTargetCharacter->m_judgeInfo.availableJudgeColors.Num() == 0 || pTargetCharacter->m_judgeInfo.availableJudgeNbs.Num() == 0) return false;
	int32 colorNb = FMath::RandRange(0, pTargetCharacter->m_judgeInfo.availableJudgeColors.Num() - 1);
	int32 numNb = FMath::RandRange(0, pTargetCharacter->m_judgeInfo.availableJudgeNbs.Num() - 1);
	outColor = pTargetCharacter->m_judgeInfo.availableJudgeColors[colorNb];
	outNb = pTargetCharacter->m_judgeInfo.availableJudgeNbs[numNb];
	//进行判定结果展示，即生成判定粒子
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	int32 judgeNb = outColor * 13 + outNb;
	FVector spawnLoc = pTargetCharacter->GetActorLocation() + FVector(0, 0, pBattleLevelGameMode->m_judgeResultSpawnHeight);
	UParticleSystem* pJudgeParticleSystem = pSingleton->FindJudgeParticleByNb(judgeNb);
	if (pJudgeParticleSystem) UGameplayStatics::SpawnEmitterAtLocation(pBattleLevelGameMode, pJudgeParticleSystem, spawnLoc);
	//将判定结果添加到角色判定牌堆中
	//pTargetCharacter->UpdateJudgeCardList(pTargetCharacter->m_judgeInfo.availableJudgeNbs[numNb]);
	pTargetCharacter->UpdateJudgeCardList(judgeNb);
	/*APlayerController* pPC = UGameplayStatics::GetPlayerController(pTargetCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);*/
	/*if (pBattlePC->m_pCharacterStatusMenu)
		pBattlePC->m_pCharacterStatusMenu->UpdateJudgeInfoList();*/
	pBattleLevelGameMode->m_pPhysCalculator->ActivateAccumulateJudgeEffect(pTargetCharacter);
	//激活角色那些需要判定牌才能发动的技能
	if (pBattleLevelGameMode->m_pPhysCalculator)
	{
		pBattleLevelGameMode->m_pPhysCalculator->ActivateJudgeEffect(outColor, outNb, pTargetCharacter);
		if (pSourceCharacter) pBattleLevelGameMode->m_pPhysCalculator->ActivateSourceJudgeEffect(outColor, outNb, pSourceCharacter);
	}
	if (pJudgeEffect->m_hitColors.Contains(outColor) && pJudgeEffect->m_hitNbs.Contains(outNb))
		return true;
	else return false;
}

void UEffectFunLib::Hurt(UEffect* pEffect, ABaseCharacter* pCharacter,const int32& damageCoeK1,const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	if (pCharacter->m_Hp > 0)
	{
		int32 scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
		HurtCharacter(scaleATK, pEffect, pCharacter);
	}
}

void UEffectFunLib::HurtNoHost(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pOriginGeo || pEffect->m_pOriginGeo->m_campFlag == pCharacter->m_campFlag) return;
	if (pCharacter->m_Hp > 0) HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
}

void UEffectFunLib::HurtAmplifiedByJudge(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);
	if (pCharacter->m_Hp <= 0) return;

	int32 scaleATK = 0;
	if (judgeResult)
	{
		//DemonstrateActivateEffect(pEffect, pCharacter);
		/*if (pEffect->m_isPhysOrMag)
			scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * pEffect->m_effectValues[1];
		else
			scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition) * pEffect->m_effectValues[1];*/
		scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * pEffect->m_effectValues[1];
	}
	else
	{
		/*if (pEffect->m_isPhysOrMag)
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
		else
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition;*/
		scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	}
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/

	HurtCharacter(scaleATK, pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::HurtAmplified(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal)
{
	if (!pEffect || !pHurtEffect) return hurtVal;
	int32 modifyHurtVal = hurtVal;
	if (pEffect->m_effectType == "AttributeReactionEffect")
	{
		//如果是AttributeReactionEffect的话，就要判断增益effect和攻击effect是否同一geo，是的话才能放大
		if (pEffect->m_pOriginGeo && pEffect->m_pOriginGeo == pHurtEffect->m_pOriginGeo)
		{
			modifyHurtVal = hurtVal + hurtVal * pEffect->m_effectValues[0] / 100;
			pEffect->m_isOnTimeEffectDone = true;
		}
	}
	else
	{
		modifyHurtVal = hurtVal + hurtVal * pEffect->m_effectValues[0] / 100;
	}
	DemonstrateActivateEffect(pEffect, pHurtTarget);
	//PlayHitParticleSystem(pEffect, pHurtTarget);
	return modifyHurtVal;
}

void UEffectFunLib::SuperposeAttribute(UEffect* pEffect, ABasePhysGeo* pIntroGeo, int32 effectParamNb)
{
	/*if (!pEffect || !pIntroGeo) return;
	FAppendEffectInfo appendEffectInfo;
	appendEffectInfo.duration = pIntroGeo->m_effectParamList[effectParamNb].duration;
	appendEffectInfo.effectName = pEffect->m_effectName;
	appendEffectInfo.hitColors = pEffect->m_hitColors;
	appendEffectInfo.hitNbs = pEffect->m_hitNbs;
	appendEffectInfo.isJudgeEffect = false;
	appendEffectInfo.isPhysOrMag = pEffect->m_isPhysOrMag;
	pIntroGeo->m_effectParamList[effectParamNb].appendEffectList.Add(appendEffectInfo);
	if (pIntroGeo->m_effectParamList[effectParamNb].effectName == "Hurt")
	{
		pIntroGeo->m_effectParamList[effectParamNb].effectValues[0] += pEffect->m_effectValues[0] * pIntroGeo->m_effectParamList[effectParamNb].effectValues[0] / 100;
	}*/
}

int32 UEffectFunLib::HurtAmplifiedByAttribute(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal)
{
	if (!pEffect || !pHurtEffect || !pHurtEffect->m_pOriginGeo) return hurtVal;
	FString appendString = pEffect->m_effectName.RightChop(15);
	bool shouldAmplified = false;
	if (appendString == "Fire" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(0)) shouldAmplified = true;
	else if (appendString == "Water" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(1)) shouldAmplified = true;
	else if (appendString == "Wood" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(3)) shouldAmplified = true;
	else if (appendString == "Ground" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(4)) shouldAmplified = true;
	else if (appendString == "Freeze" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(2)) shouldAmplified = true;
	else if (appendString == "Dark" && pHurtEffect->m_pOriginGeo->m_attributeList.Contains(5)) shouldAmplified = true;

	int32 modifyHurtVal = hurtVal;
	if (shouldAmplified)
		modifyHurtVal = hurtVal + hurtVal * pEffect->m_effectValues[0] / 100;
	DemonstrateActivateEffect(pEffect, pHurtTarget);
	//PlayHitParticleSystem(pEffect, pHurtTarget);
	return modifyHurtVal;
}

void UEffectFunLib::HurtReflect(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHost, int32 hurtVal)
{
	if (!pEffect || !pHost || !pHurtEffect || !pHurtEffect->m_pHost) return;
	int32 reflectHurtVal = hurtVal * pEffect->m_effectValues[0] / 100;
	int32 originHp = pHurtEffect->m_pHost->m_Hp;
	int32 leftHp = pHurtEffect->m_pHost->m_Hp - reflectHurtVal;
	if (leftHp <= 0)
		pHurtEffect->m_pHost->m_Hp = 0;
	else
		pHurtEffect->m_pHost->m_Hp = leftHp;
	DemonstrateHurtNb(originHp - pHurtEffect->m_pHost->m_Hp, pHurtEffect->m_pHost);
	DemonstrateActivateEffect(pEffect, pHurtEffect->m_pHost);
	if (pHurtEffect->m_pHost->m_pCharacterInfoWidget)
		pHurtEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pHurtEffect->m_pHost->m_Hp, pHurtEffect->m_pHost->m_DFC);
	pHurtEffect->m_pHost->EffectOnFx(true);
	PlayHitBeamParticle(pHost, pHurtEffect->m_pHost, pEffect);
}

void UEffectFunLib::AbsorbSameTagHurtToPlayer(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::ExemptHurtIfEffectAppendString(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pCharacter || !pHurtEffect || !pHurtEffect->m_pHost) return hurtVal;
	FString exemptStr = pEffect->m_effectName.RightChop(24);
	bool exemptFlag = false;
	if (pHurtEffect->m_effectName.Contains(exemptStr)) exemptFlag = true;
	DemonstrateActivateEffect(pEffect, pHurtEffect->m_pHost);
	if (exemptFlag) return 0;
	else return hurtVal;
}

void UEffectFunLib::ChangeJudgeFromRedToBlack(UEffect* pEffect, int32& judgeColor, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	if (judgeColor == 0) judgeColor = 1;
	else if (judgeColor == 2) judgeColor = 3;
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Vampire(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	RecoverCharacter(pEffect->m_effectValues[1], pEffect, pEffect->m_pHost);
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::VampireRevert(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pEffect->m_pHost);
	RecoverCharacter(pEffect->m_effectValues[1], pEffect, pCharacter);
	PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
}

void UEffectFunLib::ExtraHurtByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	if (pCharacter->m_Hp <= 0) return;
	FString appendString = pEffect->m_effectName.RightChop(17);
	int32 appendStringNb = 0;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pEffect->m_effectName == pCharacter->m_pEffects[i]->m_effectName) continue;
		if (pCharacter->m_pEffects[i]->m_effectName.Contains(appendString))
		{
			DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
			appendStringNb += 1;
		}
	}
	
	HurtCharacter(pEffect->m_effectValues[0] * appendStringNb, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtAmplifiedByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	FString appendString = pEffect->m_effectName.RightChop(21);
	int32 appendStringNb = 0;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i]) continue;
		if (pCharacter->m_pEffects[i]->m_effectName.Contains(appendString) && pCharacter->m_pEffects[i]->m_effectName != pEffect->m_effectName)
		{
			DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
			appendStringNb += 1;
		}
	}

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * (100 + appendStringNb * pEffect->m_effectValues[1]) / 100;
	int32 damage = 0;
	/*if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pEffect->m_pHost->m_pBaseEquipment) return;
	int32 cardNb = 0;
	for (int32 i=1; i<pEffect->m_pHost->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i]) continue;
		cardNb += 1;
	}
	cardNb = FMath::Clamp(cardNb, 0, 6);

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * (100 + (6 - cardNb) * pEffect->m_effectValues[1]) / 100;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByLeftCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pEffect->m_pHost->m_pBaseEquipment) return;
	int32 cardNb = 0;
	if (pEffect->m_effectValues[0] == 0)
	{
		for (int32 i = 1; i < pEffect->m_pHost->m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (!pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i]) continue;
			cardNb += 1;
		}
	}
	else if (pEffect->m_effectValues[0] == 1)
	{
		for (int32 i = 1; i < pEffect->m_pHost->m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (!pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i] || !pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) continue;
			cardNb += 1;
		}
	}
	else if (pEffect->m_effectValues[0] == 2)
	{
		for (int32 i = 1; i < pEffect->m_pHost->m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (!pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i] || pEffect->m_pHost->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) continue;
			cardNb += 1;
		}
	}
	
	cardNb = FMath::Clamp(cardNb, 0, 6);

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	if (cardNb <= pEffect->m_effectValues[1])
		scaleATK = pEffect->m_effectValues[2] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	else
		scaleATK = pEffect->m_effectValues[3] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByAttackCardNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pCharacter->m_pBaseEquipment) return;
	int32 atkCardNb = 0;
	for (int32 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i]) continue;
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) atkCardNb += 1;
	}

	int32 damage = atkCardNb * pEffect->m_effectValues[0];
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(damage, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Oppress(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter) return;

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = (pEffect->m_effectValues[1] + pEffect->m_pHost->m_ATKAddition) * (1 + pEffect->m_effectValues[0] * pEffect->m_effectValues[2] / 100);
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Universe(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	if (pEffect->m_effectValues[0] == 0)
	{
		//说明是第一次触发该效果，此时只需要记录技能发动者的Hp即可
		pEffect->m_effectValues[1] = pEffect->m_pHost->m_Hp;
		pEffect->m_effectValues[0] = 1;
		pEffect->m_effectDefaultParam.effectValues[0] = 1;
		pEffect->m_effectDefaultParam.effectValues[1] = pEffect->m_effectValues[1];
		return;
	}
	else
	{
		//说明这是第二次触发该效果，此时需要对发动者的Hp进行判定，如Hp与第一次记录的Hp一致，即对击中者进行扣血
		if (pEffect->m_pHost->m_Hp < pEffect->m_effectValues[1])
		{
			int32 hpDif = pEffect->m_effectValues[1] - pEffect->m_pHost->m_Hp;
			int32 damage = hpDif * pEffect->m_effectValues[2] / 100;
			DemonstrateActivateEffect(pEffect, pCharacter);
			HurtCharacter(damage, pEffect, pCharacter);
		}
		PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
	}
}

void UEffectFunLib::Eclosion(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (judgeResult)
	{
		/*int32 originHp = pCharacter->m_Hp;
		int32 hpPercent = pCharacter->m_Hp * 100 / pCharacter->m_originHp;
		if (pCharacter->m_ATKAddition >= 100) pCharacter->m_Hp = pCharacter->m_originHp;
		else if (pCharacter->m_ATKAddition > 0) pCharacter->m_Hp = pCharacter->m_originHp*pCharacter->m_ATKAddition / 100;
		else pCharacter->m_Hp = 0;*/
		//UpdateScores(originHp - pCharacter->m_Hp, pCharacter, pEffect->m_enhanceType);
		//pCharacter->m_ATKAddition = hpPercent;
		//DemonstrateActivateEffect(pEffect, pCharacter);
		int32 tempDFC = pCharacter->m_DFC;
		pCharacter->m_DFC = pCharacter->m_ATKAddition;
		int32 difAtk = tempDFC - pCharacter->m_ATKAddition;
		pCharacter->m_ATKAddition += difAtk;
		pEffect->m_modifiedValues.Add(difAtk);
		if (pCharacter->m_pCharacterInfoWidget)
			pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
		pCharacter->EffectOnFx(true);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Eclosion_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::HurtShareByCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	int32 trueHurtVal = 0;
	if (pCharacter->m_Hp > 0)
	{
		trueHurtVal = 0;
		if (pEffect->m_isPhysOrMag)
		{
			if (pCharacter->m_DFC > 0)
			{
				if (pCharacter->m_DFC > pEffect->m_effectValues[0])
				{
					pCharacter->m_DFC -= pEffect->m_effectValues[0];
					trueHurtVal = pEffect->m_effectValues[0];
				}
				else
				{
					trueHurtVal += pCharacter->m_DFC;
					int32 damage = pEffect->m_effectValues[0] - pCharacter->m_DFC;
					pCharacter->m_DFC = 0;
					int32 originHp = pCharacter->m_Hp;
					int32 leftHp = pCharacter->m_Hp - damage;
					if (leftHp <= 0)
						pCharacter->m_Hp = 0;
					else
						pCharacter->m_Hp = leftHp;
					trueHurtVal += originHp - pCharacter->m_Hp;
				}
			}
			else
			{
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal = originHp - pCharacter->m_Hp;
			}
		}
		else
		{
			if (pCharacter->m_magDFC > 0)
			{
				if (pCharacter->m_magDFC > pEffect->m_effectValues[0])
				{
					pCharacter->m_magDFC -= pEffect->m_effectValues[0];
					trueHurtVal = pEffect->m_effectValues[0];
				}
				else
				{
					trueHurtVal += pCharacter->m_magDFC;
					int32 damage = pEffect->m_effectValues[0] - pCharacter->m_magDFC;
					pCharacter->m_magDFC = 0;
					int32 originHp = pCharacter->m_Hp;
					int32 leftHp = pCharacter->m_Hp - damage;
					if (leftHp <= 0)
						pCharacter->m_Hp = 0;
					else
						pCharacter->m_Hp = leftHp;
					trueHurtVal += originHp - pCharacter->m_Hp;
				}
			}
			else
			{
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal = originHp - pCharacter->m_Hp;
			}
		}

		/*int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
		if (leftHp <= 0)
			pCharacter->m_Hp = 0;
		else
			pCharacter->m_Hp = leftHp;*/
		DemonstrateHurtNb(trueHurtVal, pCharacter);
		DemonstrateActivateEffect(pEffect, pCharacter);
		//UpdateScores(trueHurtVal, pCharacter, 0);
		if (pCharacter->m_pCharacterInfoWidget)
			pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
		pCharacter->EffectOnFx(true);
	}
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::HurtByCompanionHpLess(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	if (pCharacter->m_Hp <= 0) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = (pEffect->m_effectValues[2] + pEffect->m_pHost->m_ATKAddition) * (1 + pEffect->m_effectValues[1] * pEffect->m_effectValues[3]);
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByAverageDefPercent(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	if (pCharacter->m_Hp <= 0) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = (pEffect->m_effectValues[2] + pEffect->m_pHost->m_ATKAddition) * (1 + (pEffect->m_effectValues[1] - pEffect->m_effectValues[0]) * pEffect->m_effectValues[3]);
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCompareDfc(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	int32 amplifiedCoe = 1;
	if (pEffect->m_pHost->m_DFC <= pCharacter->m_DFC) amplifiedCoe = pEffect->m_effectValues[1];
	scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * amplifiedCoe;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCompareAttack(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	int32 amplifiedCoe = 1;
	int32 hostAtk = pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	int32 characterAtk = pCharacter->m_ATK + pCharacter->m_ATKAddition;
	if (hostAtk <= characterAtk) amplifiedCoe = pEffect->m_effectValues[1];
	if (pEffect->m_isPhysOrMag)
		scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * amplifiedCoe;
	else
		scaleATK = (pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition) * amplifiedCoe;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByAverageAtkPercent(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag) return;
	if (pCharacter->m_Hp <= 0) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = (pEffect->m_effectValues[2] + pEffect->m_pHost->m_ATKAddition) * (1 + (pEffect->m_effectValues[1] - pEffect->m_effectValues[0]) * pEffect->m_effectValues[3]);
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtOrRecoverByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	if (judgeResult)
	{
		HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
		PlayHitParticleSystem(pEffect, pCharacter);
	}
	else
	{
		RecoverCharacter(pEffect->m_effectValues[1], pEffect, pCharacter);
		PlayHitParticleSystem(pEffect, pCharacter);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByDifCampFlag(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	int32 amplifiedCoe = pEffect->m_effectValues[3] - pEffect->m_effectValues[2];
	amplifiedCoe = FMath::Clamp(amplifiedCoe, 0, 3);
	scaleATK = (pEffect->m_effectValues[0]) * (100 + amplifiedCoe * pEffect->m_effectValues[1]*100) / 100;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCompareAtkAndNoneAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pCharacter->m_pBaseEquipment || pCharacter->m_characterType == 0) return;
	int32 atkCardNb = 0;
	int32 noneAtkCardNb = 0;
	for (int32 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) atkCardNb += 1;
		else noneAtkCardNb += 1;
	}

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATKAddition;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);

	if (noneAtkCardNb < atkCardNb) return;
	int32 hostHp = pEffect->m_pHost->m_Hp + pEffect->m_effectValues[1];
	if (hostHp >= pEffect->m_pHost->m_originHp) pEffect->m_pHost->m_Hp = pEffect->m_pHost->m_originHp;
	else pEffect->m_pHost->m_Hp = hostHp;
	if (pEffect->m_pHost->m_pCharacterInfoWidget)
		pEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pEffect->m_pHost->m_Hp, pEffect->m_pHost->m_DFC);
	pEffect->m_pHost->EffectOnFx(false);
	PlayHitParticleSystem(pEffect, pEffect->m_pHost);
}

void UEffectFunLib::ExtraHurtByCardNumber(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment || pCharacter->m_characterType == 0) return;
	int32 cardNb = pCharacter->m_pBaseEquipment->m_pSkills.Num() - 1;
	if (cardNb >= pEffect->m_effectValues[1])
	{
		//DemonstrateActivateEffect(pEffect, pCharacter);
		HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
		PlayHitParticleSystem(pEffect, pCharacter);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ExtraHurtByCardAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pCharacter->m_pBaseEquipment || pCharacter->m_characterType == 0) return;
	int32 extraHurtCardNb = 0;
	for (int32 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Freeze") ||
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Water") ||
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Cloud"))
			extraHurtCardNb += 1;
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(extraHurtCardNb * pEffect->m_effectValues[0], pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtAccordLiveNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pEffect);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode) return;
	if (pEffect->m_effectValues[0] == -1)
	{
		//说明是第一次触发，只需要记录下当前人数
		pEffect->m_effectValues[0] = pBattleLevelGameMode->m_pAllCharacters.Num();
		return;
	}
	else
	{
		int32 liveCharacterDif = pEffect->m_effectValues[0] - pBattleLevelGameMode->m_pAllCharacters.Num();
		if (liveCharacterDif > 0)
		{
			int32 damage = pEffect->m_effectValues[1] * liveCharacterDif;
			//DemonstrateActivateEffect(pEffect, pCharacter);
			HurtCharacter(damage, pEffect, pCharacter);
		}
		PlayHitParticleSystem(pEffect, pCharacter);
	}
}

void UEffectFunLib::ExtraHurtByCompareCardAndCharacterNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment) return;
	if (pEffect->m_effectValues[0] <= pCharacter->m_pBaseEquipment->m_pSkills.Num() - 1)
	{
		//DemonstrateActivateEffect(pEffect, pCharacter);
		HurtCharacter(pEffect->m_effectValues[1], pEffect, pCharacter);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ExtraHurtIfEvenCharacters(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ExtraHurtByCompareAtk(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	int32 scaleHostATK = pEffect->m_pHost->m_ATKAddition;
	int32 scaleTargeATK = pCharacter->m_ATKAddition;
	bool hurtTargetFlag = true;
	if (scaleTargeATK > scaleHostATK) hurtTargetFlag = false;
	//DemonstrateActivateEffect(pEffect, pCharacter);
	if (!hurtTargetFlag)
	{
		HurtCharacter(pEffect->m_effectValues[1], pEffect, pEffect->m_pHost);
		PlayHitParticleSystem(pEffect, pEffect->m_pHost);
	}
	else
	{
		HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
		PlayHitParticleSystem(pEffect, pCharacter);
	}
}

void UEffectFunLib::ExtraHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	if (pCharacter->m_Hp > 0)
	{
		int32 trueHurtVal = 0;
		if (pEffect->m_isPhysOrMag)
		{
			if (pCharacter->m_DFC > 0)
			{
				if (pCharacter->m_DFC > pEffect->m_effectValues[0])
				{
					pCharacter->m_DFC -= pEffect->m_effectValues[0];
					trueHurtVal = pEffect->m_effectValues[0];
				}
				else
				{
					trueHurtVal += pCharacter->m_DFC;
					int32 damage = pEffect->m_effectValues[0] - pCharacter->m_DFC;
					pCharacter->m_DFC = 0;
					int32 originHp = pCharacter->m_Hp;
					int32 leftHp = pCharacter->m_Hp - damage;
					if (leftHp <= 0)
						pCharacter->m_Hp = 0;
					else
						pCharacter->m_Hp = leftHp;
					trueHurtVal += originHp - pCharacter->m_Hp;
				}
			}
			else
			{
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal = originHp - pCharacter->m_Hp;
			}
		}
		else
		{
			if (pCharacter->m_magDFC > 0)
			{
				if (pCharacter->m_magDFC > pEffect->m_effectValues[0])
				{
					pCharacter->m_magDFC -= pEffect->m_effectValues[0];
					trueHurtVal = pEffect->m_effectValues[0];
				}
				else
				{
					trueHurtVal += pCharacter->m_magDFC;
					int32 damage = pEffect->m_effectValues[0] - pCharacter->m_magDFC;
					pCharacter->m_magDFC = 0;
					int32 originHp = pCharacter->m_Hp;
					int32 leftHp = pCharacter->m_Hp - damage;
					if (leftHp <= 0)
						pCharacter->m_Hp = 0;
					else
						pCharacter->m_Hp = leftHp;
					trueHurtVal += originHp - pCharacter->m_Hp;
				}
			}
			else
			{
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal = originHp - pCharacter->m_Hp;
			}
		}

		/*int32 originHp = pCharacter->m_Hp;
		int32 leftHp = pCharacter->m_Hp - pEffect->m_effectValues[0];
		if (leftHp <= 0)
			pCharacter->m_Hp = 0;
		else
			pCharacter->m_Hp = leftHp;*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
		DemonstrateHurtNb(trueHurtVal, pCharacter);
		//UpdateScores(trueHurtVal, pCharacter, pEffect->m_enhanceType);
		if (pCharacter->m_pCharacterInfoWidget)
			pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
		pCharacter->EffectOnFx(true);
	}
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::ExtraHurtByCompareCardAndDifTagNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCoverCharacterGrade(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	if (pCharacter->m_Hp > 0)
	{
		/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
		int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
		int32 scaleATK = 0;
		if (pEffect->m_isPhysOrMag)
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
		else
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition;
		/*int32 damage = 0;
		if (!pEffect->m_isPhysOrMag)
			damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
		else
			damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
		HurtCharacter(scaleATK, pEffect, pCharacter);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCoverCharacterAverageAtk(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	if (pCharacter->m_Hp > 0)
	{
		/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
		int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
		int32 scaleATK = 0;
		if (pEffect->m_isPhysOrMag)
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
		else
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition;
		/*int32 damage = 0;
		if (!pEffect->m_isPhysOrMag)
			damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
		else
			damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
		HurtCharacter(scaleATK, pEffect, pCharacter);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByCoverActorTag(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 scaleAtk = 0;
	if (pEffect->m_effectValues[1] >= pEffect->m_effectValues[0])
		scaleAtk = (pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition)*(100 + pEffect->m_effectValues[2]) / 100;
	else
		scaleAtk = (pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition)*(100 + pEffect->m_effectValues[3]) / 100;
	HurtCharacter(scaleAtk, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtBySpecificGradeNumber(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter) return;
	if (pCharacter->m_Hp <= 0) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pCharacter);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode) return;
	int32 gradeNb = 0;
	bool isActivated = false;
	for (int32 i = 0; i < pBattleLevelGameMode->m_pAllCharacters.Num(); i++)
	{
		if (pBattleLevelGameMode->m_pAllCharacters[i]->m_grade != pEffect->m_effectValues[0]) continue;
		gradeNb += 1;
	}

	int32 scaleATK = (pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition) * (100 + pEffect->m_effectValues[1] * gradeNb)/100;

	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtAmplifiedByDifSameFlag(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	if (pCharacter->m_Hp > 0)
	{
		/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
		int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
		int32 scaleATK = 0;
		if (pEffect->m_isPhysOrMag)
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
		else
			scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition;
		/*int32 damage = 0;
		if (!pEffect->m_isPhysOrMag)
			damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
		else
			damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
		//DemonstrateActivateEffect(pEffect, pCharacter);
		HurtCharacter(scaleATK, pEffect, pCharacter);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ContinuousHurt(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtAmplifiedIfFoundationType(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter) return;
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	if (pEffect->m_isPhysOrMag)
		scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	else
		scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_magATK + pEffect->m_pHost->m_ATKAddition;
	if (pCharacter->m_characterType == 2)
		scaleATK = scaleATK * (100 + pEffect->m_effectValues[1]) / 100;
	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);
	if (pCharacter->m_characterType == 2)
		damage = damage * (100 + pEffect->m_effectValues[1]) / 100;*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
	
}

void UEffectFunLib::ExtractCompanyLifeToAttack(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	for (int32 i=0; i<pEffect->m_pSubHost.Num(); i++)
	{
		HurtCharacter(pEffect->m_effectValues[1], pEffect, pEffect->m_pSubHost[i]);
		PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
	}
	pCharacter->m_ATKAddition += pEffect->m_pSubHost.Num() * pEffect->m_effectValues[1];
	pEffect->m_modifiedValues.Add(pEffect->m_pSubHost.Num() * pEffect->m_effectValues[1]);
}

void UEffectFunLib::ExtractCompanyLifeToAttack_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::HurtByDefence(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	int32 scaleATK = 0;
	scaleATK = pEffect->m_pHost->m_DFC * pEffect->m_effectValues[0] / 100;

	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::AmplifyOrExemptHurtByOddOrEven(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pCharacter) return hurtVal;
	if (pEffect->m_effectValues[0] == 1)
	{
		//说明此时为单数，豁免伤害
		pEffect->m_effectValues[0] = 0;
		DemonstrateActivateEffect(pEffect, pCharacter);
		return 0;
	}
	else
	{
		//说明此时为双数，伤害加倍
		pEffect->m_effectValues[0] = 1;
		DemonstrateActivateEffect(pEffect, pCharacter);
		return pEffect->m_effectValues[1] * hurtVal;
	}
	return hurtVal;
}

void UEffectFunLib::AmplifyOrExemptHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);
	if (pCharacter->m_Hp <= 0 || !judgeResult) return;

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	scaleATK += scaleATK * pEffect->m_effectValues[1] / 100;

	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByLeftHp(UEffect* pEffect, ABaseCharacter* pCharacter, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pCharacter || pCharacter->m_Hp <= 0) return;
	int32 leftHpPercent = pCharacter->m_Hp * 100 / pCharacter->m_originHp;
	int32 amplifiedCoe = 100;
	for (int32 i=0; i<pEffect->m_effectOnIntervalList.Num(); i++)
	{
		if (leftHpPercent > pEffect->m_effectOnIntervalList[i]) continue;
		amplifiedCoe = pEffect->m_effectValues[i + 1];
		break;
	}
	
	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = (pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition + pEffect->m_effectValues[0]) * amplifiedCoe / 100;

	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::HurtAmplifyByAttackTimes(UEffect* pEffect, UEffect* pHurtEffect, int32 hurtVal, ABaseCharacter* pTarget)
{
	if (!pEffect || !pHurtEffect) return hurtVal;
	if (pEffect->m_effectValues[0] == 0)
	{
		//说明此时为第一次魔法攻击
		pEffect->m_effectValues[0] += 1;
		DemonstrateActivateEffect(pEffect, pTarget);
		return pEffect->m_effectValues[1] * hurtVal;
	}
	else if (pEffect->m_effectValues[0] == 1)
	{
		//说明此时为第一次魔法攻击
		pEffect->m_effectValues[0] += 1;
		DemonstrateActivateEffect(pEffect, pTarget);
		return pEffect->m_effectValues[2] * hurtVal;
	}
	else
	{
		//说明此时为双数，伤害加倍
		pEffect->m_effectValues[0] += 1;
		pEffect->m_isPermenant = false;
		pEffect->m_curTickTime = pEffect->m_duration;
		DemonstrateActivateEffect(pEffect, pTarget);
		return pEffect->m_effectValues[3] * hurtVal;
	}
	return hurtVal;
}

void UEffectFunLib::HurtQuattuorByJudge(UEffect* pEffect, ABaseCharacter* pCharacter, int32 damageCoeK1, int32 damageCoeK2)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);
	if (pCharacter->m_Hp <= 0) return;

	/*int32 scalePhysDFC = pCharacter->m_DFC*pCharacter->m_DFCPercent / 100;
	int32 scaleMagDFC = pCharacter->m_magDFC*pCharacter->m_magDFCPercent / 100;*/
	int32 scaleATK = 0;
	scaleATK = pEffect->m_effectValues[0] + pEffect->m_pHost->m_ATK + pEffect->m_pHost->m_ATKAddition;
	if (outNb == 1 || outNb == 13)
		scaleATK *= 2;
	if (outColor == 2)
		scaleATK *= 2;

	/*int32 damage = 0;
	if (!pEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	//DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Poison(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	DemonstrateActivateEffect(pEffect, pCharacter);
	HurtCharacterPiercing(pEffect->m_effectValues[0], pEffect, pCharacter);
}

void UEffectFunLib::HurtByJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	bool isOn = OneTimeJudgeListEffect(pEffect, pCharacter);
	if (!isOn) return;
	Hurt(pEffect, pCharacter, 0, 0);
}

void UEffectFunLib::HurtByLostHpAndJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost) return;
	bool isOn = OneTimeJudgeListEffect(pEffect, pCharacter);
	if (!isOn) return;
	int32 lostHp = pEffect->m_pHost->m_originHp - pEffect->m_pHost->m_Hp;
	int32 damage = lostHp * pEffect->m_effectValues[0] / 100;
	HurtCharacter(damage, pEffect, pCharacter);
	PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
}

void UEffectFunLib::HurtPiercing(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	HurtCharacterPiercing(pEffect->m_effectValues[0], pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByDeleteJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 scaleATK = pCharacter->m_allJudgeCardInfos.Num() * pEffect->m_effectValues[0];
	pCharacter->UpdateJudgeCardList(-1);
	HurtCharacter(scaleATK, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AddSpecificJudgeCard(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (int32 i=0; i<pEffect->m_effectValues.Num(); i++)
	{
		pCharacter->UpdateJudgeCardList(pEffect->m_effectValues[i]);
	}
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	/*if (pBattlePC->m_pCharacterStatusMenu)
		pBattlePC->m_pCharacterStatusMenu->UpdateJudgeInfoList();*/
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtAndRecoverByEquipmentName(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost || pCharacter->m_characterType != 1) return;
	FString equipName = pEffect->m_effectName.RightChop(16);
	int32 equipNb = 0;
	for (int32 i=0; i<pCharacter->m_pEquipmentInfos.Num(); i++)
	{
		if (!pCharacter->m_pEquipmentInfos[i] || !pCharacter->m_pEquipmentInfos[i]->m_equipmentName.Contains(equipName)) continue;
		equipNb += 1;
	}
	int32 scaleATK = pEffect->m_effectValues[0] * equipNb;
	HurtCharacter(scaleATK, pEffect, pCharacter);
	int32 recover = pEffect->m_effectName[1] * equipNb;
	RecoverCharacter(recover, pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::HurtByEffectDelete(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost) return;
	HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	DemonstrateActivateEffect(pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Recover(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	RecoverCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RecoverByAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	if (pCharacter->m_Hp >= pCharacter->m_originHp) return;
	FString appendString = pEffect->m_effectName.RightChop(15);
	bool containAppendString = false;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pEffect->m_effectName == pCharacter->m_pEffects[i]->m_effectName) continue;
		if (pCharacter->m_pEffects[i]->m_effectName.Contains(appendString) && pCharacter->m_pEffects[i]->m_effectName != pEffect->m_effectName)
		{
			containAppendString = true;
			DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
			break;
		}
	}
	
	RecoverCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RecoverByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_Hp >= pCharacter->m_originHp) return;
	int32 hostHp = pEffect->m_pHost->m_Hp + pEffect->m_effectValues[0];
	if (hostHp >= pEffect->m_pHost->m_originHp)
		pEffect->m_pHost->m_Hp = pEffect->m_pHost->m_originHp;
	else
		pEffect->m_pHost->m_Hp = hostHp;
	if (pEffect->m_pHost->m_pCharacterInfoWidget)
		pEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pEffect->m_pHost->m_Hp, pEffect->m_pHost->m_DFC);
	pEffect->m_pHost->EffectOnFx(false);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RecoverByJudgeSource(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	RecoverCharacter(pEffect->m_effectValues[0], pEffect, pEffect->m_pHost);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RecoverByJudgeList(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	bool isOn = OneTimeJudgeListEffect(pEffect, pCharacter);
	if (!isOn) return;
	RecoverCharacter(pEffect->m_effectValues[0], pEffect, pEffect->m_pHost);
	PlayHitParticleSystem(pEffect, pCharacter);
}

/*
void UEffectFunLib::DefSubOrDestroyCardByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType != 1 || !pCharacter->m_pBaseEquipment) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (judgeResult && (pCharacter->m_pBaseEquipment->m_pSkills.Num() - 1) > 0)
	{
		AKing* pPlayerCharacter = Cast<AKing>(pCharacter);
		int32 randNb = FMath::RandRange(1, pPlayerCharacter->m_pBaseEquipment->m_pSkills.Num() - 1);
		pPlayerCharacter->SwitchSkill(randNb - 1);
	}
	else
	{
		/ *int32 originDFCPercent = pCharacter->m_DFCPercent;
		int32 defSubPercent = pEffect->m_effectValues[0];
		if (pCharacter->m_DFCPercent - defSubPercent <= 10) pCharacter->m_DFCPercent = 10;
		else pCharacter->m_DFCPercent -= defSubPercent;
		pEffect->m_modifiedValues.Add(originDFCPercent - pCharacter->m_DFCPercent);* /
		if (pEffect->m_isPhysOrMag)
		{
			pCharacter->m_DFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
		}
		else
		{
			pCharacter->m_magDFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
		}
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pEffect->m_pHost);
}*/

void UEffectFunLib::RecoverIfTargetAtkCardMoreThanNoneAtkCard(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost || !pCharacter->m_pBaseEquipment) return;
	uint8 atkCardNb = 0;
	uint8 noneAtkCardNb = 0;
	for (uint8 i = 1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) atkCardNb += 1;
		else noneAtkCardNb += 1;
	}
	if (atkCardNb >= noneAtkCardNb)
	{
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		RecoverCharacter(pEffect->m_effectValues[0], pEffect, pEffect->m_pHost);
	}
	PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
}

void UEffectFunLib::RecoverOrContinuousHurtByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (judgeResult)
	{
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		RecoverCharacter(pEffect->m_effectValues[0], pEffect, pEffect->m_pHost);
	}
	else
	{
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName("ContinuousHurt");
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pNewEffect->m_canOverlap = true;
		pNewEffect->m_duration = pEffect->m_duration;
		pNewEffect->m_effectName = "ContinuousHurt";
		pNewEffect->m_effectValues.Add(pEffect->m_effectValues[1]);
		pNewEffect->m_functionNames.Add("ContinuousHurt");
		pNewEffect->m_isPhysOrMag = true;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		pNewEffect->m_effectDefaultParam.duration = pNewEffect->m_duration;
		pNewEffect->m_effectDefaultParam.effectName = pNewEffect->m_effectName;
		pNewEffect->m_effectDefaultParam.functionNames = pNewEffect->m_functionNames;
		pNewEffect->m_effectDefaultParam.effectValues = pNewEffect->m_effectValues;
		pNewEffect->m_effectDefaultParam.isPhysOrMag = pNewEffect->m_isPhysOrMag;
		pCharacter->m_pEffects.Add(pNewEffect);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pEffect, true);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
		DemonstrateActivateEffect(pEffect, pCharacter);
	}
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::JudgeToRecover(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (!judgeResult) return;
	RecoverCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RecoverByItemCard(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType != 1 || !pEffect->m_pHost) return;
	FString itemName = pEffect->m_effectName.RightChop(17);
	AKing* pKing = Cast<AKing>(pCharacter);
	int32 cardNb = 0;
	for (TMap<FString, int32>::TConstIterator iter = pKing->m_allItemCardMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Key.Contains(itemName)) continue;
		cardNb += iter->Value;
	}
	RecoverCharacter(pEffect->m_effectValues[0]*cardNb, pEffect, pEffect->m_pHost);
	PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
}

void UEffectFunLib::ClearResistByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (!judgeResult) return;
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || !pCharacter->m_pEffects[i]->m_effectName.Contains("Resist")) continue;
		pCharacter->m_pEffects[i]->m_curTickTime = pCharacter->m_pEffects[i]->m_duration;
		pCharacter->m_pEffects[i]->m_isPermenant = false;
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ClearAllAppendEffects(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		pCharacter->m_pEffects[i]->m_curTickTime = pCharacter->m_pEffects[i]->m_duration;
		pCharacter->m_pEffects[i]->m_isPermenant = false;
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ClearAllAppendEffectsByJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (!judgeResult) return;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		pCharacter->m_pEffects[i]->m_curTickTime = pCharacter->m_pEffects[i]->m_duration;
		pCharacter->m_pEffects[i]->m_isPermenant = false;
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::Invincible(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pHurtEffect || !pCharacter) return hurtVal;
	pHurtEffect->m_isOnByEmbeddedEffect = false;
	DemonstrateActivateEffect(pEffect, pCharacter);
	return 0;
}

int32 UEffectFunLib::HurtToRecover(UEffect* pEffect, ABaseCharacter* pHurtTarget, int32 hurtVal)
{
	if (!pEffect || !pHurtTarget) return 0;
	int32 leftHp = pHurtTarget->m_Hp + hurtVal;
	if (leftHp >= pHurtTarget->m_originHp)
		pHurtTarget->m_Hp = pHurtTarget->m_originHp;
	else
		pHurtTarget->m_Hp = leftHp;
	if (pHurtTarget->m_pCharacterInfoWidget)
		pHurtTarget->m_pCharacterInfoWidget->NotifyHpChange(pHurtTarget->m_Hp, pHurtTarget->m_DFC);
	DemonstrateActivateEffect(pEffect, pHurtTarget);
	pHurtTarget->EffectOnFx(false);
	//PlayHitBeamParticle(pHurtTarget, pEffect->m_pHost, pEffect);
	//PlayHitParticleSystem(pEffect, pHurtTarget);
	return 0;
}

int32 UEffectFunLib::ResistHurt(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget, int32 hurtVal)
{
	if (!pHurtTarget) return 0;
	if (!pEffect || !pHurtEffect->m_pOriginGeo) return hurtVal;
	int32 modifyHurt = hurtVal;
	if (pEffect->m_effectType == "AttributeReactionEffect")
	{
		//说明这是一次性的效果，如果是AttributeReactionEffect的话，就要判断增益effect和攻击effect是否同一geo，是的话才能放大
		if (pEffect->m_pOriginGeo && pEffect->m_pOriginGeo == pHurtEffect->m_pOriginGeo)
		{
			modifyHurt = hurtVal - hurtVal * pEffect->m_effectValues[0] / 100;
			pEffect->m_isOnTimeEffectDone = true;
		}
	}
	else
	{
		modifyHurt = hurtVal - hurtVal * pEffect->m_effectValues[0] / 100;
	}
	DemonstrateActivateEffect(pEffect, pHurtTarget);
	if (modifyHurt <= 0) return 0;
	//PlayHitParticleSystem(pEffect, pHurtTarget);
	return modifyHurt;
}

void UEffectFunLib::CopyJudgeActivateTargetEffect(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost == pCharacter) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pEffect->m_pHost->m_pEffects.Num(); i++)
	{
		if (!pEffect->m_pHost->m_pEffects[i] || pEffect->m_pHost->m_pEffects[i]->m_effectType != "JudgeActivatedTarget") continue;
		bool isEffectExist = false;
		for (int32 j=0; j<pCharacter->m_pEffects.Num(); j++)
		{
			if (pCharacter->m_pEffects[j]->m_effectName == pEffect->m_pHost->m_pEffects[i]->m_effectName)
			{
				isEffectExist = true;
				break;
			}
		}
		if (isEffectExist) continue;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_pHost->m_pEffects[i]->m_effectName);
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pEffect->m_pHost->m_pEffects[i]->Copy(pNewEffect);
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		pCharacter->m_pEffects.Add(pNewEffect);
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter) 
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::CopyPlayerAppendEffect(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pEffect);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPlayerCharacter) return;
	ABaseCharacter* pPlayerCharacter = pBattleLevelGameMode->m_pPlayerCharacter;
	for (int32 i = 0; i < pPlayerCharacter->m_pEffects.Num(); i++)
	{
		if (!pPlayerCharacter->m_pEffects[i] || pPlayerCharacter->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		bool isEffectExist = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (pCharacter->m_pEffects[j]->m_effectName == pPlayerCharacter->m_pEffects[i]->m_effectName)
			{
				isEffectExist = true;
				break;
			}
		}
		if (isEffectExist) continue;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pPlayerCharacter->m_pEffects[i]->m_effectName);
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pPlayerCharacter->m_pEffects[i]->Copy(pNewEffect);
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pPlayerCharacter;
		pCharacter->m_pEffects.Add(pNewEffect);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::FireWoodSwitch(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TArray<UEffect*> pNewEffects;
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || (pCharacter->m_pEffects[i]->m_effectName != "FireResist" && pCharacter->m_pEffects[i]->m_effectName != "HurtAmplifiedByFire" &&
			pCharacter->m_pEffects[i]->m_effectName != "WoodResist" && pCharacter->m_pEffects[i]->m_effectName != "HurtAmplifiedByWood"))
			continue;
		TSubclassOf<class UObject> effectClass = NULL;
		FString effectName;
		FString functionName;
		FString preCondition;
		if (pCharacter->m_pEffects[i]->m_effectName == "FireResist")
		{
			effectClass = pSingleton->FindEffectClassByName(TEXT("WoodResist"));
			effectName = "WoodResist";
			functionName = "ResistHurt";
			preCondition = "SuperposeWoodAtk";
		}
		else if (pCharacter->m_pEffects[i]->m_effectName == "HurtAmplifiedByFire")
		{
			effectClass = pSingleton->FindEffectClassByName(TEXT("HurtAmplifiedByAttribute"));
			effectName = "HurtAmplifiedByWood";
			functionName = "HurtAmplifiedByAttribute";
			preCondition = "SuperposeWoodAtk";
		}
		else if (pCharacter->m_pEffects[i]->m_effectName == "WoodResist")
		{
			effectClass = pSingleton->FindEffectClassByName(TEXT("FireResist"));
			effectName = "FireResist";
			functionName = "ResistHurt";
			preCondition = "SuperposeFireAtk";
		}
		else if (pCharacter->m_pEffects[i]->m_effectName == "HurtAmplifiedByWood")
		{
			effectClass = pSingleton->FindEffectClassByName(TEXT("HurtAmplifiedByAttribute"));
			effectName = "HurtAmplifiedByFire";
			functionName = "HurtAmplifiedByAttribute";
			preCondition = "SuperposeFireAtk";
		}
		if (!effectClass) continue;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pCharacter->m_pEffects[i]->Copy(pNewEffect);
		pNewEffect->m_effectDefaultParam.effectName = effectName;
		FEffectNameGroup nameGroup;
		nameGroup.effectNameList.Add(preCondition);
		pNewEffect->m_preconditionEffects.Add(nameGroup);
		pNewEffect->m_effectDefaultParam.functionNames.Add(functionName);
		pNewEffect->m_effectName = effectName;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		pCharacter->m_pEffects[i]->m_curTickTime = pCharacter->m_pEffects[i]->m_duration;
		pCharacter->m_pEffects[i]->m_isPermenant = false;
		pNewEffects.Add(pNewEffect);
	}
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pNewEffects.Num(); i++)
	{
		pCharacter->m_pEffects.Add(pNewEffects[i]);
		AddStateToCharacter(pCharacter, pNewEffects[i]->m_effectName);
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter) 
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffects[i], true);
	}
	DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

int32 UEffectFunLib::RecoverToHurt(UEffect* pEffect, ABaseCharacter* pCharacter, int32 recoverVal)
{
	if (!pEffect || !pCharacter) return recoverVal;
	/*int32 originHp = pCharacter->m_Hp;
	int32 leftHp = pCharacter->m_Hp - recoverVal;
	if (leftHp <= 0)
		pCharacter->m_Hp = 0;
	else
		pCharacter->m_Hp = leftHp;*/
	int32 trueHurtVal = 0;
	if (pEffect->m_isPhysOrMag)
	{
		if (pCharacter->m_DFC > 0)
		{
			if (pCharacter->m_DFC > recoverVal)
			{
				pCharacter->m_DFC -= recoverVal;
				trueHurtVal = recoverVal;
			}
			else
			{
				trueHurtVal += pCharacter->m_DFC;
				int32 damage = recoverVal - pCharacter->m_DFC;
				pCharacter->m_DFC = 0;
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - damage;
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal += originHp - pCharacter->m_Hp;
			}
		}
		else
		{
			int32 originHp = pCharacter->m_Hp;
			int32 leftHp = pCharacter->m_Hp - recoverVal;
			if (leftHp <= 0)
				pCharacter->m_Hp = 0;
			else
				pCharacter->m_Hp = leftHp;
			trueHurtVal = originHp - pCharacter->m_Hp;
		}
	}
	else
	{
		if (pCharacter->m_magDFC > 0)
		{
			if (pCharacter->m_magDFC > recoverVal)
			{
				pCharacter->m_magDFC -= recoverVal;
				trueHurtVal = recoverVal;
			}
			else
			{
				trueHurtVal += pCharacter->m_magDFC;
				int32 damage = recoverVal - pCharacter->m_magDFC;
				pCharacter->m_magDFC = 0;
				int32 originHp = pCharacter->m_Hp;
				int32 leftHp = pCharacter->m_Hp - damage;
				if (leftHp <= 0)
					pCharacter->m_Hp = 0;
				else
					pCharacter->m_Hp = leftHp;
				trueHurtVal += originHp - pCharacter->m_Hp;
			}
		}
		else
		{
			int32 originHp = pCharacter->m_Hp;
			int32 leftHp = pCharacter->m_Hp - recoverVal;
			if (leftHp <= 0)
				pCharacter->m_Hp = 0;
			else
				pCharacter->m_Hp = leftHp;
			trueHurtVal = originHp - pCharacter->m_Hp;
		}
	}
	DemonstrateHurtNb(trueHurtVal, pCharacter);
	DemonstrateActivateEffect(pEffect, pCharacter);
	if (pCharacter->m_pCharacterInfoWidget)
		pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	pCharacter->EffectOnFx(true);
	//PlayHitBeamParticle(pHurtTarget, pEffect->m_pHost, pEffect);
	//PlayHitParticleSystem(pEffect, pCharacter);
	return 0;
}

void UEffectFunLib::IntoTheWind(UEffect* pEffect, UEffect* pHurtEffect, const int32& damageCoeK1, const int32& damageCoeK2)
{
	if (!pEffect || !pEffect->m_pHost || !pHurtEffect || !pHurtEffect->m_pHost) return;
	/*int32 scalePhysDFC = pEffect->m_pHost->m_DFC*pEffect->m_pHost->m_DFCPercent / 100;
	int32 scaleMagDFC = pEffect->m_pHost->m_magDFC*pEffect->m_pHost->m_magDFCPercent / 100;*/
	int32 scaleATK = pHurtEffect->m_effectValues[0] + pHurtEffect->m_pHost->m_ATKAddition;
	/*int32 damage = 0;
	if (!pHurtEffect->m_isPhysOrMag)
		damage = ((scaleMagDFC + damageCoeK2)*scaleATK - damageCoeK1 * scaleMagDFC*scaleATK) / (damageCoeK2 + scaleMagDFC);
	else
		damage = ((scalePhysDFC + damageCoeK2)*scaleATK - damageCoeK1 * scalePhysDFC*scaleATK) / (damageCoeK2 + scalePhysDFC);*/
	if (scaleATK < pEffect->m_effectValues[0]) return;
	for (int32 i=0; i<pHurtEffect->m_pHost->m_pEffects.Num(); i++)
	{
		if (!pHurtEffect->m_pHost->m_pEffects[i] || pHurtEffect->m_pHost->m_pEffects[i]->m_effectType == TEXT("OneTimeEffect")) continue;
		pHurtEffect->m_pHost->m_pEffects[i]->m_isPermenant = false;
		pHurtEffect->m_pHost->m_pEffects[i]->m_curTickTime = pHurtEffect->m_pHost->m_pEffects[i]->m_duration;
	}
	DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
	//PlayHitParticleSystem(pEffect, pHurtEffect->m_pHost);
}

void UEffectFunLib::RestrictJudgeColor(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (int32 i=0; i<pEffect->m_effectValues.Num(); i++)
	{
		if (pCharacter->m_judgeInfo.availableJudgeColors.Contains(pEffect->m_effectValues[i]))
		{
			pCharacter->m_judgeInfo.availableJudgeColors.Remove(pEffect->m_effectValues[i]);
			pEffect->m_modifiedValues.Add(pEffect->m_effectValues[i]);
		}
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RestrictJudgeColor_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (uint8 i = 0; i < pEffect->m_modifiedValues.Num(); i++)
	{
		if (!pCharacter->m_judgeInfo.availableJudgeColors.Contains(pEffect->m_modifiedValues[i]))
		{
			pCharacter->m_judgeInfo.availableJudgeColors.Add(pEffect->m_modifiedValues[i]);
		}
	}
}

void UEffectFunLib::RestrictJudgeNumber(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (int32 i = 0; i < pEffect->m_effectValues.Num(); i++)
	{
		if (pCharacter->m_judgeInfo.availableJudgeNbs.Contains(pEffect->m_effectValues[i]))
		{
			pCharacter->m_judgeInfo.availableJudgeNbs.Remove(pEffect->m_effectValues[i]);
			pEffect->m_modifiedValues.Add(pEffect->m_effectValues[i]);
		}
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::RestrictJudgeNumber_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (uint8 i=0; i<pEffect->m_modifiedValues.Num(); i++)
	{
		if (!pCharacter->m_judgeInfo.availableJudgeNbs.Contains(pEffect->m_modifiedValues[i]))
		{
			pCharacter->m_judgeInfo.availableJudgeNbs.Add(pEffect->m_modifiedValues[i]);
		}
	}
}

void UEffectFunLib::FreezeByJudgeActivate(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 originSpeedRate = pCharacter->m_speedRatePercent;
	pCharacter->m_speedRatePercent = 0;
	if (pCharacter->m_pBaseAnimInstance) pCharacter->m_pBaseAnimInstance->ChangeSpeedRate(pCharacter->m_speedRatePercent);
	int32 modifyVal = originSpeedRate - pCharacter->m_speedRatePercent;
	pEffect->m_modifiedValues.Add(modifyVal);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::FreezeByJudgeActivate_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_speedRatePercent += pEffect->m_modifiedValues[0];
	if (pCharacter->m_pBaseAnimInstance) pCharacter->m_pBaseAnimInstance->ChangeSpeedRate(pCharacter->m_speedRatePercent);
}

void UEffectFunLib::AttackDecreaseByAttribute(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	FString appendString = pEffect->m_effectName.RightChop(16);
	int32 appendStringNb = 0;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectName == pEffect->m_effectName) continue;
		if (pCharacter->m_pEffects[i]->m_effectName.Contains(appendString))
		{
			appendStringNb += 1;
			DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
		}
	}
	int32 originATKAddition = pCharacter->m_ATKAddition;
	int32 atkSub = pEffect->m_effectValues[0] * appendStringNb;
	int32 lessAtk = 0;
	if (pCharacter->m_ATK < pCharacter->m_magATK) lessAtk = pCharacter->m_ATK;
	else lessAtk = pCharacter->m_magATK;
	int32 atkAppendSub = pCharacter->m_ATKAddition - atkSub;
	if (lessAtk + atkAppendSub < 0) atkSub = lessAtk + pCharacter->m_ATKAddition;
	pCharacter->m_ATKAddition -= atkSub;
	pEffect->m_modifiedValues.Add(originATKAddition - pCharacter->m_ATKAddition);
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AttackDecreaseByAttribute_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::AtkSubByNoneAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment) return;
	int32 noneAtkCardNb = 0;
	for (uint8 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) continue;
		noneAtkCardNb += 1;
	}
	int32 originATKAddition = pCharacter->m_ATKAddition;
	int32 atkSub = pEffect->m_effectValues[0] * noneAtkCardNb;
	int32 lessAtk = 0;
	if (pCharacter->m_ATK < pCharacter->m_magATK) lessAtk = pCharacter->m_ATK;
	else lessAtk = pCharacter->m_magATK;
	int32 atkAppendSub = pCharacter->m_ATKAddition - atkSub;
	if (lessAtk + atkAppendSub < 0) atkSub = lessAtk + pCharacter->m_ATKAddition;
	pCharacter->m_ATKAddition -= atkSub;
	pEffect->m_modifiedValues.Add(originATKAddition - pCharacter->m_ATKAddition);
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AtkSubByNoneAtkCardNb_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefenceDecreaseByAttribute(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	FString appendString = pEffect->m_effectName.RightChop(17);
	int32 appendStringNb = 0;
	for (int32 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pEffect->m_effectName == pCharacter->m_pEffects[i]->m_effectName) continue;
		if (pCharacter->m_pEffects[i]->m_effectName.Contains(appendString))
		{
			appendStringNb += 1;
			DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
		}
	}
	//int32 originDFCPercent = pCharacter->m_DFCPercent;
	int32 defSub = pEffect->m_effectValues[0] * appendStringNb;
	pCharacter->m_DFC -= defSub;
	if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
	//PlayHitParticleSystem(pEffect, pCharacter);
	if (pCharacter->m_pCharacterInfoWidget)
		pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	if (defSub > 0) pCharacter->EffectOnFx(true);
}

void UEffectFunLib::DefenceDecreaseByAttribute_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::AtkSubByDef(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;

	int32 originATKAddition = pCharacter->m_ATKAddition;
	if (pCharacter->m_DFC >= pEffect->m_effectValues[1])
	{
		int32 atkSub = pEffect->m_effectValues[0];
		int32 lessAtk = 0;
		if (pCharacter->m_ATK < pCharacter->m_magATK) lessAtk = pCharacter->m_ATK;
		else lessAtk = pCharacter->m_magATK;
		int32 atkAppendSub = pCharacter->m_ATKAddition - atkSub;
		if (lessAtk + atkAppendSub < 0) atkSub = lessAtk + pCharacter->m_ATKAddition;
		pCharacter->m_ATKAddition -= atkSub;
		pEffect->m_modifiedValues.Add(originATKAddition - pCharacter->m_ATKAddition);
		//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	}
	else pEffect->m_modifiedValues.Add(0);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AtkSubByDef_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefSubByCardAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pEffect->m_pHost->m_campFlag == pCharacter->m_campFlag || !pCharacter->m_pBaseEquipment) return;

	int32 appendStringNb = 0;
	for (int32 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i]) continue;
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Water") ||
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Blood") ||
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillName.Contains("Poison"))
		{
			appendStringNb += 1;
		}
	}
	//int32 originDFCPercent = pCharacter->m_DFCPercent;
	int32 defSub = pEffect->m_effectValues[0] * appendStringNb;
	if (pEffect->m_isPhysOrMag)
	{
		pCharacter->m_DFC -= defSub;
		if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
	}
	else
	{
		pCharacter->m_magDFC -= defSub;
		if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	/*if (pCharacter->m_DFCPercent - defSubPercent <= 10) pCharacter->m_DFCPercent = 10;
	else pCharacter->m_DFCPercent -= defSubPercent;
	pEffect->m_modifiedValues.Add(originDFCPercent - pCharacter->m_DFCPercent);*/
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DefSubByAtkCardNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment || pCharacter->m_characterType == 0) return;
	int32 atkCardNb = 0;
	for (int32 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || !pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) continue;
		atkCardNb += 1;
	}
	int32 defSub = pEffect->m_effectValues[0] * atkCardNb;
	//int32 originDFCPercent = pCharacter->m_DFCPercent;
	if (pEffect->m_isPhysOrMag)
	{
		pCharacter->m_DFC -= defSub;
		if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
	}
	else
	{
		pCharacter->m_magDFC -= defSub;
		if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	/*if (pCharacter->m_DFCPercent - defSubPercent <= 10) pCharacter->m_DFCPercent = 10;
	else pCharacter->m_DFCPercent -= defSubPercent;
	pEffect->m_modifiedValues.Add(originDFCPercent - pCharacter->m_DFCPercent);*/
	////PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DefSubByAtkCardNb_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefenceDecreaseByHpPercent(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 hpPercent = pCharacter->m_Hp * 100 / pCharacter->m_originHp;
	if (hpPercent >= pEffect->m_effectValues[1])
	{
		pCharacter->m_DFC -= pEffect->m_effectValues[0];
		if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
		//DemonstrateActivateEffect(pEffect, pCharacter);

		/*if (pCharacter->m_DFCPercent - pEffect->m_effectValues[0] <= 10) pCharacter->m_DFCPercent = 10;
		else pCharacter->m_DFCPercent -= pEffect->m_effectValues[0];
		pEffect->m_modifiedValues.Add(originDFCPercent - pCharacter->m_DFCPercent);*/
	}
	//else pEffect->m_modifiedValues.Add(0);
	////PlayHitParticleSystem(pEffect, pCharacter);
	if (pCharacter->m_pCharacterInfoWidget)
		pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	pCharacter->EffectOnFx(true);
}

void UEffectFunLib::DefenceDecreaseByHpPercent_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefSubByCharacterNb(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pEffect);
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	int32 characterNb = 0;
	for (int32 i=0; i<pBattleLevelGameMode->m_pAllCharacters.Num(); i++)
	{
		if (pBattleLevelGameMode->m_pAllCharacters[i]->m_grade != pEffect->m_effectValues[1]) continue;
		characterNb += 1;
	}
	if (characterNb >= pEffect->m_effectValues[2])
	{
		if (pEffect->m_isPhysOrMag)
		{
			pCharacter->m_DFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
		}
		else
		{
			pCharacter->m_magDFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
		}
		//DemonstrateActivateEffect(pEffect, pCharacter);
	}
	//else pEffect->m_modifiedValues.Add(0);
	////PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DefSubByCharacterNb_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefenceDecreaseByCD(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment) return;
	uint8 canImplementSkillNb = 0;
	for (uint8 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || !pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		canImplementSkillNb += 1;
	}
	if (canImplementSkillNb >= pEffect->m_effectValues[1])
	{
		if (pEffect->m_isPhysOrMag)
		{
			pCharacter->m_DFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
		}
		else
		{
			pCharacter->m_magDFC -= pEffect->m_effectValues[0];
			if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
		}
		//DemonstrateActivateEffect(pEffect, pCharacter);
	}
	//else pEffect->m_modifiedValues.Add(0);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DefenceDecreaseByCD_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_modifiedValues.Num() == 0) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::IncreaseCDByCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType == 0 || !pCharacter->m_pBaseEquipment) return;
	int32 increaseCD = pEffect->m_effectValues[0] * pEffect->m_effectValues[1] / 100;
	for (int32 i=1; i<pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i]) continue;
		pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = false;
		int32 skillFrameCount = pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount - increaseCD;
		if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount <= 0) pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
		else pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = skillFrameCount;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::IncreaseCDByCharacterHp(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType == 0 || !pCharacter->m_pBaseEquipment) return;
	int32 hpPercent = pCharacter->m_Hp * 100 / pCharacter->m_originHp;
	if (hpPercent >= pEffect->m_effectValues[1])
	{
		for (int32 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || !pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = false;
			int32 skillFrameCount = pCharacter->m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime - pEffect->m_effectValues[0];
			if (skillFrameCount <= 0) pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
			else pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = skillFrameCount;
		}
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::IncreaseCDByCoverCharacterAppendString(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType == 0 || !pCharacter->m_pBaseEquipment) return;
	for (int32 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || !pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = false;
		int32 skillFrameCount = pCharacter->m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime - pEffect->m_effectValues[0];
		if (skillFrameCount <= 0) pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
		else pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = skillFrameCount;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::SubCD(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType != 1 || !pCharacter->m_pBaseEquipment) return;
	for (int32 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i] || pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		int32 skillFrameCount = pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount + pEffect->m_effectValues[0];
		if (skillFrameCount >= pCharacter->m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime)
			pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = pCharacter->m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime;
		else pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = skillFrameCount;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::SwitchHpPercentByOrder(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	/*if (pCharacter->m_characterType == 1)
	{
		int32 originATKPercent = pCharacter->m_ATKAddition;
		if (pCharacter->m_ATKAddition - pEffect->m_effectValues[1] <= 10) pCharacter->m_ATKAddition = 10;
		else pCharacter->m_ATKAddition -= pEffect->m_effectValues[1];
		pEffect->m_modifiedValues.Add(originATKPercent - pCharacter->m_ATKAddition);
	}
	else pEffect->m_modifiedValues.Add(0);*/
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::SwitchHpPercentByOrder_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	//pCharacter->m_ATKAddition += pEffect->m_modifiedValues[0];
}

/*
void UEffectFunLib::LimitAllImplementedCD(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (uint8 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i]) continue;
		bool isOverlap = false;
		for (uint8 j=0; j< pCharacter->m_pBaseEquipment->m_pSkills[i]->m_appendHostEffectParams.Num(); j++)
		{
			if (pCharacter->m_pBaseEquipment->m_pSkills[i]->m_appendHostEffectParams[j].effectName == "LimitAllImplementedCD")
			{
				isOverlap = true;
				break;
			}
		}
		if (isOverlap) continue;
		pCharacter->m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = false;
		pCharacter->m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}*/

void UEffectFunLib::AttackDrop(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_isOnTimeEffectDone) return;
	int32 atkDif = pCharacter->m_ATKAddition + pCharacter->m_ATK;
	pEffect->m_modifiedValues.Add(atkDif);
	pCharacter->m_ATKAddition -= atkDif;
	pEffect->m_isOnTimeEffectDone = true;
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//DemonstrateActivateEffect(pEffect, pCharacter);
}

void UEffectFunLib::AttackDrop_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefenceIncrease(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_isOnTimeEffectDone) return;
	pCharacter->m_DFC += pEffect->m_effectValues[0];
	if (pCharacter->m_DFC >= pCharacter->m_maxDFC) pCharacter->m_DFC = pCharacter->m_maxDFC;
	if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//pEffect->m_modifiedValues.Add(pEffect->m_effectValues[0]);
	//PlayHitParticleSystem(pEffect, pCharacter);
	pEffect->m_isOnTimeEffectDone = true;
}

void UEffectFunLib::DefAdd_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DefSub(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_isOnTimeEffectDone) return;
	/*int32 originDefPercent = pCharacter->m_DFCPercent;
	pCharacter->m_DFCPercent -= pEffect->m_effectValues[0];
	if (pCharacter->m_DFCPercent <= 1) pCharacter->m_DFCPercent = 1;*/
	//pEffect->m_modifiedValues.Add(originDefPercent - pCharacter->m_DFCPercent);
	if (pEffect->m_isPhysOrMag)
	{
		pCharacter->m_DFC -= pEffect->m_effectValues[0];
		if (pCharacter->m_DFC < 0) pCharacter->m_DFC = 0;
	}
	else
	{
		pCharacter->m_magDFC -= pEffect->m_effectValues[0];
		if (pCharacter->m_magDFC < 0) pCharacter->m_magDFC = 0;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	pEffect->m_isOnTimeEffectDone = true;
}

void UEffectFunLib::DefSub_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::AttackIncrease(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 originAtkAddition = pCharacter->m_ATKAddition;

	pCharacter->m_ATKAddition += pEffect->m_effectValues[0];
	if (pCharacter->m_ATKAddition >= pCharacter->m_maxATKAddition) pCharacter->m_ATKAddition = pCharacter->m_maxATKAddition;
	int32 atkAdd = pCharacter->m_ATKAddition - originAtkAddition;
	pEffect->m_modifiedValues.Add(atkAdd);
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
	pEffect->m_isOnTimeEffectDone = true;
}

void UEffectFunLib::AtkAdd_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::AttackDecrease(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pEffect->m_isOnTimeEffectDone) return;
	int32 originAtkAddition = pCharacter->m_ATKAddition;

	int32 atkSub = pEffect->m_effectValues[0];
	int32 atkAppendSub = pCharacter->m_ATKAddition - atkSub;
	if (pCharacter->m_ATK + atkAppendSub < 0) atkSub = pCharacter->m_ATK + pCharacter->m_ATKAddition;
	pCharacter->m_ATKAddition -= atkSub;
	pEffect->m_modifiedValues.Add(originAtkAddition - pCharacter->m_ATKAddition);
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	pEffect->m_isOnTimeEffectDone = true;
}

void UEffectFunLib::AttackDecrease_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::AttributeWeak(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TSubclassOf<class UObject> effectClass = NULL;
	FString attribute = pEffect->m_effectName.LeftChop(4);
	FString effectName;
	bool canSpawn = true;
	if (attribute == "Fire") effectName = "HurtAmplifiedByFire";
	else if (attribute == "Water") effectName = "HurtAmplifiedByWater";
	else if (attribute == "Wood") effectName = "HurtAmplifiedByWood";
	else if (attribute == "Dark") effectName = "HurtAmplifiedByDark";
	else if (attribute == "Freeze") effectName = "HurtAmplifiedByFreeze";
	else if (attribute == "Ground") effectName = "HurtAmplifiedByGround";
	for (uint8 i=0; i<pCharacter->m_pEffects.Num() ; i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectName == effectName)
		{
			canSpawn = false;
			break;
		}
	}
	if (!canSpawn) return;
	effectClass = pSingleton->FindEffectClassByName("HurtAmplifiedByAttribute");
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
	pNewEffect->m_effectName = effectName;
	pNewEffect->m_functionNames.Add("HurtAmplifiedByAttribute");
	pNewEffect->m_effectValues = pEffect->m_effectValues;
	pNewEffect->m_duration = pEffect->m_duration;
	pNewEffect->m_isJudgeEffect = pEffect->m_isJudgeEffect;
	pNewEffect->m_isPhysOrMag = pEffect->m_isPhysOrMag;
	pNewEffect->m_canOverlap = false;
	pNewEffect->m_pOriginGeo = NULL;
	pNewEffect->m_pHost = pEffect->m_pHost;
	pNewEffect->m_effectOnIntervalList = pEffect->m_effectOnIntervalList;
	if (pBattlePC->m_pBattleMenu)
	{
		pNewEffect->m_description = pEffect->m_description;
	}
/*
	pNewEffect->m_effectDefaultParam.effectName = effectName;
	pNewEffect->m_effectDefaultParam.functionNames = TEXT("HurtAmplifiedByAttribute");
	pNewEffect->m_effectDefaultParam.effectValues = pEffect->m_effectValues;
	pNewEffect->m_effectDefaultParam.duration = pEffect->m_duration;
	pNewEffect->m_effectDefaultParam.isJudgeEffect = pEffect->m_isJudgeEffect;*/
	pCharacter->m_pEffects.Add(pNewEffect);
	
	if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter) 
		pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
	//DemonstrateActivateEffect(pEffect, pCharacter);
	AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AttributeWeakByHostHp(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || !pCharacter->m_pBaseEquipment) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TSubclassOf<class UObject> effectClass = NULL;
	FString attribute = pEffect->m_effectName.LeftChop(12);
	FString effectName;
	bool canSpawn = true;
	if (attribute == "Fire") effectName = "HurtAmplifiedByFire";
	else if (attribute == "Water") effectName = "HurtAmplifiedByWater";
	else if (attribute == "Wood") effectName = "HurtAmplifiedByWood";
	else if (attribute == "Dark") effectName = "HurtAmplifiedByDark";
	else if (attribute == "Freeze") effectName = "HurtAmplifiedByFreeze";
	else if (attribute == "Ground") effectName = "HurtAmplifiedByGround";
	for (uint8 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectName == effectName)
		{
			canSpawn = false;
			break;
		}
	}
	if (!canSpawn) return;
	effectClass = pSingleton->FindEffectClassByName("HurtAmplifiedByAttribute");
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	int32 hpPercent = pEffect->m_pHost->m_Hp * 100 / pEffect->m_pHost->m_originHp;
	if (hpPercent <= pEffect->m_effectValues[1])
	{
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pNewEffect->m_effectName = effectName;
		pNewEffect->m_functionNames.Add("HurtAmplifiedByAttribute");
		pNewEffect->m_effectValues = pEffect->m_effectValues;
		pNewEffect->m_duration = pEffect->m_duration;
		pNewEffect->m_isJudgeEffect = pEffect->m_isJudgeEffect;
		pNewEffect->m_isPhysOrMag = pEffect->m_isPhysOrMag;
		pNewEffect->m_canOverlap = false;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		if (pBattlePC->m_pBattleMenu)
		{
			pNewEffect->m_description = pEffect->m_description;
		}
		pCharacter->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter) 
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		//DemonstrateActivateEffect(pEffect, pCharacter);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::AttributeWeakByTargetHp(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || !pCharacter->m_pBaseEquipment) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TSubclassOf<class UObject> effectClass = NULL;
	FString attribute = pEffect->m_effectName.LeftChop(14);
	FString effectName;
	bool canSpawn = true;
	if (attribute == "Fire") effectName = "HurtAmplifiedByFire";
	else if (attribute == "Water") effectName = "HurtAmplifiedByWater";
	else if (attribute == "Wood") effectName = "HurtAmplifiedByWood";
	else if (attribute == "Dark") effectName = "HurtAmplifiedByDark";
	else if (attribute == "Freeze") effectName = "HurtAmplifiedByFreeze";
	else if (attribute == "Ground") effectName = "HurtAmplifiedByGround";
	for (uint8 i = 0; i < pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectName == effectName)
		{
			canSpawn = false;
			break;
		}
	}
	if (!canSpawn) return;
	effectClass = pSingleton->FindEffectClassByName("HurtAmplifiedByAttribute");
	if (!effectClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	int32 hpPercent = pCharacter->m_Hp * 100 / pCharacter->m_originHp;
	if (hpPercent >= pEffect->m_effectValues[1])
	{
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pNewEffect->m_effectName = effectName;
		pNewEffect->m_functionNames.Add("HurtAmplifiedByAttribute");
		pNewEffect->m_effectValues = pEffect->m_effectValues;
		pNewEffect->m_duration = pEffect->m_duration;
		pNewEffect->m_isJudgeEffect = pEffect->m_isJudgeEffect;
		pNewEffect->m_isPhysOrMag = pEffect->m_isPhysOrMag;
		pNewEffect->m_canOverlap = false;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		if (pBattlePC->m_pBattleMenu)
		{
			pNewEffect->m_description = pEffect->m_description;
		}
		pCharacter->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		//DemonstrateActivateEffect(pEffect, pCharacter);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::ResourcesSub(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || pCharacter->m_characterType != 1 || !pCharacter->m_pBaseEquipment) return;
	uint8 atkCardNb = 0;
	for (uint8 i = 1; i < pCharacter->m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!pCharacter->m_pBaseEquipment->m_pSkills[i]->m_isAtkCardFlag) continue;
		atkCardNb += 1;
	}
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pCharacter);
	if (!pGameMode) return;
	ARoguelikeBattleGameMode* pRoguelikeGameMode = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (atkCardNb == 0)
	{
		pRoguelikeGameMode->m_scoreLevelMaps[1] -= pEffect->m_effectValues[0];
		if (pRoguelikeGameMode->m_scoreLevelMaps[1] <= 0) pRoguelikeGameMode->m_scoreLevelMaps[1] = 0;
	}
	else if (atkCardNb == 1)
	{
		pRoguelikeGameMode->m_scoreLevelMaps[2] -= pEffect->m_effectValues[1];
		if (pRoguelikeGameMode->m_scoreLevelMaps[2] <= 0) pRoguelikeGameMode->m_scoreLevelMaps[2] = 0;
	}
	else if (atkCardNb == 2)
	{
		pRoguelikeGameMode->m_scoreLevelMaps[3] -= pEffect->m_effectValues[2];
		if (pRoguelikeGameMode->m_scoreLevelMaps[3] <= 0) pRoguelikeGameMode->m_scoreLevelMaps[3] = 0;
	}
	else if (atkCardNb == 3)
	{
		pRoguelikeGameMode->m_scoreLevelMaps[4] -= pEffect->m_effectValues[3];
		if (pRoguelikeGameMode->m_scoreLevelMaps[4] <= 0) pRoguelikeGameMode->m_scoreLevelMaps[4] = 0;
	}
	else
	{
		pRoguelikeGameMode->m_scoreLevelMaps[5] -= pEffect->m_effectValues[4];
		if (pRoguelikeGameMode->m_scoreLevelMaps[5] <= 0) pRoguelikeGameMode->m_scoreLevelMaps[5] = 0;
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::FourColorWish(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (outColor == 0)
	{
		//添加无敌
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName("InvincibleAccordType");
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pNewEffect->m_effectName = "InvincibleAccordType";
		pNewEffect->m_functionNames.Add("InvincibleAccordType");
		pNewEffect->m_effectValues.Add(1);
		pNewEffect->m_duration = pEffect->m_duration;
		pNewEffect->m_isJudgeEffect = false;
		pNewEffect->m_isPhysOrMag = false;
		pNewEffect->m_canOverlap = false;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pEffect->m_pHost;
		pCharacter->m_pEffects.Add(pNewEffect);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
	else if (outColor == 1 || outColor == 3)
	{
		//清除所有效果
		for (int32 i = 0; i < pEffect->m_pHost->m_pEffects.Num(); i++)
		{
			if (!pEffect->m_pHost->m_pEffects[i] || pEffect->m_pHost->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
			pEffect->m_pHost->m_pEffects[i]->m_isPermenant = false;
			pEffect->m_pHost->m_pEffects[i]->m_curTickTime = pEffect->m_pHost->m_pEffects[i]->m_duration;
		}
	}
	else if (outColor == 2)
	{
		//补满血
		int32 hpDif = pCharacter->m_originHp - pCharacter->m_Hp;
		RecoverCharacter(hpDif, pEffect, pCharacter);
	}
	//DemonstrateActivateEffect(pEffect, pCharacter);
}

void UEffectFunLib::Assimilation(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter || pCharacter->m_campFlag == pEffect->m_pHost->m_campFlag) return;
	pEffect->m_modifiedValues.Add(pCharacter->m_campFlag);
	pCharacter->m_campFlag = pEffect->m_pHost->m_campFlag;
	//DemonstrateActivateEffect(pEffect, pCharacter);
	//PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
	PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::Assimilation_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_campFlag = pEffect->m_modifiedValues[0];
}

int32 UEffectFunLib::InvincibleIfNoCards(UEffect* pEffect, bool hurtEffectPhysOrMagFlag, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment) return 0;
	DemonstrateActivateEffect(pEffect, pCharacter);
	if ((pCharacter->m_pBaseEquipment->m_pSkills.Num() - 1) > 0)
		return hurtVal;
	else return 0;
	//PlayHitParticleSystem(pEffect, pCharacter);
	return 0;
}

int32 UEffectFunLib::InvincibleIfCoverActorTag(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pCharacter) return hurtVal;
	DemonstrateActivateEffect(pEffect, pCharacter);
	int32 modifyHurtVal = 0;
	if (pEffect->m_effectValues[1] < pEffect->m_effectValues[0])
	{
		//按削弱伤害计算
		modifyHurtVal = hurtVal * pEffect->m_effectValues[2] / 100;
	}
	return modifyHurtVal;
}

int32 UEffectFunLib::Undead(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pCharacter || !pCharacter->m_pBaseEquipment) return 0;

	int32 trueHurtVal = 0;
	if (pCharacter->m_DFC > 0)
	{
		if (pCharacter->m_DFC > hurtVal)
		{
			pCharacter->m_DFC -= hurtVal;
			trueHurtVal = hurtVal;
		}
		else
		{
			trueHurtVal += pCharacter->m_DFC;
			int32 damage = hurtVal - pCharacter->m_DFC;
			pCharacter->m_DFC = 0;
			int32 originHp = pCharacter->m_Hp;
			int32 leftHp = pCharacter->m_Hp - damage;
			if (leftHp <= 1)
				pCharacter->m_Hp = 1;
			else
				pCharacter->m_Hp = leftHp;
			trueHurtVal += originHp - pCharacter->m_Hp;
		}
	}
	else
	{
		int32 originHp = pCharacter->m_Hp;
		int32 leftHp = pCharacter->m_Hp - hurtVal;
		if (leftHp <= 1)
			pCharacter->m_Hp = 1;
		else
			pCharacter->m_Hp = leftHp;
		trueHurtVal = originHp - pCharacter->m_Hp;
	}
	DemonstrateHurtNb(trueHurtVal, pCharacter);
	//UpdateScores(trueHurtVal, pHurtTarget, pHurtEffect->m_enhanceType);
	if (pCharacter->m_pCharacterInfoWidget)
		pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	if (trueHurtVal > 0) pCharacter->EffectOnFx(true);
	return 0;
}

void UEffectFunLib::AbsortState(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		bool containSameEffect = false;
		for (int32 j=0; j<pEffect->m_pHost->m_pEffects.Num(); j++)
		{
			if (!pEffect->m_pHost->m_pEffects[j] || pEffect->m_pHost->m_pEffects[j]->m_effectName != pCharacter->m_pEffects[i]->m_effectName) continue;
			containSameEffect = true;
			break;
		}
		if (containSameEffect) continue;
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pCharacter->m_pEffects[i]->m_effectName);
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pCharacter->m_pEffects[i]->Copy(pNewEffect);
		pEffect->m_pHost->m_pEffects.Add(pNewEffect);

		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		DemonstrateActivateEffect(pCharacter->m_pEffects[i], pEffect->m_pHost);
		AddStateToCharacter(pEffect->m_pHost, pNewEffect->m_effectName);
	}
	
	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::AbsortStatePassive(UEffect* pEffect, UEffect* pHurtEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pHurtEffect || !pHurtEffect->m_pHost) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i = 0; i < pHurtEffect->m_pHost->m_pEffects.Num(); i++)
	{
		//遍历被攻击对象的所有效果
		if (!pHurtEffect->m_pHost->m_pEffects[i] || pHurtEffect->m_pHost->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		bool containSameEffect = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (!pCharacter->m_pEffects[j] || pCharacter->m_pEffects[j]->m_effectName != pHurtEffect->m_pHost->m_pEffects[i]->m_effectName) continue;
			containSameEffect = true;
			break;
		}
		if (containSameEffect) continue;
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pHurtEffect->m_pHost->m_pEffects[i]->m_effectName);
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pHurtEffect->m_pHost->m_pEffects[i]->Copy(pNewEffect);
		pCharacter->m_pEffects.Add(pNewEffect);

		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		//DemonstrateActivateEffect(pCharacter->m_pEffects[i], pEffect->m_pHost);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}

	PlayHitBeamParticle(pHurtEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::BroadcastStates(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i = 0; i < pEffect->m_pHost->m_pEffects.Num(); i++)
	{
		if (!pEffect->m_pHost->m_pEffects[i] || pEffect->m_pHost->m_pEffects[i]->m_effectType == "OneTimeEffect") continue;
		bool containSameEffect = false;
		for (int32 j = 0; j < pCharacter->m_pEffects.Num(); j++)
		{
			if (!pCharacter->m_pEffects[j] || pCharacter->m_pEffects[j]->m_effectName != pEffect->m_pHost->m_pEffects[i]->m_effectName) continue;
			containSameEffect = true;
			break;
		}
		if (containSameEffect) continue;
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_pHost->m_pEffects[i]->m_effectName);
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pEffect->m_pHost->m_pEffects[i]->Copy(pNewEffect);
		pCharacter->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
		DemonstrateActivateEffect(pEffect->m_pHost->m_pEffects[i], pCharacter);
	}
	
	PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
}

void UEffectFunLib::CopyDefence(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFC = pEffect->m_effectValues[0];
	AddStateToCharacter(pCharacter, pEffect->m_effectName);
}

void UEffectFunLib::CopyDefence_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_DFCPercent += pEffect->m_modifiedValues[0];
}

void UEffectFunLib::DiseaseInfection(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pHost) return;
	
	int32 originDFC = pCharacter->m_DFC;
	if ((pCharacter->m_DFC - pEffect->m_effectValues[0]) < 0) pCharacter->m_DFC = 0;
	else pCharacter->m_DFC -= pEffect->m_effectValues[0];
	int32 DFCDif = pCharacter->m_DFC - originDFC;

	if ((pEffect->m_pHost->m_DFC + DFCDif) > pCharacter->m_maxDFC) pEffect->m_pHost->m_DFC = pEffect->m_pHost->m_maxDFC;
	else pEffect->m_pHost->m_DFC += DFCDif;

	PlayHitBeamParticle(pEffect->m_pHost, pCharacter, pEffect);
	//PlayHitBeamParticle(pHurtEffect->m_pHost, pCharacter, pEffect);
}

void UEffectFunLib::IncreaseATKAndDecreaseDFC(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	if ((pCharacter->m_DFC - pEffect->m_effectValues[0]) < 0) pCharacter->m_DFC = 0;
	else pCharacter->m_DFC -= pEffect->m_effectValues[0];

	int32 originAtkAddition = pCharacter->m_ATKAddition;
	if ((pCharacter->m_ATKAddition + pEffect->m_effectValues[1]) > pCharacter->m_maxATKAddition) pCharacter->m_ATKAddition = pCharacter->m_maxATKAddition;
	else pCharacter->m_ATKAddition += pEffect->m_effectValues[0];
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	pEffect->m_modifiedValues.Add(pCharacter->m_ATKAddition - originAtkAddition);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::IncreaseATKAndDecreaseDFC_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::IncreasePoison(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (!pCharacter->m_pEffects[i] || pCharacter->m_pEffects[i]->m_effectName != "Poison") continue;
		pCharacter->m_pEffects[i]->m_effectValues[0] += pEffect->m_effectValues[0];
		pCharacter->m_pEffects[i]->m_effectDefaultParam.effectValues = pCharacter->m_pEffects[i]->m_effectValues;
		DemonstrateActivateEffect(pCharacter->m_pEffects[i], pCharacter);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::JudgeToIncreaseDefence(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 outColor = -1;
	int32 outNb = -1;
	bool judgeResult = Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);

	if (!judgeResult) return;
	pCharacter->m_DFC += pEffect->m_effectValues[0];
	if (pCharacter->m_DFC >= pCharacter->m_maxDFC) pCharacter->m_DFC = pCharacter->m_maxDFC;
	if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);

	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DoubleAttack(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	int32 atkDif = pCharacter->m_ATKAddition;
	pEffect->m_modifiedValues.Add(atkDif);
	pCharacter->m_ATKAddition *= 2;
	pEffect->m_isOnTimeEffectDone = true;
	//if (pCharacter->m_pCharacterInfoWidget) pCharacter->m_pCharacterInfoWidget->NotifyAtkChange(pCharacter->m_ATKAddition);
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::DoubleAttack_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	pCharacter->m_ATKAddition -= pEffect->m_modifiedValues[0];
}

void UEffectFunLib::ContinuousHurtIfUnderDark(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	bool resistEffect = false;
	for (int32 i=0; i<pCharacter->m_pEffects.Num(); i++)
	{
		if (pCharacter->m_pEffects[i]->m_effectName.Contains("ResistContinuousHurtUnderDark"))
		{
			resistEffect = true;
			break;
		}
	}
	if (!resistEffect)
		HurtCharacter(pEffect->m_effectValues[0], pEffect, pCharacter);
}

void UEffectFunLib::Slow(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pOriginGeo || pCharacter->m_timeDilationParams.Contains(pEffect->m_pOriginGeo->GetName())) return;
	FTimeDilationInfo timeDilationInfo((float)pEffect->m_duration/25.f, pEffect->m_effectValues[0], 1);
	//pCharacter->m_timeDilationParams.Add(pEffect->m_pOriginGeo->GetName(), pEffect->m_effectValues[0]);
	pCharacter->m_timeDilationParams.Add(pEffect->GetName(), timeDilationInfo);
	if (pCharacter->CustomTimeDilation >= ((float)pEffect->m_effectValues[0]) / 100.f)
	{
		pCharacter->CustomTimeDilation = ((float)pEffect->m_effectValues[0]) / 100.f;
		pCharacter->m_speedRatePercent = pEffect->m_effectValues[0];
	}
}

void UEffectFunLib::Slow_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	if (!pCharacter->m_timeDilationParams.Contains(pEffect->GetName())) return;

	pCharacter->m_timeDilationParams.Remove(pEffect->GetName());

	int32 minTimeDilation = 100;
	for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = pCharacter->m_timeDilationParams.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.timeDilationPercent <= minTimeDilation)
		{
			minTimeDilation = iter->Value.timeDilationPercent;
			//curTimeDilationKey = iter->Key;
		}
	}

	//m_curTimeDilationKey = curTimeDilationKey;
	pCharacter->CustomTimeDilation = (float)minTimeDilation / 100.f;
	pCharacter->m_speedRatePercent = minTimeDilation;
}

void UEffectFunLib::ContinuousSlow(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pOriginGeo || pCharacter->m_timeDilationParams.Contains(pEffect->m_pOriginGeo->GetName())) return;
	FTimeDilationInfo timeDilationInfo((float)pEffect->m_duration / 25.f, pEffect->m_effectValues[0], 0);
	//pCharacter->m_timeDilationParams.Add(pEffect->m_pOriginGeo->GetName(), pEffect->m_effectValues[0]);
	pCharacter->m_timeDilationParams.Add(pEffect->m_pOriginGeo->GetName(), timeDilationInfo);
	if (pCharacter->CustomTimeDilation >= ((float)pEffect->m_effectValues[0]) / 100.f)
	{
		pCharacter->CustomTimeDilation = ((float)pEffect->m_effectValues[0]) / 100.f;
		pCharacter->m_speedRatePercent = pEffect->m_effectValues[0];
	}
}

void UEffectFunLib::ContinuousSlow_End(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter || !pEffect->m_pOriginGeo) return;
	if (!pCharacter->m_timeDilationParams.Contains(pEffect->m_pOriginGeo->GetName())) return;

	pCharacter->m_timeDilationParams.Remove(pEffect->m_pOriginGeo->GetName());

	int32 minTimeDilation = 100;
	for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = pCharacter->m_timeDilationParams.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.timeDilationPercent <= minTimeDilation)
		{
			minTimeDilation = iter->Value.timeDilationPercent;
			//curTimeDilationKey = iter->Key;
		}
	}

	//m_curTimeDilationKey = curTimeDilationKey;
	pCharacter->CustomTimeDilation = (float)minTimeDilation / 100.f;
	pCharacter->m_speedRatePercent = minTimeDilation;
}

void UEffectFunLib::PureJudge(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return;
	for (int32 i=0; i<pEffect->m_effectValues[0]; i++)
	{
		int32 outColor = -1;
		int32 outNb = -1;
		Judge(outColor, outNb, pEffect, pCharacter, pEffect->m_pHost);
	}
	//PlayHitParticleSystem(pEffect, pCharacter);
}

void UEffectFunLib::SpawnAppendEffect(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect || !pCharacter) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i=0; i<pEffect->m_appendEffectList.Num(); i++)
	{
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_appendEffectList[i].effectName);
		if (!effectClass) return;
		UEffect* pNewEffect = NewObject<UEffect>(pCharacter, effectClass);
		pNewEffect->m_effectValues = pEffect->m_appendEffectList[i].effectValues;
		pNewEffect->m_hitNbs = pEffect->m_appendEffectList[i].hitNbs;
		pNewEffect->m_hitColors = pEffect->m_appendEffectList[i].hitColors;
		pNewEffect->m_duration = pEffect->m_appendEffectList[i].duration;
		pNewEffect->m_isJudgeEffect = pEffect->m_appendEffectList[i].isJudgeEffect;
		pNewEffect->m_isPhysOrMag = pEffect->m_appendEffectList[i].isPhysOrMag;
		pNewEffect->m_pOriginGeo = pEffect->m_pOriginGeo;
		pNewEffect->m_pHost = pEffect->m_pHost;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = pEffect->m_appendEffectList[i].chDescription;
			else
				pNewEffect->m_description = pEffect->m_appendEffectList[i].enDescription;
		}
		pCharacter->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		AddStateToCharacter(pCharacter, pNewEffect->m_effectName);
	}
}

void UEffectFunLib::SpawnAppendEffectBackward(UEffect* pEffect, ABaseCharacter* pHitCharacter)
{
	if (!pEffect || !pHitCharacter || !pEffect->m_pHost) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(pHitCharacter, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i = 0; i < pEffect->m_appendEffectList.Num(); i++)
	{
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_appendEffectList[i].effectName);
		if (!effectClass) return;
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pNewEffect->m_effectValues = pEffect->m_appendEffectList[i].effectValues;
		pNewEffect->m_hitNbs = pEffect->m_appendEffectList[i].hitNbs;
		pNewEffect->m_hitColors = pEffect->m_appendEffectList[i].hitColors;
		pNewEffect->m_duration = pEffect->m_appendEffectList[i].duration;
		pNewEffect->m_isJudgeEffect = pEffect->m_appendEffectList[i].isJudgeEffect;
		pNewEffect->m_isPhysOrMag = pEffect->m_appendEffectList[i].isPhysOrMag;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pHitCharacter;
		pEffect->m_pHost->m_pEffects.Add(pNewEffect);
		
		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == pHitCharacter)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		AddStateToCharacter(pEffect->m_pHost, pNewEffect->m_effectName);
	}
}

void UEffectFunLib::HurtCharacter(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget)
{
	if (!pHurtTarget) return;
	if (pHurtTarget->m_characterType == 1)
	{
		AKing* pPlayerCharacter = Cast<AKing>(pHurtTarget);
		if (pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch" && pPlayerCharacter->m_curSkillNb != 0 && pPlayerCharacter->m_curHurtImmuneTimeCount < pPlayerCharacter->m_hurtImmuneTime)
			return;
	}
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pHurtTarget);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPhysCalculator) return;
	int32 modifyHurtVal = pBattleLevelGameMode->m_pPhysCalculator->ActivateHurtPassiveEffect(hurtVal, pHurtEffect, pHurtTarget);
	int32 trueHurtVal = 0;
	if (pHurtTarget->m_DFC > 0)
	{
		if (pHurtTarget->m_DFC > modifyHurtVal)
		{
			pHurtTarget->m_DFC -= modifyHurtVal;
			trueHurtVal = modifyHurtVal;
		}
		else
		{
			trueHurtVal += pHurtTarget->m_DFC;
			int32 damage = modifyHurtVal - pHurtTarget->m_DFC;
			pHurtTarget->m_DFC = 0;
			int32 originHp = pHurtTarget->m_Hp;
			int32 leftHp = pHurtTarget->m_Hp - damage;
			if (leftHp <= 0)
				pHurtTarget->m_Hp = 0;
			else
				pHurtTarget->m_Hp = leftHp;
			trueHurtVal += originHp - pHurtTarget->m_Hp;
		}
	}
	else
	{
		int32 originHp = pHurtTarget->m_Hp;
		int32 leftHp = pHurtTarget->m_Hp - modifyHurtVal;
		if (leftHp <= 0)
			pHurtTarget->m_Hp = 0;
		else
			pHurtTarget->m_Hp = leftHp;
		trueHurtVal = originHp - pHurtTarget->m_Hp;
	}

	//DemonstrateActivateEffect(pHurtEffect, pHurtTarget, trueHurtVal);
	DemonstrateHurtNb(trueHurtVal, pHurtTarget);
	//UpdateScores(trueHurtVal, pHurtTarget, pHurtEffect->m_enhanceType);
	if (pHurtTarget->m_pCharacterInfoWidget)
		pHurtTarget->m_pCharacterInfoWidget->NotifyHpChange(pHurtTarget->m_Hp, pHurtTarget->m_DFC);
	if (modifyHurtVal > 0) pHurtTarget->EffectOnFx(true);
}

void UEffectFunLib::HurtCharacterPiercing(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget)
{
	if (!pHurtTarget) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pHurtTarget);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPhysCalculator) return;
	int32 modifyHurtVal = pBattleLevelGameMode->m_pPhysCalculator->ActivateHurtPassiveEffect(hurtVal, pHurtEffect, pHurtTarget);
	int32 trueHurtVal = 0;
	int32 originHp = pHurtTarget->m_Hp;
	int32 leftHp = pHurtTarget->m_Hp - modifyHurtVal;
	if (leftHp <= 0)
		pHurtTarget->m_Hp = 0;
	else
		pHurtTarget->m_Hp = leftHp;
	trueHurtVal = originHp - pHurtTarget->m_Hp;

	//DemonstrateActivateEffect(pHurtEffect, pHurtTarget, trueHurtVal);
	DemonstrateHurtNb(trueHurtVal, pHurtTarget);
	//UpdateScores(trueHurtVal, pHurtTarget, pHurtEffect->m_enhanceType);
	if (pHurtTarget->m_pCharacterInfoWidget)
		pHurtTarget->m_pCharacterInfoWidget->NotifyHpChange(pHurtTarget->m_Hp, pHurtTarget->m_DFC);
	if (modifyHurtVal > 0) pHurtTarget->EffectOnFx(true);
}

void UEffectFunLib::RecoverCharacter(int32 recoverVal, UEffect* pRecoverEffect, ABaseCharacter* pRecoverTarget)
{
	if (!pRecoverTarget) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pRecoverTarget);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPhysCalculator) return;
	int32 modifyRecoverVal = pBattleLevelGameMode->m_pPhysCalculator->ActivateRecoverPassiveEffect(recoverVal, pRecoverEffect, pRecoverTarget);
	int32 leftHp = pRecoverTarget->m_Hp + modifyRecoverVal;
	if (leftHp >= pRecoverTarget->m_originHp)
		pRecoverTarget->m_Hp = pRecoverTarget->m_originHp;
	else
		pRecoverTarget->m_Hp = leftHp;
	if (pRecoverTarget->m_pCharacterInfoWidget)
		pRecoverTarget->m_pCharacterInfoWidget->NotifyHpChange(pRecoverTarget->m_Hp, pRecoverTarget->m_DFC);
	if (modifyRecoverVal > 0) pRecoverTarget->EffectOnFx(false);
}

void UEffectFunLib::DeadSpawnGeo(UEffect* pEffect, ABaseCharacter* pDeadCharacter)
{
	if (!pEffect || !pDeadCharacter) return;
	FString geoName = pEffect->m_effectName.RightChop(13);

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(pDeadCharacter);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	if (!pRGM || !pRGM->m_pPhysCalculator) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	if (!pSingleton->m_physGeoClassMap.Contains(geoName)) return;
	ABasePhysGeo* pGeo = pRGM->m_pPhysCalculator->SpawnPhysGeo(pSingleton->m_physGeoClassMap[geoName], pDeadCharacter->GetActorLocation(), pDeadCharacter->GetActorRotation());
	pRGM->m_pPhysCalculator->AddPhysGeo(pGeo, NULL, pDeadCharacter->m_campFlag);
	UGameplayStatics::SpawnEmitterAtLocation(pRGM, pDeadCharacter->m_skillParticleMap[geoName].particleSystem, pDeadCharacter->GetActorLocation());
}

int32 UEffectFunLib::HurtTransfer(UEffect* pEffect, ABaseCharacter* pHurtTarget, int32 hurtVal)
{
	if (!pEffect || !pEffect->m_pHost || !pHurtTarget) return hurtVal;
	if (!pEffect->m_isLinkSource)
	{
		if (pEffect->m_isOnTimeEffectDone) return 0;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_effectName);
		if (!effectClass) return 0;
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pEffect->Copy(pNewEffect);
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pHurtTarget;
		pNewEffect->m_isLinkSource = true;
		pNewEffect->m_canOverlap = pEffect->m_canOverlap;
		pEffect->m_pHost->m_pEffects.Add(pNewEffect);
		pEffect->m_isOnTimeEffectDone = true;
		pNewEffect->m_effectType = "HurtPassiveActivate";
		pNewEffect->m_duration = pEffect->m_duration - pEffect->m_curTickTime;
		PlayHitBeamParticle(pHurtTarget, pEffect->m_pHost, pEffect);
		return 0;
	}
	else
	{
		int32 trueHurtVal = 0;
		if (pEffect->m_pHost->m_DFC > 0)
		{
			if (pEffect->m_pHost->m_DFC > hurtVal)
			{
				pEffect->m_pHost->m_DFC -= hurtVal;
				trueHurtVal = hurtVal;
			}
			else
			{
				trueHurtVal += pEffect->m_pHost->m_DFC;
				int32 damage = hurtVal - pEffect->m_pHost->m_DFC;
				pEffect->m_pHost->m_DFC = 0;
				int32 originHp = pEffect->m_pHost->m_Hp;
				int32 leftHp = pEffect->m_pHost->m_Hp - damage;
				if (leftHp <= 0)
					pEffect->m_pHost->m_Hp = 0;
				else
					pEffect->m_pHost->m_Hp = leftHp;
				trueHurtVal += originHp - pEffect->m_pHost->m_Hp;
			}
		}
		else
		{
			int32 originHp = pEffect->m_pHost->m_Hp;
			int32 leftHp = pEffect->m_pHost->m_Hp - hurtVal;
			if (leftHp <= 0)
				pEffect->m_pHost->m_Hp = 0;
			else
				pEffect->m_pHost->m_Hp = leftHp;
			trueHurtVal = originHp - pEffect->m_pHost->m_Hp;
		}
		DemonstrateHurtNb(trueHurtVal, pEffect->m_pHost);
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		if (pEffect->m_pHost->m_pCharacterInfoWidget)
			pEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pEffect->m_pHost->m_Hp, pEffect->m_pHost->m_DFC);
		pEffect->m_pHost->EffectOnFx(true);
		PlayHitBeamParticle(pHurtTarget, pEffect->m_pHost, pEffect);
		return 0;
	}
	return hurtVal;
}

void UEffectFunLib::HostDieTogether(UEffect* pEffect, ABaseCharacter* pCharacter)
{
	if (!pEffect->m_isLinkSource)
	{
		if (pEffect->m_isOnTimeEffectDone) return;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_effectName);
		if (!effectClass) return;
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pEffect->Copy(pNewEffect);
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pCharacter;
		pNewEffect->m_isLinkSource = true;
		pNewEffect->m_canOverlap = pEffect->m_canOverlap;
		pEffect->m_pHost->m_pEffects.Add(pNewEffect);
		pEffect->m_isOnTimeEffectDone = true;
		pNewEffect->m_effectType = "DeadActivate";
		pNewEffect->m_duration = pEffect->m_duration - pEffect->m_curTickTime;
		PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
	}
	else
	{
		if (!pEffect->m_pHost) return;
		int32 trueHurtVal = 0;
		int32 originHp = pEffect->m_pHost->m_Hp;
		int32 leftHp = pEffect->m_pHost->m_Hp - pEffect->m_effectValues[0];
		if (leftHp <= 0)
			pEffect->m_pHost->m_Hp = 0;
		else
			pEffect->m_pHost->m_Hp = leftHp;
		trueHurtVal = originHp - pEffect->m_pHost->m_Hp;

		//DemonstrateActivateEffect(pHurtEffect, pHurtTarget, trueHurtVal);
		DemonstrateHurtNb(trueHurtVal, pEffect->m_pHost);
		//UpdateScores(trueHurtVal, pHurtTarget, pHurtEffect->m_enhanceType);
		if (pEffect->m_pHost->m_pCharacterInfoWidget)
			pEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pEffect->m_pHost->m_Hp, pEffect->m_pHost->m_DFC);
		pEffect->m_pHost->EffectOnFx(true);
	}
}

int32 UEffectFunLib::SortByEvenOdd(UEffect* pEffect, int32 hurtVal)
{
	if (!pEffect || !pEffect->m_pHost) return hurtVal;
	if (pEffect->m_effectValues[0] == 0)
	{
		//说明此次为偶数，免疫此伤害
		pEffect->m_effectValues[0] = 1;
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		return 0;
	}
	else
	{
		pEffect->m_effectValues[0] = 0;
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		return 2 * hurtVal;
	}
	return hurtVal;
}

int32 UEffectFunLib::ShareHurt(UEffect* pEffect, ABaseCharacter* pCharacter, int32 hurtVal)
{
	if (!pEffect || !pEffect->m_pHost || !pCharacter) return hurtVal;
	if (!pEffect->m_isLinkSource)
	{
		if (pEffect->m_isOnTimeEffectDone) return 0;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(pEffect->m_effectName);
		if (!effectClass) return 0;
		UEffect* pNewEffect = NewObject<UEffect>(pEffect->m_pHost, effectClass);
		pEffect->Copy(pNewEffect);
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = pCharacter;
		pNewEffect->m_isLinkSource = true;
		pNewEffect->m_canOverlap = pEffect->m_canOverlap;
		pEffect->m_pHost->m_pEffects.Add(pNewEffect);
		pEffect->m_isOnTimeEffectDone = true;
		pNewEffect->m_effectType = "HurtPassiveActivate";
		pNewEffect->m_duration = pEffect->m_duration - pEffect->m_curTickTime;
		PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
		return 0;
	}
	else
	{
		int32 shareHurt = hurtVal * pEffect->m_effectValues[0] / 100;
		int32 leftHurt = hurtVal - shareHurt;
		/*int32 originHp = pEffect->m_pHost->m_Hp;
		int32 leftHp = pEffect->m_pHost->m_Hp - shareHurt;
		if (leftHp <= 0)
			pEffect->m_pHost->m_Hp = 0;
		else
			pEffect->m_pHost->m_Hp = leftHp;*/
		int32 trueHurtVal = 0;
		if (pEffect->m_pHost->m_DFC > 0)
		{
			if (pEffect->m_pHost->m_DFC > shareHurt)
			{
				pEffect->m_pHost->m_DFC -= shareHurt;
				trueHurtVal = shareHurt;
			}
			else
			{
				trueHurtVal += pEffect->m_pHost->m_DFC;
				int32 damage = shareHurt - pEffect->m_pHost->m_DFC;
				pEffect->m_pHost->m_DFC = 0;
				int32 originHp = pEffect->m_pHost->m_Hp;
				int32 leftHp = pEffect->m_pHost->m_Hp - damage;
				if (leftHp <= 0)
					pEffect->m_pHost->m_Hp = 0;
				else
					pEffect->m_pHost->m_Hp = leftHp;
				trueHurtVal += originHp - pEffect->m_pHost->m_Hp;
			}
		}
		else
		{
			int32 originHp = pEffect->m_pHost->m_Hp;
			int32 leftHp = pEffect->m_pHost->m_Hp - shareHurt;
			if (leftHp <= 0)
				pEffect->m_pHost->m_Hp = 0;
			else
				pEffect->m_pHost->m_Hp = leftHp;
			trueHurtVal = originHp - pEffect->m_pHost->m_Hp;
		}
		DemonstrateHurtNb(trueHurtVal, pEffect->m_pHost);
		DemonstrateActivateEffect(pEffect, pEffect->m_pHost);
		if (pEffect->m_pHost->m_pCharacterInfoWidget)
			pEffect->m_pHost->m_pCharacterInfoWidget->NotifyHpChange(pEffect->m_pHost->m_Hp, pEffect->m_pHost->m_DFC);
		pEffect->m_pHost->EffectOnFx(true);
		PlayHitBeamParticle(pCharacter, pEffect->m_pHost, pEffect);
		return leftHurt;
	}
	return hurtVal;
}


void UEffectFunLib::PlayHitBeamParticle(AActor* pSource, AActor* pTarget, UEffect* pEffect)
{
	if (!pSource || !pTarget) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	FVector spawnLoc = (pSource->GetActorLocation() + pTarget->GetActorLocation()) / 2.f;
	UParticleSystem* pHitParticle = NULL;
	if (pEffect->m_pOriginGeo) pHitParticle = pEffect->m_pOriginGeo->m_pHitParticleSystem;
	else pHitParticle = pSingleton->FindHitParticleByName(pEffect->m_effectName);
	if (!pHitParticle) return;
	UParticleSystemComponent* pParticleComponent = NULL;
	if (pHitParticle) pParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(pSource, pHitParticle, spawnLoc);
	FParticleSysParam soureParam;
	soureParam.Name = "BeamSource";
	soureParam.ParamType = EParticleSysParamType::PSPT_Actor;
	soureParam.Scalar = 0.f;
	soureParam.Scalar_Low = 0.f;
	soureParam.Vector = FVector::ZeroVector;
	soureParam.Vector_Low = FVector::ZeroVector;
	soureParam.Actor = pSource;
	FParticleSysParam targetParam;
	targetParam.Name = "BeamTarget";
	targetParam.ParamType = EParticleSysParamType::PSPT_Actor;
	targetParam.Scalar = 0.f;
	targetParam.Scalar_Low = 0.f;
	targetParam.Vector = FVector::ZeroVector;
	targetParam.Vector_Low = FVector::ZeroVector;
	targetParam.Actor = pTarget;
	pParticleComponent->InstanceParameters.Add(soureParam);
	pParticleComponent->InstanceParameters.Add(targetParam);
	if (!pEffect->m_pOriginGeo || !pEffect->m_pOriginGeo->m_isHitParticleBindtoEffect) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(pSource);
	if (!pGameMode) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPhysCalculator) return;
	ABaseCharacter* pHost = Cast<ABaseCharacter>(pSource);
	ABaseCharacter* pGuest = Cast<ABaseCharacter>(pTarget);
	FBindPSInformation BindPSInformation(pHost, pGuest, pEffect);
	pBattleLevelGameMode->m_pPhysCalculator->m_bindPSMap.Add(pParticleComponent, BindPSInformation);
}
