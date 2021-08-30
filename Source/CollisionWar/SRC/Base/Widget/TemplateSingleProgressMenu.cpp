// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../../Common/SPEventFunctionLib.h"
#include "WidgetTree.h"
#include "VerticalBoxSlot.h"
#include "HorizontalBoxSlot.h"
#include "CanvasPanelSlot.h"
#include "TemplateSingleProgressMenu.h"




void UTemplateSingleProgressMenu::NotifyInitial_Implementation()
{

}

void UTemplateSingleProgressMenu::FadeOut_Implementation()
{

}

void UTemplateSingleProgressMenu::ButtonClick(const FString& buttonFunction)
{
	//m_buttonClickDelegate.Broadcast(buttonFunction);
	if (buttonFunction == "Button_Progress")
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSGM = Cast<ASingleProgressGameMode>(pGM);
		pSGM->ProceedNextGame();
	}
	else if (buttonFunction == "Mission")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		UTemplateEventSystem* pMissionMenu = CreateWidget<UTemplateEventSystem>(UGameplayStatics::GetGameInstance(this), pSPPC->m_pWidgetManager->m_widgetClassMap["MissionMenu"]);
		pMissionMenu->NotifyInitial();
		pMissionMenu->AddToViewport();
		pSPPC->m_pMissionMenu = pMissionMenu;
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSGM = Cast<ASingleProgressGameMode>(pGM);
		if (m_pMissionArrow) m_pMissionArrow->RemoveFromParent();
		if (m_pMissionArrow->IsValidLowLevel())
		{
			m_pMissionArrow->ConditionalBeginDestroy();
			m_pMissionArrow = NULL;
		}
		if (pSGM->m_missionList.missionIndexList.Num() <= 0) return;
		if (m_pWidgetManager->m_language == "Chinese")
			pMissionMenu->LoadMissionText(pSGM->m_missionList.chDescription[pSGM->m_curMissionIndexFrameKeyNb]);
		else
			pMissionMenu->LoadMissionText(pSGM->m_missionList.enDescription[pSGM->m_curMissionIndexFrameKeyNb]);
		if (pSGM->m_isInTutorial)
		{
			if (pSGM->m_tutorialSteps.Num() > 0)
			{
				FString tutorialStepName = "ClickMission";
				if (pSGM->m_tutorialSteps[0].operationName == tutorialStepName)
					pSGM->DeleteTutorialStep();
			}
			/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
			else
				pSPGM->DeleteTutorialStep();*/
		}
	}
	else if (buttonFunction == "ShowCardFunctionList")
	{
		NotifyShowCardFunctionList();
		m_showCardFunctionMenuState = 1;
	}
	else if (buttonFunction == "CloseCardFunctionList")
	{
		NotifyHideCardFunctionList();
		m_showCardFunctionMenuState = 1;
	}
	else if (buttonFunction == "TutorialSerial")
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
		pSPPC->LoadTutorialSerialMenu();
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_curTutorialName)) pCWGI->m_doneTutorialSteps.Add(pSPGM->m_curTutorialName);
		pSPGM->m_curTutorialName = "NULL";
		m_pTutorialButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTemplateSingleProgressMenu::UpdateCardNbText()
{
	/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	int32 playCardNb = pSPGM->m_pPlayCards.Num() - pSPGM->m_pActionCards.Num() - pSPGM->m_pNumericCards.Num();
	int32 eventCardNb = 0;
	for (int32 i=0; i< pSPGM->m_pActionCards.Num(); i++)
	{
		if (pSPGM->m_pActionCards[i]->m_actionType == 5)
			eventCardNb += 1;
	}
	FString playCardNbText = FString::FromInt(playCardNb) + "/" + FString::FromInt(pSPGM->m_maxPlayCardNb);
	FString actionCardNbText = FString::FromInt(pSPGM->m_pActionCards.Num() - eventCardNb) + "/" + FString::FromInt(pSPGM->m_maxActionCardNb - 1);
	m_pCurCardAndMaxNb->SetText(FText::FromString(playCardNbText));
	m_pCurActionCardAndMaxNb->SetText(FText::FromString(actionCardNbText));*/
}

