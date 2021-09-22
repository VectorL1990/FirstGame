// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../Game/BattleLevelGameModeBase.h"
#include "../../Game/Battle/RoguelikeBattleGameMode.h"
#include "../CollisionWarGameInstance.h"
#include "BattlePlayerCameraManager.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "BattleLevelPlayerController.h"



ABattleLevelPlayerController::ABattleLevelPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	m_isLeftKeyDownFlag = false;
}

void ABattleLevelPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
/*

	DealTickEvent(DeltaSeconds);

	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	if (!pCWGameInstance) return;
	if (pCWGameInstance->m_pGeometricRecognizer)
	{
		UGeometricRecognizer* pGeoRecognizer = pCWGameInstance->m_pGeometricRecognizer;
		for (int32 i=0; i<pGeoRecognizer->m_collectPts.Num(); i++)
		{
			FVector point(pGeoRecognizer->m_collectPts[i].X, pGeoRecognizer->m_collectPts[i].Y, 119.573);
			DrawDebugPoint(GetWorld(), point, 10, FColor::Red, false, 0.5);
		}
	}*/
}

bool ABattleLevelPlayerController::GetControllFromGameMode()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (!pGameMode) return false;
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (!pRGM || !pRGM->m_pPlayerCharacter) return false;
	UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
	ReadSkillCombineKeyList();
	ReadPlayerCharacterSkills(pCWGameInstance->m_curPlayerSPInfo.characterName);
	ReadPreAssignItemCardInfo();
	
	
	Possess(pRGM->m_pPlayerCharacter);
	m_viewTargetState = 0;
	m_hasBindSkillToMenu = true;
	//if (!pBaseFC) return true;
	//UClass* pTopDownCharacterClass = UCollisionWarBpFunctionLibrary::GetCharacterBlueprintClassDynamic("TopDownCharacter");
	/*UClass* pTopDownCharacterClass = pRGM->m_allCharacterInfo["TopDownCharacter"].pCharacterClass;
	m_pBuildViewTargetCharacter = GetWorld()->SpawnActor<ACharacter>(pTopDownCharacterClass, pBaseFC->GetActorLocation(), FRotator::ZeroRotator);*/
	return true;
}

void ABattleLevelPlayerController::TestAttributeReaction(TArray<uint8> atkAttributes)
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	TArray<FActiveAttributeReactionInfo> reactionInfos;
	pRGM->m_pPhysCalculator->CalCharacterAttributeReaction(pRGM->m_pPlayerCharacter, atkAttributes, reactionInfos);
}

