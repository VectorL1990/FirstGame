// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/Battle/RoguelikeBattleGameMode.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "CanvasPanelSlot.h"
#include "../CollisionWarGameInstance.h"
#include "TemplateBattleElementSystem.h"




void UTemplateBattleElementSystem::NotifyInitial_Implementation()
{

}

void UTemplateBattleElementSystem::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "MissionMenu")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBGM = Cast<ABattleLevelGameModeBase>(pGM);
		m_pMissionMenu = CreateWidget<UDialogTextMenu>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_widgetClassMap["BattleMissionMenu"]);
		m_pMissionMenu->NotifyInitial();
		if (m_pWidgetManager->m_language == "Chinese")
			m_pMissionMenu->m_pDescription->SetText(FText::FromString(pBGM->m_pAIManager->m_battleInfo.chDescription));
		else
			m_pMissionMenu->m_pDescription->SetText(FText::FromString(pBGM->m_pAIManager->m_battleInfo.description));
		//m_pMissionMenu->m_domain = 2;
		m_pMissionMenu->AddToViewport();
		if (pBGM->m_isInTutorial)
		{
			if (pBGM->m_tutorialSteps.Num() > 0)
			{
				FString tutorialStepName = "ClickMissionMenu";
				if (pBGM->m_tutorialSteps[0].operationName == tutorialStepName)
					pBGM->DeleteTutorialStep();
			}
		}
	}
	else if (buttonFunction == "Button_SkillTree")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBPC = Cast<ABattleLevelPlayerController>(pPC);
		pBPC->LoadSkillTreeMenu();
	}
	else if (buttonFunction == "Button_PageUp")
	{
		SwitchFCMenuPhase(true);
	}
	else if (buttonFunction == "Button_PageDown")
	{
		SwitchFCMenuPhase(false);
	}
	else if (buttonFunction == "TutorialSerial")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBPC = Cast<ABattleLevelPlayerController>(pPC);
		pBPC->LoadTutorialSerialMenu();
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
		if (!pCWGI->m_doneTutorialSteps.Contains(pRGM->m_curTutorialName)) pCWGI->m_doneTutorialSteps.Add(pRGM->m_curTutorialName);
		pRGM->m_curTutorialName = "NULL";
		m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		if (!pBPC->m_isGamePaused) pBPC->PauseOrUnPauseGame();
	}
	/*else
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);
		pCWGM->ButtonClickCallback(buttonFunction);
	}*/
}

void UTemplateBattleElementSystem::DeleteSkillFromMenu(int32 cardNb)
{
	if (!m_pSkillBattleCardList[cardNb] || !m_pSkillBattleCardList[cardNb]->m_isShow) return;
	m_pSkillBattleCardList[cardNb]->HideCard();
}

