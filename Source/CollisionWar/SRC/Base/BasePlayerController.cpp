// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "CollisionWarGameInstance.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "BasePlayerController.h"




void ABasePlayerController::MenuFadeOutDoneCallback_Implementation(const FString& menuName)
{

}

void ABasePlayerController::ButtonClickCallback_Implementation(const FString& buttonFunction)
{

}


void ABasePlayerController::ReadAllTextureInfo()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FString roleName = pCWGI->m_curPlayerSPInfo.characterName;
	if (roleName == "NULL" || roleName == "") roleName = "Lucian";
	ReadCharacterSkillTextureInfo(roleName);
	ReadCharacterStateTextureInfo();
	ReadGeneralTextureInfo();
	ReadItemCardInfo();
	ReadFCInfos();
	ReadCardTypeTextureMap();
	//ReadPhysGeoParticleTextureMap();
	ReadCardCombineInfo();
	//ReadPreAssignItemCardInfo();
}

void ABasePlayerController::ReadItemCardInfo_Implementation()
{

}

void ABasePlayerController::ReadPlayerCharacterSkills_Implementation(const FString& playerName)
{

}

void ABasePlayerController::WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo)
{
	m_playerSkillInfos.Add(skillInfo);
}

void ABasePlayerController::WriteFCInfo(bool isBattleMap, const FFoundationCharacterInfo& FCInfo)
{
	if (isBattleMap)
	{
		//如是战斗情况，只读取已解锁的合成公式，需要由SPPlayerInfo的信息确认
		if (FCInfo.isInitial) m_FCInfos.Add(FCInfo.foundationCharacterName, FCInfo);
		else
		{
			//再判定触发该合成公式的FC是否已解锁
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (!pCWGI->m_curPlayerSPInfo.availableFCList.Contains(FCInfo.foundationCharacterName) ||
				pCWGI->m_curPlayerSPInfo.availableFCList[FCInfo.foundationCharacterName] < FCInfo.unlockPoints) return;
			m_FCInfos.Add(FCInfo.foundationCharacterName, FCInfo);
		}
	}
	else
	{
		//如是非战斗情况，所有合成需要读入
		m_FCInfos.Add(FCInfo.foundationCharacterName, FCInfo);
	}
}

void ABasePlayerController::WriteCardCombineInfo(bool isBattleMap, const FCardCombineInfo& cardCombineInfo)
{
	if (isBattleMap)
	{
		//如是战斗情况，只读取已解锁的合成公式，需要由SPPlayerInfo的信息确认
		if (cardCombineInfo.isInitial) m_cardCombineInfo.Add(cardCombineInfo);
		else
		{
			//再判定触发该合成公式的FC是否已解锁
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (!m_FCInfos.Contains(cardCombineInfo.triggerFCName)) return;
			if (!pCWGI->m_curPlayerSPInfo.availableExtraCombineCards.Contains(cardCombineInfo.combineName)) return;
			m_cardCombineInfo.Add(cardCombineInfo);
		}
	}
	else
	{
		//如是非战斗情况，所有合成需要读入
		m_cardCombineInfo.Add(cardCombineInfo);
	}
}

UTTransitionMenu* ABasePlayerController::LoadTransitionMenu(FString menuName, TArray<float> transitionTimeSteps, uint8 type)
{
	if (!m_pWidgetManager || !m_pWidgetManager->m_widgetClassMap.Contains(menuName)) return NULL;
	m_curTransitionCountNb = 0;
	m_transitionCountTimeList = transitionTimeSteps;
	UTTransitionMenu* pMenu = CreateWidget<UTTransitionMenu>(this, m_pWidgetManager->m_widgetClassMap[menuName]);
	pMenu->NotifyInitial();
	pMenu->m_type = 1;
	GetWorldTimerManager().SetTimer(m_transitionTimerHandler, this, &ABasePlayerController::SwitchNextTransitionStep, m_transitionCountTimeList[m_curTransitionCountNb], false);
	return pMenu;
}

void ABasePlayerController::SwitchNextTransitionStep()
{
	NotifySwitchTransitionStepTimeUp();
	m_curTransitionCountNb += 1;
	if (m_curTransitionCountNb >= m_transitionCountTimeList.Num())
	{
		m_curTransitionMenuPhaseNb += 1;
		GetWorldTimerManager().ClearTimer(m_transitionTimerHandler);
	}
	else GetWorldTimerManager().SetTimer(m_transitionTimerHandler, this, &ABasePlayerController::SwitchNextTransitionStep, m_transitionCountTimeList[m_curTransitionCountNb], false);
}

void ABasePlayerController::NotifySwitchTransitionStepTimeUp_Implementation()
{

}

void ABasePlayerController::NotifySpawnMenuTutorIndicator_Implementation(const FString& operationName)
{

}

void ABasePlayerController::ReadCardCombineInfo_Implementation()
{

}

void ABasePlayerController::ReadCardTypeTextureMap_Implementation()
{

}

void ABasePlayerController::ReadFCInfos_Implementation()
{

}

void ABasePlayerController::ReadGeneralTextureInfo_Implementation()
{

}

void ABasePlayerController::ReadCharacterSkillTextureInfo_Implementation(const FString& roleName)
{

}

void ABasePlayerController::ReadCharacterStateTextureInfo_Implementation()
{

}