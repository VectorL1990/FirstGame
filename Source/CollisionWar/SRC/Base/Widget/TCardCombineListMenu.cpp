// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "WidgetTree.h"
#include "VerticalBoxSlot.h"
#include "TCardCombineListMenu.h"




void UTCardCombineListMenu::NotifyInitial_Implementation()
{

}

void UTCardCombineListMenu::SwitchDomain(uint8 domain)
{
	if (m_domain == domain) return;
	for (int32 i=0; i<m_pCombineList.Num(); i++)
	{
		m_pCombineList[i]->RemoveFromParent();
		if (m_pCombineList[i]->IsValidLowLevel())
			m_pCombineList[i]->ConditionalBeginDestroy();
	}
	m_pCombineList.Empty();
	m_pVBox->ClearChildren();
	m_transformOverviews.Empty();
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (domain == 0)
	{
		FString actionStr;
		FString overviewStr;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_exploreCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			actionStr = "(1)";
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_communicateCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			actionStr = "(2)";
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_forgeCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			actionStr = "(3)";
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_researchCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			actionStr = "(4)";
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}
		for (int32 i=0; i<m_transformOverviews.Num(); i++)
		{
			UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
			pTextBox->WidgetStyle.Font = m_combineInfoFont;
			pTextBox->SetText(FText::FromString(m_transformOverviews[i]));
			m_pVBox->AddChild(pTextBox);
		}
	}
	else if (domain == 1)
	{
		FString actionStr = "(1)";
		FString overviewStr;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_exploreCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}
		
		for (int32 i = 0; i < m_transformOverviews.Num(); i++)
		{
			UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
			pTextBox->WidgetStyle.Font = m_combineInfoFont;
			pTextBox->SetText(FText::FromString(m_transformOverviews[i]));
			m_pVBox->AddChild(pTextBox);
		}
	}
	else if (m_domain == 2)
	{
		FString actionStr = "(2)";
		FString overviewStr;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_communicateCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}

		for (int32 i = 0; i < m_transformOverviews.Num(); i++)
		{
			UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
			pTextBox->WidgetStyle.Font = m_combineInfoFont;
			pTextBox->SetText(FText::FromString(m_transformOverviews[i]));
			m_pVBox->AddChild(pTextBox);
		}
	}
	else if (m_domain == 3)
	{
		FString actionStr = "(3)";
		FString overviewStr;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_forgeCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}

		for (int32 i = 0; i < m_transformOverviews.Num(); i++)
		{
			UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
			pTextBox->WidgetStyle.Font = m_combineInfoFont;
			pTextBox->SetText(FText::FromString(m_transformOverviews[i]));
			m_pVBox->AddChild(pTextBox);
		}
	}
	else if (m_domain == 4)
	{
		FString actionStr = "(4)";
		FString overviewStr;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter = pSPGM->m_researchCardTransformInfo.CreateConstIterator(); iter; ++iter)
		{
			if (m_pWidgetManager->m_language == "Chinese")
				overviewStr = iter->Value.overview.chDescription;
			else
				overviewStr = iter->Value.overview.enDescription;
			m_transformOverviews.Add(overviewStr.Append(actionStr));
		}

		for (int32 i = 0; i < m_transformOverviews.Num(); i++)
		{
			UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
			pTextBox->WidgetStyle.Font = m_combineInfoFont;
			pTextBox->SetText(FText::FromString(m_transformOverviews[i]));
			m_pVBox->AddChild(pTextBox);
		}
	}

	m_domain = domain;
}

void UTCardCombineListMenu::Search(FString searchStr)
{
	for (int32 i = 0; i < m_pCombineList.Num(); i++)
	{
		m_pCombineList[i]->RemoveFromParent();
		if (m_pCombineList[i]->IsValidLowLevel())
			m_pCombineList[i]->ConditionalBeginDestroy();
	}
	m_pCombineList.Empty();
	m_pVBox->ClearChildren();
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	TArray<FString> results;
	for (int32 i=0; i<m_transformOverviews.Num(); i++)
	{
		if (!m_transformOverviews[i].Contains(searchStr)) continue;
		results.Add(m_transformOverviews[i]);
	}
	for (int32 i = 0; i < results.Num(); i++)
	{
		UMultiLineEditableTextBox* pTextBox = WidgetTree->ConstructWidget<UMultiLineEditableTextBox>(UMultiLineEditableTextBox::StaticClass());
		pTextBox->WidgetStyle.Font = m_combineInfoFont;
		pTextBox->SetText(FText::FromString(results[i]));
		m_pVBox->AddChild(pTextBox);
	}

}

void UTCardCombineListMenu::ClickButton(FString buttonFunction)
{
	if (buttonFunction == "Close")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->DeleteMenu("CardCombineListMenu");
	}
	/*else if (buttonFunction == "SwitchToAll")
	{
		SwitchDomain(0);
	}
	else if (buttonFunction == "SwitchToExplore")
	{
		SwitchDomain(1);
	}
	else if (buttonFunction == "SwitchToCommunication")
	{
		SwitchDomain(2);
	}
	else if (buttonFunction == "SwitchToForge")
	{
		SwitchDomain(3);
	}
	else if (buttonFunction == "SwitchToResearch")
	{
		SwitchDomain(4);
	}*/
}

