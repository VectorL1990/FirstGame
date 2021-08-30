// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateScrollBox.h"




void UTemplateScrollBox::NotifyInitial_Implementation()
{

}

void UTemplateScrollBox::InitialTemplateScrollBox(UScrollBox* pScrollBox, USizeBox* pSizeBox)
{
	m_pSizeBox = pSizeBox;
	m_pScrollBox = pScrollBox;
	if (m_pSizeBox)
	{
		m_pSizeBox->SetMinDesiredHeight(m_lineHeight);
	}
}

void UTemplateScrollBox::ScrollBoxFadeOutDone()
{
	m_scrollBoxFadeOutDoneDelegate.Broadcast(m_scrollBoxCaption);
}

void UTemplateScrollBox::NotifyFadeIn_Implementation()
{

}

void UTemplateScrollBox::NotifyFadeOut_Implementation()
{

}
