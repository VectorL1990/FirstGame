// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../../Game/BattleLevelGameModeBase.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../Login/LoginPlayerController.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "TemplateRuneElement.h"




void UTemplateRuneElement::NotifyInitial_Implementation()
{

}

void UTemplateRuneElement::NotifyFadeOut_Implementation()
{

}

void UTemplateRuneElement::NotifyPress_Implementation()
{

}

void UTemplateRuneElement::NotifyRecover_Implementation()
{

}

void UTemplateRuneElement::ButtonClick()
{
	if (m_buttonFunction == "Battle_Option")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		pBLPC->m_pESCMenu->m_curPhase = 4;
		pBLPC->m_pESCMenu->NotifyVBoxFadeOut();
	}
	else if (m_buttonFunction == "Battle_BackToMainMenu")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		pBLPC->ApplyBackToMainMenu();
	}
	else if (m_buttonFunction == "Battle_Back")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
		pBLPC->m_pESCMenu->m_curPhase = 3;
		pBLPC->m_pESCMenu->NotifyVBoxFadeOut();
	}
	else if (m_buttonFunction == "Simple_SaveGame")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pPauseMenu->m_curPhase = 1;
		pSPPC->m_pPauseMenu->NotifyVBoxFadeOut();
	}
	else if (m_buttonFunction == "Simple_Option")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pPauseMenu->m_curPhase = 2;
		pSPPC->m_pPauseMenu->NotifyVBoxFadeOut();
	}
	else if (m_buttonFunction == "Simple_BackToMainMenu")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->ApplyBackToMainMenu();
	}
	else if (m_buttonFunction == "Simple_Save")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		FString slotName = pSPPC->m_pPauseMenu->m_selectSlotName.RightChop(9);
		pSPPC->SaveGame(slotName, 0);
		pSPPC->SaveProgressInfo("AllProgressInfo", false);
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
	else if (m_buttonFunction == "Simple_Load")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		FString slotName = pSPPC->m_pPauseMenu->m_selectSlotName.RightChop(9);
		pSPPC->m_waitToLoadSlotName = slotName;
		pSPPC->ApplyLoadDynamic();
	}
	else if (m_buttonFunction == "Simple_AddNewGameSlot")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		UTemplateNotification* pNotification = CreateWidget<UTemplateNotification>(UGameplayStatics::GetGameInstance(pSPPC->m_pPauseMenu->m_pWidgetManager), pSPPC->m_pPauseMenu->m_pWidgetManager->m_widgetClassMap["Notification"]);
		pNotification->NotifyInitial();
		if (pSPPC->m_pPauseMenu->m_pWidgetManager->m_language == "Chinese")
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_chButtonText[0]));
			//pNotification->m_pCancelText->SetText(FText::FromString(pNotification->m_chButtonText[1]));
		}
		else
		{
			pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[0]));
			//pNotification->m_pSaveText->SetText(FText::FromString(pNotification->m_enButtonText[1]));
		}
		pSPPC->m_pNotificationMenu = pNotification;
		pSPPC->m_pNotificationMenu->AddToViewport();
	}
	else if (m_buttonFunction == "Simple_Back")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pPauseMenu->m_curPhase = 0;
		pSPPC->m_pPauseMenu->NotifyVBoxFadeOut();
	}
	else if (m_buttonFunction.Contains("CardFunctionElement_"))
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		FString cardName = m_buttonFunction.RightChop(20);
		if (!pSPGM->m_pPlayCardTextureMap.Contains(cardName)) return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (pSPPC->m_pSPMenu->m_pWidgetManager->m_language == "Chinese")
			pSPPC->m_pSPMenu->m_pCardFunctionDescriptionBox->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[cardName].description.chDescription));
		else
			pSPPC->m_pSPMenu->m_pCardFunctionDescriptionBox->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[cardName].description.enDescription));
	}
	else if (m_buttonFunction.Contains("CardCombineElement_"))
	{
		FString cardName = m_buttonFunction.RightChop(19);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (!pSPPC->m_pCardCombineListMenu) return;
		if (pSPPC->m_pCardCombineListMenu->m_shadowActorOvervieMap.Contains(cardName))
			pSPPC->m_pCardCombineListMenu->m_pOverivewDescriptionBox->SetText(FText::FromString(pSPPC->m_pCardCombineListMenu->m_shadowActorOvervieMap[cardName]));
		if (pSPPC->m_pCardCombineListMenu->m_shadowActorCost.Contains(cardName))
		{
			pSPPC->m_pCardCombineListMenu->m_pLife->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].life)));
			pSPPC->m_pCardCombineListMenu->m_pEnergy->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].energy)));
			pSPPC->m_pCardCombineListMenu->m_pActivity->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].activity)));
			pSPPC->m_pCardCombineListMenu->m_pDarkness->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].darkness)));
			pSPPC->m_pCardCombineListMenu->m_pMentality->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].mentality)));
			pSPPC->m_pCardCombineListMenu->m_pFlameFaith->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].flameFaith)));
			pSPPC->m_pCardCombineListMenu->m_pSunFaith->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].sunFaith)));
			pSPPC->m_pCardCombineListMenu->m_pMoney->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].money)));
			pSPPC->m_pCardCombineListMenu->m_pSuppression->SetText(FText::FromString(FString::FromInt(pSPPC->m_pCardCombineListMenu->m_shadowActorCost[cardName].suppression)));
		}
	}
	else if (m_buttonFunction == "NewGame")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		pLPC->m_pPreBattleMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(pLPC->m_pLoginMenu->m_pWidgetManager, 0);
		pLPC->m_pPreBattleMenu->AddToViewport();
	}
	else if (m_buttonFunction == "LoginLoadGame")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		pLPC->m_pPreBattleMenu = UWidgetBlueprintFunctionLibrary::CreatePreBattleMenu(pLPC->m_pLoginMenu->m_pWidgetManager, 1);
		pLPC->m_pPreBattleMenu->AddToViewport();
	}
	else if (m_buttonFunction == "LoginOption")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ALoginPlayerController* pLPC = Cast<ALoginPlayerController>(pPC);
		pLPC->m_pOptionMenu = UWidgetBlueprintFunctionLibrary::CreateMainMenu(pLPC->m_pLoginMenu->m_pWidgetManager, 0);
		pLPC->m_pOptionMenu->AddToViewport();
	}
	else if (m_buttonFunction == "LoginExit")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ACWBaseGameMode* pCWGM = Cast<ACWBaseGameMode>(pGM);
		pCWGM->QuitGame();
	}
	else if (m_buttonFunction.Contains("ChoiceButton_"))
	{
		/** 选择型按钮
		* 1. 将选择的行动节点的信息写入到新Page中
		* 2. 更新page的内容
		* 3. 更新m_choiceSelectStr及curTreeNode
		* 4. 更新ActionPanel的显示
		* 5. 翻书
		*/
		FString choiceStr = m_buttonFunction.RightChop(13);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		int32 selectNb = pSPPC->m_pEventNodeManager->m_curTreeNode.descriptionAndChoice.choices.Find(choiceStr);

		FString demoWords = "sdf";
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
		{
			demoWords = pSPPC->ReadDemoWordPrefix(0, true);
			demoWords = demoWords.Append(pSPPC->m_pEventNodeManager->m_curTreeNode.descriptionAndChoice.chChoiceStrs[selectNb]);
		}
		else
		{
			demoWords = pSPPC->ReadDemoWordPrefix(0, false);
			demoWords = demoWords.Append(pSPPC->m_pEventNodeManager->m_curTreeNode.descriptionAndChoice.choiceStrs[selectNb]);
		}

		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (pSPPC->m_pEventNodeManager->m_curTreeNode.childrenNodeNbs.Num() > 0)
		{
			pSPPC->m_pEventNodeManager->m_choiceSelectStr.Append(choiceStr);
			int32 nodeNb = pSPPC->m_pEventNodeManager->m_curTreeNode.childrenNodeNbs[selectNb];
			pSPPC->m_pEventNodeManager->m_curTreeNode = pSPPC->m_pEventNodeManager->m_eventCardInfo.allNodes[nodeNb];
			pSPPC->m_pActionPanel->UpdateActionPanelInfo(pSPPC->m_pEventNodeManager);

		}
		else
		{
			pSPGM->UpdateEventCardAction(true);
			pSPGM->m_pEventNodeManager->ResetNodeManager();
		}
		
		pSPPC->m_pSPMenu->ShowDemoText(demoWords);
	}
	else if (m_buttonFunction.Contains("SkillSelectButton_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (!pSPPC->m_pSkillSelectMenu) return;
		FString skillName = m_buttonFunction.RightChop(18);
		for (int32 i=0; i<pSPPC->m_playerSkillInfos.Num(); i++)
		{
			if (pSPPC->m_playerSkillInfos[i].skillName != skillName) continue;
			if (pSPPC->m_pSkillSelectMenu->m_pWidgetManager->m_language == "Chinese")
				pSPPC->m_pSkillSelectMenu->m_pSkillDescriptionBox->SetText(FText::FromString(pSPPC->m_playerSkillInfos[i].chSkillDescription));
			else
				pSPPC->m_pSkillSelectMenu->m_pSkillDescriptionBox->SetText(FText::FromString(pSPPC->m_playerSkillInfos[i].skillDescription));
			pSPPC->m_pSkillSelectMenu->m_pCurSelectSkillButton = this;
			break;
		}
		
	}
	else if (m_buttonFunction.Contains("IncreaseAttribute_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (m_buttonFunction.Contains("_Unlock"))
		{
			FString AttributeNameAndUnlockStr = m_buttonFunction.RightChop(18);
			FString AttributeName = AttributeNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(AttributeName))
				pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add(AttributeName, 1);
			else
				pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[AttributeName] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[AttributeName] + 1;
			//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
			//NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableFCList[AttributeName]), FString::FromInt(pSPPC->m_FCInfos[AttributeName].unlockPoints));
			pCWGI->m_curPlayerSPInfo.unlockPointMap[0] = pCWGI->m_curPlayerSPInfo.unlockPointMap[0] - 1;
			pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			pSPGM->NotifyPlaySound2DByName("Unlock");
		}
		else
		{
			if (pSPPC->m_pRuneMenu->m_pCurSelectElement == this)
			{
				NotifyRecover();
				pSPPC->m_pRuneMenu->m_pCurSelectElement = NULL;
			}
			else
			{
				if (pSPPC->m_pRuneMenu->m_pCurSelectElement) pSPPC->m_pRuneMenu->m_pCurSelectElement->NotifyRecover();
				NotifyPress();
				pSPPC->m_pRuneMenu->m_pCurSelectElement = this;
				if (m_buttonFunction.Contains("FC_"))
				{
					FString FCName = m_buttonFunction.RightChop(3);
					if (!pSPPC->m_FCInfos.Contains(FCName)) return;
					if (pSPPC->m_pRuneMenu->m_pWidgetManager->m_language == "Chinese")
						pSPPC->m_pRuneMenu->m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].chDescription));
					else
						pSPPC->m_pRuneMenu->m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].description));
				}
			}
		}
	}
	else if (m_buttonFunction.Contains("FC_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (m_buttonFunction.Contains("_Unlock"))
		{
			FString FCNameAndUnlockStr = m_buttonFunction.RightChop(3);
			FString FCName = FCNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (pCWGI->m_curPlayerSPInfo.availableFCList[FCName] >= pSPPC->m_FCInfos[FCName].unlockPoints) return;
			else
			{
				//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
				pCWGI->m_curPlayerSPInfo.availableFCList[FCName] = pCWGI->m_curPlayerSPInfo.availableFCList[FCName] + 1;
				NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableFCList[FCName]), FString::FromInt(pSPPC->m_FCInfos[FCName].unlockPoints));
				pCWGI->m_curPlayerSPInfo.unlockPointMap[1] = pCWGI->m_curPlayerSPInfo.unlockPointMap[1] - 1;
				pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
				if (pCWGI->m_curPlayerSPInfo.availableFCList[FCName] < pSPPC->m_FCInfos[FCName].unlockPoints) return;
				UObject* pObject = m_pRuneImage->Brush.GetResourceObject();
				UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
				pMI->SetScalarParameterValue(FName("FrontOrBack"), 1);
				NotifySetTimer();
			}
		}
		else
		{
			if (pSPPC->m_pRuneMenu->m_pCurSelectElement == this)
			{
				NotifyRecover();
				pSPPC->m_pRuneMenu->m_pCurSelectElement = NULL;
			}
			else
			{
				if (pSPPC->m_pRuneMenu->m_pCurSelectElement) pSPPC->m_pRuneMenu->m_pCurSelectElement->NotifyRecover();
				NotifyPress();
				pSPPC->m_pRuneMenu->m_pCurSelectElement = this;
				if (m_buttonFunction.Contains("FC_"))
				{
					FString FCName = m_buttonFunction.RightChop(3);
					if (!pSPPC->m_FCInfos.Contains(FCName)) return;
					if (pSPPC->m_pRuneMenu->m_pWidgetManager->m_language == "Chinese")
						pSPPC->m_pRuneMenu->m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].chDescription));
					else
						pSPPC->m_pRuneMenu->m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].description));
				}
			}
		}
	}
	else if (m_buttonFunction.Contains("Appearance_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (m_buttonFunction.Contains("_Unlock"))
		{
			FString AppearanceNameAndUnlockStr = m_buttonFunction.RightChop(11);
			FString AppearanceName = AppearanceNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			for (int32 i=0; i<pSPPC->m_characterAppearanceInfo.Num(); i++)
			{
				if (AppearanceName != pSPPC->m_characterAppearanceInfo[i].appearanceName) continue;
				if (pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] >= pSPPC->m_characterAppearanceInfo[i].unlockPt) return;
				else
				{
					//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
					pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] = pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] + 1;
					NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName]), FString::FromInt(pSPPC->m_characterAppearanceInfo[i].unlockPt));
					pCWGI->m_curPlayerSPInfo.unlockPointMap[2] = pCWGI->m_curPlayerSPInfo.unlockPointMap[2] - 1;
					pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
					if (pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] >= pSPPC->m_characterAppearanceInfo[i].unlockPt)
					{
						UObject* pObject = m_pRuneImage->Brush.GetResourceObject();
						UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
						pMI->SetScalarParameterValue(FName("FrontOrBack"), 1);
						NotifySetTimer();
					}
				}
				break;
			}
		}
		else
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			if (!pSPGM->m_pDemoCharacter) return;
			FString itemListName = m_buttonFunction.RightChop(11);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			pSPGM->GetItemListByName(pCWGI->m_curPlayerSPInfo.characterName, itemListName);
			pSPPC->m_pRuneMenu->m_curAppearanceName = itemListName;
		}
	}
	/*else
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (!pSPPC || !pSPPC->m_pRuneMenu) return;
		pSPPC->m_pRuneMenu->SwitchCurRuneElement(this);
	}*/
	
}