void ABattleLevelPlayerController::Client_ApplyMoveLeft()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressLeftKey = true;

	if (m_isPressLeftKey && !m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = -1;
	else if (!m_isPressLeftKey && m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityX = 0;
}

void ABattleLevelPlayerController::ReleaseLeftKey()
{
	//if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressLeftKey = false;

	if (m_isPressLeftKey && !m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = -1;
	else if (!m_isPressLeftKey && m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityX = 0;
}

void ABattleLevelPlayerController::Client_ApplyMoveRight()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressRightKey = true;

	if (m_isPressLeftKey && !m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = -1;
	else if (!m_isPressLeftKey && m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityX = 0;
}

void ABattleLevelPlayerController::ReleaseRightKey()
{
	//if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressRightKey = false;

	if (m_isPressLeftKey && !m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = -1;
	else if (!m_isPressLeftKey && m_isPressRightKey) pBattleLevelGameMode->m_playerOperation.velocityX = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityX = 0;
}

void ABattleLevelPlayerController::Client_ApplyMoveUp()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressUpKey = true;

	if (m_isPressUpKey && !m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = -1;
	else if (!m_isPressUpKey && m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityY = 0;
	
}

void ABattleLevelPlayerController::ReleaseUpKey()
{
	//if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressUpKey = false;

	if (m_isPressUpKey && !m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = -1;
	else if (!m_isPressUpKey && m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityY = 0;
}

void ABattleLevelPlayerController::Client_ApplyMoveDown()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressDownKey = true;

	if (m_isPressUpKey && !m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = -1;
	else if (!m_isPressUpKey && m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityY = 0;
	
}

void ABattleLevelPlayerController::ReleaseDownKey()
{
	//if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	//引导部分
	//if (pBattleLevelGameMode->m_isInTutorial) return;
	m_isPressDownKey = false;

	if (m_isPressUpKey && !m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = -1;
	else if (!m_isPressUpKey && m_isPressDownKey) pBattleLevelGameMode->m_playerOperation.velocityY = 1;
	else pBattleLevelGameMode->m_playerOperation.velocityY = 0;
}

void ABattleLevelPlayerController::DealLeftClickDownEvent()
{
	if (m_isWidgetClick)
	{
		m_isWidgetClick = false;
		return;
	}
	FHitResult hitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, hitResult);
	if (!hitResult.bBlockingHit) return;
	bool hitSolid = false;
	if (hitResult.GetComponent() && hitResult.GetComponent()->ComponentHasTag(FName(TEXT("BasePhysActor"))))
	{
		//if (m_isInTutorial) return;
		hitSolid = true;
		ABasePhysActor* pPhysActor = Cast<ABasePhysActor>(hitResult.GetActor());
	}
	else if (hitResult.GetComponent() && hitResult.GetComponent()->ComponentHasTag(FName(TEXT("BaseCharacterMesh"))))
	{
		hitSolid = true;
		ABaseCharacter* pCharacter = Cast<ABaseCharacter>(hitResult.GetActor());

		if (!m_pHoveredCharacter)
		{
			SwitchHoverCharacter(hitResult.GetComponent(), pCharacter);
			m_pHoveredCharacter = pCharacter;
			LoadCharacterStatusMenu(pCharacter);
		}
		else
		{
			if (pCharacter != m_pHoveredCharacter)
			{
				SwitchHoverCharacter(hitResult.GetComponent(), hitResult.GetActor());
				if (m_pCharacterStatusMenu) DeleteMenu("CharacterStatus");
				m_pHoveredCharacter = pCharacter;
				LoadCharacterStatusMenu(pCharacter);
			}
		}
		SwitchHoverPhysActor(NULL);
		if (m_isInTutorial)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
			if (pBLGM->m_tutorialSteps.Num() > 0)
			{
				FString tutorialStepName = "ClickCharacter_" + pCharacter->m_characterClassName;
				if (pBLGM->m_tutorialSteps[0].operationName == tutorialStepName)
					pBLGM->DeleteTutorialStep();
			}
		}
		//m_pHoveredPhysActor = NULL;
	}

	if (!hitSolid)
	{
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		if (!pBattleLevelGameMode->m_pPlayerCharacter) return;

		if (!hitResult.bBlockingHit)
		{
			pBattleLevelGameMode->m_playerOperation.actionName = TEXT("NULL");
			return;
		}
		SwitchHoverPhysActor(NULL);

		if (m_isInTutorial && pBattleLevelGameMode->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "CloseTradeMenu";
			if (pBattleLevelGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
				pBattleLevelGameMode->DeleteTutorialStep();
		}
		SwitchHoverCharacter(NULL, NULL);
		if (m_pCharacterStatusMenu) DeleteMenu("CharacterStatus");
	}
}

void ABattleLevelPlayerController::DealLeftClickUpEvent()
{
	/*m_isLeftKeyDownFlag = false;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	if (!pGameModeBase) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBattleLevelGameMode) return;
	if (!pBattleLevelGameMode->m_pPlayerCharacter) return;
	if (m_isLeftKeyDownFlag && m_isPressSpellKey)
	{
		UGameInstance* pGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
		UCollisionWarGameInstance* pCWGameInstance = Cast<UCollisionWarGameInstance>(pGameInstance);
		if (!pCWGameInstance) return;
		if (pBattleLevelGameMode->m_playerOperation.actionName == "NULL")
		{
			int32 matchSkillNb = GeometryRecognize();
			if (matchSkillNb != -1 && pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills.Last()->m_canImplementFlag)
			{
				pBattleLevelGameMode->m_playerOperation.actionName = TEXT("ImplementSpellSkill");
				pBattleLevelGameMode->m_playerOperation.skillNb = -1;
				pBattleLevelGameMode->m_playerOperation.equipmentNb = pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb;
				pBattleLevelGameMode->m_playerOperation.collectPhysID = matchSkillNb;
			}
		}
		
	}
	else if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == TEXT("PMS_ContinuousPunch"))
	{
		//pPlayerCharacter->StopShortTask();
		if (pBattleLevelGameMode->m_playerOperation.actionName == "NULL")
		{
			pBattleLevelGameMode->m_playerOperation.actionName = TEXT("StopContinuousPunch");
		}
		
	}*/
}


void ABattleLevelPlayerController::DealTickEvent(float dT)
{

	FHitResult hitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, hitResult);
	if (!hitResult.bBlockingHit)
	{
		return;
	}

	if (m_viewTargetState == 0)
	{
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		if (!pGameModeBase) return;
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		if (!pBattleLevelGameMode || !pBattleLevelGameMode->m_pPlayerCharacter || pBattleLevelGameMode->m_pPlayerCharacter->m_Hp <= 0) return;
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch") return;

		FVector hitLoc = hitResult.Location;
		FVector hitLocCurLocOffset = hitLoc - pBattleLevelGameMode->m_pPlayerCharacter->GetActorLocation();
		FVector2D hitDir(hitLocCurLocOffset.X, hitLocCurLocOffset.Y);
		float yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(hitDir);
		pBattleLevelGameMode->m_playerOperation.yaw = yaw;
		//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, TEXT("PC 1st yaw: ") + FString::FromInt(yaw));
	}
}

void ABattleLevelPlayerController::DealRightClickDownEvent()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBattleLevelGameMode->m_pPlayerCharacter) return;
	if (m_isInTutorial && pBattleLevelGameMode->m_tutorialSteps.Num() > 0)
	{
		FString tutorialStepName = "RightClick";
		if (pBattleLevelGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
			pBattleLevelGameMode->DeleteTutorialStep();
	}

	if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch" &&
		!pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_canTransferState)
		return;
	if (pBattleLevelGameMode->m_playerOperation.actionName != "NULL") return;
	if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_canTransferState)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "BattleLevelPlayerController::DealRightClickDown can transfer");
		pBattleLevelGameMode->m_pPlayerCharacter->NotifyEndSkill();
	}
	FHitResult hitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, hitResult);
	if (!hitResult.bBlockingHit)
	{
		pBattleLevelGameMode->m_playerOperation.actionName = TEXT("NULL");
		return;
	}

	if (pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb == -1)
	{
		pBattleLevelGameMode->m_playerOperation.equipmentNb = -1;
		if ((pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_NULL" || pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_canTransferState)
			&& pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[m_curPressSkillNb] &&
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[m_curPressSkillNb]->m_canImplementFlag)
		{
			//m_curPressSkillNb = FindSkillByCombineKey();
			pBattleLevelGameMode->m_playerOperation.skillNb = m_curPressSkillNb;
			pBattleLevelGameMode->m_playerOperation.actionName = TEXT("ImplementSkill");
			pBattleLevelGameMode->m_playerOperation.skillClickLoc = hitResult.Location;
			m_curPressSkillNb = 0;
			ClearCombineKeyList();
		}
	}
	else
	{
		pBattleLevelGameMode->m_playerOperation.equipmentNb = pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb;
		if (!m_isPressBlockKey)
		{
			if (pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos[pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb]->m_pSkills[m_applySkillNb] &&
				pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos[pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb]->m_pSkills[m_applySkillNb]->m_canImplementFlag)
			{
				pBattleLevelGameMode->m_playerOperation.skillNb = m_applySkillNb;
				pBattleLevelGameMode->m_playerOperation.actionName = TEXT("ImplementSkill");
			}
		}
	}
	m_curPressSkillNb = 0;
}

void ABattleLevelPlayerController::ChangeOperationEquipmentNb(int32 nb)
{
	if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBattleLevelGameMode->m_pPlayerCharacter) return;
	if (m_isInTutorial && pBattleLevelGameMode->m_tutorialSteps.Num() > 0)
	{
		FString tutorialStepName = "ChangeSkillNb" + FString::FromInt(nb);
		if (pBattleLevelGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
			pBattleLevelGameMode->DeleteTutorialStep();
		/*if (pBattleLevelGameMode->m_tutorialSteps[0].operationName != tutorialStepName)
		{
			//pSPGM->DeleteTutorialStep();
			return;
		}
		else
			pBattleLevelGameMode->DeleteTutorialStep();*/
	}
	if (nb >= 0 && nb <= 6)
	{
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb == -1 && pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment)
		{
			//此时为简单的切换技能号
			
			m_curPressSkillNb = nb;
			if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[m_curPressSkillNb])
			{
				for (int32 i = 0; i < m_playerSkillInfos.Num(); i++)
				{
					if (m_playerSkillInfos[i].skillName != pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[m_curPressSkillNb]->m_skillName) continue;
					if (m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
						m_pBattleMenu->m_pSkillDescription->SetText(FText::FromString(m_playerSkillInfos[i].chSkillDescription));
					else
						m_pBattleMenu->m_pSkillDescription->SetText(FText::FromString(m_playerSkillInfos[i].skillDescription));
					break;
				}
			}
		}
	}
	else if (nb >= 7 && nb <= 8)
	{
		//根据装备栏卡牌名称判断选择的是什么装备
		int32 targetEquipNb = nb - 7;
		if (!m_pBattleMenu || targetEquipNb >= m_pBattleMenu->m_pEquipBattleCardList.Num() || 
			m_pBattleMenu->m_pEquipBattleCardList[targetEquipNb]->m_cardName == "NULL") return;
		for (int32 i=0; i< pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos.Num(); i++)
		{
			if (pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentName != m_pBattleMenu->m_pEquipBattleCardList[targetEquipNb]->m_cardName)
				continue;
			pBattleLevelGameMode->m_playerOperation.equipmentNb = i;
			pBattleLevelGameMode->m_playerOperation.actionName = "ChangeEquip";
			pBattleLevelGameMode->m_playerOperation.skillNb = 0;
			break;
		}
	}
}

void ABattleLevelPlayerController::ChangeOperationSkillNb(int32 nb)
{
	if (m_viewTargetState != 0) return;
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	if (!pGameModeBase) return;
	ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBattleLevelGameMode) return;
	if (!pBattleLevelGameMode->m_pPlayerCharacter) return;
	if (pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb == -1)
	{
		if (!pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment) return;
		if (nb < 0 || nb >= pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills.Num()) return;
		m_applySkillNb = nb;
	}
	else
	{
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb < 0 ||
			pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb >= pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos.Num())
			return;
		UCharacterEquipInfo* pEquipInfo = pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos[pBattleLevelGameMode->m_pPlayerCharacter->m_curEquipNb];
		if (!pEquipInfo) return;
		m_applySkillNb = nb;
	}
}