void UTCardCombineListMenu::LoadShadowActorCards()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	

	for (TMap<FString, FCardTextureAndTags>::TConstIterator iter = pSPGM->m_pPlayCardTextureMap.CreateConstIterator(); iter; ++iter)
	{
		if (!iter->Value.isShadowActorCard) continue;
		bool findTransform = false;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter_1 = pSPGM->m_researchCardTransformInfo.CreateConstIterator(); iter_1; ++iter_1)
		{
			for (int32 i=0; i<iter_1->Value.possibleOutputList.Num(); i++)
			{
				if (iter_1->Value.possibleOutputList[i].outputCardInfo.Num() == 0 || iter_1->Value.possibleOutputList[i].outputCardInfo[0].cardName != iter->Value.cardName)
					continue;
				findTransform = true;
				m_shadowActorCost.Add(iter->Value.cardName, iter_1->Value.cost);
				if (m_pWidgetManager->m_language == "Chinese")
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.chDescription);
				else
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.enDescription);
				break;
			}
		}
		if (findTransform) continue;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter_1 = pSPGM->m_forgeCardTransformInfo.CreateConstIterator(); iter_1; ++iter_1)
		{
			for (int32 i = 0; i < iter_1->Value.possibleOutputList.Num(); i++)
			{
				if (iter_1->Value.possibleOutputList[i].outputCardInfo.Num() == 0 || iter_1->Value.possibleOutputList[i].outputCardInfo[0].cardName != iter->Value.cardName)
					continue;
				findTransform = true;
				m_shadowActorCost.Add(iter->Value.cardName, iter_1->Value.cost);
				if (m_pWidgetManager->m_language == "Chinese")
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.chDescription);
				else
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.enDescription);
				break;
			}
		}
		if (findTransform) continue;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter_1 = pSPGM->m_communicateCardTransformInfo.CreateConstIterator(); iter_1; ++iter_1)
		{
			for (int32 i = 0; i < iter_1->Value.possibleOutputList.Num(); i++)
			{
				if (iter_1->Value.possibleOutputList[i].outputCardInfo.Num() == 0 || iter_1->Value.possibleOutputList[i].outputCardInfo[0].cardName != iter->Value.cardName)
					continue;
				findTransform = true;
				m_shadowActorCost.Add(iter->Value.cardName, iter_1->Value.cost);
				if (m_pWidgetManager->m_language == "Chinese")
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.chDescription);
				else
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.enDescription);
				break;
			}
		}
		if (findTransform) continue;
		for (TMap<FString, FCardTransformInfo>::TConstIterator iter_1 = pSPGM->m_exploreCardTransformInfo.CreateConstIterator(); iter_1; ++iter_1)
		{
			for (int32 i = 0; i < iter_1->Value.possibleOutputList.Num(); i++)
			{
				if (iter_1->Value.possibleOutputList[i].outputCardInfo.Num() == 0 || iter_1->Value.possibleOutputList[i].outputCardInfo[0].cardName != iter->Value.cardName)
					continue;
				findTransform = true;
				m_shadowActorCost.Add(iter->Value.cardName, iter_1->Value.cost);
				if (m_pWidgetManager->m_language == "Chinese")
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.chDescription);
				else
					m_shadowActorOvervieMap.Add(iter->Value.cardName, iter_1->Value.overview.enDescription);
				break;
			}
		}
	}
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	for (TMap<FString, FString>::TConstIterator iter = m_shadowActorOvervieMap.CreateConstIterator(); iter; ++iter)
	{
		UTemplateRuneElement* pRuneElement = CreateWidget<UTemplateRuneElement>(pGI, m_pWidgetManager->m_widgetClassMap["CardCombineListElement"]);
		pRuneElement->NotifyInitial();
		UObject* pObject = pRuneElement->m_pRuneImage->Brush.GetResourceObject();
		UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pObject);
		FString paramName = "ButtonTexture";
		UTexture* pTexture = pSPGM->m_pPlayCardTextureMap[iter->Key].pTexture;
		pMI->SetTextureParameterValue(FName(*paramName), pTexture);
		if (m_pWidgetManager->m_language == "Chinese")
			pRuneElement->m_pRuneName->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[iter->Key].chCardName));
		else
			pRuneElement->m_pRuneName->SetText(FText::FromString(pSPGM->m_pPlayCardTextureMap[iter->Key].cardName));
		FString buttonFunction = "CardCombineElement_" + iter->Key;
		pRuneElement->m_buttonFunction = buttonFunction;
		m_pSACardElements.Add(pRuneElement);
		UPanelSlot* pSlot = m_pVBox->AddChild(pRuneElement);
		UVerticalBoxSlot* pVBoxSlot = Cast<UVerticalBoxSlot>(pSlot);
		pVBoxSlot->SetPadding(m_elementPadding);
	}
}
