// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Common/CollisionWarSingleton.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TCombineElement.h"




void UTCombineElement::NotifyInitial_Implementation()
{

}

void UTCombineElement::ClickButton(FString buttonFunction)
{
	m_buttonClickDelegate.Broadcast(buttonFunction);
}

void UTCombineElement::ResetCombineElement()
{
	m_pElementImage->SetVisibility(ESlateVisibility::Hidden);
	m_itemNb = 0;
	SetText();
}

void UTCombineElement::SetText()
{
	FString text = FString::FromInt(m_itemNb);
	m_pTextBlock->SetText(FText::FromString(text));
}

void UTCombineElement::ModifyElementNb(bool addOrSub)
{
	if (addOrSub)
	{
		int32 addNb = m_itemNb + 1;
		if (addNb >= 99) m_itemNb = 99;
		else m_itemNb = addNb;
	}
	else
	{
		int32 subNb = m_itemNb - 1;
		if (subNb <= 0) m_itemNb = 0;
		else m_itemNb = subNb;
	}
	SetText();
}

