// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "BattleLevelGameModeBase.h"
#include "../Base/Battle/BattleLevelPlayerController.h"
#include "../Base/CollisionWarGameInstance.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
//#include "Lua/LuaActor.h"
#include "../Common/WidgetBlueprintFunctionLibrary.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBEvent.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Engine/KBETypes.h"
#include "Battle/Team/SpawnPoint.h"




ABattleLevelGameModeBase::ABattleLevelGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void ABattleLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(KBEngineApp::getSingleton().isInitialized());
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(this);
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	//ReqLevelInfos(pCWGameInstance->m_curLevelName);
	TellBPBeginPlay();
}

void ABattleLevelGameModeBase::Destroyed()
{
	Super::Destroyed();
}

void ABattleLevelGameModeBase::Tick(float DeltaSeconds)
{
	
}

void ABattleLevelGameModeBase::LoadProgress_Implementation(const FString& progressCode)
{

}

void ABattleLevelGameModeBase::MatchResult_Implementation(const FString& matchResult)
{

}

void ABattleLevelGameModeBase::UpdateAINavigation()
{
	if (m_isInTutorial) return;
	for (int32 i=0; i<m_pAICharacters.Num(); i++)
	{
		if (!m_pAICharacters[i] || !m_pAICharacters[i]->m_pNormalLongTask) continue;
		for (int32 j = 0; j<m_pRecastDetourObject->m_targetPack->m_vec.Num(); j++)
		{
			if (m_pRecastDetourObject->m_targetPack->m_vec[j]->agentMark == m_pAICharacters[i]->m_entityID)
			{
				m_pRecastDetourObject->m_targetPack->m_vec[j]->x = (float)m_pAICharacters[i]->m_pNormalLongTask->m_destination.Y / 100.f;
				//m_pRecastDetourObject->m_targetPack->m_vec[j]->y = (float)m_pAICharacters[i]->GetActorLocation().Z / 100.f;
				m_pRecastDetourObject->m_targetPack->m_vec[j]->y = 150.f / 100.f;
				m_pRecastDetourObject->m_targetPack->m_vec[j]->z = (float)m_pAICharacters[i]->m_pNormalLongTask->m_destination.X / 100.f;
				/*FVector destination(m_pAICharacters[i]->m_pNormalLongTask->m_destination.X, m_pAICharacters[i]->m_pNormalLongTask->m_destination.Y, m_pAICharacters[i]->GetActorLocation().Z);
				DrawDebugLine(GetWorld(), m_pAICharacters[i]->GetActorLocation(), destination, FColor::Red, false, 0.1, 0, 5);*/
				/*GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::White, TEXT("X target is ") + FString::SanitizeFloat(m_pRecastDetourObject->m_targetPack->m_vec[j]->z) +
				TEXT("/  Y target is ") + FString::SanitizeFloat(m_pRecastDetourObject->m_targetPack->m_vec[j]->x));*/
				break;
			}
		}
	}
	for (int32 i=0; i<m_pPlayerCharacters.Num(); i++)
	{
		if (!m_pPlayerCharacters[i]) continue;
		for (int32 j=0; j<m_pRecastDetourObject->m_playerVelPack->m_vec.Num(); j++)
		{
			if (m_pRecastDetourObject->m_playerVelPack->m_vec[j]->agentMark == m_pPlayerCharacters[i]->m_entityID)
			{
				m_pRecastDetourObject->m_playerVelPack->m_vec[j]->x = (float)m_pPlayerCharacters[i]->m_curLogicVelocity.Y / 100.f;
				m_pRecastDetourObject->m_playerVelPack->m_vec[j]->z = 0;
				m_pRecastDetourObject->m_playerVelPack->m_vec[j]->z = (float)m_pPlayerCharacters[i]->m_curLogicVelocity.X / 100.f;
			}
		}
	}

	for (int32 i=0; i<m_pAllCharacters.Num(); i++)
	{
		if (!m_pAllCharacters[i]) continue;
		for (int32 j = 0; j < m_pRecastDetourObject->m_posPack->m_vec.Num(); j++)
		{
			if (m_pRecastDetourObject->m_posPack->m_vec[j]->agentMark == m_pAllCharacters[i]->m_entityID)
			{
				m_pRecastDetourObject->m_posPack->m_vec[j]->x = m_pAllCharacters[i]->GetActorLocation().Y/100.f;
				//m_pRecastDetourObject->m_posPack->m_vec[j]->y = m_pAllCharacters[i]->GetActorLocation().Z/100.f;
				m_pRecastDetourObject->m_posPack->m_vec[j]->y = 150.f / 100.f;
				m_pRecastDetourObject->m_posPack->m_vec[j]->z = m_pAllCharacters[i]->GetActorLocation().X/100.f;

				break;
			}
		}
	}
	float logicDeltaTime = (float)m_logicExpandTickTimeDelta / 1000.f;
	m_pRecastDetourObject->MainTick(logicDeltaTime);
	for (int32 i=0; i<m_pRecastDetourObject->m_velPack->m_vec.Num(); i++)
	{
		ABaseCharacter* pCharacter = FindAICharacterEntity(m_pRecastDetourObject->m_velPack->m_vec[i]->agentMark);
		if (!pCharacter) continue;
		if (pCharacter->m_characterType == 1 || pCharacter->m_characterType == 2) continue;
		
		if (m_pRecastDetourObject->m_velPack->m_vec[i]->state == DT_CROWDAGENT_STATE_INVALID ||
			m_pRecastDetourObject->m_velPack->m_vec[i]->state == DT_CROWDAGENT_STATE_OFFMESH ||
			m_pRecastDetourObject->m_velPack->m_vec[i]->targetState == DT_CROWDAGENT_TARGET_NONE)
		{
			if (!pCharacter->m_pNormalLongTask->m_pTarget)
			{
				pCharacter->m_pNormalLongTask->m_evaLogicVelocity.X = 0;
				pCharacter->m_pNormalLongTask->m_evaLogicVelocity.Y = 0;
			}
			else
			{
				FVector offset = pCharacter->m_pNormalLongTask->m_pTarget->GetActorLocation() - pCharacter->GetActorLocation();
				pCharacter->m_pNormalLongTask->m_evaLogicVelocity.X = offset.X;
				pCharacter->m_pNormalLongTask->m_evaLogicVelocity.Y = offset.Y;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "aaa");
		}
		else
		{
			pCharacter->m_pNormalLongTask->m_evaLogicVelocity.X = (int32)(m_pRecastDetourObject->m_velPack->m_vec[i]->z * 100);
			pCharacter->m_pNormalLongTask->m_evaLogicVelocity.Y = (int32)(m_pRecastDetourObject->m_velPack->m_vec[i]->x * 100);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "bbb");
		}
		/*GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, TEXT("X direction velocity is ") + FString::SanitizeFloat(pCharacter->m_pNormalLongTask->m_evaLogicVelocity.X) +
			TEXT("/  Y direction velocity is ") + FString::SanitizeFloat(pCharacter->m_pNormalLongTask->m_evaLogicVelocity.Y));*/
	}
}

