// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "SingleProgressGameMode.h"
#include "NumericCard.h"




void ANumericCard::InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, pSPGM->m_pMatCardAttachment);
	if (pSPGM->m_pColorTextureMap.Contains(color))
		pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pSPGM->m_pColorTextureMap[color]);
	m_pColorMesh1->SetMaterial(0, pMI);
	m_pColorMesh2->SetMaterial(0, pMI);
	m_pNbRender->SetText(FText::FromString(FString::FromInt(nb)));
	m_cardType = cardType;
	m_nb = nb;
	m_color = color;
	if (m_pBaseMesh)
	{
		m_pBaseMesh->ComponentTags.Add(FName(TEXT("PlayCard")));
		m_pBaseMesh->ComponentTags.Add(FName(TEXT("NumericCard")));
		if (nb != -1)
		{
			FString nbStr = FString(TEXT("Number")).Append(FString::FromInt(nb));
			m_pBaseMesh->ComponentTags.Add(FName(*nbStr));
			FString colorStr;
			FString colorType;
			if (color == 0)
			{
				colorStr = FString(TEXT("Color")).Append(FString(TEXT("Diamond")));
				colorType = "ColorRed";
			}
			else if (color == 1)
			{
				colorStr = FString(TEXT("Color")).Append(FString(TEXT("Club")));
				colorType = "ColorBlack";
			}
			else if (color == 2)
			{
				colorStr = FString(TEXT("Color")).Append(FString(TEXT("Heart")));
				colorType = "ColorRed";
			}
			else if (color == 3)
			{
				colorStr = FString(TEXT("Color")).Append(FString(TEXT("Spade")));
				colorType = "ColorBlack";
			}
			m_pBaseMesh->ComponentTags.Add(FName(*colorStr));
			m_tags.Add(colorStr);
			m_tags.Add(colorType);
			m_tags.Add(nbStr);
		}
	}
	m_tags.Add("NumericCard");
}

void ANumericCard::SetupNumericCard(UStaticMeshComponent* pBaseMesh, UStaticMeshComponent* pColorMesh1, UStaticMeshComponent* pColorMesh2, UTextRenderComponent* pNb)
{
	if (!pColorMesh1 || !pColorMesh2 || !pNb || !pBaseMesh) return;
	m_pBaseMesh = pBaseMesh;
	m_pColorMesh1 = pColorMesh1;
	m_pColorMesh2 = pColorMesh2;
	m_pNbRender = pNb;
}
