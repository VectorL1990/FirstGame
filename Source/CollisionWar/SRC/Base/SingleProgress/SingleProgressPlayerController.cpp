// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/SingleProgress/SingleProgressGameMode.h"
#include "../../Game/SingleProgress/ActionCard.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../NormalCameraManager.h"
#include "../CollisionWarGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "FileManagerGeneric.h"
#include "CanvasPanelSlot.h"
#include "SingleProgressPlayerController.h"



void ASingleProgressPlayerController::Tick(float DeltaSeconds)
{
	if (m_curDiceSkillLeftTime > 0)
	{
		m_curDiceSkillLeftTime -= DeltaSeconds;
		if (m_curDiceSkillLeftTime <= 0) m_curDiceSkillLeftTime = 0;
	}
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (!pSPGM->m_pControlCharacter) return;
	FVector curCharacterLoc = pSPGM->m_pControlCharacter->GetActorLocation();
	if (pSPGM->m_gameState == 2)
	{
		if (m_isPressLeftKey && !m_isPressRightKey && (curCharacterLoc.X - m_HMoveV > m_theorizeMovableLBPoint.X)) curCharacterLoc.X -= m_HMoveV;
		else if (!m_isPressLeftKey && m_isPressRightKey && (curCharacterLoc.X + m_HMoveV < m_theorizeMovableRTPoint.X)) curCharacterLoc.X += m_HMoveV;

		if (m_isPressUpKey && !m_isPressDownKey && (curCharacterLoc.Y - m_VMoveV > m_theorizeMovableLBPoint.Y)) curCharacterLoc.Y -= m_VMoveV;
		else if (!m_isPressUpKey && m_isPressDownKey && (curCharacterLoc.Y + m_VMoveV < m_theorizeMovableRTPoint.Y)) curCharacterLoc.Y += m_VMoveV;
	}
	else if (pSPGM->m_gameState == 1)
	{
		if (m_isPressLeftKey && !m_isPressRightKey && (curCharacterLoc.X - m_HMoveV > m_diceMovableLBPoint.X)) curCharacterLoc.X -= m_HMoveV;
		else if (!m_isPressLeftKey && m_isPressRightKey && (curCharacterLoc.X + m_HMoveV < m_diceMovableRTPoint.X)) curCharacterLoc.X += m_HMoveV;

		if (m_isPressUpKey && !m_isPressDownKey && (curCharacterLoc.Y - m_VMoveV > m_diceMovableLBPoint.Y)) curCharacterLoc.Y -= m_VMoveV;
		else if (!m_isPressUpKey && m_isPressDownKey && (curCharacterLoc.Y + m_VMoveV < m_diceMovableRTPoint.Y)) curCharacterLoc.Y += m_VMoveV;
	}
	else if (pSPGM->m_gameState == 0 || pSPGM->m_gameState == 5)
	{
		if (m_isPressLeftKey && !m_isPressRightKey && (curCharacterLoc.X - m_HMoveV > m_movableLBPoint.X)) curCharacterLoc.X -= m_HMoveV;
		else if (!m_isPressLeftKey && m_isPressRightKey && (curCharacterLoc.X + m_HMoveV < m_movableRTPoin.X)) curCharacterLoc.X += m_HMoveV;

		if (m_isPressUpKey && !m_isPressDownKey && (curCharacterLoc.Y - m_VMoveV > m_movableLBPoint.Y)) curCharacterLoc.Y -= m_VMoveV;
		else if (!m_isPressUpKey && m_isPressDownKey && (curCharacterLoc.Y + m_VMoveV < m_movableRTPoin.Y)) curCharacterLoc.Y += m_VMoveV;
	}
	/*else if (pSPGM->m_gameState == 6)
	{
		if (m_isPressLeftKey && !m_isPressRightKey) curCharacterLoc.X -= m_HMoveV;
		else if (!m_isPressLeftKey && m_isPressRightKey) curCharacterLoc.X += m_HMoveV;

		if (m_isPressUpKey && !m_isPressDownKey) curCharacterLoc.Y -= m_VMoveV;
		else if (!m_isPressUpKey && m_isPressDownKey) curCharacterLoc.Y += m_VMoveV;
	}*/
	pSPGM->m_pControlCharacter->SetActorLocation(curCharacterLoc);

	DealTickEvent();
}

void ASingleProgressPlayerController::GetControl()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	AActor* pActor = pSPGM->GetPrefabActorByTag(FName(TEXT("CameraViewTarget")));
	if (!pActor) return;
	pSPGM->m_pControlCharacter = Cast<ACamCharacter>(pActor);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	pSPGM->m_pControlCharacter->SetParticleBySceneType(pCWGI->m_weatherType);
	Possess(pSPGM->m_pControlCharacter);
	pSPGM->m_pControlCharacter->ReadDayNightDLYaw(pCWGI->m_curPlayerSPInfo.curProgress);
}

void ASingleProgressPlayerController::PauseOrUnPauseGame()
{
	if (m_isPauseMenuOn) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (!pGameMode) return;
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGameMode);
	if (pSPGM->m_tickFlag)
	{
		pSPGM->StopTick();
		//UGameplayStatics::SetGamePaused(this, true);
		if (m_pSPMenu) m_pSPMenu->m_pPauseText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		pSPGM->ResumeTick();
		//UGameplayStatics::SetGamePaused(this, false);
		if (m_pSPMenu) m_pSPMenu->m_pPauseText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASingleProgressPlayerController::Client_ApplyMoveLeft()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressLeftKey = true;
}

void ASingleProgressPlayerController::ReleaseLeftKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressLeftKey = false;
}

void ASingleProgressPlayerController::Client_ApplyMoveRight()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressRightKey = true;
}

void ASingleProgressPlayerController::ReleaseRightKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressRightKey = false;
}

void ASingleProgressPlayerController::Client_ApplyMoveUp()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressUpKey = true;
}

void ASingleProgressPlayerController::ReleaseUpKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressUpKey = false;
}

void ASingleProgressPlayerController::Client_ApplyMoveDown()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressDownKey = true;
}

void ASingleProgressPlayerController::ReleaseDownKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(GetWorld());
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_isPressDownKey = false;
}

