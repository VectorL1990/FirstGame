// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplatePlayerDetail.h"




void UTemplatePlayerDetail::NotifyInitial_Implementation()
{

}

void UTemplatePlayerDetail::InitialTemplateDetail(UImage* pDarkBG, UTextBlock* pPlayerNameCaption, UTextBlock* pPlayerNameText, 
	UTextBlock* pTotalWinCaption, UTextBlock* pTotalWinNbText)
{
	m_pDarkBG = pDarkBG;
	m_pPlayerNameCaption = pPlayerNameCaption;
	m_pPlayerNameText = pPlayerNameText;
	m_pTotalWinCaption = pTotalWinCaption;
	m_pTotalWinNbText = pTotalWinNbText;
}
