// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/CollisionWarSingleton.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "TemplateItemElement.h"




void UTemplateItemElement::NotifyInitial_Implementation()
{

}

void UTemplateItemElement::ClickButton()
{

}

void UTemplateItemElement::ClearItem()
{
	m_itemName = "NULL";
	m_itemNum = 0;
	m_pItemImage->SetVisibility(ESlateVisibility::Hidden);
	m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
	m_pItemNbText->SetVisibility(ESlateVisibility::Hidden);
	UpdateElement();
}

void UTemplateItemElement::UpdateElement()
{
	FString itemNbString = "x";
	m_itemNbString = itemNbString.Append(FString::FromInt(m_itemNum));
	if (m_itemNum <= 0)
	{
		m_pItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTemplateItemElement::SetElementTexture()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBPC = Cast<ABattleLevelPlayerController>(pPC);

	FString itemName = m_itemName;
	if (m_itemName.Contains("Numeric_"))
	{
		itemName = "NumericCard";
		FString chopNameStr = m_itemName.RightChop(8);
		FString colorStr = chopNameStr.Left(1);
		FString nbStr = chopNameStr.RightChop(2);
		m_pItemNbText->SetText(FText::FromString(nbStr));
		if (colorStr == "D") m_pColorImage->Brush.SetResourceObject(pBPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap[0]);
		else if (colorStr == "C") m_pColorImage->Brush.SetResourceObject(pBPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap[1]);
		else if (colorStr == "H") m_pColorImage->Brush.SetResourceObject(pBPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap[2]);
		else if (colorStr == "S") m_pColorImage->Brush.SetResourceObject(pBPC->m_pBattleMenu->m_pWidgetManager->m_pColorTextureMap[3]);
		m_pItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pColorImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_pItemNbText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		if (!pBPC->m_itemCardInfoMap.Contains(m_itemName)) return;
		UTexture* pTexture = pBPC->m_itemCardInfoMap[m_itemName].pTexture;
		if (pTexture)
		{
			m_pItemImage->Brush.SetResourceObject(pTexture);
			m_pItemImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
			m_pItemImage->SetVisibility(ESlateVisibility::Hidden);
		m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
		m_pItemNbText->SetVisibility(ESlateVisibility::Hidden);
	}
}

