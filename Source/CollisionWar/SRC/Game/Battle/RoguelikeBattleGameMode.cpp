// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Base/Battle/BattleLevelPlayerController.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../../Common/EventSystemFunLib.h"
#include "../../Common/EffectFunLib.h"
#include "Engine/KBEngine.h"
#include "WidgetTree.h"
#include "../../Base/Widget/TFCInfo.h"
#include "RoguelikeBattleGameMode.h"




ARoguelikeBattleGameMode::ARoguelikeBattleGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ARoguelikeBattleGameMode::BeginPlay()
{
	/*if (m_BPLuaActorClass)
	{
		m_pLuaActor = GetWorld()->SpawnActor<ALuaActor>(m_BPLuaActorClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	}*/
	//check(KBEngineApp::getSingleton().isInitialized());
	m_pCWSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	TellBPBeginPlay();
	m_tickFlag = true;
	
}

void ARoguelikeBattleGameMode::Destroyed()
{
	Super::Destroyed();
}

void ARoguelikeBattleGameMode::Tick(float DeltaSeconds)
{
	if (!m_pCWSingleton) return;
	if (!m_hasAsyncLoadDone)
	{
		if (!m_hasApplyAsyncLoad)
		{
			m_pCWSingleton->ReqAsynLoad(0);
			m_pCWSingleton->ReqAsynLoad(1);
			m_pCWSingleton->ReqAsynLoad(2);
			m_pCWSingleton->ReqAsynLoad(3);
			m_hasApplyAsyncLoad = true;
		}
		if (m_pCWSingleton->m_asyncLoadStateDone.Num() >= 4)
		{
			m_hasAsyncLoadDone = true;
			InitialLevel();
			m_tickFlag = true;
		}
	}


	if (!m_tickFlag) return;
	//Super::Tick(DeltaSeconds);
	UpdateAllDeadCharacters(DeltaSeconds);

	if (m_isFading || !m_isStart) return;

	float tickInterval = (float)(m_logicExpandTickTimeDelta) / 1000.f;
	m_curTickInterval += DeltaSeconds;
	if (m_curTickInterval < tickInterval) return;
	m_curTickInterval = 0.f;

	TriggerAllEventCards();
	//更新实际逻辑模块
	//如存在多个逻辑帧，说明逻辑帧有积压，将所有积压下来的逻辑帧运算完毕
	if (m_pAIManager)
	{
		if (m_pAIManager->m_battleInfo.updateEnermyType == 1 || (m_pAIManager->m_battleInfo.updateEnermyType == 0 && m_pAIManager->m_curRoundNb == 0))
		{
			if (m_pAIManager->m_peakCount < m_pAIManager->m_peakIntervalList.Num() && !m_isInTutorial)
			{
				SpawnEnermyByGroup();
				m_pAIManager->m_curRoundNb += 1;
			}
		}
		else
		{
			if (m_pAIManager->m_curRoundEnermyNb <= 0)
				SpawnEnermyByGroup();
		}
	}
	UpdateCharacterActionInstruction(m_playerOperation, m_AIOperationList);
	CollectAllDeadCharacters();
	UpdateCharacterNormalLogic(DeltaSeconds);
	m_pPhysCalculator->CollectAllNewPhysGeos();
	m_pPhysCalculator->UpdateAllPhysGeos();
	m_pPhysCalculator->UpdateBindPS();
	m_pPhysCalculator->CalGeoReactions();
	//m_pPhysCalculator->UpdateReactionGeoPair();


	UpdateAllCharacterAILogic(DeltaSeconds);
	UpdateTeamSquads();
	UpdateAINavigation();
	//RCDebug();
	UpdateAICharacterOperation();

	DealEventList();
	
	uint8 victoryFlag = UpdateVictoryCheck();
	if (victoryFlag == 2 || victoryFlag == 1 || m_isBattleTestFinish)
	{
		m_tickFlag = false;
		if (m_isBattleTestFinish)
		{
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			pCWGI->m_battleState = 1;
			NotifyWinLose(1);
		}
		else
		{
			NotifyWinLose(victoryFlag);
		}
	}

	UpdateFrameDemonstration();

	m_curLogicFrameNb += 1;
}

UClass* ARoguelikeBattleGameMode::ReadSpawnPointBPDynamic_Implementation(const FString& className)
{
	return NULL;
}

void ARoguelikeBattleGameMode::GenRogueMap(const TArray<FString>& specifiedLandBlockList)
{
	if (!m_pMapGenerator || !m_pPhysCalculator) return;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	m_pMapGenerator->InitialMapGeneratorFromBlueprint(pCWGI->m_curPlayerSPInfo.curProgress);
	m_pMapGenerator->GenerateRandomMap(specifiedLandBlockList);
	m_pMapGenerator->ReadRoguelikeSMMap();
	for (int32 i = 0; i < m_pMapGenerator->m_pTiles.Num(); i++)
	{
		for (int32 j = 0; j < m_pMapGenerator->m_pTiles[i]->m_physActorNames.Num(); j++)
		{
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].Y, m_defaultSpawnHeight);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_physActorSpawnYaws[j], 0);
			//UClass* geoClass = UCollisionWarBpFunctionLibrary::GetPhysGeoBlueprintClassDynamic(m_pMapGenerator->m_pTiles[i]->m_physActorNames[j]);
			if (!m_pCWSingleton->m_physGeoClassMap.Contains(m_pMapGenerator->m_pTiles[i]->m_physActorNames[j])) continue;
			ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_pCWSingleton->m_physGeoClassMap[m_pMapGenerator->m_pTiles[i]->m_physActorNames[j]], spawnLoc, spawnRot);
			//pGeo->m_logicPos2D = FLogicVec2D(m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].X, m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].Y);
			/*FLogicVec2D logicDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(m_pMapGenerator->m_pTiles[i]->m_physActorSpawnYaws[j]);
			pGeo->m_logicForwardDir = logicDir;*/
			m_pPhysCalculator->AddPhysGeo(pGeo, NULL, 0);
			pGeo->m_hierachy = 0;
			FVector relativeLoc(m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_physActorSpawnLocInWorldSpace[j].Y, pGeo->m_defaultHeight + pGeo->m_relativeHeight);
			pGeo->SetActorLocation(relativeLoc);
		}
		for (int32 j = 0; j < m_pMapGenerator->m_pTiles[i]->m_dumpActorNames.Num(); j++)
		{
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].Y, m_defaultSpawnHeight);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnYaws[j], 0);
			//UClass* geoClass = UCollisionWarBpFunctionLibrary::GetDumpActorBlueprintClassDynamic(m_pMapGenerator->m_pTiles[i]->m_dumpActorNames[j]);
			if (!m_pCWSingleton->m_dumpActorClassMap.Contains(m_pMapGenerator->m_pTiles[i]->m_dumpActorNames[j])) continue;
			ADumpPhysActor* pGeo = GetWorld()->SpawnActor<ADumpPhysActor>(m_pCWSingleton->m_dumpActorClassMap[m_pMapGenerator->m_pTiles[i]->m_dumpActorNames[j]], spawnLoc, spawnRot);
			pGeo->InitialDumpActor();
			//pGeo->m_logicPos2D = FLogicVec2D(m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].X, m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].Y);
			/*FLogicVec2D logicDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnYaws[j]);
			pGeo->m_logicForwardDir = logicDir;*/
			FVector relativeLoc(m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_dumpActorSpawnLocInWorldSpace[j].Y, m_defaultSpawnHeight + pGeo->m_relativeHeight);
			pGeo->SetActorLocation(relativeLoc);
		}
		for (int32 j = 0; j < m_pMapGenerator->m_pTiles[i]->m_planSpawnPointNames.Num(); j++)
		{
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_planSpawnPointLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_planSpawnPointLocInWorldSpace[j].Y, m_defaultSpawnHeight);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_planSpawnPointYaws[j], 0);
			//UClass* spawnPointClass = UCollisionWarBpFunctionLibrary::GetPlanSpawnPointBlueprintClassDynamic(m_pMapGenerator->m_pTiles[i]->m_planSpawnPointNames[j]);
			UClass* spawnPointClass = ReadSpawnPointBPDynamic(m_pMapGenerator->m_pTiles[i]->m_planSpawnPointNames[j]);
			APlanSpawnPoint* pPlanSpawnPoint = GetWorld()->SpawnActor<APlanSpawnPoint>(spawnPointClass, spawnLoc, spawnRot);
			pPlanSpawnPoint->m_spawnPointLoc = m_pMapGenerator->m_pTiles[i]->m_planSpawnPointLocInWorldSpace[j];
			pPlanSpawnPoint->m_spawnYaw = m_pMapGenerator->m_pTiles[i]->m_planSpawnPointYaws[j];
			m_pPlanSpawnPoints.Add(pPlanSpawnPoint);
			m_pMapGenerator->m_pTiles[i]->m_pSpawnPoints.Add(pPlanSpawnPoint);
		}
		for (int32 j = 0; j < m_pMapGenerator->m_pTiles[i]->m_staticMeshActorNameList.Num(); j++)
		{
			if (!m_pMapGenerator->m_pAllLandBlockSMs.Contains(m_pMapGenerator->m_pTiles[i]->m_staticMeshActorNameList[j])) continue;
			FVector spawnLoc(m_pMapGenerator->m_pTiles[i]->m_staticMeshLocInWorldSpace[j].X,
				m_pMapGenerator->m_pTiles[i]->m_staticMeshLocInWorldSpace[j].Y, m_pMapGenerator->m_pTiles[i]->m_staticMeshLocs[j].Z);
			FRotator spawnRot(0, m_pMapGenerator->m_pTiles[i]->m_staticMeshYaws[j], 0);

			UStaticMesh* pStaticMesh = m_pMapGenerator->m_pAllLandBlockSMs[m_pMapGenerator->m_pTiles[i]->m_staticMeshActorNameList[j]];
			AStaticMeshActor* pStaticMeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), spawnLoc, spawnRot);
			pStaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(pStaticMesh);
			pStaticMeshActor->GetStaticMeshComponent()->ComponentTags.Add(FName("SMActor"));
			FVector staticMeshScale(m_pMapGenerator->m_pTiles[i]->m_staticMeshScales[j]);
			pStaticMeshActor->GetStaticMeshComponent()->SetWorldScale3D(staticMeshScale);
		}
	}
}

