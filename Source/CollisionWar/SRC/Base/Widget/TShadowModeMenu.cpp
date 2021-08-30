// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "WidgetTree.h"
#include "HorizontalBox.h"
#include "HorizontalBoxSlot.h"
#include "TShadowModeMenu.h"




void UTShadowModeMenu::NotifyInitial_Implementation()
{

}

void UTShadowModeMenu::FadeOut_Implementation()
{

}

void UTShadowModeMenu::ReadAllShadowCards()
{
	
}

void UTShadowModeMenu::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "TutorialSerial")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->LoadTutorialSerialMenu();
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_curTutorialName)) pCWGI->m_doneTutorialSteps.Add(pSPGM->m_curTutorialName);
		pSPGM->m_curTutorialName = "NULL";
		m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTShadowModeMenu::SetTextBlockTexts()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i = 0; i < m_chTextBlockTexts.Num(); i++)
		{
			if (i >= m_pTextBlocks.Num()) return;
			m_pTextBlocks[i]->SetText(FText::FromString(m_chTextBlockTexts[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_textBlockTexts.Num(); i++)
		{
			if (i >= m_pTextBlocks.Num()) return;
			m_pTextBlocks[i]->SetText(FText::FromString(m_textBlockTexts[i]));
		}
	}
}
