// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../CollisionWarGameInstance.h"
#include "../../Game/Login/LoginGameModeBase.h"
#include "../Login/LoginPlayerController.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "TemplateNotification.h"
#include "VerticalBoxSlot.h"
#include "TemplatePreBattleMenu.h"




void UTemplatePreBattleMenu::NotifyInitial_Implementation()
{

}

void UTemplatePreBattleMenu::AskFadeOut_Implementation()
{

}

void UTemplatePreBattleMenu::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "Back")
	{
		AskFadeOut();
		return;
	}
	else if (buttonFunction == "PrePhase")
	{
		if (m_curPhase == 3)
		{
			m_curPhase = 0;
			NotifyVBoxFadeOut();
		}
		else if (m_curPhase == 0)
			AskFadeOut();
		return;
	}
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ALoginGameModeBase* pLGM = Cast<ALoginGameModeBase>(pGM);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (buttonFunction == "Ensure")
	{
		if (m_selectSlotName == "") return;
		if (m_menuType == 0 || m_menuType == 1)
		{
			if (m_selectSlotName.Contains("Character_"))
			{
				FString selectRoleName = m_selectSlotName.RightChop(10);

				for (int32 i = 0; i < m_phaseChoiceMap[m_curPhase].list.Num(); i++)
				{
					if (m_phaseChoiceMap[m_curPhase].list[i].choiceName != selectRoleName) continue;
					if (m_phaseChoiceMap[m_curPhase].list[i].isAvailable)
						break;
					if (m_pWidgetManager->m_language == "Chinese")
						m_pDescriptionBox->SetText(FText::FromString(m_chNotAvailableNotification));
					else
						m_pDescriptionBox->SetText(FText::FromString(m_enNotAvailableNotification));
					return;
				}

				m_curPhase = 3;
				NotifyVBoxFadeOut();
				pCWGI->m_curPlayerSPInfo.Reset();
				pCWGI->m_curPlayerSPInfo.characterName = selectRoleName;
				pLGM->ReadCharacterPrefixSkills(selectRoleName);
				/*FString selectRoleName = m_selectSlotName.RightChop(10);
				FPlayerSingleProgressInfo playerSPInfo;
				playerSPInfo.Reset();
				playerSPInfo.characterName = selectRoleName;
				playerSPInfo.curProgress = 0;
				pCWGI->m_curPlayerSPInfo = playerSPInfo;*/
			}
			else if (m_selectSlotName.Contains("Map_"))
			{
				FString selectMapName = m_selectSlotName.RightChop(4);
				for (int32 i=0; i<m_phaseChoiceMap[m_curPhase].list.Num(); i++)
				{
					if (m_phaseChoiceMap[m_curPhase].list[i].choiceName != selectMapName) continue;

					if (!m_phaseChoiceMap[m_curPhase].list[i].isAvailable)
					{
						if (m_pWidgetManager->m_language == "Chinese")
							m_pDescriptionBox->SetText(FText::FromString(m_chNotAvailableNotification));
						else
							m_pDescriptionBox->SetText(FText::FromString(m_enNotAvailableNotification));
						return;
					}

					pCWGI->m_curPlayerSPInfo.curProgress = i;
					pLGM->FadeToSPLevel();
					APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
					ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
					AskFadeOut();
					pLPC->m_pLoginMenu->AskFadeOut();
					break;
				}
			}
			else if (m_selectSlotName.Contains("LoadSlot_"))
			{
				FString slotName = m_selectSlotName.RightChop(9);
				for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
				{
					if (pCWGI->m_playerSingleProgressInfos[i].progressName != slotName) continue;
					pCWGI->m_curPlayerSPInfo = pCWGI->m_playerSingleProgressInfos[i];
					pLGM->FadeToSPLevel();
					APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
					ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
					AskFadeOut();
					pLPC->m_pLoginMenu->AskFadeOut();
					break;
				}
			}
			
		}
		else
		{
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			FString slotName = m_selectSlotName.RightChop(9);
			pSPPC->SaveGame(slotName, 0);
			pSPPC->SaveProgressInfo("AllProgressInfo", false);
			if (m_pDescriptionBox)
			{
				FString dateDescription;
				if (m_pWidgetManager->m_language == "Chinese")
					dateDescription = FString::FromInt(pCWGI->m_curPlayerSPInfo.year) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_chyearStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.month) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_chmonthStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.day) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_chdayStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.hour) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_chhourStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.minute) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_chminStr +
					pSPPC->m_pPauseMenu->m_pWidgetManager->m_chsaveDescription;
				else
					dateDescription = FString::FromInt(pCWGI->m_curPlayerSPInfo.year) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_yearStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.month) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_monthStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.day) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_dayStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.hour) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_hourStr +
					FString::FromInt(pCWGI->m_curPlayerSPInfo.minute) + pSPPC->m_pPauseMenu->m_pWidgetManager->m_minStr +
					pSPPC->m_pPauseMenu->m_pWidgetManager->m_saveDescription;
				m_pDescriptionBox->SetText(FText::FromString(dateDescription));
			}
		}
	}
	else if (buttonFunction == "AddNewSlot")
	{
		UTemplateNotification* pNotification = CreateWidget<UTemplateNotification>(UGameplayStatics::GetGameInstance(m_pWidgetManager), m_pWidgetManager->m_widgetClassMap["Notification"]);
		pNotification->NotifyInitial();
		if (m_pWidgetManager->m_language == "Chinese")
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_chButtonText[0]));
			//pNotification->m_pCancelText->SetText(FText::FromString(pNotification->m_chButtonText[1]));
		}
		else
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[0]));
			//pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[1]));
		}
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pNotificationMenu = pNotification;
		pSPPC->m_pNotificationMenu->AddToViewport();
	}
	else if (buttonFunction.Contains("Character_"))
	{
		m_selectSlotName = buttonFunction;
		FString characterName = buttonFunction.RightChop(10);
		if (!m_pDescriptionBox || m_curPhase != 0) return;
		for (int32 i=0; i<m_phaseChoiceMap[m_curPhase].list.Num(); i++)
		{
			if (m_phaseChoiceMap[m_curPhase].list[i].choiceName != characterName) continue;
			if (m_pWidgetManager->m_language == "Chinese")
				m_pDescriptionBox->SetText(FText::FromString(m_phaseChoiceMap[m_curPhase].list[i].chDescription));
			else
				m_pDescriptionBox->SetText(FText::FromString(m_phaseChoiceMap[m_curPhase].list[i].enDescription));
			break;
		}
	}
	else if (buttonFunction == "LoadGame")
	{
		FString slotName = m_selectSlotName.RightChop(9);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_waitToLoadSlotName = slotName;
		pSPPC->ApplyLoadDynamic();
	}
	else if (buttonFunction == "DeleteSlot")
	{
		if (!m_pCurSelectRow || !m_pLoadSlots.Contains(m_pCurSelectRow)) return;
		for (int32 i=0; i<m_pLoadSlots.Num(); i++)
		{
			if (m_pLoadSlots[i] != m_pCurSelectRow) continue;
			m_pCurSelectRow->RemoveFromParent();
			m_pLoadSlots.RemoveAt(i);
			if (m_pCurSelectRow->IsValidLowLevel())
			{
				m_pCurSelectRow->ConditionalBeginDestroy();
				m_pCurSelectRow = NULL;
			}
			m_pDescriptionBox->SetText(FText::FromString(""));
			m_selectSlotName = "";
			pCWGI->m_playerSingleProgressInfos.RemoveAt(i);
			//m_pOverallSaveGameObject->m_allProgressInfos = pCWGI->m_playerSingleProgressInfos;
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
			pLPC->m_pOverallSaveGameObject->m_allProgressInfos = pCWGI->m_playerSingleProgressInfos;
			UGameplayStatics::SaveGameToSlot(pLPC->m_pOverallSaveGameObject, "AllProgressInfo", 0);
			if (m_pDescriptionBox) m_pDescriptionBox->SetText(FText::FromString(""));
			break;
		}
	}
	else if (buttonFunction == "ChangeSlotName")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (!pLPC->m_pPreBattleMenu->m_pCurSelectRow) return;
		UTemplateNotification* pNotification = CreateWidget<UTemplateNotification>(UGameplayStatics::GetGameInstance(m_pWidgetManager), m_pWidgetManager->m_widgetClassMap["ChangeSlotNameMenu"]);
		pNotification->NotifyInitial();
		if (m_pWidgetManager->m_language == "Chinese")
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_chButtonText[0]));
			//pNotification->m_pCancelText->SetText(FText::FromString(pNotification->m_chButtonText[1]));
		}
		else
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[0]));
			//pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[1]));
		}
		
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu = pNotification;
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu->AddToViewport();
	}
}

