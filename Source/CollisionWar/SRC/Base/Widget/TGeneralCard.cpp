// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../CollisionWarGameInstance.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "TGeneralCard.h"




void UTGeneralCard::NotifyInitial_Implementation()
{

}

void UTGeneralCard::ClickButton()
{

}

void UTGeneralCard::ClearCard()
{
	m_pSkillImage->Brush.SetResourceObject(m_pDefaultSkillTexture);
	m_cardName = "";
	m_chCardName = "";
	m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
	m_pNumericNb->SetVisibility(ESlateVisibility::Hidden);
	m_pCardNameTextBox->SetText(FText::FromString(""));
}

void UTGeneralCard::AssignGeneralCardInfo(FString cardName)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (!pBLPC->m_itemCardInfoMap.Contains(cardName)) return;
	m_cardName = cardName;
	FString basicCardName = cardName;
	if (cardName.Contains("Numeric_")) basicCardName = "NumericCard";
	m_chCardName = pBLPC->m_itemCardInfoMap[basicCardName].chCardName;
	m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
	m_pNumericNb->SetVisibility(ESlateVisibility::Hidden);
	m_pCardNameTextBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	m_pSkillImage->SetVisibility(ESlateVisibility::Visible);
	m_pSkillImage->Brush.SetResourceObject(pBLPC->m_itemCardInfoMap[basicCardName].pTexture);
	if (pCWGI->m_language == "Chinese")
		m_pCardNameTextBox->SetText(FText::FromString(pBLPC->m_itemCardInfoMap[basicCardName].chCardName));
	else
		m_pCardNameTextBox->SetText(FText::FromString(pBLPC->m_itemCardInfoMap[basicCardName].cardName));
}
