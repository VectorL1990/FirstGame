// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../SingleProgress/SingleProgressPlayerController.h"
#include "../Battle/BattleLevelPlayerController.h"
#include "../../Game/Battle/RoguelikeBattleGameMode.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "CanvasPanelSlot.h"
#include "TTutorialMenu.h"




void UTTutorialMenu::NotifyInitial_Implementation()
{

}

void UTTutorialMenu::ClickButton(const FString& buttonFunction)
{
	if (buttonFunction == "NextTip")
	{
		if (m_curTutorialStep >= m_tutorialSerial.tutorialSteps.Num()) return;
		m_curTutorialMiniStep += 1;
		if (m_curTutorialMiniStep >= m_tutorialSerial.tutorialSteps[m_curTutorialStep].chDescriptions.Num())
		{
			//说明这一小步都走完了
			m_curTutorialStep += 1;
			if (m_curTutorialStep >= m_tutorialSerial.tutorialSteps.Num())
			{
				//说明所有步都走完了
				return;
			}
			else
			{
				//更新大步
				m_curTutorialMiniStep = 0;
				m_pMediaPlayer->Close();
				m_pDescriptionBox->SetText(FText::FromString(""));
				if (m_tutorialSerial.tutorialSteps[m_curTutorialStep].pMediaSource)
				{
					m_pMediaPlayer->OpenSource(m_tutorialSerial.tutorialSteps[m_curTutorialStep].pMediaSource);
					/*UTFlipImage* pFlipImage = CreateWidget<UTFlipImage>(UGameplayStatics::GetPlayerController(this, 0), m_tutorialSerial.tutorialSteps[m_curTutorialStep].pFlipImageClass);
					UPanelSlot* pSlot = m_pCanvasPanel->AddChild(pFlipImage);
					UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
					pCanvasSlot->SetSize(m_FlipImageSize);
					pCanvasSlot->SetPosition(m_FlipImagePos);
					m_pTutorialImage = pFlipImage;*/
				}
				if (m_tutorialSerial.tutorialSteps[m_curTutorialStep].chDescriptions.Num() > 0)
				{
					if (m_pWidgetManager->m_language == "Chinese")
						m_pDescriptionBox->SetText(FText::FromString(m_tutorialSerial.tutorialSteps[m_curTutorialStep].chDescriptions[0]));
					else
						m_pDescriptionBox->SetText(FText::FromString(m_tutorialSerial.tutorialSteps[m_curTutorialStep].enDescriptions[0]));
				}
			}
		}
		else
		{
			/*if (m_curTutorialMiniStep < m_tutorialSerial.tutorialSteps[m_curTutorialStep].pFlipImageClasses.Num())
			{
				if (m_pTutorialImage)
				{
					m_pTutorialImage->RemoveFromParent();
					if (m_pTutorialImage->IsValidLowLevel()) m_pTutorialImage->ConditionalBeginDestroy();
					//m_pTutorialImage = NULL;
				}
				UTFlipImage* pFlipImage = CreateWidget<UTFlipImage>(this, m_tutorialSerial.tutorialSteps[m_curTutorialStep].pFlipImageClasses[m_curTutorialMiniStep]);
				UPanelSlot* pSlot = m_pCanvasPanel->AddChild(pFlipImage);
				UCanvasPanelSlot* pCanvasSlot = Cast<UCanvasPanelSlot>(pSlot);
				pCanvasSlot->SetSize(m_FlipImageSize);
				pCanvasSlot->SetPosition(m_FlipImagePos);
				m_pTutorialImage = pFlipImage;
			}*/
			if (m_curTutorialMiniStep < m_tutorialSerial.tutorialSteps[m_curTutorialStep].chDescriptions.Num())
			{
				if (m_pWidgetManager->m_language == "Chinese")
					m_pDescriptionBox->SetText(FText::FromString(m_tutorialSerial.tutorialSteps[m_curTutorialStep].chDescriptions[m_curTutorialMiniStep]));
				else
					m_pDescriptionBox->SetText(FText::FromString(m_tutorialSerial.tutorialSteps[m_curTutorialStep].enDescriptions[m_curTutorialMiniStep]));
			}
		}
	}
	else if (buttonFunction == "Close")
	{
		//先添加当前的pCWGI中的已完成教程名
		//再将GM中的当前教程名设置为NULL
		//然后隐藏教程按钮
		
		if (m_type == 0)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			if (pSPGM->m_isInDiceTutorialState) pSPGM->m_isInDiceTutorialState = false;
			else if (pSPGM->m_isInTheorizeTutorialState) pSPGM->m_isInTheorizeTutorialState = false;
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ASingleProgressPlayerController* pSPPC = Cast<ASingleProgressPlayerController>(pPC);
			pSPPC->m_pTutorialSerialMenu = NULL;
		}
		else if (m_type == 1)
		{
			
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ABattleLevelPlayerController* pBLC = Cast<ABattleLevelPlayerController>(pPC);
			pBLC->m_pTutorialSerialMenu = NULL;
			if (pBLC->m_isGamePaused) pBLC->PauseOrUnPauseGame();
		}

		
		RemoveFromParent();
		if (IsValidLowLevel()) ConditionalBeginDestroy();
		
	}
}

void UTTutorialMenu::InitialTitleTexts()
{
	if (m_pWidgetManager->m_language == "Chinese")
	{
		for (int32 i=0; i<m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_chTitleTexts[i]));
		}
	}
	else
	{
		for (int32 i = 0; i < m_pTitleTexts.Num(); i++)
		{
			m_pTitleTexts[i]->SetText(FText::FromString(m_enTitleTexts[i]));
		}
	}
}
