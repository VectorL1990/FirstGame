// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "ScrollBoxSlot.h"
#include "GridSlot.h"
#include "WidgetTree.h"
#include "TemplateRunesMenu.h"




void UTemplateRunesMenu::NotifyInitial_Implementation()
{

}

void UTemplateRunesMenu::ButtonClick(FString buttonFunction)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
	if (buttonFunction == "Close")
	{
		pSPPC->m_playerSkillInfos.Empty();
		pSPPC->m_cardCombineInfo.Empty();
		pSPPC->m_FCInfos.Empty();
		pSPPC->PressEndRuneKey();
		return;
	}
	else if (buttonFunction == "SetCurAppearance")
	{
		if (m_curDomain != 3 || m_curAppearanceName == "") return;
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (!pCWGI->m_curPlayerSPInfo.availableAppearanceList.Contains(m_curAppearanceName)) return;
		pCWGI->m_curPlayerSPInfo.curAppearanceName = m_curAppearanceName;
		return;
	}
	/*else if (buttonFunction == "SwitchToSkillDomain")
	{
		if (m_curDomain == 1) return;
		m_targetDomain = 1;
		for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			iter->Value->NotifyFadeOut();
		}
		pSPPC->GetWorldTimerManager().SetTimer(m_switchTimerHandler, this, &UTemplateRunesMenu::SwitchDomain, m_switchDelayTime, false);
	}*/
	else if (buttonFunction == "SwitchToFCDomain")
	{
		if (m_curDomain == 2) return;
		m_targetDomain = 2;
		for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			iter->Value->NotifyFadeOut();
		}
		pSPPC->GetWorldTimerManager().SetTimer(m_switchTimerHandler, this, &UTemplateRunesMenu::SwitchDomain, m_switchDelayTime, false);
	}
	else if (buttonFunction == "SwitchToNumericDomain")
	{
		if (m_curDomain == 1) return;
		m_targetDomain = 1;
		for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			iter->Value->NotifyFadeOut();
		}
		pSPPC->GetWorldTimerManager().SetTimer(m_switchTimerHandler, this, &UTemplateRunesMenu::SwitchDomain, m_switchDelayTime, false);
	}
	else if (buttonFunction == "SwitchToAppearance")
	{
		if (m_curDomain == 3) return;
		m_targetDomain = 3;
		for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			iter->Value->NotifyFadeOut();
		}
		pSPPC->GetWorldTimerManager().SetTimer(m_switchTimerHandler, this, &UTemplateRunesMenu::SwitchDomain, m_switchDelayTime, false);
	}
	else if (buttonFunction == "SwitchToEquipInfos")
	{
		if (m_curDomain == 4) return;
		m_targetDomain = 4;
		for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value) continue;
			iter->Value->NotifyFadeOut();
		}
		pSPPC->GetWorldTimerManager().SetTimer(m_switchTimerHandler, this, &UTemplateRunesMenu::SwitchDomain, m_switchDelayTime, false);
	}
	for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value) continue;
		iter->Value->NotifyFadeOut();
	}
/*
	for (int32 i=0; i< m_pUnlockCardTitles.Num(); i++)
	{
		m_pUnlockCardTitles[i]->NotifyFadeOut();
	}*/
}

void UTemplateRunesMenu::SwitchCurRuneElement(UTemplateRuneElement* pSelectElement)
{
	if (!pSelectElement) return;
	if (m_pCurSelectElement == pSelectElement)
	{
		pSelectElement->NotifyRecover();
		m_pCurSelectElement = NULL;
	}
	else
	{
		if (m_pCurSelectElement) m_pCurSelectElement->NotifyRecover();
		pSelectElement->NotifyPress();
		m_pCurSelectElement = pSelectElement;
		/*if (m_pCurSelectElement->m_buttonFunction.Contains("Skill_"))
		{
			FString skillName = m_pCurSelectElement->m_buttonFunction.RightChop(6);
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			for (int32 i=0; i<pSPPC->m_playerSkillInfos.Num(); i++)
			{
				if (pSPPC->m_playerSkillInfos[i].skillName != skillName) continue;
				if (m_pWidgetManager->m_language == "Chinese")
					m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_playerSkillInfos[i].chSkillDescription));
				else
					m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_playerSkillInfos[i].skillDescription));
				break;
			}
		}*/
		if (m_pCurSelectElement->m_buttonFunction.Contains("FC_"))
		{
			FString FCName = m_pCurSelectElement->m_buttonFunction.RightChop(3);
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			if (!pSPPC->m_FCInfos.Contains(FCName)) return;
			if (m_pWidgetManager->m_language == "Chinese")
				m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].chDescription));
			else
				m_pDescriptionBox->SetText(FText::FromString(pSPPC->m_FCInfos[FCName].description));
		}
		if (!m_pCurSelectElement->m_buttonFunction.Contains("Appearance_")) return;
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pSPGM->m_pDemoCharacter) return;
		FString itemListName = pSelectElement->m_buttonFunction.RightChop(11);
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		pSPGM->GetItemListByName(pCWGI->m_curPlayerSPInfo.characterName, itemListName);
		m_curAppearanceName = itemListName;
	}
}