void ABattleLevelGameModeBase::RCDebug()
{
	/*if (!m_pRecastDetourObject) return;
	dtCrowdTP* pCrowd = m_pRecastDetourObject->m_pSample->getCrowd();
	if (!pCrowd) return;
	dtCrowdAgent** agents = pCrowd->m_activeAgents;
	int nagents = pCrowd->getActiveAgents(agents, pCrowd->getAgentCount());
	//int mark = m_posPack->m_vec[i]->agentMark;
	for (int j = 0; j < nagents; j++)
	{
		dtCrowdAgent* ag = agents[j];
		if (!ag) break;
		int32 mark = ag->m_agentMark;
		FVector debugPos;
		debugPos.X = ag->targetPos[2] * 100.f - 250.f;
		debugPos.Y = ag->targetPos[0] * 100.f - 250.f;
		debugPos.Z = 188;
		FString activeFlag = "true";
		if (!ag->active) activeFlag = "false";
		FString debugStr = "Mark:" + FString::FromInt(ag->m_agentMark) + "," + "isActive:" + activeFlag + "," + FString::SanitizeFloat(debugPos.X) + "," +
			FString::SanitizeFloat(debugPos.Y) + "," + FString::SanitizeFloat(debugPos.Z);
		DrawDebugString(GetWorld(), debugPos, debugStr, 0, FColor::White, 0.1);
	}*/
}

void ABattleLevelGameModeBase::LevelLogic_Implementation(int32 frameNb)
{

}

void ABattleLevelGameModeBase::UpdateAllCharacterAILogic(float deltaT)
{
	/************************************************************************/
	/* 由主机运行，AI角色行为更新 */
	/************************************************************************/
	//循环更新所有AI角色的“思想”，执行EvaluateConditionAround
	//执行Team的CharactersFormation，从Team角度更新AI角色“思想”
	//随逻辑帧发送给服务端，交由RecastnNav调用
	if (m_pAICharacters.Num() == 0)
	{
		m_curAIUpdateNb = 0;
		return;
	}
	for (int32 i=0; i<m_maxUpdateAINbPerFrame; i++)
	{
		if (m_curAIUpdateNb >= m_pAICharacters.Num()) m_curAIUpdateNb = 0;
		m_pAICharacters[m_curAIUpdateNb]->EvaluateConditionAround(deltaT);
		m_curAIUpdateNb++;
	}
}