void ASingleProgressPlayerController::DealLeftClickDownEvent()
{
	if (m_pTransitionMenu)
	{
		if (m_pTransitionMenu->m_pWidgetManager->m_language == "Chinese")
		{
			if (m_pTransitionMenu->m_curDescriptionNb >= m_pTransitionMenu->m_chDescriptions.Num() - 1)
			{
				m_pTransitionMenu->NotifyFadeOut();
				m_pTransitionMenu = NULL;
			}
			else
			{
				m_pTransitionMenu->m_curDescriptionNb += 1;
				m_pTransitionMenu->m_pDescriptionBox->SetText(FText::FromString(m_pTransitionMenu->m_chDescriptions[m_pTransitionMenu->m_curDescriptionNb]));
			}
		}
		else
		{
			if (m_pTransitionMenu->m_curDescriptionNb >= m_pTransitionMenu->m_enDescriptions.Num() - 1)
			{
				m_pTransitionMenu->NotifyFadeOut();
				m_pTransitionMenu = NULL;
			}
			else
			{
				m_pTransitionMenu->m_curDescriptionNb += 1;
				m_pTransitionMenu->m_pDescriptionBox->SetText(FText::FromString(m_pTransitionMenu->m_chDescriptions[m_pTransitionMenu->m_curDescriptionNb]));
			}
		}
		return;
	}
	if (m_isWidgetClick)
	{
		//m_isWidgetClick = false;
		return;
	}
	if (m_gameState == 0)
	{
		FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery4, false, hitResult);
		bool hitEventCard = false;
		if (hitResult.bBlockingHit && hitResult.GetComponent() && !m_pActionPanel)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
			m_mouseClickDownLoc = hitResult.Location;
			m_pMouseClickDownHitComponent = hitResult.GetComponent();
			if (hitResult.GetComponent()->ComponentHasTag(FName("EventCard")))
			{
				AEventCard* pEventCard = Cast<AEventCard>(hitResult.GetActor());
				for (TMap<uint8, FEventCardInfoList>::TConstIterator iter = pSPGM->m_allEventInfoMap.CreateConstIterator(); iter; ++iter)
				{
					for (int32 i=0; i<iter->Value.eventCardInfoList.Num(); i++)
					{
						if (iter->Value.eventCardInfoList[i].SAName != pEventCard->m_nodeName) continue;
						pSPGM->m_pEventNodeManager->m_eventCardInfo = iter->Value.eventCardInfoList[i];
						//这是有大量故事性文字的逻辑代码，现在改成只有一句
						//pSPGM->m_pEventNodeManager->m_curTreeNode = iter->Value.eventCardInfoList[i].allNodes[0];
						m_hasShownActionNodeDescription = true;
						m_pActionPanel = UWidgetBlueprintFunctionLibrary::CreateActionPanel(m_pWidgetManager, m_pEventNodeManager, pEventCard->m_eventCardInfo.defaultActionType);
						m_pActionPanel->AddToViewport();
						pSPGM->NotifyPlaySound2DByName("ClickActionCard");
						break;
					}
				}
			}
			if (pSPGM->m_pControlCharacter)
			{
				pSPGM->m_pControlCharacter->m_isDayOrNight = false;
				pSPGM->m_pControlCharacter->m_shouldRotatorDayNight = true;
			}
			return;
		}
		if (m_pActionPanel)
		{
			//这是有大量故事性文字的逻辑代码，现在改成只有一句
			/*if (m_pEventNodeManager->m_curTreeNode.descriptionAndChoice.choices.Num() <= 0 && m_pEventNodeManager->m_curTreeNode.childrenNodeNbs.Num() > 0)
			{
				//只有当没有选项并且子节点还存在的情况下，才能更新
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, "DealLeftClick set curtreenode");
				m_pEventNodeManager->m_curTreeNode = m_pEventNodeManager->m_eventCardInfo.allNodes[m_pEventNodeManager->m_curTreeNode.childrenNodeNbs[0]];
				m_pActionPanel->UpdateActionPanelInfo(m_pEventNodeManager);
			}
			else if (m_pEventNodeManager->m_curTreeNode.childrenNodeNbs.Num() <= 0)
			{
				//说明此时已经没有子节点了，触发对应的事件
				AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
				ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
				if (m_pEventNodeManager->m_eventCardInfo.actionChoiceMap.Num() <= 1) pSPGM->UpdateEventCardAction(false);
				else pSPGM->UpdateEventCardAction(true);
				m_pEventNodeManager->ResetNodeManager();
			}*/
			if (m_hasShownActionNodeDescription)
			{
				m_hasShownActionNodeDescription = false;
				AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
				ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
				pSPGM->UpdateEventCardAction(false);
				m_pEventNodeManager->ResetNodeManager();
			}
		}
		
	}
	else if (m_gameState == 1)
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pSPGM->m_diceAndTheorizeCanAction) return;
		FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, hitResult);
		if (!hitResult.bBlockingHit) return;
		if (!hitResult.GetComponent()) return;
		if (hitResult.GetComponent()->ComponentHasTag(FName(TEXT("PlayCard"))))
		{
			if (m_curDiceSkillLeftTime > 0) return;
			APlayCard* pPlayCard = Cast<APlayCard>(hitResult.GetActor());
			if (pPlayCard->m_isFlip) return;
			if (!m_pCurSelectPlayCard)
			{
				m_pCurSelectPlayCard = pPlayCard;
				m_pCurSelectPlayCard->TurnCard();
				pSPGM->NotifyPlaySound2DByName("Dice_SelectFirstCard");
			}
			else
			{
				
				if (pPlayCard->m_cardName != m_pCurSelectPlayCard->m_cardName)
				{
					m_pCurSelectPlayCard->TurnCard();
					pSPGM->m_diceBattleInfo.originLife -= 1;
					m_pDiceBattleMenu->UpdateLifeText(pSPGM->m_diceBattleInfo.originLife);
					pSPGM->TriggerDiceAppendSkill(false);
					//如剩余生命小于等于0，此时判定玩家负
					if (pSPGM->m_diceBattleInfo.originLife <= 0) pSPGM->m_diceBattleStage = 6;
					m_pCurSelectPlayCard = NULL;
					pSPGM->NotifyPlaySound2DByName("Dice_Fail");
				}
				else
				{
					pPlayCard->TurnCard();
					UGameplayStatics::SpawnEmitterAtLocation(pPlayCard, pSPGM->m_pSmokePS, pPlayCard->GetActorLocation());
					UGameplayStatics::SpawnEmitterAtLocation(m_pCurSelectPlayCard, pSPGM->m_pSmokePS, m_pCurSelectPlayCard->GetActorLocation());
					pSPGM->m_curDiceScore += 1;
					m_pDiceBattleMenu->UpdateScoreText(pSPGM->m_curDiceScore);
					pSPGM->TriggerDiceAppendSkill(true);
					//如玩家得分大于等于目标得分，玩家胜
					if (pSPGM->m_curDiceScore >= pSPGM->m_diceBattleInfo.targetScore)
					{
						pSPGM->m_diceBattleStage = 7;
						m_pCurSelectPlayCard = NULL;
						return;
					}
					pSPGM->m_curDiceFlipCardNb += 2;
					if (pSPGM->m_curDiceFlipCardNb >= pSPGM->m_diceCardNb * 2)
					{
						//说明此时所有牌都已翻转，与手动全盘翻牌同样操作，将状态设置为4
						pSPGM->m_diceBattleStage = 4;
					}
					m_pCurSelectPlayCard = NULL;
					NotifyShakeCamera();
					pSPGM->NotifyPlaySound2DByName("Dice_Right");
				}
			}
		}
	}
	else if (m_gameState == 2)
	{
		FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, hitResult);
		if (!hitResult.bBlockingHit || !hitResult.GetComponent()) return;
		m_mouseClickDownLoc = hitResult.Location;
		m_pMouseClickDownHitComponent = hitResult.GetComponent();
	}
	else if (m_gameState == 5)
	{
		
	}
}

void ASingleProgressPlayerController::DealScrollEvent(bool upOrDown)
{
	APlayerCameraManager* pCM = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	ANormalCameraManager* pNormalCM = Cast<ANormalCameraManager>(pCM);
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pSPGM->m_gameState == 6) return;
	if (upOrDown)
	{
		pNormalCM->m_POVLocation.Z += m_scrollDeltaZ;
		if (pNormalCM->m_POVLocation.Z >= m_scrollTopZ) pNormalCM->m_POVLocation.Z = m_scrollTopZ;
	}
	else
	{
		pNormalCM->m_POVLocation.Z -= m_scrollDeltaZ;
		if (pNormalCM->m_POVLocation.Z <= m_scrollBottomZ) pNormalCM->m_POVLocation.Z = m_scrollBottomZ;
	}
}

void ASingleProgressPlayerController::DealTickEvent()
{
	if (m_gameState == 0)
	{
		FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery4, false, hitResult);
		bool hitEventCard = false;
		if (hitResult.bBlockingHit && hitResult.GetComponent())
		{
			m_pMouseClickDownHitComponent = hitResult.GetComponent();
			if (!m_pPointingEventCard)
			{
				AEventCard* pEventCard = Cast<AEventCard>(hitResult.GetActor());
				if (!pEventCard) return;
				TArray<UActorComponent*> pComponents = pEventCard->GetComponentsByClass(UStaticMeshComponent::StaticClass());
				for (int32 i = 0; i < pComponents.Num(); i++)
				{
					UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pComponents[i]);
					pSMComponent->SetCustomDepthStencilValue(170);
				}
				m_pPointingEventCard = pEventCard;
				//NotifyLoadEventMenu();
				if (m_pSPMenu)
				{
					m_pSPMenu->NotifyShowEventCardDescription();
				}
			}
			else
			{
				if (hitResult.GetComponent()->ComponentHasTag(FName("EventCard")))
				{
					AEventCard* pEventCard = Cast<AEventCard>(hitResult.GetActor());
					if (pEventCard == m_pPointingEventCard)
					{
						return;
					}
					TArray<UActorComponent*> pComponents = m_pPointingEventCard->GetComponentsByClass(UStaticMeshComponent::StaticClass());
					for (int32 i = 0; i < pComponents.Num(); i++)
					{
						UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pComponents[i]);
						pSMComponent->SetCustomDepthStencilValue(180);
					}
					if (m_pEventMenu)
					{
						DeleteMenu("EventMenu");
					}

					pComponents = pEventCard->GetComponentsByClass(UStaticMeshComponent::StaticClass());
					for (int32 i = 0; i < pComponents.Num(); i++)
					{
						UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pComponents[i]);
						pSMComponent->SetCustomDepthStencilValue(170);
					}
					m_pPointingEventCard = pEventCard;
					//NotifyLoadEventMenu();
					if (m_pSPMenu)
					{
						m_pSPMenu->NotifyShowEventCardDescription();
					}
				}
				else
				{
					TArray<UActorComponent*> pComponents = m_pPointingEventCard->GetComponentsByClass(UStaticMeshComponent::StaticClass());
					for (int32 i = 0; i < pComponents.Num(); i++)
					{
						UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pComponents[i]);
						pSMComponent->SetCustomDepthStencilValue(180);
					}
					m_pPointingEventCard = NULL;
					/*if (m_pEventMenu)
					{
						DeleteMenu("EventMenu");
					}*/
					if (m_pSPMenu)
					{
						m_pSPMenu->NotifyHideEventCardDescription();
					}
				}
			}
		}
	}
	else if (m_gameState == 1)
	{
		/*FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery4, false, hitResult);
		if (!hitResult.bBlockingHit) return;
		bool hitFC = false;
		if (!hitResult.GetComponent() || 
			(!hitResult.GetComponent()->ComponentHasTag(FName(TEXT("DiceBoard"))) && !hitResult.GetComponent()->ComponentHasTag(FName(TEXT("DicePanel"))))) return;
		FVector hitLoc = hitResult.Location;
		if (m_pCurSelectPlayCard) m_pCurSelectPlayCard->SetActorLocation(hitLoc);*/
		//else if (m_pCurActionCard) m_pCurActionCard->SetActorLocation(hitLoc);
	}
	else if (m_gameState == 5)
	{
		FHitResult hitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery4, false, hitResult);
		if (!hitResult.bBlockingHit || !hitResult.GetComponent() || !hitResult.GetComponent()->ComponentHasTag(FName(TEXT("Board")))) return;
		CheckWhetherAbleToBuildShadowActor(hitResult.Location);
	}
}

