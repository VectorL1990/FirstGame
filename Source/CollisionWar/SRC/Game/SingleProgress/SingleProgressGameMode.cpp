// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "../../Base/NormalCameraManager.h"
#include "../../Base/SingleProgress/SingleProgressPlayerController.h"
#include "../../Common/SPEventFunctionLib.h"
#include "../../Base/Widget/TEnergyBall.h"
#include "Engine/AssetManager.h"
#include "SingleProgressGameMode.h"




void ASingleProgressGameMode::BeginPlay()
{
	/*if (m_BPLuaActorClass)
	{
		m_pLuaActor = GetWorld()->SpawnActor<ALuaActor>(m_BPLuaActorClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	}*/
	UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	m_pCWSingleton = pSingleton;
	//m_pCWSingleton->NotifyReadSingleprogressMeshAndMat();
	//ReadTinyMapInfos();
	TellBPBeginPlay();
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	/*if (pCWGI->m_curPlayerSPInfo.isInitial)
		TestShipping("SingleProgressGameMode_BeginPlay isInitial is true");*/
	if (pCWGI->m_battleState == 1 || pCWGI->m_battleState == 2) InitialSingleprogressInfo(2);
	else if (pCWGI->m_battleState == 3) InitialSingleprogressInfo(3);
	else InitialSingleprogressInfo(1);

	if (pCWGI->m_curPlayerSPInfo.isInitial && pCWGI->m_battleState == 0)
	{
		//读取世界观介绍菜单
		m_pSPPC->m_pTransitionMenu = CreateWidget<UTTransitionMenu>(m_pSPPC, m_pSPPC->m_pWidgetManager->m_widgetClassMap["TransitionMenu"]);
		m_pSPPC->m_pTransitionMenu->m_type = 2;
		m_pSPPC->m_pTransitionMenu->NotifyInitial();
		m_pSPPC->m_pTransitionMenu->m_pWidgetManager = m_pSPPC->m_pWidgetManager;
		if (m_pSPPC->m_pTransitionMenu->m_pWidgetManager->m_language == "Chinese")
		{
			if (m_pSPPC->m_pTransitionMenu->m_chDescriptions.Num() > 0)
				m_pSPPC->m_pTransitionMenu->m_pDescriptionBox->SetText(FText::FromString(m_pSPPC->m_pTransitionMenu->m_chDescriptions[0]));
		}
		else
		{
			if (m_pSPPC->m_pTransitionMenu->m_enDescriptions.Num() > 0)
				m_pSPPC->m_pTransitionMenu->m_pDescriptionBox->SetText(FText::FromString(m_pSPPC->m_pTransitionMenu->m_enDescriptions[0]));
		}
		m_pSPPC->m_pTransitionMenu->AddToViewport();
	}

	pCWGI->m_battleState = 0;
	NotifyPlaySound2D(pCWGI->m_weatherType, pCWGI->m_curPlayerSPInfo.curProgress);
	
	if (m_pCWSingleton->m_asyncLoadStateDone.Num() < 4)
	{
		m_pCWSingleton->ReqAsynLoad(0);
		m_pCWSingleton->ReqAsynLoad(1);
		m_pCWSingleton->ReqAsynLoad(2);
		m_pCWSingleton->ReqAsynLoad(3);
	}
}

void ASingleProgressGameMode::Tick(float DeltaSeconds)
{
	/** 这里要考虑并发的情况，主要情况如下
	* 1 - “同时”出现两场战斗，例如玩家在点击合成确认的时候触发普通战斗，同时Tick函数也运行到UpdateAllEvents触发大型战斗
	* 2 - 玩家在合成时点击确认触发骰子战斗，推理等项目，同时Tick函数也运行到UpdateAllEvents触发大型战斗
	*为解决并发问题，新增gameState = 5表示战斗，对于两种战斗同时并发的情况，采取低级战斗让步高级战斗的策略，即在UpdateAllEvents中
	*	触发的InitialBattle坚决执行，但如若在CombinePlayCard中执行InitialBattle，则需要先对游戏状态进行判断，如gameState = 5
	*	说明已经在战斗中，这时拒绝战斗，对于其余骰子战斗等情况，也是让步于战斗，直接拒绝
	*/
	if (m_gameState == 1)
		UpdateDiceLogic(DeltaSeconds);
	else if (m_gameState == 2)
		UpdateTheorize(DeltaSeconds);
	else if (m_gameState == 3)
		UpdateDrawCard(DeltaSeconds);
	else if (m_gameState == 4)
		UpdateShop();

	if (m_pControlCharacter) m_pControlCharacter->UpdateDayNight(DeltaSeconds);
	if (m_gameState == 0) UpdateOverallIndexDemoActorList(DeltaSeconds);
	/*if (!m_tickFlag)
	{
		if (m_gameState == 1)
			UpdateDiceLogic(DeltaSeconds);
		else if (m_gameState == 2)
			UpdateTheorize(DeltaSeconds);
		else if (m_gameState == 3)
			UpdateDrawCard(DeltaSeconds);
		else if (m_gameState == 4)
			UpdateShop();
		return;
	}
	if (m_gameState == 0)
	{
		/ *m_curTickTime += DeltaSeconds;
		m_curTickCount += 1;
		if (!m_pSPPC) return;
		uint8 missionState = UpdateMissionList();
		if (missionState == 2)
		{
			m_gameState = 8;
			m_pSPPC->m_gameState = 8;
			StopTick();
			HideAllCardWidget();
			m_pSPPC->m_pSPMenu->FadeOut();
			//GetWorldTimerManager().SetTimer(m_openBattleLevelTimeHandler, this, &ASingleProgressGameMode::LoadEndSPMenu, m_fadeOutTime, false);
			m_endType = 1;
			GetWorldTimerManager().SetTimer(m_endSPTimeHandler, this, &ASingleProgressGameMode::EndSP, m_endSPTime + 0.2f, false);
			m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_fadeOutTime, FLinearColor::Black, false, true);
			return;
		}
		GenerateNumericCards(DeltaSeconds);
		UpdateAllEvents(DeltaSeconds);
		//UpdateAllCards();
		UpdateOverallIndex(DeltaSeconds);
		UpdateExtraOverallIndexFun();
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateClock(m_curTickTime);
		UpdateCardCombineDemoInfo(DeltaSeconds);
		UpdateAllCardFunctions(DeltaSeconds);* /
		
		

		//UpdateCaptureScenes();
		/ *if (m_curTickTime >= m_curProgressMaxTick)
		{
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			//实现转场，如当前进程号大于等于2，要播放结局
			//if (pCWGI->m_curPlayerSPInfo.curProgress >= 2)
			//如进程号小于2，跳转场景

			StopTick();
			HideAllCardWidget();
			pSPPC->m_pSPMenu->FadeOut();
			//GetWorldTimerManager().SetTimer(m_openBattleLevelTimeHandler, this, &ASingleProgressGameMode::LoadEndSPMenu, m_fadeOutTime, false);
			GetWorldTimerManager().SetTimer(m_endSPTimeHandler, this, &ASingleProgressGameMode::EndSP, m_endSPTime + 0.2f, false);
			pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_fadeOutTime, FLinearColor::Black, false, true);
		}* /
	}*/
}

void ASingleProgressGameMode::StopTick()
{
	m_tickFlag = false;
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		if (!m_pPlayCards[i]) continue;
		m_pPlayCards[i]->m_canTick = false;
	}
}

void ASingleProgressGameMode::ResumeTick()
{
	m_tickFlag = true;
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		if (!m_pPlayCards[i]) continue;
		m_pPlayCards[i]->m_canTick = true;
	}
}

void ASingleProgressGameMode::HideAllCardWidget()
{
	for (int32 i=0; i<m_pActionCards.Num(); i++)
	{
		if (!m_pActionCards[i] || !m_pActionCards[i]->m_pActionCardInfo) continue;
		m_pActionCards[i]->m_pActionCardInfo->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASingleProgressGameMode::HideAllCard()
{
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		m_pPlayCards[i]->CardDisappear();
	}
}

void ASingleProgressGameMode::ShowAllCardWidget()
{
	for (int32 i = 0; i < m_pActionCards.Num(); i++)
	{
		if (!m_pActionCards[i] || !m_pActionCards[i]->m_pActionCardInfo) continue;
		m_pActionCards[i]->m_pActionCardInfo->SetVisibility(ESlateVisibility::Visible);
	}
}

void ASingleProgressGameMode::ShowAllCard()
{
	for (int32 i = 0; i < m_pPlayCards.Num(); i++)
	{
		m_pPlayCards[i]->m_pBaseMesh->SetVisibility(true);
		if (m_pPlayCards[i]->m_pCardImageMesh) m_pPlayCards[i]->m_pCardImageMesh->SetVisibility(true);
		if (m_pPlayCards[i]->m_pCardName) m_pPlayCards[i]->m_pCardName->SetVisibility(true);
		m_pPlayCards[i]->NotifyInitialCard("", m_pPlayCards[i]->m_cardName, -1);
	}
}

void ASingleProgressGameMode::OutputAllStaticMeshInfo()
{
	TArray<AActor*> pStaticMeshActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), pStaticMeshActors);
	int32 actorNb = 0;
	while (actorNb < pStaticMeshActors.Num())
	{
		AStaticMeshActor* pStaticMeshActor = Cast<AStaticMeshActor>(pStaticMeshActors[actorNb]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pStaticMeshActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = UKismetStringLibrary::FindSubstring(staticMeshComponentName, TEXT("StaticMeshComponent0"), true, true);
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (staticMeshName == "mesh_plane") pStaticMeshActors.RemoveAt(actorNb);
		else actorNb += 1;
	}

	FString allStrings;
	FString block = FString(TEXT("#########################")) + FString(TEXT("\n"));
	FString projectDir = FPaths::GameDir();
	projectDir += "Content/MainProgressTinyMap.txt";
	TArray<FString> StringArray;
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*projectDir))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("** Could not Find File **"));
		return;
	}
	FFileHelper::LoadANSITextFileToStrings(*(projectDir), NULL, StringArray);

	if (pStaticMeshActors.Num() > 0)
	{
		FString str = FString(TEXT("\"")) + FString(TEXT("(")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	for (int32 i = 0; i < pStaticMeshActors.Num(); i++)
	{
		FString str;
		AStaticMeshActor* pStaticMeshActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString staticMeshComponentName = UKismetSystemLibrary::GetDisplayName(pStaticMeshActor->GetStaticMeshComponent());
		int32 staticMeshNameCountFromRight = UKismetStringLibrary::FindSubstring(staticMeshComponentName, TEXT("StaticMeshComponent0"), true, true);
		FString staticMeshName = staticMeshComponentName.Right(staticMeshComponentName.Len() - (21 + staticMeshNameCountFromRight));
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) + FString(TEXT("\"")) + FString(TEXT(",")) + FString(TEXT("\""));
		else
			str = FString(TEXT("\"")) + staticMeshName + FString(TEXT("\"")) + FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
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
		float locX = pStaticMeshActors[i]->GetActorLocation().X;
		float locY = pStaticMeshActors[i]->GetActorLocation().Y;
		float locZ = pStaticMeshActors[i]->GetActorLocation().Z;
		if (i != (pStaticMeshActors.Num() - 1))
		{
			str = FString(TEXT("(")) + FString(TEXT("X=")) + FString::SanitizeFloat(locX) + FString(TEXT(",")) +
				FString(TEXT("Y=")) + FString::SanitizeFloat(locY) + FString(TEXT(",")) +
				FString(TEXT("Z=")) + FString::SanitizeFloat(locZ) + FString(TEXT(")")) + FString(TEXT(","));
		}
		else
		{
			str = FString(TEXT("(")) + FString(TEXT("X=")) + FString::SanitizeFloat(locX) + FString(TEXT(",")) +
				FString(TEXT("Y=")) + FString::SanitizeFloat(locY) + FString(TEXT(",")) +
				FString(TEXT("Z=")) + FString::SanitizeFloat(locZ) + FString(TEXT(")")) + FString(TEXT(")")) + FString(TEXT("\""));
		}
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
		float pitch = pStaticMeshActors[i]->GetActorRotation().Pitch;
		float yaw = pStaticMeshActors[i]->GetActorRotation().Yaw;
		float roll = pStaticMeshActors[i]->GetActorRotation().Roll;
		if (i != (pStaticMeshActors.Num() - 1))
		{
			str = FString(TEXT("(")) + FString(TEXT("Pitch=")) + FString::SanitizeFloat(pitch) + FString(TEXT(",")) +
				FString(TEXT("Yaw=")) + FString::SanitizeFloat(yaw) + FString(TEXT(",")) +
				FString(TEXT("Roll=")) + FString::SanitizeFloat(roll) + FString(TEXT(")")) + FString(TEXT(","));
		}
		else
		{
			str = FString(TEXT("(")) + FString(TEXT("Pitch=")) + FString::SanitizeFloat(pitch) + FString(TEXT(",")) +
				FString(TEXT("Yaw=")) + FString::SanitizeFloat(yaw) + FString(TEXT(",")) +
				FString(TEXT("Roll=")) + FString::SanitizeFloat(roll) + FString(TEXT(")")) + FString(TEXT(")")) + FString(TEXT("\""));
		}
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
		AStaticMeshActor* pStaticMeshActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString str;
		float scaleX = pStaticMeshActor->GetStaticMeshComponent()->GetComponentScale().X;
		float scaleY = pStaticMeshActor->GetStaticMeshComponent()->GetComponentScale().Y;
		float scaleZ = pStaticMeshActor->GetStaticMeshComponent()->GetComponentScale().Z;
		if (i != (pStaticMeshActors.Num() - 1))
		{
			str = FString(TEXT("(")) + FString(TEXT("X=")) + FString::SanitizeFloat(scaleX) + FString(TEXT(",")) +
				FString(TEXT("Y=")) + FString::SanitizeFloat(scaleY) + FString(TEXT(",")) +
				FString(TEXT("Z=")) + FString::SanitizeFloat(scaleZ) + FString(TEXT(")")) + FString(TEXT(","));
		}
		else
		{
			str = FString(TEXT("(")) + FString(TEXT("X=")) + FString::SanitizeFloat(scaleX) + FString(TEXT(",")) +
				FString(TEXT("Y=")) + FString::SanitizeFloat(scaleY) + FString(TEXT(",")) +
				FString(TEXT("Z=")) + FString::SanitizeFloat(scaleZ) + FString(TEXT(")")) + FString(TEXT(")")) + FString(TEXT("\""));
		}
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
		AStaticMeshActor* pStaticMeshActor = Cast<AStaticMeshActor>(pStaticMeshActors[i]);
		FString matName = UKismetSystemLibrary::GetDisplayName(pStaticMeshActor->GetStaticMeshComponent()->GetMaterial(0));
		FString str;
		if (i != (pStaticMeshActors.Num() - 1))
			str = FString(TEXT("\"")) + FString(TEXT("\"")) + matName + FString(TEXT("\"")) + FString(TEXT("\"")) + FString(TEXT(","));
		else
			str = FString(TEXT("\"")) + FString(TEXT("\"")) + matName + FString(TEXT("\"")) + FString(TEXT("\"")) + FString(TEXT(")")) + FString(TEXT("\""));
		allStrings.Append(str);
	}
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	allStrings.Append(FString(TEXT(",")));
	allStrings.Append(FString(TEXT("\"")));
	allStrings.Append(FString(TEXT("(")));
	FString cameraLocString = FString(TEXT("X=")) + FString::SanitizeFloat(pNormalCM->m_POVLocation.X) + FString(TEXT(",")) +
		FString(TEXT("Y=")) + FString::SanitizeFloat(pNormalCM->m_POVLocation.Y) + FString(TEXT(",")) +
		FString(TEXT("Z=")) + FString::SanitizeFloat(pNormalCM->m_POVLocation.Z) + FString(TEXT(")")) + FString(TEXT("\""));
	allStrings.Append(cameraLocString);
	allStrings.Append(FString(TEXT(",")));
	allStrings.Append(FString(TEXT("\"")));
	allStrings.Append(FString(TEXT("(")));
	FString cameraRotString = FString(TEXT("Pitch=")) + FString::SanitizeFloat(pNormalCM->m_POVRotation.Pitch) + FString(TEXT(",")) +
		FString(TEXT("Yaw=")) + FString::SanitizeFloat(pNormalCM->m_POVRotation.Yaw) + FString(TEXT(",")) +
		FString(TEXT("Roll=")) + FString::SanitizeFloat(pNormalCM->m_POVRotation.Roll) + FString(TEXT(")")) + FString(TEXT("\""));
	allStrings.Append(cameraRotString);
/*

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
	}*/

	FFileHelper::SaveStringToFile(allStrings, *(projectDir));
}

void ASingleProgressGameMode::SpawnStaticMeshActors(const TArray<FString>& staticMeshNames, const TArray<FVector>& locs, const TArray<FRotator>& rots, const TArray<FVector>& scales, const TArray<FString>& matNames, const FVector& camLoc, const FRotator& camRot)
{
	for (int32 i=0; i<staticMeshNames.Num(); i++)
	{
		FString staticMeshName = staticMeshNames[i];
		if (!m_pCWSingleton->m_pStaticMeshMap.Contains(staticMeshName)) continue;
		UStaticMesh* pStaticMesh = m_pCWSingleton->m_pStaticMeshMap[staticMeshName];
		AStaticMeshActor* pStaticMeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), locs[i], rots[i]);
		pStaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(pStaticMesh);
		pStaticMeshActor->GetStaticMeshComponent()->SetWorldScale3D(scales[i]);
		FString matName = matNames[i];
		if (!m_pCWSingleton->m_pMatMap.Contains(matName)) continue;
		UMaterialInstance* pMat = m_pCWSingleton->m_pMatMap[matName];
		pStaticMeshActor->GetStaticMeshComponent()->SetMaterial(0, pMat);
	}
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	pNormalCM->m_POVLocation = camLoc;
	pNormalCM->m_POVRotation = camRot;
}

void ASingleProgressGameMode::PlayBeamParticle(AActor* pSource, AActor* pTarget, uint8 beamType)
{
	if (!pSource || !pTarget || !m_pSPBeamParticle_1 || !m_pSPBeamParticle_2) return;
	FVector spawnLoc = (pSource->GetActorLocation() + pTarget->GetActorLocation()) / 2.f;
	UParticleSystemComponent* pParticleComponent = NULL;
	if (beamType == 0) pParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(pSource, m_pSPBeamParticle_1, spawnLoc);
	else pParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(pSource, m_pSPBeamParticle_2, spawnLoc);
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
}

void ASingleProgressGameMode::ReadTextureInfo_Implementation()
{

}

void ASingleProgressGameMode::ReadAllEventInfo_Implementation()
{

}

void ASingleProgressGameMode::AddCardTransformInfo(FString transformName, FCardTransformInfo transformInfo)
{
	transformInfo.transformName = transformName;
	if (transformInfo.actionType == 1) m_exploreCardTransformInfo.Add(transformName, transformInfo);
	else if (transformInfo.actionType == 2) m_communicateCardTransformInfo.Add(transformName, transformInfo);
	else if (transformInfo.actionType == 3) m_forgeCardTransformInfo.Add(transformName, transformInfo);
	else if (transformInfo.actionType == 4) m_researchCardTransformInfo.Add(transformName, transformInfo);
}

bool ASingleProgressGameMode::FindEmptyActionCardLoc(FVector& emptyLoc)
{
	FVector panelLoc(m_actionCardBoardLDPoint.X, m_actionCardBoardRTPoint.Y, m_actionPanelZ);
	panelLoc.X += m_actionCardWidth / 2;
	panelLoc.Y -= m_actionCardHeight / 2;
	while (true)
	{
		FLogicVec2D LTPoint(panelLoc.X - m_actionCardWidth / 2, panelLoc.Y + m_actionCardHeight / 2);
		FLogicVec2D RTPoint(panelLoc.X + m_actionCardWidth / 2, panelLoc.Y + m_actionCardHeight / 2);
		FLogicVec2D RBPoint(panelLoc.X + m_actionCardWidth / 2, panelLoc.Y - m_actionCardHeight / 2);
		FLogicVec2D LBPoint(panelLoc.X - m_actionCardWidth / 2, panelLoc.Y - m_actionCardHeight / 2);
		if (RBPoint.X > m_actionCardBoardRTPoint.X && RBPoint.Y < m_actionCardBoardLDPoint.Y) return false;
		TArray<FLogicVec2D> points1;
		points1.Add(LTPoint);
		points1.Add(RTPoint);
		points1.Add(RBPoint);
		points1.Add(LBPoint);
		bool needToShift = false;
		for (int32 i=0; i<m_pActionCards.Num(); i++)
		{
			FLogicVec2D existPanelLoc(m_pActionCards[i]->GetActorLocation().X, m_pActionCards[i]->GetActorLocation().Y);
			FLogicVec2D LTPoint2(existPanelLoc.X - m_actionCardWidth / 2, existPanelLoc.Y + m_actionCardHeight / 2);
			FLogicVec2D RTPoint2(existPanelLoc.X + m_actionCardWidth / 2, existPanelLoc.Y + m_actionCardHeight / 2);
			FLogicVec2D RBPoint2(existPanelLoc.X + m_actionCardWidth / 2, existPanelLoc.Y - m_actionCardHeight / 2);
			FLogicVec2D LBPoint2(existPanelLoc.X - m_actionCardWidth / 2, existPanelLoc.Y - m_actionCardHeight / 2);
			TArray<FLogicVec2D> points2;
			points2.Add(LTPoint2);
			points2.Add(RTPoint2);
			points2.Add(RBPoint2);
			points2.Add(LBPoint2);
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyPolyIntercept(points1, points2);
			if (isIntercept)
			{
				needToShift = true;
				break;
			}
		}
		if (needToShift)
		{
			if (RBPoint.X >= m_actionCardBoardRTPoint.X)
			{
				panelLoc.X = m_actionCardBoardLDPoint.X + m_actionCardWidth / 2;
				panelLoc.Y -= m_panelSweepYDis;
			}
			else panelLoc.X += m_panelSweepXDis;
		}
		else
		{
			emptyLoc.X = panelLoc.X;
			emptyLoc.Y = panelLoc.Y;
			emptyLoc.Z = m_actionPanelZ;
			return true;
		}
	}
	return false;
}