void UTemplateBattleElementSystem::SwitchSkillCard(int32 cardNb, FString newCardName, FString supplementSkillName)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
	if (newCardName == "NULL")
	{
		UMaterialInstanceDynamic* pMI = m_pSkillBattleCardList[cardNb]->m_pSkillImage->GetDynamicMaterial();
		pMI->SetTextureParameterValue(FName(TEXT("Back")), m_pWidgetManager->m_pBattleSkillCardDefaultTex);
		m_pSkillBattleCardList[cardNb]->m_pCurTexture = m_pWidgetManager->m_pBattleSkillCardDefaultTex;

		m_pSkillBattleCardList[cardNb]->m_pCardName->SetText(FText::FromString(""));
		m_pSkillBattleCardList[cardNb]->m_isShow = false;
		m_pSkillBattleCardList[cardNb]->m_cardName = "NULL";

		m_pSkillBattleCardList[cardNb]->NotifySetUpdateTimer();
	}
	else
	{
		for (int32 i = 0; i < pBPC->m_playerSkillInfos.Num(); i++)
		{
			if (pBPC->m_playerSkillInfos[i].skillName != newCardName) continue;
			UMaterialInstanceDynamic* pMI = m_pSkillBattleCardList[cardNb]->m_pSkillImage->GetDynamicMaterial();
			pMI->SetTextureParameterValue(FName(TEXT("Back")), pBPC->m_playerSkillInfos[i].pTexture);
			m_pSkillBattleCardList[cardNb]->m_pCurTexture = pBPC->m_playerSkillInfos[i].pTexture;

			if (m_pWidgetManager->m_language == "Chinese")
				m_pSkillBattleCardList[cardNb]->m_pCardName->SetText(FText::FromString(pBPC->m_playerSkillInfos[i].chSkillName));
			else
				m_pSkillBattleCardList[cardNb]->m_pCardName->SetText(FText::FromString(pBPC->m_playerSkillInfos[i].skillName));
			m_pSkillBattleCardList[cardNb]->m_isShow = true;
			m_pSkillBattleCardList[cardNb]->m_cardName = pBPC->m_playerSkillInfos[i].skillName;

			m_pSkillBattleCardList[cardNb]->NotifySetUpdateTimer();

			break;
		}
	}
	
	//要诸位下移，先获得各卡牌位的新名字，然后执行下移动画
	/*TArray<FString> newPreBattleCardNameList;
	for (int32 i = 0; i < m_pPreSkillBattleCardList.Num(); i++)
	{
		if (i >= availableSkills.Num() - 1)
			newPreBattleCardNameList.Add("NULL");
		else
			newPreBattleCardNameList.Add(availableSkills[i + 1]);
	}*/
	SlidePreBattleCards(supplementSkillName);
}

void UTemplateBattleElementSystem::DeleteEquipFromMenu(int32 slotNb)
{
	if (!m_pEquipBattleCardList[slotNb] || !m_pEquipBattleCardList[slotNb]->m_isShow) return;
	m_pEquipBattleCardList[slotNb]->HideCard();
}

void UTemplateBattleElementSystem::SwitchSkillAndBuildDomain(bool switchToSkillDomain)
{
	if ((m_isInSkillDomain && switchToSkillDomain) || (!m_isInSkillDomain && !switchToSkillDomain)) return;
	else if (m_isInSkillDomain && !switchToSkillDomain)
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
		m_curTempSwitchDomainSkillCardNames.Empty();
		for (int32 i=0; i<m_pSkillBattleCardList.Num(); i++)
		{
			m_curTempSwitchDomainSkillCardNames.Add(m_pSkillBattleCardList[i]->m_cardName);
		}
		uint8 i = 0;
		for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = pBPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value.pTexture) continue;
			if (i >= m_pSkillBattleCardList.Num()) break;
			m_pSkillBattleCardList[i]->SwitchImage(iter->Value.pTexture, iter->Value.foundationCharacterName);
			m_pSkillBattleCardList[i]->m_cardName = iter->Key;
			m_pSkillBattleCardList[i]->ShowCard();
			i += 1;
		}
		for (int32 j=i; j< m_pSkillBattleCardList.Num(); j++)
		{
			m_pSkillBattleCardList[j]->HideCard();
		}
		m_isInSkillDomain = false;

		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
		if (!pCWGI->m_doneTutorialSteps.Contains(pRGM->m_fixTutorialSerialNames[1])) pRGM->RefreshTutorial(pRGM->m_fixTutorialSerialNames[1], true, 1);
		else pRGM->RefreshTutorial("NULL", false, 1);
	}
	else
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ARoguelikeBattleGameMode* pBLGM = Cast<ARoguelikeBattleGameMode>(pGM);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
		if (!pBLGM->m_pPlayerCharacter) return;
		int32 curSkillNb = 0;
		for (int32 i=0; i<m_curTempSwitchDomainSkillCardNames.Num(); i++)
		{
			if (m_curTempSwitchDomainSkillCardNames[i] == "NULL" || m_curTempSwitchDomainSkillCardNames[i] == "")
				m_pSkillBattleCardList[i]->HideCard();
			else
			{
				UTexture* pSkillTexture = NULL;
				for (int32 j = 0; j < pBPC->m_playerSkillInfos.Num(); j++)
				{
					if (pBPC->m_playerSkillInfos[j].skillName != m_curTempSwitchDomainSkillCardNames[i]) continue;
					pSkillTexture = pBPC->m_playerSkillInfos[j].pTexture;
					break;
				}
				if (!pSkillTexture) continue;
				m_pSkillBattleCardList[i]->SwitchImage(pSkillTexture, m_curTempSwitchDomainSkillCardNames[i]);
				m_pSkillBattleCardList[i]->m_cardName = m_curTempSwitchDomainSkillCardNames[i];
				m_pSkillBattleCardList[i]->ShowCard();
			}
		}
		m_isInSkillDomain = true;

		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (!pCWGI->m_doneTutorialSteps.Contains(pBLGM->m_fixTutorialSerialNames[0])) pBLGM->RefreshTutorial(pBLGM->m_fixTutorialSerialNames[0], true, 0);
		else pBLGM->RefreshTutorial("NULL", false, 0);
	}
}