void ARoguelikeBattleGameMode::UpdateCharacterActionInstruction(const FPlayerOperationInfo& playerOperation, const TArray<FAICharacterOperationInfo>& aiCharacterOperations)
{
	for (int32 i = 0; i < aiCharacterOperations.Num(); i++)
	{
		ABaseCharacter* pCharacter = NULL;
		pCharacter = FindAICharacterEntity(aiCharacterOperations[i].entityID);
		if (!pCharacter) continue;
		//如果是NULL，直接赋值
		//如果是TransientPunch，可以预先修改actionName，等TransientPunch结束后再立刻执行新的任务
		//如果是ContinuousPunch或RepeatPunch，如skillname与现skillname一致，说明运动状态不用变
		if ((pCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_ContinuousPunch" ||
			pCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_RepeatPunch")
			&&
			aiCharacterOperations[i].actionName == "ImplementSkill" &&
			aiCharacterOperations[i].skillNb == pCharacter->m_curSkillNb)
		{
			pCharacter->m_actionName = "NULL";
		}
		else pCharacter->m_actionName = aiCharacterOperations[i].actionName;
		pCharacter->m_skillOperationNb = aiCharacterOperations[i].skillNb;
		FLogicVec2D forwardVec = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(aiCharacterOperations[i].yaw);
		pCharacter->m_logicForwardOperation.X = forwardVec.X;
		pCharacter->m_logicForwardOperation.Y = forwardVec.Y;
		pCharacter->m_logicVelOperation.X = aiCharacterOperations[i].velocityX;
		pCharacter->m_logicVelOperation.Y = aiCharacterOperations[i].velocityY;
		pCharacter->m_targetLoc = aiCharacterOperations[i].targetLoc;
	}
	//更新玩家部分
	if (m_pPlayerCharacter)
	{
		if (playerOperation.actionName == "ImplementSkill" ||
			playerOperation.actionName == "Spell" ||
			playerOperation.actionName == "CollectPhysActor" ||
			playerOperation.actionName == "ImplementSpellSkill" ||
			playerOperation.actionName == "BuildWorkShop" ||
			playerOperation.actionName == "ImplementBlock" ||
			playerOperation.actionName == "ImplementDodge")
		{
			if (m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString != "PMS_NULL" && 
				!m_pPlayerCharacter->m_pBaseAnimInstance->m_canTransferState)
				m_pPlayerCharacter->m_actionName = "NULL";
			else
			{
				if (m_pPlayerCharacter->m_pBaseAnimInstance->m_canTransferState)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "RoguelikeGM::UpdateCharacterActionInstruction can transfer is true");
				}
				m_pPlayerCharacter->m_actionName = playerOperation.actionName;
			}
		}
		else if (playerOperation.actionName == "CancelBlock" && m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_Block")
		{
			m_pPlayerCharacter->m_actionName = playerOperation.actionName;
		}
		else if (m_pPlayerCharacter->m_actionName == TEXT("ChangeEquip"))
		{
			m_pPlayerCharacter->m_actionName = playerOperation.actionName;
		}
		else if (playerOperation.actionName == "StopContinuousPunch")
		{
			if (m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString != "PMS_ContinuousPunch"&&
				m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString != "PMS_RepeatPunch" &&
				m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString != "PMS_Spell")
				m_pPlayerCharacter->m_actionName = "NULL";
			else m_pPlayerCharacter->m_actionName = playerOperation.actionName;
		}
		else m_pPlayerCharacter->m_actionName = playerOperation.actionName;
		m_pPlayerCharacter->m_equipOperationNb = playerOperation.equipmentNb;
		m_pPlayerCharacter->m_skillOperationNb = playerOperation.skillNb;
		m_pPlayerCharacter->m_targetLoc = playerOperation.skillClickLoc;
		m_pPlayerCharacter->m_collectPhysOperationNb = playerOperation.collectPhysID;
		FLogicVec2D forwardVec = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(playerOperation.yaw);
		m_pPlayerCharacter->m_logicForwardOperation.X = forwardVec.X;
		m_pPlayerCharacter->m_logicForwardOperation.Y = forwardVec.Y;
		m_pPlayerCharacter->m_logicVelOperation.X = playerOperation.velocityX;
		m_pPlayerCharacter->m_logicVelOperation.Y = playerOperation.velocityY;
	}
	m_playerOperation.actionName = "NULL";
	m_playerOperation.collectPhysID = -1;
	m_playerOperation.equipmentNb = 0;
	m_playerOperation.skillNb = 0;
	m_playerOperation.spellSkillNb = 0;
	m_AIOperationList.Empty();
}

void ARoguelikeBattleGameMode::UpdateAllCharacterAILogic(float deltaT)
{
	if (m_pAICharacters.Num() == 0 || m_isInTutorial) return;
	for (int32 i = 0; i < m_pAICharacters.Num(); i++)
	{
		m_pAICharacters[i]->m_surviveTime += 1;
		m_pAICharacters[i]->EvaluateConditionAround(deltaT);
	}
}

void ARoguelikeBattleGameMode::UpdateTeamSquads()
{
	for (int32 i = 0; i < m_pTeams.Num(); i++)
	{
		m_pTeams[i]->CharactersFormation();
	}
}

void ARoguelikeBattleGameMode::UpdateAICharacterOperation()
{
	for (int32 i = 0; i < m_pAICharacters.Num(); i++)
	{
		if (!m_pAICharacters[i] || !m_pAICharacters[i]->m_pNormalLongTask || !m_pAICharacters[i]->m_pNormalShortTask) continue;

		bool wantToAimCharacter = false;
		//operationRotateDir就是目标朝向
		FVector2D operationRotateDir(0, 0);

		if (m_pAICharacters[i]->m_pNormalLongTask && m_pAICharacters[i]->HasReachCurDes_Int(m_pAICharacters[i]->m_pNormalLongTask->m_destination))
			m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity = FVector2D(0, 0);
		else
		{
			m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity.Normalize();
			m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity *= m_pAICharacters[i]->m_MaxSPD;
			//m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity, m_pAICharacters[i]->m_MaxSPD);
		}

		if (m_pAICharacters[i]->m_pNormalShortTask && m_pAICharacters[i]->m_pNormalShortTask->m_pTarget)
		{
			FVector offset = m_pAICharacters[i]->m_pNormalShortTask->m_pTarget->GetActorLocation() - m_pAICharacters[i]->GetActorLocation();
			operationRotateDir.X = offset.X;
			operationRotateDir.Y = offset.Y;
			wantToAimCharacter = true;
		}
		else
		{
			if (m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity.X == 0 && m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity.Y == 0)
			{
				FVector forwardVec = m_pAICharacters[i]->GetActorForwardVector();
				operationRotateDir.X = forwardVec.X;
				operationRotateDir.Y = forwardVec.Y;
			}
			else
			{
				operationRotateDir = m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity;
			}
		}

		//求出世界坐标下的目标朝向角度，用来赋值给NormalLongTask，再赋值给操作信息
		float yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(operationRotateDir);


		m_pAICharacters[i]->m_pNormalLongTask->m_evaYaw = yaw;

		bool isAimToTarget = false;
		if (wantToAimCharacter)
		{
			FVector curForwardVec = m_pAICharacters[i]->GetActorForwardVector();
			FVector2D curForwardVec2D(curForwardVec.X, curForwardVec.Y);
			float angle = UCollisionWarBpFunctionLibrary::GetExpandCosAngleOfTwoVector(operationRotateDir, curForwardVec2D);
			//int32 alpha = UCollisionWarBpFunctionLibrary::LogicACos(expandCosAlpha);
			if (angle <= 1) isAimToTarget = true;
			else isAimToTarget = false;
		}

		if (m_pAICharacters[i]->m_pNormalShortTask->m_evaluateActionName == TEXT("ImplementSkill") && !isAimToTarget)
			m_pAICharacters[i]->m_pNormalShortTask->m_evaluateActionName = TEXT("NULL");


		FAICharacterOperationInfo newInfo;
		//常规变量，每帧上传
		newInfo.yaw = m_pAICharacters[i]->m_pNormalLongTask->m_evaYaw;
		newInfo.velocityX = m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity.X;
		newInfo.velocityY = m_pAICharacters[i]->m_pNormalLongTask->m_evaLogicVelocity.Y;
		newInfo.entityID = m_pAICharacters[i]->m_entityID;
		if (m_pAICharacters[i]->m_pNormalShortTask->m_pTarget)
			newInfo.targetLoc = m_pAICharacters[i]->m_pNormalShortTask->m_pTarget->GetActorLocation();
		//任务评估变量，只有当有更新时才上传
		if ((wantToAimCharacter && !isAimToTarget) || !m_pAICharacters[i]->m_hasUpdateAI)
		{
			newInfo.actionName = "NULL";
			newInfo.skillNb = -1;
		}
		else
		{
			newInfo.actionName = m_pAICharacters[i]->m_pNormalShortTask->m_evaluateActionName;
			newInfo.skillNb = m_pAICharacters[i]->m_pNormalShortTask->m_evaSkillNb;
			m_pAICharacters[i]->m_hasUpdateAI = false;
		}
		//保护
		if (newInfo.actionName == "") newInfo.actionName == "NULL";
		m_AIOperationList.Add(newInfo);
	}
}