bool ASingleProgressGameMode::FindEmptyCardLoc(FVector& emptyLoc)
{
	FVector cardLoc(m_LDPoint.X, m_RTPoint.Y, m_cardZ);
	cardLoc.X += m_cardWidth / 2;
	cardLoc.Y -= m_cardHeight / 2;
	while (true)
	{
		FLogicVec2D LTPoint(cardLoc.X - m_cardWidth / 2, cardLoc.Y + m_cardHeight / 2);
		FLogicVec2D RTPoint(cardLoc.X + m_cardWidth / 2, cardLoc.Y + m_cardHeight / 2);
		FLogicVec2D RBPoint(cardLoc.X + m_cardWidth / 2, cardLoc.Y - m_cardHeight / 2);
		FLogicVec2D LBPoint(cardLoc.X - m_cardWidth / 2, cardLoc.Y - m_cardHeight / 2);
		if (RBPoint.X > m_RTPoint.X && RBPoint.Y < m_LDPoint.Y) return false;
		TArray<FLogicVec2D> points1;
		points1.Add(LTPoint);
		points1.Add(RTPoint);
		points1.Add(RBPoint);
		points1.Add(LBPoint);
		bool needToShift = false;
		for (int32 i = 0; i < m_pPlayCards.Num(); i++)
		{
			FLogicVec2D existCardLoc(m_pPlayCards[i]->GetActorLocation().X, m_pPlayCards[i]->GetActorLocation().Y);
			FLogicVec2D LTPoint2(existCardLoc.X - m_cardWidth / 2, existCardLoc.Y + m_cardHeight / 2);
			FLogicVec2D RTPoint2(existCardLoc.X + m_cardWidth / 2, existCardLoc.Y + m_cardHeight / 2);
			FLogicVec2D RBPoint2(existCardLoc.X + m_cardWidth / 2, existCardLoc.Y - m_cardHeight / 2);
			FLogicVec2D LBPoint2(existCardLoc.X - m_cardWidth / 2, existCardLoc.Y - m_cardHeight / 2);
			TArray<FLogicVec2D> points2;
			points2.Add(LTPoint2);
			points2.Add(RTPoint2);
			points2.Add(RBPoint2);
			points2.Add(LBPoint2);
			bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyPolyIntercept(points1, points2);
			if (isIntercept)
			{
				needToShift = true;
				break;
			}
		}
		if (needToShift)
		{
			if (RBPoint.X >= m_RTPoint.X)
			{
				cardLoc.X = m_LDPoint.X + m_actionCardWidth / 2;
				cardLoc.Y -= m_panelSweepYDis;
			}
			else cardLoc.X += m_panelSweepXDis;
		}
		else
		{
			emptyLoc.X = cardLoc.X;
			emptyLoc.Y = cardLoc.Y;
			emptyLoc.Z = m_cardZ;
			return true;
		}
	}
	return false;
}

void ASingleProgressGameMode::DeleteCard(APlayCard* pPlayCard, bool shouldUpdateIntrinsicFunction)
{
	if (pPlayCard->m_cardType == 0)
	{
		ANumericCard* pNumericCard = Cast<ANumericCard>(pPlayCard);
		m_pNumericCards.Remove(pNumericCard);
	}
	else if (pPlayCard->m_cardType == 2)
	{
		AActionCard* pActionCard = Cast<AActionCard>(pPlayCard);
		m_pActionCards.Remove(pActionCard);
	}
	m_pPlayCards.Remove(pPlayCard);
	if (pPlayCard->IsValidLowLevel())
	{
		pPlayCard->Destroy();
		pPlayCard->ConditionalBeginDestroy();
	}
	
	if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateCardNbText();
}

void ASingleProgressGameMode::ReadSkillCardInfo_Implementation()
{

}

FOverallIndexSlopeInfo ASingleProgressGameMode::ModifyOverallIndexSlopeByExtraFunction(const FOverallIndexSlopeInfo& slopeIndex)
{
	FOverallIndexSlopeInfo returnInfo = slopeIndex;
	for (int32 i=0; i< m_extraOverallIndexSlopeFuns.Num(); i++)
	{
		if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Mentality Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 4, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Activity Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 1, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Money Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 0, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Suppression Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 6, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Darkness Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 2, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase FlameFaith Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 3, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase SunFaith Slope")
			USPEventFunctionLib::IncreaseIndexSlope(m_extraOverallIndexSlopeFuns[i], 5, returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Index Slope By CardNb")
			USPEventFunctionLib::IncreaseIndexSlopeByCardNb(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Index Slope By Color")
			USPEventFunctionLib::IncreaseIndexSlopeByColorNb(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Index Slope By Action CardNb")
			USPEventFunctionLib::IncreaseIndexSlopeByActionCardNb(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Index Slope By Index Exceed")
			USPEventFunctionLib::IncreaseIndexSlopeIfIndexExceed(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName.Contains("Increase Index Slope By CardName"))
			USPEventFunctionLib::IncreaseIndexSlopeByCardName(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
		else if (m_extraOverallIndexSlopeFuns[i].functionName == "Increase Index Slope By NumericNb")
			USPEventFunctionLib::IncreaseIndexSlopeByNumberNb(m_extraOverallIndexSlopeFuns[i], returnInfo, this);
	}
	return returnInfo;
}

void ASingleProgressGameMode::UpdateOverallIndex(float dT)
{
	/*int32 overallEnergyReduction = m_energyReduction;
	for (TMap<int32, FOverallIndexSlopeInfo>::TConstIterator iter = m_curOverallSlopeIndex.CreateConstIterator(); iter; ++iter)
	{
		if (!m_overallSlopeTickCount.Contains(iter->Key) || iter->Key == 0) continue;
		//m_energyReduction += iter->Value.extraEnergyIncreasePerT;
		overallEnergyReduction += iter->Value.extraEnergyIncreasePerT;
		if (m_overallSlopeTickCount[iter->Key] >= iter->Value.changeInterval)
		{
			FOverallIndexSlopeInfo modifySlopeIndex = ModifyOverallIndexSlopeByExtraFunction(iter->Value);
			m_curOverallIndex.activity += modifySlopeIndex.activity;
			m_curOverallIndex.darkness += modifySlopeIndex.darkness;
			m_curOverallIndex.flameFaith += modifySlopeIndex.flameFaith;
			m_curOverallIndex.money += modifySlopeIndex.money;
			m_curOverallIndex.sunFaith += modifySlopeIndex.sunFaith;
			m_curOverallIndex.suppression += modifySlopeIndex.suppression;
			m_curOverallIndex.mentality += modifySlopeIndex.mentality;
			m_overallSlopeTickCount[iter->Key] = 0;
		}
		else m_overallSlopeTickCount[iter->Key] += dT;
	}

	TArray<FString> deleteEventCodeList;
	for (TMap<FString, FEventOverallIndexSlopInfo>::TConstIterator iter = m_curEventOverallSlopeIndex.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.curInterval < iter->Value.maxInterval)
		{
			overallEnergyReduction += iter->Value.info.extraEnergyIncreasePerT;
			if (iter->Value.curSlopeTick >= iter->Value.info.changeInterval)
			{
				FOverallIndexSlopeInfo modifySlopeIndex = ModifyOverallIndexSlopeByExtraFunction(iter->Value.info);
				m_curOverallIndex.money += modifySlopeIndex.money;
				m_curOverallIndex.activity += modifySlopeIndex.activity;
				m_curOverallIndex.darkness += modifySlopeIndex.darkness;
				m_curOverallIndex.flameFaith += modifySlopeIndex.flameFaith;
				m_curOverallIndex.mentality += modifySlopeIndex.mentality;
				m_curOverallIndex.sunFaith += modifySlopeIndex.sunFaith;
				m_curOverallIndex.suppression += modifySlopeIndex.suppression;
				m_curEventOverallSlopeIndex[iter->Key].curSlopeTick = 0;
			}
			else m_curEventOverallSlopeIndex[iter->Key].curSlopeTick += dT;
			m_curEventOverallSlopeIndex[iter->Key].curInterval += dT;
		}
		else
		{
			deleteEventCodeList.Add(iter->Key);
		}
	}

	for (int32 i=0; i<deleteEventCodeList.Num(); i++)
	{
		m_maxOverallIndexValue.activity -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.activity;
		m_maxOverallIndexValue.darkness -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.darkness;
		m_maxOverallIndexValue.energy -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.energy;
		m_maxOverallIndexValue.flameFaith -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.flameFaith;
		m_maxOverallIndexValue.life -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.life;
		m_maxOverallIndexValue.money -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.money;
		m_maxOverallIndexValue.mentality -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.mentality;
		m_maxOverallIndexValue.sunFaith -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.sunFaith;
		m_maxOverallIndexValue.suppression -= m_curEventOverallSlopeIndex[deleteEventCodeList[i]].limitChangeInfo.suppression;
		m_curEventOverallSlopeIndex.Remove(deleteEventCodeList[i]);
	}

	if (m_curOverallIndex.activity >= m_maxOverallIndexValue.activity) m_curOverallIndex.activity = m_maxOverallIndexValue.activity;
	if (m_curOverallIndex.activity <= 0) m_curOverallIndex.activity = 0;
	if (m_curOverallIndex.darkness >= m_maxOverallIndexValue.darkness) m_curOverallIndex.darkness = m_maxOverallIndexValue.darkness;
	if (m_curOverallIndex.darkness <= 0) m_curOverallIndex.darkness = 0;
	if (m_curOverallIndex.flameFaith >= m_maxOverallIndexValue.flameFaith) m_curOverallIndex.flameFaith = m_maxOverallIndexValue.flameFaith;
	if (m_curOverallIndex.flameFaith <= 0) m_curOverallIndex.flameFaith = 0;
	if (m_curOverallIndex.money >= m_maxOverallIndexValue.money) m_curOverallIndex.money = m_maxOverallIndexValue.money;
	if (m_curOverallIndex.money <= 0) m_curOverallIndex.money = 0;
	if (m_curOverallIndex.mentality >= m_maxOverallIndexValue.mentality) m_curOverallIndex.mentality = m_maxOverallIndexValue.mentality;
	if (m_curOverallIndex.mentality <= 0) m_curOverallIndex.mentality = 0;
	if (m_curOverallIndex.sunFaith >= m_maxOverallIndexValue.sunFaith) m_curOverallIndex.sunFaith = m_maxOverallIndexValue.sunFaith;
	if (m_curOverallIndex.sunFaith <= 0) m_curOverallIndex.sunFaith = 0;
	if (m_curOverallIndex.suppression >= m_maxOverallIndexValue.suppression) m_curOverallIndex.suppression = m_maxOverallIndexValue.suppression;
	if (m_curOverallIndex.suppression <= 0) m_curOverallIndex.suppression = 0;

	if (m_pSPPC->m_pSPMenu)
	{
		m_pSPPC->m_pSPMenu->m_pMoneyBar->SetText(FText::FromString(money));
	}
	if (m_curEnergyReductionTime < m_energyReductionInterval)
		m_curEnergyReductionTime += dT;
	else
	{
		int32 modifyEnergyReduction = overallEnergyReduction;
		for (int32 i = 0; i < m_extraOverallIndexSlopeFuns.Num(); i++)
		{
			if (m_extraOverallIndexSlopeFuns[i].functionName == "Release Energy Reduction")
				modifyEnergyReduction = USPEventFunctionLib::IncreaseEnergySlope(m_extraOverallIndexSlopeFuns[i], modifyEnergyReduction);
		}
		m_curOverallIndex.energy -= modifyEnergyReduction;
		if (m_curOverallIndex.energy < 0)
		{
			m_curOverallIndex.energy = 0;
			m_curLife -= m_lifeReduction;
			if (m_curLife <= 0) m_curLife = 0;
			else if (m_curLife >= m_maxOverallIndexValue.life) m_curLife = m_maxOverallIndexValue.life;
		}
		else if (m_curOverallIndex.energy >= m_maxOverallIndexValue.energy)
		{
			m_curOverallIndex.energy = m_maxOverallIndexValue.energy;
		}
		m_curEnergyReductionTime = 0;
	}*/
}

void ASingleProgressGameMode::InitialSingleprogressInfo(uint8 initialType)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	m_pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	ReadTextureInfo();
	ReadAllEventInfo();
	ReadShadowSkeletalMesh();
	ReadCardCombineDemoInfo();

	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	
	m_pSPPC->m_pWidgetManager->m_language = pCWGI->m_language;
	DecideWeather();
	NotifySetSkyColorMatParam(pCWGI->m_curPlayerSPInfo.curProgress, true, false);

	m_pEventNodeManager = NewObject<UEventNodeManager>(this, m_pEventNodeManagerClass);
	m_pEventNodeManager->m_language = m_pSPPC->m_pWidgetManager->m_language;
	m_pSPPC->m_pEventNodeManager = m_pEventNodeManager;

	m_pSPPC->m_dragCardZ = m_cardZ;
	m_pSPPC->LoadSPMenu();
	m_pSPPC->ReadPlayerCharacterSkills("Lucian");
	if (initialType == 2)
	{
		//战斗结束进入界面
		m_pSPPC->LoadGame("BattleTempSlot", 0, 1);
		if (m_isInBossBattleLayer) m_pSPPC->m_pSPMenu->AddBossBattleProgressBall();
		//重新设置小进度条，大进度条+1
		int32 maxActionNodeNb = m_maxActionNodeNbPerLine;
		if (m_isInBossBattleLayer) maxActionNodeNb += 1;
		if (m_curEventNodeNb >= maxActionNodeNb)
		{
			if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(0, m_curEventNodeLayerNb);
		}
		else
		{
			if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
		}
	}
	else if (initialType == 3)
	{
		//切换大场景进入大流程场景
		m_pSPPC->LoadGame("SwitchLandscape", 0, 2);
		m_curTickTime = 0;
		m_curTickCount = 0;
		NotifyLoadCalenderMenu();
	}
	else
	{
		//初始化进入或读取进入场景
		if (pCWGI->m_curPlayerSPInfo.isInitial)
		{
			m_pSPPC->ReadFCInfos();
			m_pSPPC->ReadCharacterAppearanceInfo(pCWGI->m_curPlayerSPInfo.characterName);
			GenerateRandActionNodeWeb(false);
			for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = m_pSPPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
			{
				pCWGI->m_curPlayerSPInfo.availableFCList.Add(iter->Key, 0);
			}
			for (int32 i=0; i<m_pSPPC->m_characterAppearanceInfo.Num(); i++)
			{
				pCWGI->m_curPlayerSPInfo.availableAppearanceList.Add(m_pSPPC->m_characterAppearanceInfo[i].appearanceName, 0);
			}
			m_pSPPC->m_characterAppearanceInfo.Empty();
			m_pSPPC->m_FCInfos.Empty();
			//如果是初次登陆，这里要随机生成技能填充m_curPlayerSPInfo
			TArray<FString> chopSkillNameList;
			TArray<FString> dodgeSkillNameList;
			TArray<FString> blockSkillNameList;
			TArray<FString> normalSkillNameList;
			for (int32 i=0; i<m_pSPPC->m_playerSkillInfos.Num(); i++)
			{
				if (m_pSPPC->m_playerSkillInfos[i].skillType == 0)
				{
					if (m_pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(m_pSPPC->m_playerSkillInfos[i].skillName))
					{
						chopSkillNameList.Add(m_pSPPC->m_playerSkillInfos[i].skillName);
					}
				}
				else if (m_pSPPC->m_playerSkillInfos[i].skillType == 1)
				{
					if (m_pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(m_pSPPC->m_playerSkillInfos[i].skillName))
					{
						blockSkillNameList.Add(m_pSPPC->m_playerSkillInfos[i].skillName);
					}
				}
				else if (m_pSPPC->m_playerSkillInfos[i].skillType == 3)
				{
					if (m_pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(m_pSPPC->m_playerSkillInfos[i].skillName))
					{
						dodgeSkillNameList.Add(m_pSPPC->m_playerSkillInfos[i].skillName);
					}
				}
				else if (m_pSPPC->m_playerSkillInfos[i].skillType == 2)
				{
					if (m_pSPPC->m_playerSkillInfos[i].isInitial || pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(m_pSPPC->m_playerSkillInfos[i].skillName))
					{
						normalSkillNameList.Add(m_pSPPC->m_playerSkillInfos[i].skillName);
					}
				}
			}
			for (int32 i=0; i<m_pSPPC->m_pSPMenu->m_pChopSkillIcons.Num(); i++)
			{
				if (chopSkillNameList.Num() <= 0)
				{
					break;
				}
				int32 randNb = FMath::RandRange(0, chopSkillNameList.Num() - 1);
				pCWGI->m_curPlayerSPInfo.selectSkillInfo.chopSkillName = chopSkillNameList[randNb];
				m_pSPPC->m_pSPMenu->m_pChopSkillIcons[i]->m_skillName = chopSkillNameList[randNb];
			}
			for (int32 i=0; i<m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons.Num(); i++)
			{
				if (dodgeSkillNameList.Num() <= 0)
				{
					break;
				}
				int32 randNb = FMath::RandRange(0, dodgeSkillNameList.Num() - 1);
				pCWGI->m_curPlayerSPInfo.selectSkillInfo.dodgeSkillName = dodgeSkillNameList[randNb];
				m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons[i]->m_skillName = dodgeSkillNameList[randNb];
			}
			for (int32 i = 0; i < m_pSPPC->m_pSPMenu->m_pBlockSkillIcons.Num(); i++)
			{
				if (blockSkillNameList.Num() <= 0)
				{
					break;
				}
				int32 randNb = FMath::RandRange(0, blockSkillNameList.Num() - 1);
				pCWGI->m_curPlayerSPInfo.selectSkillInfo.blockSkillName = blockSkillNameList[randNb];
				m_pSPPC->m_pSPMenu->m_pBlockSkillIcons[i]->m_skillName = blockSkillNameList[randNb];
			}
			for (int32 i=0; i<m_pSPPC->m_pSPMenu->m_pNormalSkillIcons.Num(); i++)
			{
				if (normalSkillNameList.Num() <= 0)
				{
					break;
				}
				int32 randNb = FMath::RandRange(0, normalSkillNameList.Num() - 1);
				pCWGI->m_curPlayerSPInfo.selectSkillInfo.normalSkillNames.Add(normalSkillNameList[randNb]);
				m_pSPPC->m_pSPMenu->m_pNormalSkillIcons[i]->m_skillName = normalSkillNameList[randNb];
				normalSkillNameList.RemoveAt(randNb);
			}
		}
		else
		{
			m_pSPPC->LoadGame(pCWGI->m_curPlayerSPInfo.progressName, 0, 0);
			m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
		}
		//event cards should be spawned here
		FVector firstSALoc = m_SAOriginalLoc - ((float)m_actionNodeList[m_curNodeNb].actionNodeBriefInfoList.Num() - 1.f) * 0.5f * FVector(m_SADemoOffset, 0, 0);
		for (int32 i=0; i<m_actionNodeList[m_curNodeNb].actionNodeBriefInfoList.Num(); i++)
		{
			FVector SASpawnLoc = firstSALoc + (float)i * 0.5f * FVector(m_SADemoOffset, 0, 0);
			AEventCard* pEventCard = GetWorld()->SpawnActor<AEventCard>(m_eventCardClass, SASpawnLoc, FRotator::ZeroRotator);
			pEventCard->NotifyInitialCard();

			pEventCard->m_cardType = m_actionNodeList[m_curNodeNb].actionNodeBriefInfoList[i].actionType;
			pEventCard->m_pCardMesh->ComponentTags.Add(FName(TEXT("EventCard")));
			pEventCard->m_pCardMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Block);
			if (pEventCard->m_pCardImageMesh)
			{
				UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pEventCard, m_pSurfaceMatRoundButton);
				pEventCard->m_pCardImageMesh->SetMaterial(0, pMI);
				UTexture* pTexture = m_eventCardTypeTextureMap[pEventCard->m_cardType];
				pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
			}
			//计算等级，然后赋值m_eventCardInfo
			pEventCard->m_nodeName = m_actionNodeList[m_curNodeNb].actionNodeBriefInfoList[i].nodeName;
			pEventCard->m_rewardType = m_actionNodeList[m_curNodeNb].actionNodeBriefInfoList[i].rewardType;
			if (pEventCard->m_pRewardMesh)
			{
				UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pEventCard, m_pMatCardAttachment);
				pEventCard->m_pRewardMesh->SetMaterial(0, pMI);
				UTexture* pTexture = m_rewardTypeTextureMap[pEventCard->m_rewardType];
				pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
			}
			pEventCard->StartWarpIn();
		}
		//Bonus should be calculate here
		NotifyLoadCalenderMenu();
	}
	//这里要填充SPMenu界面的那些技能按钮
	for (int32 i = 0; i < m_pSPPC->m_pSPMenu->m_pChopSkillIcons.Num(); i++)
	{
		for (int32 j = 0; j < m_pSPPC->m_playerSkillInfos.Num(); j++)
		{
			if (m_pSPPC->m_playerSkillInfos[j].skillName != m_pSPPC->m_pSPMenu->m_pChopSkillIcons[i]->m_skillName) continue;
			UMaterialInstanceDynamic* pMDI = m_pSPPC->m_pSPMenu->m_pChopSkillIcons[i]->m_pSkillImage->GetDynamicMaterial();
			pMDI->SetTextureParameterValue(FName("Front"), m_pSPPC->m_playerSkillInfos[j].pTexture);
			UTEnergyBall* pAttributeBall = CreateWidget<UTEnergyBall>(m_pSPPC, m_pSPPC->m_pWidgetManager->m_widgetClassMap["AttributeBall"]);
			pAttributeBall->NotifyInitial();
			for (int32 k = 0; k < m_pSPPC->m_playerSkillInfos[j].attributeList.Num(); k++)
			{
				if (m_pSPPC->m_playerSkillInfos[j].attributeList[k] == m_pSPPC->m_playerSkillInfos[j].mutationType)
				{
					if (m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap.Contains(m_pSPPC->m_playerSkillInfos[j].mutationType))
					{
						pAttributeBall->m_pImage->SetBrushFromTexture(m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap[m_pSPPC->m_playerSkillInfos[j].mutationType]);
					}
					m_pSPPC->m_pSPMenu->m_pChopSkillIcons[i]->m_pAttributeVerticalBox->AddChild(pAttributeBall);
					break;
				}
			}
			break;
		}
	}
	for (int32 i = 0; i < m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons.Num(); i++)
	{
		for (int32 j = 0; j < m_pSPPC->m_playerSkillInfos.Num(); j++)
		{
			if (m_pSPPC->m_playerSkillInfos[j].skillName != m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons[i]->m_skillName) continue;
			UMaterialInstanceDynamic* pMDI = m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons[i]->m_pSkillImage->GetDynamicMaterial();
			pMDI->SetTextureParameterValue(FName("Front"), m_pSPPC->m_playerSkillInfos[j].pTexture);
			UTEnergyBall* pAttributeBall = CreateWidget<UTEnergyBall>(m_pSPPC, m_pSPPC->m_pWidgetManager->m_widgetClassMap["AttributeBall"]);
			pAttributeBall->NotifyInitial();
			for (int32 k = 0; k < m_pSPPC->m_playerSkillInfos[j].attributeList.Num(); k++)
			{
				if (m_pSPPC->m_playerSkillInfos[j].attributeList[k] == m_pSPPC->m_playerSkillInfos[j].mutationType)
				{
					if (m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap.Contains(m_pSPPC->m_playerSkillInfos[j].mutationType))
					{
						pAttributeBall->m_pImage->SetBrushFromTexture(m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap[m_pSPPC->m_playerSkillInfos[j].mutationType]);
					}
					m_pSPPC->m_pSPMenu->m_pDodgeSkillIcons[i]->m_pAttributeVerticalBox->AddChild(pAttributeBall);
					break;
				}
			}
			break;
		}
	}
	for (int32 i = 0; i < m_pSPPC->m_pSPMenu->m_pNormalSkillIcons.Num(); i++)
	{
		for (int32 j = 0; j < m_pSPPC->m_playerSkillInfos.Num(); j++)
		{
			if (m_pSPPC->m_playerSkillInfos[j].skillName != m_pSPPC->m_pSPMenu->m_pNormalSkillIcons[i]->m_skillName) continue;
			UMaterialInstanceDynamic* pMDI = m_pSPPC->m_pSPMenu->m_pNormalSkillIcons[i]->m_pSkillImage->GetDynamicMaterial();
			pMDI->SetTextureParameterValue(FName("Front"), m_pSPPC->m_playerSkillInfos[j].pTexture);
			UTEnergyBall* pAttributeBall = CreateWidget<UTEnergyBall>(m_pSPPC, m_pSPPC->m_pWidgetManager->m_widgetClassMap["AttributeBall"]);
			pAttributeBall->NotifyInitial();
			for (int32 k = 0; k < m_pSPPC->m_playerSkillInfos[j].attributeList.Num(); k++)
			{
				if (m_pSPPC->m_playerSkillInfos[j].attributeList[k] == m_pSPPC->m_playerSkillInfos[j].mutationType)
				{
					if (m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap.Contains(m_pSPPC->m_playerSkillInfos[j].mutationType))
					{
						pAttributeBall->m_pImage->SetBrushFromTexture(m_pSPPC->m_pWidgetManager->m_pAttributeTextureMap[m_pSPPC->m_playerSkillInfos[j].mutationType]);
					}
					m_pSPPC->m_pSPMenu->m_pNormalSkillIcons[i]->m_pAttributeVerticalBox->AddChild(pAttributeBall);
					break;
				}
			}
			break;
		}
	}
	
	if (!pCWGI->m_doneTutorialSteps.Contains(m_fixTutorialSerialNames[0])) RefreshTutorial(m_fixTutorialSerialNames[0], true, 0);
	else RefreshTutorial("NULL", false, 0);
	//DrawDebugPoint(GetWorld(), FVector(-300,-361,142), 20, FColor::Red, false, 20);
	m_curProgressMaxTick = m_progressMaxTickMap[pCWGI->m_curPlayerSPInfo.curProgress];
	m_curUpdateOIDemoActorTick = m_defaultUpdateOIDemoActorInterval;
	//if (pSPPC->m_pSPMenu) pSPPC->m_pSPMenu->UpdateCardNbText(m_pPlayCards, m_pActionCards, m_pNumericCards, m_maxPlayCardNb, m_maxActionCardNb);
	NotifyFadeIn();
	m_tickFlag = true;
}

void ASingleProgressGameMode::AddTinyMapInfoToClassificationInfo(const FString& mapName, const uint8& classification, const TArray<uint8>& gameTypes,const uint8& tinyMapLevel)
{
	bool findClassification = false;
	for (int32 i=0; i<m_tinyMapClassificationList.Num(); i++)
	{
		if (m_tinyMapClassificationList[i].classificationLevel != classification) continue;
		bool mapExist = false;
		for (int32 j=0; j<m_tinyMapClassificationList[i].tinyMapList.Num(); j++)
		{
			if (m_tinyMapClassificationList[i].tinyMapList[j].tinyMapName == mapName)
			{
				mapExist = true;
				break;
			}
		}
		if (mapExist) return;
		FTinyMapInfo newTinyMapInfo;
		newTinyMapInfo.classificationLevel = classification;
		newTinyMapInfo.tinyMapLevel = tinyMapLevel;
		newTinyMapInfo.tinyMapName = mapName;
		newTinyMapInfo.gameTypes = gameTypes;
		m_tinyMapClassificationList[i].tinyMapList.Add(newTinyMapInfo);
		findClassification = true;
		break;
	}
	if (findClassification) return;
	FTinyMapClassificationInfo newClassification;
	newClassification.classificationLevel = classification;
	FTinyMapInfo newTinyMapInfo;
	newTinyMapInfo.classificationLevel = classification;
	newTinyMapInfo.tinyMapLevel = tinyMapLevel;
	newTinyMapInfo.tinyMapName = mapName;
	newTinyMapInfo.gameTypes = gameTypes;
	newClassification.tinyMapList.Add(newTinyMapInfo);
	m_tinyMapClassificationList.Add(newClassification);
}

void ASingleProgressGameMode::ReadAllEvents_Implementation()
{

}

void ASingleProgressGameMode::InitialEvent(FEventGroupInfo event)
{
	if (event.groupType == 0)
	{
		//说明属于周期性事件
		m_periodicEvents.Add(event);
	}
	else if (event.groupType == 1 || event.groupType == 3)
		m_potentialEvents.Add(event);
	else
		m_initialEvents.Add(event);
}

int32 ASingleProgressGameMode::GenerateEventCode()
{
	int32 i = 0;
	while (true)
	{
		if (m_existEventCodeNameMap.Contains(i)) i += 1;
		else break;
	}
	return i;
}

void ASingleProgressGameMode::TriggerChoiceEvent(FEventFunction fun)
{
	if (fun.functionName == "GetRandDiceSkillCard")
	{
		ReadDiceSkillPS(1);
		TArray<FString> allSkills;
		for (TMap<FString, FDiceBattleAndTheorizeSkillInfo>::TConstIterator iter = m_pSPPC->m_allDiceBattleSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.level != fun.values[1]) continue;
			allSkills.Add(iter->Key);
		}
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		for (int32 i=0; i<fun.values[0]; i++)
		{
			int32 randNb = FMath::RandRange(0, allSkills.Num() - 1);
			if (pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap.Contains(allSkills[randNb]))
				pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap[allSkills[randNb]] = pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap[allSkills[randNb]] + 1;
			else
				pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap.Add(allSkills[randNb], 1);
		}
		m_pSPPC->m_allDiceBattleSkillInfos.Empty();

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(2, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(2, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "GetRandTheorizeSkillCard")
	{
		NotifyGetTheorizeParamFromDT(0, 1);
		TArray<FString> allSkills;
		for (TMap<FString, FDiceBattleAndTheorizeSkillInfo>::TConstIterator iter = m_pSPPC->m_alltheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.level != fun.values[1]) continue;
			allSkills.Add(iter->Key);
		}
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		for (int32 i = 0; i < fun.values[0]; i++)
		{
			int32 randNb = FMath::RandRange(0, allSkills.Num() - 1);
			if (pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap.Contains(allSkills[randNb]))
				pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap[allSkills[randNb]] = pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap[allSkills[randNb]] + 1;
			else
				pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap.Add(allSkills[randNb], 1);
		}
		m_pSPPC->m_alltheorizeSkillInfos.Empty();

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(3, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(3, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	/*else if (fun.functionName.Contains("CursedCardNextBattle_"))
	{
		FString targetAndEffect = fun.functionName.RightChop(21);
		FString targetStr = targetAndEffect.Left(3);
		FString effectName = targetAndEffect.RightChop(4);
		FCursedCardInfo cursedCardInfo;
		cursedCardInfo.eventFunction.functionName = effectName;
		cursedCardInfo.eventFunction.values = fun.values;
		if (targetStr == "ToE") cursedCardInfo.exertTargetType = 0;
		else if (targetStr == "ToP") cursedCardInfo.exertTargetType = 1;
		else if (targetStr == "ToH") cursedCardInfo.exertTargetType = 2;
		//cursedCardInfo.cursedType = 1;
		m_curCursedCardInfo.Add(cursedCardInfo);
	}*/
	else if (fun.functionName == "GetRandWeapon")
	{
		TArray<FString> allWeapons;
		for (TMap<FString, FCardTextureAndTags>::TConstIterator iter = m_pPlayCardTextureMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value.tags.Contains("Weapon Lv1") || iter->Value.cardValueLevel != fun.values[0]) continue;
			allWeapons.Add(iter->Key);
		}
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (pCWGI->m_curPlayerSPInfo.availableEquipList.Num() >= m_maxWeaponNb) return;
		int32 randWeaponNb = FMath::RandRange(0, allWeapons.Num() - 1);
		pCWGI->m_curPlayerSPInfo.availableEquipList.Add(allWeapons[randWeaponNb]);

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(4, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(4, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "IncreaseMoney")
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (pCWGI->m_curPlayerSPInfo.money + fun.values[0] >= m_maxMoney) pCWGI->m_curPlayerSPInfo.money = m_maxMoney;
		else if (pCWGI->m_curPlayerSPInfo.money + fun.values[0] <= 0) pCWGI->m_curPlayerSPInfo.money = 0;

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(5, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(5, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "IncreaseMaxHp")
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		//if (pCWGI->m_curPlayerSPInfo.money + fun.values[0] >= m_maxMoney) pCWGI->m_curPlayerSPInfo.money = m_maxMoney;
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseLife"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseLife", fun.values[0]);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] + fun.values[0];
		FCharacterAttributeInfo attributeInfo = GetCharacterAttributeInfo(pCWGI->m_curPlayerSPInfo.characterName);
		if (attributeInfo.maxLife + pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"]*pCWGI->m_attributeIncreaseValueMap["IncreaseLife"] <= 0)
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] + 1;

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(6, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(6, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "IncreaseAtk")
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		//if (pCWGI->m_curPlayerSPInfo.money + fun.values[0] >= m_maxMoney) pCWGI->m_curPlayerSPInfo.money = m_maxMoney;
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseAtk"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseAtk", fun.values[0]);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] + fun.values[0];
		FCharacterAttributeInfo attributeInfo = GetCharacterAttributeInfo(pCWGI->m_curPlayerSPInfo.characterName);
		if (attributeInfo.maxLife + pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] * pCWGI->m_attributeIncreaseValueMap["IncreaseAtk"] <= 0)
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] + 1;

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(7, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(7, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "IncreaseMaxDfc")
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		//if (pCWGI->m_curPlayerSPInfo.money + fun.values[0] >= m_maxMoney) pCWGI->m_curPlayerSPInfo.money = m_maxMoney;
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseDfc"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseDfc", fun.values[0]);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] + fun.values[0];
		FCharacterAttributeInfo attributeInfo = GetCharacterAttributeInfo(pCWGI->m_curPlayerSPInfo.characterName);
		if (attributeInfo.maxLife + pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] * pCWGI->m_attributeIncreaseValueMap["IncreaseDfc"] <= 0)
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] + 1;

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(8, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(8, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
	else if (fun.functionName == "LoseWeapon")
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		for (int32 i=0; i<fun.values[0]; i++)
		{
			if (pCWGI->m_curPlayerSPInfo.availableEquipList.Num() <= 0) break;
			int32 randNb = FMath::RandRange(0, pCWGI->m_curPlayerSPInfo.availableEquipList.Num() - 1);
			pCWGI->m_curPlayerSPInfo.availableEquipList.RemoveAt(randNb);
		}

		FString prefixWords = "";
		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
			prefixWords = m_pSPPC->ReadDemoWordPrefix(9, true);
		else
			prefixWords = m_pSPPC->ReadDemoWordPrefix(9, false);
		m_pSPPC->m_pSPMenu->ShowDemoText(prefixWords);
	}
}