void UTemplateRunesMenu::UpdateUnlockCardNbText()
{
	if (m_curDomain == 1)
	{
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chAttributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_attributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
	else if (m_curDomain == 2)
	{
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chFCUnlockTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_fcUnlockTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
	else if (m_curDomain == 3)
	{
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chAppearanceUnlockTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_appearanceUnlockTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
}

void UTemplateRunesMenu::SwitchDomain()
{
	if (m_curDomain == m_targetDomain) return;
	for (TMap<FString, UTemplateRuneElement*>::TConstIterator iter = m_pRuneElementMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value) continue;
		iter->Value->RemoveFromParent();
		if (iter->Value->IsValidLowLevel())
			iter->Value->ConditionalBeginDestroy();
	}
	m_pRuneElementMap.Empty();
	m_pContentBox->ClearChildren();

	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FString unlockTitleStr;
	if (m_pWidgetManager->m_language == "Chinese")
		unlockTitleStr = m_chAttributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
	else
		unlockTitleStr = m_attributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
	m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(unlockTitleStr));

	//m_curDomainUnlockCardNbMap.Empty();
	m_curUnlockNb = 0;

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	
	if (m_targetDomain == 2)
	{
		if (m_pEquipGridPanel)
		{
			m_pEquipGridPanel->RemoveFromParent();
			if (m_pEquipGridPanel->IsValidLowLevel()) m_pEquipGridPanel->ConditionalBeginDestroy();
			m_pEquipGridPanel = NULL;
		}
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = pSPPC->m_FCInfos.CreateConstIterator(); iter; ++iter)
		{
			UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pCWGI, m_pWidgetManager->m_widgetClassMap["RuneElement"]);
			pRuneElement->NotifyInitial();
			UPanelSlot* pPanelSlot = m_pContentBox->AddChild(pRuneElement);
			UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pPanelSlot);
			pVBoxSlot->SetPadding(m_elementPadding);
			m_pRuneElementMap.Add(iter->Key, pRuneElement);
			/*UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(m_pWidgetManager, m_pWidgetManager->m_pSkillIconButtonMat);
			FString paramName = "ButtonTexture";
			pMI->SetTextureParameterValue(FName(*paramName), iter->Value.pTexture);
			pRuneElement->m_pRuneImage->Brush.SetResourceObject(pMI);*/
			UObject* pObject = pRuneElement->m_pRuneImage->Brush.GetResourceObject();
			UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
			pMI->SetTextureParameterValue(FName("BaseTexture"), iter->Value.pTexture);
			pMI->SetScalarParameterValue(FName("FlipOrFade"), 1);
			if (m_pWidgetManager->m_language == "Chinese")
				pRuneElement->m_pRuneName->SetText(FText::FromString(iter->Value.chFoundationCharacterName));
			else
				pRuneElement->m_pRuneName->SetText(FText::FromString(iter->Value.foundationCharacterName));
			FString runeFunction = "FC_";
			pRuneElement->m_buttonFunction = runeFunction.Append(iter->Value.foundationCharacterName);
			int32 curUnlockPt = pCWGI->m_curPlayerSPInfo.availableFCList[iter->Value.foundationCharacterName];
			int32 maxUnlockPt = iter->Value.unlockPoints;
			pRuneElement->NotifySetUnlockText(FString::FromInt(curUnlockPt), FString::FromInt(maxUnlockPt));
			if (iter->Value.isInitial || pCWGI->m_curPlayerSPInfo.availableFCList.Contains(iter->Value.foundationCharacterName)) continue;
			/*FString paramName_2 = "BaseColor";
			pMI->SetVectorParameterValue(FName(*paramName_2), m_inAvailableRuneColor);*/
			pMI->SetScalarParameterValue(FName("FrontOrBack"), 0);
		}

		if (pCWGI->m_curPlayerSPInfo.unlockPointMap.Contains(1)) m_curUnlockNb = pCWGI->m_curPlayerSPInfo.unlockPointMap[1];
		//m_curDomainUnlockCardNbMap.Add(0, unlockCardNb);
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chFCUnlockTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_fcUnlockTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
	else if (m_targetDomain == 1)
	{
		if (m_pEquipGridPanel)
		{
			m_pEquipGridPanel->RemoveFromParent();
			if (m_pEquipGridPanel->IsValidLowLevel()) m_pEquipGridPanel->ConditionalBeginDestroy();
			m_pEquipGridPanel = NULL;
		}
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		for (int32 i=0; i< m_increaseAttributeName.Num(); i++)
		{
			UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pCWGI, m_pWidgetManager->m_widgetClassMap["AttributeRuneElement"]);
			pRuneElement->NotifyInitial();
			UPanelSlot* pPanelSlot = m_pContentBox->AddChild(pRuneElement);
			UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pPanelSlot);
			pVBoxSlot->SetPadding(m_elementPadding);
			FString buttonName = m_increaseAttributeName[i];
			m_pRuneElementMap.Add(buttonName, pRuneElement);
			if (m_pWidgetManager->m_language == "Chinese")
				pRuneElement->NotifyChangeButtonImageAndText(buttonName, true);
			else
				pRuneElement->NotifyChangeButtonImageAndText(buttonName, false);

			FString runeFunction = "IncreaseAttribute_" + buttonName;
			pRuneElement->m_buttonFunction = runeFunction;

		}

		if (pCWGI->m_curPlayerSPInfo.unlockPointMap.Contains(0)) m_curUnlockNb = pCWGI->m_curPlayerSPInfo.unlockPointMap[0];
		//m_curDomainUnlockCardNbMap.Add(0, unlockCardNb);
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chAttributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_attributeIncreaseTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
	else if (m_targetDomain == 3)
	{
		if (m_pEquipGridPanel)
		{
			m_pEquipGridPanel->RemoveFromParent();
			if (m_pEquipGridPanel->IsValidLowLevel()) m_pEquipGridPanel->ConditionalBeginDestroy();
			m_pEquipGridPanel = NULL;
		}
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		for (int32 i = 0; i < pSPPC->m_characterAppearanceInfo.Num(); i++)
		{
			UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pCWGI, m_pWidgetManager->m_widgetClassMap["RuneElement"]);
			pRuneElement->NotifyInitial();
			UPanelSlot* pPanelSlot = m_pContentBox->AddChild(pRuneElement);
			UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pPanelSlot);
			pVBoxSlot->SetPadding(m_elementPadding);
			m_pRuneElementMap.Add(pSPPC->m_characterAppearanceInfo[i].appearanceName, pRuneElement);
			//pRuneElement->m_pRuneImage->Brush.SetResourceObject(m_pDefaultCardCombineTexture);
			UObject* pObject = pRuneElement->m_pRuneImage->Brush.GetResourceObject();
			UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
			pMI->SetTextureParameterValue(FName("BaseTexture"), m_pDefaultCardCombineTexture);
			pMI->SetScalarParameterValue(FName("FlipOrFade"), 1);
			if (m_pWidgetManager->m_language == "Chinese")
				pRuneElement->m_pRuneName->SetText(FText::FromString(pSPPC->m_characterAppearanceInfo[i].chAppearanceName));
			else
				pRuneElement->m_pRuneName->SetText(FText::FromString(pSPPC->m_characterAppearanceInfo[i].appearanceName));
			FString runeFunction = "Appearance_";
			pRuneElement->m_buttonFunction = runeFunction.Append(pSPPC->m_characterAppearanceInfo[i].appearanceName);
			int32 curUnlockPt = 0;
			if (pCWGI->m_curPlayerSPInfo.availableAppearanceList.Contains(pSPPC->m_characterAppearanceInfo[i].appearanceName))
				curUnlockPt = pCWGI->m_curPlayerSPInfo.availableAppearanceList[pSPPC->m_characterAppearanceInfo[i].appearanceName];
			int32 maxUnlockPt = pSPPC->m_characterAppearanceInfo[i].unlockPt;
			pRuneElement->NotifySetUnlockText(FString::FromInt(curUnlockPt), FString::FromInt(maxUnlockPt));
			if (pCWGI->m_curPlayerSPInfo.availableAppearanceList.Contains(pSPPC->m_characterAppearanceInfo[i].appearanceName)) continue;
			/*FString paramName_2 = "BaseColor";
			FSlateColor color(m_inAvailableRuneColor);
			pRuneElement->m_pRuneImage->Brush.TintColor = color;*/
			pMI->SetScalarParameterValue(FName("FrontOrBack"), 0);
		}

		if (pCWGI->m_curPlayerSPInfo.unlockPointMap.Contains(2)) m_curUnlockNb = pCWGI->m_curPlayerSPInfo.unlockPointMap[2];
		//m_curDomainUnlockCardNbMap.Add(0, unlockCardNb);
		FString str;
		if (m_pWidgetManager->m_language == "Chinese")
			str = m_chAppearanceUnlockTitle + FString::FromInt(m_curUnlockNb);
		else
			str = m_appearanceUnlockTitle + FString::FromInt(m_curUnlockNb);
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(str));
	}
	else if (m_targetDomain == 4)
	{
		m_pEquipGridPanel = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
		UPanelSlot* pSlot = m_pScrollBox->AddChild(m_pEquipGridPanel);
		UScrollBoxSlot* pScrollSlot = Cast<UScrollBoxSlot>(pSlot);
		pScrollSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		TMap<FString, int32> equipMap;
		for (int32 i = 0; i < pCWGI->m_curPlayerSPInfo.availableEquipList.Num(); i++)
		{
			if (equipMap.Contains(pCWGI->m_curPlayerSPInfo.availableEquipList[i]))
				equipMap[pCWGI->m_curPlayerSPInfo.availableEquipList[i]] = equipMap[pCWGI->m_curPlayerSPInfo.availableEquipList[i]] + 1;
			else
				equipMap.Add(pCWGI->m_curPlayerSPInfo.availableEquipList[i], 1);
		}
		for (TMap<FString, int32>::TConstIterator iter = equipMap.CreateConstIterator(); iter; ++iter)
		{
			UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pCWGI, m_pWidgetManager->m_widgetClassMap["EquipElement"]);
			pRuneElement->NotifyInitial();
			UPanelSlot* pPanelSlot = m_pEquipGridPanel->AddChild(pRuneElement);
			UGridSlot* pGridSlot = Cast<UGridSlot>(pPanelSlot);
			m_pRuneElementMap.Add(iter->Key, pRuneElement);
			UMaterialInstanceDynamic* pMI = pRuneElement->m_pRuneImage->GetDynamicMaterial();
			if (!pSPGM->m_pPlayCardTextureMap.Contains(iter->Key)) continue;
			pMI->SetTextureParameterValue(FName("Front"), pSPGM->m_pPlayCardTextureMap[iter->Key].pTexture);
			//pMI->SetScalarParameterValue(FName("FlipOrFade"), 1);
			FString nbText = "X" + FString::FromInt(iter->Value);
			pRuneElement->m_pRuneName->SetText(FText::FromString(nbText));
			pMI->SetScalarParameterValue(FName("FrontOrBack"), 0);
		}
		m_pUnlockCardTitle->m_pRuneName->SetText(FText::FromString(""));
	}
	m_curDomain = m_targetDomain;
}

