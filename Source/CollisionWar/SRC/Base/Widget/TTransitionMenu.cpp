// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "TTransitionMenu.h"




void UTTransitionMenu::InitialTransitionMenu()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		if (m_chDescriptions.Num() > 0) m_pDescriptionBox->SetText(FText::FromString(m_chDescriptions[0]));
	}
	else if (m_chDescriptions.Num() > 0) m_pDescriptionBox->SetText(FText::FromString(m_enDescriptions[0]));
}

void UTTransitionMenu::UpdateProgressBar()
{
	float curProgress = (float)m_curLoadProgress / 100.f;
	m_pProgressBar->SetPercent(curProgress);
}

void UTTransitionMenu::FadeOutEnd()
{
	RemoveFromParent();
	if (IsValidLowLevel()) ConditionalBeginDestroy();
}

void UTTransitionMenu::InitialCalenderData()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	FString dayText = "DAY ";
	m_pTitleText->SetText(FText::FromString(dayText + FString::FromInt(pSPGM->m_curDayNb)));
	FString calenderDemoText;
	if (pSPGM->m_pSPPC->m_pWidgetManager->m_language == "Chinese")
		calenderDemoText = ReadCalenderDemoText(true);
	else
		calenderDemoText = ReadCalenderDemoText(false);
	m_pDescriptionBox->SetText(FText::FromString(calenderDemoText));
	int32 randNb = FMath::RandRange(0, m_pAllMediaSources.Num() - 1);
	m_pMediaPlayer->OpenSource(m_pAllMediaSources[randNb]);
}

FString UTTransitionMenu::ReadCalenderDemoText_Implementation(bool chOrEn)
{
	FString demoText;
	return demoText;
}

void UTTransitionMenu::NotifyInitial_Implementation()
{

}

void UTTransitionMenu::NotifyFadeOut_Implementation()
{

}