uint8 ARoguelikeBattleGameMode::UpdateVictoryCheck()
{
	/** victoryFlag标记三个状态
	* 0 = 正常状态
	* 1 = 胜
	* 2 = 负
	*/
	uint8 victoryFlag = 0;
	if (m_isInTutorial)
	{
		if (m_pPlayerCharacter->m_Hp <= 0) victoryFlag = 2;
		else if (m_tutorialSteps.Num() <= 0 || m_curLogicFrameNb >= m_pAIManager->m_battleInfo.maxFrame)
		{
			victoryFlag = 1;
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			pCWGI->m_curPlayerSPInfo.isInitial = false;
		}
		//return 0;
	}
	else
	{
		if (m_pAIManager->m_battleInfo.battleType == 0)
		{
			if (m_curLogicFrameNb < m_pAIManager->m_battleInfo.maxFrame)
			{
				if (!m_pPlayerCharacter || m_pPlayerCharacter->m_Hp <= 0) victoryFlag = 2;
			}
			else
			{
				if (!m_pPlayerCharacter || m_pPlayerCharacter->m_Hp <= 0) victoryFlag = 2;
				else victoryFlag = 1;
			}
		}
		else if (m_pAIManager->m_battleInfo.battleType == 1 || m_pAIManager->m_battleInfo.battleType == 5)
		{
			//限时击杀敌人
			if (m_curLogicFrameNb < m_pAIManager->m_battleInfo.maxFrame)
			{
				if (!m_pPlayerCharacter || m_pPlayerCharacter->m_Hp <= 0) victoryFlag = 2;
				else
				{
					if (m_deadCharacterNameList.Num() >= m_pAIManager->m_battleInfo.targetKill) victoryFlag = 1;
				}
			}
			else victoryFlag = 2;
		}
		else if (m_pAIManager->m_battleInfo.battleType == 3)
		{
			//限时击杀敌人
			if (m_curLogicFrameNb < m_pAIManager->m_battleInfo.maxFrame)
			{
				if (m_deadCharacterNameList.Contains(m_pAIManager->m_battleInfo.targetKillName)) victoryFlag = 1;
				else if (!m_pPlayerCharacter || m_pPlayerCharacter->m_Hp <= 0)  victoryFlag = 2;
			}
			else victoryFlag = 2;
		}
		else if (m_pAIManager->m_battleInfo.battleType == 4)
		{
			if (m_curLogicFrameNb < m_pAIManager->m_battleInfo.maxFrame)
			{
				if (m_pAIManager->m_battleInfo.targetCollectNameList.Num() <= 0) victoryFlag = 1;
			}
			else victoryFlag = 2;
		}
	}
	
	if (victoryFlag != 0)
	{
		m_tickFlag = false;
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		pCWGI->m_battleState = victoryFlag;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		pPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_fadeOutTime, FLinearColor::Black, false, true);
		NotifyWinLose(victoryFlag);
		NotifyMusicFadeOut();
		GetWorldTimerManager().SetTimer(m_backToSPTimerHandler, this, &ARoguelikeBattleGameMode::BackSingleprogressLevel, m_fadeOutTime, false);
		return victoryFlag;
	}
	return 0;
}

void ARoguelikeBattleGameMode::NotifyWinLose_Implementation(uint8 winLoseFlag)
{

}

void ARoguelikeBattleGameMode::BackSingleprogressLevel()
{
	m_isFading = false;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	FString levelName;
	if (pCWGameInstance->m_battleState == 2)
		levelName = "LoginMap";
	else if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 0)
		levelName = "SingleprogressMap_Snow";
	else if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 1)
		levelName = "SingleprogressMap_Desert";
	else if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 2)
		levelName = "SingleprogressMap_Forest";
	UGameplayStatics::OpenLevel(this, FName(*levelName));
}

void ARoguelikeBattleGameMode::UpdateTutorialStep()
{
	if (m_tutorialSteps.Num() <= 0) return;
	/**
	* 1. 先判定是否需要生成指示器
	* 2. 然后更新指示菜单
	*/
	if (!m_pBPC) return;
	if (m_pBPC->m_pTutorialMenu)
	{
		if (m_pBPC->m_pTutorialMenu->m_pWidgetManager->m_language == "Chinese")
			m_pBPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].chExplanation));
		else
			m_pBPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].enExplanation));
	}
	m_pBPC->NotifySpawnMenuTutorIndicator(m_tutorialSteps[0].operationName);
}

void ARoguelikeBattleGameMode::CollectAllDeadCharacters()
{
	int32 i = 0;
	TArray<ABaseCharacter*> pDeadCharacters;
	while (i < m_pAllCharacters.Num())
	{
		if (!m_pAllCharacters[i]) RemoveCharacterFromGame(m_pAllCharacters[i]);
		else if (m_pAllCharacters[i]->m_Hp <= 0)
		{
			if (m_pAllCharacters[i]->m_level < 5) m_pAIManager->m_curRoundEnermyNb -= 1;
			if (m_pBPC->m_pCharacterStatusMenu && m_pBPC->m_pCharacterStatusMenu->m_pCharacter == m_pAllCharacters[i])
				m_pBPC->m_pCharacterStatusMenu->ClearAllInfo();
			//SpawnDeadCharacterFixSkill(m_pAllCharacters[i]->m_fixDeadSkillGeoClass, m_pAllCharacters[i]);
			if (m_pAllCharacters[i]->m_fixDeadSkillGeoClass)
			{
				ABasePhysGeo* pGeo = m_pPhysCalculator->SpawnPhysGeo(m_pAllCharacters[i]->m_fixDeadSkillGeoClass, m_pAllCharacters[i]->GetActorLocation(), m_pAllCharacters[i]->GetActorRotation());
				m_pPhysCalculator->AddPhysGeo(pGeo, NULL, m_pAllCharacters[i]->m_campFlag);
				UGameplayStatics::SpawnEmitterAtLocation(this, m_pAllCharacters[i]->m_skillParticleMap["DeadSkill"].particleSystem, m_pAllCharacters[i]->m_skillParticleMap["DeadSkill"].loc);
			}
			m_pPhysCalculator->ActivateDeadEffect(m_pAllCharacters[i]);
			pDeadCharacters.Add(m_pAllCharacters[i]);
			RemoveCharacterFromGame(m_pAllCharacters[i]);
		}
		else i += 1;
	}
	for (int32 j = 0; j < pDeadCharacters.Num(); j++)
	{
		if (!m_pDeadCharacters.Contains(pDeadCharacters[j])) m_pDeadCharacters.Add(pDeadCharacters[j]);
		if (m_pBPC->m_pBattleMenu) m_pBPC->m_pBattleMenu->m_curKillEnermyNb += 1;
	}
	if (m_pBPC->m_pBattleMenu) m_pBPC->m_pBattleMenu->m_pCurKillText->SetText(FText::FromString(FString::FromInt(m_pBPC->m_pBattleMenu->m_curKillEnermyNb)));
	RecordAllScores(pDeadCharacters);
}

