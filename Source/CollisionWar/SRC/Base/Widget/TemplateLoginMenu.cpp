// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../Login/LoginPlayerController.h"
#include "TemplateLoginMenu.h"




void UTemplateLoginMenu::NotifyInitial_Implementation()
{

}

void UTemplateLoginMenu::AskFadeOut_Implementation()
{

}

void UTemplateLoginMenu::ClickButton(const FString& buttonFunction)
{
	/*APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
	if (buttonFunction == "NewGame")
		pLPC->m_pPreBattleMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(m_pWidgetManager, 0);
	else if (buttonFunction == "LoadGame")
		pLPC->m_pPreBattleMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(m_pWidgetManager, 1);
	else if (buttonFunction == "Option")
		pLPC->m_pPreBattleMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(m_pWidgetManager, 3);
	pLPC->m_pPreBattleMenu->AddToViewport();*/
}
