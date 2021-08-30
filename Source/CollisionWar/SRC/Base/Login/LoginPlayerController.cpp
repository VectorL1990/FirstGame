// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "LoginPlayerController.h"





void ALoginPlayerController::DeleteMenu(const FString& menuName)
{
	if (menuName == "PreBattleMenu")
	{
		m_pPreBattleMenu->RemoveFromParent();
		if (m_pPreBattleMenu->IsValidLowLevel())
		{
			m_pPreBattleMenu->ConditionalBeginDestroy();
			m_pPreBattleMenu = NULL;
		}
	}
}

void ALoginPlayerController::NotifyLoadLogoMenu_Implementation()
{

}

void ALoginPlayerController::NotifyLoadTransitionMenu_Implementation()
{

}