void ABattleLevelPlayerController::ClickBlockKey()
{
	if (m_viewTargetState == 0)
	{
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		if (!pBattleLevelGameMode->m_pPlayerCharacter || pBattleLevelGameMode->m_pPlayerCharacter->m_energyBallList <= 0) return;
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch" ||
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_Block" ||
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_Dodge") return;
		m_isPressBlockKey = true;
		pBattleLevelGameMode->m_playerOperation.actionName = TEXT("ImplementBlock");
		pBattleLevelGameMode->m_playerOperation.skillNb = -1;
		pBattleLevelGameMode->m_playerOperation.equipmentNb = -1;
	}
	
}

void ABattleLevelPlayerController::ClickDodgeKey()
{
	if (m_viewTargetState == 0)
	{
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		if (!pBattleLevelGameMode->m_pPlayerCharacter || pBattleLevelGameMode->m_pPlayerCharacter->m_energyBallList <= 0) return;
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch" ||
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_Block" ||
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString == "PMS_Dodge") return;
		m_isPressBlockKey = true;
		pBattleLevelGameMode->m_playerOperation.actionName = TEXT("ImplementDodge");
		pBattleLevelGameMode->m_playerOperation.skillNb = -1;
		pBattleLevelGameMode->m_playerOperation.equipmentNb = -1;
	}
}

void ABattleLevelPlayerController::ReleaseBlockKey()
{
	m_isPressBlockKey = false;
	if (m_viewTargetState == 0)
	{
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		if (!pBattleLevelGameMode->m_pPlayerCharacter) return;
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseAnimInstance->m_motionStateString != "PMS_Block") return;
		pBattleLevelGameMode->m_playerOperation.actionName = TEXT("CancelBlock");
		if (pBattleLevelGameMode->m_pPlayerCharacter->m_pBlockSkillPSComponent)
			pBattleLevelGameMode->m_pPlayerCharacter->m_pBlockSkillPSComponent->Deactivate();
		pBattleLevelGameMode->m_pPlayerCharacter->FadeCSCharacter();
	}
}

