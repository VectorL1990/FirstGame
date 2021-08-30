// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "TJudgeInfo.h"




void UTJudgeInfo::NotifyInitial_Implementation()
{

}

void UTJudgeInfo::ClickButton()
{
	if (m_buttonFunction.Contains("CharacterState_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		if (!pBLPC->m_pCharacterStatusMenu) return;
		FString stateName = m_buttonFunction.RightChop(15);
		//m_pColorImage->Brush.SetResourceObject(pBLPC->m_stateCardInfoMap[stateName].pTexture);
		pBLPC->m_pCharacterStatusMenu->m_pDescriptionBox->SetText(FText::FromString(m_description));
		/*if (pBLPC->m_pCharacterStatusMenu->m_pWidgetManager->m_language == "Chinese")
			pBLPC->m_pCharacterStatusMenu->m_pDescriptionBox->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[stateName].chDescription));
		else
			pBLPC->m_pCharacterStatusMenu->m_pDescriptionBox->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[stateName].description));*/
	}
}