void ASingleProgressGameMode::AddEventInfo(const FEventCardInfo& eventCardInfo)
{
	if (!m_allEventInfoMap.Contains(eventCardInfo.defaultActionType))
	{
		FEventCardInfoList newList;
		newList.eventCardInfoList.Add(eventCardInfo);
		m_allEventInfoMap.Add(eventCardInfo.defaultActionType, newList);
	}
	else
	{
		m_allEventInfoMap[eventCardInfo.defaultActionType].eventCardInfoList.Add(eventCardInfo);
	}
}

void ASingleProgressGameMode::UpdateActionNode(uint8 updateType)
{
	m_curNodeNb += 1;
	
	//delete original shadowactors first
	while (m_pShadowActorList.Num() > 0)
	{
		DeleteShadowActor(m_pShadowActorList.Last());
	}
	if (updateType == 2)
	{
		//this is the last available node
		
		/*UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGameInstance);
		if (pCWGI->m_curPlayerSPInfo.curProgress >= 2)
		{
			//this is ending, we should load ending menu
			ReadAllEndingInfo(0);
			m_pSPPC->LoadEndSPMenu(3);
			GetWorldTimerManager().SetTimer(m_endSPTimeHandler, m_pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_gotPictureActivateTextTime, false);
		}
		else if (pCWGI->m_curPlayerSPInfo.curProgress == 0)
		{
			pCWGI->m_curPlayerSPInfo.curProgress += 1;
			pCWGI->m_battleState = 3;
			m_pSPPC->SaveGame("SwitchLandscape", 0);
			UGameplayStatics::OpenLevel(this, FName("SingleProgressMap_Desert"));
		}
		else if (pCWGI->m_curPlayerSPInfo.curProgress == 1)
		{
			pCWGI->m_curPlayerSPInfo.curProgress += 1;
			pCWGI->m_battleState = 3;
			m_pSPPC->SaveGame("SwitchLandscape", 0);
			UGameplayStatics::OpenLevel(this, FName("SingleProgressMap_Forest"));
		}*/
	}
	else
	{
		//we should spawn shadowactors like initialsingleprogressinfo
	}

}

void ASingleProgressGameMode::DecideWeather()
{
	int32 totalWeight = 0;
	TMap<uint8, int32> weightList;
	for (TMap<uint8, int32>::TConstIterator iter = m_weatherWeight.CreateConstIterator(); iter; ++iter)
	{
		totalWeight += iter->Value;
		weightList.Add(iter->Key, totalWeight);
	}
	int32 randWeight = FMath::RandRange(0, totalWeight);
	uint8 weather = 0;
	for (TMap<uint8, int32>::TConstIterator iter = weightList.CreateConstIterator(); iter; ++iter)
	{
		if (randWeight > iter->Value) continue;
		weather = iter->Key;
		break;
	}
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (weather == 0)
	{
		//It means it's special weather now, which depends on which map it is, for example
		//if player is in desert map, it's sand storm
		if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 0) weather = 0;
		else if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 1) weather = 1;
		else if (pCWGameInstance->m_curPlayerSPInfo.curProgress == 2) weather = 2;
	}
	pCWGameInstance->m_weatherType = weather;
}

void ASingleProgressGameMode::DecideDayOrNight()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	int32 randNb = FMath::RandRange(0, 100);
	if (randNb < 50) pCWGameInstance->m_dayOrNight = true;
	else pCWGameInstance->m_dayOrNight = false;
}

void ASingleProgressGameMode::CalculateBonus(int32 totalCardNb, uint8 type, bool winFlag, TArray<FString>& bonusCards)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	TMap<uint8, int32> tempBonusNbs;
	for (TMap<uint8, float>::TConstIterator iter = m_allBonusTypeProportion; iter; ++iter)
	{
		int32 fluctuatedNb = iter->Value / 100.f * m_fluctuatedTotalBonusNb;
		tempBonusNbs.Add(iter->Key, fluctuatedNb);
	}
	TMap<uint8, int32> possibleBonus;
	for (TMap<uint8, int32>::TConstIterator iter = pCWGI->m_curPlayerSPInfo.bonusAmount.CreateConstIterator(); iter; ++iter)
	{
		possibleBonus.Add(iter->Key, 0);
		if (!tempBonusNbs.Contains(iter->Key)) continue;
		//The actual available bonus nb should be equal to fluctuatedMaxNb minus bonus nb already given to player
		possibleBonus[iter->Key] = tempBonusNbs[iter->Key] - iter->Value;
	}
	//type represents what bonus is
	// type == 0 battle, type == 1 dice, type == 2 theorize
	if (type == 0)
	{
		// This variable is used to tell whether skill bonus is given to player
		// If skill is given to player, next bonus should be attribute
		bool isSkillGiven = false;
		for (int32 i = 0; i < totalCardNb; i++)
		{
			if (possibleBonus[0] > 0)
			{
				//which means player can get new skill as bonus, but we should still use rand function to decide whether skill is given
				int32 randBonus = FMath::RandRange(0, 1);
				if (randBonus == 0)
				{
					isSkillGiven = true;
					//we should take skills that are not occupied by player to be optional bonus
					TArray<FString> availableSkills;
					for (int32 i=0; i< m_pSPPC->m_playerSkillInfos.Num(); i++)
					{
						if (pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(m_pSPPC->m_playerSkillInfos[i].skillName))
							continue;
						availableSkills.Add(m_pSPPC->m_playerSkillInfos[i].skillName);
					}
					TArray<FString> skillChoices;
					for (int32 i=0; i<m_maxBonusChoiseCardNb; i++)
					{
						if (availableSkills.Num() <= 0) break;
						int32 randNb = FMath::RandRange(0, availableSkills.Num() - 1);
						skillChoices.Add(availableSkills[randNb]);
						availableSkills.RemoveAt(randNb);
					}
				}
				else
				{
					//attribute bonus should be random given to player
					// 0 - fire
					// 1 - water
					// 2 - freeze
					// 3 - 
					int32 attributeNb = FMath::RandRange(0, 6);
					FString bonusCardName = "Attribute_" + FString::FromInt(attributeNb);
					bonusCards.Add(bonusCardName);
				}
			}
			else
			{
				// If skills are not allowed to be given to player, attributes should be given
				// 0 - fire
				// 1 - water
				// 2 - freeze
				// 3 - 
				int32 attributeNb = FMath::RandRange(0, 6);
				FString bonusCardName = "Attribute_" + FString::FromInt(attributeNb);
				bonusCards.Add(bonusCardName);
			}
		}
	}
	else if (type == 1)
	{
		// If player win dice game, player can get money
		bonusCards.Add("Money");
	}
	else if (type == 2)
	{
		// Number of relics is limit
		bool isRelicsGiven = false;
		for (int32 i = 0; i < totalCardNb; i++)
		{
			int32 randBonus = FMath::RandRange(0, 1);
			if (possibleBonus[3] > 0)
			{
				if (randBonus == 0)
				{
					isRelicsGiven = true;
					//We should search all available relics
				}
				else
				{
					// PhysAttribute could be Hp or Atk, which should be given randomly
					int32 randPhysBonus = FMath::RandRange(0, 1);
					if (randPhysBonus == 0)
					{

					}
					else
					{

					}
				}
			}
			else
			{
				int32 randPhysBonus = FMath::RandRange(0, 1);
				if (randPhysBonus == 0)
				{

				}
				else
				{

				}
			}
		}
		
	}
}

void ASingleProgressGameMode::InterpretBonus()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	for (int32 i=0; i < m_pSPPC->m_pCardSelectMenu->m_allBonusCardNames.Num(); i++)
	{
		if (m_pSPPC->m_pCardSelectMenu->m_allBonusCardNames[i].Contains("MustBonusCard_"))
		{
			FString bonusName = m_pSPPC->m_pCardSelectMenu->m_allBonusCardNames[i].RightChop(14);
			if (bonusName == "Physics Attribute Increase")
			{
				if (pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Contains(0))
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[0] = pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[0] + 1;
				else
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Add(0, 1);
			}
			else if (bonusName == "Knowledge Increase")
			{
				if (pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Contains(3))
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[1] = pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[3] + 1;
				else
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Add(1, 1);
			}
			else if (bonusName == "Mentality Increase")
			{
				/*if (pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Contains(1))
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[1] = pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[1] + 1;
				else
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Add(1, 1);*/
				if (pCWGameInstance->m_curPlayerSPInfo.attributeIncreaseMap.Contains("Mentality"))
					pCWGameInstance->m_curPlayerSPInfo.attributeIncreaseMap["Mentality"] = pCWGameInstance->m_curPlayerSPInfo.attributeIncreaseMap["Mentality"] + 1;
				else
					pCWGameInstance->m_curPlayerSPInfo.attributeIncreaseMap.Add("Mentality", 1);
			}
			else if (bonusName == "UnlockAppearance")
			{
				if (pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Contains(4))
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[2] = pCWGameInstance->m_curPlayerSPInfo.unlockPointMap[4] + 1;
				else
					pCWGameInstance->m_curPlayerSPInfo.unlockPointMap.Add(2, 1);
			}
		}
		else if (m_pSPPC->m_pCardSelectMenu->m_allBonusCardNames[i].Contains("ChoiceBonusCard_"))
		{
			
		}
	}
}