int32 ABattleLevelPlayerController::FindMatchRecognizeSkill(FString recognizeString)
{
	return 1;
}

void ABattleLevelPlayerController::ReadSkillCombineKeyList_Implementation()
{

}

void ABattleLevelPlayerController::WritePlayerSkillInfo(const FCharacterSkillAvailableInfo& skillInfo)
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBLGM->m_pPlayerCharacter) return;
	if (skillInfo.isInitial)
	{
		pBLGM->m_pPlayerCharacter->m_pBaseEquipment->m_skillClassMap.Add(skillInfo.skillName, skillInfo.skillClass);
		m_playerSkillInfos.Add(skillInfo);
	}
	else
	{
		UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
		UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
		if (!pCWGI->m_curPlayerSPInfo.availableExtraSkillList.Contains(skillInfo.skillName)) return;
		pBLGM->m_pPlayerCharacter->m_pBaseEquipment->m_skillClassMap.Add(skillInfo.skillName, skillInfo.skillClass);
		m_playerSkillInfos.Add(skillInfo);
	}
}

void ABattleLevelPlayerController::ReadPreAssignItemCardInfo()
{
	AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGameModeBase);
	if (!pBLGM->m_pPlayerCharacter) return;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i< pCWGI->m_curPlayerSPInfo.availableEquipList.Num(); i++)
	{
		pBLGM->m_pPlayerCharacter->AddNewItem(pCWGI->m_curPlayerSPInfo.availableEquipList[i]);
	}
}

void ABattleLevelPlayerController::ClearCombineKeyList()
{
	m_combinationKeys = "";
	if (!m_pBattleMenu) return;
	m_pBattleMenu->UpdateCombineKeyList(m_combinationKeys);
}

void ABattleLevelPlayerController::AppendCombineKey(FString key)
{
	if (!m_basicKeyMap.Contains(key)) return;
	m_combinationKeys.Append(m_basicKeyMap[key]);
	if (!m_pBattleMenu) return;
	m_pBattleMenu->UpdateCombineKeyList(m_combinationKeys);
}

int32 ABattleLevelPlayerController::FindSkillByCombineKey()
{
	for (int32 i=0; i<m_playerSkillInfos.Num(); i++)
	{
		if (m_playerSkillInfos[i].combineKeyList != m_combinationKeys) continue;
		AGameModeBase* pGameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGameModeBase);
		for (int32 j = 0; j < pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills.Num(); j++)
		{
			if (!pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[j] ||
				pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[j]->m_skillName != m_playerSkillInfos[i].skillName)
				continue;
			if (!pBattleLevelGameMode->m_pPlayerCharacter->m_pBaseEquipment->m_pSkills[j]->m_canImplementFlag)
				return 0;
			if (m_isInTutorial && pBattleLevelGameMode->m_tutorialSteps.Num() > 0)
			{
				FString tutorialStepName = "FindSkill_" + m_playerSkillInfos[i].skillName;
				if (pBattleLevelGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
					pBattleLevelGameMode->DeleteTutorialStep();
			}
			return j;
		}
		break;
	}
	return 0;
}

void ABattleLevelPlayerController::ChangeOperationSkillNbByClick(int32 cardNb, bool skillOrEquip)
{
	//int32 clickCardNb = cardNb;
	//clickCardNb -= 1;
	if (m_isInTutorial)
	{
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGM);
		if (pBattleLevelGameMode->m_tutorialSteps.Num() > 0)
		{
			FString tutorialStepName = "ChangeOperationSkillNbByClick" + FString::FromInt(cardNb);
			if (pBattleLevelGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
				pBattleLevelGameMode->DeleteTutorialStep();
		}
		/*if (pBattleLevelGameMode->m_tutorialSteps[0].operationName != tutorialStepName)
		{
			//pSPGM->DeleteTutorialStep();
			return;
		}
		else
			pBattleLevelGameMode->DeleteTutorialStep();*/
	}
	if (skillOrEquip)
	{
		if (!m_pBattleMenu->m_isInSkillDomain)
		{
			if (m_viewTargetState != 1) return;
			//说明此时为FoundationCharacter卡牌范畴
			//m_curSelectFCNb = m_pBattleMenu->m_curFCMenuPhase*m_pBattleMenu->m_pSkillBattleCardList.Num() + cardNb;
			m_curSelectFCNb = cardNb;
			int32 i = 0;
			for (TMap<FString, FFoundationCharacterInfo>::TConstIterator iter = m_FCInfos.CreateConstIterator(); iter; ++iter)
			{
				if (i == m_curSelectFCNb)
				{
					m_curFCOccupyInfo = iter->Value.occupyInfo;
					break;
				}
				i += 1;
			}
		}
		else
		{
			if (m_viewTargetState != 0) return;
			m_curPressSkillNb = cardNb + 1;
		}
	}
	else
	{
		FString equipName = m_pBattleMenu->m_pEquipBattleCardList[cardNb]->m_cardName;
		if (equipName == "NULL") return;
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ABattleLevelGameModeBase* pBattleLevelGameMode = Cast<ABattleLevelGameModeBase>(pGM);
		for (int32 i=0; i< pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos.Num(); i++)
		{
			if (pBattleLevelGameMode->m_pPlayerCharacter->m_pEquipmentInfos[i]->m_equipmentName != equipName) continue;
			pBattleLevelGameMode->m_playerOperation.equipmentNb = i;
			pBattleLevelGameMode->m_playerOperation.actionName = "ChangeEquip";
			break;
		}
	}
}

