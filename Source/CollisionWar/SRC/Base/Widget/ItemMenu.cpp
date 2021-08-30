// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "ItemMenu.h"




void UItemMenu::NotifyInitial_Implementation()
{

}

void UItemMenu::InitialItemMenu(USizeBox* pContentSizeBox, UGridPanel* pGridPanel, UButton* pResumeButton)
{
	m_pContentSizeBox = pContentSizeBox;
	m_pGridPanel = pGridPanel;
	m_pResumeButton = pResumeButton;
}

void UItemMenu::ClickResumeButton(FString buttonName)
{
	m_resumeButtonClickDelegate.Broadcast(buttonName);
}

void UItemMenu::MenuFadeOutDone()
{
	m_fadeOutDoneDelegate.Broadcast(m_menuName);
}

void UItemMenu::AskFadeOut_Implementation()
{

}
