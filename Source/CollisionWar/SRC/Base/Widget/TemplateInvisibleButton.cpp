// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateInvisibleButton.h"




void UTemplateInvisibleButton::NotifyInitial_Implementation()
{

}

void UTemplateInvisibleButton::InitialInvisibleButton(USpacer* pLeftSpacer, USpacer* pRightSpacer, UButton* pButton, UTextBlock* pTextBlock, USizeBox* pSizeBox)
{
	m_pLeftSpacer = pLeftSpacer;
	m_pRightSpacer = pRightSpacer;
	m_pButton = pButton;
	m_pButtonText = pTextBlock;
	m_pSizeBox = pSizeBox;
	if (m_pSizeBox)
	{
		m_pSizeBox->SetMinDesiredHeight(m_lineHeight);
	}
}

void UTemplateInvisibleButton::InvisibleButtonClick(FString function)
{
	m_buttonClickDelegate.Broadcast(function, m_buttonLocation);
}

void UTemplateInvisibleButton::SetActive()
{
	if (!m_pButton) return;
	m_pButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(0.8f, 0.1f, 0.1f, 0.5f));
	m_pButton->WidgetStyle.Hovered.TintColor = FSlateColor(FLinearColor(0.8f, 0.1f, 0.1f, 0.5f));
	m_pButton->WidgetStyle.Pressed.TintColor = FSlateColor(FLinearColor(0.8f, 0.1f, 0.1f, 0.5f));
}

void UTemplateInvisibleButton::SetDeactive()
{
	if (!m_pButton) return;
	m_pButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	m_pButton->WidgetStyle.Hovered.TintColor = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	m_pButton->WidgetStyle.Pressed.TintColor = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
}