int32 ABattleLevelPlayerController::GeometryRecognize()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	if (!pBattleGameMode->m_pGeometricRecognizer) return -1;
	FRecognitionResult recognizeResult = pBattleGameMode->m_pGeometricRecognizer->Recognize();
	pBattleGameMode->m_pGeometricRecognizer->m_collectPts.Empty();
	pBattleGameMode->m_pGeometricRecognizer->m_curCollectTime = 0;
	int32 matchSkillNb = FindMatchRecognizeSkill(recognizeResult.name);
	return matchSkillNb;
}

void ABattleLevelPlayerController::PauseOrUnPauseGame()
{
	if (m_isPauseMenuOn) return;
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (!pGameMode) return;
	ARoguelikeBattleGameMode* pRoguelikeGameMode = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (m_isInTutorial && pRoguelikeGameMode->m_tutorialSteps.Num() > 0)
	{
		FString tutorialStepName = "Pause";
		if (pRoguelikeGameMode->m_tutorialSteps[0].operationName == tutorialStepName)
		{
			pRoguelikeGameMode->DeleteTutorialStep();
		}
	}
	if (!m_isGamePaused)
	{
		pRoguelikeGameMode->m_tickFlag = false;
		m_isGamePaused = true;
		UGameplayStatics::SetGamePaused(this, true);
	}
	else
	{
		pRoguelikeGameMode->m_tickFlag = true;
		m_isGamePaused = false;
		UGameplayStatics::SetGamePaused(this, false);
	}
}

void ABattleLevelPlayerController::NotifyPlayPPTimeLine_Implementation(FVector playerLoc, bool switchToFCDomain)
{

}

void ABattleLevelPlayerController::SwitchViewTarget()
{
	
	if (m_viewTargetState == 3)
	{
		m_viewTargetState = 0;
		AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
		ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
		if (pBattleGameMode->m_pPlayerCharacter)
			Possess(pBattleGameMode->m_pPlayerCharacter);
	}
	else
	{
		m_viewTargetState = 2;
		Possess(m_pBuildViewTargetCharacter);
	}
}

bool ABattleLevelPlayerController::TellWhetherFitTutorialStep(const FString& stepName)
{
	if (!m_isInTutorial) return true;
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
	if (pBLGM->m_tutorialSteps.Num() <= 0) return true;
	if (pBLGM->m_tutorialSteps[0].operationName == stepName)
	{
		pBLGM->DeleteTutorialStep();
		return true;
	}
	else return false;
	/*if (pBLGM->m_tutorialSteps[0].operationName != stepName)
	{
		//pSPGM->DeleteTutorialStep();
		return false;
	}
	else
	{
		pBLGM->DeleteTutorialStep();
		return true;
	}*/
}

void ABattleLevelPlayerController::EndTutorial()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
	if (pBLGM->m_tutorialSteps.Num() <= 0 || !m_pTutorialMenu) return;
	pBLGM->m_tutorialSteps.Empty();
	m_pTutorialMenu->NotifyFadeOut();
}

void ABattleLevelPlayerController::ApplyBackToMainMenu()
{
	/*PlayerCameraManager->StartCameraFade(0.f, 1.f, m_waitToFadeTime, FLinearColor::Black, false, true);
	/ *pSPGM->StopTick();
	pSPGM->HideAllCardWidget();* /
	//if (m_pSaveMenu) m_pSaveMenu->AskFadeOut();
	if (m_pESCMenu) m_pESCMenu->AskMenuFadeOut();
	m_pBattleMenu->AskFadeOut();
	GetWorldTimerManager().SetTimer(m_timerHandle, this, &ABattleLevelPlayerController::WaitToMainMenu, m_waitToFadeTime + 0.3f, false);*/
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoginMap")));
}

void ABattleLevelPlayerController::WaitToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoginMap")));
}

void ABattleLevelPlayerController::EndBattle()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	pRGM->m_isBattleTestFinish = true;
}

void ABattleLevelPlayerController::NotifyShakeCamera_Implementation()
{

}

void ABattleLevelPlayerController::LoadLoadMenu_Implementation()
{

}

void ABattleLevelPlayerController::LoadBattleMenu_Implementation()
{

}

void ABattleLevelPlayerController::LoadESCMenu()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	if (pRGM->m_tickFlag) PauseOrUnPauseGame();
	m_pESCMenu = UWidgetBlueprintFunctionLibrary::CreateSimpleMenu(m_pBattleMenu->m_pWidgetManager, 3, 1);
	m_pESCMenu->AddToViewport();
	m_isPauseMenuOn = true;
}

void ABattleLevelPlayerController::LoadConcludeScoresMenu_Implementation()
{

}

void ABattleLevelPlayerController::LoadConcludePrizeMenu_Implementation()
{

}

void ABattleLevelPlayerController::LoadConcludeEXPMenu_Implementation()
{

}

void ABattleLevelPlayerController::LoadConcludeTextMenu_Implementation(const TArray<FString>& text)
{

}

void ABattleLevelPlayerController::LoadChangeRoundTextMenu_Implementation(const TArray<FString>& text)
{

}

void ABattleLevelPlayerController::LoadTradeItemSelectMenu_Implementation()
{
	
}

void ABattleLevelPlayerController::LoadSkillTreeMenu_Implementation()
{
	
}