void ASingleProgressPlayerController::DealLeftClickUpEvent()
{
	if (m_isWidgetClick)
	{
		m_isWidgetClick = false;
		return;
	}
	if (m_gameState == 1)
	{
		/*FHitResult channel4Result;
		GetHitResultUnderCursorByChannel(TraceTypeQuery4, false, channel4Result);
		if (m_pCurSelectPlayCard)
		{
			if (channel4Result.bBlockingHit && channel4Result.GetComponent() && channel4Result.GetComponent()->ComponentHasTag(FName(TEXT("DicePanel"))))
			{
				AActionPanel* pDicePanel = Cast<AActionPanel>(channel4Result.GetActor());
				ANumericCard* pNumericCard = Cast<ANumericCard>(m_pCurSelectPlayCard);
				bool putSuccessfulFlag = pDicePanel->PutPlayCardInArray(pNumericCard);
				if (!putSuccessfulFlag)
				{
					AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
					ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
					int32 cardNb = pSPGM->m_pDiceCardList.Find(pNumericCard);
					if (cardNb == INDEX_NONE) cardNb = 0;
					FVector diceCardLoc = pSPGM->m_diceCardOriginLoc + FVector(cardNb*pSPGM->m_diceCardOffset, 0, 0);
					m_pCurSelectPlayCard->m_targetLoc = diceCardLoc;
				}
			}
			else
			{
				ANumericCard* pNumericCard = Cast<ANumericCard>(m_pCurSelectPlayCard);
				AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
				ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
				for (int32 i=0; i<pSPGM->m_pAllActionPanels.Num(); i++)
				{
					if (pSPGM->m_pAllActionPanels[i]->RemovePlayCardOutArray(pNumericCard)) break;
				}
			}
			m_pCurSelectPlayCard = NULL;
		}*/
	}
	else if (m_gameState == 2)
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (!pSPGM->m_diceAndTheorizeCanAction) return;
		//说明是推理玩法
		FHitResult channel1Result;
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, channel1Result);
		if (channel1Result.bBlockingHit && channel1Result.GetComponent() && 
			channel1Result.GetComponent()->ComponentHasTag(FName(TEXT("NumericCard"))) && channel1Result.GetComponent() == m_pMouseClickDownHitComponent)
		{
			ANumericCard* pTheorizeCard = Cast<ANumericCard>(channel1Result.GetActor());
			//引导部分
			if (m_isInTutorial)
			{
				
				if (pSPGM->m_tutorialSteps.Num() > 0)
				{
					FString tutorialStepName = "ClickTheorizeCard_" + FString::FromInt(pTheorizeCard->m_color) + "_" + FString::FromInt(pTheorizeCard->m_nb);
					if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
						pSPGM->DeleteTutorialStep();
				}
				/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
				else
					pSPGM->DeleteTutorialStep();*/
			}
			if (!m_pCurSelectTheorizeNumericCard)
			{
				if (!pSPGM->m_pPlayerTheorizeCards.Contains(pTheorizeCard)) return;
				m_pCurSelectTheorizeNumericCard = pTheorizeCard;
				m_pCurSelectTheorizeNumericCard->NotifyChangeState(2);
			}
			else
			{
				if (pSPGM->m_pPlayerTheorizeCards.Contains(pTheorizeCard))
				{
					return;
					/*if (pSPGM->m_pPlayerTheorizeCards.Contains(m_pCurSelectTheorizeNumericCard))
					{
						//切换选中卡牌
						m_pCurSelectTheorizeNumericCard->NotifyChangeState(0);
						m_pCurSelectTheorizeNumericCard = pTheorizeCard;
						m_pCurSelectTheorizeNumericCard->NotifyChangeState(2);
					}
					else if (pSPGM->m_pOppTheorizeCards.Contains(m_pCurSelectTheorizeNumericCard))
					{
						//进行对赌
						if (pSPGM->m_theorizePlayerInfo.compareTimes > 0)
						{
							uint8 betResult = pSPGM->Bet(pTheorizeCard, m_pCurSelectTheorizeNumericCard);
							if (betResult == 0)
								pSPGM->PlayBeamParticle(pTheorizeCard, m_pCurSelectTheorizeNumericCard, 0);
							else
								pSPGM->PlayBeamParticle(pTheorizeCard, m_pCurSelectTheorizeNumericCard, 1);
						}
						
						m_pCurSelectTheorizeNumericCard->NotifyChangeState(0);
						m_pCurSelectTheorizeNumericCard = NULL;
					}*/
				}
				else
				{
					if (pSPGM->m_pOppTheorizeCards.Contains(m_pCurSelectTheorizeNumericCard))
					{
						//切换
						m_pCurSelectTheorizeNumericCard->NotifyChangeState(0);
						m_pCurSelectTheorizeNumericCard = pTheorizeCard;
						m_pCurSelectTheorizeNumericCard->NotifyChangeState(2);

					}
					else if (pSPGM->m_pPlayerTheorizeCards.Contains(m_pCurSelectTheorizeNumericCard))
					{
						//对赌
						if (pSPGM->m_theorizePlayerInfo.compareTimes > 0)
						{
							uint8 betResult = pSPGM->Bet(m_pCurSelectTheorizeNumericCard, pTheorizeCard);
							if (betResult == 0)
							{
								pSPGM->PlayBeamParticle(pTheorizeCard, m_pCurSelectTheorizeNumericCard, 1);
								pSPGM->NotifyPlaySound2DByName("Bet_Large");
							}
							else
							{
								pSPGM->PlayBeamParticle(pTheorizeCard, m_pCurSelectTheorizeNumericCard, 0);
								pSPGM->NotifyPlaySound2DByName("Bet_Less");
							}
						}

						m_pCurSelectTheorizeNumericCard->NotifyChangeState(0);
						m_pCurSelectTheorizeNumericCard = NULL;
					}
				}
			}

			
			//pSPGM->Theorize(pTheorizeCard);
		}
	}
}

void ASingleProgressPlayerController::DealRightClickDownEvent()
{
	if (m_gameState != 5 || !m_pSAOccupyInfoActor) return;
	if (m_pSAOccupyInfoActor && m_pSAOccupyInfoActor->IsValidLowLevel())
	{
		m_pSAOccupyInfoActor->Destroy();
		m_pSAOccupyInfoActor->ConditionalBeginDestroy();
		m_pSAOccupyInfoActor = NULL;
	}
	m_curSelectSAOccupyInfo = "";
}

void ASingleProgressPlayerController::SaveGame(FString slotName, int32 index)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	FDateTime Time = FDateTime::Now();
	pCWGI->m_curPlayerSPInfo.year = Time.GetYear();
	pCWGI->m_curPlayerSPInfo.month = Time.GetMonth();
	pCWGI->m_curPlayerSPInfo.day = Time.GetDay();
	pCWGI->m_curPlayerSPInfo.hour = Time.GetHour();
	pCWGI->m_curPlayerSPInfo.minute = Time.GetMinute();
	for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
	{
		if (pCWGI->m_playerSingleProgressInfos[i].progressName != slotName) continue;
		pCWGI->m_playerSingleProgressInfos[i] = pCWGI->m_curPlayerSPInfo;
		pCWGI->m_playerSingleProgressInfos[i].progressName = slotName;
		break;
	}

	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	m_pSPSaveGameObject->m_actionNodeList = pSPGM->m_actionNodeList;
	m_pSPSaveGameObject->m_curEventNodeNb = pSPGM->m_curEventNodeNb;
	m_pSPSaveGameObject->m_curEventNodeLayerNb = pSPGM->m_curEventNodeLayerNb;
	m_pSPSaveGameObject->m_isInBossBattleLayer = pSPGM->m_isInBossBattleLayer;
	m_pSPSaveGameObject->m_curAvailableNodeIDs = pSPGM->m_curAvailableNodeIDs;
	m_pSPSaveGameObject->m_curDayNb = pSPGM->m_curDayNb;

	UGameplayStatics::SaveGameToSlot(m_pSPSaveGameObject, slotName, index);
	m_pSPSaveGameObject->Reset();
}

void ASingleProgressPlayerController::SaveProgressInfo(FString slotName, bool isNewSlot)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	//pCWGI->m_curPlayerSPInfo.progressName = slotName;
	if (isNewSlot)
	{
		pCWGI->m_curPlayerSPInfo.isInitial = false;
		pCWGI->m_playerSingleProgressInfos.Add(pCWGI->m_curPlayerSPInfo);
	}
	/*else
	{
		for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
		{
			if (pCWGI->m_playerSingleProgressInfos[i].progressName != pCWGI->m_curPlayerSPInfo.progressName) continue;
			pCWGI->m_playerSingleProgressInfos[i] = pCWGI->m_curPlayerSPInfo;
			break;
		}
	}*/
	m_pOverallSaveGameObject->m_allProgressInfos = pCWGI->m_playerSingleProgressInfos;
	m_pOverallSaveGameObject->m_doneTutorialSteps = pCWGI->m_doneTutorialSteps;
	UGameplayStatics::SaveGameToSlot(m_pOverallSaveGameObject, slotName, 0);
}

