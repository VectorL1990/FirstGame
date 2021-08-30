// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TJudgeInfo.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "HorizontalBoxSlot.h"
#include "TemplateCharacterInfo.h"




void UTemplateCharacterInfo::NotifyInitial_Implementation()
{
	
}

void UTemplateCharacterInfo::UpdateEnergyBall(bool addOrSub, uint8 type)
{
	if (!addOrSub)
	{
		if (m_pEnergyBallList.Num() <= 0)
		{
			return;
		}
		m_pEnergyBallList.Last()->RemoveFromParent();
		if (m_pEnergyBallList.Last()->IsValidLowLevel())
			m_pEnergyBallList.Last()->ConditionalBeginDestroy();
		m_pEnergyBallList.Pop();
	}
	else
	{
		if (!m_energyBallClass) return;
		UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(UGameplayStatics::GetGameInstance(this), m_energyBallClass);
		pBall->NotifyInitial();
		pBall->SetEnergyBallTexture(type);
		m_pEnergyBallList.Add(pBall);
		if (m_pEnergyBallBox)
		{
			m_pEnergyBallBox->AddChild(pBall);
		}
	}
}

void UTemplateCharacterInfo::UpdateJudgeList(int32 judge)
{
	if (!m_pJudgeHBox) return;
	if (judge == -1)
	{
		m_pJudgeHBox->ClearChildren();
		return;
	}

	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pWidgetManager) return;
	TSubclassOf<class UTJudgeInfo> pClass = pBLPC->m_pBattleMenu->m_pWidgetManager->m_widgetClassMap["JudgeInfo"];
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(pBLPC->m_pBattleMenu->m_pWidgetManager);
	UTJudgeInfo* pJudgeInfo = CreateWidget<UTJudgeInfo>(pGI, pClass);
	pJudgeInfo->NotifyInitial();
	int32 color = (judge - 1) / 13;
	int32 nb = judge - color * 13;
	/*if (color == 0) nb = judge;
	else nb = judge - color * 13 + 1;*/
	if (!pBLPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap.Contains(color)) return;
	UTexture* pColorTexture = pBLPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap[color];
	pJudgeInfo->m_pColorImage->Brush.SetResourceObject(pColorTexture);
	FString nbStr = FString::FromInt(nb);
	pJudgeInfo->m_pJudgeNb->SetText(FText::FromString(nbStr));
	UPanelSlot* pSlot = m_pJudgeHBox->AddChild(pJudgeInfo);
	UHorizontalBoxSlot* pHSlot = Cast<UHorizontalBoxSlot>(pSlot);
	//pHSlot->Padding.Right = 10;
	pHSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Center;
	pHSlot->VerticalAlignment = EVerticalAlignment::VAlign_Center;
	pHSlot->Size.SizeRule = ESlateSizeRule::Fill;
/*
	pText->SetText(FText::FromString(colorStr.Append(nbStr)));
	/ *pImage->Brush.SetResourceObject(m_pSkillConnectLineMI);
	UPanelSlot* pPanelSlot = m_pCanvasPanel->AddChild(pImage);* /*/
}

void UTemplateCharacterInfo::InitialHpBar()
{
	if (!m_pHpBar) return;
	m_pHpBar->m_pProgressBar->SetPercent(1);
}

void UTemplateCharacterInfo::InitialEnergyBar(int32 energyBallNb)
{
	if (!m_energyBallClass) return;
	for (int32 i=0; i<energyBallNb; i++)
	{
		UTEnergyBall* pBall = CreateWidget<UTEnergyBall>(UGameplayStatics::GetGameInstance(this), m_energyBallClass);
		pBall->NotifyInitial();
		pBall->SetEnergyBallTexture(0);
		m_pEnergyBallList.Add(pBall);
		if (m_pEnergyBallBox)
		{
			m_pEnergyBallBox->AddChild(pBall);
		}
	}
}

void UTemplateCharacterInfo::NotifyHpChange(int32 hp, int32 curDFC)
{
	if (!m_pHpBar) return;
	m_curHp = hp;
	m_curDFC = curDFC;
	float hpPercent = (float)m_curHp / (float)m_maxHp;
	m_pHpBar->SetHp(hpPercent, hp, m_maxHp, curDFC, m_maxDFC);
}

void UTemplateCharacterInfo::NotifyAtkChange(int32 atkAddition)
{
	if (!m_pHpBar) return;
	if (atkAddition == 0)
		m_pHpBar->m_pATKText->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		m_pHpBar->m_pATKText->SetVisibility(ESlateVisibility::Visible);
		FString atkStr = FString::FromInt(atkAddition);
		m_pHpBar->m_pATKText->SetText(FText::FromString(atkStr));
	}
}

void UTemplateCharacterInfo::ChangeMaxHpAndDFC(int32 maxHp, int32 maxDFC)
{
	m_maxHp = maxHp;
	m_maxDFC = maxDFC;
	m_pHpBar->SetHp(1, maxHp, maxHp, maxDFC, maxDFC);
}

