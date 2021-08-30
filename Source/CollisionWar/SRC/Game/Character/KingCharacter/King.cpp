// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../../Base/Battle/BattleLevelPlayerController.h"
#include "../../Battle/RoguelikeBattleGameMode.h"
#include "CanvasPanelSlot.h"
#include "../../Battle/Physics/PhysPointSonClass/ProjectilePoint.h"
#include "King.h"




AKing::AKing()
{
	m_pressLeftKeyFlag = false;
	m_pressRightKeyFlag = false;
	m_pressUpKeyFlag = false;
	m_pressDownKeyFlag = false;
	m_pressSpellKeyFlag = false;
	//m_characterIdleMotionState = ECharacterIdleMotionType::CHAMT_HoldWeapon;
}

void AKing::Tick(float DeltaSeconds)
{
	if (m_Hp <= 0)
	{
		m_curLogicVelocity.X = 0;
		m_curLogicVelocity.Y = 0;
		m_pBaseAnimInstance->m_speed = 0;
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		return;
	}

	if (m_pBaseAnimInstance && m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch")
	{
		if (m_curHurtImmuneTimeCount < m_hurtImmuneTime)
			m_curHurtImmuneTimeCount += DeltaSeconds;
	}
	UpdateAllSkills(DeltaSeconds);
	UpdateAllTimeDilationEffects(DeltaSeconds);
	UpdateAllAttributes(DeltaSeconds);
	RecoverEnergyBall(DeltaSeconds);

	if (m_logicVelOperation.X == 0 && m_logicVelOperation.Y == 0 || m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch")
	{
		m_curLogicVelocity.X = 0;
		m_curLogicVelocity.Y = 0;
		if (m_pBaseAnimInstance)
		{
			m_pBaseAnimInstance->m_speed = 0;
			if (m_pBaseAnimInstance->m_motionStateString != "PMS_TransientPunch")
			{
				FVector modifyDirVector(m_logicForwardOperation.X, m_logicForwardOperation.Y, 0);
				FRotator modifyRotator = modifyDirVector.ToOrientationRotator();
				SetActorRotation(modifyRotator);
			}
		}
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		
	}
	else
	{
		
		//FLogicVec2D deltaVel = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(m_logicVelOperation, m_acc);
		FVector2D deltaVel = m_logicVelOperation;
		deltaVel.Normalize();
		deltaVel *= m_acc;
		FVector2D nextLogicVel = m_curLogicVelocity + deltaVel;
		int32 scaleMaxSPD = m_MaxSPD * m_speedRatePercent / 100;
		if (nextLogicVel.Size() >= scaleMaxSPD)
		{
			nextLogicVel.Normalize();
			nextLogicVel *= scaleMaxSPD;
			/*FLogicVec2D maxSPDVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(nextLogicVel, scaleMaxSPD);
			nextLogicVel = maxSPDVec;*/
		}
		FVector nextVelocity(nextLogicVel.X, nextLogicVel.Y, 0);
		FVector nextLoc = GetActorLocation() + nextVelocity * DeltaSeconds;
		/*if (nextLoc.X >= m_maxLocX || nextLoc.X <= m_minLocX || nextLoc.Y >= m_maxLocY || nextLoc.Y <= m_minLocY)
		{
			m_curLogicVelocity.X = 0;
			m_curLogicVelocity.Y = 0;
			m_pBaseAnimInstance->m_speed = 0;
			GetCharacterMovement()->Velocity = FVector::ZeroVector;
			return;
		}*/

		/*TArray<FOverlapResult> hitResults;
		FCollisionResponseParams responseParams;
		responseParams.CollisionResponse.SetAllChannels(ECR_Overlap);
		FVector capsuleExtent(1, 1, 100);
		GetWorld()->OverlapMultiByChannel(hitResults, nextLoc, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeCapsule(capsuleExtent),
			FCollisionQueryParams::DefaultQueryParam, responseParams);
		/ *GetWorld()->SweepMultiByChannel(hitResults, GetActorLocation(), nextLoc, FQuat::Identity, ECollisionChannel::ECC_Visibility,
			FCollisionShape::MakeSphere(m_characterRadius + 2), FCollisionQueryParams::DefaultQueryParam, responseParams);* /
		for (int32 i = 0; i < hitResults.Num(); i++)
		{
			if (!hitResults[i].GetComponent() || !hitResults[i].GetComponent()->ComponentHasTag("Boundary")) continue;
			m_curLogicVelocity.X = 0;
			m_curLogicVelocity.Y = 0;
			m_pBaseAnimInstance->m_speed = 0;
			GetCharacterMovement()->Velocity = FVector::ZeroVector;
			return;
		}*/
		FVector modifyDirVector(m_logicForwardOperation.X, m_logicForwardOperation.Y, 0);
		FRotator modifyRotator = modifyDirVector.ToOrientationRotator();
		SetActorRotation(modifyRotator);
		nextLoc.Z = m_defaultHeight + m_relativeHeight;

		FCollisionQueryParams collisionQueryParam;
		FCollisionShape collisionShape = FCollisionShape::MakeCapsule(GetCapsuleComponent()->GetScaledCapsuleRadius(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		//collisionShape.SetCapsule(GetCapsuleComponent()->extent)
		bool isTrap = false;
		bool isNextLocOutTrap = false;
		TArray<int32> needToDeleteNb;
		for (TMap<int32, ABasePhysGeo*>::TConstIterator iter = m_pRestrictMoveEffect.CreateConstIterator(); iter; ++iter)
		{
			if (!iter->Value || !iter->Value->IsValidLowLevel() || !iter->Value->m_isGeoValid)
			{
				needToDeleteNb.Add(iter->Key);
				continue;
			}
			isTrap = true;
			if (!iter->Value->m_pBasicComponent->OverlapComponent(nextLoc, FQuat::Identity, collisionShape))
			{
				//˵������ײ���������ƶ�
				
				isNextLocOutTrap = true;
				//break;
			}
		}
		for (int32 i = 0; i < needToDeleteNb.Num(); i++)
		{
			m_pRestrictMoveEffect.Remove(needToDeleteNb[i]);
		}

		/*if (isTrap && isNextLocOutTrap)
		{
			m_curLogicVelocity.X = 0;
			m_curLogicVelocity.Y = 0;
			if (m_pBaseAnimInstance)
				m_pBaseAnimInstance->m_speed = 0;
			GetCharacterMovement()->Velocity = FVector::ZeroVector;
			return;
		}*/

		m_curLogicVelocity = nextLogicVel;
		m_pBaseAnimInstance->m_speed = m_curLogicVelocity.Size();
		GetCharacterMovement()->Velocity = FVector(m_curLogicVelocity.X, m_curLogicVelocity.Y, 0);
		
		SetActorLocation(nextLoc);
			

		//m_curLogicForwardDir = m_logicForwardOperation;
		
	}
	/*if (m_shouldCountToReload)
	{
		if (m_curReloadTime >= m_reloadTime)
		{
			m_shouldCountToReload = false;
			m_curReloadTime = 0.f;
			MessAllSkillCard();
			APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
			ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
			pBattlePC->m_pBattleMenu->StopReload();
			return;
		}
		m_curReloadTime += DeltaSeconds;
	}*/

	
	//����spawnPointλ��
	/*int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_curLogicForwardDir);
	FLogicVec2D spawnPointDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicRelativeSpawnPoint, FLogicVec2D(0, 0), yaw);
	FLogicVec2D logicPos2D(GetActorLocation().X, GetActorLocation().Y);
	m_logicSpawnPoint = logicPos2D + spawnPointDir;
	//DrawDebugPoint(GetWorld(), FVector(m_logicSpawnPoint.X, m_logicSpawnPoint.Y, m_defaultHeight), 20, FColor::Black, false, 0.1);
	//����λ��
	float expandDeltaX = m_curLogicVelocity.X * DeltaSeconds;
	float expandDeltaY = m_curLogicVelocity.Y * DeltaSeconds;
	if (m_characterType == 0 && m_pNormalLongTask)
	{
		FVector destinationOffset = m_pNormalLongTask->m_destination - GetActorLocation();
		destinationOffset.Z = 0;
		int32 destinationOffsetSquare = destinationOffset.sqr();
		if ((expandDeltaX*expandDeltaX + expandDeltaY * expandDeltaY) >= destinationOffsetSquare)
		{
			expandDeltaX = destinationOffset.X;
			expandDeltaY = destinationOffset.Y;
		}
	}*/

	
}

void AKing::InitialBaseEquipmentInfo()
{
	Super::InitialBaseEquipmentInfo();
}
/*

void AKing::CalPlayerCharacterVel_Int(bool canMove)
{
	if (m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch")
	{
		m_curLogicVelocity.X = 0;
		m_curLogicVelocity.Y = 0;
	}
	else
	{
		FLogicVec2D deltaVel = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(m_logicVelOperation, m_acc);
		FLogicVec2D nextLogicVel = m_curLogicVelocity + deltaVel;
		int32 scaleMaxSPD = m_MaxSPD * m_speedRatePercent / 100;
		if (UCollisionWarBpFunctionLibrary::GetLogicVecSize(nextLogicVel) >= scaleMaxSPD)
		{
			FLogicVec2D maxSPDVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(nextLogicVel, scaleMaxSPD);
			nextLogicVel = maxSPDVec;
		}
		m_curLogicVelocity = nextLogicVel;
	}
	/ *GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, "ID: " + FString::FromInt(m_entityID) + 
		" cur velX is: " + FString::FromInt(m_curLogicVelocity.X) +
		" cur velY is: " + FString::FromInt(m_curLogicVelocity.Y));* /
	m_pBaseAnimInstance->m_speed = UCollisionWarBpFunctionLibrary::GetLogicVecSize(m_curLogicVelocity);
	GetCharacterMovement()->Velocity = FVector(m_curLogicVelocity.X, m_curLogicVelocity.Y, 0);
}*/

void AKing::SetCollectActorDetectComponent(UShapeComponent* pComponent)
{
	m_pCollectPhysActorDetectComponent = pComponent;
}

void AKing::OnCollectActorDetectoBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (!OtherComp) return;
	if (!OtherComp->ComponentHasTag(FName(TEXT("BasePhysActor")))) return;
	ABasePhysActor* pPhysActor = Cast<ABasePhysActor>(otherActor);
	/*if (!pPhysActor || m_pCanCollectPhysActors.Contains(pPhysActor)) return;
	m_pCanCollectPhysActors.Add(pPhysActor);*/
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	pPhysActor->PopPhysActorWidget();
}

void AKing::OnCollectActorDetectoEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (!OtherComp) return;
	if (!OtherComp->ComponentHasTag(FName(TEXT("BasePhysActor")))) return;
	ABasePhysActor* pPhysActor = Cast<ABasePhysActor>(otherActor);
	/*if (!pPhysActor || !m_pCanCollectPhysActors.Contains(pPhysActor)) return;
	m_pCanCollectPhysActors.Remove(pPhysActor);*/
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	pPhysActor->HidePhysActorWidget();
}

void AKing::AddGeometrySkills()
{
	for (int32 i=0; i<m_geometrySkillClasses.Num(); i++)
	{
		UBaseSkill* pSkill = NewObject<UBaseSkill>(this, m_geometrySkillClasses[i]);
		pSkill->NotifyInitial();
		m_pGeometrySkills.Add(pSkill);
	}
}

void AKing::SetupItemComponentList(USkeletalMeshComponent* pBaseMesh,const TArray<FCharacterSKComponentInfo>& pSMComponents)
{
	if (!pBaseMesh) return;
	for (TMap<int32, USkeletalMeshComponent*>::TConstIterator iter = m_pItemComponentMap.CreateConstIterator(); iter; ++iter)
	{
		if (!m_itemComponentType.Contains(iter->Key)) continue;
		if (m_itemComponentType[iter->Key] == 0)
			iter->Value->SetMasterPoseComponent(pBaseMesh);
		else if (m_itemComponentType[iter->Key] == 1)
			iter->Value->AttachTo(pBaseMesh, FName(TEXT("NeckSocket")));
	}

	/*for (int32 i=0; i<pSMComponents.Num(); i++)
	{
		if (!pSMComponents[i].pComponent) continue;
		m_pItemComponents.Add(pSMComponents[i]);
		if (pSMComponents[i].componentType == 0)
			m_pItemComponents.Last().pComponent->SetMasterPoseComponent(pBaseMesh);
		else if (pSMComponents[i].componentType == 1)
			m_pItemComponents.Last().pComponent->AttachTo(pBaseMesh, FName(TEXT("NeckSocket")));
		m_pItemComponents.Last().pComponent->SetSkeletalMesh(NULL);
	}*/
}

void AKing::ImplementBlockSkill()
{
	//����������
	if (!m_pBlockSkillPS) return;
	FString socketString = "RootSocket";
	m_pBlockSkillPSComponent = UGameplayStatics::SpawnEmitterAttached(m_pBlockSkillPS, GetMesh(), FName(*socketString));
}

void AKing::ImplementDodgeSkill()
{
	//���ɷ���������
	if (!m_pDodgeSkill || !m_pCSAttachPS.particleSystem) return;
	TArray<ABasePhysGeo*> spawnGeos;
	int32 geoNb = 0;
	float yaw = GetActorRotation().Yaw;
	for (int32 i = 0; i < m_pDodgeSkill->m_geoClass.Num(); i++)
	{
		if (!m_pDodgeSkill->m_geoClass[i]) continue;
		TSubclassOf<class UObject> geoClass = m_pDodgeSkill->m_geoClass[i];
		for (int32 j = 0; j < m_pDodgeSkill->m_spawnGeoNb[i]; j++)
		{
			int32 relativeLauchAngle = m_pDodgeSkill->m_spreadAngle[geoNb];
			FVector spawnPtCharacterOffset = m_pSpawnPoint->GetComponentLocation() - GetActorLocation();
			FVector roateVector = spawnPtCharacterOffset.RotateAngleAxis(relativeLauchAngle, FVector::UpVector);
			FRotator launchRotator(0, yaw + relativeLauchAngle, 0);
			FVector launchLoc(GetActorLocation().X + roateVector.X, GetActorLocation().Y + roateVector.Y, m_defaultHeight);
			ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_pDodgeSkill->m_geoClass[i], launchLoc, launchRotator);
			for (int32 k = 0; k < spawnGeos.Num(); k++)
			{
				spawnGeos[k]->m_pRootGeos.Add(pGeo);
				pGeo->m_pRootGeos.Add(spawnGeos[k]);
			}
			m_pNewSpawnPhysGeos.Add(pGeo);
			if (m_pDodgeSkill->m_isHostSkill)
				m_pControlPhysGeos.Add(pGeo);
			geoNb += 1;
		}
	}
}

void AKing::DyeCSCharacter(ABaseCharacter* pCharacter)
{
	if (!pCharacter) return;
	m_pCSCharacter = pCharacter;
	m_pCSCharacter->NotifyCSDyeing();
}

void AKing::FadeCSCharacter()
{
	if (!m_pCSCharacter) return;
	m_pCSCharacter->NotifyCSFade();
}

void AKing::MessAllSkillCard()
{
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	AddSkill(pCWGI->m_curPlayerSPInfo.selectSkillInfo.chopSkillName, 0, true, 0);
	AddSkill(pCWGI->m_curPlayerSPInfo.selectSkillInfo.blockSkillName, -1, true, 1);
	AddSkill(pCWGI->m_curPlayerSPInfo.selectSkillInfo.dodgeSkillName, -1, true, 3);

	for (int32 i = 0; i < pCWGI->m_curPlayerSPInfo.selectSkillInfo.normalSkillNames.Num(); i++)
	{
		m_allAvailableSkills.Add(pCWGI->m_curPlayerSPInfo.selectSkillInfo.normalSkillNames[i]);
	}
	APlayerController * pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	for (int32 i = 0; i < pBattlePC->m_pBattleMenu->m_pSkillBattleCardList.Num(); i++)
	{
		if (m_allAvailableSkills.Num() > 0)
		{
			AddSkill(m_allAvailableSkills[0], i + 1, true, 2);

			for (int32 j = 0; j < pBattlePC->m_playerSkillInfos.Num(); j++)
			{
				if (pBattlePC->m_playerSkillInfos[j].skillName != m_allAvailableSkills[0]) continue;
				UMaterialInstanceDynamic* pMI = pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_pSkillImage->GetDynamicMaterial();
				pMI->SetTextureParameterValue(FName(TEXT("Back")), pBattlePC->m_playerSkillInfos[j].pTexture);
				pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_pCurTexture = pBattlePC->m_playerSkillInfos[j].pTexture;

				if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
					pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_pCardName->SetText(FText::FromString(pBattlePC->m_playerSkillInfos[j].chSkillName));
				else
					pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_pCardName->SetText(FText::FromString(pBattlePC->m_playerSkillInfos[j].skillName));
				pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_isShow = true;
				pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->m_cardName = pBattlePC->m_playerSkillInfos[j].skillName;

				pBattlePC->m_pBattleMenu->m_pSkillBattleCardList[i]->NotifySetUpdateTimer();

				break;
			}

			m_allAvailableSkills.RemoveAt(0);
		}
		else break;
	}
}

void AKing::UpdateAllSkills(float dT)
{
	//����ʱ����Ҫ�����Ƿ����ɼ����壬�Ƿ񶳽����Ƿ񶳽�ʹ��
	//����ǰִ�е�skill�Ƿ��Ѿ�����ǰҡ�׶Σ������ǰҡ�׶���ʼ���ɼ�����
	//�绹û�ȹ�ǰҡ�����ɼ���

	if (!m_pBaseEquipment) return;
	float increaseTick = dT * (float)m_speedRatePercent / 100.f;
	//int32 increaseTick = m_pRGM->m_increaseTickPerFrame * m_speedRatePercent / 100;
	if (m_implementSkillType == 0)
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (!m_pBaseEquipment->m_pSkills[i]) continue;
			//float CDPercent = 0.f;
			if (m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_TransientPunch")
			{
				//�����TransientPunch�ļ��ܣ�ֻ�е���ǰ��ʱ���ڵ��ڶ���ʱ�䣬���ܽ���
				if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += increaseTick;
					if (i > 0)
					{
						float CDPercent = m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount / m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime;
						pBattlePC->m_pBattleMenu->UpdateSkillCoolDownPercentage(i, CDPercent);
					}
					if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime)
					{
						m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
						m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;
						m_pBaseEquipment->m_pSkills[i]->m_hasSpawnGeo = false;
					}
				}
			}
		}
	}
}