void ASingleProgressGameMode::UpdateCursedCardRound()
{
	/*int32 i = 0;
	while (i < m_curCursedCardInfo.Num())
	{
		if (m_curCursedCardInfo[i].doneStep > m_curCursedCardInfo[i].steps)
		{
			m_curCursedCardInfo[i].doneStep += 1;
			i += 1;
		}
		else
		{
			m_curCursedCardInfo.RemoveAt(i);
			continue;
		}
	}*/
}

void ASingleProgressGameMode::NotifyLoadCalenderMenu_Implementation()
{

}

FSAOverallIndexSlopInfo ASingleProgressGameMode::ReadWeatherEffectInfo_Implementation(const FString& weatherType)
{
	FSAOverallIndexSlopInfo slopeInfo;
	return slopeInfo;
}

void ASingleProgressGameMode::NotifyTriggerEvent_Implementation()
{

}

void ASingleProgressGameMode::NotifyEndEventMode_Implementation()
{

}

FEventLandBlockInfo ASingleProgressGameMode::ReadEventDemoInfos_Implementation(const FString& eventName)
{
	FEventLandBlockInfo info;
	return info;
}

void ASingleProgressGameMode::EndEventMode()
{
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	m_diceBattleStage = 0;
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
	NotifyChangeGameState(m_gameState);
	m_pControlCharacter->SetActorLocation(FVector(0, 0, 330));
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	pNormalCM->m_POVRotation.Pitch = -70;
	pNormalCM->m_POVLocation = m_SPPOVLoc;
	
	if (m_isInTutorial) m_pSPPC->InitialTutorial();
	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_launchEventTime, FLinearColor::Black, false, true);
	NotifyEndEventMode();

	ShowAllCard();

	m_gameState = 0;
	m_pSPPC->m_gameState = 0;

	while (m_pEventDemoActorList.Num() > 0)
	{
		if (!m_pEventDemoActorList.Last()) m_pEventDemoActorList.Pop();
		else
		{
			if (m_pEventDemoActorList.Last()->IsValidLowLevel())
			{
				m_pEventDemoActorList.Last()->ConditionalBeginDestroy();
				m_pEventDemoActorList.Last()->Destroy();
			}
			m_pEventDemoActorList.Pop();
		}
	}
	m_pEventDemoActorList.Empty();
	while (m_pEventDemoPSList.Num() > 0)
	{
		m_pEventDemoPSList.Last()->Deactivate();
		if (m_pEventDemoPSList.Last()->IsValidLowLevel())
		{
			m_pEventDemoPSList.Last()->ConditionalBeginDestroy();
		}
		m_pEventDemoPSList.Pop();
	}
	m_pEventDemoPSList.Empty();
}

UStaticMesh* ASingleProgressGameMode::ReadStaticBP_Implementation(const FString& name)
{
	return NULL;
}

void ASingleProgressGameMode::InitialDiceBattle()
{
	//StopTick();

	m_pSPPC->m_pCurSelectPlayCard = NULL;
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");

	m_pSPPC->SwitchMenu(1);
	m_gameState = 1;
	m_pSPPC->m_gameState = 1;
	m_pSPPC->m_pDiceBattleMenu->m_maxTime = m_diceBattleInfo.maxAvailableTimePerRound;
	m_pSPPC->m_pDiceBattleMenu->InitialMenuParam(m_diceBattleInfo.targetScore, m_diceBattleInfo.maxAvailableTimePerRound);
	m_pSPPC->m_pDiceBattleMenu->UpdateLifeText(m_diceBattleInfo.originLife);
	m_pSPPC->m_pDiceBattleMenu->UpdateScoreText(0);
	m_pSPPC->m_pDiceBattleMenu->UpdateResetTimes(m_diceBattleInfo.maxFlipTime);

	m_pControlCharacter->SetActorLocation(m_diceBattleCharacterLoc);

	if (m_pSPPC->m_pDiceBattleMenu) m_pSPPC->m_pDiceBattleMenu->LoadAvailableSkills();

	NotifyChangeGameState(m_gameState);

	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
}

void ASingleProgressGameMode::EndDiceBattle()
{
	for (int32 i = 0; i < m_pDiceCardList.Num(); i++)
	{
		if (m_pDiceCardList[i] && m_pDiceCardList[i]->IsValidLowLevel())
		{
			m_pDiceCardList[i]->ConditionalBeginDestroy();
			m_pDiceCardList[i]->Destroy();
		}
	}
	m_pDiceCardList.Empty();
	
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	if (m_isInTutorial) m_pSPPC->InitialTutorial();
	m_diceBattleStage = 0;
	m_diceAndTheorizeCanAction = false;
	m_pSPPC->m_dicSkillMap.Empty();
	m_pDiceOrTheorizeSkillParticleMap.Empty();
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
	NotifyChangeGameState(m_gameState);
	m_pControlCharacter->SetActorLocation(FVector(0, 0, 330));
	m_allLevelDiceBattleInfos.Empty();
	m_pSPPC->m_allDiceBattleSkillInfos.Empty();
	m_pSPPC->m_curDiceSkills.Empty();

	m_pSPPC->m_pCurSelectPlayCard = NULL;

	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
	for (TMap<UParticleSystemComponent*, float>::TConstIterator iter = m_allDiceAndTheorizeSkillPSDurations.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Key) continue;
		iter->Key->DeactivateSystem();
	}
	m_allDiceAndTheorizeSkillPSDurations.Empty();
	if (m_pDemoCharacter->IsValidLowLevel())
	{
		m_pDemoCharacter->Destroy();
		m_pDemoCharacter->ConditionalBeginDestroy();
	}

	if (m_isInBossBattleLayer) m_pSPPC->m_pSPMenu->AddBossBattleProgressBall();
	//重新设置小进度条，大进度条+1
	int32 maxActionNodeNb = m_maxActionNodeNbPerLine;
	if (m_isInBossBattleLayer) maxActionNodeNb += 1;
	if (m_curEventNodeNb >= maxActionNodeNb)
	{
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(0, m_curEventNodeLayerNb);
	}
	else
	{
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
	}
	NotifyLoadCalenderMenu();
	//UpdateCursedCardRound();
}

