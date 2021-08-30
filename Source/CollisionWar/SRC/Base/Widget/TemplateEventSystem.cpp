// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "TemplateEventSystem.h"




void UTemplateEventSystem::NotifyInitial_Implementation()
{

}

void UTemplateEventSystem::ButtonClick(const FString& buttonFunction)
{
	if (buttonFunction == "Cancel")
	{
		RemoveFromParent();
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pMissionMenu = NULL;
		if (IsValidLowLevel())
			ConditionalBeginDestroy();
		
	}
}

void UTemplateEventSystem::LoadMissionText(const FString& text)
{
	m_pDescriptionBox->SetText(FText::FromString(text));
}
