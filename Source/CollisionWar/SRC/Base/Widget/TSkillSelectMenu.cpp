// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "GridSlot.h"
#include "TSkillSelectMenu.h"




void UTSkillSelectMenu::NotifyInitial_Implementation()
{

}

void UTSkillSelectMenu::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "EnterMap")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		pSPGM->OpenBattleLevel();
	}
	else if (buttonFunction == "TutorialSerial")
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

void UTSkillSelectMenu::InitialTexts(TArray<UTextBlock*> pTextBlocks)
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i = 0; i < pTextBlocks.Num(); i++)
		{
			if (i >= m_defaultChStrs.Num()) break;
			pTextBlocks[i]->SetText(FText::FromString(m_defaultChStrs[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < pTextBlocks.Num(); i++)
		{
			if (i >= m_defaultChStrs.Num()) break;
			pTextBlocks[i]->SetText(FText::FromString(m_defaultStrs[i]));
		}
	}
}

void UTSkillSelectMenu::DropSelectCard(UTemplateRuneElement* pSource)
{
	
}

void UTSkillSelectMenu::InitialTitleTexts()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i=0; i<m_pTitles.Num(); i++)
		{
			m_pTitles[i]->SetText(FText::FromString(m_chTitles[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_pTitles.Num(); i++)
		{
			m_pTitles[i]->SetText(FText::FromString(m_enTitles[i]));
		}
	}
	m_pLeftSkillSelectNb->SetText(FText::FromString(FString::FromInt(m_skillCapacity)));
}

void UTSkillSelectMenu::UpdateSkillCapacityText()
{
	m_pLeftSkillSelectNb->SetText(FText::FromString(FString::FromInt(m_skillCapacity)));
}