/*
void AKing::UpdateCurSkillState(float dT)
{
	//������ܺ�Ϊ-1��˵����ɫ��ǰ��Ϊ����ʩ�ż��ܣ��˳�
	if (m_curSkillNb == -1 && m_implementSkillType == 0) return;
	//����ʩ�ŷּ����׶�
	//1.��ʱ�����ǰҡ����ʱ�䣬���ɼ�����
	//2.�缼��Ϊ�����ͼ��ܣ���ʱ����ڶ����������ʱ��˵�����ܽ�������curSkillNb��m_pBaseAnimInstance->m_motionStateString
	//3.�缼��Ϊ�����ͼ��ܣ���ʱ�����������ʱ��ʱ��˵�����ܽ�������curSkillNb��m_pBaseAnimInstance->m_motionStateString
	UCharacterEquipInfo* pEquipInfo = NULL;
	if (m_curEquipNb == -1) pEquipInfo = m_pBaseEquipment;
	else pEquipInfo = m_pEquipmentInfos[m_curEquipNb];

	bool isSpawnGeo = false;
	UBaseSkill* pSkill = NULL;
	if (m_implementSkillType == 0)
		pSkill = pEquipInfo->m_pSkills[m_curSkillNb];
	else if (m_implementSkillType == 1)
		pSkill = m_pBlockSkill;
	else if (m_implementSkillType == 3)
		pSkill = m_pAbsortSkill;
	else
		pSkill = m_pCounterStrikeSkill;
	if (!pSkill) return;
	int32 scalePreShakeLogicTick = pSkill->m_preShakeLogicTickTime / 100;

	if (!pSkill) return;
	/ *if (pSkill->m_skillMotionTypeString == "PMS_RepeatPunch" && pSkill->m_skillFrameCount >= scalePreShakeLogicTick)
	{
		//��ǰ���ܼ�ʱ����ǰҡʱ��ͬʱΪRepeatPunchʱ���ɿ�ʼ���ɼ�����
		int32 scaleRepeatSpawnInterval = m_speedRatePercent * pSkill->m_repeatSkillSpawnInterval / 100;
		int32 remainder = pSkill->m_skillFrameCount % scaleRepeatSpawnInterval;
		if (remainder == 0)
		{
			//˵����ǰ��ʱ��m_repeatSkillSpawnInterval������������ʱ�����ɼ�����
			m_pBaseAnimInstance->NotifyImplementSkill(pSkill->m_skillAnimName);
			isSpawnGeo = true;
		}
	}* /
	if (!pSkill->m_hasSpawnGeo &&
		(pSkill->m_skillMotionTypeString == "PMS_TransientPunch" || pSkill->m_skillMotionTypeString == "PMS_Block" || pSkill->m_skillMotionTypeString == "PMS_CanCounterStrike") &&
		pSkill->m_skillFrameCount >= scalePreShakeLogicTick)
	{
		isSpawnGeo = true;
		pSkill->m_hasSpawnGeo = true;
	}
	if (!isSpawnGeo) return;
	
	/ ** �������ɼ������ˣ�����Ҫ���������
		* һ����ͨ���ܣ����������������ɼ����弴��
		* �����ٻ����ܣ���ʱ���ɵ��ǽ�ɫ���Ǽ�����
		* /
	pSkill->m_campFlag = m_campFlag;

	bool hasSpawnEnhancePS = false;
	if (m_implementSkillType == 0)
	{
		//��Ϊ��ͨ���ܷ�������
		TArray<ABasePhysGeo*> spawnGeos;
		int32 geoNb = 0;
		float yaw = GetActorRotation().Yaw;
		for (int32 i = 0; i < pSkill->m_geoClass.Num(); i++)
		{
			if (!pSkill->m_geoClass[i]) continue;
			//int32 halfNb = (pSkill->m_spawnGeoNb[i] - pSkill->m_spawnGeoNb[i] % 2) / 2;
			TSubclassOf<class UObject> geoClass = pSkill->m_geoClass[i];
			//geoNb = 0;
			for (int32 j = 0; j < pSkill->m_spawnGeoNb[i]; j++)
			{
				//FVector hostDir = GetActorForwardVector();
				int32 relativeLauchAngle = pSkill->m_spreadAngle[geoNb];
				FVector spawnPtCharacterOffset = m_pSpawnPoint->GetComponentLocation() - GetActorLocation();
				FVector roateVector = spawnPtCharacterOffset.RotateAngleAxis(relativeLauchAngle, FVector::UpVector) * pSkill->m_spawnDistanceAmplifiedList[geoNb];
				//FLogicVec2D relativeLauchLoc = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicRelativeSpawnPoint, FLogicVec2D(0, 0), relativeLauchAngle + yaw)*pSkill->m_spawnDistanceAmplifiedList[geoNb];
				//FLogicVec2D launchLogicDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_curLogicForwardDir, FLogicVec2D(0, 0), relativeLauchAngle);
				FRotator launchRotator(0, yaw + relativeLauchAngle, 0);
				FVector launchLoc(GetActorLocation().X + roateVector.X, GetActorLocation().Y + roateVector.Y, m_defaultHeight);
				ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(pSkill->m_geoClass[i], launchLoc, launchRotator);
				if (pGeo->m_physGeoType == EPhysGeoType::PGT_Actor || pGeo->m_physGeoType == EPhysGeoType::PGT_DetonationActor)
				{
					m_pRGM->m_pPhysCalculator->AddPhysGeo(pGeo, this, m_campFlag);
					/ *ABasePhysActor* pPhysActor = Cast<ABasePhysActor>(pGeo);
					pPhysActor->InitialPhysActor(m_campFlag, this, m_pRGM->m_pPhysCalculator->m_defaultSpawnHeight);* /
					/ *UCapsuleComponent* pCapsuleComponent = Cast<UCapsuleComponent>(pGeo->m_pBasicComponent);
					m_pRGM->m_pRecastDetourObject->HandleAddTempObstacle(launchLoc, pCapsuleComponent->GetScaledCapsuleRadius() / 100.f,
						pCapsuleComponent->GetUnscaledCapsuleHalfHeight() * 2.f / 100.f);* /
				}
				for (int32 k = 0; k < spawnGeos.Num(); k++)
				{
					spawnGeos[k]->m_pRootGeos.Add(pGeo);
					pGeo->m_pRootGeos.Add(spawnGeos[k]);
				}
				pGeo->SetAttachEquipment(pEquipInfo);
				//pGeo->m_logicForwardDir = launchLogicDir;
				/ *UParticleSystem* pSuperposePS = SuperposeEnergyBallList(pGeo);
				if (pSuperposePS)
				{
					if (pGeo->m_physGeoType == EPhysGeoType::PGT_Point) UGameplayStatics::SpawnEmitterAttached(pSuperposePS, pGeo->m_pBasicComponent);
					else UGameplayStatics::SpawnEmitterAtLocation(pGeo, pSuperposePS, pGeo->GetActorLocation(), pGeo->GetActorRotation());
				}* /
				m_pNewSpawnPhysGeos.Add(pGeo);
				if (pSkill->m_isHostSkill)
					m_pControlPhysGeos.Add(pGeo);
				geoNb += 1;
			}
		}
		for (int32 i = 0; i < pSkill->m_appendHostEffectParams.Num(); i++)
		{
			if (spawnGeos.Num() > 0)
				ImplementSkillAttachEffect(pSkill->m_appendHostEffectParams[i], spawnGeos.Last());
			else
				ImplementSkillAttachEffect(pSkill->m_appendHostEffectParams[i], NULL);
		}
	}
	else if (m_implementSkillType == 1)
		ImplementBlockSkill();
	else if (m_implementSkillType == 3)
		ImplementAbsortSkill();
	else
		ImplementCounterStrikeSkill();
	//�˴����ŷ�������ʱ�̵���Ч
	SetSkillIndependentFXTemplate(pSkill->m_skillName);
	
}*/