void ABattleLevelGameModeBase::UpdateCharacterNormalLogic(float dT)
{
	for (int32 i=0; i<m_pAllCharacters.Num(); i++)
	{
		if (!m_pAllCharacters[i]->m_pBaseAnimInstance) continue;
		/*DrawDebugString(GetWorld(), m_pAllCharacters[i]->GetActorLocation() + FVector(0, 0, 200), TEXT("HP:") + FString::FromInt(m_pAllCharacters[i]->m_Hp),
			NULL, FColor::Red, 0.1);*/
		
		bool canMove = true;
		for (int32 j=0; j<m_pAllCharacters[i]->m_pEffects.Num(); j++)
		{
			if (m_pAllCharacters[i]->m_pEffects[j]->m_effectName.Contains("_Dizzy") ||
				m_pAllCharacters[i]->m_pEffects[j]->m_effectName.Contains("_Freeze"))
			{
				canMove = false;
				break;
			}
		}
		
		if ((m_pAllCharacters[i]->m_actionName == TEXT("ImplementSkill") || 
			m_pAllCharacters[i]->m_actionName == TEXT("ImplementSpellSkill") || 
			m_pAllCharacters[i]->m_actionName == TEXT("BuildWorkShop") ||
			m_pAllCharacters[i]->m_actionName == TEXT("ImplementBlock") ||
			m_pAllCharacters[i]->m_actionName == TEXT("ImplementDodge")) && canMove == true)
		{
			if (m_pAllCharacters[i]->m_actionName == TEXT("ImplementBlock"))
			{
				m_pAllCharacters[i]->m_implementSkillType = 1;
				m_pAllCharacters[i]->ImplementSkill_Int(m_pAllCharacters[i]->m_campFlag);
			}
			else if (m_pAllCharacters[i]->m_actionName == TEXT("ImplementDodge"))
			{
				m_pAllCharacters[i]->StopContinuousTask();
				m_pAllCharacters[i]->m_implementSkillType = 3;
				m_pAllCharacters[i]->ImplementSkill_Int(m_pAllCharacters[i]->m_campFlag);
			}
			else
			{
				if (m_pAllCharacters[i]->m_pBaseAnimInstance->m_motionStateString == "PMS_NULL" ||
					m_pAllCharacters[i]->m_pBaseAnimInstance->m_canTransferState)
				{
					if (m_pAllCharacters[i]->m_pBaseAnimInstance->m_canTransferState)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, "BattleLevelGM::UpdateCharacterNormalLogic can transfer is true");
					}
					m_pAllCharacters[i]->ImplementSkill_Int(m_pAllCharacters[i]->m_campFlag);
				}
			}
		}
		else if (m_pAllCharacters[i]->m_actionName == TEXT("CancelBlock"))
		{
			AKing* pKing = Cast<AKing>(m_pAllCharacters[i]);
			if (!pKing->m_pBlockSkill) continue;
			pKing->m_pBlockSkill->m_skillFrameCount = -1;
		}
		else if (m_pAllCharacters[i]->m_actionName == TEXT("StopContinuousPunch"))
		{
			m_pAllCharacters[i]->StopContinuousTask();
		}
		else if (m_pAllCharacters[i]->m_actionName == TEXT("Spell") && canMove == true)
		{
			m_pAllCharacters[i]->ImplementSkill_Int(m_pAllCharacters[i]->m_campFlag);
		}
		else if (m_pAllCharacters[i]->m_actionName == TEXT("CollectPhysActor") && canMove == true)
		{
			AKing* pPlayerCharacter = Cast<AKing>(m_pAllCharacters[i]);
			ABasePhysGeo* pGeo = m_pPhysCalculator->FindEntity(pPlayerCharacter->m_collectPhysOperationNb);
			if (!pGeo || !pGeo->m_pAttachEquipInfo) continue;
			UClass* equipClass = UCollisionWarBpFunctionLibrary::GetAttachEquipBlueprintClassDynamic(pGeo->m_pAttachEquipInfo->m_equipmentName);
			UCharacterEquipInfo* pEquipInfo = NewObject<UCharacterEquipInfo>(pPlayerCharacter, equipClass);
			pPlayerCharacter->m_pEquipmentInfos.Add(pEquipInfo);
			pGeo->m_isGeoValid = false;
			pPlayerCharacter->m_actionName = "NULL";
		}
		else if (m_pAllCharacters[i]->m_actionName == TEXT("ChangeEquip") && canMove == true)
		{
			if (m_pAllCharacters[i]->m_pBaseAnimInstance->m_motionStateString == "PMS_NULL")
			{
				AKing* pPlayerCharacter = Cast<AKing>(m_pAllCharacters[i]);
				pPlayerCharacter->m_curEquipNb = pPlayerCharacter->m_equipOperationNb;
				//pPlayerCharacter->ChangeEquipment(pPlayerCharacter->m_curEquipNb);
				pPlayerCharacter->m_actionName = "NULL";
				pPlayerCharacter->m_curSkillNb = 0;
				pPlayerCharacter->ImplementSkill_Int(pPlayerCharacter->m_campFlag);
			}
		}
	}
}

void ABattleLevelGameModeBase::UpdateAllDeadCharacters(float tick)
{
	int32 i = 0;
	while (i < m_pDeadCharacters.Num())
	{
		if (m_pDeadCharacters[i]->m_curDeadCount >= m_pDeadCharacters[i]->m_deadTime)
		{
			m_pDeadCharacters[i]->m_isInitialDoneFlag = false;
			if (!m_pDeadCharacters[i] || !m_pDeadCharacters[i]->IsValidLowLevel()) continue;
			m_pDeadCharacters[i]->Destroy();
			m_pDeadCharacters[i]->ConditionalBeginDestroy();
			m_pDeadCharacters.RemoveAt(i);
		}
		else
		{
			m_pDeadCharacters[i]->m_curDeadCount += tick;
			i += 1;
		}
	}
}

