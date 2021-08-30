// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "UniformGridSlot.h"
#include "CanvasPanelSlot.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "TDrawCardMenu.h"




void UTDrawCardMenu::NotifyInitial_Implementation()
{

}

void UTDrawCardMenu::NotifyDemonstrateString_Implementation(uint8 demoNb)
{

}

void UTDrawCardMenu::AddDrawCardToMenu(int32 drawCardNb, uint8 drawCardColor, int32 row, int32 col)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	UTActionCard* pDrawCard = CreateWidget<UTActionCard>(pPC, m_drawCardBackClass);
	pDrawCard->NotifyInitial();
	//pDrawCard->InitialActionCard(drawCardNb, drawCardColor, "NULL", NULL);
	pDrawCard->m_cardName = "NULL";
	pDrawCard->m_nb = drawCardNb;
	pDrawCard->m_color = drawCardColor;
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, m_pDrawCardMat);
	FString paramStr1 = "FlipOrFade";
	FString paramStr2 = "FrontOrBack";
	pMI->SetScalarParameterValue(FName(*paramStr1), 0);
	pMI->SetScalarParameterValue(FName(*paramStr2), 0);
	pDrawCard->m_pPlayCardImage->SetBrushFromMaterial(pMI);

	UPanelSlot* pPanelSlot = m_pCardGridPanel->AddChild(pDrawCard);
	UUniformGridSlot* pUniformSlot = Cast<UUniformGridSlot>(pPanelSlot);
	pUniformSlot->SetColumn(col);
	pUniformSlot->SetRow(row);

	pDrawCard->SetupFadeInTimer(0, true);
}

void UTDrawCardMenu::AddPlayerCardToMenu(int32 drawCardNb, uint8 drawCardColor)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	UTActionCard* pPlayerDrawCard = CreateWidget<UTActionCard>(pPC, m_drawCardBackClass);
	pPlayerDrawCard->NotifyInitial();
	//pDrawCard->InitialActionCard(drawCardNb, drawCardColor, "NULL", NULL);
	pPlayerDrawCard->m_cardName = "NULL";
	pPlayerDrawCard->m_nb = drawCardNb;
	pPlayerDrawCard->m_color = drawCardColor;
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, m_pDrawCardMat);
	FString paramStr1 = "FlipOrFade";
	FString paramStr2 = "FrontOrBack";
	pMI->SetScalarParameterValue(FName(*paramStr1), 0);
	pMI->SetScalarParameterValue(FName(*paramStr2), 1);
	pPlayerDrawCard->m_pPlayCardImage->SetBrushFromMaterial(pMI);
	UPanelSlot* pPanelSlot = m_pCanvasPanel->AddChild(pPlayerDrawCard);
	UCanvasPanelSlot* pCanvasPanelSlot = Cast<UCanvasPanelSlot>(pPanelSlot);
	FAnchors anchor;
	anchor.Maximum = FVector2D(0.5, 0.5);
	anchor.Minimum = FVector2D(0.5, 0.5);
	pCanvasPanelSlot->SetAnchors(anchor);
	pCanvasPanelSlot->SetAlignment(FVector2D(0.5, 0.5));
	pCanvasPanelSlot->SetPosition(m_playerDrawCardPos);

	pPlayerDrawCard->SetupFadeInTimer(0, true);
}