void UTemplateRuneElement::AppendButtonClick(FString buttonFunction)
{
	if (buttonFunction.Contains("IncreaseAttribute_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (buttonFunction.Contains("_Unlock"))
		{
			FString AttributeNameAndUnlockStr = buttonFunction.RightChop(18);
			FString AttributeName = AttributeNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(AttributeName))
				pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add(AttributeName, 1);
			else
				pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[AttributeName] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[AttributeName] + 1;
			//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
			
			//NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableFCList[AttributeName]), FString::FromInt(pSPPC->m_FCInfos[AttributeName].unlockPoints));
			pCWGI->m_curPlayerSPInfo.unlockPointMap[0] = pCWGI->m_curPlayerSPInfo.unlockPointMap[0] - 1;
			if (pCWGI->m_curPlayerSPInfo.unlockPointMap[0] <= 0) pCWGI->m_curPlayerSPInfo.unlockPointMap.Remove(0);
			pSPPC->m_pRuneMenu->m_curUnlockNb -= 1;
			pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
			pSPPC->m_pRuneMenu->UpdateAttributeValue();
		}
	}
	else if (buttonFunction.Contains("FC_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (buttonFunction.Contains("_Unlock"))
		{
			FString FCNameAndUnlockStr = buttonFunction.RightChop(3);
			FString FCName = FCNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			if (pCWGI->m_curPlayerSPInfo.availableFCList[FCName] >= pSPPC->m_FCInfos[FCName].unlockPoints) return;
			else
			{
				//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
				pCWGI->m_curPlayerSPInfo.availableFCList[FCName] = pCWGI->m_curPlayerSPInfo.availableFCList[FCName] + 1;
				NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableFCList[FCName]), FString::FromInt(pSPPC->m_FCInfos[FCName].unlockPoints));
				pCWGI->m_curPlayerSPInfo.unlockPointMap[1] = pCWGI->m_curPlayerSPInfo.unlockPointMap[1] - 1;
				pSPPC->m_pRuneMenu->m_curUnlockNb -= 1;
				pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
				AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
				ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
				pSPGM->NotifyPlaySound2DByName("Unlock");
				if (pCWGI->m_curPlayerSPInfo.availableFCList[FCName] < pSPPC->m_FCInfos[FCName].unlockPoints) return;
				UObject* pObject = m_pRuneImage->Brush.GetResourceObject();
				UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
				pMI->SetScalarParameterValue(FName("FrontOrBack"), 1);
				NotifySetTimer();
			}
		}
	}
	else if (buttonFunction.Contains("Appearance_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (buttonFunction.Contains("_Unlock"))
		{
			FString AppearanceNameAndUnlockStr = buttonFunction.RightChop(11);
			FString AppearanceName = AppearanceNameAndUnlockStr.LeftChop(7);
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			for (int32 i = 0; i < pSPPC->m_characterAppearanceInfo.Num(); i++)
			{
				if (AppearanceName != pSPPC->m_characterAppearanceInfo[i].appearanceName) continue;
				if (pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] >= pSPPC->m_characterAppearanceInfo[i].unlockPt) return;
				else
				{
					//解锁点+1，显示那里要+1，同时解锁点-1，显示-1
					pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] = pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] + 1;
					NotifySetUnlockText(FString::FromInt(pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName]), FString::FromInt(pSPPC->m_characterAppearanceInfo[i].unlockPt));
					pCWGI->m_curPlayerSPInfo.unlockPointMap[2] = pCWGI->m_curPlayerSPInfo.unlockPointMap[2] - 1;
					pSPPC->m_pRuneMenu->m_curUnlockNb -= 1;
					pSPGM->NotifyPlaySound2DByName("Unlock");
					pSPPC->m_pRuneMenu->UpdateUnlockCardNbText();
					if (pCWGI->m_curPlayerSPInfo.availableAppearanceList[AppearanceName] >= pSPPC->m_characterAppearanceInfo[i].unlockPt)
					{
						UObject* pObject = m_pRuneImage->Brush.GetResourceObject();
						UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
						pMI->SetScalarParameterValue(FName("FrontOrBack"), 1);
						NotifySetTimer();
					}
				}
				break;
			}
		}
	}
}

void UTemplateRuneElement::NotifySetTimer_Implementation()
{

}

void UTemplateRuneElement::Fade()
{
	if (m_curFadeTime >= m_fadeTotalTime)
	{
		ClearFadeTimer();
		return;
	}
	else
	{
		float fadePercent = (float)m_curFadeTime / (float)m_fadeTotalTime;
		UMaterialInstanceDynamic* pMI = m_pRuneImage->GetDynamicMaterial();
		FString dissolveTimeParamStr = "BackDissolveTime";
		pMI->SetScalarParameterValue(FName(*dissolveTimeParamStr), fadePercent);
		m_curFadeTime += 1;
	}
}

void UTemplateRuneElement::NotifySetUnlockText_Implementation(const FString& curUnlockPt, const FString& maxUnlockPt)
{

}

void UTemplateRuneElement::ClearFadeTimer_Implementation()
{

}

void UTemplateRuneElement::NotifyChangeButtonImageAndText_Implementation(const FString& buttonName, bool chOrEn)
{

}
