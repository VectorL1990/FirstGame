// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "LoginGameModeBase.h"
#include "../../Base/Login/LoginPlayerController.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"



/*
void ALoginGameModeBase::installEvents()
{
	Super::installEvents();

	// login
	KBENGINE_REGISTER_EVENT("onCreateAccountResult", onCreateAccountResult);
	KBENGINE_REGISTER_EVENT("onLoginFailed", onLoginFailed);
	KBENGINE_REGISTER_EVENT("onVersionNotMatch", onVersionNotMatch);
	KBENGINE_REGISTER_EVENT("onScriptVersionNotMatch", onScriptVersionNotMatch);
	KBENGINE_REGISTER_EVENT("onLoginBaseappFailed", onLoginBaseappFailed);
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", onLoginSuccessfully);
	KBENGINE_REGISTER_EVENT("onLoginBaseapp", onLoginBaseapp);
	KBENGINE_REGISTER_EVENT("Loginapp_importClientMessages", Loginapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientMessages", Baseapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientEntityDef", Baseapp_importClientEntityDef);
	KBENGINE_REGISTER_EVENT("dispatchPlayerInfo", dispatchPlayerInfo);
	KBENGINE_REGISTER_EVENT("dispatchMallInfoList", dispatchMallInfoList);
	KBENGINE_REGISTER_EVENT("dispatchLogonStatus", dispatchLogonStatus);
	KBENGINE_REGISTER_EVENT("dispatchRelogonInfo", dispatchRelogonInfo);
	KBENGINE_REGISTER_EVENT("dispatchRelogonPlayerInfo", dispatchRelogonPlayerInfo);
}*/

void ALoginGameModeBase::BeginPlay()
{
	// 每次进入到这个界面时对KBE做一次清理，否则KBE插件内缓存的内容将一直存在
	//KBEngineApp::getSingleton().reset();

	//Super::BeginPlay();
	TestShipping("LoginGameMode::BeginPlay Start");
	TellBPBeginPlay();
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	m_pLPC = Cast<ALoginPlayerController>(pPC);
	bool isSaveSlotExist = UGameplayStatics::DoesSaveGameExist("AllProgressInfo", 0);
	TestShipping("LoginGameMode::BeginPlay Test All Progress Info");
	if (!isSaveSlotExist) return;
	TestShipping("LoginGameMode::BeginPlay AllProgress Info Exist");
	USaveGame* pSaveGame = UGameplayStatics::LoadGameFromSlot("AllProgressInfo", 0);
	m_pLPC->m_pOverallSaveGameObject = Cast<UOverallSaveGame>(pSaveGame);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	pCWGI->m_playerSingleProgressInfos = m_pLPC->m_pOverallSaveGameObject->m_allProgressInfos;
	pCWGI->m_battleState = 0;
	pCWGI->m_doneTutorialSteps = m_pLPC->m_pOverallSaveGameObject->m_doneTutorialSteps;
	pCWGI->m_curPlayerSPInfo.Reset();

	TestShipping("LoginGameMode::BeginPlay Before AsyncLoad");
	m_pCWSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
	if (!m_pCWSingleton->m_asyncLoadStateDone.Contains(0) || !m_pCWSingleton->m_asyncLoadStateDone.Contains(3))
	{
		m_pLPC->m_pLoadMenu = CreateWidget<UTTransitionMenu>(m_pLPC, m_pLPC->m_pWidgetManager->m_widgetClassMap["LoadMenu"]);
		m_pLPC->m_pLoadMenu->NotifyInitial();
		//m_pLPC->m_pLoadMenu->m_pProgressBar->SetVisibility(ESlateVisibility::Hidden);
		//m_pLPC->m_pLoadMenu->m_pProgressImage->SetVisibility(ESlateVisibility::Hidden);
		m_pLPC->m_pLoadMenu->m_pWidgetManager = m_pLPC->m_pWidgetManager;
		m_pLPC->m_pLoadMenu->AddToViewport();
		TestShipping("LoginGameMode::BeginPlay ReqAsyncLoc 0");
		m_pCWSingleton->ReqAsynLoad(0);
		TestShipping("LoginGameMode::BeginPlay ReqAsyncLoc 3");
		m_pCWSingleton->ReqAsynLoad(3);
	}
	
	m_canTick = true;
	/*if (pCWGI->m_curPlayerSPInfo.isInitial)
		TestShipping("LoginGameMode_BeginPlay isInitial is true");*/
	//NotifyPlaySound2D(0);
}

