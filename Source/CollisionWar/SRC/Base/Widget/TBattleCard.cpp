// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "../../Game/Battle/RoguelikeBattleGameMode.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "CanvasPanelSlot.h"
#include "TBattleCard.h"




void UTBattleCard::NotifyInitial_Implementation()
{

}

void UTBattleCard::ShowCard()
{
	m_pFrameImage->SetVisibility(ESlateVisibility::Visible);
	m_pSkillImage->SetVisibility(ESlateVisibility::Visible);
	m_pCardName->SetVisibility(ESlateVisibility::Visible);
	m_isShow = true;
}

void UTBattleCard::HideCard()
{
	//m_pFrameImage->SetVisibility(ESlateVisibility::Hidden);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	m_pCardName->SetText(FText::FromString(""));
	UMaterialInstanceDynamic* pDMI = m_pSkillImage->GetDynamicMaterial();
	pDMI->SetTextureParameterValue(FName("Front"), pBLPC->m_pBattleMenu->m_pWidgetManager->m_pBattleSkillCardDefaultTex);
	//m_pSkillImage->Brush.SetResourceObject(pBLPC->m_pBattleMenu->m_pWidgetManager->m_pBattleSkillCardDefaultTex);
	m_isShow = false;
	m_pMask->SetPercent(0);
	m_cardName = "NULL";
}

void UTBattleCard::ClickButton()
{
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);
	pCWGM->ButtonClickCallback(m_buttonFunction);*/
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (pBLPC->m_isGamePaused) return;
	if (pBLPC->m_viewTargetState == 1)
	{
		int32 i = 0;
		FString FCName;
		for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = pBLPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key != m_cardName)
			{
				i += 1;
				continue;
			}
			FCName = iter->Value.foundationCharacterName;
			pBLPC->ChangeOperationSkillNbByClick(i, true);
			break;
		}
		if (!pBLPC->m_pBattleMenu || !pBLPC->m_FCInfos.Contains(FCName)) return;
		FString description;
		if (pBLPC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
			description = pBLPC->m_FCInfos[FCName].chDescription;
		else
			description = pBLPC->m_FCInfos[FCName].description;
		pBLPC->m_pBattleMenu->m_pSkillDescription->SetText(FText::FromString(description));
	}
	else if (pBLPC->m_viewTargetState == 0)
	{
		if (!pBLPC->m_pBattleMenu || !pBLPC->m_pBattleMenu->m_pSkillBattleCardList.Contains(this)) return;
		for (int32 i = 0; i < pBLPC->m_playerSkillInfos.Num(); i++)
		{
			if (pBLPC->m_playerSkillInfos[i].skillName != m_cardName) continue;
			if (pBLPC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pBLPC->m_pBattleMenu->m_pSkillDescription->SetText(FText::FromString(pBLPC->m_playerSkillInfos[i].chSkillDescription));
			else
				pBLPC->m_pBattleMenu->m_pSkillDescription->SetText(FText::FromString(pBLPC->m_playerSkillInfos[i].skillDescription));
			break;
		}
	}
}

void UTBattleCard::SwitchImage(UTexture* pSkillTexture, const FString& cardName)
{
	if (!m_pSkillImage || !pSkillTexture) return;
	UMaterialInstanceDynamic* pMI = m_pSkillImage->GetDynamicMaterial();
	pMI->SetTextureParameterValue(FName(TEXT("Front")), pSkillTexture);
	m_pCurTexture = pSkillTexture;
	m_pCardName->SetText(FText::FromString(cardName));
}

void UTBattleCard::UpdateCoolDown(float percentage)
{
	if (!m_pMask) return;
	float leftPercent = 1.f - percentage;
	m_pMask->SetPercent(leftPercent);
}

void UTBattleCard::CopyFromBattleCard(UTBattleCard* pSourceCard)
{
	m_pSkillImage->SetBrush(pSourceCard->m_pSkillImage->Brush);
	m_pCardName->SetText(FText::FromString(pSourceCard->m_cardName));
	m_cardName = pSourceCard->m_cardName;
}

void UTBattleCard::OnCardDrop(UUserWidget* pDropCard)
{

}

void UTBattleCard::NotifySetUpdateTimer_Implementation()
{

}

void UTBattleCard::UpdateTimer()
{
	if (m_curUpdateTime >= m_totalUpdateTime)
	{
		ClearFadeTimer();
		m_curUpdateTime = 0;
		UMaterialInstanceDynamic* pMI = m_pSkillImage->GetDynamicMaterial();
		pMI->SetTextureParameterValue(FName(TEXT("Front")), m_pCurTexture);
		pMI->SetScalarParameterValue(FName(TEXT("Amount")), m_updateRange.X);
		return;
	}
	else
	{
		float fadePercent = (float)m_curUpdateTime / (float)m_totalUpdateTime;
		float curUpdateNb = (m_updateRange.Y - m_updateRange.X)*fadePercent + m_updateRange.X;
		UMaterialInstanceDynamic* pMI = m_pSkillImage->GetDynamicMaterial();
		pMI->SetScalarParameterValue(FName(TEXT("Amount")), curUpdateNb);
		m_curUpdateTime += 1;
	}
}

void UTBattleCard::NotifyPlaySlideAnimation_Implementation(uint8 slideType)
{

}

void UTBattleCard::ClearFadeTimer_Implementation()
{

}