void ASingleProgressPlayerController::LoadGame(FString slotName, int32 index, uint8 loadType)
{
	bool isSaveSlotExist = UGameplayStatics::DoesSaveGameExist(slotName, index);
	if (!isSaveSlotExist) return;
	USaveGame* pSaveGame = UGameplayStatics::LoadGameFromSlot(slotName, index);
	USPSaveGame* pSPSG = Cast<USPSaveGame>(pSaveGame);
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i<pCWGI->m_playerSingleProgressInfos.Num(); i++)
	{
		if (pCWGI->m_playerSingleProgressInfos[i].progressName != slotName) continue;
		pCWGI->m_curPlayerSPInfo = pCWGI->m_playerSingleProgressInfos[i];
		for (TMap<FString, uint8>::TConstIterator iter = pCWGI->m_curPlayerSPInfo.skillAttributeAssignment.CreateConstIterator(); iter; ++iter)
		{
			for (int32 j=0; j<m_playerSkillInfos.Num(); j++)
			{
				if (m_playerSkillInfos[j].skillName != iter->Key) continue;
				m_playerSkillInfos[j].mutationType = iter->Value;
				break;
			}
		}
		break;
	}

	pSPGM->m_actionNodeList = pSPSG->m_actionNodeList;
	pSPGM->m_curEventNodeNb = pSPSG->m_curEventNodeNb;
	pSPGM->m_curEventNodeLayerNb = pSPSG->m_curEventNodeLayerNb;
	pSPGM->m_isInBossBattleLayer = pSPSG->m_isInBossBattleLayer;
	pSPGM->m_curAvailableNodeIDs = pSPSG->m_curAvailableNodeIDs;
	pSPGM->m_curDayNb = pSPSG->m_curDayNb;
	
	if (loadType == 1 || loadType == 2)
	{
		int32 maxActionNodeNb = pSPGM->m_maxActionNodeNbPerLine;
		if (pSPGM->m_isInBossBattleLayer) maxActionNodeNb += 1;
		if (pSPGM->m_curEventNodeNb < maxActionNodeNb && loadType == 1)
		{
			for (int32 i = 0; i < pSPSG->m_eventCardSaveInfos.Num(); i++)
			{
				AEventCard* pEventCard = GetWorld()->SpawnActor<AEventCard>(pSPGM->m_eventCardClass, pSPSG->m_eventCardSaveInfos[i].loc, FRotator::ZeroRotator);
				if (!pEventCard) continue;
				pEventCard->NotifyInitialCard();

				pEventCard->m_cardType = pSPSG->m_eventCardSaveInfos[i].cardType;
				pEventCard->m_pCardImageMesh->ComponentTags.Add(FName(TEXT("EventCard")));
				if (pEventCard->m_pCardImageMesh)
				{
					UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pEventCard, pSPGM->m_pSurfaceMatRoundButton);
					pEventCard->m_pCardImageMesh->SetMaterial(0, pMI);
					UTexture* pTexture = pSPGM->m_eventCardTypeTextureMap[pEventCard->m_cardType];
					pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
				}
				//计算等级，然后赋值m_eventCardInfo
				pEventCard->m_eventCardInfo = pSPSG->m_eventCardSaveInfos[i].cardInfo;

				pEventCard->StartWarpIn();
			}
			//说明还没到最后的节点，这时需要按照保存信息生成卡牌
			pSPGM->UpdateActionNode(loadType);
			if (pSPGM->m_pEventNodeManager) pSPGM->m_pEventNodeManager->ResetNodeManager();
			
		}
		else
		{
			//说明已是最后的节点，这时重新生成所有节点信息，然后生成卡牌
			pSPGM->UpdateActionNode(loadType);
			if (pSPGM->m_pEventNodeManager) pSPGM->m_pEventNodeManager->ResetNodeManager();
		}
	}
	else
	{
		for (int32 i = 0; i < pSPSG->m_eventCardSaveInfos.Num(); i++)
		{
			AEventCard* pEventCard = GetWorld()->SpawnActor<AEventCard>(pSPGM->m_eventCardClass, pSPSG->m_eventCardSaveInfos[i].loc, FRotator::ZeroRotator);
			if (!pEventCard) continue;
			pEventCard->NotifyInitialCard();

			pEventCard->m_cardType = pSPSG->m_eventCardSaveInfos[i].cardType;
			pEventCard->m_pCardImageMesh->ComponentTags.Add(FName(TEXT("EventCard")));
			if (pEventCard->m_pCardImageMesh)
			{
				UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(pEventCard, pSPGM->m_pSurfaceMatRoundButton);
				pEventCard->m_pCardImageMesh->SetMaterial(0, pMI);
				UTexture* pTexture = pSPGM->m_eventCardTypeTextureMap[pEventCard->m_cardType];
				pMI->SetTextureParameterValue(FName(TEXT("BaseTexture")), pTexture);
			}
			//计算等级，然后赋值m_eventCardInfo
			pEventCard->m_eventCardInfo = pSPSG->m_eventCardSaveInfos[i].cardInfo;

			pEventCard->StartWarpIn();
		}
	}
	
	pSPSG->Reset();
}

void ASingleProgressPlayerController::ApplyLoadDynamic()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	PlayerCameraManager->StartCameraFade(0.f, 1.f, m_waitToLoadTime, FLinearColor::Black, false, true);
	pSPGM->StopTick();
	pSPGM->HideAllCardWidget();
	//if (m_pSaveMenu) m_pSaveMenu->AskFadeOut();
	if (m_pPauseMenu) m_pPauseMenu->AskMenuFadeOut();
	m_pSPMenu->FadeOut();
	if (m_pActionPanel) DeleteMenu("ActionPanel");
	GetWorldTimerManager().SetTimer(m_waitToLoadTimerHandler, this, &ASingleProgressPlayerController::WaitToLoad, m_waitToLoadTime + 0.3f, false);
}

void ASingleProgressPlayerController::WaitToLoad()
{
	LoadGame(m_waitToLoadSlotName, 0, 0);
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	PlayerCameraManager->StartCameraFade(1.f, 0.f, m_waitToLoadTime, FLinearColor::Black, false, true);
	pSPGM->ResumeTick();
	SwitchMenu(0);

}

void ASingleProgressPlayerController::ApplyBackToMainMenu()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	PlayerCameraManager->StartCameraFade(0.f, 1.f, m_waitToLoadTime, FLinearColor::Black, false, true);
	pSPGM->StopTick();
	pSPGM->HideAllCardWidget();
	//if (m_pSaveMenu) m_pSaveMenu->AskFadeOut();
	if (m_pPauseMenu) m_pPauseMenu->AskMenuFadeOut();
	m_pSPMenu->FadeOut();
	pSPGM->NotifyMusicFadeOut();
	GetWorldTimerManager().SetTimer(m_waitToLoadTimerHandler, this, &ASingleProgressPlayerController::WaitToMainMenu, m_waitToLoadTime + 0.3f, false);
}

void ASingleProgressPlayerController::WaitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoginMap")));
}

void ASingleProgressPlayerController::WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo)
{
	m_playerSkillInfos.Add(skillInfo);
}

void ASingleProgressPlayerController::PressRuneKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pSPGM->m_gameState == 6) return;
	if (m_isInTutorial)
	{
		if (pSPGM->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "PressRuneKey";
			if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pSPGM->DeleteTutorialStep();
		}
		/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
		else
			pSPGM->DeleteTutorialStep();*/
	}
	PlayerCameraManager->StartCameraFade(0.f, 1.f, pSPGM->m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
	pSPGM->StopTick();
	pSPGM->HideAllCardWidget();
	m_pSPMenu->FadeOut();
	if (m_pTutorialMenu) m_pTutorialMenu->NotifyFadeOut();
	pSPGM->SpawnRuneDemoCharacter(0);
	GetWorldTimerManager().SetTimer(m_runeSwitchTimerHandler, pSPGM, &ASingleProgressGameMode::InitialRuneMode, pSPGM->m_diceAndTheorizeFadeOutTime + 0.3f, false);
}

void ASingleProgressPlayerController::PressEndRuneKey()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (m_isInTutorial)
	{
		if (pSPGM->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "EndPressRuneKey";
			if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pSPGM->DeleteTutorialStep();
			/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
			else
				pSPGM->DeleteTutorialStep();*/
			if (m_pTutorialMenu) m_pTutorialMenu->NotifyFadeOut();
		}
	}
	PlayerCameraManager->StartCameraFade(0.f, 1.f, pSPGM->m_diceAndTheorizeFadeOutTime, FLinearColor::Black, false, true);
	GetWorldTimerManager().SetTimer(m_runeSwitchTimerHandler, pSPGM, &ASingleProgressGameMode::EndRuneMode, pSPGM->m_diceAndTheorizeFadeOutTime + 0.3f, false);
}

void ASingleProgressPlayerController::CaptureScene()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	UGameUserSettings* pGS = GEngine->GetGameUserSettings();
	FIntPoint resolution = pGS->GetScreenResolution();
	FString captureSceneStr = "HighResShot ";
	FString resStr = FString::FromInt(resolution.X).Append("x").Append(FString::FromInt(resolution.Y));
	captureSceneStr = captureSceneStr.Append(resStr);
	m_pPPComponent->Settings.ColorSaturation = FVector4(0, 0, 0, 0);
	ConsoleCommand(captureSceneStr);
	m_pPPComponent->Settings.ColorSaturation = FVector4(1,1,1,1);
	//GetWorld()->Exec(GetWorld(), *captureSceneStr);
}