/*
void ABattleLevelGameModeBase::SpawnDeadCharacterFixSkill(TSubclassOf<class UObject> skillGeoClass, ABaseCharacter* pCharacter)
{
	if (!skillGeoClass || !pCharacter) return;
	int32 spawnLocX = pCharacter->m_logicPos2D.X;
	int32 spawnLocY = pCharacter->m_logicPos2D.Y;
	FVector spawnLoc(spawnLocX, spawnLocY, m_defaultSpawnHeight);
	int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(pCharacter->m_curLogicForwardDir);
	FRotator spawnRot(0, yaw, 0);
	ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(skillGeoClass, spawnLoc, spawnRot);
	pPhysGeo->m_logicPos2D = FLogicVec2D(spawnLocX, spawnLocY);
	pPhysGeo->m_logicForwardDir = pCharacter->m_curLogicForwardDir;
	pPhysGeo->m_moveType = 0;
	m_pPhysCalculator->AddPhysGeo(pPhysGeo, NULL, 0);
}*/

void ABattleLevelGameModeBase::UpdateTeamSquads()
{
	for (int32 i = 0; i < m_maxUpdateTeamNbPerFrame; i++)
	{
		if (m_curTeamAIUpdateNb >= m_pTeams.Num()) m_curTeamAIUpdateNb = 0;
		m_pTeams[m_curTeamAIUpdateNb]->CharactersFormation();
		m_curTeamAIUpdateNb++;
	}
}

void ABattleLevelGameModeBase::UpdateAllScore()
{
	/*if (!m_pPhysCalculator) return;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	for (int32 i=0; i<m_pPhysCalculator->m_tempScorePairs.Num(); i++)
	{
		for (int32 j=0; j<m_tempPlayerStatics.Num(); j++)
		{
			if (m_tempPlayerStatics[j].accountID == m_pPhysCalculator->m_tempScorePairs[i].pCharacter->m_entityID)
			{
				if (m_pPhysCalculator->m_tempScorePairs[i].scoreType == TEXT("killEnermy"))
				{
					m_tempPlayerStatics[j].killEnermyNb += 1;
				}
				else if (m_pPhysCalculator->m_tempScorePairs[i].scoreType == TEXT("outputScore"))
				{
					m_tempPlayerStatics[j].outputScore += m_pPhysCalculator->m_tempScorePairs[i].num;
				}
				break;
			}
		}
	}
	m_pPhysCalculator->m_tempScorePairs.Empty();*/
}

void ABattleLevelGameModeBase::ReadDifficultyParams()
{
	/*UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	int32 level = pCWGameInstance->m_playerSingleProgressInfos[pCWGameInstance->m_curProgressNb].characterInfo.level;

	int32 difficulty = (int32)pCWGameInstance->m_playerSingleProgressInfos[pCWGameInstance->m_curProgressNb].difficulty;
	FString difficultyString = FString::FromInt(difficulty);
	difficultyString = difficultyString.Append("-");
	difficultyString = difficultyString.Append(FString::FromInt(level));
	ReadSpecialEffectPercent(difficultyString);
	ReadAmplificationCoe(FString::FromInt(level));*/
}

void ABattleLevelGameModeBase::ReadSpecialEffectPercent_Implementation(const FString& difficultyAndLevel)
{

}

void ABattleLevelGameModeBase::ReadAmplificationCoe_Implementation(const FString& difficulty)
{

}