void ABattleLevelPlayerController::DeleteMenu(FString menuName)
{
	if (menuName == "CharacterStatus")
	{
		if (!m_pCharacterStatusMenu) return;
		m_pCharacterStatusMenu->RemoveFromRoot();
		if (m_pCharacterStatusMenu->IsValidLowLevel())
			m_pCharacterStatusMenu->ConditionalBeginDestroy();
		m_pCharacterStatusMenu = NULL;
		m_pHoveredCharacter = NULL;
		if (m_isInTutorial)
		{
			AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
			ABattleLevelGameModeBase* pBLGM = Cast<ABattleLevelGameModeBase>(pGM);
			if (pBLGM->m_tutorialSteps.Num() > 0)
			{
				FString tutorialStepName = "CloseCharacterState";
				if (pBLGM->m_tutorialSteps[0].operationName == tutorialStepName)
					pBLGM->DeleteTutorialStep();
			}
		}
	}
	else if (menuName == "TutorialMenu")
	{
		if (!m_pTutorialMenu) return;
		m_pTutorialMenu->RemoveFromParent();
		if (m_pTutorialMenu->IsValidLowLevel())
			m_pTutorialMenu->ConditionalBeginDestroy();
		m_pTutorialMenu = NULL;
	}
	m_curMenuName = "";
}

void ABattleLevelPlayerController::SwitchMenu(FString menuName)
{
	if (m_curMenuName == menuName) return;
	if (m_curMenuName == "CharacterStatus")
	{
		DeleteMenu("CharacterStatus");
		SwitchHoverCharacter(NULL, NULL);
		SwitchHoverPhysActor(NULL);
	}
	m_curMenuName = menuName;
	
}

void ABattleLevelPlayerController::UpdateInitialResources()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	if (!pGameMode) return;
	ARoguelikeBattleGameMode* pRoguelikeGameMode = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (!m_pBattleMenu) return;
	m_pBattleMenu->NotifyHurtLevelChange(pRoguelikeGameMode->m_scoreLevelMaps[1], pRoguelikeGameMode->m_scoreLevelMaps[2], pRoguelikeGameMode->m_scoreLevelMaps[3],
		pRoguelikeGameMode->m_scoreLevelMaps[4], pRoguelikeGameMode->m_scoreLevelMaps[5]);
}

/*
void ABattleLevelPlayerController::AddPreAssignCards()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (!pRGM->m_pPlayerCharacter) return;
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	for (int32 i=0; i< pCWGI->m_curPlayerSPInfo.cardInfoList.Num(); i++)
	{
		FItemCardCondition cardCondition;
		if (!m_itemCardInfoMap.Contains(pCWGI->m_curPlayerSPInfo.cardInfoList[i].cardName)) continue;
		int32 id = pRGM->m_pPlayerCharacter->GenCardID();
		cardCondition.cardName = pCWGI->m_curPlayerSPInfo.cardInfoList[i].cardName;
		cardCondition.cardType = m_itemCardInfoMap[pCWGI->m_curPlayerSPInfo.cardInfoList[i].cardName].cardType;
		pRGM->m_pPlayerCharacter->m_allCardMap.Add(id, cardCondition);
		if (pCWGI->m_curPlayerSPInfo.cardInfoList[i].cardType != 2) continue;
		TSubclassOf<class UObject> equipmentInfoClass = pRGM->m_characterEquipInfoClassMap[pCWGI->m_curPlayerSPInfo.cardInfoList[i].cardName];
		UCharacterEquipInfo* pEquipInfo = NewObject<UCharacterEquipInfo>(pRGM->m_pPlayerCharacter, equipmentInfoClass);
		pEquipInfo->m_equipmentNb = 1;
		pEquipInfo->InitialEquipInfo();
		pRGM->m_pPlayerCharacter->m_pEquipmentInfos.Add(pEquipInfo);
	}
}*/

void ABattleLevelPlayerController::LoadCharacterStatusMenu(ABaseCharacter* pCharacter)
{
	m_pCharacterStatusMenu = UWidgetBlueprintFunctionLibrary::CreateCharacterStatusMenu(m_pBattleMenu->m_pWidgetManager);
	m_pCharacterStatusMenu->LoadBaseCharacterInfo(pCharacter);
	m_pCharacterStatusMenu->AddToViewport();
	m_curMenuName = "CharacterStatus";

	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (!pCWGI->m_doneTutorialSteps.Contains(pRGM->m_fixTutorialSerialNames[2])) pRGM->RefreshTutorial(pRGM->m_fixTutorialSerialNames[2], true, 2);
	else pRGM->RefreshTutorial("NULL", false, 2);
}

void ABattleLevelPlayerController::LoadTutorialmenu()
{
	m_pTutorialMenu = UWidgetBlueprintFunctionLibrary::CreateTutorialMenu(m_pWidgetManager, 1);
	if (!m_pTutorialMenu) return;
	m_pTutorialMenu->AddToViewport();
}

