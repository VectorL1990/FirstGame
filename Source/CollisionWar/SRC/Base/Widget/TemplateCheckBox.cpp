// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "TemplateCheckBox.h"




void UTemplateCheckBox::NotifyInitial_Implementation()
{

}

void UTemplateCheckBox::InitialTemplateCheckBox(USizeBox* pSizeBox, UTextBlock* pCaption, USpacer* pSpacer, UCheckBox* pCheckBox)
{
	m_pSizeBox = pSizeBox;
	m_pCaption = pCaption;
	m_pSpacer = pSpacer;
	m_pCheckBox = pCheckBox;
}

void UTemplateCheckBox::CheckBoxClick()
{
	if (m_isCheck) m_isCheck = false;
	else m_isCheck = true;
	m_checkBoxDelegate.Broadcast(m_function, m_isCheck);
}