void ABattleLevelGameModeBase::DEBUG_FUN_Implementation(const FString& msg)
{

}
/*

void ABattleLevelGameModeBase::SpawnEnermyByGroup()
{
	if (!m_pAIManager || m_pPlanSpawnPoints.Num() == 0) return;
	int32 minHpPercent = 0;
	AKing* pMinHpPlayerCharacter = NULL;
	for (int32 i=0; i<m_pPlayerCharacters.Num(); i++)
	{
		if (!m_pPlayerCharacters[i]) continue;
		int32 hpPercent = m_pPlayerCharacters[i]->m_Hp * 100 / m_pPlayerCharacters[i]->m_originHp;
		if (i == 0 || hpPercent <= minHpPercent)
		{
			minHpPercent = hpPercent;
			pMinHpPlayerCharacter = m_pPlayerCharacters[i];
		}
	}
	if (!pMinHpPlayerCharacter) return;
	
	//每个campFlag代表一支队伍，将所有AI角色按阵营、类别进行分类
	TArray<int32> campFlags;
	TArray<FGradingExpectToSpawnInfo> expectSpawnInfoList;

	m_pAIManager->GetSpawnNameList(pMinHpPlayerCharacter->m_Hp, pMinHpPlayerCharacter->m_originHp, 
		m_curLogicFrameNb, m_maxFrameNb, expectSpawnInfoList,pMinHpPlayerCharacter->m_originCampFlag, true);
		
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);

	for (int32 i=0; i< expectSpawnInfoList.Num(); i++)
	{
		TArray<FString> spawnNameList;
		for (int32 j=0; j<expectSpawnInfoList[i].expectSpawnNameList.Num(); j++)
		{
			for (int32 k=0; k<expectSpawnInfoList[i].expectSpawnNameList[j].spawnNb; k++)
			{
				spawnNameList.Add(expectSpawnInfoList[i].expectSpawnNameList[j].characterName);
			}
		}
		//对将要生成的角色进行特殊状态赋值，例如加火属性得益效果、无敌或劈砍衰弱等特殊效果。
		TMap<int32, FPreAssignEffectList> assignSpecialStateList;
		m_pAIManager->AssignSpecialEffectToCharacters(spawnNameList, assignSpecialStateList);
		//生成角色，同时将特殊效果赋值给对应的角色
		for (int32 j = 0; j < spawnNameList.Num(); j++)
		{
			int32 newID = GetAnUnOccupyID();
			if (newID == -1) return;
			UClass* characterBP = UCollisionWarBpFunctionLibrary::GetCharacterBlueprintClassDynamic(spawnNameList[j]);
			FLogicVec2D logicSpawnLoc;
			int32 spawnYaw;

			int32 randPlanSpawnPointNb = FMath::RandRange(0, m_pPlanSpawnPoints.Num()-1);
			int32 randLocInSpawnPointX = FMath::RandRange(-m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnPointWidth, m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnPointWidth);
			int32 randLocInSpawnPointY = FMath::RandRange(-m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnPointWidth, m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnPointWidth);
			logicSpawnLoc = m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnPointLoc + FLogicVec2D(randLocInSpawnPointX, randLocInSpawnPointY);
			spawnYaw = m_pPlanSpawnPoints[randPlanSpawnPointNb]->m_spawnYaw;

			FVector spawnLoc(logicSpawnLoc.X, logicSpawnLoc.Y, m_defaultSpawnHeight);
			FRotator spawnRot(0, spawnYaw, 0);
			ABaseCharacter* pCharacter = GetWorld()->SpawnActor<ABaseCharacter>(characterBP, spawnLoc, spawnRot);
			ModifyCharacterProByLevel(pCharacter, m_pPlayerCharacter->m_level);
			InitialNewCharacter(pCharacter, expectSpawnInfoList[i].campFlag, newID, logicSpawnLoc, false);
			//看指定特殊效果的号码队列里是否包含当前序号，如包含说明该名角色是有对应的特殊效果的，对其赋值
			if (assignSpecialStateList.Contains(j) && m_pPhysCalculator)
			{
				for (int32 k = 0; k < assignSpecialStateList[j].list.Num(); k++)
				{
					m_pPhysCalculator->AddPermenantEffectOnCharacter(assignSpecialStateList[j].list[k], pCharacter);
				}
			}
			/ *UWidgetBlueprintFunctionLibrary::AddEnermyInfoToBattleMenu(pCharacter->m_characterRace, pCharacter->m_characterClassName,
				pCharacter->m_stateNames, pBLPC->m_pBattleMenu);* /
		}
	}
}*/