void AKing::NotifyLaunchSkill()
{
	//������ܺ�Ϊ-1��˵����ɫ��ǰ��Ϊ����ʩ�ż��ܣ��˳�
	if (m_curSkillNb == -1 && m_implementSkillType == 0) return;
	//����ʩ�ŷּ����׶�
	//1.��ʱ�����ǰҡ����ʱ�䣬���ɼ�����
	//2.�缼��Ϊ�����ͼ��ܣ���ʱ����ڶ����������ʱ��˵�����ܽ�������curSkillNb��m_pBaseAnimInstance->m_motionStateString
	//3.�缼��Ϊ�����ͼ��ܣ���ʱ�����������ʱ��ʱ��˵�����ܽ�������curSkillNb��m_pBaseAnimInstance->m_motionStateString
	UCharacterEquipInfo* pEquipInfo = NULL;
	if (m_curEquipNb == -1) pEquipInfo = m_pBaseEquipment;
	else pEquipInfo = m_pEquipmentInfos[m_curEquipNb];

	bool isSpawnGeo = false;
	UBaseSkill* pSkill = NULL;
	if (m_implementSkillType == 0)
		pSkill = pEquipInfo->m_pSkills[m_curSkillNb];
	else if (m_implementSkillType == 1)
		pSkill = m_pBlockSkill;
	else if (m_implementSkillType == 3)
		pSkill = m_pDodgeSkill;

	if (!pSkill) return;

	if (!pSkill->m_hasSpawnGeo &&
		(pSkill->m_skillMotionTypeString == "PMS_TransientPunch" || pSkill->m_skillMotionTypeString == "PMS_Block"))
	{
		isSpawnGeo = true;
		pSkill->m_hasSpawnGeo = true;
	}
	if (!isSpawnGeo) return;

	/** �������ɼ������ˣ�����Ҫ���������
		* һ����ͨ���ܣ����������������ɼ����弴��
		* �����ٻ����ܣ���ʱ���ɵ��ǽ�ɫ���Ǽ�����
		*/
	pSkill->m_campFlag = m_campFlag;

	bool hasSpawnEnhancePS = false;
	if (m_implementSkillType == 0 || m_implementSkillType == 1)
	{
		//��Ϊ��ͨ���ܷ�������
		TArray<ABasePhysGeo*> spawnGeos;
		int32 geoNb = 0;
		float yaw = GetActorRotation().Yaw;
		TArray<TSubclassOf<class ABasePhysGeo> > geoClasses;
		if (pSkill->m_mutationGeoClass.Contains(pSkill->m_mutationType)) geoClasses = pSkill->m_mutationGeoClass[pSkill->m_mutationType].geoClasses;
		for (int32 i = 0; i < geoClasses.Num(); i++)
		{
			if (!geoClasses[i]) continue;
			for (int32 j = 0; j < pSkill->m_spawnGeoNb[i]; j++)
			{
				int32 relativeLauchAngle = pSkill->m_spreadAngle[geoNb];
				FVector spawnPtCharacterOffset = m_pSpawnPoint->GetComponentLocation() - GetActorLocation();
				FVector roateVector = spawnPtCharacterOffset.RotateAngleAxis(relativeLauchAngle, FVector::UpVector) * pSkill->m_spawnDistanceAmplifiedList[geoNb];
				FRotator launchRotator(0, yaw + relativeLauchAngle, 0);
				FVector launchLoc;
				//����Ҫ���ݼ���������ȷ�����ɵ�λ��
				if (pSkill->m_skillType == 1)
				{
					//��λ�ͼ���
					launchLoc.X = m_targetLoc.X + roateVector.X;
					launchLoc.Y = m_targetLoc.Y + roateVector.Y;
					launchLoc.Z = m_defaultHeight;
				}
				else
				{
					launchLoc.X = GetActorLocation().X + roateVector.X;
					launchLoc.Y = GetActorLocation().Y + roateVector.Y;
					launchLoc.Z = m_defaultHeight;
				}
				//����Ҫ���ݼ���������ȷ�����ɵ�λ��
				ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(geoClasses[i], launchLoc, launchRotator);
				if (pSkill->m_skillType == 2)
				{
					AProjectilePoint* pProjectilePoint = Cast<AProjectilePoint>(pGeo);
					pProjectilePoint->InitialProjectilePoint(m_targetLoc);
				}
				for (int32 k = 0; k < spawnGeos.Num(); k++)
				{
					spawnGeos[k]->m_pRootGeos.Add(pGeo);
					pGeo->m_pRootGeos.Add(spawnGeos[k]);
				}
				pGeo->SetAttachEquipment(pEquipInfo);
				m_pNewSpawnPhysGeos.Add(pGeo);
				if (pSkill->m_isHostSkill)
					m_pControlPhysGeos.Add(pGeo);
				geoNb += 1;
			}
		}
		for (int32 i = 0; i < pSkill->m_appendHostEffectParams.Num(); i++)
		{
			if (spawnGeos.Num() > 0)
				ImplementSkillAttachEffect(pSkill->m_appendHostEffectParams[i], spawnGeos.Last());
			else
				ImplementSkillAttachEffect(pSkill->m_appendHostEffectParams[i], NULL);
		}
	}

	//�˴����ŷ�������ʱ�̵���Ч
	SetSkillIndependentFXTemplate(pSkill->m_skillName);

}

