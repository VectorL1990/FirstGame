// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "SingleProgressGameMode.h"
#include "../../Base/SingleProgress/SingleProgressPlayerController.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "ActionCard.h"



void AActionCard::Tick(float DeltaTime)
{
	
}

void AActionCard::SetupActionCard(UStaticMeshComponent* pBaseMesh, UTextRenderComponent* pCardName)
{
	m_pBaseMesh = pBaseMesh;
	m_pCardName = pCardName;
}

void AActionCard::InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName)
{
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (cardName == "Thoughts")
	{
		m_cardName = "Thoughts";
		m_actionName = "Thoughts";
		m_actionType = 0;
	}
	else if (cardName == "Explore")
	{
		m_cardName = "Explore";
		m_actionName = "Explore";
		m_actionType = 1;
	}
	else if (cardName == "Communication")
	{
		m_cardName = "Communication";
		m_actionName = "Communication";
		m_actionType = 2;
	}
	else if (cardName == "Forge")
	{
		m_cardName = "Forge";
		m_actionName = "Forge";
		m_actionType = 3;
	}
	else if (cardName == "Research")
	{
		m_cardName = "Research";
		m_actionName = "Research";
		m_actionType = 4;
	}
	else if (cardName.Contains("Event_"))
	{
		m_cardName = cardName;
		m_actionName = cardName.RightChop(6);
		m_actionType = 5;
		if (m_pCardName)
		{
			m_pCardName->SetVisibility(true);
			m_pCardName->SetText(m_actionName);
		}
	}
	ReadCardName(m_cardName);
	if (pSPGM->m_pPlayCardTextureMap.Contains(m_actionName))
	{
		/ *UMaterialInterface* pMatInterface = m_pBaseMesh->GetMaterial(0);
		UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pMatInterface);
		pMI->SetTextureParameterValue(FName(TEXT("MaterialExpressionTextureSampleParameter2D_2")), pSPGM->m_pPlayCardTextureMap[m_actionName].pTexture);* /

		UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pMatActionCardType);
		pMI->SetTextureParameterValue(FName(TEXT("MaterialExpressionTextureSampleParameter2D_2")), pSPGM->m_pPlayCardTextureMap[m_actionName].pTexture);
		m_pBaseMesh->SetMaterial(0, pMI);
	}
	if (m_pBaseMesh) m_pBaseMesh->ComponentTags.Add(FName(TEXT("ActionCard")));
	if (pSPGM->m_actionDescription.Contains(m_actionType))
	{
		m_chActionDescription = pSPGM->m_actionDescription[m_actionType].chDescription;
		m_actionDescription = pSPGM->m_actionDescription[m_actionType].enDescription;
	}
	m_cardType = cardType;

	NotifyInitialWidget();
	m_pActionCardInfo->NotifyInitial();*/
}

void AActionCard::NotifyInitialWidget_Implementation()
{

}