void ASingleProgressPlayerController::InitialTutorial()
{
	if (!m_isInTutorial) return;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	LoadTutorialmenu();
	
	pSPGM->UpdateTutorialStep();
}

void ASingleProgressPlayerController::AddTestCard(const TArray<FString>& cardNames)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	for (int32 i = 0; i < cardNames.Num(); i++)
	{
		pSPGM->SpawnNewPlayCard(-1, 5, cardNames[i]);
	}
}

void ASingleProgressPlayerController::SetTestAttribute(int32 hp, int32 atk, int32 dfc)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i<hp; i++)
	{
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseLife"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseLife", 1);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseLife"] + 1;
	}
	for (int32 i = 0; i < atk; i++)
	{
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseAtk"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseAtk", 1);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseAtk"] + 1;
	}
	for (int32 i = 0; i < dfc; i++)
	{
		if (!pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Contains("IncreaseDfc"))
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap.Add("IncreaseDfc", 1);
		else
			pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] = pCWGI->m_curPlayerSPInfo.attributeIncreaseMap["IncreaseDfc"] + 1;
	}
}

void ASingleProgressPlayerController::NotifyShakeCamera_Implementation()
{

}

void ASingleProgressPlayerController::SwitchMenu(uint8 menuState)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (menuState == 0)
	{
		if (m_gameState == 1)
		{
			m_pCardSelectMenu->FadeOut();
			m_pDiceBattleMenu->FadeOut();
		}
		else if (m_gameState == 2)
		{
			m_pCardSelectMenu->FadeOut();
			m_pTheorizeMenu->FadeOut();
		}
		else if (m_gameState == 4)
		{
			m_pShopMenu->FadeOut();
		}
		else if (m_gameState == 5)
		{
			m_pShadowModeMenu->FadeOut();
		}
		else if (m_gameState == 6)
		{
			m_pRuneMenu->FadeOut();
		}
		LoadSPMenu();

		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_fixTutorialSerialNames[0])) pSPGM->RefreshTutorial(pSPGM->m_fixTutorialSerialNames[0], true, 0);
		else pSPGM->RefreshTutorial("NULL", false, 0);
		/*AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		if (pSPGM->m_isInBossBattleLayer)
			m_pSPMenu->AddBossBattleProgressBall();*/
		//if (pSPGM->m_dumpCardList.Num() <= 0) return;
		//m_pSPMenu->UpdateDiscardPile(pSPGM->m_dumpCardList.Last());
	}
	else if (menuState == 1)
	{
		LoadDiceBattleMenu();
		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_fixTutorialSerialNames[1])) pSPGM->RefreshTutorial(pSPGM->m_fixTutorialSerialNames[1], true, 1);
		else pSPGM->RefreshTutorial("NULL", false, 1);
	}
	else if (menuState == 2)
	{
		LoadDecipherMenu();
		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_fixTutorialSerialNames[2])) pSPGM->RefreshTutorial(pSPGM->m_fixTutorialSerialNames[2], true, 2);
		else pSPGM->RefreshTutorial("NULL", false, 2);
	}
	else if (menuState == 3)
	{
		
		LoadDrawCardMenu();
	}
	else if (menuState == 4)
	{
		m_pSPMenu->FadeOut();
		LoadTradingMenu();
	}
	else if (menuState == 5)
	{
		m_pSPMenu->FadeOut();
		LoadShadowModeMenu();

		if (!pCWGI->m_doneTutorialSteps.Contains(pSPGM->m_fixTutorialSerialNames[3])) pSPGM->RefreshTutorial(pSPGM->m_fixTutorialSerialNames[3], true, 3);
		else pSPGM->RefreshTutorial("NULL", false, 3);
	}
	else if (menuState == 6)
	{
		NotifyLoadRuneMenu();
	}
}

void ASingleProgressPlayerController::LoadSPMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadDiceBattleMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadDecipherMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadDrawCardMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadTradingMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadShadowModeMenu_Implementation()
{

}

void ASingleProgressPlayerController::NotifyLoadRuneMenu_Implementation()
{

}

void ASingleProgressPlayerController::NotifyLoadEventMenu_Implementation()
{

}

void ASingleProgressPlayerController::LoadTutorialSerialMenu()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	FTutorialStepSerial tutorialSerial = pSPGM->ReadTutorialInfoByName(pSPGM->m_curTutorialName);
	UTTutorialMenu* pTutorialMenu = CreateWidget<UTTutorialMenu>(this, m_pTutorialMenuClass);
	//pTutorialMenu->m_curTutorialSerialName = pSPGM->m_curTutorialName;
	pTutorialMenu->m_type = 0;
	pTutorialMenu->m_pWidgetManager = m_pWidgetManager;
	pTutorialMenu->NotifyInitial();
	pTutorialMenu->m_tutorialSerial = tutorialSerial;
	//pTutorialMenu->m_pWidgetManager = m_pWidgetManager;
	if (tutorialSerial.tutorialSteps.Num() <= 0) return;
	if (tutorialSerial.tutorialSteps[0].pMediaSource)
	{
		pTutorialMenu->m_pMediaPlayer->OpenSource(tutorialSerial.tutorialSteps[0].pMediaSource);
	}
	if (tutorialSerial.tutorialSteps[0].chDescriptions.Num() > 0)
	{
		if (pTutorialMenu->m_pWidgetManager->m_language == "Chinese")
			pTutorialMenu->m_pDescriptionBox->SetText(FText::FromString(tutorialSerial.tutorialSteps[0].chDescriptions[0]));
		else
			pTutorialMenu->m_pDescriptionBox->SetText(FText::FromString(tutorialSerial.tutorialSteps[0].enDescriptions[0]));
	}
	m_pTutorialSerialMenu = pTutorialMenu;
	m_pTutorialSerialMenu->AddToViewport();
}

void ASingleProgressPlayerController::LoadRuneMenu(UWidgetManager* pWidgetManager, FString chTitle, FString enTitle, FString chSkillDomainTitle, FString skillDomainTitle,
	FString chWormDomainTitle, FString wormDomainTitle, FString chCombineDomainTitle, FString combineDomainTitle, FString chNumericDomainTitle, FString numericDomainTitle)
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (m_pRuneMenu) return;
	FString characterName = pCWGI->m_curPlayerSPInfo.characterName;
	if (characterName == "" || characterName == "NULL") characterName = "Lucian";
	//ReadPlayerCharacterSkills(characterName);
	ReadFCInfos();
	ReadCardCombineInfo();
	ReadCharacterAppearanceInfo(characterName);
	m_pRuneMenu = UWidgetBlueprintFunctionLibrary::CreateRuneMenu(pWidgetManager, chTitle, enTitle, chSkillDomainTitle, skillDomainTitle, chWormDomainTitle, wormDomainTitle,
		chCombineDomainTitle, combineDomainTitle, chNumericDomainTitle, numericDomainTitle);
	m_pRuneMenu->AddToViewport();
}

void ASingleProgressPlayerController::LoadCardCombineListMenu(UWidgetManager* pWidgetManager, FString chExploreTitle, FString enExploreTitle, FString chCommunicationTitle, FString enCommunicationTitle, FString chForgeTitle, FString enForgeTitle, FString chResearchTitle, FString enResearchTitle,
	FString consumeTitle, FString lifeTitle, FString energyTitle, FString activityTitle, FString darknessTitle, FString mentalityTitle, FString moneyTitle,
	FString suppressionTitle, FString flameTitle, FString sunTitle, FString chconsumeTitle, FString chlifeTitle, FString chenergyTitle, FString chactivityTitle, FString chdarknessTitle, FString chmentalityTitle, FString chmoneyTitle,
	FString chsuppressionTitle, FString chflameTitle, FString chsunTitle)
{
	if (m_pCardCombineListMenu)
	{
		DeleteMenu("CardCombineListMenu");
	}
	m_pCardCombineListMenu = UWidgetBlueprintFunctionLibrary::CreateCardCombineListMenu(pWidgetManager, chExploreTitle, enExploreTitle, chCommunicationTitle, enCommunicationTitle,
		chForgeTitle, enForgeTitle, chResearchTitle, enResearchTitle, consumeTitle, lifeTitle, energyTitle, activityTitle, darknessTitle, mentalityTitle,
		moneyTitle, suppressionTitle, flameTitle, sunTitle, chconsumeTitle, chlifeTitle, chenergyTitle, chactivityTitle, chdarknessTitle, chmentalityTitle,
		chmoneyTitle, chsuppressionTitle, chflameTitle, chsunTitle);
	m_pCardCombineListMenu->AddToViewport();
}

