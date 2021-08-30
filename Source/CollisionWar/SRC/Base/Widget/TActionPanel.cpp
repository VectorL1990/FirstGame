// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "VerticalBoxSlot.h"
#include "TActionPanel.h"




void UTActionPanel::NotifyInitial_Implementation()
{

}

void UTActionPanel::UpdateActionPanelInfo(UEventNodeManager* pEventNodeManager)
{
	if (!pEventNodeManager) return;
	while (m_pChoiceButtons.Num() > 0)
	{
		m_pChoiceButtons.Last()->RemoveFromParent();
		if (m_pChoiceButtons.Last()->IsValidLowLevel())
			m_pChoiceButtons.Last()->ConditionalBeginDestroy();
		m_pChoiceButtons.Pop();
	}

	if (m_pWidgetManager->m_language == "Chinese")
		m_pDescriptionBox->SetText(FText::FromString(pEventNodeManager->m_curTreeNode.descriptionAndChoice.chDescriptions));
	else
		m_pDescriptionBox->SetText(FText::FromString(pEventNodeManager->m_curTreeNode.descriptionAndChoice.descriptions));
	if (pEventNodeManager->m_curTreeNode.descriptionAndChoice.choices.Num() > 0)
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		for (int32 i = 0; i < pEventNodeManager->m_curTreeNode.descriptionAndChoice.choices.Num(); i++)
		{
			UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pPC, m_pWidgetManager->m_widgetClassMap["ChoiceButton"]);
			pRuneElement->NotifyInitial();
			if (m_pWidgetManager->m_language == "Chinese")
				pRuneElement->m_pRuneName->SetText(FText::FromString(pEventNodeManager->m_curTreeNode.descriptionAndChoice.chChoiceStrs[i]));
			else
				pRuneElement->m_pRuneName->SetText(FText::FromString(pEventNodeManager->m_curTreeNode.descriptionAndChoice.choiceStrs[i]));
			pRuneElement->m_buttonFunction = "ChoiceButton_" + pEventNodeManager->m_curTreeNode.descriptionAndChoice.choices[i];
			m_pChoiceButtons.Add(pRuneElement);
			UPanelSlot* pSlot = m_pVBox->AddChild(pRuneElement);
			UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
			pVSlot->SetPadding(m_vboxMargin);
		}
	}
}


void UTActionPanel::ClickButton(const FString& buttonFunction)
{
	
}

void UTActionPanel::ShowActionWords(FString words)
{
	if (!m_pDescriptionBox)
	{
		return;
	}
	m_pDescriptionBox->SetText(FText::FromString(words));
}

void UTActionPanel::NotifyPlaySwitchContextAnim_Implementation()
{

}