void ABattleLevelGameModeBase::InitialNewCharacter(ABaseCharacter* pCharacter, int32 campFlag, int32& characterID, FLogicVec2D logicSpawnLoc, bool isAlreadyAssignID)
{
	//还要初始化logicLoc和logicForwardDir
	pCharacter->NotifySetCharacterInfoWidget();
	pCharacter->m_pCharacterInfoWidget->NotifyInitial();
	pCharacter->m_pCharacterInfoWidget->InitialHpBar();
	pCharacter->m_campFlag = campFlag;
	pCharacter->m_originCampFlag = campFlag;
	if (!isAlreadyAssignID)
	{
		if (pCharacter->m_characterType == 1) pCharacter->m_entityID = characterID;
		else
		{
			while (FindCharacterEntity(characterID))
			{
				characterID += 1;
			}
			pCharacter->m_entityID = characterID;
			m_occupyIDs.Add(characterID);
		}
	}
	pCharacter->m_Hp = pCharacter->m_originHp;
	pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	pCharacter->m_defaultHeight = m_defaultSpawnHeight;
	pCharacter->SetActorLocation(FVector(logicSpawnLoc.X, logicSpawnLoc.Y, m_defaultSpawnHeight + pCharacter->m_relativeHeight));
	/*FLogicVec2D forwardDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(logicSpawnYaw);
	pCharacter->m_curLogicForwardDir = forwardDir;*/

	//将角色加入到对应的Team中
	bool isFoundCorrespondTeam = false;
	for (int32 i=0; i<m_pTeams.Num(); i++)
	{
		if (m_pTeams[i]->m_campFlag == campFlag)
		{
			m_pTeams[i]->m_pCharacters.Add(pCharacter);
			isFoundCorrespondTeam = true;
			break;
		}
	}
	if (!isFoundCorrespondTeam)
	{
		ATeam* pNewTeam = GetWorld()->SpawnActor<ATeam>(m_BPTeamClass, FVector::ZeroVector, FRotator::ZeroRotator);
		pNewTeam->m_campFlag = campFlag;
		pNewTeam->m_pCharacters.Add(pCharacter);
		m_pTeams.Add(pNewTeam);
	}

	pCharacter->InitialCharacterAnim();

	//初始化角色之间的相互引用
	for (int32 i=0; i<m_pAllCharacters.Num(); i++)
	{
		if (m_pAllCharacters[i]->m_originCampFlag != campFlag)
		{
			pCharacter->m_pOppCharacters.Add(m_pAllCharacters[i]);
			m_pAllCharacters[i]->m_pOppCharacters.Add(pCharacter);
		}
		else
		{
			pCharacter->m_pMyCharacters.Add(m_pAllCharacters[i]);
			m_pAllCharacters[i]->m_pMyCharacters.Add(pCharacter);
		}
	}

	//将角色加入到PhysCalculator中
	m_pPhysCalculator->AddPlayerToList(pCharacter);

	//将角色加入到各种引用队列中
	m_pAllCharacters.Add(pCharacter);
	if (pCharacter->m_characterType == 0)
	{
		m_pAICharacters.Add(pCharacter);
	}
	else
	{
		AKing* pKing = Cast<AKing>(pCharacter);
		m_pPlayerCharacters.Add(pKing);
	}
	
	//如是AI角色，初始化AI
	if (pCharacter->m_characterType == 0 || pCharacter->m_characterType == 2)
	{
		pCharacter->m_pNormalLongTask = NewObject<UTask>();
		pCharacter->m_pNormalShortTask = NewObject<UTask>();
	}

	//将角色加入到AINavigation中
	m_pRecastDetourObject->HandleAddAgent_Int(pCharacter->GetActorLocation(), pCharacter->m_entityID, pCharacter->m_characterType,
		pCharacter->m_characterRadius, pCharacter->m_characterHeight, pCharacter->m_MaxSPD, pCharacter->m_acc);

	pCharacter->m_isInitialDoneFlag = true;
	pCharacter->ReadSkillIndependentFXInfo();
	pCharacter->InitialCharacterDone();
}

void ABattleLevelGameModeBase::RemoveCharacterFromGame(ABaseCharacter* pCharacter)
{
	//将角色从对应的Team中删除
	for (int32 i=0; i<m_pTeams.Num(); i++)
	{
		if (pCharacter->m_originCampFlag == m_pTeams[i]->m_campFlag)
		{
			m_pTeams[i]->m_pCharacters.Remove(pCharacter);
			break;
		}
	}
	//取消角色之间的相互引用
	TArray<FString> stateNamesExcludeDeleteCharacter;
	for (int32 i = 0; i < m_pAllCharacters.Num(); i++)
	{
		if (m_pAllCharacters[i]->m_originCampFlag != pCharacter->m_originCampFlag)
			m_pAllCharacters[i]->m_pOppCharacters.Remove(pCharacter);
		else
			m_pAllCharacters[i]->m_pMyCharacters.Remove(pCharacter);
		if (m_pAllCharacters[i]->m_characterClassName != pCharacter->m_characterClassName || m_pAllCharacters[i] == pCharacter) continue;
		for (int32 j=0; j< m_pAllCharacters[i]->m_stateNames.Num(); j++)
		{
			if (stateNamesExcludeDeleteCharacter.Contains(m_pAllCharacters[i]->m_stateNames[j])) continue;
			stateNamesExcludeDeleteCharacter.Add(m_pAllCharacters[i]->m_stateNames[j]);
		}
	}
	//将角色从PhysCalculator中删除
	m_pPhysCalculator->m_pCharacterList.Remove(pCharacter);
	//将角色从各种引用队列中删除
	m_pAllCharacters.Remove(pCharacter);
	if (pCharacter->m_characterType == 0)
	{
		int32 characterNb = m_pAICharacters.Find(pCharacter);
		if (characterNb != INDEX_NONE && characterNb != 0 && characterNb <= m_curAIUpdateNb) m_curAIUpdateNb -= 1;
		m_pAICharacters.Remove(pCharacter);
	}
	else
	{
		AKing* pKing = Cast<AKing>(pCharacter);
		m_pPlayerCharacters.Remove(pKing);
	}
	//将角色从AINavigation中删除
	m_pRecastDetourObject->HandleDeleteAgent(pCharacter->m_entityID, pCharacter->m_characterType);

	pCharacter->NotifyAnimCharacterDead();

	m_pDeadCharacters.Add(pCharacter);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	/*UWidgetBlueprintFunctionLibrary::RemoveEnermyCardInfoFromBattleMenu(pCharacter->m_characterClassName, pCharacter->m_stateNames,
		stateNamesExcludeDeleteCharacter, pBLPC->m_pBattleMenu);*/
	/*pCharacter->m_isInitialDoneFlag = false;
	if (!pCharacter || !pCharacter->IsValidLowLevel()) return;
	pCharacter->Destroy();
	pCharacter->ConditionalBeginDestroy();*/
}