void ASingleProgressPlayerController::DeleteMenu(const FString& menuName)
{
	if (menuName == "ActionPanel")
	{
		if (!m_pActionPanel) return;
		m_pActionPanel->RemoveFromParent();
		if (m_pActionPanel->IsValidLowLevel())
			m_pActionPanel->ConditionalBeginDestroy();
		m_pActionPanel = NULL;
		m_pCurSelectEventCard = NULL;
	}
	else if (menuName == "DiceBattleMenu")
	{
		if (!m_pDiceBattleMenu) return;
		m_pDiceBattleMenu->RemoveFromParent();
		if (m_pDiceBattleMenu->IsValidLowLevel())
			m_pDiceBattleMenu->ConditionalBeginDestroy();
		m_pDiceBattleMenu = NULL;
	}
	else if (menuName == "TheorizeMenu")
	{
		if (!m_pTheorizeMenu) return;
		m_pTheorizeMenu->RemoveFromParent();
		if (m_pTheorizeMenu->IsValidLowLevel())
			m_pTheorizeMenu->ConditionalBeginDestroy();
		m_pTheorizeMenu = NULL;
	}
	else if (menuName == "CardSelectMenu")
	{
		if (!m_pCardSelectMenu) return;
		m_pCardSelectMenu->RemoveFromParent();
		if (m_pCardSelectMenu->IsValidLowLevel())
			m_pCardSelectMenu->ConditionalBeginDestroy();
		m_pCardSelectMenu = NULL;
	}
	else if (menuName == "ShadowModeMenu")
	{
		if (!m_pShadowModeMenu) return;
		m_pShadowModeMenu->RemoveFromParent();
		if (m_pShadowModeMenu->IsValidLowLevel())
			m_pShadowModeMenu->ConditionalBeginDestroy();
		m_pShadowModeMenu = NULL;
	}
	else if (menuName == "ShopMenu")
	{
		if (!m_pShopMenu) return;
		m_pShopMenu->RemoveFromParent();
		if (m_pShopMenu->IsValidLowLevel())
			m_pShopMenu->ConditionalBeginDestroy();
		m_pShopMenu = NULL;
	}
	else if (menuName == "RuneMenu")
	{
		if (!m_pRuneMenu) return;
		m_pRuneMenu->RemoveFromParent();
		if (m_pRuneMenu->IsValidLowLevel())
			m_pRuneMenu->ConditionalBeginDestroy();
		m_pRuneMenu = NULL;
	}
	else if (menuName == "CardCombineListMenu")
	{
		if (!m_pCardCombineListMenu) return;
		m_pCardCombineListMenu->RemoveFromParent();
		if (m_pCardCombineListMenu->IsValidLowLevel())
			m_pCardCombineListMenu->ConditionalBeginDestroy();
		m_pCardCombineListMenu = NULL;
		m_playerSkillInfos.Empty();
	}
	/*else if (menuName == "SaveMenu")
	{
		if (!m_pSaveMenu) return;
		m_pSaveMenu->RemoveFromParent();
		if (m_pSaveMenu->IsValidLowLevel())
			m_pSaveMenu->ConditionalBeginDestroy();
		m_pSaveMenu = NULL;
	}*/
	else if (menuName == "PauseMenu")
	{
		if (!m_pPauseMenu) return;
		m_pPauseMenu->RemoveFromParent();
		if (m_pPauseMenu->IsValidLowLevel())
			m_pPauseMenu->ConditionalBeginDestroy();
		m_pPauseMenu = NULL;
	}
	else if (menuName == "TutorialMenu")
	{
		if (!m_pTutorialMenu) return;
		m_pTutorialMenu->RemoveFromParent();
		if (m_pTutorialMenu->IsValidLowLevel())
			m_pTutorialMenu->ConditionalBeginDestroy();
		m_pTutorialMenu = NULL;
	}
	else if (menuName == "SPMenu")
	{
		if (!m_pSPMenu) return;
		m_pSPMenu->RemoveFromParent();
		if (m_pSPMenu->IsValidLowLevel())
			m_pSPMenu->ConditionalBeginDestroy();
		m_pSPMenu = NULL;
	}
	else if (menuName == "EventMenu")
	{
		if (!m_pEventMenu) return;
		m_pEventMenu->RemoveFromParent();
		if (m_pEventMenu->IsValidLowLevel())
			m_pEventMenu->ConditionalBeginDestroy();
		m_pEventMenu = NULL;
	}
}

void ASingleProgressPlayerController::LoadExtraBounusCard(const TArray<FString>& mustBonus, uint8 type)
{
	ReadMustBonusCardTexture();
	m_pCardSelectMenu = UWidgetBlueprintFunctionLibrary::CreateCardSelectMenu(m_pWidgetManager);
	m_pCardSelectMenu->m_mustBonusCards = mustBonus;
	m_pCardSelectMenu->m_bonusType = type;
	m_pCardSelectMenu->AddActionCardToPanel(0);
	//if (type == 0) m_playerSkillInfos.Empty();
	m_pMustBonusCardTextureMap.Empty();
	m_pCardSelectMenu->AddToViewport();
}

void ASingleProgressPlayerController::WriteCharacterAppearanceInfo(const FCharacterAppearanceInfo& appearanceInfo)
{
	m_characterAppearanceInfo.Add(appearanceInfo);
}

void ASingleProgressPlayerController::LoadSimpleMenu(FString chSaveText, FString enSaveText)
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pSPGM->m_tickFlag) PauseOrUnPauseGame();
	m_pPauseMenu = UWidgetBlueprintFunctionLibrary::CreateSimpleMenu(m_pWidgetManager, 0, 0);
	m_pPauseMenu->AddToViewport();
	m_isPauseMenuOn = true;
	//pSPGM->StopTick();
}

void ASingleProgressPlayerController::LoadTutorialmenu()
{
	m_pTutorialMenu = UWidgetBlueprintFunctionLibrary::CreateTutorialMenu(m_pWidgetManager, 0);
	if (!m_pTutorialMenu) return;
	m_pTutorialMenu->AddToViewport();
}

void ASingleProgressPlayerController::LoadSkillSelectMenu()
{
	m_pSkillSelectMenu = UWidgetBlueprintFunctionLibrary::CreateSkillSelectMenu(m_pWidgetManager);
	m_pSkillSelectMenu->AddToViewport();
}

bool ASingleProgressPlayerController::TellWhetherHitSkillTree(FVector2D hitLoc)
{
	if (hitLoc.X < m_skillTreeTopLeftCorner.X || hitLoc.X > m_skillTreeRightBottomCorner.X ||
		hitLoc.Y > m_skillTreeRightBottomCorner.Y || hitLoc.Y < m_skillTreeTopLeftCorner.Y)
	{
		if (m_pSPMenu && m_pSPMenu->m_pSkillTree && !m_pSPMenu->m_pSkillTree->m_isFading)
		{
			m_pSPMenu->m_pSkillTree->RemoveFromParent();
			if (m_pSPMenu->m_pSkillTree->IsValidLowLevel())
				m_pSPMenu->m_pSkillTree->ConditionalBeginDestroy();
			m_pSPMenu->m_pSkillTree = NULL;
		}
		return false;
	}
	return true;
}

FString ASingleProgressPlayerController::ReadDemoWordPrefix_Implementation(uint8 type, bool chOrEn)
{
	FString words;
	return words;
}

void ASingleProgressPlayerController::ReadMustBonusCardTexture_Implementation()
{

}

void ASingleProgressPlayerController::NotifyLoadDemoWords_Implementation(uint8 type, bool chOrEn)
{

}

void ASingleProgressPlayerController::LoadEndSPMenu_Implementation(int32 curProgress)
{

}

void ASingleProgressPlayerController::ReadCharacterAppearanceInfo_Implementation(const FString& characterName)
{

}