void AKing::NotifyEndSkill()
{
	//����ʱ����Ҫ�����Ƿ����ɼ����壬�Ƿ񶳽����Ƿ񶳽�ʹ��
	//����ǰִ�е�skill�Ƿ��Ѿ�����ǰҡ�׶Σ������ǰҡ�׶���ʼ���ɼ�����
	//�绹û�ȹ�ǰҡ�����ɼ���

	if (!m_pBaseEquipment) return;
	if (m_implementSkillType == 0)
	{
		UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[m_curSkillNb];
		int32 deleteSkillNb = m_curSkillNb;
		StopContinuousTask();
		pSkill->m_skillFrameCount = 0;
		pSkill->m_hasSpawnGeo = false;

		if (m_curEquipNb == -1) return;
		//bool isCurEquipDelete = false;
		if (m_curEquipNb >= m_pEquipmentInfos.Num() || !m_pEquipmentInfos[m_curEquipNb] || !m_pEquipmentInfos[m_curEquipNb]->m_pSkills[m_curSkillNb])
			return;
		m_pEquipmentInfos[m_curEquipNb]->m_pSkills[m_curSkillNb]->m_skillFrameCount = 0;
		m_pEquipmentInfos[m_curEquipNb]->m_pSkills[m_curSkillNb]->m_canImplementFlag = true;
		m_pEquipmentInfos[m_curEquipNb]->m_pSkills[m_curSkillNb]->m_hasSpawnGeo = false;
		StopContinuousTask();
	}
	else if (m_implementSkillType == 1)
	{
		StopContinuousTask();
		m_pBlockSkill->m_skillFrameCount = 0;
		m_pBlockSkill->m_hasSpawnGeo = false;
	}
	else if (m_implementSkillType == 3)
	{
		StopContinuousTask();
		m_pDodgeSkill->m_skillFrameCount = 0;
		m_pDodgeSkill->m_hasSpawnGeo = false;
	}
}

