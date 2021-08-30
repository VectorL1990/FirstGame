// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../CollisionWarGameInstance.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Login/LoginPlayerController.h"
#include "TemplateNotification.h"




void UTemplateNotification::NotifyInitial_Implementation()
{

}

void UTemplateNotification::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "Ensure")
	{
		/** 保存要分两步
		* 1. 保存总体信息
		* 2. 保存单独的关卡信息
		* 3. 在PreBattleMenu里添加新的记录
		*/
		if (m_slotName == "") return;
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		bool findProgress = false;
		for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
		{
			if (pCWGI->m_playerSingleProgressInfos[i].progressName != m_slotName) continue;
			findProgress = true;
			break;
		}
		if (findProgress) return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pCWGI->m_curPlayerSPInfo.progressName = m_slotName;
		pSPPC->SaveGame(m_slotName, 0);
		pSPPC->SaveProgressInfo("AllProgressInfo", true);
		UTemplateRow* pRow = CreateWidget<UTemplateRow>(pGI, pSPPC->m_pWidgetManager->m_widgetClassMap["Row"]);
		pRow->NotifyIntial();
		pRow->m_type = 2;
		FString slotNamePrefix = "LoadSlot_";
		pRow->m_buttonFunction = slotNamePrefix.Append(m_slotName);
		pRow->m_pSlotText->SetText(FText::FromString(m_slotName));
		if (pSPPC->m_pPauseMenu)
		{
			pSPPC->m_pPauseMenu->m_pSlotVBox->AddChild(pRow);
			pSPPC->m_pPauseMenu->m_pRows.Add(pRow);
			if (pSPPC->m_pPauseMenu->m_pSaveSlotDescription)
			{
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

		/*pSPPC->m_pSaveMenu->m_pVBox->AddChild(pRow);
		pSPPC->m_pSaveMenu->m_pLoadSlots.Add(pRow);*/

		if (!pSPPC->m_pNotificationMenu || !pSPPC->m_pNotificationMenu->IsValidLowLevel()) return;
		pSPPC->m_pNotificationMenu->RemoveFromParent();
		pSPPC->m_pNotificationMenu->ConditionalBeginDestroy();
		pSPPC->m_pNotificationMenu = NULL;
	}
	else if (buttonFunction == "ChangeSlotName")
	{
		if (m_slotName == "BattleTempSlot" || m_slotName == "AllProgressInfo") return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (!pLPC->m_pPreBattleMenu || !pLPC->m_pPreBattleMenu->m_pCurSelectRow) return;
		FString slotName = pLPC->m_pPreBattleMenu->m_pCurSelectRow->m_buttonFunction.RightChop(9);
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		int32 slotNb = -1;
		for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
		{
			if (pCWGI->m_playerSingleProgressInfos[i].progressName == slotName) slotNb = i;
			if (pCWGI->m_playerSingleProgressInfos[i].progressName != m_slotName) continue;
			slotNb = -1;
			break;
		}
		if (slotNb == -1) return;
		pCWGI->m_playerSingleProgressInfos[slotNb].progressName = m_slotName;
		//保存
		pLPC->m_pOverallSaveGameObject->m_allProgressInfos = pCWGI->m_playerSingleProgressInfos;
		UGameplayStatics::SaveGameToSlot(pLPC->m_pOverallSaveGameObject, "AllProgressInfo", 0);
		//改上级菜单中的名字
		if (slotNb < pLPC->m_pPreBattleMenu->m_pLoadSlots.Num())
		{
			FString loadButtonFunction = "LoadSlot_" + m_slotName;
			pLPC->m_pPreBattleMenu->m_pLoadSlots[slotNb]->m_buttonFunction = loadButtonFunction;
			pLPC->m_pPreBattleMenu->m_pLoadSlots[slotNb]->m_pSlotText->SetText(FText::FromString(m_slotName));
		}
		//删除这个菜单
		RemoveFromParent();
		ConditionalBeginDestroy();
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu = NULL;
	}
	else if (buttonFunction == "Cancel")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (!pSPPC->m_pNotificationMenu || !pSPPC->m_pNotificationMenu->IsValidLowLevel()) return;
		pSPPC->m_pNotificationMenu->RemoveFromParent();
		pSPPC->m_pNotificationMenu->ConditionalBeginDestroy();
		pSPPC->m_pNotificationMenu = NULL;

	}
	else if (buttonFunction == "CancelChangeSlotNameMenu")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		if (!pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu || !pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu->IsValidLowLevel()) return;
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu->RemoveFromParent();
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu->ConditionalBeginDestroy();
		pLPC->m_pPreBattleMenu->m_pChangeSlotNameMenu = NULL;

	}
}

void UTemplateNotification::EnsureSlotName(FString slotName)
{
	m_slotName = slotName;
}

