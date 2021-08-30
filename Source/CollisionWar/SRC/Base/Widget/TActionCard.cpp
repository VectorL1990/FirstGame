// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TimerManager.h"
#include "TActionCard.h"




void UTActionCard::NotifyInitial_Implementation()
{

}

void UTActionCard::InitialActionCard(int32 cardNb, uint8 color, FString cardName, UTexture* pTexture)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (cardNb == -1)
	{
		m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
		m_pNbText->SetVisibility(ESlateVisibility::Hidden);
		if (!pSPGM->m_pPlayCardTextureMap.Contains(cardName) && !pTexture) return;
		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pBurningTextureMI);
		if (!pTexture)
			pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pSPGM->m_pPlayCardTextureMap[cardName].pTexture);
		else
			pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
		m_pPlayCardImage->Brush.SetResourceObject(pMI);
	}
	else
	{
		m_pNbText->SetText(FText::FromString(FString::FromInt(cardNb)));
		if (!pSPGM->m_pColorTextureMap.Contains(color)) return;
		m_pColorImage->Brush.SetResourceObject(pSPGM->m_pColorTextureMap[color]);
		/*UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pBurningTextureMI);
		pMI->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pSPGM->m_pColorTextureMap[color]);
		m_pColorImage->Brush.SetResourceObject(pMI);*/
	}
	m_cardName = cardName;
	m_nb = cardNb;
	m_color = color;
}

void UTActionCard::OnCardDrag()
{
	//if (m_nb == -1) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (pSPPC->m_gameState == 1)
	{
		//说明是DiceBattle状态，这时拖动ActionCard是拖动技能卡
		pSPPC->m_pSelectDiceBattleSkill = this;
	}
	else if (pSPPC->m_gameState == 2)
	{
		pSPPC->m_pSelectTheorizeCard = this;
	}
}

void UTActionCard::NotifySetTimer_Implementation(uint8 fadeType)
{

}

void UTActionCard::ClearFadeTimer_Implementation()
{

}

void UTActionCard::SetFadeType(bool flipOrFade, bool frontOrBack)
{
	UMaterialInstanceDynamic* pMI = m_pPlayCardImage->GetDynamicMaterial();
	FString paramStr1 = "FlipOrFade";
	FString paramStr2 = "FrontOrBack";
	if (flipOrFade)
		pMI->SetScalarParameterValue(FName(*paramStr1), 1);
	else
		pMI->SetScalarParameterValue(FName(*paramStr1), 0);
	if  (frontOrBack)
		pMI->SetScalarParameterValue(FName(*paramStr2), 1);
	else
		pMI->SetScalarParameterValue(FName(*paramStr2), 0);
}

void UTActionCard::Fade()
{
	if (m_curFadeTime >= m_fadeTotalTime)
	{
		ClearFadeTimer();
		return;
	}
	else
	{
		float fadePercent = 0;
		if (m_fadeInOrOut)
			fadePercent = (float)m_curFadeTime / (float)m_fadeTotalTime;
		else
			fadePercent = 1.f - (float)m_curFadeTime / (float)m_fadeTotalTime;
		UMaterialInstanceDynamic* pMI = m_pPlayCardImage->GetDynamicMaterial();
		FString dissolveTimeParamStr = "BackDissolveTime";
		pMI->SetScalarParameterValue(FName(*dissolveTimeParamStr), fadePercent);
		m_curFadeTime += 1;
	}
}

void UTActionCard::HighLight()
{
	if (m_highHightFlag)
	{
		//说明是从0开始，此时往高亮方向发展
		if (!m_pPlayCardImage) return;
		m_curHighLightProgress += m_highLightStep;
		if (m_curHighLightProgress >= 1) m_curHighLightProgress = 1;
		UObject* pObject = m_pPlayCardImage->Brush.GetResourceObject();
		UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
		pMI->SetScalarParameterValue(FName(TEXT("Fresnel_Emissive")), m_curHighLightProgress);
		if (m_curHighLightProgress == 1)
			ClearFadeTimer();
	}
	else
	{
		if (!m_pPlayCardImage) return;
		m_curHighLightProgress -= m_highLightStep;
		if (m_curHighLightProgress <= 0) m_curHighLightProgress = 0;
		UObject* pObject = m_pPlayCardImage->Brush.GetResourceObject();
		UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
		pMI->SetScalarParameterValue(FName(TEXT("Fresnel_Emissive")), m_curHighLightProgress);
		if (m_curHighLightProgress == 0)
			ClearFadeTimer();
	}
}