void AKing::ImplementSkill_Int(int32 campFlag)
{
	if (m_energyBallList <= 0) return;
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	//����װ����curEquipNb
	if (m_equipOperationNb != -1) m_curEquipNb = m_equipOperationNb;
	//���¼��ܺ�curSkillNb
	m_curSkillNb = m_skillOperationNb;
	UBaseSkill* pSkill = NULL;
	if (m_implementSkillType == 0)
	{
		UCharacterEquipInfo* pEquipInfo = NULL;
		if (m_curEquipNb == -1)
		{
			pEquipInfo = m_pBaseEquipment;
		}
		else
		{
			UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
			UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
			pEquipInfo = m_pEquipmentInfos[m_curEquipNb];
			if (pCWGI->m_curPlayerSPInfo.availableEquipList.Contains(pEquipInfo->m_equipmentName))
				pCWGI->m_curPlayerSPInfo.availableEquipList.Remove(pEquipInfo->m_equipmentName);
		}
		//���¶���ָ����ڶ���
		pSkill = pEquipInfo->m_pSkills[m_curSkillNb];
		if (!pSkill) return;
		pSkill->m_campFlag = campFlag;
		ConsumeEnergyBall();
	}
	else if (m_implementSkillType == 1)
	{
		pSkill = m_pBlockSkill;
		ConsumeEnergyBall();
	}
	else if (m_implementSkillType == 3)
	{
		pSkill = m_pDodgeSkill;
		ConsumeEnergyBall();
	}
	m_pBaseAnimInstance->m_motionStateString = pSkill->m_skillMotionTypeString;
	m_pBaseAnimInstance->NotifyImplementSkill(pSkill->m_skillAnimName);
	//���¼�����Ϣ
	pSkill->m_canImplementFlag = false;

	//ʵʩ������Ϣ�󣬻ָ��ӿ�
	m_actionName = "NULL";


}