AKing* ABattleLevelGameModeBase::FindPlayerCharacterEntity(int32 entityID)
{
	for (int32 i=0; i<m_pPlayerCharacters.Num(); i++)
	{
		if (m_pPlayerCharacters[i]->m_entityID == entityID)
			return m_pPlayerCharacters[i];
	}
	return NULL;
}

ABaseCharacter* ABattleLevelGameModeBase::FindAICharacterEntity(int32 entityID)
{
	for (int32 i = 0; i < m_pAICharacters.Num(); i++)
	{
		if (m_pAICharacters[i]->m_entityID == entityID)
			return m_pAICharacters[i];
	}
	return NULL;
}

ABaseCharacter* ABattleLevelGameModeBase::FindCharacterEntity(int32 entityID)
{
	for (int32 i = 0; i < m_pAllCharacters.Num(); i++)
	{
		if (m_pAllCharacters[i]->m_entityID == entityID)
			return m_pAllCharacters[i];
	}
	return NULL;
}

int32 ABattleLevelGameModeBase::GetAnUnOccupyID()
{
	int32 i = 1;
	while (true)
	{
		if (i >= 2147483647) return -1;
		if (m_occupyIDs.Contains(i)) i++;
		else
		{
			m_occupyIDs.Add(i);
			return i;
		}
	}
}

void ABattleLevelGameModeBase::SpawnPhysGeo()
{
	if (!m_pPhysCalculator) return;
	for (int32 i = 0; i < m_originPhysActorSpawnList.values.Num(); i++)
	{
		if (m_originPhysActorSpawnList.values[i].spawnFrames.Num() == 0) continue;
		for (int32 j=0; j<m_originPhysActorSpawnList.values[i].spawnFrames.Num(); j++)
		{
			if (m_curLogicFrameNb != m_originPhysActorSpawnList.values[i].spawnFrames[j]) continue;
			//UClass* BPClass = UCollisionWarBpFunctionLibrary::GetPhysGeoBlueprintClassDynamic(m_originPhysActorSpawnList.values[i].physActorName);
			if (!m_pCWSingleton->m_physGeoClassMap.Contains(m_originPhysActorSpawnList.values[i].physActorName)) continue;
			int32 spawnLocX = m_originPhysActorSpawnList.values[i].positionX;
			int32 spawnLocY = m_originPhysActorSpawnList.values[i].positionY;
			FVector spawnLoc(spawnLocX, spawnLocY, 0);
			FRotator spawnRot(0, m_originPhysActorSpawnList.values[i].yaw, 0);
			//FLogicVec2D logicDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(m_originPhysActorSpawnList.values[i].yaw);
			ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_pCWSingleton->m_physGeoClassMap[m_originPhysActorSpawnList.values[i].physActorName], spawnLoc, spawnRot);
			//pPhysGeo->m_logicForwardDir = logicDir;
			pPhysGeo->m_moveType = m_originPhysActorSpawnList.values[i].moveType;
			m_pPhysCalculator->AddPhysGeo(pPhysGeo, NULL, 0);
			pPhysGeo->m_hierachy = 0;
		}
	}
}

void ABattleLevelGameModeBase::ClearAllDeadCharacters()
{
	while (m_pDeadCharacters.Num() > 0)
	{
		ABaseCharacter* pLastDeadCharacter = m_pDeadCharacters.Last();
		m_occupyIDs.Remove(pLastDeadCharacter->m_entityID);
		m_pDeadCharacters.Pop();
		pLastDeadCharacter->m_isInitialDoneFlag = false;
		if (!pLastDeadCharacter || !pLastDeadCharacter->IsValidLowLevel()) return;
		pLastDeadCharacter->Destroy();
		pLastDeadCharacter->ConditionalBeginDestroy();
	}
}