void ARoguelikeBattleGameMode::RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type)
{
	if (type == 0 || type == 1 || type == 2)
	{
		//说明是在BattleMenu阶段或圣灵阶段
		if (!m_pBPC->m_pBattleMenu) return;
		if (!needToShowTutorialButton) m_pBPC->m_pBattleMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pBPC->m_pBattleMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	m_curTutorialName = tutorialStepName;
}

UClass* ARoguelikeBattleGameMode::ReadCharacterBPDynamic_Implementation(const FString& className)
{
	return NULL;
}

void ARoguelikeBattleGameMode::InitialLevel()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!pGameInstance) return;
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;

	NotifySetSkyColorMatParam(pCWGameInstance->m_curPlayerSPInfo.curProgress, pCWGameInstance->m_dayOrNight, true);

	ReadDifficultyParams();
	ReadEquipmentClass();
	ReadCharacterHurtScoreLevels();

	m_pAIManager = NewObject<UAIManager>(this, m_aiManagerClass);

	m_pAIManager->m_battleInfo = pCWGameInstance->m_battleInfo;

	m_pGeometricRecognizer = NewObject<UGeometricRecognizer>(this, m_geometricRecognizerClass);

	if (!m_BPMapGeneratorClass) return;
	m_pMapGenerator = NewObject<UMapGenerator>(this, m_BPMapGeneratorClass);

	TArray<AActor*> pPrefabGeos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePhysGeo::StaticClass(), pPrefabGeos);

	TArray<AActor*> pPrefabSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanSpawnPoint::StaticClass(), pPrefabSpawnPoints);

	for (int32 i=0; i<pPrefabSpawnPoints.Num(); i++)
	{
		APlanSpawnPoint* pPlanSpawnPoint = Cast<APlanSpawnPoint>(pPrefabSpawnPoints[i]);
		if (!pPlanSpawnPoint) continue;
		m_pPlanSpawnPoints.Add(pPlanSpawnPoint);
	}

	NavManager = SpawnActor<ANavManager>(NavManagerBPClass, FVector::ZeroVector, FRotator::ZeroRotator);

	m_pRecastDetourObject = NewObject<URecastDetourObject>();
	m_pRecastDetourObject->m_defaultArenaHeight = m_defaultSpawnHeight;
	m_pRecastDetourObject->InitialBuild("RogueLikeMap");
	m_pPhysCalculator = GetWorld()->SpawnActor<APhysCalculator>(m_BPPhysCalculatorClass, FVector::ZeroVector, FRotator::ZeroRotator);
	m_pPhysCalculator->m_pCWSingleton = m_pCWSingleton;
	m_pPhysCalculator->m_pRGM = this;
	m_pPhysCalculator->m_defaultSpawnHeight = m_defaultSpawnHeight;
	m_pPhysCalculator->InitialPhys();

	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		ABasePhysGeo* pPrefabGeo = Cast<ABasePhysGeo>(pPrefabGeos[i]);
		if (!pPrefabGeo) continue;
		pPrefabGeo->m_moveType = 0;
		/*FLogicVec2D forwardDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(pPrefabGeo->GetActorRotation().Yaw);
		pPrefabGeo->m_logicForwardDir = forwardDir;*/
		m_pPhysCalculator->AddPhysGeo(pPrefabGeo, NULL, 0);
		pPrefabGeo->m_hierachy = 0;
	}

	GenRogueMap(m_pAIManager->m_battleInfo.specifiedLandBlockNameList);

	// Must init NavManager after phys and dump roguelike stuffs generation
	NavManager->Init();

	//将小兵的生成方式从服务端派发改为由AIDirector来自动控制
	
	TArray<int32> campFlags = {2};
	m_pAIManager->m_spawnAmplificationCoe = m_spawnAmplification;
	m_pAIManager->InitialAIManager(campFlags, pCWGameInstance->m_curPlayerSPInfo.curProgress, pCWGameInstance->m_curPlayerSPInfo.difficulty);
	m_pAIManager->InitialGradingNameList();
	m_pAIManager->m_specialEffectPercent = m_specialEffectPercent;

	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!pPlayerController) return;
	m_pBPC = Cast<ABattleLevelPlayerController>(pPlayerController);
	if (!m_pBPC) return;
	m_pBPC->ReadAllTextureInfo();
	//if (!m_pBPC->GetControllFromGameMode()) return;
	if (pCWGameInstance->m_curPlayerSPInfo.isInitial)
	{
		/*m_isInTutorial = true;
		m_pBPC->m_isInTutorial = true;
		ReadTutorialSteps();
		m_pPlayerCharacter->AddNewItem("Numeric_S_1");
		m_pPlayerCharacter->AddNewItem("Numeric_H_2");
		m_pPlayerCharacter->AddNewItem("Mask");
		m_pAIManager->m_battleInfo.firstPeakInterval += m_tutorialExtraTick;
		m_pAIManager->m_battleInfo.maxFrame += m_tutorialExtraTick;
		if (pCWGameInstance->m_language == "Chinese")
			m_pAIManager->m_battleInfo.chDescription = m_chTutorialDescription;
		else
			m_pAIManager->m_battleInfo.chDescription = m_enTutorialDescription;
		

		TArray<FString> spawnNameList;
		for (int32 i = 0; i < m_TutorialDumpEnermies.expectSpawnNameList.Num(); i++)
		{
			for (int32 j = 0; j < m_TutorialDumpEnermies.expectSpawnNameList[i].spawnNb; j++)
			{
				spawnNameList.Add(m_TutorialDumpEnermies.expectSpawnNameList[i].characterName);
			}
		}
		//对将要生成的角色进行特殊状态赋值，例如加火属性得益效果、无敌或劈砍衰弱等特殊效果。
		TMap<int32, FPreAssignEffectList> assignSpecialStateList;
		m_pAIManager->AssignSpecialEffectToCharacters(spawnNameList, assignSpecialStateList);
		//生成角色，同时将特殊效果赋值给对应的角色
		int32 i = 0;
		while (i < spawnNameList.Num())
		{
			int32 newID = GetAnUnOccupyID();
			if (newID == -1) return;
			//UClass* characterBP = UCollisionWarBpFunctionLibrary::GetCharacterBlueprintClassDynamic(spawnNameList[j]);
			UClass* characterBP = m_allCharacterInfo[spawnNameList[i]].pCharacterClass;
			FLogicVec2D logicSpawnLoc;
			int32 spawnYaw;

			//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, TEXT("cur rand seed is: ") + FString::FromInt(m_curRandSeed));
			int32 randLocInSpawnPointX = FMath::RandRange(-pRandSpawnPoint->m_spawnPointWidth, pRandSpawnPoint->m_spawnPointWidth);
			int32 randLocInSpawnPointY = FMath::RandRange(-pRandSpawnPoint->m_spawnPointWidth, pRandSpawnPoint->m_spawnPointWidth);

			logicSpawnLoc = pRandSpawnPoint->m_spawnPointLoc + FLogicVec2D(randLocInSpawnPointX, randLocInSpawnPointY);
			spawnYaw = FMath::RandRange(0,180);

			FVector spawnLoc(logicSpawnLoc.X, logicSpawnLoc.Y, m_defaultSpawnHeight);
			FRotator spawnRot(0, spawnYaw, 0);
			ABaseCharacter* pCharacter = GetWorld()->SpawnActor<ABaseCharacter>(characterBP, spawnLoc, spawnRot);
			//ModifyCharacterProByLevel(pCharacter, m_pPlayerCharacter->m_level);
			InitialNewCharacter(pCharacter, m_TutorialDumpEnermies.campFlag, newID, logicSpawnLoc, false);
			//看指定特殊效果的号码队列里是否包含当前序号，如包含说明该名角色是有对应的特殊效果的，对其赋值
			if (assignSpecialStateList.Contains(i) && m_pPhysCalculator)
			{
				for (int32 j = 0; j < assignSpecialStateList[i].list.Num(); j++)
				{
					m_pPhysCalculator->AddPermenantEffectOnCharacter(assignSpecialStateList[i].list[j], pCharacter);
				}
			}
			/ *UWidgetBlueprintFunctionLibrary::AddEnermyInfoToBattleMenu(pCharacter->m_characterRace, pCharacter->m_characterClassName,
				pCharacter->m_stateNames, pBLPC->m_pBattleMenu);* /
			i += 1;
		}

		m_pAIManager->m_battleInfo.maxFrame = m_tutorialMaxTick;
		m_pAIManager->m_battleInfo.intervalList.Empty();
		m_pAIManager->m_peakIntervalList.Empty();
		m_pBPC->InitialTutorial();*/
	}
	//pBattlePlayerController->AddPreAssignCards();
	m_isStart = true;
	//GetWorldTimerManager().SetTimer(m_backToSPTimerHandler, this, &ASingleProgressGameMode::EndSP, m_endSPTime + 0.2f, false);
	m_pBPC->LoadBattleMenu();

	int32 randSpawnPointNb = FMath::RandRange(0, m_pPlanSpawnPoints.Num() - 1);
	APlanSpawnPoint* pRandSpawnPoint = m_pPlanSpawnPoints[randSpawnPointNb];

	FString roleType = pCWGameInstance->m_curPlayerSPInfo.characterName;
	if (roleType == "NULL" || roleType == "")
	{
		roleType = "Lucian";
		pCWGameInstance->m_curPlayerSPInfo.characterName = "Lucian";
	}
	//UClass* characterBP = UCollisionWarBpFunctionLibrary::GetCharacterBlueprintClassDynamic(roleType);
	UClass* characterBP = m_pCWSingleton->m_allCharacterInfo[roleType];
	FVector spawnLoc(pRandSpawnPoint->m_spawnPointLoc.X, pRandSpawnPoint->m_spawnPointLoc.Y, m_defaultSpawnHeight);
	FRotator spawnRot(0, pRandSpawnPoint->m_spawnYaw, 0);
	AKing* pKing = GetWorld()->SpawnActor<AKing>(characterBP, spawnLoc, spawnRot);
	pKing->m_pRGM = this;
	int32 playerID = 1;
	m_occupyIDs.Add(playerID);
	InitialNewCharacter(pKing, 0, playerID, FLogicVec2D(pRandSpawnPoint->m_spawnPointLoc.X, pRandSpawnPoint->m_spawnPointLoc.Y), false);
	m_pPlayerCharacter = pKing;
	if (!m_pBPC->GetControllFromGameMode()) return;
	//Initial Skills
	pKing->m_pBaseEquipment->m_pSkills[0]->m_mutationType = pCWGameInstance->m_chopSkillMutationType;
	pKing->MessAllSkillCard();
	
	if (pCWGameInstance->m_curPlayerSPInfo.curAppearanceName != "")
		GetItemListByName(pCWGameInstance->m_curPlayerSPInfo.characterName, pCWGameInstance->m_curPlayerSPInfo.curAppearanceName);

	m_pCamCharacter = GetWorld()->SpawnActor<ACamCharacter>(m_camCharacterClass, spawnLoc, spawnRot);
	m_pCamCharacter->m_domain = 1;
	m_pCamCharacter->m_pTargetCharacter = pKing;
	if (m_pWeatherPSMap.Contains(pCWGameInstance->m_weatherType))
	{
		if (pCWGameInstance->m_weatherType == 3 || pCWGameInstance->m_weatherType == 4 || pCWGameInstance->m_weatherType == 5)
			m_pCamCharacter->m_pPSComponent = UGameplayStatics::SpawnEmitterAttached(m_pWeatherPSMap[pCWGameInstance->m_weatherType].pPS, m_pCamCharacter->GetCapsuleComponent(),
				FName("PSSocket_1"), m_pWeatherPSMap[pCWGameInstance->m_weatherType].relativeLoc, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
		else
			m_pCamCharacter->m_pPSComponent = UGameplayStatics::SpawnEmitterAttached(m_pWeatherPSMap[pCWGameInstance->m_weatherType].pPS, m_pCamCharacter->GetCapsuleComponent(),
				FName("PSSocket"), m_pWeatherPSMap[pCWGameInstance->m_weatherType].relativeLoc, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	}
	m_pPlanSpawnPoints.Remove(pRandSpawnPoint);
	for (int32 i = 0; i < m_pMapGenerator->m_pTiles.Num(); i++)
	{
		if (!m_pMapGenerator->m_pTiles[i]->m_pSpawnPoints.Contains(pRandSpawnPoint)) continue;
		m_pMapGenerator->m_pTiles[i]->m_pSpawnPoints.Remove(pRandSpawnPoint);
		break;
	}
	if (pRandSpawnPoint->IsValidLowLevel())
	{
		pRandSpawnPoint->Destroy();
		pRandSpawnPoint->ConditionalBeginDestroy();
	}

	if (!pCWGameInstance->m_doneTutorialSteps.Contains(m_fixTutorialSerialNames[0])) RefreshTutorial(m_fixTutorialSerialNames[0], true, 0);
	else RefreshTutorial("NULL", false, 0);
	
	m_pBPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_fadeOutTime, FLinearColor::Black, false, true);
	NotifyPlaySound2D(pCWGameInstance->m_weatherType, pCWGameInstance->m_curPlayerSPInfo.curProgress);
	//NewMessage("NotifyInitialDone");
}

