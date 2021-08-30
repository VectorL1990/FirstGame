// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Login/LoginPlayerController.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "TemplateRow.h"




void UTemplateRow::NotifyIntial_Implementation()
{

}

void UTemplateRow::ClickButton(FString buttonFunction)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	if (m_type == 1 || m_type == 0 || m_type == 3)
	{
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (!pLPC->m_pPreBattleMenu) return;
		pLPC->m_pPreBattleMenu->m_selectSlotName = m_buttonFunction;
		pLPC->m_pPreBattleMenu->m_pCurSelectRow = this;
		if (pLPC->m_pPreBattleMenu->m_menuType == 0)
		{
			FString functionName;
			if (pLPC->m_pPreBattleMenu->m_curPhase == 0)
				functionName = m_buttonFunction.RightChop(10);
			else if (pLPC->m_pPreBattleMenu->m_curPhase == 3)
				functionName = m_buttonFunction.RightChop(4);

			for (int32 i=0; i<pLPC->m_pPreBattleMenu->m_phaseChoiceMap[pLPC->m_pPreBattleMenu->m_curPhase].list.Num(); i++)
			{
				if (pLPC->m_pPreBattleMenu->m_phaseChoiceMap[pLPC->m_pPreBattleMenu->m_curPhase].list[i].choiceName != functionName) continue;
				if (pLPC->m_pPreBattleMenu->m_pWidgetManager->m_language == "Chinese")
					pLPC->m_pPreBattleMenu->m_pDescriptionBox->SetText(FText::FromString(pLPC->m_pPreBattleMenu->m_phaseChoiceMap[pLPC->m_pPreBattleMenu->m_curPhase].list[i].chDescription));
				else
					pLPC->m_pPreBattleMenu->m_pDescriptionBox->SetText(FText::FromString(pLPC->m_pPreBattleMenu->m_phaseChoiceMap[pLPC->m_pPreBattleMenu->m_curPhase].list[i].enDescription));
				break;
			}
		}
		else
		{
			if (pLPC->m_pPreBattleMenu->m_pDescriptionBox)
			{
				UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
				UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
				FString slotName = m_buttonFunction.RightChop(9);
				for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
				{
					if (pCWGI->m_playerSingleProgressInfos[i].progressName != slotName) continue;
					FString dateDescription;
					if (pLPC->m_pPreBattleMenu->m_pWidgetManager->m_language == "Chinese")
						dateDescription = FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].year) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chyearStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].month) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chmonthStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].day) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chdayStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].hour) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chhourStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].minute) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chminStr +
						pLPC->m_pPreBattleMenu->m_pWidgetManager->m_chsaveDescription;
					else
						dateDescription = FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].year) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_yearStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].month) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_monthStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].day) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_dayStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].hour) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_hourStr +
						FString::FromInt(pCWGI->m_playerSingleProgressInfos[i].minute) + pLPC->m_pPreBattleMenu->m_pWidgetManager->m_minStr +
						pLPC->m_pPreBattleMenu->m_pWidgetManager->m_saveDescription;
					pLPC->m_pPreBattleMenu->m_pDescriptionBox->SetText(FText::FromString(dateDescription));
					break;
				}
				
			}
		}
	}
	else
	{
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (!pSPPC->m_pPauseMenu) return;
		pSPPC->m_pPauseMenu->m_selectSlotName = m_buttonFunction;
		if (pSPPC->m_pPauseMenu->m_pSaveSlotDescription)
		{
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			FString dateDescription;
			if (pSPPC->m_pPauseMenu->m_pWidgetManager->m_language == "Chinese")
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
			pSPPC->m_pPauseMenu->m_pSaveSlotDescription->SetText(FText::FromString(dateDescription));
		}
	}

}