void UTActionCard::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "FlipDrawCard")
	{
		SetFadeType(true, false);
		SetupFadeInTimer(0 ,true);

		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (pSPGM->m_allDrawCardsInfo[pSPGM->m_winDrawCardNb].color == m_color && pSPGM->m_allDrawCardsInfo[pSPGM->m_winDrawCardNb].nb == m_nb)
			pSPGM->m_drawCardState = 2;
		else
		{
			pSPGM->m_drawTrialTimes -= 1;
			if (pSPGM->m_drawTrialTimes <= 0) pSPGM->m_drawCardState = 3;
		}
	}
	else if (buttonFunction == "SelectShopCard")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		if (pSPPC->m_pShopMenu->m_pCurSelectActionCard == this) return;
		if (pSPPC->m_pShopMenu->m_pCurSelectActionCard)
		{
			pSPPC->m_pShopMenu->m_pCurSelectActionCard->m_highHightFlag = false;
			pSPPC->m_pShopMenu->m_pCurSelectActionCard->NotifySetTimer(1);
		}
		pSPPC->m_pShopMenu->m_pCurSelectActionCard = this;
		if (pSPGM->m_pPlayCardTextureMap.Contains(m_cardName))
		{
			if (pSPPC->m_pShopMenu->m_pWidgetManager->m_language == "Chinese")
				pSPPC->m_pShopMenu->m_pShopCardDescriptionBox->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[m_cardName].description.chDescription));
			else
				pSPPC->m_pShopMenu->m_pShopCardDescriptionBox->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[m_cardName].description.enDescription));
		}
		m_highHightFlag = true;
		NotifySetTimer(1);
	}
	else if (buttonFunction.Contains("DecipherSkill_"))
	{
		FString skillName = buttonFunction.RightChop(32);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		pSPGM->LaunchTheorizeSkill(skillName);
		NotifySetTimer(0);
	}
	else if (buttonFunction.Contains("ChoiceBonusCard_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pCardSelectMenu->m_allBonusCardNames.Add(m_cardName);

		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (pSPGM->m_gameState == 0)
		{
			pSPPC->m_pCardSelectMenu->FadeOut();
			pSPGM->m_pControlCharacter->SetActorLocation(FVector(0, 0, 330));
			pSPGM->NotifyLoadCalenderMenu();
		}
		else if (pSPGM->m_gameState == 1)
			pSPGM->m_diceBattleStage = 13;
		else if (pSPGM->m_gameState == 2)
			pSPGM->m_theorizeState = 14;
		pSPGM->InterpretBonus();
	}
	else if (buttonFunction.Contains("MustBonusCard_"))
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->m_pCardSelectMenu->m_allBonusCardNames.Add(m_cardName);
		if (pSPPC->m_pCardSelectMenu->m_pAllBonusCards.Num() <= 1)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			if (pSPGM->m_gameState == 1)
				pSPGM->m_diceBattleStage = 13;
			else if (pSPGM->m_gameState == 2)
				pSPGM->m_theorizeState = 14;
			pSPGM->InterpretBonus();
		}
		else
		{
			NotifyFadeOut();
			pSPPC->m_pCardSelectMenu->m_pAllBonusCards.Remove(this);
		}
	}
}

void UTActionCard::OnHoverStart(uint8 cardType)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (cardType == 0)
	{
		//说明是DiceSkillCard
		if (!pSPPC->m_allDiceBattleSkillInfos.Contains(m_cardName)) return;
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
			pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(pSPPC->m_allDiceBattleSkillInfos[m_cardName].chSkillDescription));
		else
			pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(pSPPC->m_allDiceBattleSkillInfos[m_cardName].skillDescription));
	}
	else if (cardType == 1)
	{
		//说明是TheorizeSkillCard
		if (!pSPPC->m_alltheorizeSkillInfos.Contains(m_cardName)) return;
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
			pSPPC->m_pTheorizeMenu->m_pDescription->SetText(FText::FromString(pSPPC->m_alltheorizeSkillInfos[m_cardName].chSkillDescription));
		else
			pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(pSPPC->m_alltheorizeSkillInfos[m_cardName].skillDescription));
	}
}

