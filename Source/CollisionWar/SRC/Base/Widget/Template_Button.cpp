// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Template_Button.h"




void UTemplate_Button::NotifyInitial_Implementation()
{

}

void UTemplate_Button::InitialButton(UButton* pButton, USizeBox* pSizeBox, USpacer* pLeftSpacer, USpacer* pRightSpacer, UTextBlock* pCaption, UImage* pBGImage)
{
	m_pButton = pButton;
	m_pSizeBox = pSizeBox;
	m_pLeftSpacer = pLeftSpacer;
	m_pRightSpacer = pRightSpacer;
	m_pCaption = pCaption;
	m_pBorderImage = pBGImage;
}

void UTemplate_Button::ClickButton()
{
	m_buttonClickDelegate.Broadcast(m_buttonFunction);
}