void ABattleLevelGameModeBase::DeleteTutorialStep()
{
	m_tutorialSteps.RemoveAt(0);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (m_pTutorialIndicator && m_pTutorialIndicator->IsValidLowLevel())
	{
		m_pTutorialIndicator->Destroy();
		m_pTutorialIndicator->ConditionalBeginDestroy();
	}
	while (pBLPC->m_pTutorialIndicators.Num() > 0)
	{
		if (!pBLPC->m_pTutorialIndicators.Last())
		{
			pBLPC->m_pTutorialIndicators.Pop();
			continue;
		}
		pBLPC->m_pTutorialIndicators.Last()->RemoveFromParent();
		if (pBLPC->m_pTutorialIndicators.Last()->IsValidLowLevel())
		{
			pBLPC->m_pTutorialIndicators.Last()->ConditionalBeginDestroy();
		}
		pBLPC->m_pTutorialIndicators.Pop();
	}
	if (m_tutorialSteps.Num() <= 0)
	{
		pBLPC->m_pTutorialMenu->NotifyFadeOut();
		return;
	}
	pBLPC->NotifySpawnMenuTutorIndicator(m_tutorialSteps[0].operationName);
	if (pBLPC->m_pTutorialMenu)
	{
		if (pBLPC->m_pTutorialMenu->m_pWidgetManager->m_language == "Chinese")
			pBLPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].chExplanation));
		else
			pBLPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].enExplanation));
	}
	if (m_tutorialSteps[0].isSpawnIndicator)
	{
		FString spawnIndicatorActorType = m_tutorialSteps[0].spawnIndicationActorName.Left(2);
		FString spawnIndicatorActorName = m_tutorialSteps[0].spawnIndicationActorName.RightChop(3);
		//TArray<AActor*> pAllActors;
		AActor* pTargetActor = NULL;
		if (spawnIndicatorActorType == "EC")
		{
			//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActionCard::StaticClass(), pAllActors);
			for (int32 i = 0; i < m_pAICharacters.Num(); i++)
			{
				if (!m_pAICharacters[i] || m_pAICharacters[i]->m_characterClassName != spawnIndicatorActorName) continue;
				pTargetActor = m_pAICharacters[i];
				break;
			}
		}

		if (!pTargetActor) return;
		FVector indicatorLoc = pTargetActor->GetActorLocation() + m_tutorialSteps[0].indicatorRelativeLoc;
		m_pTutorialIndicator = GetWorld()->SpawnActor<AActor>(m_tutorialIndicatorClass, indicatorLoc, FRotator::ZeroRotator);
		NotifyIndicatorShowUp();
	}
}

void ABattleLevelGameModeBase::NotifyIndicatorShowUp_Implementation()
{

}

int32 ABattleLevelGameModeBase::GenRandNumber(int32 min, int32 max)
{
	if (min >= max) return min;
	int32 interval = max - min;
	int32 randNb = (m_randMul*m_curRandSeed + m_randAdd) % m_randMod;
	m_curRandSeed = randNb;
	int32 randMod = randNb % interval;
	return (randMod + min);
}

void ABattleLevelGameModeBase::ModifyCharacterProByLevel(ABaseCharacter* pCharacter, const int32& level)
{
	if (level < 1) return;
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	if (pCharacter->m_characterType == 0)
	{
		pCharacter->m_originHp = pCharacter->m_originHp * FMath::Pow(pSingleton->m_enermyHpRollRate, level - 1);
		pCharacter->m_Hp = pCharacter->m_originHp;
		pCharacter->m_ATK = pCharacter->m_ATK * FMath::Pow(pSingleton->m_enermyAtkRollRate, level - 1);
		pCharacter->m_magATK = pCharacter->m_magATK * FMath::Pow(pSingleton->m_enermyAtkRollRate, level - 1);
		pCharacter->m_DFC = pCharacter->m_DFC * FMath::Pow(pSingleton->m_enermyDfcRollRate, level - 1);
		//pCharacter->m_magDFC = pCharacter->m_magDFC * FMath::Pow(pSingleton->m_enermyDfcRollRate, level - 1);
	}
	else if (pCharacter->m_characterType == 1)
	{
		pCharacter->m_originHp = pCharacter->m_originHp * FMath::Pow(pSingleton->m_playerHpRollRate, level - 1);
		pCharacter->m_Hp = pCharacter->m_originHp;
		pCharacter->m_ATK = pCharacter->m_ATK * FMath::Pow(pSingleton->m_playerAtkRollRate, level - 1);
		pCharacter->m_magATK = pCharacter->m_magATK * FMath::Pow(pSingleton->m_playerAtkRollRate, level - 1);
		pCharacter->m_DFC = pCharacter->m_DFC * FMath::Pow(pSingleton->m_playerDfcRollRate, level - 1);
		//pCharacter->m_magDFC = pCharacter->m_magDFC * FMath::Pow(pSingleton->m_playerDfcRollRate, level - 1);
	}
}

void ABattleLevelGameModeBase::RecoverPlayerPerInterval()
{
	if (!m_pPlayerCharacter || m_pPlayerCharacter->m_Hp <= 0) return;
	if (m_recoverIntervalTickCount < m_recoverInterval)
	{
		m_recoverIntervalTickCount += 1;
		return;
	}
	m_recoverIntervalTickCount = 0;
	int32 recoverHp = m_pPlayerCharacter->m_originHp * m_playerRecoverPercent / 100;
	int32 curHp = m_pPlayerCharacter->m_Hp + recoverHp;
	if (curHp >= m_pPlayerCharacter->m_originHp) m_pPlayerCharacter->m_Hp = m_pPlayerCharacter->m_originHp;
	else m_pPlayerCharacter->m_Hp = curHp;
}

void ABattleLevelGameModeBase::ReadCharacterHurtScoreLevels_Implementation()
{

}

void ABattleLevelGameModeBase::RecordAllScores(TArray<ABaseCharacter*> pAllDeadCharacters)
{

}

void ABattleLevelGameModeBase::ReadEquipmentClass_Implementation()
{

}