void UTemplateBattleElementSystem::SwitchFCMenuPhase(bool upOrDownPage)
{
	if (m_isInSkillDomain) return;
	if (upOrDownPage)
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
		int32 totalCardNb = pBPC->m_FCInfos.Num();
		int32 firstCardNb = (m_curFCMenuPhase + 1)*m_pSkillBattleCardList.Num();
		if (firstCardNb >= totalCardNb) return;
		int32 i = 0;
		int32 curSkillCardNb = 0;
		for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = pBPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value.pTexture) continue;
			if (i < firstCardNb)
			{
				i += 1;
				continue;
			}
			if (i >= pBPC->m_FCInfos.Num() || curSkillCardNb >= m_pSkillBattleCardList.Num()) break;
			m_pSkillBattleCardList[curSkillCardNb]->SwitchImage(iter->Value.pTexture, iter->Value.foundationCharacterName);
			m_pSkillBattleCardList[curSkillCardNb]->m_cardName = iter->Key;
			m_pSkillBattleCardList[curSkillCardNb]->ShowCard();
			curSkillCardNb += 1;
			i += 1;
		}
		for (int32 j=curSkillCardNb; j< m_pSkillBattleCardList.Num(); j++)
		{
			m_pSkillBattleCardList[j]->HideCard();
		}
		m_curFCMenuPhase += 1;
	}
	else
	{
		if (m_curFCMenuPhase == 0) return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
		int32 firstCardNb = (m_curFCMenuPhase - 1)*m_pSkillBattleCardList.Num();
		int32 i = 0;
		int32 curSkillCardNb = 0;
		for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = pBPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value.pTexture) continue;
			if (i < firstCardNb)
			{
				i += 1;
				continue;
			}
			if (curSkillCardNb >= m_pSkillBattleCardList.Num()) break;
			m_pSkillBattleCardList[curSkillCardNb]->SwitchImage(iter->Value.pTexture, iter->Value.foundationCharacterName);
			m_pSkillBattleCardList[curSkillCardNb]->m_cardName = iter->Key;
			m_pSkillBattleCardList[curSkillCardNb]->ShowCard();
			curSkillCardNb += 1;
			i += 1;
		}
		m_curFCMenuPhase -= 1;
	}
}

void UTemplateBattleElementSystem::UpdateResourcesAmout(uint8 resourceID, int32 resourceNb)
{
	FString resourceNbString = FString::FromInt(resourceNb);
	if (resourceID == 1)
		m_pFirstResourceText->SetText(FText::FromString(resourceNbString));
	else if (resourceID == 2)
		m_pSecondResourceText->SetText(FText::FromString(resourceNbString));
	else if (resourceID == 3)
		m_pThirdResourceText->SetText(FText::FromString(resourceNbString));
	else if (resourceID == 4)
		m_pFourthResourceText->SetText(FText::FromString(resourceNbString));
	else if (resourceID == 5)
		m_pFifthResourceText->SetText(FText::FromString(resourceNbString));
}