void ASingleProgressPlayerController::DropDiceSkillCard()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (!m_pSelectDiceBattleSkill || !pSPGM->m_diceAndTheorizeCanAction) return;
	FVector2D mouseViewportPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	float viewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	FVector worldPos;
	FVector worldDir;
	UGameplayStatics::DeprojectScreenToWorld(this, mouseViewportPos*viewportScale, worldPos, worldDir);
	FHitResult channel4Result;
	TArray<AActor*> ignoreActorList;
	UKismetSystemLibrary::LineTraceSingle(this, worldPos, worldPos + worldDir * 20000, TraceTypeQuery4, false, ignoreActorList, EDrawDebugTrace::None,
		channel4Result, true);

	if (!channel4Result.bBlockingHit || !channel4Result.GetComponent() || !channel4Result.GetComponent()->ComponentHasTag(FName("DiceCard")))
	{
		//一是将拖动卡牌删除，二是将当前拖动卡牌设为NULL
		m_pSelectDiceBattleSkill = NULL;
		return;
	}
	else
	{
		APlayCard* pPlayCard = Cast<APlayCard>(channel4Result.GetActor());
		FString skillName = m_pSelectDiceBattleSkill->m_cardName.RightChop(14);
		FString functionName = m_allDiceBattleSkillInfos[skillName].functionName;
		
		if (functionName == "SquareUncover")
		{
			
			int32 dropCardNb = pSPGM->m_pDiceCardList.Find(pPlayCard);
			int32 LTNb = dropCardNb - m_allDiceBattleSkillInfos[skillName].values[0] * pSPGM->m_diceBattleInfo.diceCardColNb - m_allDiceBattleSkillInfos[skillName].values[0];
			while (LTNb < 0)
			{
				LTNb += 1;
			}
			int32 LTRow = LTNb / pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 LTCol = LTNb - LTRow * pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 DropCardRow = dropCardNb / pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 DropCardCol = dropCardNb - DropCardRow * pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 RDRow = DropCardRow + m_allDiceBattleSkillInfos[skillName].values[0];
			int32 RDCol = DropCardCol + m_allDiceBattleSkillInfos[skillName].values[0];
			if (RDRow >= pSPGM->m_diceBattleInfo.diceCardColNb - 1) RDRow = pSPGM->m_diceBattleInfo.diceCardColNb - 1;
			if (RDCol >= pSPGM->m_diceBattleInfo.diceCardColNb - 1) RDCol = pSPGM->m_diceBattleInfo.diceCardColNb - 1;
			TArray<int32> uncoverNbs;
			for (int32 i=LTRow; i <= RDRow; i++)
			{
				for (int32 j=LTCol; j<= RDCol; j++)
				{
					int32 cardNb = i * pSPGM->m_diceBattleInfo.diceCardColNb + j;
					if (!uncoverNbs.Contains(cardNb))
						uncoverNbs.Add(cardNb);
				}
			}
			for (int32 i=0; i<uncoverNbs.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isFlip)
				{
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->TurnCard();
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isInSkillState = true;
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
					pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[uncoverNbs[i]]);
				}
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "CrossUncover")
		{
			int32 dropCardNb = pSPGM->m_pDiceCardList.Find(pPlayCard);
			int32 DropCardRow = dropCardNb / pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 DropCardCol = dropCardNb - DropCardRow * pSPGM->m_diceBattleInfo.diceCardColNb;
			TArray<int32> uncoverNbs;
			for (int32 i=0; i<pSPGM->m_diceBattleInfo.diceCardColNb; i++)
			{
				int32 cardNb = i * pSPGM->m_diceBattleInfo.diceCardColNb + DropCardCol;
				if (!uncoverNbs.Contains(cardNb)) uncoverNbs.Add(cardNb);
			}
			for (int32 i = 0; i < pSPGM->m_diceBattleInfo.diceCardColNb; i++)
			{
				int32 cardNb = DropCardRow * pSPGM->m_diceBattleInfo.diceCardColNb + i;
				if (!uncoverNbs.Contains(cardNb)) uncoverNbs.Add(cardNb);
			}
			for (int32 i = 0; i < uncoverNbs.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isFlip)
				{
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->TurnCard();
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isInSkillState = true;
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
					pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[uncoverNbs[i]]);
				}
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "HLineUncover")
		{
			int32 dropCardNb = pSPGM->m_pDiceCardList.Find(pPlayCard);
			int32 DropCardRow = dropCardNb / pSPGM->m_diceBattleInfo.diceCardColNb;
			TArray<int32> uncoverNbs;
			for (int32 i = 0; i < pSPGM->m_diceBattleInfo.diceCardColNb; i++)
			{
				int32 cardNb = DropCardRow * pSPGM->m_diceBattleInfo.diceCardColNb + i;
				if (!uncoverNbs.Contains(cardNb)) uncoverNbs.Add(cardNb);
			}
			for (int32 i = 0; i < uncoverNbs.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isFlip)
				{
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->TurnCard();
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isInSkillState = true;
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
					pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[uncoverNbs[i]]);
				}
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "VLineUncover")
		{
			int32 dropCardNb = pSPGM->m_pDiceCardList.Find(pPlayCard);
			int32 DropCardRow = dropCardNb / pSPGM->m_diceBattleInfo.diceCardColNb;
			int32 DropCardCol = dropCardNb - DropCardRow * pSPGM->m_diceBattleInfo.diceCardColNb;
			TArray<int32> uncoverNbs;
			for (int32 i = 0; i < pSPGM->m_diceBattleInfo.diceCardColNb; i++)
			{
				int32 cardNb = i * pSPGM->m_diceBattleInfo.diceCardColNb + DropCardCol;
				if (!uncoverNbs.Contains(cardNb)) uncoverNbs.Add(cardNb);
			}
			for (int32 i = 0; i < uncoverNbs.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isFlip)
				{
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->TurnCard();
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_isInSkillState = true;
					pSPGM->m_pDiceCardList[uncoverNbs[i]]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
					pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[uncoverNbs[i]]);
				}
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "RandUncover")
		{
			TArray<int32> unFlipCards;
			for (int32 i=0; i<pSPGM->m_pDiceCardList.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[i]->m_isFlip)
					unFlipCards.Add(i);
			}
			TArray<int32> flipNbs;
			for (int32 i=0; i< m_allDiceBattleSkillInfos[skillName].values[0]; i++)
			{
				if (unFlipCards.Num() <= 0) break;
				int32 randNb = FMath::RandRange(0, unFlipCards.Num() - 1);
				flipNbs.Add(unFlipCards[randNb]);
				unFlipCards.RemoveAt(randNb);
			}
			for (int32 i=0; i<flipNbs.Num(); i++)
			{
				pSPGM->m_pDiceCardList[flipNbs[i]]->TurnCard();
				pSPGM->m_pDiceCardList[flipNbs[i]]->m_isInSkillState = true;
				pSPGM->m_pDiceCardList[flipNbs[i]]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
				pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[flipNbs[i]]);
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "DropUncover")
		{
			pPlayCard->TurnCard();
			pPlayCard->m_isInSkillState = true;
			pPlayCard->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[0];
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[0] + 0.1;
			pSPGM->m_pDiceSkillFlipCards.Add(pPlayCard);
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[0] + 0.1, false);
		}
		else if (functionName == "ColorUncover")
		{
			for (int32 i = 0; i < pSPGM->m_pDiceCardList.Num(); i++)
			{
				if (!pSPGM->m_pDiceCardList[i]->m_isFlip && (int32)pSPGM->m_pDiceCardList[i]->m_color == m_allDiceBattleSkillInfos[skillName].values[0])
				{
					pSPGM->m_pDiceCardList[i]->TurnCard();
					pSPGM->m_pDiceCardList[i]->m_isInSkillState = true;
					pSPGM->m_pDiceCardList[i]->m_skillCountDown = m_allDiceBattleSkillInfos[skillName].values[1];
					pSPGM->m_pDiceSkillFlipCards.Add(pSPGM->m_pDiceCardList[i]);
				}
			}
			pSPGM->m_diceBattleStage = 12;
			GetWorldTimerManager().SetTimer(pSPGM->m_diceSkillTimerHandler, pSPGM, &ASingleProgressGameMode::DiceSkillFlipCardEnd, m_allDiceBattleSkillInfos[skillName].values[1] + 0.1, false);
			//m_curDiceSkillLeftTime = m_allDiceBattleSkillInfos[skillName].values[1] + 0.1;
		}
		else if (functionName == "IncreaseLifeByBingo" || functionName == "Keep Life")
		{
			FDiceAndTheorizeSkillAppendInfo newAppendInfo;
			newAppendInfo.skillName = skillName;
			newAppendInfo.functionName = functionName;
			newAppendInfo.leftTime = m_allDiceBattleSkillInfos[skillName].values[1];
			int32 i = 0;
			for (TMap<int32, FDiceAndTheorizeSkillAppendInfo>::TConstIterator iter = pSPGM->m_curAppendDiceSkillInfos.CreateConstIterator(); iter; ++iter)
			{
				if (iter->Key == i)
					i += 1;
				else
					break;
			}
			pSPGM->m_curAppendDiceSkillInfos.Add(i, newAppendInfo);
			m_pDiceBattleMenu->AddDiceSkillImage(skillName, i);
		}
		m_pSelectDiceBattleSkill->NotifySetTimer(0);
		m_pSelectDiceBattleSkill = NULL;
		pSPGM->PlayDiceOrTheorizeSkillPS(skillName, 0);
		pSPGM->NotifyPlaySound2DByName("Dice_LaunchSkill");
	}
}

void ASingleProgressPlayerController::DropDecipherCard()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (!m_pSelectTheorizeCard || !pSPGM->m_diceAndTheorizeCanAction) return;

	FVector2D mouseViewportPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	float viewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	FVector worldPos;
	FVector worldDir;
	UGameplayStatics::DeprojectScreenToWorld(this, mouseViewportPos*viewportScale, worldPos, worldDir);
	FHitResult channel1Result;
	TArray<AActor*> ignoreActorList;
	UKismetSystemLibrary::LineTraceSingle(this, worldPos, worldPos + worldDir * 20000, TraceTypeQuery1, false, ignoreActorList, EDrawDebugTrace::None,
		channel1Result, true);

	FString theorizeCardTag = "TheorizeCard";
	if (!channel1Result.bBlockingHit || !channel1Result.GetComponent() || !channel1Result.GetComponent()->ComponentHasTag(FName(*theorizeCardTag)))
	{
		
		ANumericCard* pNumericCard = Cast<ANumericCard>(channel1Result.GetActor());
		if (pSPGM->m_pOppTheorizeCards.Contains(pNumericCard) && !pNumericCard->m_isFlip)
		{
			pSPGM->Theorize(pNumericCard);
		}
	}
	m_pSelectTheorizeCard = NULL;
}

