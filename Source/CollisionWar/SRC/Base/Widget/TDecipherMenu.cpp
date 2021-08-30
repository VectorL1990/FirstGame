// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "UniformGridSlot.h"
#include "CanvasPanelSlot.h"
#include "TDecipherMenu.h"




void UTDecipherMenu::NotifyInitial_Implementation()
{

}

void UTDecipherMenu::FadeOut_Implementation()
{

}

void UTDecipherMenu::MenuFadeInDoneCallaback(FString menuName)
{
	
}

void UTDecipherMenu::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "SwitchCards")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pSPGM->m_diceAndTheorizeCanAction) return;
		if (pSPGM->m_theorizePlayerInfo.availableFlipTimes > 0)
		{
			pSPGM->m_theorizeState = 4;
			pSPGM->m_theorizePlayerInfo.availableFlipTimes -= 1;
			for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = pSPGM->m_curAppendTheorizeSkillInfos.CreateConstIterator(); iter; ++iter)
			{
				DeleteTheorizeSkillImage(iter->Key);
			}
			pSPGM->m_curAppendTheorizeSkillInfos.Empty();

		}
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
		pSPGM->m_isInTheorizeTutorialState = true;
	}
}

void UTDecipherMenu::NotifyDemonstrateString_Implementation(uint8 textNb)
{

}

void UTDecipherMenu::InitialDecipherMenu()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	int32 curCol = 0;
	int32 curRow = 0;
	for (int32 i=0; i<2; i++)
	{
		for (int32 j=1; j<pSPGM->m_maxCardNb + 1; j++)
		{
			UTActionCard* pNumberCard = CreateWidget<UTActionCard>(pPC, m_numberCardClass);
			pNumberCard->NotifyInitial();
			if (i == 0)
				pNumberCard->InitialActionCard(j, 2, "NULL", NULL);
			else
				pNumberCard->InitialActionCard(j, 3, "NULL", NULL);
			UPanelSlot* pPanelSlot = m_pNumberCardGridPanel->AddChild(pNumberCard);
			UUniformGridSlot* pUniformGridSlot = Cast<UUniformGridSlot>(pPanelSlot);
			if (curCol >= m_columnPerRow)
			{
				curCol = 0;
				curRow += 1;
			}
			pUniformGridSlot->SetColumn(curCol);
			pUniformGridSlot->SetRow(curRow);
			m_pNumberCardList.Add(pNumberCard);
			curCol += 1;
		}
	}
	m_targetScore = pSPGM->m_targetScore;
	m_pTargetScoreText->SetText(FText::FromString(FString::FromInt(pSPGM->m_targetScore)));
	m_pCurScoreText->SetText(FText::FromString(FString::FromInt(0)));
	UMaterialInstanceDynamic* pDMI = m_pScoreImage->GetDynamicMaterial();
	pDMI->SetScalarParameterValue(FName("Progress"), 0);

	for (int32 i = 0; i < pSPGM->m_theorizePlayerInfo.compareTimes; i++)
	{
		UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(pPC, m_pCompareBallClass);
		pBall->NotifyInitial();
		UPanelSlot* pSlot = m_pCompareCanvasPanel->AddChild(pBall);
		UCanvasPanelSlot* pCPSlot = Cast<UCanvasPanelSlot>(pSlot);
		pCPSlot->SetSize(m_compareBallDefaultSize);
		FAnchors anchor;
		anchor.Maximum = FVector2D(1, 0.5);
		anchor.Minimum = FVector2D(1, 0.5);
		pCPSlot->SetAnchors(anchor);
		FVector2D alignment;
		alignment.X = 1;
		alignment.Y = 0.5;
		pCPSlot->SetAlignment(alignment);
		float slotX = -m_resetBallInterval * m_pCompareBalls.Num();
		pCPSlot->SetPosition(FVector2D(slotX, 0));
		m_pCompareBalls.Add(pBall);
	}
	for (int32 i = 0; i < pSPGM->m_theorizePlayerInfo.life; i++)
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
	for (int32 i = 0; i < pSPGM->m_theorizePlayerInfo.availableFlipTimes; i++)
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