void AKing::AddSkill(FString skillName, int32 insertLoc, bool isFirstAdd, uint8 skillType)
{
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	if (!m_pBaseEquipment->m_skillClassMap.Contains(skillName) || !m_pBaseEquipment->m_skillClassMap[skillName]) return;

	/*if (insertLoc < m_pBaseEquipment->m_pSkills.Num() && m_pBaseEquipment->m_pSkills[insertLoc] && insertLoc != -1)
		DeleteSkill(insertLoc);*/
	UBaseSkill* pSkill = NewObject<UBaseSkill>(this, m_pBaseEquipment->m_skillClassMap[skillName]);
	UGameInstance* pGI = UGameplayStatics::GetGameInstance(this);
	UCollisionWarGameInstance* pCWGI = Cast<UCollisionWarGameInstance>(pGI);
	if (pCWGI->m_curPlayerSPInfo.skillAttributeAssignment.Contains(skillName))
	{
		pSkill->m_mutationType = pCWGI->m_curPlayerSPInfo.skillAttributeAssignment[skillName];
	}
	pSkill->NotifyInitial();
	if (skillType == 1)
		m_pBlockSkill = pSkill;
	else if (skillType == 3)
		m_pDodgeSkill = pSkill;
	else
		m_pBaseEquipment->m_pSkills[insertLoc] = pSkill;
}