void ASingleProgressGameMode::UpdateDiceLogic(float dT)
{
	TArray<UParticleSystemComponent*> pDeletePSComponents;
	for (TMap<UParticleSystemComponent*, float>::TConstIterator iter = m_allDiceAndTheorizeSkillPSDurations.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value <= 0) pDeletePSComponents.Add(iter->Key);
		else
		{
			m_allDiceAndTheorizeSkillPSDurations[iter->Key] = iter->Value - dT;
		}
	}
	for (int32 i=0; i<pDeletePSComponents.Num(); i++)
	{
		if (!pDeletePSComponents[i]) continue;
		m_allDiceAndTheorizeSkillPSDurations.Remove(pDeletePSComponents[i]);
		pDeletePSComponents[i]->DeactivateSystem();
	}
	if (m_diceBattleStage == 0)
	{
		//总前摇阶段，主要展示Start字眼
		float preCount = m_diceIntervalMap[0];
		if (m_curDiceCount >= preCount)
		{
			m_diceBattleStage = 1;
			m_curDiceCount = 0;
			if (m_pSPPC->m_pDiceBattleMenu) m_pSPPC->m_pDiceBattleMenu->NotifyDemonstrateText(0);
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 1)
	{
		float demoTime = m_diceIntervalMap[1];
		if (m_curDiceCount >= demoTime)
		{
			//说明展示文字时间过了，需要生成数字卡牌
			GenerateDiceCard();
			if (m_isInTutorial)
			{
				m_pSPPC->InitialTutorial();
			}
			m_diceBattleStage = 2;
			m_curDiceCount = 0;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 2)
	{
		//float spawnDiceCardTime = m_diceIntervalMap[2];
		if (m_curDiceCount >= m_diceBattleInfo.demoTime)
		{
			//全部翻牌
			for (int32 i=0; i<m_pDiceCardList.Num(); i++)
			{
				m_pDiceCardList[i]->TurnCard();
			}
			m_diceBattleStage = 3;
			m_diceAndTheorizeCanAction = true;
			m_curDiceCount = 0;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 3)
	{
		if (m_isInDiceTutorialState) return;
		m_curDiceTotalCount += dT;
		if (m_curDiceTotalCount >= m_diceBattleInfo.maxAvailableTimePerRound)
		{
			m_diceAndTheorizeCanAction = false;
			if (m_diceBattleInfo.maxFlipTime > 0)
			{
				m_diceBattleInfo.maxFlipTime -= 1;
				m_pSPPC->m_pDiceBattleMenu->UpdateResetTimes(m_diceBattleInfo.maxFlipTime);
				for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
				{
					m_pSPPC->m_pDiceBattleMenu->DeleteDiceSkillImage(iter->Key);
				}
				m_curAppendDiceSkillInfos.Empty();
				m_diceBattleStage = 4;
				m_curDiceTotalCount = 0.f;
			}
			else
			{
				m_diceBattleStage = 6;
			}
			if (m_pSPPC->m_pDiceBattleMenu)
			{
				m_pSPPC->m_pDiceBattleMenu->UpdateTime(m_diceBattleInfo.maxAvailableTimePerRound);
			}
		}
		else
		{
			if (m_pSPPC->m_pDiceBattleMenu)
			{
				m_pSPPC->m_pDiceBattleMenu->UpdateTime(m_diceBattleInfo.maxAvailableTimePerRound - m_curDiceTotalCount);
			}
			TArray<int32> removeKeys;
			for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
			{
				
				m_curAppendDiceSkillInfos[iter->Key].leftTime = iter->Value.leftTime - dT;
				if (iter->Value.leftTime <= 0)
				{
					removeKeys.Add(iter->Key);
				}
			}
			for (int32 i=0; i<removeKeys.Num(); i++)
			{
				m_curAppendDiceSkillInfos.Remove(removeKeys[i]);
				m_pSPPC->m_pDiceBattleMenu->DeleteDiceSkillImage(removeKeys[i]);
			}
		}
		return;
	}
	else if (m_diceBattleStage == 4)
	{
		m_diceAndTheorizeCanAction = false;
		//判断是否超过了总时间，如是重置
		if (m_curDiceCount >= m_diceIntervalMap[3])
		{
			m_curDiceCount = 0;
			//手动全盘换牌或到时全盘换牌阶段
			m_curDiceFlipCardNb = 0;
			for (int32 i = 0; i < m_pDiceCardList.Num(); i++)
			{
				if (!m_pDiceCardList[i] || m_pDiceCardList[i]->m_isFlip) continue;
				m_pDiceCardList[i]->TurnCard();
			}
			m_diceBattleStage = 5;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 5)
	{
		//展示系统运算字样
		float preCount = m_diceIntervalMap[4];
		if (m_curDiceCount >= preCount)
		{
			//上一轮卡牌展示完毕，删除所有现有卡牌，并重新生成卡牌
			GenerateDiceCard();
			m_diceBattleStage = 2;
			m_curDiceCount = 0;
			m_curDiceTotalCount = 0.f;
			if (m_pSPPC->m_pDiceBattleMenu) m_pSPPC->m_pDiceBattleMenu->NotifyDemonstrateText(2);
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 6)
	{
		m_diceAndTheorizeCanAction = false;
		//说明是玩家负
		if (m_curDiceCount >= m_diceIntervalMap[5])
		{
			if (m_pSPPC->m_pDiceBattleMenu) m_pSPPC->m_pDiceBattleMenu->NotifyDemonstrateText(4);
			m_diceBattleStage = 8;
			m_curDiceCount = 0;
			return;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 7)
	{
		m_diceAndTheorizeCanAction = false;
		//说明是玩家胜
		if (m_curDiceCount >= m_diceIntervalMap[9])
		{
			//展示获得卡牌
			if (m_pSPPC->m_pDiceBattleMenu) m_pSPPC->m_pDiceBattleMenu->NotifyDemonstrateText(5);
			m_diceBattleStage = 9;
			m_curDiceCount = 0;
			return;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 8 || m_diceBattleStage == 9)
	{
		if (m_curDiceCount >= m_diceIntervalMap[10])
		{
			//展示获得卡牌
			if (m_diceBattleStage == 9)
			{
				if (!m_pSPPC->m_pCardSelectMenu)
				{
					//m_pSPPC->LoadExtraBounusCard(true);
					if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
						m_pSPPC->NotifyLoadDemoWords(0, true);
					else
						m_pSPPC->NotifyLoadDemoWords(0, false);
				}
				m_diceBattleStage = 10;
			}
			else
			{
				if (!m_pSPPC->m_pCardSelectMenu)
				{
					//m_pSPPC->LoadExtraBounusCard(false);
					if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
						m_pSPPC->NotifyLoadDemoWords(1, true);
					else
						m_pSPPC->NotifyLoadDemoWords(1, false);
				}
				m_diceBattleStage = 11;
			}
			m_curDiceCount = 0;
			
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 10 || m_diceBattleStage == 11)
	{
		if (m_curDiceCount >= m_diceIntervalMap[11])
		{
			TArray<FString> bonusCards;
			if (m_diceBattleStage == 10)
			{
				//win dice, bonus should be given to player
			}
			else
			{
				//lose dice, nothing should be given
			}
			m_pSPPC->LoadExtraBounusCard(bonusCards, 1);
			m_curDiceCount = 0;
			m_diceBattleStage = 12;
		}
		else m_curDiceCount += dT;
	}
	else if (m_diceBattleStage == 12)
	{
		m_diceAndTheorizeCanAction = false;
	}
	else if (m_diceBattleStage == 13)
	{
		m_diceBattleStage = 14;
		m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
		GetWorldTimerManager().SetTimer(m_diceAndTheorizeTimeHandler, this, &ASingleProgressGameMode::EndDiceBattle, m_diceAndTheorizeFadeOutTime + 0.3f, false);
		UpdateActionNode(0);
		if (m_pEventNodeManager) m_pEventNodeManager->ResetNodeManager();
		
		//EndDiceBattle();
	}
}

void ASingleProgressGameMode::GenerateDiceCard()
{
	while (m_pDiceCardList.Num() > 0)
	{
		if (m_pDiceCardList.Last() && m_pDiceCardList.Last()->IsValidLowLevel())
		{
			m_pDiceCardList.Last()->Destroy();
			m_pDiceCardList.Last()->ConditionalBeginDestroy();
		}
		m_pDiceCardList.Pop();
	}
	int32 totalDiceCardNb = m_diceCardNb * 2;
	int32 halfWidth = m_diceBattleColNb / 2;
	TArray<int32> availableCardNbList;
	for (int32 i=-halfWidth; i<= halfWidth; i++)
	{
		if (i == 0) continue;
		int32 rowNb;
		for (int32 j= -halfWidth; j<= halfWidth; j++)
		{
			if (j == 0) continue;
			float x = 0.f;
			float y = 0.f;
			if (i < 0)
			{
				y = m_diceCardOffset * ((float)(i + 1) - 0.5) + m_diceCardOriginLoc.Y;
				rowNb = i + halfWidth;
			}
			else
			{
				y = m_diceCardOffset * ((float)(i - 1) + 0.5) + m_diceCardOriginLoc.Y;
				rowNb = i + halfWidth - 1;
			}

			int32 colNb = 0;
			if (j < 0)
			{
				x = m_diceCardOffset * ((float)(j + 1) - 0.5) + m_diceCardOriginLoc.X;
				colNb = j + halfWidth;
			}
			else
			{
				x = m_diceCardOffset * ((float)(j - 1) + 0.5) + m_diceCardOriginLoc.X;
				colNb = j + halfWidth - 1;
			}
			FVector diceCardLoc(x, y, m_diceCardOriginLoc.Z);
			APlayCard* pPlayCard = GetWorld()->SpawnActor<APlayCard>(m_playCardClass, diceCardLoc, FRotator::ZeroRotator);
			TArray<UActorComponent*> pStaticComponents = pPlayCard->GetComponentsByClass(UStaticMeshComponent::StaticClass());
			for (int32 k=0; k<pStaticComponents.Num(); k++)
			{
				pStaticComponents[k]->ComponentTags.Add(FName("DiceCard"));
			}
			pPlayCard->m_pCardName->SetVisibility(false);
			m_pDiceCardList.Add(pPlayCard);

			int32 cardNb = rowNb * m_diceBattleColNb + colNb;
			availableCardNbList.Add(cardNb);
		}
	}

	TArray<UTexture*> pExistTextures;
	TArray<FString> allPlayCardNames;
	for (TMap<FString, FCardTextureAndTags>::TConstIterator iter = m_pPlayCardTextureMap.CreateConstIterator(); iter; ++iter)
	{
		if (pExistTextures.Contains(iter->Value.pTexture)) continue;
		allPlayCardNames.Add(iter->Value.cardName);
		pExistTextures.Add(iter->Value.pTexture);
	}
	for (int32 i=0; i<m_diceCardNb; i++)
	{
		int32 randPlayCardNameNb = FMath::RandRange(0, allPlayCardNames.Num() - 1);
		FString cardName = allPlayCardNames[randPlayCardNameNb];
		allPlayCardNames.RemoveAt(randPlayCardNameNb);
		int32 randNb_1 = FMath::RandRange(0, availableCardNbList.Num() - 1);
		int32 randCardNb_1 = FMath::RandRange(1, 10);
		int32 randColor_1 = FMath::RandRange(0, 3);
		m_pDiceCardList[availableCardNbList[randNb_1]]->InitialPlayCard(0, randCardNb_1, randColor_1, cardName);
		m_pDiceCardList[availableCardNbList[randNb_1]]->NotifyInitialCard("", "", 0);
		availableCardNbList.RemoveAt(randNb_1);

		int32 randNb_2 = FMath::RandRange(0, availableCardNbList.Num() - 1);
		int32 randCardNb_2 = FMath::RandRange(1, 10);
		int32 randColor_2 = FMath::RandRange(0, 3);
		m_pDiceCardList[availableCardNbList[randNb_2]]->InitialPlayCard(0, randCardNb_2, randColor_2, cardName);
		m_pDiceCardList[availableCardNbList[randNb_2]]->NotifyInitialCard("", "", 0);
		availableCardNbList.RemoveAt(randNb_2);
	}
}

void ASingleProgressGameMode::InitialDiceBattleParam(int32 difficulty, bool isCharacterDice)
{
	/*if (isCharacterDice)
	{
		if (!m_allLevelDiceBattleInfos.Contains(difficulty)) return;
		m_diceBattleColNb = m_allLevelDiceBattleInfos[difficulty].diceCardColNb;
		m_diceCardNb = m_diceBattleColNb * m_diceBattleColNb / 2;
		m_diceBattleInfo.maxAvailableTimePerRound = m_allLevelDiceBattleInfos[difficulty].maxAvailableTimePerRound;
		m_diceBattleInfo.maxFlipTime = m_allLevelDiceBattleInfos[difficulty].maxFlipTime;
		m_diceBattleInfo.originLife = m_allLevelDiceBattleInfos[difficulty].originLife;
		m_diceBattleInfo.targetScore = m_allLevelDiceBattleInfos[difficulty].targetScore;
		m_diceBattleInfo.demoTime = m_allLevelDiceBattleInfos[difficulty].demoTime;
	}
	else
	{
		m_diceBattleColNb = m_pSPPC->m_pCurSelectEventCard->m_eventCardInfo.diceInfo.diceCardColNb;
		m_diceCardNb = m_diceBattleColNb * m_diceBattleColNb / 2;
		m_diceBattleInfo = m_pSPPC->m_pCurSelectEventCard->m_eventCardInfo.diceInfo;
	}*/
	if (!m_allLevelDiceBattleInfos.Contains(difficulty)) return;
	m_diceBattleColNb = m_allLevelDiceBattleInfos[difficulty].diceCardColNb;
	m_diceCardNb = m_diceBattleColNb * m_diceBattleColNb / 2;
	m_diceBattleInfo.maxAvailableTimePerRound = m_allLevelDiceBattleInfos[difficulty].maxAvailableTimePerRound;
	m_diceBattleInfo.maxFlipTime = m_allLevelDiceBattleInfos[difficulty].maxFlipTime;
	m_diceBattleInfo.originLife = m_allLevelDiceBattleInfos[difficulty].originLife;
	m_diceBattleInfo.targetScore = m_allLevelDiceBattleInfos[difficulty].targetScore;
	m_diceBattleInfo.demoTime = m_allLevelDiceBattleInfos[difficulty].demoTime;
	m_diceBattleInfo.diceCardColNb = m_diceBattleColNb;
	
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	TArray<FString> allSkills;
	for (TMap<FString, int32>::TConstIterator iter = pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap.CreateConstIterator(); iter; ++iter)
	{
		for (int32 i = 0; i < iter->Value; i++)
		{
			allSkills.Add(iter->Key);
		}
	}
	for (int32 i = 0; i < m_diceSkillNb; i++)
	{
		if (allSkills.Num() <= 0) break;
		int32 randNb = FMath::RandRange(0, allSkills.Num() - 1);
		m_pSPPC->m_curDiceSkills.Add(allSkills[randNb]);
		allSkills.RemoveAt(randNb);
	}
}

void ASingleProgressGameMode::AssignDiceParamAccordKnowledge()
{
	/*UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	int32 curKnowledge = pCWGameInstance->m_curPlayerSPInfo.attributeValueMap[4];
	for (TMap<int32, FKnowledgeParamInfo>::TConstIterator iter = m_knowledgeAttributeParamInfo.CreateConstIterator(); iter; ++iter)
	{
		if (curKnowledge >= iter->Key) continue;
		m_diceBattleInfo.originLife = iter->Value.life;
		m_diceBattleInfo.demoTime = iter->Value.demoTime;
		break;
	}*/
}

void ASingleProgressGameMode::TriggerDiceAppendSkill(bool bingoOrNot)
{
	if (bingoOrNot)
	{
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (m_pSPPC->m_allDiceBattleSkillInfos.Contains(iter->Value.skillName))
			{
				if (iter->Value.functionName == "IncreaseLifeByBingo")
				{
					m_diceBattleInfo.originLife += m_pSPPC->m_allDiceBattleSkillInfos[iter->Value.functionName].values[0];
					m_pSPPC->m_pDiceBattleMenu->UpdateLifeText(m_diceBattleInfo.originLife);
				}
			}
		}
	}
	else
	{
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (m_pSPPC->m_allDiceBattleSkillInfos.Contains(iter->Value.skillName))
			{
				if (iter->Value.functionName == "Keep Life")
				{
					m_diceBattleInfo.originLife += m_pSPPC->m_allDiceBattleSkillInfos[iter->Value.functionName].values[0];
				}
			}
		}
	}
}

void ASingleProgressGameMode::PlayDiceOrTheorizeSkillPS(FString skillName, uint8 type)
{
	if (!m_pDiceOrTheorizeSkillParticleMap.Contains(skillName)) return;
	if (type == 0)
	{
		UParticleSystemComponent* pPSComponent = UGameplayStatics::SpawnEmitterAtLocation(this, m_pDiceOrTheorizeSkillParticleMap[skillName].pPS, m_diceSkillPSLoc);
		m_allDiceAndTheorizeSkillPSDurations.Add(pPSComponent, m_pDiceOrTheorizeSkillParticleMap[skillName].time);
	}
	else if (type == 1)
	{
		UParticleSystemComponent* pPSComponent = UGameplayStatics::SpawnEmitterAtLocation(this, m_pDiceOrTheorizeSkillParticleMap[skillName].pPS, m_theorizeSkillPSLoc);
		m_allDiceAndTheorizeSkillPSDurations.Add(pPSComponent, m_pDiceOrTheorizeSkillParticleMap[skillName].time);
	}
}

void ASingleProgressGameMode::DiceSkillFlipCardEnd()
{
	for (int32 i=0; i<m_pDiceSkillFlipCards.Num(); i++)
	{
		m_pDiceSkillFlipCards[i]->TurnCard();
	}
	m_pDiceSkillFlipCards.Empty();
	m_diceBattleStage = 3;
	m_diceAndTheorizeCanAction = true;
}

void ASingleProgressGameMode::ReadAllDifficultyDiceInfo_Implementation()
{

}

void ASingleProgressGameMode::ReadDiceSkillPS_Implementation(uint8 readType)
{

}

void ASingleProgressGameMode::InitialTheorizePanel()
{
	//StopTick();
	//HideAllCardWidget();
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");
	m_gameState = 2;
	m_pSPPC->m_gameState = 2;
	FVector theorizeBoardLoc(0, 0, m_theorizeBoardZ);
	/*m_pTheorizeBoard = GetWorld()->SpawnActor<ABoard>(m_pTheorizeBoardClass, theorizeBoardLoc, FRotator::ZeroRotator);
	m_pTheorizeBoard->NotifyShowup();*/
	m_pControlCharacter->SetActorLocation(m_theorizeCharacterLoc);
	
	m_theorizePlayerInfo.availableFlipTimes = m_maxResetTimes;
	m_pSPPC->SwitchMenu(2);
	NotifyChangeGameState(m_gameState);
	if (m_pSPPC->m_pTheorizeMenu) m_pSPPC->m_pTheorizeMenu->LoadTheorizeSkills();

	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
}

void ASingleProgressGameMode::EndTheorize()
{
	while (m_pOppTheorizeCards.Num() > 0)
	{
		//DeleteCard(m_pOppNumericCards.Last());
		DeleteTheorizeCard(m_pOppTheorizeCards.Last());
	}
	while (m_pPlayerTheorizeCards.Num() > 0)
	{
		DeleteTheorizeCard(m_pPlayerTheorizeCards.Last());
	}
	/*if (m_pTheorizeBoard && m_pTheorizeBoard->IsValidLowLevel())
	{
		m_pTheorizeBoard->ConditionalBeginDestroy();
		m_pTheorizeBoard->Destroy();
	}*/
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	if (m_isInTutorial) m_pSPPC->InitialTutorial();
	m_theorizeState = 0;
	m_diceAndTheorizeCanAction = false;
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
	NotifyChangeGameState(m_gameState);

	m_pControlCharacter->SetActorLocation(FVector(0, 0, 330));
	m_pSPPC->m_alltheorizeSkillInfos.Empty();

	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
	m_pDiceOrTheorizeSkillParticleMap.Empty();
	m_pSPPC->m_curTheorizeSkills.Empty();
	for (TMap<UParticleSystemComponent*, float>::TConstIterator iter = m_allDiceAndTheorizeSkillPSDurations.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Key) continue;
		iter->Key->DeactivateSystem();
	}
	m_allDiceAndTheorizeSkillPSDurations.Empty();
	if (m_pDemoCharacter->IsValidLowLevel())
	{
		m_pDemoCharacter->Destroy();
		m_pDemoCharacter->ConditionalBeginDestroy();
	}
	if (m_pDemoEnermy->IsValidLowLevel())
	{
		m_pDemoEnermy->Destroy();
		m_pDemoEnermy->ConditionalBeginDestroy();
	}

	if (m_isInBossBattleLayer) m_pSPPC->m_pSPMenu->AddBossBattleProgressBall();
	//重新设置小进度条，大进度条+1
	int32 maxActionNodeNb = m_maxActionNodeNbPerLine;
	if (m_isInBossBattleLayer) maxActionNodeNb += 1;
	if (m_curEventNodeNb >= maxActionNodeNb)
	{
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(0, m_curEventNodeLayerNb);
	}
	else
	{
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
	}
	NotifyLoadCalenderMenu();
	//UpdateCursedCardRound();
}

void ASingleProgressGameMode::NotifyGetTheorizeParamFromDT_Implementation(int32 difficulty, uint8 readType)
{

}

void ASingleProgressGameMode::InitialTheorizeParam(int32 difficulty)
{
	/** 难度影响要素包括
	* 1.每盘最多对赌次数
	* 2.最多重置次数
	* 3.总卡牌数量
	* 4.翻牌数量
	* 总共分5个难度等级，由CardTransformInfo记录并输入
	*/
	/*if (difficulty == 1)
	{
		m_flipCardNb = 2;
		m_maxBetTimes = 6;
		m_maxResetTimes = 3;
		m_maxCardNb = 8;
	}
	else if (difficulty == 2)
	{
		m_flipCardNb = 2;
		m_maxBetTimes = 5;
		m_maxResetTimes = 3;
		m_maxCardNb = 9;
	}
	else if (difficulty == 3)
	{
		m_flipCardNb = 1;
		m_maxBetTimes = 4;
		m_maxResetTimes = 3;
		m_maxCardNb = 9;
	}
	else if (difficulty == 4)
	{
		m_flipCardNb = 1;
		m_maxBetTimes = 4;
		m_maxResetTimes = 2;
		m_maxCardNb = 10;
	}
	else if (difficulty == 5)
	{
		m_flipCardNb = 1;
		m_maxBetTimes = 3;
		m_maxResetTimes = 2;
		m_maxCardNb = 10;
	}*/
	NotifyGetTheorizeParamFromDT(difficulty, 0);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	TArray<FString> allSkills;
	for (TMap<FString, int32>::TConstIterator iter = pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap.CreateConstIterator(); iter; ++iter)
	{
		for (int32 i = 0; i < iter->Value; i++)
		{
			allSkills.Add(iter->Key);
		}
	}
	for (int32 i = 0; i < m_theorizeSkillNb; i++)
	{
		if (allSkills.Num() <= 0) break;
		int32 randNb = FMath::RandRange(0, allSkills.Num() - 1);
		m_pSPPC->m_curTheorizeSkills.Add(allSkills[randNb]);
		allSkills.RemoveAt(randNb);
	}
	//m_targetScore = targetScore;
	if (m_isInTutorial) m_targetScore = 1;
}

void ASingleProgressGameMode::DispatchTheorizeCards()
{
	float cardOffset = m_theorizeCardPanelWidth / m_cardNbPerRound;
	float firstCardLocX = m_oppCardCenterLoc.X - (float)(m_cardNbPerRound - 1) / 2.f;
	FVector firstOppCardLoc(firstCardLocX, m_oppCardCenterLoc.Y, m_oppCardCenterLoc.Z);
	FVector firstPlayerCardLoc(firstCardLocX, m_playerCardCenterLoc.Y, m_playerCardCenterLoc.Z);

	TArray<FOutputCardInfo> allTheorizeCardList = m_allTheorizeCardInfos;
	TArray<int32> cardNbList;
	TArray<FOutputCardInfo> oppCardInfoList;
	TArray<FOutputCardInfo> playerCardInfoList;
	for (int32 i=0; i<m_cardNbPerRound; i++)
	{
		int32 randPlayerCard = 0;
		if (!m_isInTutorial)
			randPlayerCard = FMath::RandRange(0, allTheorizeCardList.Num() - 1);
		bool hasInsert = false;
		for (int32 j=0; j<playerCardInfoList.Num(); j++)
		{
			if (allTheorizeCardList[randPlayerCard].nb < playerCardInfoList[j].nb)
			{
				playerCardInfoList.Insert(allTheorizeCardList[randPlayerCard], j);
				hasInsert = true;
				break;
			}
			else if (allTheorizeCardList[randPlayerCard].nb == playerCardInfoList[j].nb)
			{
				if (allTheorizeCardList[randPlayerCard].color == 2) playerCardInfoList.Insert(allTheorizeCardList[randPlayerCard], j);
				else playerCardInfoList.Insert(allTheorizeCardList[randPlayerCard], j+1);
				hasInsert = true;
				break;
			}
			else continue;
		}
		if (!hasInsert) playerCardInfoList.Add(allTheorizeCardList[randPlayerCard]);
		allTheorizeCardList.RemoveAt(randPlayerCard);

		hasInsert = false;
		int32 randOppCard = 0;
		if (!m_isInTutorial)
			randOppCard = FMath::RandRange(0, allTheorizeCardList.Num() - 1);
		for (int32 j = 0; j < oppCardInfoList.Num(); j++)
		{
			if (allTheorizeCardList[randOppCard].nb < oppCardInfoList[j].nb)
			{
				oppCardInfoList.Insert(allTheorizeCardList[randOppCard], j);
				hasInsert = true;
				break;
			}
			else if (allTheorizeCardList[randOppCard].nb == oppCardInfoList[j].nb)
			{
				if (allTheorizeCardList[randOppCard].color == 2) oppCardInfoList.Insert(allTheorizeCardList[randOppCard], j);
				else oppCardInfoList.Insert(allTheorizeCardList[randOppCard], j + 1);
				hasInsert = true;
				break;
			}
			else continue;
		}
		if (!hasInsert) oppCardInfoList.Add(allTheorizeCardList[randOppCard]);
		allTheorizeCardList.RemoveAt(randOppCard);
	}

	for (int32 i=0; i<m_cardNbPerRound; i++)
	{
		cardNbList.Add(i);
		FVector oppCardLoc = firstOppCardLoc + i * FVector(cardOffset, 0, 0);
		FVector playerCardLoc = firstPlayerCardLoc + i * FVector(cardOffset, 0, 0);
		ANumericCard* pOppCard = GetWorld()->SpawnActor<ANumericCard>(m_numericCardClass, oppCardLoc, FRotator(0, 0, 180));
		ANumericCard* pPlayerCard = GetWorld()->SpawnActor<ANumericCard>(m_numericCardClass, playerCardLoc, FRotator::ZeroRotator);
		pPlayerCard->InitialPlayCard(0, playerCardInfoList[i].nb, playerCardInfoList[i].color, "NULL");
		pOppCard->InitialPlayCard(0, oppCardInfoList[i].nb, oppCardInfoList[i].color, "NULL");
		FString playerCardName = "PlayerTheorizeCard_" + FString::FromInt(playerCardInfoList[i].color) + "_" + FString::FromInt(playerCardInfoList[i].nb);
		FString oppCardName = "OppTheorizeCard_" + FString::FromInt(oppCardInfoList[i].color) + "_" + FString::FromInt(oppCardInfoList[i].nb);
		pPlayerCard->m_cardName = playerCardName;
		pOppCard->m_cardName = oppCardName;
		pOppCard->m_isFlip = false;
		m_pOppTheorizeCards.Add(pOppCard);
		m_pPlayerTheorizeCards.Add(pPlayerCard);
	}
	for (int32 i=0; i<m_flipCardNb; i++)
	{
		int32 randNb = 2;
		if (!m_isInTutorial)
			randNb = FMath::RandRange(0, cardNbList.Num() - 1);
		m_pOppTheorizeCards[cardNbList[randNb]]->TurnCard();
		cardNbList.RemoveAt(randNb);
	}
}

void ASingleProgressGameMode::DeleteTheorizeCard(ANumericCard* pCard)
{
	if (m_pOppTheorizeCards.Contains(pCard))
	{
		m_pOppTheorizeCards.Remove(pCard);
		if (pCard->IsValidLowLevel())
		{
			pCard->Destroy();
			pCard->ConditionalBeginDestroy();
		}
	}
	else if (m_pPlayerTheorizeCards.Contains(pCard))
	{
		m_pPlayerTheorizeCards.Remove(pCard);
		if (pCard->IsValidLowLevel())
		{
			pCard->Destroy();
			pCard->ConditionalBeginDestroy();
		}
	}
}

void ASingleProgressGameMode::ResetAllTheorizeCards()
{
	while (m_pOppTheorizeCards.Num() > 0)
	{
		//DeleteCard(m_pOppNumericCards.Last());
		DeleteTheorizeCard(m_pOppTheorizeCards.Last());
	}
	while (m_pPlayerTheorizeCards.Num() > 0)
	{
		DeleteTheorizeCard(m_pPlayerTheorizeCards.Last());
	}
	m_allTheorizeCardInfos.Empty();
	for (int32 i=0; i< (m_maxCardNb + m_curTheorizeLevel); i++)
	{
		FOutputCardInfo heartInfo;
		heartInfo.color = 2;
		heartInfo.nb = i + 1;
		FOutputCardInfo spadeInfo;
		spadeInfo.color = 3;
		spadeInfo.nb = i + 1;
		m_allTheorizeCardInfos.Add(heartInfo);
		m_allTheorizeCardInfos.Add(spadeInfo);
	}
	DispatchTheorizeCards();
}

uint8 ASingleProgressGameMode::Bet(ANumericCard* pPlayerCard, ANumericCard* pOppCard)
{
	m_theorizePlayerInfo.compareTimes -= 1;
	m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
	TriggerTheorizeSkill(0, pOppCard, pPlayerCard);
	if (pPlayerCard->m_nb > pOppCard->m_nb) return 0;
	else if (pPlayerCard->m_nb == pOppCard->m_nb)
	{
		if (pPlayerCard->m_color == 2 && pOppCard->m_color == 3) return 1;
		else if ((pPlayerCard->m_color == 2 && pOppCard->m_color == 2) || (pPlayerCard->m_color == 3 && pOppCard->m_color == 3)) return 0;
		else return 0;
	}
	else return 1;
}

void ASingleProgressGameMode::Theorize(ANumericCard* pTheorizeCard)
{
	if (!pTheorizeCard) return;
	if (!m_pSPPC->m_pSelectTheorizeCard) return;
	//引导部分
	if (m_isInTutorial)
	{
		FString tutorialStepName = "Theorize";
		if (m_tutorialSteps[0].operationName == tutorialStepName)
			DeleteTutorialStep();
		/*if (m_tutorialSteps[0].operationName != tutorialStepName) return;
		else
			DeleteTutorialStep();*/
	}
	if (m_pSPPC->m_pSelectTheorizeCard->m_color != pTheorizeCard->m_color || m_pSPPC->m_pSelectTheorizeCard->m_nb != pTheorizeCard->m_nb)
	{
		//推断失败，扣分
		m_theorizePlayerInfo.life -= 1;
		TriggerTheorizeSkill(2, pTheorizeCard, NULL);
		m_pDemoCharacter->TriggerDemoAnim("TheorizeLoseScore");
		m_pDemoEnermy->TriggerDemoAnim("TheorizeGetScore");
		m_pSPPC->NotifyShakeCamera();
		if (m_theorizePlayerInfo.life <= 0)
		{
			if (m_pSPPC->m_pTutorialMenu) m_pSPPC->m_pTutorialMenu->NotifyFadeOut();
			m_theorizeState = 8;
		}
		NotifyPlaySound2DByName("Theorize_Fail");
	}
	else
	{
		//推断成功，加分同时翻牌，同时判定是否所有牌已翻，如是进入下一轮
		//m_theorizePlayerInfo.curScore += 1;
		TriggerTheorizeSkill(1, pTheorizeCard, NULL);
		m_pDemoCharacter->TriggerDemoAnim("TheorizeGetScore");
		m_pDemoEnermy->TriggerDemoAnim("TheorizeLoseScore");
		m_pSPPC->NotifyShakeCamera();
		UncoverTheorizeCard(pTheorizeCard);
		UGameplayStatics::SpawnEmitterAtLocation(pTheorizeCard, m_pSmokePS, pTheorizeCard->GetActorLocation());
		NotifyPlaySound2DByName("Theorize_Right");
	}
	m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
}


void ASingleProgressGameMode::UncoverTheorizeCard(ANumericCard* pTheorizeCard)
{
	m_theorizePlayerInfo.curScore += 1;
	if (m_pSPPC->m_pTheorizeMenu) m_pSPPC->m_pTheorizeMenu->NotifyShowDemoImage(0);
	if (m_theorizePlayerInfo.curScore >= m_targetScore)
	{
		if (m_pSPPC->m_pTutorialMenu) m_pSPPC->m_pTutorialMenu->NotifyFadeOut();
		pTheorizeCard->m_isFlip = true;
		m_theorizeState = 7;
		m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
		return;
	}
	pTheorizeCard->m_isFlip = true;
	bool allCardsFlip = true;
	for (int32 i = 0; i < m_pOppTheorizeCards.Num(); i++)
	{
		if (m_pOppTheorizeCards[i]->m_isFlip) continue;
		allCardsFlip = false;
		break;
	}
	if (allCardsFlip)
	{
		m_pSPPC->m_pTheorizeMenu->NotifyDemonstrateString(2);
		m_theorizeState = 6;
		m_curTheorizeTimeCount = 0;
	}
}

void ASingleProgressGameMode::UpdateTheorize(float dT)
{
	TArray<UParticleSystemComponent*> pDeletePSComponents;
	for (TMap<UParticleSystemComponent*, float>::TConstIterator iter = m_allDiceAndTheorizeSkillPSDurations.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value <= 0) pDeletePSComponents.Add(iter->Key);
		else
		{
			m_allDiceAndTheorizeSkillPSDurations[iter->Key] = iter->Value - dT;
		}
	}
	for (int32 i = 0; i < pDeletePSComponents.Num(); i++)
	{
		if (!pDeletePSComponents[i]) continue;
		m_allDiceAndTheorizeSkillPSDurations.Remove(pDeletePSComponents[i]);
		pDeletePSComponents[i]->DeactivateSystem();
	}
	if (m_theorizeState == 0)
	{
		//总前摇阶段
		float preCount = m_theorizeIntervalMap[0];
		if (m_curTheorizeTimeCount >= preCount)
		{
			m_theorizeState = 1;
			m_curTheorizeTimeCount = 0;
			if (m_pSPPC->m_pTheorizeMenu) m_pSPPC->m_pTheorizeMenu->NotifyDemonstrateString(0);
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 1)
	{
		float demoTime = m_theorizeIntervalMap[1];
		if (m_curTheorizeTimeCount >= demoTime)
		{
			//说明展示文字时间过了，需要生成数字卡牌
			ResetAllTheorizeCards();
			if (m_isInTutorial)
			{
				m_pSPPC->InitialTutorial();
			}
			m_theorizeState = 2;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 2)
	{
		float spawnTheorizeCardTime = m_theorizeIntervalMap[2];
		if (m_curTheorizeTimeCount >= spawnTheorizeCardTime)
		{
			m_theorizeState = 3;
			m_curTheorizeTimeCount = 0;
			m_diceAndTheorizeCanAction = true;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 3)
	{
		if (m_isInTheorizeTutorialState) return;
		TArray<int32> removeKeys;
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			m_curAppendTheorizeSkillInfos[iter->Key].leftTime = iter->Value.leftTime - dT;
			if (iter->Value.leftTime <= 0)
			{
				removeKeys.Add(iter->Key);
			}
		}
		for (int32 i = 0; i < removeKeys.Num(); i++)
		{
			m_curAppendTheorizeSkillInfos.Remove(removeKeys[i]);
			m_pSPPC->m_pTheorizeMenu->DeleteTheorizeSkillImage(removeKeys[i]);
		}
		return;
	}
	else if (m_theorizeState == 4)
	{
		m_diceAndTheorizeCanAction = false;
		float switchCardPreTime = m_theorizeIntervalMap[3];
		if (m_curTheorizeTimeCount >= switchCardPreTime)
		{
			for (int32 i = 0; i < m_pOppTheorizeCards.Num(); i++)
			{
				if (!m_pOppTheorizeCards[i] || m_pOppTheorizeCards[i]->m_isFlip) continue;
				m_pOppTheorizeCards[i]->m_isFlip = true;
			}
			m_theorizeState = 5;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 5)
	{
		float switchCardTime = m_theorizeIntervalMap[4];
		if (m_curTheorizeTimeCount >= switchCardTime)
		{
			m_pSPPC->m_pTheorizeMenu->NotifyDemonstrateString(1);
			m_theorizeState = 6;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 6)
	{
		m_diceAndTheorizeCanAction = false;
		float demoStringTime = m_theorizeIntervalMap[5];
		if (m_curTheorizeTimeCount >= demoStringTime)
		{
			ResetAllTheorizeCards();
			m_theorizeState = 3;
			m_diceAndTheorizeCanAction = true;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 7)
	{
		m_diceAndTheorizeCanAction = false;
		//说明胜利了
		float demoStringTime = m_theorizeIntervalMap[6];
		if (m_curTheorizeTimeCount >= demoStringTime)
		{
			m_pSPPC->m_pTheorizeMenu->NotifyDemonstrateString(2);
			m_theorizeState = 9;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 8)
	{
		m_diceAndTheorizeCanAction = false;
		//说明失败了
		float demoStringTime = m_theorizeIntervalMap[7];
		if (m_curTheorizeTimeCount >= demoStringTime)
		{
			m_pSPPC->m_pTheorizeMenu->NotifyDemonstrateString(3);
			m_theorizeState = 10;
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 9 || m_theorizeState == 10)
	{
		float demoStringTime = m_theorizeIntervalMap[8];
		if (m_curTheorizeTimeCount >= demoStringTime)
		{
			//展示获得卡牌
			if (m_theorizeState == 9)
			{
				if (!m_pSPPC->m_pCardSelectMenu)
				{
					//m_pSPPC->LoadExtraBounusCard(true);
					if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
						m_pSPPC->NotifyLoadDemoWords(2, true);
					else
						m_pSPPC->NotifyLoadDemoWords(2, false);
				}
				m_theorizeState = 11;
			}
			else
			{
				/*if (!m_pSPPC->m_pCardSelectMenu)
					m_pSPPC->LoadExtraBounusCard(true);*/
				if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
					m_pSPPC->NotifyLoadDemoWords(3, true);
				else
					m_pSPPC->NotifyLoadDemoWords(3, false);
				m_theorizeState = 12;
			}
			m_curTheorizeTimeCount = 0;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 11 || m_theorizeState == 12)
	{
		float demoStringTime = m_theorizeIntervalMap[9];
		if (m_curTheorizeTimeCount >= demoStringTime)
		{
			TArray<FString> bonusCards;
			if (m_theorizeState == 11)
			{
				//win theorize, bonus should be given to player
			}
			else
			{
				//lose theorize, nothing is given to player
			}
			m_pSPPC->LoadExtraBounusCard(bonusCards, 2);
			m_curTheorizeTimeCount = 0;
			m_theorizeState = 13;
		}
		else m_curTheorizeTimeCount += dT;
	}
	else if (m_theorizeState == 14)
	{
		m_theorizeState = 15;
		m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
		GetWorldTimerManager().SetTimer(m_diceAndTheorizeTimeHandler, this, &ASingleProgressGameMode::EndTheorize, m_diceAndTheorizeFadeOutTime + 0.3f, false);
		UpdateActionNode(0);
		if (m_pEventNodeManager) m_pEventNodeManager->ResetNodeManager();
	}
}

void ASingleProgressGameMode::AssignTheorizeParamAccordSpeculative()
{
	/*UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	int32 curSpeculative = pCWGameInstance->m_curPlayerSPInfo.attributeValueMap[3];
	for (TMap<int32, FSpeculativeParamInfo>::TConstIterator iter = m_speculativeAttributeParamInfo.CreateConstIterator(); iter; ++iter)
	{
		if (curSpeculative >= iter->Key) continue;
		m_theorizePlayerInfo.life = iter->Value.life;
		m_theorizePlayerInfo.compareTimes = iter->Value.compareTimes;
		break;
	}
	m_theorizePlayerInfo.curScore = 0;*/
}

void ASingleProgressGameMode::LaunchTheorizeSkill(FString skillName)
{
	if (!m_pSPPC->m_alltheorizeSkillInfos.Contains(skillName) || !m_diceAndTheorizeCanAction) return;
	if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "UncoverByCompareCardNb")
	{
		for (int32 i=0; i<m_pOppTheorizeCards.Num(); i++)
		{
			if ((m_pSPPC->m_alltheorizeSkillInfos[skillName].values[0] == 0 && (m_pOppTheorizeCards[i]->m_nb <= m_pSPPC->m_alltheorizeSkillInfos[skillName].values[1] && !m_pOppTheorizeCards[i]->m_isFlip))
				||
				(m_pSPPC->m_alltheorizeSkillInfos[skillName].values[0] == 1 && (m_pOppTheorizeCards[i]->m_nb >= m_pSPPC->m_alltheorizeSkillInfos[skillName].values[1] && !m_pOppTheorizeCards[i]->m_isFlip)))
			{
				UncoverTheorizeCard(m_pOppTheorizeCards[i]);
				m_pDemoCharacter->TriggerDemoAnim(skillName);
				m_pDemoEnermy->TriggerDemoAnim(skillName);
				m_pSPPC->NotifyShakeCamera();
			}
		}
		m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "UncoverByCardNb")
	{
		for (int32 i = 0; i < m_pOppTheorizeCards.Num(); i++)
		{
			if (m_pSPPC->m_alltheorizeSkillInfos[skillName].values[0] == m_pOppTheorizeCards[i]->m_nb && !m_pOppTheorizeCards[i]->m_isFlip)
			{
				UncoverTheorizeCard(m_pOppTheorizeCards[i]);
				m_pDemoCharacter->TriggerDemoAnim(skillName);
				m_pDemoEnermy->TriggerDemoAnim(skillName);
				m_pSPPC->NotifyShakeCamera();
			}
		}
		m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "UncoverByColor")
	{
		for (int32 i = 0; i < m_pOppTheorizeCards.Num(); i++)
		{
			if (m_pSPPC->m_alltheorizeSkillInfos[skillName].values[0] == m_pOppTheorizeCards[i]->m_color && !m_pOppTheorizeCards[i]->m_isFlip)
			{
				UncoverTheorizeCard(m_pOppTheorizeCards[i]);
				m_pDemoCharacter->TriggerDemoAnim(skillName);
				m_pDemoEnermy->TriggerDemoAnim(skillName);
				m_pSPPC->NotifyShakeCamera();
			}
		}
		m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "ChangeLifeByCompare")
	{
		if (m_theorizePlayerInfo.compareTimes > 0)
		{
			m_theorizePlayerInfo.compareTimes -= 1;
			m_theorizePlayerInfo.life += 1;
			m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
		}
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "UncoverByLife")
	{
		TArray<int32> allUnflipCards;
		for (int32 i=0; i<m_pOppTheorizeCards.Num(); i++)
		{
			if (!m_pOppTheorizeCards[i]->m_isFlip) allUnflipCards.Add(i);
		}
		if (allUnflipCards.Num() <= 0) return;
		int32 randNb = FMath::RandRange(0, allUnflipCards.Num() - 1);
		UncoverTheorizeCard(m_pOppTheorizeCards[allUnflipCards[randNb]]);
		m_pDemoCharacter->TriggerDemoAnim(skillName);
		m_pDemoEnermy->TriggerDemoAnim(skillName);
		m_pSPPC->NotifyShakeCamera();
		m_theorizePlayerInfo.life -= 1;
		m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "SeeThrough" ||
		m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "SeeThroughColor")
	{
		FDiceAndTheorizeSkillAppendInfo newAppendInfo;
		newAppendInfo.functionName = m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName;
		newAppendInfo.skillName = skillName;
		if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "SeeThrough")
			newAppendInfo.leftTime = m_pSPPC->m_alltheorizeSkillInfos[skillName].values[2];
		else
			newAppendInfo.leftTime = m_pSPPC->m_alltheorizeSkillInfos[skillName].values[1];
		int32 i = 0;
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key == i)
				i += 1;
			else
				break;
		}
		m_curAppendTheorizeSkillInfos.Add(i, newAppendInfo);
		m_pSPPC->m_pTheorizeMenu->AddTheorizeSkillImage(skillName, i);
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "IncreaseLifeByTheorize" ||
		m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "IncreaseCompareByTheorize")
	{
		FDiceAndTheorizeSkillAppendInfo newAppendInfo;
		newAppendInfo.functionName = m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName;
		newAppendInfo.skillName = skillName;
		if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "IncreaseLifeByTheorize")
			newAppendInfo.leftTime = m_pSPPC->m_alltheorizeSkillInfos[skillName].values[2];
		else
			newAppendInfo.leftTime = m_pSPPC->m_alltheorizeSkillInfos[skillName].values[1];
		int32 i = 0;
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key == i)
				i += 1;
			else
				break;
		}
		m_curAppendTheorizeSkillInfos.Add(i, newAppendInfo);
		m_pSPPC->m_pTheorizeMenu->AddTheorizeSkillImage(skillName, i);
	}
	else if (m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName == "KeepLife")
	{
		FDiceAndTheorizeSkillAppendInfo newAppendInfo;
		newAppendInfo.functionName = m_pSPPC->m_alltheorizeSkillInfos[skillName].functionName;
		newAppendInfo.skillName = skillName;
		newAppendInfo.leftTime = m_pSPPC->m_alltheorizeSkillInfos[skillName].values[0];
		int32 i = 0;
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key == i)
				i += 1;
			else
				break;
		}
		m_curAppendTheorizeSkillInfos.Add(i, newAppendInfo);
		m_pSPPC->m_pTheorizeMenu->AddTheorizeSkillImage(skillName, i);
	}
	PlayDiceOrTheorizeSkillPS(skillName, 1);
	NotifyPlaySound2DByName("Theorize_Skill");
}

void ASingleProgressGameMode::TriggerTheorizeSkill(uint8 actionType, ANumericCard* pTargetCard, ANumericCard* pSourceCard)
{
	/** 代表各种操作
	* 0. 对比
	* 1. 猜对
	* 2. 猜错
	*/
	if (actionType == 0)
	{
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.functionName == "SeeThrough")
			{
				//这个参数是判断类型的，如为0则是比较谁小，1为比较谁大
				if ((m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[0] == 0 &&
					(pSourceCard->m_nb == m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[1] && pSourceCard->m_nb < pTargetCard->m_nb &&
						!pTargetCard->m_isFlip))
					||
					(m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[0] == 1 &&
					(pSourceCard->m_nb == m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[1] && pSourceCard->m_nb > pTargetCard->m_nb &&
						!pTargetCard->m_isFlip)))
				{
					UncoverTheorizeCard(pTargetCard);
					m_pDemoCharacter->TriggerDemoAnim(iter->Value.skillName);
					m_pDemoEnermy->TriggerDemoAnim(iter->Value.skillName);
					m_pSPPC->NotifyShakeCamera();
				}
			}
			else if (iter->Value.functionName == "SeeThroughColor")
			{
				//这个参数是判断类型的，如为0则是比较谁小，1为比较谁大
				if ((int32)pTargetCard->m_color == m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[0] && !pTargetCard->m_isFlip)
				{
					UncoverTheorizeCard(pTargetCard);
					m_pDemoCharacter->TriggerDemoAnim(iter->Value.skillName);
					m_pDemoEnermy->TriggerDemoAnim(iter->Value.skillName);
					m_pSPPC->NotifyShakeCamera();
				}
			}
		}
	}
	else if (actionType == 1)
	{
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.functionName == "IncreaseLifeByTheorize" && m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[1] == pTargetCard->m_nb)
			{
				m_theorizePlayerInfo.life += m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[0];
				m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
			}
			else if (iter->Value.functionName == "IncreaseCompareByTheorize")
			{
				m_theorizePlayerInfo.compareTimes += m_pSPPC->m_alltheorizeSkillInfos[iter->Value.skillName].values[0];
				m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
			}
		}
	}
	else if (actionType == 2)
	{
		for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value.functionName == "KeepLife")
			{
				m_theorizePlayerInfo.life += 1;
				//m_pSPPC->m_pTheorizeMenu->UpdateAllParam();
			}
		}
	}
}

