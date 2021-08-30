// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../../Game/BattleLevelGameModeBase.h"
#include "TTradeCard.h"




void UTTradeCard::NotifyInitial_Implementation()
{

}

void UTTradeCard::ButtonClick()
{

}

void UTTradeCard::ClearTradeCard(UTexture* pBlackTexture)
{
	UObject* pObject3 = m_pButton->WidgetStyle.Normal.GetResourceObject();
	UMaterialInstanceDynamic* pButtonMI = Cast<UMaterialInstanceDynamic>(pObject3);
	pButtonMI->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pBlackTexture);

	UObject* pObject1 = m_pButton->WidgetStyle.Hovered.GetResourceObject();
	UMaterialInstanceDynamic* pButtonMI1 = Cast<UMaterialInstanceDynamic>(pObject1);
	pButtonMI1->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pBlackTexture);

	UObject* pObject2 = m_pButton->WidgetStyle.Pressed.GetResourceObject();
	UMaterialInstanceDynamic* pButtonMI2 = Cast<UMaterialInstanceDynamic>(pObject2);
	pButtonMI2->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pBlackTexture);

	m_cardName = "";
	m_itemSelectID = -1;

	m_pColorImage->SetVisibility(ESlateVisibility::Hidden);
	m_pNbText->SetVisibility(ESlateVisibility::Hidden);
}