void UTemplateBattleElementSystem::UpdateSkillCoolDownPercentage(uint8 skillNb, float coolDownPercent)
{
	if (skillNb <= 0 || ((int32)skillNb - 1) >= m_pSkillBattleCardList.Num() || !m_pSkillBattleCardList[((int32)skillNb - 1)]) return;
	m_pSkillBattleCardList[skillNb-1]->UpdateCoolDown(coolDownPercent);
}

void UTemplateBattleElementSystem::NotifyHurtLevelChange_Implementation(int32 lv1, int32 lv2, int32 lv3, int32 lv4, int32 lv5)
{

}

void UTemplateBattleElementSystem::SetEquipCard(uint8 cardNb, UTexture* pTexture, FString cardName)
{
	m_pEquipBattleCardList[cardNb]->SwitchImage(pTexture, cardName);
	m_pEquipBattleCardList[cardNb]->m_cardName = cardName;
	m_pEquipBattleCardList[cardNb]->ShowCard();
}

void UTemplateBattleElementSystem::UpdateCombineKeyList(const FString& combineKeyList)
{
	m_combineKeyStr = combineKeyList;
}

void UTemplateBattleElementSystem::UpdateCurFrameCount(int32 curFrame, int32 maxFrame, uint8 type)
{
	if (!m_pCurLeftTime || !m_pCurLeftTimeImage) return;
	int32 curSecond = curFrame / 25;
	int32 maxSecond = maxFrame / 25;
	UMaterialInstanceDynamic* pDMI = m_pCurLeftTimeImage->GetDynamicMaterial();
	if (type == 0)
	{
		float percent = (float)curSecond / (float)maxSecond;
		pDMI->SetScalarParameterValue(FName("Progress"), percent);
	}
	else pDMI->SetScalarParameterValue(FName("Progress"), 1);
	/*FString demoStr;
	if (m_pWidgetManager->m_language == "Chinese")
		demoStr = m_chCurLeftTimeTitleStr + FString::FromInt(curSecond) + "/" + FString::FromInt(maxSecond);
	else
		demoStr = m_curLeftTimeTitleStr + FString::FromInt(curSecond) + "/" + FString::FromInt(maxSecond);*/
	m_pCurLeftTime->SetText(FText::FromString(FString::FromInt(curSecond)));
}


void UTemplateBattleElementSystem::UpdateReloadTime(float dT)
{
	if (!m_shouldReload) return;
	float percent = m_curReloadTime / m_reloadTime;
	UMaterialInstanceDynamic* pMI = m_pReloadBar->GetDynamicMaterial();
	pMI->SetScalarParameterValue(FName(TEXT("Progress")), percent);
	m_pReloadLeftTime->SetText(FText::FromString(FString::SanitizeFloat(m_reloadTime - m_curReloadTime)));
	m_curReloadTime += dT;
	if (m_curReloadTime >= m_reloadTime) m_curReloadTime = m_reloadTime;
}

void UTemplateBattleElementSystem::StopReload()
{
	m_shouldReload = false;
	UMaterialInstanceDynamic* pMI = m_pReloadBar->GetDynamicMaterial();
	pMI->SetScalarParameterValue(FName(TEXT("Progress")), 0.f);
	m_pReloadLeftTime->SetText(FText::FromString("0"));
	m_curReloadTime = 0;
}