void ASingleProgressGameMode::UpdateDrawCard(float dT)
{
	if (m_drawCardState == 0)
	{
		//总前摇阶段
		float preCount = m_drawCardTimeIntervalMap[0];
		if (m_curDrawCardTimeCount >= preCount)
		{
			m_drawCardState = 1;
			m_curDrawCardTimeCount = 0;
			if (m_pSPPC->m_pDrawCardMenu) m_pSPPC->m_pDrawCardMenu->NotifyDemonstrateString(0);
		}
		else m_curDrawCardTimeCount += dT;
	}
	else if (m_drawCardState == 1)
	{
		return;
	}
	else if (m_drawCardState == 2)
	{
		//说明胜利了
		float count = m_drawCardTimeIntervalMap[1];
		if (m_curDrawCardTimeCount >= count)
		{
			m_drawCardState = 4;
			if (m_pSPPC->m_pDrawCardMenu) m_pSPPC->m_pDrawCardMenu->NotifyDemonstrateString(1);
			m_curDrawCardTimeCount = 0;
		}
		else m_curDrawCardTimeCount += dT;
	}
	else if (m_drawCardState == 3)
	{
		//说明失败了
		float count = m_drawCardTimeIntervalMap[1];
		if (m_curDrawCardTimeCount >= count)
		{
			m_drawCardState = 4;
			if (m_pSPPC->m_pDrawCardMenu) m_pSPPC->m_pDrawCardMenu->NotifyDemonstrateString(2);
			m_curDrawCardTimeCount = 0;
		}
		else m_curDrawCardTimeCount += dT;
	}
	else if (m_drawCardState == 4)
	{
		float count = m_drawCardTimeIntervalMap[2];
		if (m_curDrawCardTimeCount >= count)
		{
			EndDrawCard();
			m_drawCardState = 5;
		}
		else m_curDrawCardTimeCount += dT;
	}
}

void ASingleProgressGameMode::InitialDrawCard(int32 drawCardNb, int32 trialTimes)
{
	StopTick();
	HideAllCardWidget();
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");
	m_drawCardNb = drawCardNb;
	m_drawTrialTimes = trialTimes;
	m_pSPPC->SwitchMenu(3);
	m_gameState = 3;
	m_pSPPC->m_gameState = 3;
	GenerateDrawCardInfo();

}

void ASingleProgressGameMode::GenerateDrawCardInfo()
{
	if (!m_pSPPC->m_pDrawCardMenu) return;
	int32 curRow = 0;
	int32 curCol = 0;
	for (int32 i=0; i<m_drawCardNb; i++)
	{
		uint8 drawCardColor;
		int32 drawCardNb;
		GenerateJudgeCard(drawCardColor, drawCardNb);
		FOutputCardInfo drawCardInfo(drawCardNb, drawCardColor);
		m_allDrawCardsInfo.Add(drawCardInfo);
		if (curCol >= m_pSPPC->m_pDrawCardMenu->m_maxColPerRow)
		{
			curCol = 0;
			curRow += 1;
		}
		m_pSPPC->m_pDrawCardMenu->AddDrawCardToMenu(drawCardNb, drawCardColor, curRow, curCol);
		curCol += 1;
	}
	m_winDrawCardNb = FMath::RandRange(0, m_drawCardNb - 1);

	m_pSPPC->m_pDrawCardMenu->AddPlayerCardToMenu(m_allDrawCardsInfo[m_winDrawCardNb].nb, m_allDrawCardsInfo[m_winDrawCardNb].color);
}

void ASingleProgressGameMode::EndDrawCard()
{
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	m_drawCardState = 0;
}

void ASingleProgressGameMode::InitialShop()
{
	StopTick();
	HideAllCardWidget();
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");
	m_pSPPC->SwitchMenu(4);
	m_gameState = 4;
	m_pSPPC->m_gameState = 4;
}

void ASingleProgressGameMode::UpdateShop()
{
	if (m_shopState == 1)
	{
		EndShop();
		m_shopState = 2;
	}
}

void ASingleProgressGameMode::EndShop()
{
	
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
	
}

void ASingleProgressGameMode::InitialBattle(const FBattleInfo& battleInfo)
{
	StopTick();
	HideAllCardWidget();
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");

	m_gameState = 9;
	m_pSPPC->m_gameState = 9;
	DecideDayOrNight();
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	pCWGameInstance->m_battleInfo = battleInfo;
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		if (!m_pPlayCards[i] || !m_pPlayCards[i]->m_tags.Contains("BattleEquipment")) continue;
		pCWGameInstance->m_curPlayerSPInfo.availableEquipList.Add(m_pPlayCards[i]->m_cardName);
	}
	//要先进行保存，以便从战斗回来时恢复
	if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->FadeOut();
	if (m_pSPPC->m_pTutorialMenu) m_pSPPC->m_pTutorialMenu->NotifyFadeOut();
	m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_fadeOutTime, FLinearColor::Black, false, true);
	NotifyMusicFadeOut();
	GetWorldTimerManager().SetTimer(m_openBattleLevelTimeHandler, this, &ASingleProgressGameMode::EnterMap, m_fadeOutTime, false);
}

void ASingleProgressGameMode::OpenBattleLevel()
{
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGameInstance);

	m_pSPPC->SaveGame("BattleTempSlot", 0);

	FString levelName;
	if (pCWGI->m_curPlayerSPInfo.curProgress == 0)
		levelName = "Roguelike_Snow";
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 1)
		levelName = "Roguelike_Desert";
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 2)
		levelName = "Roguelike_Forest";
	UGameplayStatics::OpenLevel(this, FName(*levelName));
}

TArray<int32> ASingleProgressGameMode::GetBattleBonusLevels_Implementation(uint8 battleLevel)
{
	TArray<int32> valus;
	return valus;
}

void ASingleProgressGameMode::ReadShadowSkeletalMesh_Implementation()
{

}

AShadowActor* ASingleProgressGameMode::AddShadowActor(FString skeletalMeshName, FVector spawnLoc, FRotator spawnRot, uint8 shadowPSType, int32 idx)
{
	if (!m_pCWSingleton->m_SAClassMap.Contains(skeletalMeshName) || !m_shadowPSMap.Contains(shadowPSType)) return NULL;

	AShadowActor* pShadowActor = NULL;
	if (m_pSPPC->m_pSAOccupyInfoActor && m_pSPPC->m_pSAOccupyInfoActor->IsValidLowLevel())
	{
		m_pSPPC->m_pSAOccupyInfoActor->Destroy();
		m_pSPPC->m_pSAOccupyInfoActor->ConditionalBeginDestroy();
		m_pSPPC->m_pSAOccupyInfoActor = NULL;
	}
	if (skeletalMeshName == "DiceBattleSkillPanel")
		pShadowActor = GetWorld()->SpawnActor<AActionPanel>(m_pDicePanelClass, spawnLoc, spawnRot);
	else
		pShadowActor = GetWorld()->SpawnActor<AShadowActor>(m_pCWSingleton->m_SAClassMap[skeletalMeshName], spawnLoc, spawnRot);
	pShadowActor->m_idx = idx;
	pShadowActor->m_SAName = skeletalMeshName;

	if (!pShadowActor) return NULL;
	pShadowActor->m_pOverlapSAs.Empty();
	pShadowActor->m_isSet = true;

	TArray<UActorComponent*> pComponents = pShadowActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
	for (int32 i = 0; i < pComponents.Num(); i++)
	{
		USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
		pSMComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Block);
		pSMComponent->ComponentTags.Add(FName("ShadowActor"));
		pSMComponent->SetCustomDepthStencilValue(180);
	}

	TArray<UActorComponent*> pStaticComponents = pShadowActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (int32 i = 0; i < pStaticComponents.Num(); i++)
	{
		UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticComponents[i]);
		pSMComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel4, ECR_Block);
		pSMComponent->ComponentTags.Add(FName("ShadowActor"));
		pSMComponent->SetCustomDepthStencilValue(180);
	}

	UParticleSystemComponent* pPSComponent = UGameplayStatics::SpawnEmitterAtLocation(pShadowActor, m_shadowPSMap[shadowPSType], FVector::ZeroVector, FRotator::ZeroRotator);
	FParticleSysParam psParam;
	psParam.Name = "VertSurfaceActor";
	psParam.ParamType = EParticleSysParamType::PSPT_Actor;
	psParam.Actor = pShadowActor;
	pPSComponent->InstanceParameters.Add(psParam);
	m_pShadowActorPSComponentList.Add(pPSComponent);
	m_pShadowActorList.Add(pShadowActor);
	return pShadowActor;
}

void ASingleProgressGameMode::DeleteShadowActor(AShadowActor* pShadowActor)
{
	if (!pShadowActor) return;
	int32 actorNb = m_pShadowActorList.Find(pShadowActor);
	if (actorNb == INDEX_NONE) return;
	m_pShadowActorPSComponentList[actorNb]->DeactivateSystem();
	if (m_pShadowActorPSComponentList[actorNb]->IsValidLowLevel())
		m_pShadowActorPSComponentList[actorNb]->ConditionalBeginDestroy();
	m_pShadowActorPSComponentList.RemoveAt(actorNb);

	if (m_pShadowActorList[actorNb]->IsValidLowLevel())
	{
		m_pShadowActorList[actorNb]->Destroy();
		m_pShadowActorList[actorNb]->ConditionalBeginDestroy();
	}
	m_pShadowActorList.RemoveAt(actorNb);
}

void ASingleProgressGameMode::InitialShadowMode()
{
	/** 进入暗影模式要进行几件事
	* 1. 使Tick失效
	* 2. 隐藏所有卡牌及对应的widget
	* 3. 修改menu
	*/
	StopTick();
	HideAllCardWidget();
	HideAllCard();

	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");

	m_pSPPC->SwitchMenu(5);
	m_gameState = 5;
	m_pSPPC->m_gameState = 5;

}

TSubclassOf<class ADemoCharacter> ASingleProgressGameMode::ReadCharacterBP_Implementation(const FString& characterName)
{
	return NULL;
}

void ASingleProgressGameMode::InitialRuneMode()
{
	m_pSPPC->m_pCurSelectEventCard = NULL;
	m_pSPPC->DeleteMenu("ActionPanel");
	m_gameState = 6;
	m_pSPPC->m_gameState = 6;
	
	m_pControlCharacter->SetActorLocation(m_runeCharacterLoc);
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	pNormalCM->m_POVRotation.Pitch = -55;
	pNormalCM->m_POVLocation = m_runePOVLoc;

	m_pSPPC->SwitchMenu(6);
	NotifyChangeGameState(m_gameState);
	if (m_isInTutorial) m_pSPPC->InitialTutorial();
	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
}

void ASingleProgressGameMode::EndRuneMode()
{
	ResumeTick();
	ShowAllCardWidget();
	m_pSPPC->SwitchMenu(0);
	m_diceBattleStage = 0;
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
	NotifyChangeGameState(m_gameState);
	m_pControlCharacter->SetActorLocation(FVector(0, 0, 330));
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	pNormalCM->m_POVRotation.Pitch = -70;
	pNormalCM->m_POVLocation = m_SPPOVLoc;
	if (m_pDemoCharacter->IsValidLowLevel())
	{
		m_pDemoCharacter->Destroy();
		m_pDemoCharacter->ConditionalBeginDestroy();
	}
	if (m_isInTutorial) m_pSPPC->InitialTutorial();
	m_pSPPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
}