void UTemplateSingleProgressMenu::UpdateSPProgressImage(int32 curProgress, int32 curProgressLayer)
{
	//if (!m_pSPProgressBarImage) return;
	if (curProgress == 0)
	{
		//说明是复原，如当前的行动数已经大于最大行动数，需要复原
		for (int32 i=0; i< m_pProgressBalls.Num(); i++)
		{
			UMaterialInstanceDynamic* pBallDMI = m_pProgressBalls[i]->m_pImage->GetDynamicMaterial();
			pBallDMI->SetTextureParameterValue(FName("Front"), m_pDefaultProgressBallTexture);
		}
	}
	else
	{
		for (int32 i = 0; i < curProgress; i++)
		{
			UMaterialInstanceDynamic* pBallDMI = m_pProgressBalls[i]->m_pImage->GetDynamicMaterial();
			pBallDMI->SetTextureParameterValue(FName("Front"), m_pProgressBallTexture);
		}
	}
	for (int32 i=0; i<curProgressLayer; i++)
	{
		UMaterialInstanceDynamic* pBallDMI = m_pLayerProgressBalls[i]->m_pImage->GetDynamicMaterial();
		pBallDMI->SetTextureParameterValue(FName("Front"), m_pLayerProgressBallTexture);
	}
}

void UTemplateSingleProgressMenu::AddBossBattleProgressBall()
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	UTEnergyBall* pProgressBall = CreateWidget<UTEnergyBall>(pPC, m_pProgressBallClass);
	pProgressBall->NotifyInitial();
	UPanelSlot* pSlot = m_pProgressBoxHBox->AddChild(pProgressBall);
	UHorizontalBoxSlot* pHSlot = Cast<UHorizontalBoxSlot>(pSlot);
	FSlateChildSize slotSize;
	slotSize.SizeRule = ESlateSizeRule::Fill;
	slotSize.Value = 1;
	pHSlot->SetSize(slotSize);
	m_pProgressBalls.Add(pProgressBall);
}

void UTemplateSingleProgressMenu::ShowDemoText(const FString& demoText)
{
	int32 curDemoNb = 0;
	while (true)
	{
		if (!m_pDemoTexts.Contains(curDemoNb)) break;
		curDemoNb += 1;
	}
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	UTemplateMenuTitle* pTitle = CreateWidget<UTemplateMenuTitle>(pPC, m_pDemoTextClass);
	pTitle->NotifyInitial();
	pTitle->m_pTitle->SetText(FText::FromString(demoText));
	UPanelSlot* pSlot = m_pDemoTextCanvasPanel->AddChild(pTitle);
	UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
	FAnchors anchor;
	anchor.Maximum = FVector2D(0.5, 0.5);
	anchor.Minimum = FVector2D(0.5, 0.5);
	pCanvasSlot->SetAnchors(anchor);
	pCanvasSlot->SetAlignment(FVector2D(0.5, 0.5));
	pCanvasSlot->SetPosition(FVector2D(0, curDemoNb*m_demoTextInterval));
	m_pDemoTexts.Add(curDemoNb, pTitle);
	//m_pDemoText->SetText(FText::FromString(demoText));
	pTitle->NotifyShowDemoText();
}

void UTemplateSingleProgressMenu::NotifyHideEventCardDescription_Implementation()
{

}

void UTemplateSingleProgressMenu::NotifyShowEventCardDescription_Implementation()
{

}

void UTemplateSingleProgressMenu::NotifyShowMissionArrow_Implementation()
{

}

void UTemplateSingleProgressMenu::NotifyHideCardFunctionList_Implementation()
{

}

void UTemplateSingleProgressMenu::NotifyShowCardFunctionList_Implementation()
{

}