void ARoguelikeBattleGameMode::NotifySetSkyColorMatParam_Implementation(uint8 curProgress, bool dayOrNight, bool battleOrSP)
{

}

/*
void ARoguelikeBattleGameMode::ReadAllScoreLevels_Implementation()
{

}*/

void ARoguelikeBattleGameMode::OutputAllActorLocations()
{
	TArray<AActor*> pPrefabGeos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePhysGeo::StaticClass(), pPrefabGeos);

	TArray<AActor*> pPrefabDumpActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADumpPhysActor::StaticClass(), pPrefabDumpActors);

	TArray<AActor*> pPlanSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanSpawnPoint::StaticClass(), pPlanSpawnPoints);

	TArray<AActor*> pStaticMeshActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), pStaticMeshActors);

	FString allStrings;
	FString block = FString(TEXT("#########################")) + FString(TEXT("\n"));
	FString projectDir = FPaths::GameDir();
	projectDir += "Content/TextFile.txt";
	TArray<FString> StringArray;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);

	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i=0; i<pPrefabGeos.Num(); i++)
	{
		FString str;
		ABasePhysActor* pGeo = Cast<ABasePhysActor>(pPrefabGeos[i]);
		if (i != (pPrefabGeos.Num() - 1))
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		int32 locX = pPrefabGeos[i]->GetActorLocation().X;
		if (i != (pPrefabGeos.Num() - 1))
			str = FString::FromInt(locX) + FString(TEXT(","));
		else
			str = FString::FromInt(locX) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		int32 locY = pPrefabGeos[i]->GetActorLocation().Y;
		if (i != (pPrefabGeos.Num() - 1))
			str = FString::FromInt(locY) + FString(TEXT(","));
		else
			str = FString::FromInt(locY) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		int32 yaw = pPrefabGeos[i]->GetActorRotation().Yaw;
		if (i != (pPrefabGeos.Num() - 1))
			str = FString::FromInt(yaw) + FString(TEXT(","));
		else
			str = FString::FromInt(yaw) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	
	//保存DumpActor信息
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		ADumpPhysActor* pGeo = Cast<ADumpPhysActor>(pPrefabDumpActors[i]);
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		int32 locX = pPrefabDumpActors[i]->GetActorLocation().X;
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString::FromInt(locX) + FString(TEXT(","));
		else
			str = FString::FromInt(locX) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		int32 locY = pPrefabDumpActors[i]->GetActorLocation().Y;
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString::FromInt(locY) + FString(TEXT(","));
		else
			str = FString::FromInt(locY) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		int32 yaw = pPrefabDumpActors[i]->GetActorRotation().Yaw;
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString::FromInt(yaw) + FString(TEXT(","));
		else
			str = FString::FromInt(yaw) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	//保存生成点信息
	allStrings.Append(FString(TEXT(",")));
	if (pPlanSpawnPoints.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPlanSpawnPoints.Num(); i++)
	{
		FString str;
		APlanSpawnPoint* pSpawnPoint = Cast<APlanSpawnPoint>(pPlanSpawnPoints[i]);
		if (i != (pPlanSpawnPoints.Num() - 1))
			str = FString(TEXT("\"")) + pSpawnPoint->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + pSpawnPoint->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPlanSpawnPoints.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPlanSpawnPoints.Num(); i++)
	{
		FString str;
		int32 locX = pPlanSpawnPoints[i]->GetActorLocation().X;
		if (i != (pPlanSpawnPoints.Num() - 1))
			str = FString::FromInt(locX) + FString(TEXT(","));
		else
			str = FString::FromInt(locX) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPlanSpawnPoints.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPlanSpawnPoints.Num(); i++)
	{
		FString str;
		int32 locY = pPlanSpawnPoints[i]->GetActorLocation().Y;
		if (i != (pPlanSpawnPoints.Num() - 1))
			str = FString::FromInt(locY) + FString(TEXT(","));
		else
			str = FString::FromInt(locY) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPlanSpawnPoints.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPlanSpawnPoints.Num(); i++)
	{
		FString str;
		int32 yaw = pPlanSpawnPoints[i]->GetActorRotation().Yaw;
		if (i != (pPlanSpawnPoints.Num() - 1))
			str = FString::FromInt(yaw) + FString(TEXT(","));
		else
			str = FString::FromInt(yaw) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	//保存StaticMeshActor信息
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pSMActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = staticMeshComponentName.Find(TEXT("StaticMeshComponent0"));
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "mesh_plane") continue;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		int32 locX = pStaticMeshActors[i]->GetActorLocation().X;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::FromInt(locX) + FString(TEXT(","));
		else
			str = FString::FromInt(locX) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		int32 locY = pStaticMeshActors[i]->GetActorLocation().Y;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::FromInt(locY) + FString(TEXT(","));
		else
			str = FString::FromInt(locY) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		int32 locZ = pStaticMeshActors[i]->GetActorLocation().Z;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::FromInt(locZ) + FString(TEXT(","));
		else
			str = FString::FromInt(locZ) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		int32 yaw = pStaticMeshActors[i]->GetActorRotation().Yaw;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::FromInt(yaw) + FString(TEXT(","));
		else
			str = FString::FromInt(yaw) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		float scale = pSMActor->GetStaticMeshComponent()->GetComponentScale().X;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::FromInt(scale) + FString(TEXT(","));
		else
			str = FString::FromInt(scale) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	FFileHelper::SaveStringToFile(allStrings, *(projectDir));
}