void UTemplateBattleElementSystem::SlidePreBattleCards(FString supplementSkill)
{
	/*if (supplementSkill != "NULL")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABasePlayerController* pBPC = Cast<ABasePlayerController>(pPC);
		UTBattleCard* pPreBattleSkillCard = CreateWidget<UTBattleCard>(pPC, m_preBattleSkillCardClass);
		pPreBattleSkillCard->NotifyInitial();
		UMaterialInstanceDynamic* pMI = pPreBattleSkillCard->m_pSkillImage->GetDynamicMaterial();
		for (int32 i = 0; i < pBPC->m_playerSkillInfos.Num(); i++)
		{
			if (pBPC->m_playerSkillInfos[i].skillName != supplementSkill) continue;
			pMI->SetTextureParameterValue(FName("ButtonTexture"), pBPC->m_playerSkillInfos[i].pTexture);
			pPreBattleSkillCard->m_cardName = supplementSkill;
			break;
		}
		UPanelSlot* pSlot = m_pCanvasPanel->AddChild(pPreBattleSkillCard);
		UCanvasPanelSlot* pCanvasPanelSlot = Cast<UCanvasPanelSlot>(pSlot);
		FAnchors anchor;
		anchor.Minimum.X = 0;
		anchor.Minimum.Y = 1;
		anchor.Maximum.X = 0;
		anchor.Maximum.Y = 1;
		pCanvasPanelSlot->SetAnchors(anchor);
		pCanvasPanelSlot->SetPosition(m_preBattleCardLocs.Last());
		m_pPreSkillBattleCardList.Add(pPreBattleSkillCard);
		pPreBattleSkillCard->NotifyPlaySlideAnimation(1);
		//pPreBattleSkillCard->m_curSlidePos = m_preBattleCardLocs.Num() - 1;
	}
	for (int32 i=0; i<m_pPreSkillBattleCardList.Num(); i++)
	{
		if (i == 0)
		{
			if (m_pPreSkillBattleCardList[i]->m_slideTimes == 0) m_pPreSkillBattleCardList[i]->NotifyPlaySlideAnimation(0);
			else if (m_pPreSkillBattleCardList[i]->m_slideTimes == 1) m_pPreSkillBattleCardList[i]->NotifyPlaySlideAnimation(5);
			else if (m_pPreSkillBattleCardList[i]->m_slideTimes == 2) m_pPreSkillBattleCardList[i]->NotifyPlaySlideAnimation(2);
		}
		else
		{
			if (i >= m_pPreSkillBattleCardList.Num() - 1 && supplementSkill != "NULL") break;
			if (m_pPreSkillBattleCardList[i]->m_slideTimes == 0) m_pPreSkillBattleCardList[i]->NotifyPlaySlideAnimation(4);
			else if (m_pPreSkillBattleCardList[i]->m_slideTimes == 1) m_pPreSkillBattleCardList[i]->NotifyPlaySlideAnimation(3);
			m_pPreSkillBattleCardList[i]->m_slideTimes += 1;
		}
	}*/
}

bool UTemplateBattleElementSystem::AddNNumericCardToPanel(FString cardName, int32 ID)
{
	if (!m_pNumericGridPanel || m_pNumericCards.Num() >= m_pAllNumericCards.Num()) return false;

	for (int32 i=0; i<m_pAllNumericCards.Num(); i++)
	{
		if (m_pAllNumericCards[i]->GetVisibility() == ESlateVisibility::Hidden)
		{
			m_pAllNumericCards[i]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			m_pAllNumericCards[i]->m_cardName = cardName;

			FString nbStr = cardName.RightChop(10);
			if (cardName.Contains("Numeric_D_")) m_pAllNumericCards[i]->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[0]);
			else if (cardName.Contains("Numeric_C_")) m_pAllNumericCards[i]->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[1]);
			else if (cardName.Contains("Numeric_H_")) m_pAllNumericCards[i]->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[2]);
			else if (cardName.Contains("Numeric_S_")) m_pAllNumericCards[i]->m_pColorImage->Brush.SetResourceObject(m_pWidgetManager->m_pColorTextureMap[3]);
			m_pAllNumericCards[i]->m_pNbText->SetText(FText::FromString(nbStr));
			m_pNumericCards.Add(ID, m_pAllNumericCards[i]);
			break;
		}
	}
	return true;
}

void UTemplateBattleElementSystem::InitialTitleTexts()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i=0; i<m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_chTitleTexts[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_enTitleTexts[i]));
		}
	}
}

void UTemplateBattleElementSystem::AskFadeOut_Implementation()
{

}

void UTemplateBattleElementSystem::NotifyShakeHitText_Implementation(int32 scoreLevel)
{

}