void UTemplatePreBattleMenu::NotifyVBoxFadeOut_Implementation()
{

}

void UTemplatePreBattleMenu::NotifyVBoxFadeInt_Implementation()
{

}

void UTemplatePreBattleMenu::SwitchPhase()
{
	while (m_pLoadSlots.Num() > 0)
	{
		m_pLoadSlots.Last()->RemoveFromParent();
		if (m_pLoadSlots.Last()->IsValidLowLevel())
			m_pLoadSlots.Last()->ConditionalBeginDestroy();
		m_pLoadSlots.Pop();
	}
	m_pVBox->ClearChildren();
	for (int32 i = 0; i < m_phaseChoiceMap[m_curPhase].list.Num(); i++)
	{
		UTemplateRow* pRow = CreateWidget<UTemplateRow>(UGameplayStatics::GetGameInstance(this), m_pWidgetManager->m_widgetClassMap["Row"]);
		pRow->NotifyIntial();
		pRow->m_type = m_curPhase;
		pRow->m_buttonFunction = m_phaseChoiceMap[m_curPhase].list[i].function;
		if (m_pWidgetManager->m_language == "Chinese")
			pRow->m_pSlotText->SetText(FText::FromString(m_phaseChoiceMap[m_curPhase].list[i].chName));
		else
			pRow->m_pSlotText->SetText(FText::FromString(m_phaseChoiceMap[m_curPhase].list[i].enName));
		UPanelSlot* pSlot = m_pVBox->AddChild(pRow);
		UVerticalBoxSlot* pVSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVSlot->SetPadding(m_margin);
		m_pLoadSlots.Add(pRow);
	}
	m_pDescriptionBox->SetText(FText::FromString(""));
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);
	pCWGM->TestShipping("PreBattleMenuSwitchPhase_now phase is:" + FString::FromInt(m_curPhase));*/
	NotifyVBoxFadeInt();
}

void UTemplatePreBattleMenu::ReadDescription_Implementation()
{

}