void ARoguelikeBattleGameMode::OutputAllEventDemoActorLocations()
{
	TArray<AActor*> pPrefabGeos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePhysGeo::StaticClass(), pPrefabGeos);

	TArray<AActor*> pPrefabDumpActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADumpPhysActor::StaticClass(), pPrefabDumpActors);

	TArray<AActor*> pPlanSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanSpawnPoint::StaticClass(), pPlanSpawnPoints);

	TArray<AActor*> pStaticMeshActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), pStaticMeshActors);

	FString allStrings;
	FString block = FString(TEXT("#########################")) + FString(TEXT("\n"));
	FString projectDir = FPaths::GameDir();
	projectDir += "Content/TextFile_1.txt";
	TArray<FString> StringArray;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);

	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		ABasePhysActor* pGeo = Cast<ABasePhysActor>(pPrefabGeos[i]);
		if (i != (pPrefabGeos.Num() - 1))
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		FVector loc = pPrefabGeos[i]->GetActorLocation();
		if (i != (pPrefabGeos.Num() - 1))
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y)+",Z="+FString::SanitizeFloat(loc.Z)+ "),";
		else
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y) + ",Z=" + FString::SanitizeFloat(loc.Z) + 
			"))" + "\"";
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabGeos.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabGeos.Num(); i++)
	{
		FString str;
		FRotator rot = pPrefabGeos[i]->GetActorRotation();
		if (i != (pPrefabGeos.Num() - 1))
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) + "),";
		else
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) + 
			"))" + "\"";
		allStrings.Append(str);
	}

	//保存DumpActor信息
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		ADumpPhysActor* pGeo = Cast<ADumpPhysActor>(pPrefabDumpActors[i]);
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + pGeo->m_className + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		FVector loc = pPrefabDumpActors[i]->GetActorLocation();
		if (i != (pPrefabDumpActors.Num() - 1))
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y) + ",Z=" + FString::SanitizeFloat(loc.Z) + "),";
		else
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y) + ",Z=" + FString::SanitizeFloat(loc.Z) +
			"))" + "\"";
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pPrefabDumpActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pPrefabDumpActors.Num(); i++)
	{
		FString str;
		FRotator rot = pPrefabDumpActors[i]->GetActorRotation();
		if (i != (pPrefabDumpActors.Num() - 1))
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) + "),";
		else
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) +
			"))" + "\"";
		allStrings.Append(str);
	}
	
	//保存StaticMeshActor信息
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pSMActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = staticMeshComponentName.Find(TEXT("StaticMeshComponent0"));
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "Plane") continue;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) +
			FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pSMActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = staticMeshComponentName.Find(TEXT("StaticMeshComponent0"));
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "Plane") continue;
		FVector loc = pStaticMeshActors[i]->GetActorLocation();
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y) + ",Z=" + FString::SanitizeFloat(loc.Z) + "),";
		else
			str = FString(TEXT("(X=")) + FString::SanitizeFloat(loc.X) + ",Y=" + FString::SanitizeFloat(loc.Y) + ",Z=" + FString::SanitizeFloat(loc.Z) +
			"))" + "\"";
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pSMActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = staticMeshComponentName.Find(TEXT("StaticMeshComponent0"));
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "Plane") continue;
		FRotator rot = pStaticMeshActors[i]->GetActorRotation();
		if (i != (pStaticMeshActors.Num() - 1))
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) + "),";
		else
			str = "(Pitch=" + FString::SanitizeFloat(rot.Pitch) + ",Yaw=" + FString::SanitizeFloat(rot.Yaw) + ",Roll=" + FString::SanitizeFloat(rot.Roll) +
			"))" + "\"";
		allStrings.Append(str);
	}
	allStrings.Append(FString(TEXT(",")));
	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("("));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pSMActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = staticMeshComponentName.Find(TEXT("StaticMeshComponent0"));
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "Plane") continue;
		//AStaticMeshActor* pSMActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		float scale = pSMActor->GetStaticMeshComponent()->GetComponentScale().X;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString::SanitizeFloat(scale) + FString(TEXT(","));
		else
			str = FString::SanitizeFloat(scale) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	FString lastStr = FString(TEXT(",")) + FString(TEXT("\"")) + FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\"")) + FString(TEXT("\""));
	allStrings.Append(lastStr);
	FFileHelper::SaveStringToFile(allStrings, *(projectDir));
}

void ARoguelikeBattleGameMode::DrawAllTiles()
{

}

void ARoguelikeBattleGameMode::SpawnPrefabActors(TArray<FString> physGeoNameList, TArray<FVector2D> physGeoSpawnLocs, 
	TArray<float> physActorYaws, TArray<FString> dumpActorNameList, TArray<FVector2D> dumpActorSpawnLocs, 
	TArray<float> dumpActorYaws, float spawnHeight)
{
	for (int32 i=0; i<physGeoNameList.Num(); i++)
	{
		FVector spawnLoc(physGeoSpawnLocs[i].X, physGeoSpawnLocs[i].Y, spawnHeight);
		FRotator spawnRot(0, physActorYaws[i], 0);
		//UClass* pClass = UCollisionWarBpFunctionLibrary::GetPhysGeoBlueprintClassDynamic(physGeoNameList[i]);
		if (!m_pCWSingleton->m_physGeoClassMap.Contains(physGeoNameList[i])) continue;
		ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_pCWSingleton->m_physGeoClassMap[physGeoNameList[i]], spawnLoc, spawnRot);
	}
	for (int32 i = 0; i < dumpActorNameList.Num(); i++)
	{
		FVector spawnLoc(dumpActorSpawnLocs[i].X, dumpActorSpawnLocs[i].Y, spawnHeight);
		FRotator spawnRot(0, dumpActorYaws[i], 0);
		//UClass* pClass = UCollisionWarBpFunctionLibrary::GetPhysGeoBlueprintClassDynamic(dumpActorNameList[i]);
		if (!m_pCWSingleton->m_physGeoClassMap.Contains(dumpActorNameList[i])) continue;
		ADumpPhysActor* pGeo = GetWorld()->SpawnActor<ADumpPhysActor>(m_pCWSingleton->m_physGeoClassMap[dumpActorNameList[i]], spawnLoc, spawnRot);
	}
}

void ARoguelikeBattleGameMode::InitialNewCharacter(ABaseCharacter* pCharacter, int32 campFlag, int32& characterID, FLogicVec2D logicSpawnLoc, bool isAlreadyAssignID)
{
	//还要初始化logicLoc和logicForwardDir
	pCharacter->NotifySetCharacterInfoWidget();
	pCharacter->m_pCharacterInfoWidget->NotifyInitial();
	pCharacter->m_pCharacterInfoWidget->InitialHpBar();
	pCharacter->m_campFlag = campFlag;
	pCharacter->m_originCampFlag = campFlag;
	pCharacter->m_beAttackedNb = 0;
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
		}
	}
	pCharacter->m_Hp = pCharacter->m_originHp;
	pCharacter->m_pCharacterInfoWidget->NotifyHpChange(pCharacter->m_Hp, pCharacter->m_DFC);
	pCharacter->m_defaultHeight = m_defaultSpawnHeight;
	pCharacter->SetActorLocation(FVector(logicSpawnLoc.X, logicSpawnLoc.Y, m_defaultSpawnHeight + pCharacter->m_relativeHeight));

	//将角色加入到对应的Team中
	bool isFoundCorrespondTeam = false;
	for (int32 i = 0; i < m_pTeams.Num(); i++)
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
	for (int32 i = 0; i < m_pAllCharacters.Num(); i++)
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
		pKing->m_energyBallList = pKing->m_maxEnergyBallNb;
		pKing->m_pCharacterInfoWidget->InitialEnergyBar(pKing->m_energyBallList);
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		int32 attributeIndex = 0;
		for (TMap<FString, int32>::TConstIterator iter = pCWGI->m_attributeIncreaseValueMap.CreateConstIterator(); iter; ++iter)
		{
			if (attributeIndex == 0 && pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(iter->Key))
			{
				pKing->m_originHp += iter->Value*pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[iter->Key];
				pKing->m_Hp = pKing->m_originHp;
			}
			else if (attributeIndex == 1&& pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(iter->Key))
				pKing->m_ATK += iter->Value*pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[iter->Key];
			else if (attributeIndex == 2 && pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(iter->Key))
			{
				pKing->m_maxDFC += iter->Value*pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[iter->Key];
			}
			attributeIndex += 1;
		}
		pCharacter->m_pCharacterInfoWidget->ChangeMaxHpAndDFC(pKing->m_originHp, pKing->m_maxDFC);
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