void UTActionCard::FadeOutEnd(uint8 cardType)
{
	if (IsValidLowLevel()) ConditionalBeginDestroy();
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	/** 这里的type标识卡牌类型
	* 0 - 此卡为记忆玩法的技能牌
	* 1 - 此卡为推理玩法的技能牌
	* 2 - 此卡为奖励卡牌
	*/
	if (cardType == 0)
	{
		if (pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap.Contains(m_cardName))
		{
			pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap[m_cardName] = pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap[m_cardName] - 1;
			if (pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap[m_cardName] <= 0)
				pCWGI->m_curPlayerSPInfo.availableDiceBattleSkillMap.Remove(m_cardName);
		}
	}
	else if (cardType == 1)
	{
		if (pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap.Contains(m_cardName))
		{
			pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap[m_cardName] = pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap[m_cardName] - 1;
			if (pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap[m_cardName] <= 0)
				pCWGI->m_curPlayerSPInfo.availableTheorizeSkillMap.Remove(m_cardName);
		}
	}
}

void UTActionCard::NotifyChangeColor_Implementation(uint8 type)
{

}

void UTActionCard::Hover()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (m_cardName.Contains("ChoiceBonusCard_") || m_cardName.Contains("MustBonusCard_") || m_cardName.Contains("SAChoiceCard_"))
	{
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
		{
			if (pSPPC->m_pCardSelectMenu->m_pDescriptionBox)
				pSPPC->m_pCardSelectMenu->m_pDescriptionBox->SetText(FText::FromString(m_chDescription));
		}
		else
		{
			if (pSPPC->m_pCardSelectMenu->m_pDescriptionBox)
				pSPPC->m_pCardSelectMenu->m_pDescriptionBox->SetText(FText::FromString(m_enDescription));
		}
	}
	else if (m_cardName.Contains("DiceSkillCard_"))
	{
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
		{
			if (pSPPC->m_pDiceBattleMenu->m_pDescription)
				pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(m_chDescription));
		}
		else
		{
			if (pSPPC->m_pDiceBattleMenu->m_pDescription)
				pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(m_enDescription));
		}
	}
	else if (m_cardName.Contains("TheorizeSkillCard_"))
	{
		if (pSPPC->m_pWidgetManager->m_language == "Chinese")
		{
			if (pSPPC->m_pTheorizeMenu->m_pDescription)
				pSPPC->m_pTheorizeMenu->m_pDescription->SetText(FText::FromString(m_chDescription));
		}
		else
		{
			if (pSPPC->m_pTheorizeMenu->m_pDescription)
				pSPPC->m_pTheorizeMenu->m_pDescription->SetText(FText::FromString(m_enDescription));
		}
	}
}

void UTActionCard::HoverEnd()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (m_cardName.Contains("ChoiceBonusCard_") || m_cardName.Contains("MustBonusCard_") || m_cardName.Contains("SAChoiceCard_"))
	{
		if (pSPPC->m_pCardSelectMenu->m_pDescriptionBox)
			pSPPC->m_pCardSelectMenu->m_pDescriptionBox->SetText(FText::FromString(""));
	}
	else if (m_cardName.Contains("DiceSkillCard_"))
	{
		if (pSPPC->m_pDiceBattleMenu->m_pDescription)
			pSPPC->m_pDiceBattleMenu->m_pDescription->SetText(FText::FromString(""));
	}
	else if (m_cardName.Contains("TheorizeSkillCard_"))
	{
		if (pSPPC->m_pTheorizeMenu->m_pDescription)
			pSPPC->m_pTheorizeMenu->m_pDescription->SetText(FText::FromString(""));
	}
}

void UTActionCard::NotifyFadeOut_Implementation()
{

}

void UTActionCard::SetupFadeInTimer(uint8 fadeOrHighLight, bool fadeInOrOut)
{
	m_curFadeTime = 0;
	m_fadeInOrOut = fadeInOrOut;
	NotifySetTimer(fadeOrHighLight);
}

