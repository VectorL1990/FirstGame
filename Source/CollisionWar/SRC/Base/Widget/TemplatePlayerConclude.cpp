// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplatePlayerConclude.h"




void UTemplatePlayerConclude::NotifyInitial_Implementation()
{

}

void UTemplatePlayerConclude::InitialTemplatePlayerConclude(USizeBox* pSizeBox, UTextBlock* pPlayerName, UTextBlock* pCaption1, 
	UTextBlock* pContent1, UTextBlock* pCaption2, UTextBlock* pContent2, UTextBlock* pCaption3, UTextBlock* pContent3, 
	UTextBlock* pCaption4, UTextBlock* pContent4)
{
	m_pSizeBox = pSizeBox;
	m_pPlayerNameText = pPlayerName;
	m_pCaption1 = pCaption1;
	m_pCaption2 = pCaption2;
	m_pCaption3 = pCaption3;
	m_pCaption4 = pCaption4;
	m_pContent1 = pContent1;
	m_pContent2 = pContent2;
	m_pContent3 = pContent3;
	m_pContent4 = pContent4;
	if (m_pSizeBox)
	{
		m_pSizeBox->SetMinDesiredHeight(m_lineHeight);
	}
}