void ASingleProgressGameMode::ApplyCombineCardFunctions(AActionCard* pActionCard)
{
	/*for (int32 i=0; i<m_cardFunctionList.Num(); i++)
	{
		if (m_cardFunctionList[i].functionName == "ShrinkForgeTime")
			USPEventFunctionLib::ShrinkForgeTime(m_cardFunctionList[i], pActionCard);
	}*/
}

void ASingleProgressGameMode::ApplyIntrinsicFunction(APlayCard* pPlayCard)
{
	/*if (pPlayCard->m_cardFunction == "IncreaseAllDeviceDurability")
		USPEventFunctionLib::IncreaseAllDeviceDurability(pPlayCard);
	else if (pPlayCard->m_cardFunction == "GenerateCards")
		USPEventFunctionLib::GenerateCards(pPlayCard);
	else if (pPlayCard->m_cardFunction == "RecoverDiscardByMoney")
		USPEventFunctionLib::RecoverDiscardByMoney(pPlayCard);
	else if (pPlayCard->m_cardFunction== "Increase Mentality Slope" || pPlayCard->m_cardFunction == "Increase Activity Slope" ||
		pPlayCard->m_cardFunction == "Increase Money Slope" || pPlayCard->m_cardFunction == "Increase Suppression Slope" ||
		pPlayCard->m_cardFunction == "Increase Darkness Slope" || pPlayCard->m_cardFunction == "Increase FlameFaith Slope" ||
		pPlayCard->m_cardFunction == "Increase SunFaith Slope" || pPlayCard->m_cardFunction == "Increase Index Slope By CardNb" ||
		pPlayCard->m_cardFunction == "Increase Index Slope By Color" || pPlayCard->m_cardFunction == "Increase Index By Decrease Index" ||
		pPlayCard->m_cardFunction == "Increase Index Slope By Action CardNb" || pPlayCard->m_cardFunction == "Release Energy Reduction" || 
		pPlayCard->m_cardFunction == "Increase Index Slope By Index Exceed" || pPlayCard->m_cardFunction == "Increase Index By Discard" ||
		pPlayCard->m_cardFunction.Contains("Increase Index Slope By CardName") || pPlayCard->m_cardFunction == "Increase Index Slope By NumericNb")
	{
		FOverallIndexExtraFunInfo extraFunInfo;
		extraFunInfo.cardName = pPlayCard->m_cardName;
		extraFunInfo.functionName = pPlayCard->m_cardFunction;
		extraFunInfo.values = pPlayCard->m_functionValues;
		extraFunInfo.curTick = 0;
		extraFunInfo.duration = pPlayCard->m_functionValues.Last();
		m_extraOverallIndexSlopeFuns.Add(extraFunInfo);
		m_pSPPC->m_pSPMenu->UpdateCardFunctionList(pPlayCard->m_cardName, true);
	}*/
}

void ASingleProgressGameMode::ApplyCombineTimeFunction(AActionCard* pActionCard)
{
	for (int32 i=0; i<m_cardFunctionList.Num(); i++)
	{
		if ((m_cardFunctionList[i].functionName == "ShrinkForgeTime" && pActionCard->m_actionType == 3) ||
			(m_cardFunctionList[i].functionName == "ShrinkAllTime") ||
			(m_cardFunctionList[i].functionName == "ShrinkThinkTime" && pActionCard->m_actionType == 0) ||
			(m_cardFunctionList[i].functionName == "ShrinkThinkTime" && pActionCard->m_actionType == 0))
		{
			pActionCard->m_originLoadTime -= m_cardFunctionList[i].functionValues[0];
			if (pActionCard->m_originLoadTime <= 1) pActionCard->m_originLoadTime = 1;
			pActionCard->m_curLoadTime = pActionCard->m_originLoadTime;
		}
	}
}

void ASingleProgressGameMode::UpdateOverallIndexDemoActorList(float dT)
{
	int32 demoNb = 0;
	while (demoNb < m_pOIDemoActors.Num())
	{
		if (!m_pOIDemoActors[demoNb])
		{
			m_pOIDemoActors.RemoveAt(demoNb);
			continue;
		}
		if (m_pOIDemoActors[demoNb]->m_curTick >= m_OIDemoTime)
		{
			if (m_pOIDemoActors[demoNb]->m_pDemoPS)
				m_pOIDemoActors[demoNb]->m_pDemoPS->DeactivateSystem();
			if (m_pOIDemoActors[demoNb]->IsValidLowLevel())
			{
				m_pOIDemoActors[demoNb]->Destroy();
				m_pOIDemoActors[demoNb]->ConditionalBeginDestroy();
				m_pOIDemoActors.RemoveAt(demoNb);
				continue;
			}
		}
		else
		{
			m_pOIDemoActors[demoNb]->m_curTick += dT;
			demoNb += 1;
		}
	}

	if (m_curUpdateOIDemoActorTick >= m_defaultUpdateOIDemoActorInterval)
	{
		/*AActor* pDemoActor = GetWorld()->SpawnActor<AActor>(m_cardCombineDemoInfoMap[transformName].pDemoActorClass,
			loc + m_cardCombineDemoInfoMap[transformName].actorRelativeLoc, FRotator::ZeroRotator);
		pDemoActor->SetActorScale3D(m_cardCombineDemoInfoMap[transformName].scale);

		if (m_pSPPC->m_pWidgetManager->m_language == "Chinese")
		{
			int32 randChDemoWords = FMath::RandRange(0, m_cardCombineDemoInfoMap[transformName].chDemoWords.Num() - 1);
			if (randChDemoWords < m_cardCombineDemoInfoMap[transformName].chDemoWords.Num())
				pActionCard->m_pActionCardInfo->NotifyDemoWords(m_cardCombineDemoInfoMap[transformName].chDemoWords[randChDemoWords]);
		}
		else
		{
			int32 randChDemoWords = FMath::RandRange(0, m_cardCombineDemoInfoMap[transformName].enDemoWords.Num() - 1);
			if (randChDemoWords < m_cardCombineDemoInfoMap[transformName].enDemoWords.Num())
				pActionCard->m_pActionCardInfo->NotifyDemoWords(m_cardCombineDemoInfoMap[transformName].enDemoWords[randChDemoWords]);
		}*/

		float randX = FMath::RandRange(m_LDPoint.X, m_RTPoint.X);
		float randY = FMath::RandRange(m_LDPoint.Y, m_RTPoint.Y);
		FVector spawnLoc(randX, randY, m_actionPanelZ);
		int32 randOIDemoNb = FMath::RandRange(0, m_allOIDemoInfos.Num() - 1);
		AOverallIndexDemoActor* pDemoActor = NULL;
		if (m_allOIDemoInfos[randOIDemoNb].pDemoActorClass)
			pDemoActor = GetWorld()->SpawnActor<AOverallIndexDemoActor>(m_allOIDemoInfos[randOIDemoNb].pDemoActorClass, spawnLoc + m_allOIDemoInfos[randOIDemoNb].actorRelativeLoc, FRotator::ZeroRotator);
		else
			pDemoActor = GetWorld()->SpawnActor<AOverallIndexDemoActor>(m_pDefaultOIDemoActorClass, spawnLoc + m_allOIDemoInfos[randOIDemoNb].actorRelativeLoc, FRotator::ZeroRotator);
		pDemoActor->SetActorScale3D(m_allOIDemoInfos[randOIDemoNb].scale);
		if (m_allOIDemoInfos[randOIDemoNb].pDemoPS)
			pDemoActor->m_pDemoPS = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_allOIDemoInfos[randOIDemoNb].pDemoPS, pDemoActor->GetActorTransform());
		m_pOIDemoActors.Add(pDemoActor);
		if (m_allOIDemoInfos[randOIDemoNb].chDemoWords.Num() > 0)
		{
			int32 randDemoWordNb = FMath::RandRange(0, m_allOIDemoInfos[randOIDemoNb].chDemoWords.Num() - 1);
			if (!m_pSPPC->m_pSPMenu || m_pSPPC->m_pSPMenu->m_pWidgetManager->m_language == "English")
				pDemoActor->NotifyDemoOverallIndexWords(m_allOIDemoInfos[randOIDemoNb].enDemoWords[randDemoWordNb]);
			else
				pDemoActor->NotifyDemoOverallIndexWords(m_allOIDemoInfos[randOIDemoNb].chDemoWords[randDemoWordNb]);
		}
		m_curUpdateOIDemoActorTick = 0;
	}
	else m_curUpdateOIDemoActorTick += 1;
	/*if (m_curDemoOverallIndexNb >= 6) m_curDemoOverallIndexNb = 0;
	int32 demoNb = 0;
	while (demoNb <m_pOIDemoActors.Num())
	{
		if (!m_pOIDemoActors[demoNb])
		{
			m_pOIDemoActors.RemoveAt(demoNb);
			continue;
		}
		if (m_pOIDemoActors[demoNb]->m_curTick >= m_OIDemoTime)
		{
			m_pOIDemoActors[demoNb]->m_pDemoPS->DeactivateSystem();
			if (m_pOIDemoActors[demoNb]->IsValidLowLevel())
			{
				m_pOIDemoActors[demoNb]->Destroy();
				m_pOIDemoActors[demoNb]->ConditionalBeginDestroy();
				m_pOIDemoActors.RemoveAt(demoNb);
				continue;
			}
		}
		else
		{
			m_pOIDemoActors[demoNb]->m_curTick += dT;
			demoNb += 1;
		}
	}

	if (m_curUpdateOIDemoActorTick >= m_defaultUpdateOIDemoActorInterval)
	{
		if (!m_overallIndexDemoInfoMap.Contains(m_curDemoOverallIndexNb))
		{
			m_curDemoOverallIndexNb += 1;
			m_curUpdateOIDemoActorTick = 0;
			return;
		}
		int32 m_curIndex = 0;
		if (m_curDemoOverallIndexNb == 0)
			m_curIndex = m_curOverallIndex.activity;
		else if (m_curDemoOverallIndexNb == 1)
			m_curIndex = m_curOverallIndex.mentality;
		else if (m_curDemoOverallIndexNb == 1)
			m_curIndex = m_curOverallIndex.suppression;
		else if (m_curDemoOverallIndexNb == 1)
			m_curIndex = m_curOverallIndex.flameFaith;
		else if (m_curDemoOverallIndexNb == 1)
			m_curIndex = m_curOverallIndex.sunFaith;
		else if (m_curDemoOverallIndexNb == 1)
			m_curIndex = m_curOverallIndex.darkness;
		for (int32 i=0; i< m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list.Num(); i++)
		{
			if (m_curIndex <= m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].maxOverallIndex || i == m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list.Num() - 1)
			{
				float xSpan = m_RTPoint.X - m_LDPoint.X;
				float ySpan = m_RTPoint.Y - m_LDPoint.Y;
				float randX = FMath::RandRange(m_LDPoint.X, m_RTPoint.X);
				float randY = FMath::RandRange(m_LDPoint.Y, m_RTPoint.Y);
				FVector spawnLoc(randX, randY, m_actionPanelZ);
				AOverallIndexDemoActor* pDemoActor = GetWorld()->SpawnActor<AOverallIndexDemoActor>(m_overallIndexDemoActorClass, spawnLoc, FRotator::ZeroRotator);
				int32 randInfoNb = FMath::RandRange(0, m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].demoInfos.Num() - 1);
				int32 randPSNb = FMath::RandRange(0, m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].pPS.Num() - 1);
				pDemoActor->m_pDemoPS = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].pPS[randPSNb], pDemoActor->GetActorTransform());
				m_pOIDemoActors.Add(pDemoActor);
				if (!m_pSPPC->m_pSPMenu || m_pSPPC->m_pSPMenu->m_pWidgetManager->m_language == "English")
					pDemoActor->NotifyDemoOverallIndexWords(m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].demoInfos[randInfoNb].enDemoWords);
				else
					pDemoActor->NotifyDemoOverallIndexWords(m_overallIndexDemoInfoMap[m_curDemoOverallIndexNb].list[i].demoInfos[randInfoNb].chDemoWords);
				break;
			}
		}
		m_curDemoOverallIndexNb += 1;
		m_curUpdateOIDemoActorTick = 0;
	}
	else m_curUpdateOIDemoActorTick += 1;*/
}

void ASingleProgressGameMode::NotifySetSkyColorMatParam_Implementation(uint8 curProgress, bool dayOrNight, bool battleOrSP)
{

}

void ASingleProgressGameMode::ReadOverallIndexDemoInfoList_Implementation()
{

}

void ASingleProgressGameMode::SpawnAllShadowActors()
{
	
	GetWorldTimerManager().ClearTimer(m_pSPPC->m_shadowModeTimerHandle);
}

void ASingleProgressGameMode::EndShadowMode()
{
	while (m_pShadowActorList.Num() > 0)
	{
		DeleteShadowActor(m_pShadowActorList.Last());
	}
	m_pSPPC->SwitchMenu(0);
	if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
	m_pShadowActorList.Empty();
	m_pShadowActorPSComponentList.Empty();

	ResumeTick();
	ShowAllCardWidget();
	ShowAllCard();
	
	m_gameState = 0;
	m_pSPPC->m_gameState = 0;
}

void ASingleProgressGameMode::SpawnRuneDemoCharacter(uint8 idleState)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FString characterName = pCWGI->m_curPlayerSPInfo.characterName;
	if (characterName == "" || characterName == "NULL") characterName = "Lucian";
	TSubclassOf<class ADemoCharacter> characterClass = ReadCharacterBP(characterName);
	if (idleState == 0)
		m_pDemoCharacter = GetWorld()->SpawnActor<ADemoCharacter>(characterClass, m_demoCharacterLoc, m_demoCharacterRot);
	else if (idleState == 1)
	{
		m_pDemoCharacter = GetWorld()->SpawnActor<ADemoCharacter>(characterClass, m_defaultTheorizeCharacterLoc, m_defaultTheorizeCharacterRot);
		TSubclassOf<class ADemoCharacter> demoEnermyClass = ReadCharacterBP("DemoEnermy");
		m_pDemoEnermy = GetWorld()->SpawnActor<ADemoCharacter>(demoEnermyClass, m_defaultTheorizeDemoEnermyLoc, m_defaultTheorizeDemoEnermyRot);
		UAnimInstance* pEnermyAnimInstance = m_pDemoEnermy->GetMesh()->GetAnimInstance();
		m_pDemoEnermy->m_pAnimInstance = Cast<UBaseAnimInstance>(pEnermyAnimInstance);
	}
	else if (idleState == 2)
		m_pDemoCharacter = GetWorld()->SpawnActor<ADemoCharacter>(characterClass, m_defaultDiceCharacterLoc, m_defaultDiceCharacterRot);
	UAnimInstance* pAnimInstance = m_pDemoCharacter->GetMesh()->GetAnimInstance();
	if (pAnimInstance)
	{
		m_pDemoCharacter->m_pAnimInstance = Cast<UBaseAnimInstance>(pAnimInstance);
		m_pDemoCharacter->m_pAnimInstance->m_idleMotionState = idleState;
	}
}

void ASingleProgressGameMode::ResetItemList(const FCharacterItemList& itemList)
{
	if (!m_pDemoCharacter) return;
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pDemoCharacter->m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value) continue;
		iter->Value->SetSkeletalMesh(NULL);
	}
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pDemoCharacter->m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value || iter->Key >= itemList.pItemMeshList.Num() || !itemList.pItemMeshList[iter->Key]) continue;
		iter->Value->SetSkeletalMesh(itemList.pItemMeshList[iter->Key]);
	}
	/*for (int32 i = 0; i < m_pDemoCharacter->m_pItemComponents.Num(); i++)
	{
		m_pDemoCharacter->m_pItemComponents[i].pComponent->SetSkeletalMesh(NULL);
	}
	for (int32 i = 0; i < itemList.pItemMeshList.Num(); i++)
	{
		if (!itemList.pItemMeshList[i] || i >= m_pDemoCharacter->m_pItemComponents.Num()) continue;
		m_pDemoCharacter->m_pItemComponents[i].pComponent->SetSkeletalMesh(itemList.pItemMeshList[i]);
	}*/
}

void ASingleProgressGameMode::UpdateCaptureScenes()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (!m_captureFramesInfo.Contains(pCWGI->m_curPlayerSPInfo.curProgress)) return;
	if (!m_captureFramesInfo[pCWGI->m_curPlayerSPInfo.curProgress].captureFrames.Contains(m_curTickCount)) return;
	m_pSPPC->CaptureScene();
}

void ASingleProgressGameMode::EndSP()
{
	/*UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i<m_pPlayCards.Num(); i++)
	{
		if (!m_pPlayCards[i] || m_pPlayCards[i]->m_cardType == 0 || m_pPlayCards[i]->m_cardType == 2 ||
			!m_pPlayCardTextureMap.Contains(m_pPlayCards[i]->m_cardName) || m_pPlayCardTextureMap[m_pPlayCards[i]->m_cardName].isInitial)
			continue;
		pCWGI->m_inheritCardNames.Add(m_pPlayCards[i]->m_cardName);
	}
	if (pCWGI->m_curPlayerSPInfo.curProgress >= 2)
	{
		//说明是结局，读取结局界面
		ReadAllEndingInfo(0);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->LoadEndSPMenu(3);
		/ *if (pSPPC->m_pEndMenu->m_pFlipImage->m_textureList.pTextureList.Num() == 0)
			GetWorldTimerManager().SetTimer(m_endSPTimeHandler, pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_noPictureActivateTextTime, false);
		else
			GetWorldTimerManager().SetTimer(m_endSPTimeHandler, pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_gotPictureActivateTextTime, false);* /
		GetWorldTimerManager().SetTimer(m_endSPTimeHandler, pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_gotPictureActivateTextTime, false);
	}
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 0)
	{
		pCWGI->m_curPlayerSPInfo.curProgress += 1;
		FString levelName = "SingleProgressMap_Desert";
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		int32 i = 0;
		while (i < m_pPlayCards.Num())
		{
			if (m_pPlayCards[i]->m_tags.Contains("Location") && m_pPlayCards[i]->m_cardName != "Wild")
				DeleteCard(m_pPlayCards[i], false);
			else i += 1;
		}
		m_oneTimeOutputRecords.Empty();
		m_periodicEvents.Empty();
		m_potentialEvents.Empty();
		m_existEventCodeNameMap.Empty();
		pSPPC->SaveGame("SwitchLandscape", 0);
		pCWGI->m_battleState = 3;
		UGameplayStatics::OpenLevel(this, FName(*levelName));
	}
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 1)
	{
		pCWGI->m_curPlayerSPInfo.curProgress += 1;
		FString levelName = "SingleProgressMap_Forest";
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		int32 i = 0;
		while (i < m_pPlayCards.Num())
		{
			if (m_pPlayCards[i]->m_tags.Contains("Location") && m_pPlayCards[i]->m_cardName != "Wild")
				DeleteCard(m_pPlayCards[i], false);
			else i += 1;
		}
		m_oneTimeOutputRecords.Empty();
		m_periodicEvents.Empty();
		m_potentialEvents.Empty();
		m_existEventCodeNameMap.Empty();
		pSPPC->SaveGame("SwitchLandscape", 0);
		pCWGI->m_battleState = 3;
		UGameplayStatics::OpenLevel(this, FName(*levelName));
	}*/
	ReadAllEndingInfo(m_endType);
	m_pSPPC->LoadEndSPMenu(3);
	/*if (pSPPC->m_pEndMenu->m_pFlipImage->m_textureList.pTextureList.Num() == 0)
		GetWorldTimerManager().SetTimer(m_endSPTimeHandler, pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_noPictureActivateTextTime, false);
	else
		GetWorldTimerManager().SetTimer(m_endSPTimeHandler, pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_gotPictureActivateTextTime, false);*/
		GetWorldTimerManager().SetTimer(m_endSPTimeHandler, m_pSPPC->m_pEndMenu, &UTEndMenu::ActivateSwitchTextTick, m_gotPictureActivateTextTime, false);
}

void ASingleProgressGameMode::GetEndInfo(const TArray<FEndInfo>& endInfos, uint8 endType)
{
	if (endType == 1)
	{
		//说明是没达成指标式失败结局，直接取最后一个结局
		m_endInfo = endInfos.Last();
		return;
	}
	for (int32 i=0; i<endInfos.Num(); i++)
	{
		if (m_curOverallIndex.activity < endInfos[i].triggerInfo.minActivity || m_curOverallIndex.activity > endInfos[i].triggerInfo.maxActivity ||
			m_curOverallIndex.darkness < endInfos[i].triggerInfo.minDarkness || m_curOverallIndex.darkness > endInfos[i].triggerInfo.maxDarkness ||
			m_curOverallIndex.mentality < endInfos[i].triggerInfo.minMentality || m_curOverallIndex.mentality > endInfos[i].triggerInfo.maxMentality ||
			m_curOverallIndex.money < endInfos[i].triggerInfo.minMoney || m_curOverallIndex.money > endInfos[i].triggerInfo.maxMoney ||
			m_curOverallIndex.suppression < endInfos[i].triggerInfo.minSuppression || m_curOverallIndex.suppression > endInfos[i].triggerInfo.maxSuppression ||
			m_curOverallIndex.flameFaith < endInfos[i].triggerInfo.minFlameFaith || m_curOverallIndex.flameFaith > endInfos[i].triggerInfo.maxFlameFaith ||
			m_curOverallIndex.sunFaith < endInfos[i].triggerInfo.minSunFaith || m_curOverallIndex.sunFaith > endInfos[i].triggerInfo.maxSunFaith)
			continue;
		m_endInfo = endInfos[i];
		return;
	}
	m_endInfo = endInfos[0];
}

void ASingleProgressGameMode::ReadTutorialSteps_Implementation()
{

}