void ASingleProgressPlayerController::NormalModeToShadowMode()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	if (pSPGM->m_gameState != 0) return;

	pSPGM->InitialShadowMode();
	//引导部分
	if (m_isInTutorial)
	{
		if (pSPGM->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "InitialShadowMode";
			if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pSPGM->DeleteTutorialStep();
		}
		/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
		else
			pSPGM->DeleteTutorialStep();*/
	}
	GetWorldTimerManager().SetTimer(m_shadowModeTimerHandle, pSPGM, &ASingleProgressGameMode::SpawnAllShadowActors, m_shadowActorSpawnDelayTime, false);
}

void ASingleProgressPlayerController::ShadowModeToNormalMode()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
	//引导部分
	if (m_isInTutorial)
	{
		if (pSPGM->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "EndShadowMode";
			if (pSPGM->m_tutorialSteps[0].operationName == tutorialStepName)
				pSPGM->DeleteTutorialStep();
		}
		/*if (pSPGM->m_tutorialSteps[0].operationName != tutorialStepName) return;
		else
			pSPGM->DeleteTutorialStep();*/
	}
	pSPGM->EndShadowMode();
	GetWorldTimerManager().ClearTimer(m_shadowModeTimerHandle);
}

bool ASingleProgressPlayerController::CheckWhetherAbleToBuildShadowActor(FVector cursorLoc)
{

	if (!m_pSAOccupyInfoActor)
	{
		//说明此事检测
		if (m_curSelectSAOccupyInfo == "") return false;
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);

		AShadowActor* pShadowActor = GetWorld()->SpawnActor<AShadowActor>(pSPGM->m_pCWSingleton->m_SAClassMap[m_curSelectSAOccupyInfo], cursorLoc, FRotator::ZeroRotator);
		TArray<UActorComponent*> pComponents = pShadowActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
		for (int32 i=0; i< pComponents.Num(); i++)
		{
			USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
			pSMComponent->SetCustomDepthStencilValue(100);
		}

		TArray<UActorComponent*> pStaticComponents = pShadowActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		for (int32 i = 0; i < pStaticComponents.Num(); i++)
		{
			UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticComponents[i]);
			pSMComponent->SetCustomDepthStencilValue(100);
		}
		//pShadowActor->m_isOverlapSA = false;
		m_pSAOccupyInfoActor = pShadowActor;
		return false;

		/*if (!m_SAOccupyInfoActorClass || m_curSelectSAOccupyInfo == "") return false;
		
		m_pSAOccupyInfoActor = GetWorld()->SpawnActor<AActor>(m_SAOccupyInfoActorClass, cursorLoc, FRotator::ZeroRotator);
		float radiusScale = (float)pSPGM->m_pShadowSkeletalMeshMap[m_curSelectSAOccupyInfo].occupyRadiusPercent / 100.f;
		m_pSAOccupyInfoActor->SetActorScale3D(FVector(radiusScale));
		float radius = m_occupyActorRadius * radiusScale;*/

		/*TArray<FOverlapResult> overlapResults;
		GetWorld()->OverlapMultiByChannel(overlapResults, cursorLoc, FQuat::Identity, ECC_EngineTraceChannel4, FCollisionShape::MakeBox(FVector(radius)));
		bool canBuild = true;
		for (int32 i = 0; i < overlapResults.Num(); i++)
		{
			if (!overlapResults[i].GetActor())
				continue;
			if (overlapResults[i].GetComponent()->ComponentHasTag(FName(TEXT("ShadowActor"))))
			{
				canBuild = false;
				break;
			}
		}

		/ *TArray<UActorComponent*> pStaticMeshComponents = m_pSAOccupyInfoActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticMeshComponents[0]);* /
		if (!canBuild)
		{
			TArray<UActorComponent*> pComponents = pShadowActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			for (int32 i = 0; i < pComponents.Num(); i++)
			{
				USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
				pSMComponent->SetCustomDepthStencilValue(150);
			}
			return false;
		}
		else
		{
			//pSMComponent->SetCustomDepthStencilValue(180);
			//pSMComponent->SetVectorParameterValueOnMaterials(FName(TEXT("BaseColor")), FVector(0, 1, 0));
			return true;
		}*/
	}
	else
	{
		m_pSAOccupyInfoActor->SetActorLocation(cursorLoc);
		if (m_pSAOccupyInfoActor->m_pOverlapSAs.Num() > 0)
		{
			TArray<UActorComponent*> pComponents = m_pSAOccupyInfoActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			for (int32 i = 0; i < pComponents.Num(); i++)
			{
				USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
				pSMComponent->SetCustomDepthStencilValue(100);
			}

			TArray<UActorComponent*> pStaticComponents = m_pSAOccupyInfoActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
			for (int32 i = 0; i < pStaticComponents.Num(); i++)
			{
				UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticComponents[i]);
				pSMComponent->SetCustomDepthStencilValue(100);
			}
			return false;
		}
		else
		{
			TArray<UActorComponent*> pComponents = m_pSAOccupyInfoActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			for (int32 i = 0; i < pComponents.Num(); i++)
			{
				USkeletalMeshComponent* pSMComponent = Cast<USkeletalMeshComponent>(pComponents[i]);
				pSMComponent->SetCustomDepthStencilValue(150);
			}

			TArray<UActorComponent*> pStaticComponents = m_pSAOccupyInfoActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
			for (int32 i = 0; i < pStaticComponents.Num(); i++)
			{
				UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticComponents[i]);
				pSMComponent->SetCustomDepthStencilValue(150);
			}
			return true;
		}
	}
	/*else
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ASingleProgressGameMode* pSPGM = Cast<ASingleProgressGameMode>(pGM);
		m_pSAOccupyInfoActor->SetActorLocation(cursorLoc);
		TArray<FOverlapResult> overlapResults;
		float radius = (float)pSPGM->m_pShadowSkeletalMeshMap[m_curSelectSAOccupyInfo].occupyRadiusPercent * m_occupyActorRadius / 100.f;
		GetWorld()->OverlapMultiByChannel(overlapResults, cursorLoc, FQuat::Identity, ECC_EngineTraceChannel4, FCollisionShape::MakeBox(FVector(radius)));
		bool canBuild = true;
		for (int32 i = 0; i < overlapResults.Num(); i++)
		{
			if (!overlapResults[i].GetActor())
				continue;
			if (overlapResults[i].GetComponent()->ComponentHasTag(FName(TEXT("ShadowActor"))))
			{
				canBuild = false;
				break;
			}
		}

		TArray<UActorComponent*> pStaticMeshComponents = m_pSAOccupyInfoActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticMeshComponents[0]);
		if (!canBuild)
		{
			pSMComponent->SetCustomDepthStencilValue(250);
			//pSMComponent->SetVectorParameterValueOnMaterials(FName(TEXT("BaseColor")), FVector(1, 0, 0));
			return false;
		}
		else
		{
			pSMComponent->SetCustomDepthStencilValue(180);
			//pSMComponent->SetVectorParameterValueOnMaterials(FName(TEXT("BaseColor")), FVector(0, 1, 0));
			return true;
		}
	}*/
}

void ASingleProgressPlayerController::SetupBookControl(AAnimBook* pAnimBook)
{
	if (!m_pAnimBook)
	{
		m_pAnimBook = pAnimBook;
		//m_pAnimBook->m_pWidgetManager = m_pWidgetManager;
		FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);
		m_pDestinationLocation->AttachToComponent(PlayerCameraManager->GetRootComponent(), attachRules);
		m_pDestinationLocation->AddLocalOffset(FVector(m_bookDisFromCam.Z, m_bookDisFromCam.X, m_bookDisFromCam.Y), false, nullptr, ETeleportType::TeleportPhysics);
		m_pDestinationLocation->AddLocalRotation(m_bookViewAngle);
		m_pOriginLocation->SetWorldTransform(pAnimBook->GetActorTransform());
		m_bookOriginOpenAmount = pAnimBook->m_bookOpenTargetAmount;
		m_pMoveToCamera->SetPlayRate(1.5);
	}
}

void ASingleProgressPlayerController::MoveBookToPlayer(bool returnBook)
{
	m_moveEnded = returnBook;
	if (returnBook)
		m_pAnimBook->OpenToPage(m_bookOriginOpenAmount, 0.7, -1);
	else
		m_pAnimBook->OpenToPage(m_openBookHowWide, 0.7, -1);
	NotifyPlayMoveBookTimeLine(returnBook);
}

void ASingleProgressPlayerController::UpdateMoveBook(float time)
{
	FTransform originTransform = m_pOriginLocation->GetComponentTransform();
	FTransform offsetTransform = m_pOffsetLocation->GetComponentTransform();
	FTransform newTransform = UKismetMathLibrary::TLerp(originTransform, offsetTransform, time, ELerpInterpolationMode::QuatInterp);
	newTransform.SetScale3D(m_pAnimBook->GetActorScale3D());
	m_pAnimBook->SetActorTransform(newTransform, false, nullptr, ETeleportType::TeleportPhysics);
}

void ASingleProgressPlayerController::FinishMoveBook()
{
	if (m_moveEnded)
	{
		FDetachmentTransformRules detachRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
		m_pAnimBook->DetachFromActor(detachRules);
	}
	else
	{
		FAttachmentTransformRules attachRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
		m_pAnimBook->AttachToComponent(m_pDestinationLocation, attachRules);
	}
}

void ASingleProgressPlayerController::NotifyPlayMoveBookTimeLine_Implementation(bool returnBook)
{

}

