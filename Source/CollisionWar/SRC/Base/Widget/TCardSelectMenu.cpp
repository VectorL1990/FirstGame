// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "CanvasPanelSlot.h"
#include "TCardSelectMenu.h"




void UTCardSelectMenu::NotifyInitial_Implementation()
{

}

void UTCardSelectMenu::ClickButton(FString buttonFunction)
{
	
}

void UTCardSelectMenu::StartSwitchDomain()
{
	m_curDomainNb += 1;
	for (int32 i = 0; i < m_pAllBonusCards.Num(); i++)
	{
		m_pAllBonusCards[i]->NotifyFadeOut();
	}
	NotifySetTimer();
}

void UTCardSelectMenu::SwitchDomain()
{
	while (m_pAllBonusCards.Num() > 0)
	{
		m_pAllBonusCards.Last()->RemoveFromParent();
		m_pAllBonusCards.Last()->ConditionalBeginDestroy();
		m_pAllBonusCards.Pop();
	}
	m_pCurSelectCard = NULL;
	AddActionCardToPanel(m_curDomainNb);
}

void UTCardSelectMenu::AddActionCardToPanel(uint8 domain)
{
	float halfCardNb = 0;
	if (domain == 0) halfCardNb = (float)(m_mustBonusCards.Num()) / 2.f;
	float firstSlotLocX = -(halfCardNb - 0.5)*m_cardInterval;

	if (m_pWidgetManager->m_language == "Chinese")
		m_pInstructionText->SetText(FText::FromString(m_chInstruction[domain]));
	else
		m_pInstructionText->SetText(FText::FromString(m_enInstruction[domain]));

	if (domain == 0)
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		for (int32 i = 0; i < m_mustBonusCards.Num(); i++)
		{
			UTActionCard* pActionCard = CreateWidget<UTActionCard>(pSPPC, m_pBonusCardClass);
			pActionCard->NotifyInitial();
			UMaterialInstanceDynamic* pDMI = pActionCard->m_pPlayCardImage->GetDynamicMaterial();
			if (pSPPC->m_pMustBonusCardTextureMap.Contains(m_mustBonusCards[i]))
			{
				pDMI->SetTextureParameterValue(FName("Front"), pSPPC->m_pMustBonusCardTextureMap[m_mustBonusCards[i]]);
				pActionCard->m_chDescription = pSPPC->m_mustBonusDescription[m_mustBonusCards[i]].chDescription;
				pActionCard->m_enDescription = pSPPC->m_mustBonusDescription[m_mustBonusCards[i]].enDescription;
			}
			pActionCard->m_cardName = "MustBonusCard_" + m_mustBonusCards[i];
			UPanelSlot* pSlot = m_pBonusCanvas->AddChild(pActionCard);
			UCanvasPanelSlot* pCanvasPanelSlot = Cast<UCanvasPanelSlot>(pSlot);
			pCanvasPanelSlot->SetSize(m_bonusCardSize);
			FAnchors anchor;
			anchor.Minimum.X = 0.5;
			anchor.Minimum.Y = 1;
			anchor.Maximum.X = 0.5;
			anchor.Maximum.Y = 1;
			pCanvasPanelSlot->SetAnchors(anchor);
			FVector2D alignment(0, 1);
			pCanvasPanelSlot->SetAlignment(alignment);
			FVector2D loc(firstSlotLocX + i * m_cardInterval, 0);
			pCanvasPanelSlot->SetPosition(loc);
			m_pAllBonusCards.Add(pActionCard);
		}
	}
}

void UTCardSelectMenu::InitialTitles()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i=0; i<m_pTitles.Num(); i++)
		{
			m_pTitles[i]->SetText(FText::FromString(m_chTitles[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_pTitles.Num(); i++)
		{
			m_pTitles[i]->SetText(FText::FromString(m_enTitles[i]));
		}
	}
}

void UTCardSelectMenu::NotifySetTimer_Implementation()
{

}

void UTCardSelectMenu::FadeOut_Implementation()
{

}
