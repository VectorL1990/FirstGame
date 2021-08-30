// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Login/LoginPlayerController.h"
#include "TemplateMainMenu.h"




void UTemplateMainMenu::NotifyInitial_Implementation()
{

}

void UTemplateMainMenu::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "CancelLoginOption")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (pLPC->m_pOptionMenu->IsValidLowLevel())
		{
			pLPC->m_pOptionMenu->RemoveFromParent();
			pLPC->m_pOptionMenu->ConditionalBeginDestroy();
		}
	}
}
