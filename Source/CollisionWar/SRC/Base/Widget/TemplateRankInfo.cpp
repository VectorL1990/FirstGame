// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateRankInfo.h"




void UTemplateRankInfo::NotifyInitial_Implementation()
{

}

void UTemplateRankInfo::InitialTemplateRankInfo(USizeBox* pSizeBox, UVerticalBox* pSingleVBox, UTextBlock* pSingleRankBoxCaption, 
	UScrollBox* pSingleScrollBox, UVerticalBox* pOneOneVBox, UTextBlock* pOneOneRankBoxCaption, UScrollBox* pOneOneScrollBox, 
	UVerticalBox* pTwoTwoVBox, UTextBlock* pTwoTwoRankBoxCaption, UScrollBox* pTwoTwoScrollBox, UVerticalBox* pThreeThreeVBox, 
	UTextBlock* pThreeThreeRankBoxCaption, UScrollBox* pThreeThreeScrollBox)
{
	m_pSizeBox = pSizeBox;
	m_pSingleVBox = pSingleVBox;
	m_pSingleRankBoxCaption = pSingleRankBoxCaption;
	m_pSingleScrollBox = pSingleScrollBox;
	m_pOneOneVBox = pOneOneVBox;
	m_pOneOneRankBoxCaption = pOneOneRankBoxCaption;
	m_pOneOneScrollBox = pOneOneScrollBox;
	m_pTwoTwoVBox = pTwoTwoVBox;
	m_pTwoTwoRankBoxCaption = pTwoTwoRankBoxCaption;
	m_pTwoTwoScrollBox = pTwoTwoScrollBox;
	m_pThreeThreeVBox = pThreeThreeVBox;
	m_pThreeThreeRankBoxCaption = pThreeThreeRankBoxCaption;
	m_pThreeThreeScrollBox = pThreeThreeScrollBox;

	if (m_pSizeBox)
	{
		m_pSizeBox->SetMinDesiredHeight(m_lineHeight);
	}
}

void UTemplateRankInfo::RankInfoFadeOutDone()
{
	m_rankInfoFadeOutDelegate.Broadcast(m_mapType);
}

void UTemplateRankInfo::AskFadeOut_Implementation()
{

}
