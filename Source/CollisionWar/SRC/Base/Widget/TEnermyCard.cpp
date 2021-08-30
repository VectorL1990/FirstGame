// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "WidgetTree.h"
#include "TEnermyCard.h"




void UTEnermyCard::NotifyInitial_Implementation()
{

}

void UTEnermyCard::SetEnermyTexture(UTexture* pTexture, UMaterialInstance* pMI)
{
	if (!m_pEnermyImage || !pTexture) return;
	UMaterialInstanceDynamic* pMIDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pMI);
	pMIDynamic->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pTexture);
	m_pEnermyImage->Brush.SetResourceObject(pMIDynamic);
}

void UTEnermyCard::AddStateToCard(FString stateName, UMaterialInstance* pMI)
{
	if (m_stateList.Contains(stateName)) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(pPC);
	if (!pBLPC->m_stateCardInfoMap.Contains(stateName)) return;
	UTexture* pTexture = pBLPC->m_stateCardInfoMap[stateName].pTexture;
	UImage* pImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	UMaterialInstanceDynamic* pMIDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pMI);
	pMIDynamic->SetTextureParameterValue(FName(TEXT("ButtonTexture")), pTexture);
	pImage->Brush.SetResourceObject(pMIDynamic);
	m_pScrollBox->AddChild(pImage);
	m_stateList.Add(stateName);
}

void UTEnermyCard::RemoveState(FString stateName)
{
	if (!m_stateList.Contains(stateName)) return;
	int32 nb = m_stateList.Find(stateName);
	m_pScrollBox->RemoveChildAt(nb);
	m_stateList.Remove(stateName);
}