void ABattleLevelPlayerController::LoadTutorialSerialMenu()
{
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
	FTutorialStepSerial tutorialSerial = pRGM->ReadTutorialInfoByName(pRGM->m_curTutorialName);
	UTTutorialMenu* pTutorialMenu = CreateWidget<UTTutorialMenu>(this, m_pTutorialMenuClass);
	//pTutorialMenu->m_curTutorialSerialName = pSPGM->m_curTutorialName;
	pTutorialMenu->m_type = 1;
	pTutorialMenu->m_pWidgetManager = m_pBattleMenu->m_pWidgetManager;
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

void ABattleLevelPlayerController::InitialTutorial()
{
	if (!m_isInTutorial) return;
	LoadTutorialmenu();
	AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pBLGM = Cast<ARoguelikeBattleGameMode>(pGM);
	pBLGM->UpdateTutorialStep();
}

void ABattleLevelPlayerController::SwitchHoverCharacter(UPrimitiveComponent* pHitComponent, AActor* pHitActor)
{
	if (!pHitActor || !pHitComponent)
	{
		/** 说明没有点击中任何东西
		* 1. 将当前Hover的角色设置为NULL
		* 2. 将角色详情Menu关闭
		* 3. 将Hover角色的高亮材质设置为原色
		*/
		if (m_pHoveredCharacter)
		{
			TArray<UActorComponent*> pOriginSKMesh = m_pHoveredCharacter->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			if (pOriginSKMesh.Num() > 0)
			{
				for (int32 i = 0; i < pOriginSKMesh.Num(); i++)
				{
					USkeletalMeshComponent* pSKComponent = Cast<USkeletalMeshComponent>(pOriginSKMesh[i]);
					pSKComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 0);
				}
			}
		}
		if (m_pCharacterStatusMenu) m_pCharacterStatusMenu->ClearAllInfo();
	}
	else
	{
		/** 说明点击中的是BaseCharacter
		* 1. 如当前HoverCharacter不为空
		*   1.1 将HoverCharacter切换为当前点击的角色
		*   1.2 重新设置角色详情Menu内容
		*   1.3 将原HoverCharacter的高亮去掉
		*   1.4 设置新Hover角色高亮
		*/
		TArray<UActorComponent*> pSKMesh = pHitActor->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
		if (pSKMesh.Num() > 0)
		{
			for (int32 i = 0; i< pSKMesh.Num(); i++)
			{
				USkeletalMeshComponent* pSKComponent = Cast<USkeletalMeshComponent>(pSKMesh[i]);
				pSKComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 1);
			}
		}

		if (m_pHoveredCharacter)
		{
			TArray<UActorComponent*> pOriginSKMesh = m_pHoveredCharacter->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			if (pOriginSKMesh.Num() > 0)
			{
				for (int32 i = 0; i < pOriginSKMesh.Num(); i++)
				{
					USkeletalMeshComponent* pSKComponent = Cast<USkeletalMeshComponent>(pOriginSKMesh[i]);
					pSKComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 0);
				}
			}
		}
		if (m_pCharacterStatusMenu)
		{
			m_pCharacterStatusMenu->ClearAllInfo();
			m_pCharacterStatusMenu->LoadBaseCharacterInfo(m_pHoveredCharacter);
		}
	}
}

void ABattleLevelPlayerController::SwitchHoverPhysActor(AActor* pActor)
{
	if (!pActor)
	{
		/** 说明没有点击中任何东西
		* 1. 将当前Hover的角色设置为NULL
		* 2. 将角色详情Menu关闭
		* 3. 将Hover角色的高亮材质设置为原色
		*/
		if (m_pHoveredPhysActor)
		{
			TArray<UActorComponent*> pStaticMeshComponents = m_pHoveredPhysActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
			for (int32 i=0; i<pStaticMeshComponents.Num(); i++)
			{
				UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticMeshComponents[i]);
				pSMComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 0);
			}
		}
	}
	else
	{
		/** 说明点击中的是BaseCharacter
		* 1. 如当前HoverCharacter不为空
		*   1.1 将HoverCharacter切换为当前点击的角色
		*   1.2 重新设置角色详情Menu内容
		*   1.3 将原HoverCharacter的高亮去掉
		*   1.4 设置新Hover角色高亮
		*/
		TArray<UActorComponent*> pStaticMeshComponents = pActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		for (int32 i=0; i<pStaticMeshComponents.Num(); i++)
		{
			UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticMeshComponents[i]);
			pSMComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 1);
		}

		if (m_pHoveredPhysActor)
		{
			TArray<UActorComponent*> pStaticMeshComponents = m_pHoveredPhysActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
			for (int32 i=0; i<pStaticMeshComponents.Num(); i++)
			{
				UStaticMeshComponent* pSMComponent = Cast<UStaticMeshComponent>(pStaticMeshComponents[i]);
				pSMComponent->SetScalarParameterValueOnMaterials(FName(TEXT("HoveredHighlightScale")), 0);
			}
		}
	}
}

bool ABattleLevelPlayerController::FindCardCombineInfo(TArray<FString> inputList, FString FCName, FCardCombineInfo& combineInfo)
{
	FString row1;
	FString row2;
	//标注运算方式，0为正常减法，1为加法
	uint8 calculationType = 0;
	for (int32 i = 0; i < inputList.Num(); i++)
	{
		FString nbStr;
		if (inputList[i] == "NULL")
			nbStr.Append("0");
		else if (inputList[i].Contains("_D_"))
		{
			nbStr = inputList[i].RightChop(10);
			if (calculationType == 0) calculationType = 1;
		}
		else if (inputList[i].Contains("_C_")) nbStr = inputList[i].RightChop(10);
		else if (inputList[i].Contains("_H_"))
		{
			nbStr = inputList[i].RightChop(10);
			if (calculationType == 0) calculationType = 1;
		}
		else if (inputList[i].Contains("_S_")) nbStr = inputList[i].RightChop(10);

		if (i < 6)
			row1.Append(nbStr);
		else
			row2.Append(nbStr);
	}
	//先进行运算统计，然后进行
	int32 calResult = 0;
	int32 row1Nb = FCString::Atoi(*row1);
	int32 row2Nb = FCString::Atoi(*row2);
	if (calculationType == 0)
		calResult = row1Nb - row2Nb;
	else
		calResult = row1Nb + row2Nb;

	if (calResult <= 0) calResult = -calResult;

	for (int32 i = 0; i < m_cardCombineInfo.Num(); i++)
	{
		if (m_cardCombineInfo[i].triggerFCName != FCName || m_cardCombineInfo[i].inputNb != calResult) continue;
		combineInfo = m_cardCombineInfo[i];
		return true;
	}
	return false;
}

void ABattleLevelPlayerController::TestRecoverHpFull()
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	if (!pGameMode) return;
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (!pRGM->m_pPlayerCharacter) return;
	pRGM->m_pPlayerCharacter->m_Hp = pRGM->m_pPlayerCharacter->m_originHp;
}