void ARoguelikeBattleGameMode::SpawnEnermyByGroup()
{
	if (!m_pAIManager || m_pPlanSpawnPoints.Num() == 0) return;
	if (!m_pPlayerCharacter) return;

	//每个campFlag代表一支队伍，将所有AI角色按阵营、类别进行分类
	TArray<int32> campFlags;
	TArray<FGradingExpectToSpawnInfo> expectSpawnInfoList;

	m_pAIManager->GetSpawnNameList(m_curLogicFrameNb, m_maxFrameNb, expectSpawnInfoList, m_pPlayerCharacter->m_originCampFlag);

	m_pAIManager->m_curRoundEnermyNb = 0;
	for (int32 i = 0; i < expectSpawnInfoList.Num(); i++)
	{
		TArray<FString> spawnNameList;
		for (int32 j = 0; j < expectSpawnInfoList[i].expectSpawnNameList.Num(); j++)
		{
			for (int32 k = 0; k < expectSpawnInfoList[i].expectSpawnNameList[j].spawnNb; k++)
			{
				spawnNameList.Add(expectSpawnInfoList[i].expectSpawnNameList[j].characterName);
			}
		}
		//生成角色，同时将特殊效果赋值给对应的角色
		int32 j = 0;
		while (j < spawnNameList.Num())
		{
			TArray<FVector> availableSpawnPoints = GetEnermySpawnPointRandomly();
			int32 randSpawnPoint = FMath::RandRange(0, availableSpawnPoints.Num() - 1);

			int32 newID = GetAnUnOccupyID();
			if (newID == -1) return;
			//UClass* characterBP = UCollisionWarBpFunctionLibrary::GetCharacterBlueprintClassDynamic(spawnNameList[j]);
			UClass* characterBP = m_pCWSingleton->m_allCharacterInfo[spawnNameList[j]];
			FLogicVec2D logicSpawnLoc(availableSpawnPoints[randSpawnPoint].X, availableSpawnPoints[randSpawnPoint].Y);
			
			ABaseCharacter* pCharacter = GetWorld()->SpawnActor<ABaseCharacter>(characterBP, availableSpawnPoints[randSpawnPoint], FRotator::ZeroRotator);
			pCharacter->m_spawnLoc = availableSpawnPoints[randSpawnPoint];
			if (m_pAIManager->m_battleInfo.battleType == 5)
			{
				pCharacter->m_thinkMode = ECharacterThinkMode::CTM_Patrol;
			}
			if (pCharacter->m_level < 5)
			{
				//which means it's not a boss enermy, we should cout it as normal enermy.
				m_pAIManager->m_curRoundEnermyNb += 1;
			}
			InitialNewCharacter(pCharacter, expectSpawnInfoList[i].campFlag, newID, logicSpawnLoc, false);
			//看指定特殊效果的号码队列里是否包含当前序号，如包含说明该名角色是有对应的特殊效果的，对其赋值
			j += 1;
		}
	}
}

void ARoguelikeBattleGameMode::TestSpawnEnermyByGroup()
{

}

TArray<ULandBlockTile*> ARoguelikeBattleGameMode::GetPlayerAdjoinTiles()
{
	FVector playerCharacterLoc = m_pPlayerCharacter->GetActorLocation();
	FLogicVec2D playerCharacterLoc2D(playerCharacterLoc.X, playerCharacterLoc.Y);
	FLogicVec2D playerRelativeLogicLoc = playerCharacterLoc2D - m_pMapGenerator->m_leftDownCornerCoord;
	int32 tileX = playerRelativeLogicLoc.X / m_pMapGenerator->m_tileWidth;
	int32 tileY = playerRelativeLogicLoc.Y / m_pMapGenerator->m_tileHeight;
	int32 totalTileWidth = m_pMapGenerator->m_bigTileWidthNb * m_pMapGenerator->m_bigTileWidth;
	int32 totalTileHeight = m_pMapGenerator->m_bigTileHeightNb * m_pMapGenerator->m_bigTileHeight;
	TArray<ULandBlockTile*> tiles;
	for (int32 i=-1; i<2; i++)
	{
		for (int32 j=-1; j<2; j++)
		{
			if ((i == 0 && j == 0) || (tileX + i < 0) || (tileX + i >= totalTileWidth) ||
				(tileY + j < 0) || (tileY + j >= totalTileHeight)) continue;
			int32 tileNb = (tileY + j) * m_pMapGenerator->m_bigTileWidth*m_pMapGenerator->m_bigTileWidthNb + tileX + i;
			ULandBlockTile* pTile = m_pMapGenerator->m_pTiles[tileNb];
			tiles.Add(pTile);
		}
	}
	//这里把玩家当前所在格子加在最后
	int32 playerCurTileNb = tileY * m_pMapGenerator->m_bigTileWidth * m_pMapGenerator->m_bigTileWidthNb + tileX;
	tiles.Add(m_pMapGenerator->m_pTiles[playerCurTileNb]);
	return tiles;
}

TArray<FVector> ARoguelikeBattleGameMode::GetEnermySpawnPointRandomly()
{
	FVector playerCharacterLoc = m_pPlayerCharacter->GetActorLocation();
	FLogicVec2D playerCharacterLoc2D(playerCharacterLoc.X, playerCharacterLoc.Y);
	FLogicVec2D playerRelativeLogicLoc = playerCharacterLoc2D - m_pMapGenerator->m_leftDownCornerCoord;
	int32 tileX = playerRelativeLogicLoc.X / m_pMapGenerator->m_tileWidth;
	int32 tileY = playerRelativeLogicLoc.Y / m_pMapGenerator->m_tileHeight;
	//先计算出当前格子的顶角坐标
	int32 tileLeftCornerX = m_pMapGenerator->m_tileWidth * tileX + m_pMapGenerator->m_leftDownCornerCoord.X;
	int32 tileLeftCornerY = m_pMapGenerator->m_tileHeight * tileY + m_pMapGenerator->m_leftDownCornerCoord.Y;
	//然后每隔x、y一定间距取一个点
	int32 samplePointNbX = 0;
	int32 samplePointNbY = 0;
	TArray<FVector> availableSpawnPoints;
	while (true)
	{
		if (samplePointNbX * m_pMapGenerator->m_spawnEnermySampleDis.X > m_pMapGenerator->m_tileWidth)
		{
			samplePointNbX = 0;
			samplePointNbY += 1;
			if (samplePointNbY * m_pMapGenerator->m_spawnEnermySampleDis.Y > m_pMapGenerator->m_tileHeight)
				break;
		}
		FVector testLoc(tileLeftCornerX + samplePointNbX * m_pMapGenerator->m_spawnEnermySampleDis.X,
			tileLeftCornerY + samplePointNbY * m_pMapGenerator->m_spawnEnermySampleDis.Y, m_defaultSpawnHeight);
		TArray<FOverlapResult> OverlapResults;
		GetWorld()->OverlapMultiByChannel(OverlapResults, testLoc, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeCapsule(m_pMapGenerator->m_spawnEnermySampleExtent));
		bool hasOstacle = false;
		for (int32 i = 0; i < OverlapResults.Num(); i++)
		{
			if (OverlapResults[i].GetComponent()->ComponentHasTag(FName("BasePhysActor")) ||
				OverlapResults[i].GetComponent()->ComponentHasTag(FName("DumpActor")) ||
				OverlapResults[i].GetComponent()->ComponentHasTag(FName("SMActor")))
			{
				hasOstacle = true;
				break;
			}
		}
		samplePointNbX += 1;
		if (hasOstacle) continue;
		//DrawDebugCapsule(GetWorld(), testLoc, m_pMapGenerator->m_spawnEnermySampleExtent.Z, m_pMapGenerator->m_spawnEnermySampleExtent.X, FQuat(FRotator::ZeroRotator), FColor::Red, false, 10.f, 0, 5);
		availableSpawnPoints.Add(testLoc);
	}
	return availableSpawnPoints;
}