void ALoginGameModeBase::Tick(float DeltaSeconds)
{
	//TickToNewLevel();
	if (!m_canTick) return;
	if (!m_hasApplyAsyncLoad)
	{
		if (!m_pCWSingleton->m_asyncLoadStateDone.Contains(0) || !m_pCWSingleton->m_asyncLoadStateDone.Contains(3) || m_type == 1)
		{
			//这时资源还没读取完毕
			if (!m_pLPC->m_pLoadMenu) return;
			if (m_pCWSingleton->m_asyncLoadStateDone.Contains(0) && !m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Contains(0))
			{
				m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Add(0);
				m_pLPC->m_pLoadMenu->m_curLoadProgress += 50;
				m_pLPC->m_pLoadMenu->UpdateProgressBar();
			}
			if (m_pCWSingleton->m_asyncLoadStateDone.Contains(3) && !m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Contains(3))
			{
				m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Add(3);
				m_pLPC->m_pLoadMenu->m_curLoadProgress += 50;
				m_pLPC->m_pLoadMenu->UpdateProgressBar();
				//m_pCWSingleton->ReqAsynLoad(2);
			}
		}
		else
		{
			//说明这时已经读取角色数据完毕
			if (!m_pLPC->m_pLoadMenu)
			{
				//这时直接进入展示Logo阶段
				m_pLPC->NotifyLoadLogoMenu();
			}
			else
			{
				//这时直接删除读取界面即可
				m_pLPC->m_pLoadMenu->RemoveFromParent();
				if (m_pLPC->m_pLoadMenu->IsValidLowLevel()) m_pLPC->m_pLoadMenu->ConditionalBeginDestroy();
				m_pLPC->m_pLoadMenu = NULL;
				m_pLPC->NotifyLoadLogoMenu();
			}
			//说明已经读取角色完毕，不会被tick无限执行
			m_type = 1;
		}
	}
	else
	{
		if (m_pCWSingleton->m_asyncLoadStateDone.Contains(0) && m_pCWSingleton->m_asyncLoadStateDone.Contains(1) && m_pCWSingleton->m_asyncLoadStateDone.Contains(2))
		{
			//说明所有异步加载完毕，可以执行OpenLevel了
			if (m_pLPC->m_pLoadMenu) m_pLPC->m_pLoadMenu->RemoveFromParent();
			OpenSPLevel();
		}
		else
		{
			if (!m_pLPC->m_pLoadMenu) return;
			if (m_pCWSingleton->m_asyncLoadStateDone.Contains(0) && !m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Contains(0))
			{
				m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Add(0);
				m_pLPC->m_pLoadMenu->m_curLoadProgress += 30;
				m_pLPC->m_pLoadMenu->UpdateProgressBar();
			}
			if (m_pCWSingleton->m_asyncLoadStateDone.Contains(1) && !m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Contains(1))
			{
				m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Add(1);
				m_pLPC->m_pLoadMenu->m_curLoadProgress += 50;
				m_pLPC->m_pLoadMenu->UpdateProgressBar();
				//m_pCWSingleton->ReqAsynLoad(2);
			}
			if (m_pCWSingleton->m_asyncLoadStateDone.Contains(2) && !m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Contains(2))
			{
				m_pLPC->m_pLoadMenu->m_asyncLoadDoneState.Add(2);
				m_pLPC->m_pLoadMenu->m_curLoadProgress += 20;
				m_pLPC->m_pLoadMenu->UpdateProgressBar();
			}
		}
	}
}

void ALoginGameModeBase::Destroyed()
{
	Super::Destroyed();
}

void ALoginGameModeBase::OpenSPLevel()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	/*if (pCWGI->m_curPlayerSPInfo.isInitial)
		TestShipping("OpenSPLevel_BeginPlay isInitial is true");*/
	FString levelName;
	if (pCWGI->m_curPlayerSPInfo.curProgress == 0)
		levelName = "SingleprogressMap_Snow";
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 1)
		levelName = "SingleprogressMap_Desert";
	else if (pCWGI->m_curPlayerSPInfo.curProgress == 2)
		levelName = "SingleprogressMap_Forest";
	UGameplayStatics::OpenLevel(this, FName(*levelName));
}

void ALoginGameModeBase::FadeToSPLevel()
{
	NotifyMusicFadeOut();
	GetWorldTimerManager().SetTimer(m_cameraFadeTimerHandle, this, &ALoginGameModeBase::FadeOutDone, m_cameraFadeTime, false);
	/*APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
	pLPC->PlayerCameraManager->StartCameraFade(1.f, 0.f, m_cameraFadeTime, FLinearColor::Black, false, true);*/
}

void ALoginGameModeBase::FadeOutDone()
{

	//先加载读取界面
	//申请异步加载DumpActors、PhysGeo
	if (!m_pCWSingleton->m_asyncLoadStateDone.Contains(1) || !m_pCWSingleton->m_asyncLoadStateDone.Contains(2))
	{
		m_pLPC->m_pLoadMenu = CreateWidget<UTTransitionMenu>(m_pLPC, m_pLPC->m_pWidgetManager->m_widgetClassMap["LoadMenu"]);
		m_pLPC->m_pLoadMenu->NotifyInitial();
		m_pLPC->m_pLoadMenu->m_pWidgetManager = m_pLPC->m_pWidgetManager;
		m_pLPC->m_pLoadMenu->AddToViewport();
		m_pCWSingleton->ReqAsynLoad(1);
		m_pCWSingleton->ReqAsynLoad(2);
		m_hasApplyAsyncLoad = true;
	}
	else
	{
		m_hasApplyAsyncLoad = true;
	}
}

void ALoginGameModeBase::ReadCharacterPrefixSkills_Implementation(const FString& characterName)
{

}

