// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../CollisionWarGameInstance.h"
#include "TemplateCharacterStateElement.h"




void UTemplateCharacterStateElement::NotifyInitial_Implementation()
{

}

void UTemplateCharacterStateElement::InitialCharacterStateElement(UImage* pImage)
{
	m_pImage = pImage;
}

void UTemplateCharacterStateElement::LoadStateImage()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_stateCardInfoMap.Contains(m_stateName)) return;
	m_pImage->Brush.SetResourceObject(pBLPC->m_stateCardInfoMap[m_stateName].pTexture);
	FLinearColor linearColor(pBLPC->m_stateCardInfoMap[m_stateName].color);
	m_pImage->SetColorAndOpacity(linearColor);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (pCWGI->m_language == "Chinese")
		m_pStateName->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[m_stateName].chCardName));
	else
		m_pStateName->SetText(FText::FromString(pBLPC->m_stateCardInfoMap[m_stateName].cardName));
}