void ARoguelikeBattleGameMode::ResetItemList(const FCharacterItemList& itemList)
{
	if (!m_pPlayerCharacter) return;
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pPlayerCharacter->m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value) continue;
		iter->Value->SetSkeletalMesh(NULL);
	}
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pPlayerCharacter->m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value || iter->Key >= itemList.pItemMeshList.Num() || !itemList.pItemMeshList[iter->Key]) continue;
		iter->Value->SetSkeletalMesh(itemList.pItemMeshList[iter->Key]);
	}

	/*for (int32 i = 0; i < m_pPlayerCharacter->m_pItemComponents.Num(); i++)
	{
		m_pPlayerCharacter->m_pItemComponents[i].pComponent->SetSkeletalMesh(NULL);
	}
	for (int32 i = 0; i < itemList.pItemMeshList.Num(); i++)
	{
		if (!itemList.pItemMeshList[i] || i >= m_pPlayerCharacter->m_pItemComponents.Num()) continue;
		m_pPlayerCharacter->m_pItemComponents[i].pComponent->SetSkeletalMesh(itemList.pItemMeshList[i]);
	}*/
}

void ARoguelikeBattleGameMode::CalculateHurtScore()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	int32 i = 0;
	for (TMap<int32, int32>::TConstIterator iter = m_scoreLevelMaps.CreateConstIterator(); iter; ++iter)
	{
		if (!m_hurtLevelFinalScoreConvertMap.Contains(iter->Key)) continue;
		pCWGI->m_totalBattleScore += m_hurtLevelFinalScoreConvertMap[iter->Key] * iter->Value;
	}
}

void ARoguelikeBattleGameMode::UpdateFrameDemonstration()
{
	if (!m_pBPC || !m_pBPC->m_pBattleMenu) return;
	if (m_pAIManager->m_curPeakNb >= m_pAIManager->m_peakIntervalList.Num())
		m_pBPC->m_pBattleMenu->UpdateCurFrameCount(m_curLogicFrameNb, m_pAIManager->m_battleInfo.maxFrame, 1);
	else
		m_pBPC->m_pBattleMenu->UpdateCurFrameCount(m_curLogicFrameNb, m_pAIManager->m_peakIntervalList[m_pAIManager->m_curPeakNb], 0);
}

void ARoguelikeBattleGameMode::UpdateFullFieldStates(bool addOrSub, ABasePhysGeo* pGeo, const FEffectParams& param)
{
	TArray<uint8> stateList;
	if (addOrSub)
	{
		for (TMap<int32, uint8>::TConstIterator iter = m_fullFieldStates.CreateConstIterator(); iter; ++iter)
		{
			if (!stateList.Contains(param.effectValues.Last()))
				stateList.Add(param.effectValues.Last());
		}
		if (m_skillMaskMap.Num() >= m_maxSkillMaskNb) return;
		for (int32 i = 0; i < m_maxSkillMaskNb; i++)
		{
			if (m_skillMaskMap.Contains(i)) continue;
			m_skillMaskMap.Add(i, pGeo);
			FString maskParamStr = "MaskPos" + FString::FromInt(i);
			FString radiusParamStr = "Radius" + FString::FromInt(i);
			NotifyAddSkillMask(maskParamStr, radiusParamStr, pGeo->GetActorLocation());
			break;
		}
	}
	else
	{
		m_fullFieldStates.Remove(pGeo->m_entityID);
		for (TMap<int32, uint8>::TConstIterator iter = m_fullFieldStates.CreateConstIterator(); iter; ++iter)
		{
			if (!stateList.Contains(iter->Value))
				stateList.Add(iter->Value);
		}
		for (TMap<int32, ABasePhysGeo*>::TConstIterator iter = m_skillMaskMap.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value != pGeo) continue;
			FString maskParamStr = "MaskPos" + FString::FromInt(iter->Key);
			FString radiusParamStr = "Radius" + FString::FromInt(iter->Key);
			NotifyDeleteSkillMask(maskParamStr, radiusParamStr, pGeo->GetActorLocation());
			m_skillMaskMap.Remove(iter->Key);
			break;
		}
	}
	NotifySetFullFieldState(stateList);
}

void ARoguelikeBattleGameMode::NotifyDeleteSkillMask_Implementation(const FString& skillMaskNb, const FString& radiusMaskNb, FVector loc)
{

}

void ARoguelikeBattleGameMode::NotifyAddSkillMask_Implementation(const FString& skillMaskNb, const FString& radiusMaskNb, FVector loc)
{

}

void ARoguelikeBattleGameMode::NotifySetFullFieldState_Implementation(const TArray<uint8>& stateList)
{

}

void ARoguelikeBattleGameMode::ReadTutorialEnermyGroup_Implementation(TArray<FGradingExpectToSpawnInfo>& tutorialEnermyGroup)
{

}

void ARoguelikeBattleGameMode::ReadTutorialSteps_Implementation()
{

}

void ARoguelikeBattleGameMode::DealEventList()
{
	/*for (int32 i=0; i< m_pWaitToDealEventPhysActorList.Num(); i++)
	{
		if (!m_pWaitToDealEventPhysActorList[i]) continue;
		for (uint8 j=0; j< m_pWaitToDealEventPhysActorList[i]->m_effectParamList.Num(); j++)
		{
			if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "GetCards")
				UEventSystemFunLib::GetCards(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "SpawnEffectToPlayer")
				UEventSystemFunLib::SpawnEffectToPlayer(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "SpawnGeo")
				UEventSystemFunLib::SpawnGeo(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], m_pWaitToDealEventPhysActorList[i]);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "SpawnEffectToType")
				UEventSystemFunLib::SpawnEffectToType(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "GetResources")
				UEventSystemFunLib::GetResources(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "IncreaseEquipCardNbByAppendString")
				UEventSystemFunLib::IncreaseEquipCardNbByAppendString(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "GetResourcesByEquipCardAppendString")
				UEventSystemFunLib::GetResourcesByEquipCardAppendString(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
			else if (m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j].functionNames[0] == "TradeDiscount")
				UEventSystemFunLib::TradeDiscount(m_pWaitToDealEventPhysActorList[i]->m_effectParamList[j], this);
		}

	}
	m_pWaitToDealEventPhysActorList.Empty();*/
	if (m_curEventNb >= m_pAIManager->m_battleInfo.eventList.Num()) return;
	if (m_curLogicFrameNb == m_pAIManager->m_battleInfo.eventList[m_curEventNb].frameNb)
	{
		int32 randEventNb = FMath::RandRange(0, m_pAIManager->m_battleInfo.eventList[m_curEventNb].possibleEventNameList.Num() - 1);
		FString eventName = m_pAIManager->m_battleInfo.eventList[m_curEventNb].possibleEventNameList[randEventNb];
		if (m_eventEffectParamMap.Contains(eventName))
		{
			if (eventName == "Winter Fall")
			{
				
			}
		}
		if (m_pEventPSMap.Contains(eventName) && m_pPlayerCharacter)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, m_pEventPSMap[eventName], m_pPlayerCharacter->GetActorLocation());
			NotifyEventOccur(eventName);
		}
		m_curEventNb += 1;
	}
}

void ARoguelikeBattleGameMode::RecordAllScores(TArray<ABaseCharacter*> pAllDeadCharacters)
{
	for (int32 i=0; i<pAllDeadCharacters.Num(); i++)
	{
		if (!m_characterScoreLevels.Contains(pAllDeadCharacters[i]->m_grade)) continue;
		bool findHurtScoreLevel = false;
		for (int32 j=0; j< m_characterScoreLevels[pAllDeadCharacters[i]->m_grade].hurtTimes.Num(); j++)
		{
			if (pAllDeadCharacters[i]->m_beAttackedNb <= m_characterScoreLevels[pAllDeadCharacters[i]->m_grade].hurtTimes[j])
			{
				//m_characterHurtScoreLevels[pAllDeadCharacters[i]->m_grade].score
				if (m_scoreLevelMaps.Contains(m_characterScoreLevels[pAllDeadCharacters[i]->m_grade].scoreLevels[j]))
				{
					m_scoreLevelMaps[m_characterScoreLevels[pAllDeadCharacters[i]->m_grade].scoreLevels[j]] += 1;
				}
				findHurtScoreLevel = true;
				break;
			}
		}
		if (!findHurtScoreLevel && m_scoreLevelMaps.Contains(pAllDeadCharacters[i]->m_grade))
			m_scoreLevelMaps[pAllDeadCharacters[i]->m_grade] += 1;
		m_deadCharacterNameList.Add(pAllDeadCharacters[i]->m_characterClassName);
	}
	m_pBPC->UpdateInitialResources();
}

void ARoguelikeBattleGameMode::TriggerAllEventCards()
{
	if (!m_pPhysCalculator) return;
	
	for (TMap<ABasePhysGeo*, FEffectParams>::TConstIterator iter = m_fullFieldEffectMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Key) continue;
		m_pPhysCalculator->SpawnOverallEffect(iter->Value, iter->Key);
		if (iter->Value.functionNames[0].Contains("FullField_"))
			UpdateFullFieldStates(true, iter->Key, iter->Value);
	}
	m_fullFieldEffectMap.Empty();
}

void ARoguelikeBattleGameMode::NotifyEventOccur_Implementation(const FString& eventName)
{

}
