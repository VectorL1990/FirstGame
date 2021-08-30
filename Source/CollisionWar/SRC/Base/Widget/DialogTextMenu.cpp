// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../../Game/BattleLevelGameModeBase.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "DialogTextMenu.h"




void UDialogTextMenu::NotifyInitial_Implementation()
{

}

void UDialogTextMenu::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "Close")
	{
		if (m_gameState == 0)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			pSPGM->m_isInTutorial = false;
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			pSPPC->m_isInTutorial = false;
			pSPGM->m_tutorialSteps.Empty();
			pSPGM->UpdateTutorialStep();
			if (pSPPC->m_pTutorialMenu)
				pSPPC->m_pTutorialMenu->NotifyFadeOut();

		}
		else if (m_gameState == 1)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
			pBLGM->m_isInTutorial = false;
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
			pBLPC->m_isInTutorial = false;
			pBLGM->m_tutorialSteps.Empty();
			//pBLGM->UpdateTutorialStep();
			if (pBLPC->m_pTutorialMenu)
				pBLPC->m_pTutorialMenu->NotifyFadeOut();
		}
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		pCWGI->m_curPlayerSPInfo.isInitial = false;
	}
	else if (buttonFunction == "NextTip")
	{
		if (m_gameState == 0)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			FString tutorialStepName = "NextTip";
			if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pSPGM->DeleteTutorialStep();
		}
		else if (m_gameState == 1)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
			FString tutorialStepName = "NextTip";
			if (pBLGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pBLGM->DeleteTutorialStep();
		}
	}
	else if (buttonFunction == "CancelBattleMissionMenu")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pMissionMenu) return;
		pBLPC->m_pBattleMenu->m_pMissionMenu->RemoveFromParent();
		if (pBLPC->m_pBattleMenu->m_pMissionMenu->IsValidLowLevel())
			pBLPC->m_pBattleMenu->m_pMissionMenu->ConditionalBeginDestroy();
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		pCWGI->m_curPlayerSPInfo.isInitial = false;
	}
}

void UDialogTextMenu::NotifyFadeOut_Implementation()
{

}