void AKing::DeleteSkill(int32 deleteSkillNb)
{
	/** ɾ������Ҫע�����¼�������
	* ɾ��ǰҪ�жϽ�ɫ״̬�����ɫ״̬ΪTransientPunch��˵����ɫ���ڷ������ܣ���ʱӦ�������²���
	* 1. ִ��StopTask������ɫ����״̬������ǰ���ܺŸ�Ϊ-1
	* 2. ��UpdateCurSkillStateʱ���ڵ�ǰ����Ϊ-1����ֱ���Ƴ����ᱨ��
	* 3. ��ִ��UpdateAllSkillStateʱ
	*/
	if (m_curEquipNb == -1 && m_curSkillNb == deleteSkillNb && m_implementSkillType == 0)
		StopContinuousTask();
	
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	if (m_pBaseEquipment->m_pSkills[deleteSkillNb] && m_pBaseEquipment->m_pSkills[deleteSkillNb]->IsValidLowLevel())
	{
		m_pBaseEquipment->m_pSkills[deleteSkillNb]->ConditionalBeginDestroy();
		m_pBaseEquipment->m_pSkills[deleteSkillNb] = NULL;
	}
	pBattlePC->m_pBattleMenu->DeleteSkillFromMenu(deleteSkillNb - 1);
}

void AKing::UpdateFastEquip(FString itemName, int32 slotNb, bool addOrSub)
{
	if (!addOrSub)
	{
		//˵����װ���ӿ����������
		if (!m_fastEquipInfoMap.Contains(slotNb)) return;
		m_fastEquipInfoMap.Remove(slotNb);
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		if (pBattlePC->m_pBattleMenu)
			pBattlePC->m_pBattleMenu->DeleteEquipFromMenu(slotNb);
	}
	else
	{
		//һ���Ѿ���һ����ݼ�ָ�����װ�������ǻ�û�п�ݼ�ָ�����װ�������������ݼ��Ѿ���ռ��Ҫ��ɾ���
		UCharacterEquipInfo* pEquipInfo = NULL;
		for (int32 i = 0; i < m_pEquipmentInfos.Num(); i++)
		{
			if (!m_pEquipmentInfos[i] || m_pEquipmentInfos[i]->m_equipmentName != itemName) continue;
			pEquipInfo = m_pEquipmentInfos[i];
			break;
		}
		if (!pEquipInfo) return;
		if (m_fastEquipInfoMap.Contains(slotNb))
		{
			//�ȼ���Ƿ�ͬ����slot����ͬ����װ��������ֱ���˳�
			if (m_fastEquipInfoMap[slotNb]->m_equipmentName == itemName) return;
			//�������slot�Ƿ���ͬ����װ����������ɾ����Ȼ�������µ�slot���
			TArray<int32> repeatEquipNbList;
			for (TMap<int32, UCharacterEquipInfo*>::TConstIterator iter = m_fastEquipInfoMap.CreateConstIterator(); iter; ++iter)
			{
				if (!iter->Value || !iter->Value->m_equipmentName.Contains(itemName)) continue;
				repeatEquipNbList.Add(iter->Key);
			}
			for (int32 i = 0; i < repeatEquipNbList.Num(); i++)
			{
				m_fastEquipInfoMap.Remove(repeatEquipNbList[i]);
			}
			m_fastEquipInfoMap[slotNb] = pEquipInfo;
		}
		else
		{
			//�������slot�Ƿ���ͬ����װ����������ɾ����Ȼ�������µ�slot���
			TArray<int32> repeatEquipNbList;
			for (TMap<int32, UCharacterEquipInfo*>::TConstIterator iter = m_fastEquipInfoMap.CreateConstIterator(); iter; ++iter)
			{
				if (!iter->Value || iter->Value->m_equipmentName != itemName) continue;
				repeatEquipNbList.Add(iter->Key);
			}
			for (int32 i = 0; i < repeatEquipNbList.Num(); i++)
			{
				m_fastEquipInfoMap.Remove(repeatEquipNbList[i]);
			}
			m_fastEquipInfoMap.Add(slotNb, pEquipInfo);
		}
	}
}

void AKing::StopContinuousTask()
{
	/**��Ҫ��������һ����������ǵ����ʹ�����������л�������װ����Ȼ������������ʱ������ʱ��Ϻ�ᴥ��StopContinuousTask
	* �����ڴ�ʱ�ֳ���Ʒ����ɼ�ʱ�����壬�Ӷ���ͣ����װ��
	* ����������������ڣ���Ϊ�粻�����ٻ����ܣ����ֳ�����װ�����ɷ���������ô�ڼ�ʱ����FreezeMotionTimeʱ�ǲ������κ�
	* �����ģ������ǲ��������ʹ���������������л�������װ�������
	* ��ʹ���ֳ���������װ���������ٻ����ܵ������ͬ����Ҫ���²���
	*/
	m_curSkillNb = -1;
	m_pBaseAnimInstance->m_motionStateString = "PMS_NULL";
	m_curHurtImmuneTimeCount = 0.f;
	int32 i = 0;
	while (i < m_pControlPhysGeos.Num())
	{
		if (!m_pControlPhysGeos[i]) m_pControlPhysGeos.RemoveAt(i);
		else
		{
			if (!m_pControlPhysGeos[i]->m_attributeTags.Contains("PersistGeo"))
				m_pControlPhysGeos[i]->m_isGeoValid = false;
			i++;
		}
	}
	m_pBaseAnimInstance->NotifyStopAnim();
	m_actionName = "NULL";
	//�統ǰ���е��߲���Ĭ��������Ҫ�Գ��е��ߵ����������жϣ�������С�ڵ���0���Զ��л���Ĭ��������Ȼ��ɾ�����õ���
	/**��Ҫ��������һ����������ǵ����ʹ�����������л�������װ����Ȼ������������ʱ������ʱ��Ϻ�ᴥ��StopContinuousTask
	* �����ڴ�ʱ�ֳ���Ʒ����ɼ�ʱ�����壬�Ӷ�ɾ������װ��
	* ����������������ڣ���Ϊ�粻�����ٻ����ܣ����ֳ�����װ�����ɷ���������ô�ڼ�ʱ����FreezeMotionTimeʱ�ǲ������κ�
	* �����ģ������ǲ��������ʹ���������������л�������װ�������
	* ������ֳ�����װ���������ٻ����ܵ������ֱ�������������
	*/
	if (m_implementSkillType != 0)
	{
		m_implementSkillType = 0;
		return;
	}
	if (m_curEquipNb == -1 || !m_pEquipmentInfos[m_curEquipNb]) return;
	m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb -= 1;
	UpdateItemMap(m_pEquipmentInfos[m_curEquipNb]->m_equipmentName, m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb);
	APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
	ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
	
	if (m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb <= 0)
	{
		int32 equipNb = m_curEquipNb;
		int32 slotNb = -1;
		for (TMap<int32, UCharacterEquipInfo*>::TConstIterator iter = m_fastEquipInfoMap.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Value->m_equipmentName != m_pEquipmentInfos[m_curEquipNb]->m_equipmentName) continue;
			slotNb = iter->Key;
			break;
		}
		if (slotNb != -1)
			UpdateFastEquip(m_pEquipmentInfos[m_curEquipNb]->m_equipmentName, slotNb, false);
		ChangeEquipment(-1);
		DeleteEquipment(equipNb);
		
	}
	m_curEquipNb = -1;
}