void ASingleProgressGameMode::UpdateTutorialStep()
{
	if (m_pTutorialIndicator && m_pTutorialIndicator->IsValidLowLevel())
	{
		m_pTutorialIndicator->Destroy();
		m_pTutorialIndicator->ConditionalBeginDestroy();
	}
	while (m_pSPPC->m_pTutorialIndicators.Num() > 0)
	{
		m_pSPPC->m_pTutorialIndicators.Last()->RemoveFromParent();
		if (m_pSPPC->m_pTutorialIndicators.Last()->IsValidLowLevel())
		{
			m_pSPPC->m_pTutorialIndicators.Last()->ConditionalBeginDestroy();
		}
		m_pSPPC->m_pTutorialIndicators.Pop();
	}
	if (m_tutorialSteps.Num() <= 0) return;
	/**
	* 1. 先判定是否需要生成指示器
	* 2. 然后更新指示菜单
	*/
	
	m_pSPPC->NotifySpawnMenuTutorIndicator(m_tutorialSteps[0].operationName);
	if (m_pSPPC->m_pTutorialMenu)
	{
		if (m_pSPPC->m_pTutorialMenu->m_pWidgetManager->m_language == "Chinese")
			m_pSPPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].chExplanation));
		else
			m_pSPPC->m_pTutorialMenu->m_pDescription->SetText(FText::FromString(m_tutorialSteps[0].enExplanation));
	}
	if (m_tutorialSteps[0].isSpawnIndicator)
	{
		FString spawnIndicatorActorType = m_tutorialSteps[0].spawnIndicationActorName.Left(2);
		FString spawnIndicatorActorName = m_tutorialSteps[0].spawnIndicationActorName.RightChop(3);
		//TArray<AActor*> pAllActors;
		AActor* pTargetActor = NULL;
		if (spawnIndicatorActorType == "AC")
		{
			//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActionCard::StaticClass(), pAllActors);
			for (int32 i=0; i<m_pActionCards.Num(); i++)
			{
				if (!m_pActionCards[i] || m_pActionCards[i]->m_cardName != spawnIndicatorActorName) continue;
				pTargetActor = m_pActionCards[i];
				break;
			}
		}
		else if (spawnIndicatorActorType == "PC")
		{
			for (int32 i = 0; i < m_pPlayCards.Num(); i++)
			{
				if (!m_pPlayCards[i] || m_pPlayCards[i]->m_cardName != spawnIndicatorActorName) continue;
				pTargetActor = m_pPlayCards[i];
				break;
			}
		}
		else if (spawnIndicatorActorType == "NC")
		{
			//FString colorStr = spawnIndicatorActorName.Left(1);
			//FString nbStr = spawnIndicatorActorName.RightChop(1);
			if (!spawnIndicatorActorName.Contains("Theorize"))
			{
				if (spawnIndicatorActorName.Contains("Color"))
				{
					for (int32 i = 0; i < m_pNumericCards.Num(); i++)
					{
						if (!m_pNumericCards[i]) continue;
						ANumericCard* pNumericCard = Cast<ANumericCard>(m_pNumericCards[i]);
						if (!pNumericCard->m_tags.Contains(spawnIndicatorActorName))
							continue;
						pTargetActor = pNumericCard;
						break;
					}
				}
				else
				{
					for (int32 i = 0; i < m_pNumericCards.Num(); i++)
					{
						if (!m_pNumericCards[i]) continue;
						ANumericCard* pNumericCard = Cast<ANumericCard>(m_pNumericCards[i]);
						if (pNumericCard->m_nb != FCString::Atoi(*spawnIndicatorActorName))
							continue;
						pTargetActor = pNumericCard;
						break;
					}
				}

			}
			else
			{
				if (!pTargetActor)
				{
					for (int32 i = 0; i < m_pPlayerTheorizeCards.Num(); i++)
					{
						if (!m_pPlayerTheorizeCards[i]) continue;
						if (m_pPlayerTheorizeCards[i]->m_cardName != spawnIndicatorActorName) continue;
						pTargetActor = m_pPlayerTheorizeCards[i];
						break;
					}
				}
				if (!pTargetActor)
				{
					for (int32 i = 0; i < m_pOppTheorizeCards.Num(); i++)
					{
						if (!m_pOppTheorizeCards[i]) continue;
						if (m_pOppTheorizeCards[i]->m_cardName != spawnIndicatorActorName) continue;
						pTargetActor = m_pOppTheorizeCards[i];
						break;
					}
				}
			}
			
		}

		if (!pTargetActor) return;
		FVector indicatorLoc = pTargetActor->GetActorLocation() + m_tutorialSteps[0].indicatorRelativeLoc;
		m_pTutorialIndicator = GetWorld()->SpawnActor<AActor>(m_tutorialIndicatorClass, indicatorLoc, FRotator::ZeroRotator);
		NotifyIndicatorShowUp();
	}
}

void ASingleProgressGameMode::DeleteTutorialStep()
{
	m_tutorialSteps.RemoveAt(0);
	UpdateTutorialStep();
	if (m_tutorialSteps.Num() > 0) return;
	m_pSPPC->m_isInTutorial = false;
}

void ASingleProgressGameMode::RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type)
{
	if (type == 0)
	{
		//说明是在SPMenu阶段
		if (!m_pSPPC->m_pSPMenu) return;
		if (!needToShowTutorialButton) m_pSPPC->m_pSPMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pSPPC->m_pSPMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (type == 1)
	{
		//说明是在DiceBattleMenu阶段
		if (!m_pSPPC->m_pDiceBattleMenu) return;
		if (!needToShowTutorialButton) m_pSPPC->m_pDiceBattleMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pSPPC->m_pDiceBattleMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (type == 2)
	{
		//说明是在TheorizeMenu阶段
		if (!m_pSPPC->m_pTheorizeMenu) return;
		if (!needToShowTutorialButton) m_pSPPC->m_pTheorizeMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pSPPC->m_pTheorizeMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (type == 3)
	{
		//说明是在TheorizeMenu阶段
		if (!m_pSPPC->m_pShadowModeMenu) return;
		if (!needToShowTutorialButton) m_pSPPC->m_pShadowModeMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pSPPC->m_pShadowModeMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (type == 4)
	{
		//说明是在TheorizeMenu阶段
		if (!m_pSPPC->m_pSkillSelectMenu) return;
		if (!needToShowTutorialButton) m_pSPPC->m_pSkillSelectMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		else
			m_pSPPC->m_pSkillSelectMenu->m_pTutorialButton->SetVisibility(ESlateVisibility::Visible);
	}
	m_curTutorialName = tutorialStepName;
	//FTutorialStepSerial tutorialSerial = ReadTutorialInfoByName(m_curTutorialName);
}

FCharacterAttributeInfo ASingleProgressGameMode::GetCharacterAttributeInfo_Implementation(const FString& characterName)
{
	FCharacterAttributeInfo info(0, 0, 0);
	return info;
}

void ASingleProgressGameMode::GenerateRandActionNodeWeb(bool isIncludeBossBattle)
{
	TArray<int32> weightList;
	int32 weightSum = 0;
	for (int32 i=0; i<m_actionNodePercent.actionTypeList.Num(); i++)
	{
		int32 randWeight = FMath::RandRange(m_actionNodePercent.actionNodeRangeList[i].min, m_actionNodePercent.actionNodeRangeList[i].max);
		weightList.Add(randWeight);
		weightSum += randWeight;
	}

	TArray<int32> rewardWeightList;
	int32 rewardWeightSum = 0;
	for (int32 i=0; i<m_actionNodePercent.rewardRangeList.Num(); i++)
	{
		int32 randWeight = FMath::RandRange(m_actionNodePercent.rewardRangeList[i].min, m_actionNodePercent.rewardRangeList[i].max);
		rewardWeightSum += randWeight;
		rewardWeightList.Add(rewardWeightSum);
	}

	for (int32 i=0; i<weightList.Num(); i++)
	{
		if (!m_allEventInfoMap.Contains(m_actionNodePercent.actionTypeList[i])) continue;
		TArray<FString> availableActionNodeNames;
		//We should extract all actionnodeinfo from m_allEventInfoMap, so that we can pick up random actionNodeInfo
		for (int32 j=0; j<m_allEventInfoMap[m_actionNodePercent.actionTypeList[i]].eventCardInfoList.Num(); j++)
		{
			availableActionNodeNames.Add(m_allEventInfoMap[m_actionNodePercent.actionTypeList[i]].eventCardInfoList[j].SAName);
		}

		int32 nodeNbPerAction = (int32)(((float)m_maxActionNodeNbPerLine * (float)weightList[i]) / (float)weightSum);
		for (int32 j=0; j<nodeNbPerAction; j++)
		{
			FActionNodeBriefInfoList newBriefList;
			int32 randPos = FMath::RandRange(0, m_actionNodeList.Num());
			for (int32 k=0; k<m_pEventNodeManager->m_multipleChoiceNb; k++)
			{
				int32 randActionNamePos = FMath::RandRange(0, availableActionNodeNames.Num() - 1);
				FActionNodeBriefInfo newBriefInfo;
				newBriefInfo.actionType = m_actionNodePercent.actionTypeList[i];
				newBriefInfo.nodeName = availableActionNodeNames[randActionNamePos];
				availableActionNodeNames.RemoveAt(randActionNamePos);
				newBriefList.actionNodeBriefInfoList.Add(newBriefInfo);
			}
			m_actionNodeList.Insert(newBriefList, randPos);
		}
	}
	//接下来进行奖励运算
	for (int32 i=0; i<m_actionNodeList.Num(); i++)
	{
		for (int32 j=0; j<m_actionNodeList[i].actionNodeBriefInfoList.Num(); j++)
		{
			//随机一个整数，看这个整数落在哪个区间，对应哪个奖励
			uint8 rewardType = 0;
			int32 randWeight = FMath::RandRange(0, rewardWeightSum);
			for (int32 k=0; k<rewardWeightList.Num(); k++)
			{
				if (randWeight <= rewardWeightList[k])
				{
					rewardType = (uint8)k;
					break;
				}
			}
			m_actionNodeList[i].actionNodeBriefInfoList[j].rewardType = rewardType;
		}
	}
}

void ASingleProgressGameMode::UpdateEventCardAction(bool isChoiceEvent)
{
	if (!isChoiceEvent)
	{
		if (m_pSPPC->m_pEventNodeManager->m_eventCardInfo.defaultActionType == 0 || m_pSPPC->m_pEventNodeManager->m_eventCardInfo.defaultActionType == 1)
			InitialBattle(m_pSPPC->m_pEventNodeManager->m_eventCardInfo.battleInfo);
		else if (m_pSPPC->m_pEventNodeManager->m_eventCardInfo.defaultActionType == 2)
		{
			ReadAllDifficultyDiceInfo();
			ReadDiceSkillPS(0);
			InitialDiceBattleParam(m_pSPPC->m_pEventNodeManager->m_eventCardInfo.diceInfo.difficulty, false);
			SpawnRuneDemoCharacter(2);
			m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
			m_curDiceScore = 0;
			m_curDiceFlipCardNb = 0;
			m_curDiceTotalCount = 0.f;
			m_pSPPC->m_pSPMenu->FadeOut();
			GetWorldTimerManager().SetTimer(m_diceAndTheorizeTimeHandler, this, &ASingleProgressGameMode::InitialDiceBattle, m_diceAndTheorizeFadeOutTime + 0.3f, false);
		}
		else if (m_pSPPC->m_pEventNodeManager->m_eventCardInfo.defaultActionType == 3)
		{
			m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
			InitialTheorizeParam(m_pSPPC->m_pEventNodeManager->m_eventCardInfo.theorizeInfo.difficulty);
			SpawnRuneDemoCharacter(1);
			m_theorizePlayerInfo.curScore = 0;
			m_pSPPC->m_pSPMenu->FadeOut();
			GetWorldTimerManager().SetTimer(m_diceAndTheorizeTimeHandler, this, &ASingleProgressGameMode::InitialTheorizePanel, m_diceAndTheorizeFadeOutTime + 0.3f, false);
		}
		else if (m_pSPPC->m_pEventNodeManager->m_eventCardInfo.defaultActionType == 4)
		{
			for (TMap<FString, FEventFunctionList>::TConstIterator iter = m_pSPPC->m_pEventNodeManager->m_eventCardInfo.actionChoiceMap.CreateConstIterator(); iter; ++iter)
			{
				FEventFunctionList funList = iter->Value;
				for (int32 i = 0; i < funList.list.Num(); i++)
				{
					TriggerChoiceEvent(funList.list[i]);
				}
				break;
			}
			if (m_pSPPC->m_pActionPanel) m_pSPPC->DeleteMenu("ActionPanel");
		}
	}
	else
	{
		if (!m_pSPPC->m_pEventNodeManager->m_eventCardInfo.actionChoiceMap.Contains(m_pSPPC->m_pEventNodeManager->m_choiceSelectStr) &&
			m_pSPPC->m_pEventNodeManager->m_choiceSelectStr != "") return;
		FEventFunctionList funList;
		if (m_pSPPC->m_pEventNodeManager->m_choiceSelectStr != "")
			 funList = m_pSPPC->m_pEventNodeManager->m_eventCardInfo.actionChoiceMap[m_pSPPC->m_pEventNodeManager->m_choiceSelectStr];
		else
		{
			TArray<FString> keys;
			m_pSPPC->m_pEventNodeManager->m_eventCardInfo.actionChoiceMap.GetKeys(keys);
			funList = m_pSPPC->m_pEventNodeManager->m_eventCardInfo.actionChoiceMap[keys.Last()];
		}
		for (int32 i=0; i<funList.list.Num(); i++)
		{
			TriggerChoiceEvent(funList.list[i]);
		}
		if (m_pSPPC->m_pActionPanel) m_pSPPC->DeleteMenu("ActionPanel");
	}

	if (m_pEventNodeManager->m_eventCardInfo.defaultActionType == 4)
	{
		//说明是故事型事件，此时要
		// 1. 更新gamemode中的进程信息
		// 2. 设置menu的进程信息
		//重新设置小进度条，大进度条+1
		UpdateActionNode(0);
		int32 maxActionNodeNb = m_maxActionNodeNbPerLine;
		if (m_isInBossBattleLayer) maxActionNodeNb += 1;
		if (m_curEventNodeNb >= maxActionNodeNb)
		{
			if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(0, m_curEventNodeLayerNb);
		}
		else
		{
			if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateSPProgressImage(m_curEventNodeNb, m_curEventNodeLayerNb);
		}
		NotifyLoadCalenderMenu();
	}

	if (m_pControlCharacter)
	{
		m_pControlCharacter->m_isDayOrNight = true;
		m_pControlCharacter->m_shouldRotatorDayNight = true;
	}
}

void ASingleProgressGameMode::NotifyIndicatorShowUp_Implementation()
{

}

void ASingleProgressGameMode::ReadAllEndingInfo_Implementation(uint8 state)
{

}

void ASingleProgressGameMode::ProceedNextGame()
{
	if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->FadeOut();
	m_pSPPC->PlayerCameraManager->StartCameraFade(0.f, 1.f, m_fadeOutTime, FLinearColor::Black, false, true);
	GetWorldTimerManager().SetTimer(m_openBattleLevelTimeHandler, this, &ASingleProgressGameMode::EnterMap, m_fadeOutTime, false);
}


void ASingleProgressGameMode::GenerateNumericCards(float dT)
{
	//APlayCard* pPlayCard = GetWorld()->SpawnActor<APlayCard>(m_numericCardClass, )
	if (m_curNumericCardGenerateTick < m_generateNumericCardInterval)
	{
		m_curNumericCardGenerateTick += dT;
		return;
	}
	m_curNumericCardGenerateTick = 0;
	int32 canSpawnNumericCardNb = m_maxNumericCardNb - m_pNumericCards.Num();
	for (int32 i=0; i< canSpawnNumericCardNb; i++)
	{
		uint8 randColor = FMath::RandRange(1, 4) - 1;
		int32 randNb = FMath::RandRange(1, 9);
		FVector emptyCardLoc;
		bool isFindEmptyLoc = FindEmptyCardLoc(emptyCardLoc);
		if (!isFindEmptyLoc) continue;
		ANumericCard* pNumericCard = GetWorld()->SpawnActor<ANumericCard>(m_numericCardClass, emptyCardLoc, FRotator::ZeroRotator);
		pNumericCard->InitialPlayCard(0, randNb, randColor, "NULL");
		//pNumericCard->m_loc = emptyCardLoc;
		m_pPlayCards.Add(pNumericCard);
		m_pNumericCards.Add(pNumericCard);
	}
}

void ASingleProgressGameMode::UpdateAllCards()
{
	int32 i = 0;
	while (i < m_pPlayCards.Num())
	{
		if (!m_pPlayCards[i]->m_isDead)
		{
			i += 1;
			continue;
		}
		DeleteCard(m_pPlayCards[i], true);
		/*if (m_pPlayCards[i]->m_cardType == 2)
		{
			AActionCard* pActionCard = Cast<AActionCard>(m_pPlayCards[i]);
			if (pActionCard->m_actionType == 5)
			{
				bool findCard = false;
				for (TMap<int32, AActionCard*>::TConstIterator iter = m_pEventCardMap.CreateConstIterator(); iter; ++iter)
				{
					if (iter->Value != pActionCard) continue;
					EventOff(iter->Key);
					m_pPlayCards.RemoveAt(i);
					findCard = true;
					break;
				}
				if (!findCard) i += 1;
			}
			else
			{
				if (m_pPlayCards[i]->IsValidLowLevel())
				{
					m_pPlayCards[i]->Destroy();
					m_pPlayCards[i]->ConditionalBeginDestroy();
					m_pPlayCards.RemoveAt(i);
				}
				else i += 1;
			}
		}
		else
		{
			if (m_pPlayCards[i]->IsValidLowLevel())
			{
				m_pPlayCards[i]->Destroy();
				m_pPlayCards[i]->ConditionalBeginDestroy();
				m_pPlayCards.RemoveAt(i);
			}
			else i += 1;
		}*/
	}
}

void ASingleProgressGameMode::NotifyChangeGameState_Implementation(uint8 state)
{

}

void ASingleProgressGameMode::NotifyFadeIn_Implementation()
{

}

void ASingleProgressGameMode::GenerateJudgeCard(uint8& judgeColor, int32& judgeNb)
{
	if (m_leftJudgeCardList.Num() > 0)
	{
		int32 randNb = FMath::RandRange(0, m_leftJudgeCardList.Num() - 1);
		judgeColor = (m_leftJudgeCardList[randNb] - 1) / 13;
		judgeNb = m_leftJudgeCardList[randNb] - judgeColor * 13;
		m_leftJudgeCardList.RemoveAt(randNb);
	}
	else
	{
		m_leftJudgeCardList = {
			1,2,3,4,5,6,7,8,9,10,
			11,12,13,14,15,16,17,18,19,20,
			21,22,23,24,25,26,27,28,29,30,
			31,32,33,34,35,36,37,38,39,40,
			41,42,43,44,45,46,47,48,49,50,
			51,52
		};
		int32 randNb = FMath::RandRange(0, m_leftJudgeCardList.Num() - 1);
		judgeColor = m_leftJudgeCardList[randNb] / 13;
		judgeNb = randNb - judgeColor * 13 + 1;
		m_leftJudgeCardList.RemoveAt(randNb);
	}
}


APlayCard* ASingleProgressGameMode::SpawnNewPlayCard(int32 cardNb, uint8 color, FString cardName)
{
	FVector emptyCardLoc;
	if (cardName == "Thoughts" || cardName == "Explore" || cardName == "Communication" || cardName == "Research" || 
		cardName == "Forge" || cardName.Contains("Event_"))
	{
		bool isFindEmptyLoc = FindEmptyActionCardLoc(emptyCardLoc);
		if (!isFindEmptyLoc) return NULL;
		AActionCard* pPlayCard = GetWorld()->SpawnActor<AActionCard>(m_actionCardClass, emptyCardLoc, FRotator::ZeroRotator);
		pPlayCard->InitialPlayCard(2, cardNb, color, cardName);
		//pPlayCard->m_loc = emptyCardLoc;
		m_pPlayCards.Add(pPlayCard);
		m_pActionCards.Add(pPlayCard);
		pPlayCard->NotifyInitialCard("", pPlayCard->m_actionName, cardNb);
		if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateCardNbText();
		return pPlayCard;
	}
	else
	{
		bool isFindEmptyLoc = FindEmptyCardLoc(emptyCardLoc);
		if (!isFindEmptyLoc) return NULL;
		if (cardNb == -1)
		{
			APlayCard* pPlayCard = GetWorld()->SpawnActor<APlayCard>(m_playCardClass, emptyCardLoc, FRotator::ZeroRotator);
			pPlayCard->InitialPlayCard(1, cardNb, color, cardName);
			//pPlayCard->m_loc = emptyCardLoc;
			m_pPlayCards.Add(pPlayCard);
			if (m_pSPPC->m_pSPMenu) m_pSPPC->m_pSPMenu->UpdateCardNbText();
			pPlayCard->NotifyInitialCard("", cardName, cardNb);
			return pPlayCard;
		}
		else
		{
			ANumericCard* pPlayCard = GetWorld()->SpawnActor<ANumericCard>(m_numericCardClass, emptyCardLoc, FRotator::ZeroRotator);
			pPlayCard->InitialPlayCard(0, cardNb, color, cardName);
			//pPlayCard->m_loc = emptyCardLoc;
			m_pPlayCards.Add(pPlayCard);
			m_pNumericCards.Add(pPlayCard);
			pPlayCard->NotifyInitialCard("", cardName, cardNb);
			return pPlayCard;
		}
	}
	return NULL;
}

void ASingleProgressGameMode::ReadCardCombineDemoInfo_Implementation()
{

}

void ASingleProgressGameMode::EnterMap()
{
	//OpenBattleLevel();
	//这里要做两件事，一是读取战斗技能选择界面，二是计算得出天气
	//天气的计算要获得固定卡、事件卡
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);

	if (!pCWGameInstance->m_doneTutorialSteps.Contains(m_fixTutorialSerialNames[4])) RefreshTutorial(m_fixTutorialSerialNames[4], true, 4);
	else RefreshTutorial("NULL", false, 4);
	OpenBattleLevel();
}

void ASingleProgressGameMode::NotifyInitialMissionList_Implementation()
{

}

void ASingleProgressGameMode::NotifyGetMissionListByName_Implementation(const FString& groupName)
{

}

void ASingleProgressGameMode::NotifyGenTinyMap_Implementation(const FString& tinyMapName)
{

}