void UTDecipherMenu::UpdateAllParam()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_pCurScoreText->SetText(FText::FromString(FString::FromInt(pSPGM->m_theorizePlayerInfo.curScore)));
	float percent = (float)pSPGM->m_theorizePlayerInfo.curScore / (float)m_targetScore;
	UMaterialInstanceDynamic* pDMI = m_pScoreImage->GetDynamicMaterial();
	pDMI->SetScalarParameterValue(FName("Progress"), percent);

	if (pSPGM->m_theorizePlayerInfo.compareTimes > m_pCompareBalls.Num())
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		int32 dif = pSPGM->m_theorizePlayerInfo.compareTimes - m_pCompareBalls.Num();
		for (int32 i = 0; i < dif; i++)
		{
			UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(pPC, m_pCompareBallClass);
			pBall->NotifyInitial();
			UPanelSlot* pSlot = m_pCompareCanvasPanel->AddChild(pBall);
			UCanvasPanelSlot* pCPSlot = Cast<UCanvasPanelSlot>(pSlot);
			pCPSlot->SetSize(m_compareBallDefaultSize);
			FAnchors anchor;
			anchor.Maximum = FVector2D(1, 0.5);
			anchor.Minimum = FVector2D(1, 0.5);
			pCPSlot->SetAnchors(anchor);
			FVector2D alignment;
			alignment.X = 1;
			alignment.Y = 0.5;
			pCPSlot->SetAlignment(alignment);
			float slotX = -m_resetBallInterval * m_pCompareBalls.Num();
			pCPSlot->SetPosition(FVector2D(slotX, 0));
			m_pCompareBalls.Add(pBall);
		}
	}
	else
	{
		int32 dif = m_pCompareBalls.Num() - pSPGM->m_theorizePlayerInfo.compareTimes;
		for (int32 i = 0; i < dif; i++)
		{
			m_pCompareBalls.Last()->RemoveFromParent();
			if (m_pCompareBalls.Last()->IsValidLowLevel())
				m_pCompareBalls.Last()->ConditionalBeginDestroy();
			m_pCompareBalls.Pop();
		}
	}

	if (pSPGM->m_theorizePlayerInfo.life > m_pLifeBalls.Num())
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		int32 dif = pSPGM->m_theorizePlayerInfo.life - m_pLifeBalls.Num();
		for (int32 i = 0; i < dif; i++)
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
		int32 dif = m_pLifeBalls.Num() - pSPGM->m_theorizePlayerInfo.life;
		for (int32 i = 0; i < dif; i++)
		{
			m_pLifeBalls.Last()->RemoveFromParent();
			if (m_pLifeBalls.Last()->IsValidLowLevel())
				m_pLifeBalls.Last()->ConditionalBeginDestroy();
			m_pLifeBalls.Pop();
		}
		NotifyShowDemoImage(1);
	}

	if (pSPGM->m_theorizePlayerInfo.availableFlipTimes > m_pResetBalls.Num())
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		int32 dif = pSPGM->m_theorizePlayerInfo.availableFlipTimes - m_pResetBalls.Num();
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
		int32 dif = m_pResetBalls.Num() - pSPGM->m_theorizePlayerInfo.availableFlipTimes;
		for (int32 i = 0; i < dif; i++)
		{
			m_pResetBalls.Last()->RemoveFromParent();
			if (m_pResetBalls.Last()->IsValidLowLevel())
				m_pResetBalls.Last()->ConditionalBeginDestroy();
			m_pResetBalls.Pop();
		}
	}
}

void UTDecipherMenu::NotifyShowDemoImage_Implementation(uint8 type)
{

}

void UTDecipherMenu::LoadTheorizeSkills()
{
	if (!m_pTheorizeSkillCardClass) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	float halfCardNb = (float)(pSPPC->m_curTheorizeSkills.Num()) / 2.f;
	float firstSlotLocX = -(halfCardNb - 0.5)*m_skillCardInterval;
	//int32 startIdx = pSPPC->m_curTheorizeSkills.Num() / 2;
	for (int32 i = 0; i < pSPPC->m_curTheorizeSkills.Num(); i++)
	{
		UTActionCard* pSkillCard = CreateWidget<UTActionCard>(pSPPC, m_pTheorizeSkillCardClass);
		pSkillCard->NotifyInitial();
		UMaterialInstanceDynamic* pDMI = pSkillCard->m_pPlayCardImage->GetDynamicMaterial();
		if (pSPPC->m_alltheorizeSkillInfos.Contains(pSPPC->m_curTheorizeSkills[i]))
		{
			pDMI->SetTextureParameterValue(FName("Front"), pSPPC->m_alltheorizeSkillInfos[pSPPC->m_curTheorizeSkills[i]].pTexture);
			pSkillCard->m_chDescription = pSPPC->m_alltheorizeSkillInfos[pSPPC->m_curTheorizeSkills[i]].chSkillDescription;
			pSkillCard->m_enDescription = pSPPC->m_alltheorizeSkillInfos[pSPPC->m_curTheorizeSkills[i]].skillDescription;
		}
		pSkillCard->m_cardName = "TheorizeSkillCard_" + pSPPC->m_curTheorizeSkills[i];
		UPanelSlot* pSlot = m_pSkillCanvasPanel->AddChild(pSkillCard);
		UCanvasPanelSlot* pCanvasPanelSlot = Cast<UCanvasPanelSlot>(pSlot);
		pCanvasPanelSlot->SetSize(m_skillCardSize);
		FVector2D alignment;
		alignment.X = 0.5;
		alignment.Y = 1;
		pCanvasPanelSlot->SetAlignment(alignment);
		FAnchors anchor;
		anchor.Maximum = FVector2D(0.5, 1);
		anchor.Minimum = FVector2D(0.5, 1);
		pCanvasPanelSlot->SetAnchors(anchor);
		FVector2D loc;
		loc.X = firstSlotLocX + i * m_skillCardInterval;
		loc.Y = 0;
		pCanvasPanelSlot->SetPosition(loc);
	}
}

void UTDecipherMenu::SetupTextBlockStrs()
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

void UTDecipherMenu::AddTheorizeSkillImage(FString theorizeSkillName, int32 skillNb)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	for (TMap<UTemplateRuneElement*, int32>::TConstIterator iter = m_pAllTheorizeSkillDemoCards.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Key->GetVisibility() == ESlateVisibility::Hidden)
		{
			iter->Key->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			UMaterialInstanceDynamic* pDMI = iter->Key->m_pRuneImage->GetDynamicMaterial();
			pDMI->SetTextureParameterValue(FName("ButtonTexture"), pSPPC->m_alltheorizeSkillInfos[theorizeSkillName].pTexture);
			m_pAllTheorizeSkillDemoCards[iter->Key] = skillNb;
			break;
		}
	}
}

void UTDecipherMenu::DeleteTheorizeSkillImage(int32 skillNb)
{
	for (TMap<UTemplateRuneElement*, int32>::TConstIterator iter = m_pAllTheorizeSkillDemoCards.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value == skillNb)
		{
			m_pAllTheorizeSkillDemoCards[iter->Key] = -1;
			iter->Key->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
