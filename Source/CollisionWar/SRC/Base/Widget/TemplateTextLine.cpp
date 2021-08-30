// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateTextLine.h"




void UTemplateTextLine::NotifyInitial_Implementation()
{

}

void UTemplateTextLine::InitialTemplateTextLine(USizeBox* pSizeBox, USpacer* pLeftSpacer, USpacer* pRightSpacer, UTextBlock* pText)
{
	m_pSizeBox = pSizeBox;
	m_pLeftSpacer = pLeftSpacer;
	m_pRightSpacer = pRightSpacer;
	m_pTextBlock = pText;
	if (m_pSizeBox)
	{
		m_pSizeBox->SetMinDesiredHeight(m_lineHeight);
	}
}
