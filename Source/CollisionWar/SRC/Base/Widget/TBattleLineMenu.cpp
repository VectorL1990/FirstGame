// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "WidgetTree.h"
#include "HorizontalBoxSlot.h"
#include "CanvasPanelSlot.h"
#include "TBattleLineMenu.h"




void UTBattleLineMenu::NotifyInitial_Implementation()
{

}

void UTBattleLineMenu::FadeOut_Implementation()
{

}

void UTBattleLineMenu::MenuFadeInDoneCallaback(FString menuName)
{
	
}

void UTBattleLineMenu::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "Ensure")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pSPGM->m_diceAndTheorizeCanAction) return;
		if (pSPGM->m_diceBattleInfo.maxFlipTime > 0)
		{
			pSPGM->m_diceBattleStage = 4;
			pSPGM->m_diceBattleInfo.maxFlipTime -= 1;
			pSPGM->m_curDiceTotalCount = 0.f;
			UpdateTime(pSPGM->m_diceBattleInfo.maxAvailableTimePerRound);
			UpdateResetTimes(pSPGM->m_diceBattleInfo.maxFlipTime);
			for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = pSPGM->m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
			{
				DeleteDiceSkillImage(iter->Key);
			}
			pSPGM->m_curAppendDiceSkillInfos.Empty();
		}
		else return;
	}
	else if (buttonFunction == "TutorialSerial")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->LoadTutorialSerialMenu();
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_curTutorialName)) pCWGI->m_doneTutorialSteps.Add(pSPGM->m_curTutorialName);
		pSPGM->m_curTutorialName = "NULL";
		m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
		pSPGM->m_isInDiceTutorialState = true;
	}
}

