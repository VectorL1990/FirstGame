// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "TemplateInputText.h"




void UTemplateInputText::InitialTemplateInputText(UTextBlock* pCaption, USpacer* pSpacer, UEditableTextBox* pEditBox, USizeBox* pSizeBox)
{
	m_pCaption = pCaption;
	m_pSpacer = pSpacer;
	m_pEditBox = pEditBox;
	m_pSizeBox = pSizeBox;
	
}

void UTemplateInputText::InputTextCommit()
{
	m_commitTextDelegate.Broadcast(m_inputText, m_function);
}

void UTemplateInputText::NotifyIntial_Implementation()
{

}
