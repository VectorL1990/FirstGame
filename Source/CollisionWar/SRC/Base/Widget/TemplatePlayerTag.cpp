// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplatePlayerTag.h"




void UTemplatePlayerTag::NotifyInitial_Implementation()
{

}

void UTemplatePlayerTag::InitialTemplatePlayerTag(UButton* pInvisibleButton, UImage* pHeadShot, UTextBlock* pPlayerName)
{
	m_pInvisibleButton = pInvisibleButton;
	m_pHeadShot = pHeadShot;
	m_pPlayerName = pPlayerName;
}

void UTemplatePlayerTag::PlayerTagClick()
{
	m_playerTagClickDelegate.Broadcast(m_buttonFunction);
}

void UTemplatePlayerTag::SetDeactive()
{
	if (!m_pInvisibleButton) return;
	m_pInvisibleButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(0, 0, 0, 0));
}

void UTemplatePlayerTag::SetActive()
{
	if (!m_pInvisibleButton) return;
	m_pInvisibleButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 0, 0, 1));
}