void UTBattleLineMenu::LoadAvailableSkills()
{
	if (!m_pDiceSkillCardClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	float halfCardNb = (float)(pSPPC->m_curDiceSkills.Num()) / 2.f;
	float firstSlotLocX = -(halfCardNb - 0.5)*m_skillCardInterval;
	for (int32 i=0; i<pSPPC->m_curDiceSkills.Num(); i++)
	{
		UTActionCard* pSkillCard = CreateWidget<UTActionCard>(pSPPC, m_pDiceSkillCardClass);
		pSkillCard->NotifyInitial();
		UMaterialInstanceDynamic* pDMI = pSkillCard->m_pPlayCardImage->GetDynamicMaterial();
		if (pSPPC->m_allDiceBattleSkillInfos.Contains(pSPPC->m_curDiceSkills[i]))
		{
			pDMI->SetTextureParameterValue(FName("Front"), pSPPC->m_allDiceBattleSkillInfos[pSPPC->m_curDiceSkills[i]].pTexture);
			pSkillCard->m_chDescription = pSPPC->m_allDiceBattleSkillInfos[pSPPC->m_curDiceSkills[i]].chSkillDescription;
			pSkillCard->m_enDescription = pSPPC->m_allDiceBattleSkillInfos[pSPPC->m_curDiceSkills[i]].skillDescription;
		}
		pSkillCard->m_cardName = "DiceSkillCard_" + pSPPC->m_curDiceSkills[i];
		UPanelSlot* pSlot = m_pSkillCanvasPanel->AddChild(pSkillCard);
		UCanvasPanelSlot* pCanvasPanelSlot = Cast<UCanvasPanelSlot>(pSlot);
		pCanvasPanelSlot->SetSize(m_skillCardSize);
		FAnchors anchor;
		anchor.Minimum.X = 0.5;
		anchor.Minimum.Y = 1;
		anchor.Maximum.X = 0.5;
		anchor.Maximum.Y = 1;
		pCanvasPanelSlot->SetAnchors(anchor);
		FVector2D alignment(0.5, 1);
		pCanvasPanelSlot->SetAlignment(alignment);
		FVector2D loc(firstSlotLocX + i*m_skillCardInterval, 0);
		pCanvasPanelSlot->SetPosition(loc);
	}
}

void UTBattleLineMenu::SetupTextBlockStrs()
{
	if (!m_pWidgetManager) return;
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i = 0; i < m_chMenuStrs.Num(); i++)
		{
			m_pTextBlocks[i]->SetText(FText::FromString(m_chMenuStrs[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_menuStrs.Num(); i++)
		{
			m_pTextBlocks[i]->SetText(FText::FromString(m_menuStrs[i]));
		}
	}
}

void UTBattleLineMenu::InitialMenuParam(int32 targetScore, int32 time)
{
	m_targetScore = targetScore;
	m_pTargetScoreNb->SetText(FText::FromString(FString::FromInt(targetScore)));
	//m_pTotalTimeText->SetText(FText::FromString(FString::FromInt(time)));
	m_pCurTimeText->SetText(FText::FromString(FString::FromInt(time)));
	UMaterialInstanceDynamic* pDMI = m_pTimeCountImage->GetDynamicMaterial();
	pDMI->SetScalarParameterValue(FName("Progress"), 1);
}

void UTBattleLineMenu::UpdateTime(float time)
{
	m_pCurTimeText->SetText(FText::FromString(FString::FromInt((int32)time)));
	UMaterialInstanceDynamic* pDMI = m_pTimeCountImage->GetDynamicMaterial();
	float percent = time / m_maxTime;
	pDMI->SetScalarParameterValue(FName("Progress"), percent);
}

void UTBattleLineMenu::UpdateLifeText(int32 life)
{
	if (life > m_pLifeBalls.Num())
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		int32 dif = life - m_pLifeBalls.Num();
		for (int32 i=0; i<dif; i++)
		{
			UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(pPC, m_pLifeBallClass);
			pBall->NotifyInitial();
			UPanelSlot* pSlot = m_pLifeCanvasPanel->AddChild(pBall);
			UCanvasPanelSlot* pCPSlot = Cast<UCanvasPanelSlot>(pSlot);
			pCPSlot->SetSize(m_lifeBallDefaultSize);
			FAnchors anchor;
			anchor.Maximum = FVector2D(1, 0.5);
			anchor.Minimum = FVector2D(1, 0.5);
			pCPSlot->SetAnchors(anchor);
			FVector2D alignment;
			alignment.X = 1;
			alignment.Y = 0.5;
			pCPSlot->SetAlignment(alignment);
			float slotX = -m_lifeBallInterval * m_pLifeBalls.Num();
			pCPSlot->SetPosition(FVector2D(slotX, 0));
			m_pLifeBalls.Add(pBall);
		}
	}
	else
	{
		int32 dif = m_pLifeBalls.Num() - life;
		for (int32 i=0; i<dif; i++)
		{
			m_pLifeBalls.Last()->RemoveFromParent();
			if (m_pLifeBalls.Last()->IsValidLowLevel())
				m_pLifeBalls.Last()->ConditionalBeginDestroy();
			m_pLifeBalls.Pop();
		}
		NotifyShowDemoImage(1);
	}
	//m_pCurLifeNb->SetText(FText::FromString(FString::FromInt(life)));
}

void UTBattleLineMenu::UpdateScoreText(int32 score)
{
	m_pCurScoreNb->SetText(FText::FromString(FString::FromInt(score)));
	float percent = (float)score / (float)m_targetScore;
	UMaterialInstanceDynamic* pDMI = m_pScoreImage->GetDynamicMaterial();
	pDMI->SetScalarParameterValue(FName("Progress"), percent);
	NotifyShowDemoImage(0);
}

void UTBattleLineMenu::NotifyShowDemoImage_Implementation(uint8 type)
{

}

void UTBattleLineMenu::UpdateResetTimes(int32 times)
{
	if (times > m_pResetBalls.Num())
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		int32 dif = times - m_pResetBalls.Num();
		for (int32 i = 0; i < dif; i++)
		{
			UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(pPC, m_pResetBallClass);
			pBall->NotifyInitial();
			UPanelSlot* pSlot = m_pResetCanvasPanel->AddChild(pBall);
			UCanvasPanelSlot* pCPSlot = Cast<UCanvasPanelSlot>(pSlot);
			pCPSlot->SetSize(m_resetBallDefaultSize);
			FAnchors anchor;
			anchor.Maximum = FVector2D(1, 0.5);
			anchor.Minimum = FVector2D(1, 0.5);
			pCPSlot->SetAnchors(anchor);
			FVector2D alignment;
			alignment.X = 1;
			alignment.Y = 0.5;
			pCPSlot->SetAlignment(alignment);
			float slotX = -m_resetBallInterval * m_pResetBalls.Num();
			pCPSlot->SetPosition(FVector2D(slotX, 0));
			m_pResetBalls.Add(pBall);
		}
	}
	else
	{
		int32 dif = m_pResetBalls.Num() - times;
		for (int32 i = 0; i < dif; i++)
		{
			m_pResetBalls.Last()->RemoveFromParent();
			if (m_pResetBalls.Last()->IsValidLowLevel())
				m_pResetBalls.Last()->ConditionalBeginDestroy();
			m_pResetBalls.Pop();
		}
	}
	//m_pCurResetNb->SetText(FText::FromString(FString::FromInt(times)));
}

void UTBattleLineMenu::AddDiceSkillImage(FString diceSkillName, int32 skillNb)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	for (TMap<UTemplateRuneElement*, int32>::TConstIterator iter = m_pAllDiceSkillDemoCards.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Key->GetVisibility() == ESlateVisibility::Hidden)
		{
			iter->Key->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			UMaterialInstanceDynamic* pDMI = iter->Key->m_pRuneImage->GetDynamicMaterial();
			pDMI->SetTextureParameterValue(FName("ButtonTexture"), pSPPC->m_allDiceBattleSkillInfos[diceSkillName].pTexture);
			m_pAllDiceSkillDemoCards[iter->Key] = skillNb;
			break;
		}
	}
}

void UTBattleLineMenu::DeleteDiceSkillImage(int32 diceSkillNb)
{
	for (TMap<UTemplateRuneElement*, int32>::TConstIterator iter = m_pAllDiceSkillDemoCards.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value == diceSkillNb)
		{
			m_pAllDiceSkillDemoCards[iter->Key] = -1;
			iter->Key->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTBattleLineMenu::NotifyDemonstrateText_Implementation(uint8 demoWordNb)
{

}