void UTemplateRunesMenu::UpdateAttributeValue()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FString characterName = pCWGI->m_curPlayerSPInfo.characterName;
	if (characterName == "" || characterName == "NULL") characterName = "Lucian";
	FCharacterAttributeInfo characterAttributeInfo = ReadCharacterAttributeInfo(characterName);
	int32 curLife = characterAttributeInfo.maxLife;
	int32 curIncreaseLife = 0;
	if (pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(m_increaseAttributeName[0]))
	{
		curIncreaseLife = pCWGI->m_attributeIncreaseValueMap[m_increaseAttributeName[0]] * pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[m_increaseAttributeName[0]];
		if (curIncreaseLife >= pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[0]])
			curIncreaseLife = pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[0]];
	}
	m_pLifeNbText->SetText(FText::FromString(FString::FromInt(curLife + curIncreaseLife)));
	int32 curAtk = characterAttributeInfo.maxAtk;
	int32 curIncreaseAtk = 0;
	if (pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(m_increaseAttributeName[1]))
	{
		curIncreaseAtk = pCWGI->m_attributeIncreaseValueMap[m_increaseAttributeName[1]] * pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[m_increaseAttributeName[1]];
		if (curIncreaseAtk >= pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[1]])
			curIncreaseAtk = pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[1]];
	}
	m_pAtkNbText->SetText(FText::FromString(FString::FromInt(curAtk + curIncreaseAtk)));
	int32 curDfc = characterAttributeInfo.maxDfc;
	int32 curIncreaseDfc = 0;
	if (pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains(m_increaseAttributeName[2]))
	{
		curIncreaseDfc = pCWGI->m_attributeIncreaseValueMap[m_increaseAttributeName[2]] * pCWGI->m_curPlayerSPInfo.attributeIncreaseMap[m_increaseAttributeName[2]];
		if (curIncreaseDfc >= pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[2]])
			curIncreaseDfc = pCWGI->m_attributeIncreaseMaxValueMap[m_increaseAttributeName[2]];
	}
	m_pDfcNbText->SetText(FText::FromString(FString::FromInt(curDfc + curIncreaseDfc)));
}

void UTemplateRunesMenu::InitialTitleTexts()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i = 0; i < m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_chTitleTexts[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_enTitleTexts[i]));
		}
	}
}

FCharacterAttributeInfo UTemplateRunesMenu::ReadCharacterAttributeInfo_Implementation(const FString& characterName)
{
	FCharacterAttributeInfo info(0,0,0);
	return info;
}

void UTemplateRunesMenu::FadeOut_Implementation()
{

}