void ABattleLevelPlayerController::TestSpawnEnermy(int32 level)
{
	AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	if (!pGameMode) return;
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	pRGM->m_pAIManager->m_testCrisitLevel = level;
	pRGM->m_pAIManager->m_testPressSpawnKey = true;
}

void ABattleLevelPlayerController::TestDrawNavMeshLine()
{
	/*AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGameMode);
	if (!pRGM->m_pRecastDetourObject) return;

	if (!pRGM->m_pRecastDetourObject->m_pSample) return;
	/ *if (pRGM->m_pPlayerCharacter)
	{
		FString playerLocStr = FString::SanitizeFloat(pRGM->m_pPlayerCharacter->GetActorLocation().X) + "," + 
			FString::SanitizeFloat(pRGM->m_pPlayerCharacter->GetActorLocation().Y) + "," + 
			FString::SanitizeFloat(pRGM->m_pPlayerCharacter->GetActorLocation().Z);
		DrawDebugString(GetWorld(), pRGM->m_pPlayerCharacter->GetActorLocation(), playerLocStr, 0, FColor::Red, 5);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, playerLocStr);
	}* /
	//const dtNavMesh& navMesh = *(m_pSample->m_navMesh);
	int32 maxTileNb = (*pRGM->m_pRecastDetourObject->m_pSample->m_navMesh).getMaxTiles();
	float maxX = 0;
	float minX = 0;
	float maxY = 0;
	float minY = 0;
	for (int i = 0; i < maxTileNb; ++i)
	{
		const dtMeshTile* tile = (*pRGM->m_pRecastDetourObject->m_pSample->m_navMesh).getTile(i);
		if (!tile->header) continue;
		for (int j = 0; j < tile->header->polyCount; ++j)
		{
			const dtPoly* p = &tile->polys[j];
			if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION)	// Skip off-mesh links.
				continue;

			const dtPolyDetail* pd = &tile->detailMeshes[j];

			for (int k = 0; k < pd->triCount; ++k)
			{
				const unsigned char* t = &tile->detailTris[(pd->triBase + k) * 4];
				if (t[0] >= p->vertCount || t[1] >= p->vertCount || t[2] >= p->vertCount) return;
				float* ptRaw1 = &tile->verts[p->verts[t[0]] * 3];
				float* ptRaw2 = &tile->verts[p->verts[t[1]] * 3];
				float* ptRaw3 = &tile->verts[p->verts[t[2]] * 3];
				FVector pt1(ptRaw1[2] * 100, ptRaw1[0] * 100, ptRaw1[1] + pRGM->m_pRecastDetourObject->m_relativeDebugLineHeight + 100);
				FVector pt2(ptRaw2[2] * 100, ptRaw2[0] * 100, ptRaw2[1] + pRGM->m_pRecastDetourObject->m_relativeDebugLineHeight + 100);
				FVector pt3(ptRaw3[2] * 100, ptRaw3[0] * 100, ptRaw3[1] + pRGM->m_pRecastDetourObject->m_relativeDebugLineHeight + 100);
				FString pt1Str = FString::SanitizeFloat(pt1.X) + "," + FString::SanitizeFloat(pt1.Y) + "," + FString::SanitizeFloat(pt1.Z);
				FString pt2Str = FString::SanitizeFloat(pt2.X) + "," + FString::SanitizeFloat(pt2.Y) + "," + FString::SanitizeFloat(pt2.Z);
				FString pt3Str = FString::SanitizeFloat(pt3.X) + "," + FString::SanitizeFloat(pt3.Y) + "," + FString::SanitizeFloat(pt3.Z);
				/ *GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt1Str);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt2Str);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, pt3Str);* /
				DrawDebugLine(GetWorld(), pt1, pt2, FColor::Cyan, false, pRGM->m_pRecastDetourObject->m_relativeDebugLineTime, 0, 10);
				DrawDebugLine(GetWorld(), pt2, pt3, FColor::Cyan, false, pRGM->m_pRecastDetourObject->m_relativeDebugLineTime, 0, 10);
				DrawDebugLine(GetWorld(), pt3, pt1, FColor::Cyan, false, pRGM->m_pRecastDetourObject->m_relativeDebugLineTime, 0, 10);
				/ *DrawDebugPoint(GetWorld(), pt1, 25, FColor::Green, false, 5, 0);
				DrawDebugPoint(GetWorld(), pt2, 25, FColor::Green, false, 5, 0);
				DrawDebugPoint(GetWorld(), pt3, 25, FColor::Green, false, 5, 0);* /
				//DrawDebugString(GetWorld(), pt1, pt1Str, 0, FColor::White, 5);
				if (pt1.X >= maxX) maxX = pt1.X;
				if (pt1.X <= minX) minX = pt1.X;
				if (pt1.Y >= maxY) maxY = pt1.Y;
				if (pt1.Y <= minY) minY = pt1.Y;

				if (pt2.X >= maxX) maxX = pt2.X;
				if (pt2.X <= minX) minX = pt2.X;
				if (pt2.Y >= maxY) maxY = pt2.Y;
				if (pt2.Y <= minY) minY = pt2.Y;

				if (pt3.X >= maxX) maxX = pt3.X;
				if (pt3.X <= minX) minX = pt3.X;
				if (pt3.Y >= maxY) maxY = pt3.Y;
				if (pt3.Y <= minY) minY = pt3.Y;
			}
		}
	}*/
	/*GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(minX));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(maxX));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(minY));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::SanitizeFloat(maxY));*/

	//pRGM->m_pRecastDetourObject->DrawDebug();
}