void AKing::DeleteEquipment(int32 equipNb)
{
	if (equipNb < 0 || equipNb >= m_pEquipmentInfos.Num()) return;
	if (!m_pEquipmentInfos[equipNb])
	{
		m_pEquipmentInfos.RemoveAt(equipNb);
	}
	else
	{
		UCharacterEquipInfo* pEquip = m_pEquipmentInfos[equipNb];
		/*APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		pBattlePC->m_pItemMenu->UpdateItemList(pEquip->m_equipmentName, 0);*/
		if (pEquip->IsValidLowLevel())
		{
			pEquip->ConditionalBeginDestroy();
		}
		m_pEquipmentInfos.RemoveAt(equipNb);
	}
}

void AKing::ConsumeEnergyBall()
{
	if (m_energyBallList <= 0)
	{
		return;
	}
	m_energyBallList -= 1;
	if (m_pCharacterInfoWidget)
	{
		m_pCharacterInfoWidget->UpdateEnergyBall(false, 0);
	}
}

void AKing::RecoverEnergyBall(float dT)
{
	if (m_energyBallList >= m_maxEnergyBallNb)
	{
		return;
	}
	if (m_curEnergyBallRecoverTime >= m_energyBallRecoverInterval)
	{
		m_energyBallList += 1;
		m_curEnergyBallRecoverTime = 0.f;
		if (m_pCharacterInfoWidget)
		{
			m_pCharacterInfoWidget->UpdateEnergyBall(true, 0);
		}
	}
	else
	{
		m_curEnergyBallRecoverTime += dT;
	}
}

int32 AKing::GenCardID()
{
	int32 i = 0;
	bool isExist = true;

	while (isExist)
	{
		isExist = false;
		for (TMap<int32, FItemCardCondition>::TConstIterator iter = m_allNumericCardMap.CreateConstIterator(); iter; ++iter)
		{
			if (iter->Key == i)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist) break;
		i += 1;
	}
	return i;
}

bool AKing::AddNewItem(FString itemName)
{
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	FItemCardCondition cardCondition;
	cardCondition.cardName = itemName;
	//cardCondition.cardType = pBLPC->m_itemCardInfoMap[itemName].cardType;
	if (itemName.Contains("Numeric_"))
	{
		if (m_allNumericCardMap.Num() >= m_pRGM->m_maxNumericCardNb) return false;
		int32 id = GenCardID();
		m_allNumericCardMap.Add(id, cardCondition);
		if (pBLPC->m_pBattleMenu)
		{
			pBLPC->m_pBattleMenu->AddNNumericCardToPanel(itemName, id);
		}
	}
	else
	{
		if (m_allItemCardMap.Num() >= m_pRGM->m_maxInventoryNb) return false;
		if (m_allItemCardMap.Contains(itemName)) m_allItemCardMap[itemName] += 1;
		else m_allItemCardMap.Add(itemName, 1);
	}

	
	//��ʤ�����������жϣ���ս���������ռ�ʤ���ͣ���ʱҪ�ж��Ƿ����ռ���ϳɳ��涨����Ʒ�����ǽ��������Ʒ�����Ƴ�����UpdateVictory���ٽ���ʤ���ж�
	
	if (m_pRGM->m_pAIManager->m_battleInfo.targetCollectNameList.Contains(itemName))
	{
		m_pRGM->m_pAIManager->m_battleInfo.targetCollectNameList.Remove(itemName);
	}

	//����ǿ���װ����Ʒ������Ҫ���װ��
	if (itemName.Contains("Numeric") || pBLPC->m_itemCardInfoMap[itemName].cardType != 2) return true;
	FString equipName = itemName;
	bool equipExist = false;
	for (int32 i = 0; i < m_pEquipmentInfos.Num(); i++)
	{
		if (m_pEquipmentInfos[i]->m_equipmentName == equipName)
		{
			m_pEquipmentInfos[i]->m_equipmentNb += 1;
			equipExist = true;
			break;
		}
	}
	
	if (equipExist || !m_pRGM->m_characterEquipInfoClassMap.Contains(equipName)) return true;
	TSubclassOf<class UObject> equipmentInfoClass = m_pRGM->m_characterEquipInfoClassMap[equipName];
	UCharacterEquipInfo* pEquipInfo = NewObject<UCharacterEquipInfo>(this, equipmentInfoClass);
	pEquipInfo->m_equipmentNb = 1;
	pEquipInfo->InitialEquipInfo();
	m_pEquipmentInfos.Add(pEquipInfo);
	return true;
}

/*
void AKing::RemoveItem(int32 itemID)
{
	ABattleLevelPlayerController* pBLPC = Cast<ABattleLevelPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!m_allNumericCardMap.Contains(itemID)) return;
	FString itemName = m_allNumericCardMap[itemID].cardName;
	//����װ���˵�
	if (pBLPC->m_pInventoryMenu && pBLPC->m_pInventoryMenu->m_itemMap.Contains(itemName))
	{
		pBLPC->m_pInventoryMenu->m_itemMap[itemName]->m_itemNum -= 1;
		pBLPC->m_pInventoryMenu->UpdateItemList(itemName, pBLPC->m_pInventoryMenu->m_itemMap[itemName]->m_itemNum);
	}
	//���ºϳɲ˵�
	if (pBLPC->m_pTradeMenu)
	{
		pBLPC->m_pTradeMenu->RemoveItemFromList(itemID);
	}
	m_allNumericCardMap.Remove(itemID);
}*/

void AKing::UpdateItemMap(FString itemName, int32 nb)
{
	if (!m_allItemCardMap.Contains(itemName)) return;
	if (nb <= 0) m_allItemCardMap.Remove(itemName);
	else m_allItemCardMap[itemName] = nb;
}
