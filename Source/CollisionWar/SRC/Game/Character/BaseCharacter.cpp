// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "BaseCharacter.h"
//#include <SkUEProjectGeneratedBindings.generated.hpp>
#include "../Battle/Physics/PhysPolySonClass/PhysPolygon.h"
#include "../Battle/Physics/PhysActorSonClass/BasePhysActor.h"
#include "../Battle/Physics/DumpPhysActor.h"
#include "../Battle/Physics/PhysPointSonClass/ProjectilePoint.h"
//#include "../Lua/LuaActor.h"
#include "../../Common/WidgetBlueprintFunctionLibrary.h"
#include "../../Base/Battle/BattleLevelPlayerController.h"
#include "../Battle/RoguelikeBattleGameMode.h"
#include "../Battle/Physics/PhysLineSonClass/PhysLine.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_campFlag = 0;
	m_isInitialDoneFlag = false;
	m_pBaseAnimInstance = NULL;
	m_curSkillNb = -1;
	m_curEquipNb = -1;

	m_pHandAttachment = NULL;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	USceneComponent* pRootComponent = GetRootComponent();
	FName tag(TEXT("BaseCharacter"));
	pRootComponent->ComponentTags.Add(tag);
	FName meshTag(TEXT("BaseCharacterMesh"));
	if (GetMesh()->ComponentHasTag(meshTag)) return;
	GetMesh()->ComponentTags.Add(meshTag);
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	if (!m_isInitialDoneFlag) return;
	//DrawDebugString(GetWorld(), GetActorLocation(), FString::FromInt(m_entityID), 0, FColor::White, 0.1);
	if (m_Hp <= 0)
	{
		m_curLogicVelocity.X = 0;
		m_curLogicVelocity.Y = 0;
		m_pBaseAnimInstance->m_speed = 0;
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		return;
	}
	UpdateAllSkills(DeltaSeconds);
	UpdateAllTimeDilationEffects(DeltaSeconds);
	UpdateAllAttributes(DeltaSeconds);

	if (m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch")
	{
		m_curLogicVelocity.X = 0;
		m_curLogicVelocity.Y = 0;
		m_pBaseAnimInstance->m_speed = 0;
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		//GEngine->AddOnScreenDebugMessage(-1,0.2,FColor::Red,"sdf");
	}
	else
	{
		//如非玩家角色才需要执行
		FVector2D scaleLogicVel(0, 0);
		if (m_speedRatePercent != 0) scaleLogicVel = m_logicVelOperation * m_speedRatePercent / 100;
		m_curLogicVelocity = scaleLogicVel;
		m_pBaseAnimInstance->m_speed = m_logicVelOperation.Size();
		GetCharacterMovement()->Velocity = FVector(m_curLogicVelocity.X, m_curLogicVelocity.Y, 0);
		//调整朝向
		//m_curLogicForwardDir = m_logicForwardOperation;
		FVector modifyDirVector(m_logicForwardOperation.X, m_logicForwardOperation.Y, 0);
		FRotator modifyRotator = modifyDirVector.ToOrientationRotator();
		SetActorRotation(modifyRotator);
		
		//DrawDebugPoint(GetWorld(), FVector(m_logicSpawnPoint.X, m_logicSpawnPoint.Y, m_defaultHeight), 20, FColor::Black, false, 0.1);
		//调整位置
		float expandDeltaX = m_curLogicVelocity.X * DeltaSeconds;
		float expandDeltaY = m_curLogicVelocity.Y * DeltaSeconds;
		FVector expandVector(expandDeltaX, expandDeltaY, 0);
		if (m_characterType == 0 && m_pNormalLongTask)
		{
			if (m_thinkMode == ECharacterThinkMode::CTM_Patrol && m_pNormalLongTask->m_taskType == ETaskType::TT_NULL)
			{
				return;
			}
			else
			{
				FVector destinationOffset = m_pNormalLongTask->m_destination - GetActorLocation();
				float destinationOffsetSquare = destinationOffset.Size();
				float expandSize = expandVector.Size();
				if (expandSize >= destinationOffsetSquare)
				{
					FVector desLoc(m_pNormalLongTask->m_destination.X, m_pNormalLongTask->m_destination.Y, GetActorLocation().Z);
					SetActorLocation(desLoc);
					m_pNormalLongTask->m_taskType = ETaskType::TT_NULL;
					return;
				}
			}
		}

		FVector nextLoc = GetActorLocation() + FVector(expandDeltaX, expandDeltaY, 0);
		SetActorLocation(nextLoc);
		//GEngine->AddOnScreenDebugMessage(-1, 0.2, FColor::Red, "sdfsssssssssss");
	}
	
}

void ABaseCharacter::SetTorsoMeshComponent(USkeletalMeshComponent* pBaseMesh, USkeletalMeshComponent* pHeadMesh, USkeletalMeshComponent* pHeadMesh1, USkeletalMeshComponent* pHeadMesh2,
	USkeletalMeshComponent* pHandMesh, USkeletalMeshComponent* pHandMesh2, USkeletalMeshComponent* pHandMesh3, USkeletalMeshComponent* pHandMesh4,
	USkeletalMeshComponent* pHandMesh5, USkeletalMeshComponent* pHandMesh6, USkeletalMeshComponent* pHandMesh7, USkeletalMeshComponent* pHandMesh8,
	USkeletalMeshComponent* pTorsoMesh, USkeletalMeshComponent* pBackMesh, USkeletalMeshComponent* pHipMesh, USkeletalMeshComponent* pLegMesh,
	USkeletalMeshComponent* pLegMesh2, USkeletalMeshComponent* pLegMesh3, USkeletalMeshComponent* pLegMesh4, USkeletalMeshComponent* pAttachMesh)
{
	if (!pBaseMesh) return;
	if (pHeadMesh) pHeadMesh->SetMasterPoseComponent(pBaseMesh);
	if (pHeadMesh1) pHeadMesh1->SetMasterPoseComponent(pBaseMesh);
	if (pHeadMesh2) pHeadMesh2->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh) pHandMesh->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh2) pHandMesh2->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh3) pHandMesh3->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh4) pHandMesh4->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh5) pHandMesh5->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh6) pHandMesh6->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh7) pHandMesh7->SetMasterPoseComponent(pBaseMesh);
	if (pHandMesh8) pHandMesh8->SetMasterPoseComponent(pBaseMesh);
	if (pTorsoMesh) pTorsoMesh->SetMasterPoseComponent(pBaseMesh);
	if (pBackMesh) pBackMesh->SetMasterPoseComponent(pBaseMesh);
	if (pHipMesh) pHipMesh->SetMasterPoseComponent(pBaseMesh);
	if (pLegMesh) pLegMesh->SetMasterPoseComponent(pBaseMesh);
	if (pLegMesh2) pLegMesh2->SetMasterPoseComponent(pBaseMesh);
	if (pLegMesh3) pLegMesh3->SetMasterPoseComponent(pBaseMesh);
	if (pLegMesh4) pLegMesh4->SetMasterPoseComponent(pBaseMesh);
	if (pAttachMesh) pAttachMesh->SetMasterPoseComponent(pBaseMesh);
}

void ABaseCharacter::SetSpawnPointComponent(USphereComponent* pComponent)
{
	if (!pComponent) return;
	m_pSpawnPoint = pComponent;
}

void ABaseCharacter::OnCapsuleComponentOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (pGeo->m_pHost == this) return;
		if (pGeo->m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))) || pGeo->m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilationOnlyCharacter"))))
		{
			if (!m_timeDilationParams.Contains(pGeo->GetName()))
			{
				for (int32 i = 0; i < pGeo->m_effectParamList.Num(); i++)
				{
					if (pGeo->m_effectParamList[i].effectName != "TimeDilation") continue;
					if ((pGeo->m_effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == m_campFlag)) continue;
					FTimeDilationInfo timeDilationInfo(0.f, pGeo->m_effectParamList[i].effectValues[0], 0);
					m_timeDilationParams.Add(pGeo->GetName(), timeDilationInfo);
					if (CustomTimeDilation >= ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f)
					{
						CustomTimeDilation = ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f;
						m_speedRatePercent = pGeo->m_effectParamList[i].effectValues[0];
						//m_curTimeDilationKey = pGeo->GetName();
					}
					break;
				}
			}
		}
	}
}

void ABaseCharacter::OnCapsuleComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo) return;
		if (m_timeDilationParams.Contains(pGeo->GetName()))
		{
			//这里要将时间膨胀的顺序理清
			//FString curTimeDilationKey = "";
			int32 minTimeDilation = 100;
			for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
			{
				if (pGeo->GetName() == iter->Key) continue;
				if (iter->Value.timeDilationPercent <= minTimeDilation)
				{
					minTimeDilation = iter->Value.timeDilationPercent;
					//curTimeDilationKey = iter->Key;
				}
			}

			//m_curTimeDilationKey = curTimeDilationKey;
			CustomTimeDilation = (float)minTimeDilation / 100.f;
			m_speedRatePercent = minTimeDilation;
			m_timeDilationParams.Remove(pGeo->GetName());
		}
	}
}

void ABaseCharacter::AddOrRemoveAttachPS(uint8 attribute, bool addOrSub)
{
	if (addOrSub)
	{
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		if (!pSingleton->m_attachPSMap.Contains(attribute)) return;
		UParticleSystemComponent* pPSComponent = UGameplayStatics::SpawnEmitterAttached(pSingleton->m_attachPSMap[attribute], GetRootComponent(), FName("NULL"),
			FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
		FParticleSysParam psParam;
		psParam.Name = "VertSurfaceActor";
		psParam.ParamType = EParticleSysParamType::PSPT_Actor;
		psParam.Actor = this;
		pPSComponent->InstanceParameters.Add(psParam);
		m_attachAttributePS.Add(attribute, pPSComponent);
	}
	else
	{
		if (!m_attachAttributePS.Contains(attribute)) return;
		m_attachAttributePS[attribute]->Deactivate();
		m_attachAttributePS.Remove(attribute);
	}
}

// Called to bind functionality to input
/*
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}*/

void ABaseCharacter::UpdateAllSkills(float dT)
{
	//技能时钟主要包括是否生成几何体，是否冻结活动，是否冻结使用
	//看当前执行的skill是否已经过了前摇阶段，如过了前摇阶段则开始生成几何体
	//如还没度过前摇则不生成技能
	
	if (!m_pBaseEquipment) return;
	//AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(this);
	//ABattleLevelGameModeBase* pBattleGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
	float increaseTick = dT * (float)m_speedRatePercent / 100.f;
	//int32 increaseTick = pBattleGameMode->m_increaseTickPerFrame * m_speedRatePercent / 100;
	for (int32 i=0; i<m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!m_pBaseEquipment->m_pSkills[i]) continue;
		if (m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_TransientPunch")
		{
			//如果是TransientPunch的技能，只有当当前计时大于等于冻结时间，才能解锁
			if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += increaseTick;
				/*if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_freezeMotionTime && m_curSkillNb == i && m_curEquipNb == -1)
					StopContinuousTask();*/
				if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime)
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
					m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;
					m_pBaseEquipment->m_pSkills[i]->m_hasSpawnGeo = false;
				}
				
			}
		}
		/*else if (m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_ContinuousPunch" ||
			m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_RepeatPunch")
		{
			//如果是持续型技能，同时此技能为正在使用
			if (m_curSkillNb == i)
			{
				if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_maxContinuousSkillTime && m_curEquipNb == -1)
					StopContinuousTask();
				if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag && 
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime)
					m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;
				
				m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += increaseTick;
			}
			else
			{
				if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += increaseTick;
					if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime)
					{
						m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
						m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;
						m_pBaseEquipment->m_pSkills[i]->m_hasSpawnGeo = false;
					}
				}
				else
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
					m_pBaseEquipment->m_pSkills[i]->m_hasSpawnGeo = false;
				}
			}
		}*/
	}
}

void ABaseCharacter::UpdateAllTimeDilationEffects(float dT)
{
	TArray<FString> removeKeys;
	for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.type != 1) continue;
		if (iter->Value.duration <= 0)
			removeKeys.Add(iter->Key);
		else
			m_timeDilationParams[iter->Key].duration -= dT;
	}
	if (removeKeys.Num() <= 0) return;

	for (int32 i=0; i<removeKeys.Num(); i++)
	{
		m_timeDilationParams.Remove(removeKeys[i]);
	}

	int32 minTimeDilation = 100;
	for (TMap<FString, FTimeDilationInfo>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value.timeDilationPercent <= minTimeDilation)
		{
			minTimeDilation = iter->Value.timeDilationPercent;
			//curTimeDilationKey = iter->Key;
		}
	}

	//m_curTimeDilationKey = curTimeDilationKey;
	CustomTimeDilation = (float)minTimeDilation / 100.f;
	m_speedRatePercent = minTimeDilation;
}

/*
void ABaseCharacter::UpdateCurSkillState(float dT)
{
	//如果技能号为-1，说明角色当前行为不是施放技能，退出
	if (m_curSkillNb == -1) return;
	//技能施放分几个阶段
	//1.当时间等于前摇结束时间，生成几何体
	//2.如技能为短暂型技能，当时间等于动作冻结结束时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	//3.如技能为持续型技能，当时间等于最大持续时间时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	UCharacterEquipInfo* pEquipInfo = m_pBaseEquipment;

	bool isSpawnGeo = false;
	UBaseSkill* pSkill = NULL;
	pSkill = pEquipInfo->m_pSkills[m_curSkillNb];

	int32 scalePreShakeLogicTick = pSkill->m_preShakeLogicTickTime;

	/ *if (pSkill->m_skillMotionTypeString == "PMS_RepeatPunch" && pSkill->m_skillFrameCount >= scalePreShakeLogicTick)
	{
		//当前技能计时大于前摇时限同时为RepeatPunch时即可开始生成几何体
		int32 scaleRepeatSpawnInterval = pSkill->m_repeatSkillSpawnInterval / 100;
		int32 remainder = pSkill->m_skillFrameCount % scaleRepeatSpawnInterval;
		if (remainder == 0)
		{
			//说明当前计时是m_repeatSkillSpawnInterval的整数倍，此时可生成几何体
			m_pBaseAnimInstance->NotifyImplementSkill(pSkill->m_skillAnimName);
			isSpawnGeo = true;
		}
	}* /
	if (!pSkill->m_hasSpawnGeo &&
		(pSkill->m_skillMotionTypeString == "PMS_TransientPunch" || pSkill->m_skillMotionTypeString == "PMS_ContinuousPunch") &&
		pSkill->m_skillFrameCount >= scalePreShakeLogicTick)
	{
		isSpawnGeo = true;
		pSkill->m_hasSpawnGeo = true;
	}
	if (isSpawnGeo)
	{
		for (int32 i=0; i<m_curIntrinsicActiveAttributeInfo.Num(); i++)
		{
			if (m_curIntrinsicActiveAttributeInfo[i].reactionType == 4) return;
		}
		/ ** 可以生成几何体了，但需要分两种情况
		* 一是普通技能，按照正常流程生成几何体即可
		* 二是召唤技能，此时生成的是角色而非几何体
		* /
		pSkill->m_campFlag = m_campFlag;

		//此为普通技能发动流程
		TArray<ABasePhysGeo*> spawnGeos;
		int32 geoNb = 0;
		float yaw = GetActorRotation().Yaw;
		for (int32 i = 0; i < pSkill->m_geoClass.Num(); i++)
		{
			if (!pSkill->m_geoClass[i]) continue;
			//int32 halfNb = (pSkill->m_spawnGeoNb[i] - pSkill->m_spawnGeoNb[i] % 2) / 2;
			TSubclassOf<class UObject> geoClass = pSkill->m_geoClass[i];
			for (int32 j = 0; j < pSkill->m_spawnGeoNb[i]; j++)
			{
				int32 relativeLauchAngle = pSkill->m_spreadAngle[geoNb];
				FVector spawnPtCharacterOffset = m_pSpawnPoint->GetComponentLocation() - GetActorLocation();
				FVector roateVector = spawnPtCharacterOffset.RotateAngleAxis(relativeLauchAngle, FVector::UpVector);
				//FVector relativeLauchLoc = GetActorLocation() + roateVector;
				//FLogicVec2D relativeLauchLoc = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicRelativeSpawnPoint, FLogicVec2D(0, 0), relativeLauchAngle + yaw)*pSkill->m_spawnDistanceAmplifiedList[geoNb];
				//FLogicVec2D launchLogicDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_curLogicForwardDir, FLogicVec2D(0, 0), relativeLauchAngle);
				FRotator launchRotator(0, yaw + relativeLauchAngle, 0);
				FVector launchLoc(GetActorLocation().X + roateVector.X, GetActorLocation().Y + roateVector.Y, m_defaultHeight);
				ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(pSkill->m_geoClass[i], launchLoc, launchRotator);
				for (int32 k = 0; k < spawnGeos.Num(); k++)
				{
					spawnGeos[k]->m_pRootGeos.Add(pGeo);
					pGeo->m_pRootGeos.Add(spawnGeos[k]);
				}
				pGeo->SetAttachEquipment(pEquipInfo);
				//pGeo->m_logicForwardDir = launchLogicDir;
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
		//此处播放发动技能时刻的特效
		SetSkillIndependentFXTemplate(pSkill->m_skillName);
	}
}*/

void ABaseCharacter::NotifyLaunchSkill()
{
	if (m_curSkillNb == -1) return;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "BaseCharacter::NotifyLaunchSkill");
	//技能施放分几个阶段
	//1.当时间等于前摇结束时间，生成几何体
	//2.如技能为短暂型技能，当时间等于动作冻结结束时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	//3.如技能为持续型技能，当时间等于最大持续时间时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	UCharacterEquipInfo* pEquipInfo = m_pBaseEquipment;

	bool isSpawnGeo = false;
	UBaseSkill* pSkill = NULL;
	pSkill = pEquipInfo->m_pSkills[m_curSkillNb];

	if (!pSkill->m_hasSpawnGeo &&
		(pSkill->m_skillMotionTypeString == "PMS_TransientPunch" || pSkill->m_skillMotionTypeString == "PMS_ContinuousPunch"))
	{
		isSpawnGeo = true;
		pSkill->m_hasSpawnGeo = true;
	}
	if (isSpawnGeo)
	{
		for (TMap<uint8, FEffectList>::TConstIterator iter = m_curIntrinsicActiveAttributeInfo.CreateConstIterator(); iter; ++iter)
		{
			for (int32 i=0; i<iter->Value.Effects.Num(); i++)
			{
				if (iter->Value.Effects[i]->m_functionNames.Contains("AtkForbiden"))
					return;
			}
		}
		/** 可以生成几何体了，但需要分两种情况
		* 一是普通技能，按照正常流程生成几何体即可
		* 二是召唤技能，此时生成的是角色而非几何体
		*/
		pSkill->m_campFlag = m_campFlag;

		//此为普通技能发动流程
		TArray<ABasePhysGeo*> spawnGeos;
		int32 geoNb = 0;
		float yaw = GetActorRotation().Yaw;
		for (int32 i = 0; i < pSkill->m_mutationGeoClass[-1].geoClasses.Num(); i++)
		{
			if (!pSkill->m_mutationGeoClass[-1].geoClasses[i]) continue;
			//int32 halfNb = (pSkill->m_spawnGeoNb[i] - pSkill->m_spawnGeoNb[i] % 2) / 2;
			TSubclassOf<class UObject> geoClass = pSkill->m_mutationGeoClass[-1].geoClasses[i];
			for (int32 j = 0; j < pSkill->m_spawnGeoNb[i]; j++)
			{
				int32 relativeLauchAngle = pSkill->m_spreadAngle[geoNb];
				FVector spawnPtCharacterOffset = m_pSpawnPoint->GetComponentLocation() - GetActorLocation();
				FVector roateVector = spawnPtCharacterOffset.RotateAngleAxis(relativeLauchAngle, FVector::UpVector);
				//FVector relativeLauchLoc = GetActorLocation() + roateVector;
				//FLogicVec2D relativeLauchLoc = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicRelativeSpawnPoint, FLogicVec2D(0, 0), relativeLauchAngle + yaw)*pSkill->m_spawnDistanceAmplifiedList[geoNb];
				//FLogicVec2D launchLogicDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_curLogicForwardDir, FLogicVec2D(0, 0), relativeLauchAngle);
				FRotator launchRotator(0, yaw + relativeLauchAngle, 0);
				FVector launchLoc;
				//这里要根据技能类型来确定生成的位置
				if (pSkill->m_skillType == 1)
				{
					//定位型技能
					launchLoc.X = m_targetLoc.X + roateVector.X;
					launchLoc.Y = m_targetLoc.Y + roateVector.Y;
					launchLoc.Z = m_defaultHeight;
				}
				else if (pSkill->m_skillType == 4)
				{
					FVector2D randDir = FMath::RandPointInCircle((float)pSkill->m_spawnDistanceAmplifiedList[0]);
					FVector randLoc = GetActorLocation() + FVector(randDir.X, randDir.Y, 0);
					launchLoc.X = randLoc.X;
					launchLoc.Y = randLoc.Y;
					launchLoc.Z = m_defaultHeight;
				}
				else
				{
					//launchLoc.X = GetActorLocation().X + roateVector.X;
					//launchLoc.Y = GetActorLocation().Y + roateVector.Y;
					launchLoc.X = m_pSpawnPoint->GetComponentLocation().X + roateVector.X;
					launchLoc.Y = m_pSpawnPoint->GetComponentLocation().Y + roateVector.Y;
					launchLoc.Z = m_defaultHeight;
				}
				ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(pSkill->m_mutationGeoClass[-1].geoClasses[i], launchLoc, launchRotator);
				if (pSkill->m_skillType == 2)
				{
					AProjectilePoint* pProjectilePoint = Cast<AProjectilePoint>(pGeo);
					pProjectilePoint->InitialProjectilePoint(m_targetLoc);
				}
				//pGeo->SetMutationPS();
				spawnGeos.Add(pGeo);
				for (int32 k = 0; k < spawnGeos.Num(); k++)
				{
					spawnGeos[k]->m_pRootGeos.Add(pGeo);
					pGeo->m_pRootGeos.Add(spawnGeos[k]);
				}
				pGeo->SetAttachEquipment(pEquipInfo);
				//pGeo->m_logicForwardDir = launchLogicDir;
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
		//此处播放发动技能时刻的特效
		SetSkillIndependentFXTemplate(pSkill->m_skillName);
	}
}

void ABaseCharacter::NotifyEndSkill()
{
	if (!m_pBaseEquipment) return;
	//UBaseSkill* pSkill = NULL;
	//pSkill = m_pBaseEquipment->m_pSkills[m_curSkillNb];
	StopContinuousTask();
	//pSkill->m_skillFrameCount = 0;
	//pSkill->m_canImplementFlag = true;
	//pSkill->m_hasSpawnGeo = false;
}

void ABaseCharacter::DeleteSkill(int32 deleteSkillNb)
{

}

bool ABaseCharacter::TellWhetherCharacterContainEffect(FString effectName)
{
	for (int32 i=0; i<m_pEffects.Num(); i++)
	{
		if (!m_pEffects[i]) continue;
		if (m_pEffects[i]->m_effectName == effectName) return true;
	}
	return false;
}

bool ABaseCharacter::IsContainEffect(FString effectName)
{
	if (m_beCarriedSkillNames.Contains(effectName)) return true;
	else return false;
}

void ABaseCharacter::EffectOnFx_Implementation(bool goodOrBad)
{

}

void ABaseCharacter::StopContinuousTask()
{
	/**需要考虑其中一种特殊情况是当玩家使用完此物体后切换到其他装备，然后此物体继续计时，当计时完毕后会触发StopContinuousTask
	* 而由于此时手持物品非完成计时的物体，从而暂停错了装备
	* 上述考虑情况不存在，因为如不考虑召唤技能（即手持任意装备均可发动），那么在计时超过FreezeMotionTime时是不允许任何
	* 操作的，所以是不允许玩家使用完此物体后立刻切换到其他装备的情况
	* 即使是手持其他任意装备而发动召唤技能的情况，同样需要如下操作
	*/
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, "sdf");
	m_curSkillNb = -1;
	m_pBaseAnimInstance->m_motionStateString = "PMS_NULL";
	int32 i = 0;
	while (i < m_pControlPhysGeos.Num())
	{
		if (!m_pControlPhysGeos[i]) m_pControlPhysGeos.RemoveAt(i);
		else
		{
			m_pControlPhysGeos[i]->m_isGeoValid = false;
			i++;
		}
	}
	m_pBaseAnimInstance->NotifyStopAnim();
	m_actionName = "NULL";
	//如当前持有道具不是默认武器，要对持有道具的数量进行判断，如数量小于等于0，自动切换回默认武器，然后删除掉该道具
	/**需要考虑其中一种特殊情况是当玩家使用完此物体后切换到其他装备，然后此物体继续计时，当计时完毕后会触发StopContinuousTask
	* 而由于此时手持物品非完成计时的物体，从而删除错了装备
	* 上述考虑情况不存在，因为如不考虑召唤技能（即手持任意装备均可发动），那么在计时超过FreezeMotionTime时是不允许任何
	* 操作的，所以是不允许玩家使用完此物体后立刻切换到其他装备的情况
	* 如果是手持任意装备而发动召唤技能的情况，直接跳过下面操作
	*/
	if (m_implementSkillType != 0)
	{
		m_implementSkillType = 0;
		return;
	}
	/*if (m_curEquipNb == -1 || !m_pEquipmentInfos[m_curEquipNb]) return;
	m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb -= 1;
	if (m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb <= 0)
	{
		int32 equipNb = m_curEquipNb;
		ChangeEquipment(-1);
		DeleteEquipment(equipNb);
	}
	else
	{
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		//pBattlePC->m_pItemMenu->UpdateItemList(m_pEquipmentInfos[m_curEquipNb]->m_equipmentName, m_pEquipmentInfos[m_curEquipNb]->m_equipmentNb, 1);
	}*/
}




















/**
*移动模块
*
*
*
*/
/*

void ABaseCharacter::Accelerate_Int()
{/ *
	//if (!m_hasUpdateVel && !m_isPlayerCharacter) return;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "ID: " + FString::FromInt(m_entityID) + " cur logic velX is: " + FString::FromInt(m_curLogicVelocity.X));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "cur logic velY is: " + FString::FromInt(m_curLogicVelocity.Y));
	int32 expandDeltaX = m_curLogicVelocity.X * m_expandLogicTickTimeDelta;
	int32 expandDeltaY = m_curLogicVelocity.Y * m_expandLogicTickTimeDelta;
	int32 deltaX = expandDeltaX / 1000;
	int32 deltaY = expandDeltaY / 1000;
	if (m_characterType == 0 && m_pNormalLongTask)
	{
		FLogicVec2D destinationOffset = m_pNormalLongTask->m_destination - m_logicPos2D;
		int32 destinationOffsetSquare = destinationOffset.sqr();
		if ((deltaX*deltaX + deltaY * deltaY) >= destinationOffsetSquare)
		{
			deltaX = destinationOffset.X;
			deltaY = destinationOffset.Y;
		}
	}
	
	FLogicVec2D nextLogicLoc(m_logicPos2D.X + deltaX, m_logicPos2D.Y + deltaY);	
	if (nextLogicLoc == m_logicPos2D) return;
	FLogicVec2D offset(deltaX, deltaY);
	FLogicVec2D offsetPerpendicularVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(FLogicVec2D(-deltaY, deltaX), m_characterRadius);
	FLogicVec2D offsetNormalizeVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(offset, m_characterRadius);
	TArray<FLogicVec2D> coverPts;
	coverPts.Add(m_logicPos2D + offsetPerpendicularVec);
	coverPts.Add(m_logicPos2D - offsetPerpendicularVec);
	coverPts.Add(nextLogicLoc - offsetPerpendicularVec + offsetNormalizeVec);
	coverPts.Add(nextLogicLoc + offsetPerpendicularVec + offsetNormalizeVec);

	FVector startPoint(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight);
	FVector lineTraceEndPt(nextLogicLoc.X + offsetNormalizeVec.X, nextLogicLoc.Y + offsetNormalizeVec.Y, m_defaultHeight);
	TArray<FHitResult> hitResults;
	FCollisionResponseParams responseParams;
	responseParams.CollisionResponse.SetAllChannels(ECR_Overlap);
	GetWorld()->SweepMultiByChannel(hitResults, startPoint, lineTraceEndPt, FQuat::Identity, COLLISION_OBSTACLE_FINDING,
		FCollisionShape::MakeSphere(m_characterRadius + 2), FCollisionQueryParams::DefaultQueryParam, responseParams);
	bool canMove = true;
	if (m_characterType == 1)
	{
		for (int32 i = 0; i < hitResults.Num(); i++)
		{
			if (hitResults[i].GetActor() == this || !hitResults[i].GetActor()) continue;
			if (!hitResults[i].GetComponent()) continue;
			if (!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysGeo"))) &&
				!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("DumpActor")))) continue;
			if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysGeo"))) &&
				!hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("Boundary")))) continue;

			if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysPolygon"))))
			{
				APhysPolygon* pPolygon = Cast<APhysPolygon>(hitResults[i].GetActor());
				bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyPolyIntercept(coverPts, pPolygon->m_logicFixPts);
				if (!isIntercept) continue;
				bool isInPolygon = UCollisionWarBpFunctionLibrary::TellWhetherPointInsideConvex_Int(pPolygon->m_logicFixPts, m_logicPos2D);
				if (isInPolygon) continue;
				canMove = false;
				break;
			}
			else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysActor"))))
			{
				ABasePhysActor* pActor = Cast<ABasePhysActor>(hitResults[i].GetActor());
				bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyCircleIntercept(coverPts, pActor->m_logicPos2D, pActor->m_actorRadius);
				if (!isIntercept) continue;
				int32 distance = UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint_Int(m_logicPos2D, pActor->m_logicPos2D);
				if (distance <= pActor->m_actorRadius) continue;
				canMove = false;
				break;
			}
			else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("DumpActor"))))
			{
				ADumpPhysActor* pActor = Cast<ADumpPhysActor>(hitResults[i].GetActor());
				bool isIntercept = UCollisionWarBpFunctionLibrary::IsPolyCircleIntercept(coverPts, pActor->m_logicPos2D, pActor->m_actorRadius);
				if (!isIntercept) continue;
				int32 distance = UCollisionWarBpFunctionLibrary::GetDisFromPointToPoint_Int(m_logicPos2D, pActor->m_logicPos2D);
				if (distance <= pActor->m_actorRadius) continue;
				canMove = false;
				break;
			}
			/ *else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysLine"))))
			{
				APhysLine* pLine = Cast<APhysLine>(hitResults[i].GetActor());
				bool isIntercept = UCollisionWarBpFunctionLibrary::IsSegmentsIntersect_Int(pLine->m_logicStartPoint, pLine->m_logicEndPoint,
					m_logicPos2D, nextLogicLoc);
				if (!isIntercept) continue;
				canMove = false;
				break;
			}* /
		}
	}
	
	//DrawDebugPoint(GetWorld(), FVector(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight), 20, FColor::Red, false, 0.1);
	if (!canMove)
	{
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
		m_pBaseAnimInstance->m_speed = 0;
		return;
	}
	m_preLogicPos2D = m_logicPos2D;
	m_logicPos2D = nextLogicLoc;
	FVector nextLoc(m_preLogicPos2D.X, m_preLogicPos2D.Y, m_defaultHeight + m_relativeHeight);
	SetActorLocation(nextLoc);
	//m_hasUpdateVel = false;
* /

}
*/

/*
void ABaseCharacter::Brake_Int()
{
	FLogicVec2D brakeDir(-m_curLogicVelocity.X, -m_curLogicVelocity.Y);
	FLogicVec2D brakeVec = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(brakeDir, m_acc);
	if (UCollisionWarBpFunctionLibrary::GetLogicVecSize(brakeVec) >= UCollisionWarBpFunctionLibrary::GetLogicVecSize(m_curLogicVelocity))
		m_curLogicVelocity = FLogicVec2D(0,0);
	else
	{
		m_curLogicVelocity = m_curLogicVelocity + brakeVec;
	}
	
	m_pBaseAnimInstance->m_speed = UCollisionWarBpFunctionLibrary::GetLogicVecSize(m_curLogicVelocity);
	GetCharacterMovement()->Velocity = FVector(m_curLogicVelocity.X, m_curLogicVelocity.Y, 0);
}*/

bool ABaseCharacter::HasReachCurDes_Int(FVector des)
{
	FVector offset = des - GetActorLocation();
	if (offset.Size() <= 1) return true;
	else return false;
}
/*

void ABaseCharacter::MoveToTarget_Int(bool isPlayer, bool canMove)
{
	if (m_isInitialDoneFlag == true && (m_pBaseAnimInstance->m_motionStateString == "PMS_TransientPunch" || !canMove))
	{
		if (isPlayer) return;
		else
		{
			m_curLogicVelocity.X = 0;
			m_curLogicVelocity.Y = 0;
			m_pBaseAnimInstance->m_speed = 0;
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			return;
		}
	}
	if (!isPlayer)
	{
		FLogicVec2D scaleLogicVel(0,0);
		if (m_speedRatePercent != 0) scaleLogicVel = m_logicVelOperation * m_speedRatePercent / 100;
		m_curLogicVelocity = scaleLogicVel;
		m_pBaseAnimInstance->m_speed = UCollisionWarBpFunctionLibrary::GetLogicVecSize(m_logicVelOperation);
		GetCharacterMovement()->Velocity = FVector(m_curLogicVelocity.X, m_curLogicVelocity.Y, 0);
	}
	//调整朝向
	m_curLogicForwardDir = m_logicForwardOperation;
	FVector modifyDirVector(m_curLogicForwardDir.X, m_curLogicForwardDir.Y, 0);
	FRotator modifyRotator = modifyDirVector.ToOrientationRotator();
	SetActorRotation(modifyRotator);
	/ *GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, TEXT("Character forwardX: ") + FString::FromInt(m_curLogicForwardDir.X) + 
		TEXT(" Character forwardY: ") + FString::FromInt(m_curLogicForwardDir.Y));* /
	//更新spawnPoint位置
	int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_curLogicForwardDir);
	FLogicVec2D spawnPointDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicRelativeSpawnPoint, FLogicVec2D(0, 0), yaw);
	m_logicSpawnPoint = m_logicPos2D + spawnPointDir;
	//DrawDebugPoint(GetWorld(), FVector(m_logicSpawnPoint.X, m_logicSpawnPoint.Y, m_defaultHeight), 20, FColor::Black, false, 0.1);
	//调整位置
	Accelerate_Int();
}*/













/**
*物理模块
*
*
*
*/
void ABaseCharacter::InitialCharacterAnim()
{
	if (m_pBaseAnimInstance) return;
	UAnimInstance* pAnimInstance = GetMesh()->GetAnimInstance();
	if (pAnimInstance)
	{
		m_pBaseAnimInstance = Cast<UBaseAnimInstance>(pAnimInstance);
		if (m_characterType == 1)
			m_pBaseAnimInstance->m_pCharacter = Cast<AKing>(this);
		if (m_pBaseAnimInstance)
		{
			m_pBaseAnimInstance->m_notifyChaImplementSkillDelegate.AddDynamic(this, &ABaseCharacter::AnimNotifyImplementSkill);
			m_pBaseAnimInstance->m_notifyChaStopTrasientMotionDelegate.AddDynamic(this, &ABaseCharacter::AnimNotifyStopTransientMotion);
		}
	}
}

void ABaseCharacter::KillCharacter()
{
	m_isInitialDoneFlag = false;
	GetMesh()->SetVisibility(false);
}

void ABaseCharacter::RecoverPhysics()
{
	GetMesh()->SetVisibility(true);
	m_isInitialDoneFlag = true;
}












void ABaseCharacter::EvaluateConditionAround(float deltaT)
{
	if (m_thinkMode == ECharacterThinkMode::CTM_RandomAtk)
		EvaluateLongTaskUnderRandomAttackState();
	else if (m_thinkMode == ECharacterThinkMode::CTM_Patrol)
		EvaluateLongTaskPatrolling(deltaT);
	else
		EvaluateLongTaskUnderPlayerHunterState();
	EvaluateShortTask();
	m_hasUpdateAI = true;
}

void ABaseCharacter::InitialBaseEquipmentInfo()
{
	if (!m_pBaseEquipment)
	{
		if (!m_baseEquipInfoClass) return;
		m_pBaseEquipment = NewObject<UCharacterEquipInfo>(this, m_baseEquipInfoClass);
	}
}

void ABaseCharacter::EvaluateLongTaskUnderStrongholdDestroyerState()
{
	//只有主机才计算，每两个逻辑帧计算一次，上报给服务端
	if (!m_pNormalLongTask || !m_pBaseEquipment) return;

	ABaseCharacter* pTarget = NULL;
	float minLogicDis = 0;
	for (int32 i = 0; i < m_pOppCharacters.Num(); i++)
	{
		if (!m_pOppCharacters[i]) continue;
		FVector enermyPos = m_pOppCharacters[i]->GetActorLocation();
		FVector offsetToCurLoc = enermyPos - GetActorLocation();
		if (!pTarget)
		{
			pTarget = m_pOppCharacters[i];
			minLogicDis = FMath::Sqrt(offsetToCurLoc.Size());
		}
		else
		{
			if (pTarget->m_characterType == 2 && (m_pOppCharacters[i]->m_characterType == 0 || m_pOppCharacters[i]->m_characterType == 1)) continue;
			float offsetLen = FMath::Sqrt(offsetToCurLoc.Size());
			if (offsetLen < minLogicDis)
			{
				pTarget = m_pOppCharacters[i];
				minLogicDis = offsetLen;
			}
		}
	}

	if (pTarget)
	{
		UBaseSkill* pAvailableBestSkill = NULL;
		for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				pAvailableBestSkill = m_pBaseEquipment->m_pSkills[i];
				break;
			}
		}
		if (!pAvailableBestSkill)
		{
			//说明此时所有技能都处于CD中
			//这时判断首选技能（虽然仍然在CD中）是否能覆盖目标，如不可以即向目标移动
			//如可以即停止移动并向目标瞄准
			if (m_pBaseEquipment->m_pSkills.Num() == 0) return;
			pAvailableBestSkill = m_pBaseEquipment->m_pSkills[0];
			if (pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = GetActorLocation();
			}
			else
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
			}
		}
		else if (pAvailableBestSkill && !pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
		}
		else if (pAvailableBestSkill && pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = GetActorLocation();
		}
	}
	else
	{
		m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
		m_pNormalLongTask->m_pTarget = NULL;
		m_pNormalLongTask->m_destination = GetActorLocation();
	}
}

void ABaseCharacter::EvaluateLongTaskUnderPlayerHunterState()
{
	//只有主机才计算，每两个逻辑帧计算一次，上报给服务端
	if (!m_pNormalLongTask || !m_pBaseEquipment) return;

	ABaseCharacter* pTarget = NULL;
	float minLogicDis = 0;
	for (int32 i = 0; i < m_pOppCharacters.Num(); i++)
	{
		if (!m_pOppCharacters[i]) continue;
		FVector enermyPos = m_pOppCharacters[i]->GetActorLocation();
		FVector offsetToCurLoc = enermyPos - GetActorLocation();
		if (!pTarget)
		{
			pTarget = m_pOppCharacters[i];
			minLogicDis = FMath::Sqrt(offsetToCurLoc.Size());
		}
		else
		{
			if (pTarget->m_characterType == 1 && (m_pOppCharacters[i]->m_characterType == 0 || m_pOppCharacters[i]->m_characterType == 2)) continue;
			float offsetLen = FMath::Sqrt(offsetToCurLoc.Size());
			if (offsetLen < minLogicDis)
			{
				pTarget = m_pOppCharacters[i];
				minLogicDis = offsetLen;
			}
		}
	}

	if (pTarget)
	{
		UBaseSkill* pAvailableBestSkill = NULL;
		for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				pAvailableBestSkill = m_pBaseEquipment->m_pSkills[i];
				break;
			}
		}
		if (!pAvailableBestSkill)
		{
			//说明此时所有技能都处于CD中
			//这时判断首选技能（虽然仍然在CD中）是否能覆盖目标，如不可以即向目标移动
			//如可以即停止移动并向目标瞄准
			if (m_pBaseEquipment->m_pSkills.Num() == 0) return;
			pAvailableBestSkill = m_pBaseEquipment->m_pSkills[0];
			if (pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = GetActorLocation();
			}
			else
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
			}
		}
		else if (pAvailableBestSkill && !pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
		}
		else if (pAvailableBestSkill && pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = GetActorLocation();
		}
	}
	else
	{
		m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
		m_pNormalLongTask->m_pTarget = NULL;
		m_pNormalLongTask->m_destination = GetActorLocation();
	}
}

void ABaseCharacter::EvaluateLongTaskPatrolling(float deltaT)
{
	if (!m_pNormalLongTask || !m_pBaseEquipment) return;

	// Only characters inside the range could be attacked
	// Enermy patrol around spawn point, he/she will not change path until destination is reached
	// Enermies will attack player immediately if player is found
	ABaseCharacter* pTarget = NULL;
	float minLogicDis = 0;
	for (int32 i = 0; i < m_pOppCharacters.Num(); i++)
	{
		if (!m_pOppCharacters[i]) continue;
		FVector enermyPos = m_pOppCharacters[i]->GetActorLocation();
		FVector offsetToCurLoc = enermyPos - GetActorLocation();
		if (!pTarget)
		{
			pTarget = m_pOppCharacters[i];
			minLogicDis = FMath::Sqrt(offsetToCurLoc.Size());
		}
		else
		{
			if (pTarget->m_characterType == 1 && (m_pOppCharacters[i]->m_characterType == 0 || m_pOppCharacters[i]->m_characterType == 2)) continue;
			float offsetLen = FMath::Sqrt(offsetToCurLoc.Size());
			if (offsetLen < minLogicDis)
			{
				pTarget = m_pOppCharacters[i];
				minLogicDis = offsetLen;
			}
		}
	}

	if (pTarget)
	{
		UBaseSkill* pAvailableBestSkill = NULL;
		for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				pAvailableBestSkill = m_pBaseEquipment->m_pSkills[i];
				break;
			}
		}
		if (!pAvailableBestSkill)
		{
			//说明此时所有技能都处于CD中
			//这时判断首选技能（虽然仍然在CD中）是否能覆盖目标，如不可以即向目标移动
			//如可以即停止移动并向目标瞄准
			if (m_pBaseEquipment->m_pSkills.Num() == 0) return;
			pAvailableBestSkill = m_pBaseEquipment->m_pSkills[0];
			if (pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = GetActorLocation();
			}
			else
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
			}
		}
		else if (pAvailableBestSkill && !pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
		}
		else if (pAvailableBestSkill && pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = GetActorLocation();
		}
	}
	else
	{
		// If this enermy is patrolling, return immediately
		if (m_pNormalLongTask->m_taskType == ETaskType::TT_Rush)
		{
			return;
		}
		else if (m_pNormalLongTask->m_taskType == ETaskType::TT_NULL)
		{
			if (m_currentPatrolIntervalCount >= m_patrolInterval)
			{
				// If no target is locked down, we should give an arbitrary target to move
				FVector2D randPatrolPoint2D = FMath::RandPointInCircle(m_patrolRange);
				FVector randPatrolPoint(randPatrolPoint2D.X, randPatrolPoint2D.Y, GetActorLocation().Z);
				m_pNormalLongTask->m_pTarget = NULL;
				m_pNormalLongTask->m_destination = randPatrolPoint;
				m_pNormalLongTask->m_taskType = ETaskType::TT_Rush;
				m_currentPatrolIntervalCount = 0.f;
			}
			else
			{
				m_currentPatrolIntervalCount += deltaT;
			}
		}
	}
}

void ABaseCharacter::EvaluateShortTask()
{
	if (!m_pNormalShortTask || !m_pBaseEquipment || m_pBaseAnimInstance->m_motionStateString != "PMS_NULL") return;
	ETaskType taskType = ETaskType::TT_NULL;
	int32 skillNb = -1;
	ABaseCharacter* pCharacter = NULL;
	for (int32 i=0; i<m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!m_pBaseEquipment->m_pSkills[i] || !m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		bool hasTarget = false;
		for (int32 j=0; j<m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Num(); j++)
		{
			hasTarget = true;
			break;
		}
		if (!hasTarget) continue;
		skillNb = i;
		break;
	}
	if (skillNb == -1)
	{
		m_pNormalShortTask->m_taskType = ETaskType::TT_NULL;
		m_pNormalShortTask->m_pTarget = NULL;
		m_pNormalShortTask->m_evaluateActionName = "NULL";
		m_pNormalShortTask->m_evaSkillNb = -1;
		//taskType = ETaskType::TT_NULL;
		//pCharacter = NULL;
		return;
	}

	float maxYaw = 0;
	int32 minHp = 0;
	float minDis = 0;
	int32 maxCosCharacterNb = 0;
	int32 minHpCharacterNb = 0;
	int32 minDisCharacterNb = 0;
	TArray<int32> scores;
	for (int32 i=0; i<m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters.Num(); i++)
	{
		int32 score = 0;
		scores.Add(score);
		if (m_pNormalLongTask && m_pNormalLongTask->m_pTarget &&
			m_pNormalLongTask->m_pTarget == m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i])
			score += 8;
		//FLogicVec2D curDir(m_curLogicForwardDir.X, m_curLogicForwardDir.Y);
		FVector targetDirOffset = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->GetActorLocation() - GetActorLocation();
		//FLogicVec2D targetDir(targetDirOffset.X, targetDirOffset.Y);
		float yaw = GetActorRotation().Yaw;
		float dis = targetDirOffset.Size();
		int32 hp = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->m_Hp;
		if (i == 0 || yaw >= maxYaw)
		{
			maxYaw = yaw;
			maxCosCharacterNb = i;
		}
		if (i == 0 || dis <= minDis)
		{
			minDis = dis;
			minDisCharacterNb = i;
		}
		if (i == 0 || hp <= minHp)
		{
			minHp = hp;
			minHpCharacterNb = i;
		}
	}

	if (scores.Num() > 0)
	{
		scores[maxCosCharacterNb] += 4;
		scores[minDisCharacterNb] += 2;
		scores[minHpCharacterNb] += 1;
		int32 maxScore = 0;
		int32 maxScoreNb = 0;
		for (int32 i=0; i<scores.Num(); i++)
		{
			if (scores[i] >= maxScore)
			{
				maxScore = scores[i];
				maxScoreNb = i;
			}
		}
		taskType = ETaskType::TT_ImplementSkill;
		pCharacter = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[maxScoreNb];
	}
	else
	{
		taskType = ETaskType::TT_NULL;
		pCharacter = NULL;
	}

	//根据evaluate结果赋值
	if (taskType == ETaskType::TT_NULL)
	{
		m_pNormalShortTask->m_evaluateActionName = "StopContinuousTask";
		m_pNormalShortTask->m_evaSkillNb = -1;
		m_pNormalShortTask->m_pTarget = NULL;
		m_pNormalShortTask->m_taskType = ETaskType::TT_NULL;
	}
	else if (taskType == ETaskType::TT_ImplementSkill)
	{
		m_pNormalShortTask->m_evaluateActionName = "ImplementSkill";
		m_pNormalShortTask->m_evaSkillNb = skillNb;
		m_pNormalShortTask->m_pTarget = pCharacter;
		m_pNormalShortTask->m_taskType = ETaskType::TT_ImplementSkill;
	}
}

void ABaseCharacter::EvaluateLongTaskUnderRandomAttackState()
{
	//只有主机才计算，每两个逻辑帧计算一次，上报给服务端
	if (!m_pNormalLongTask || !m_pBaseEquipment) return;

	ABaseCharacter* pTarget = NULL;
	float minLogicDis = 0;
	for (int32 i = 0; i < m_pOppCharacters.Num(); i++)
	{
		FVector enermyPos = m_pOppCharacters[i]->GetActorLocation();
		FVector offsetToCurLoc = enermyPos - GetActorLocation();
		if (!pTarget)
		{
			pTarget = m_pOppCharacters[i];
			minLogicDis = FMath::Sqrt(offsetToCurLoc.Size());
		}
		else
		{
			float offsetLen = FMath::Sqrt(offsetToCurLoc.Size());
			if (offsetLen < minLogicDis)
			{
				pTarget = m_pOppCharacters[i];
				minLogicDis = offsetLen;
			}
		}
	}

	if (pTarget)
	{
		UBaseSkill* pAvailableBestSkill = NULL;
		for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
		{
			if (m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				pAvailableBestSkill = m_pBaseEquipment->m_pSkills[i];
				break;
			}
		}
		if (!pAvailableBestSkill)
		{
			//说明此时所有技能都处于CD中
			//这时判断首选技能（虽然仍然在CD中）是否能覆盖目标，如不可以即向目标移动
			//如可以即停止移动并向目标瞄准
			if (m_pBaseEquipment->m_pSkills.Num() == 0) return;
			pAvailableBestSkill = m_pBaseEquipment->m_pSkills[0];
			if (pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = GetActorLocation();
			}
			else
			{
				m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
				m_pNormalLongTask->m_pTarget = pTarget;
				m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
			}
		}
		else if (pAvailableBestSkill && !pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_ChaseEnermy;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = pTarget->GetActorLocation();
		}
		else if (pAvailableBestSkill && pAvailableBestSkill->m_pOverlapCharacters.Contains(pTarget))
		{
			m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
			m_pNormalLongTask->m_pTarget = pTarget;
			m_pNormalLongTask->m_destination = GetActorLocation();
		}
	}
	else
	{
		m_pNormalLongTask->m_taskType = ETaskType::TT_StayAndAim;
		m_pNormalLongTask->m_pTarget = NULL;
		m_pNormalLongTask->m_destination = GetActorLocation();
	}
}

void ABaseCharacter::NotifyAnimStopMotion_Implementation()
{

}


void ABaseCharacter::NotifyAnimEffectChange(UEffect* pEffect,TArray<float> values)
{
	if (!m_pBaseAnimInstance) return;
	m_pBaseAnimInstance->NotifyEffectChange(pEffect->m_effectName, values);
}

void ABaseCharacter::NotifyBeingHurt_Implementation()
{

}

void ABaseCharacter::NotifyAnimCharacterDead()
{
	if (!m_pBaseAnimInstance) return;
	m_pBaseAnimInstance->TellCharacterDead();
}

void ABaseCharacter::SetSkillIndependentFXTemplate(const FString& skillName)
{
	UParticleSystem* pParticleSystem = NULL;
	FVector scale(1, 1, 1);
	FRotator rot(0, 0, 0);
	FVector loc(0, 0, 0);
	if (m_curEquipNb == -1)
	{
		if (!m_skillParticleMap.Find(skillName) || !m_skillParticleMap[skillName].particleSystem) return;
		else pParticleSystem = m_skillParticleMap[skillName].particleSystem;
		scale = m_skillParticleMap[skillName].scale;
		rot = m_skillParticleMap[skillName].rot + GetActorRotation();
		FVector loc2D(m_skillParticleMap[skillName].loc.X, m_skillParticleMap[skillName].loc.Y, 0);
		float actorYaw = GetActorRotation().Yaw;
		loc = loc2D.RotateAngleAxis(actorYaw, FVector(0, 0, 1));
		loc.Z = m_skillParticleMap[skillName].loc.Z;
	}
	else
	{
		if (!m_pEquipmentInfos[m_curEquipNb]->m_pParticleTemplate) return;
		else pParticleSystem = m_pEquipmentInfos[m_curEquipNb]->m_pParticleTemplate;
		rot = GetActorRotation();
		FVector loc2D(m_pEquipmentInfos[m_curEquipNb]->m_equipPSRelativeLoc.X, m_pEquipmentInfos[m_curEquipNb]->m_equipPSRelativeLoc.Y, 0);
		float actorYaw = GetActorRotation().Yaw;
		loc = loc2D.RotateAngleAxis(actorYaw, FVector(0, 0, 1));
		loc.Z = m_pEquipmentInfos[m_curEquipNb]->m_equipPSRelativeLoc.Z;
	}
	FVector spawnPointLoc = m_pSpawnPoint->GetComponentLocation();
	FVector launchLoc(spawnPointLoc.X, spawnPointLoc.Y, m_defaultHeight);
	UGameplayStatics::SpawnEmitterAtLocation(this, pParticleSystem, loc + launchLoc, rot,scale, true);
	//UGameplayStatics::SpawnEmitterAttached(pParticleSystem, GetMesh(), FName(*socketName), loc, rot, EAttachLocation::KeepWorldPosition, true);
}

void ABaseCharacter::ImplementSkill_Int(int32 campFlag)
{
	//更新装备号curEquipNb
	if (m_equipOperationNb != -1) m_curEquipNb = m_equipOperationNb;
	//更新技能号curSkillNb
	m_curSkillNb = m_skillOperationNb;
	UBaseSkill* pSkill = NULL;
	UCharacterEquipInfo* pEquipInfo = m_pBaseEquipment;
	/*if (m_curEquipNb == -1) pEquipInfo = m_pBaseEquipment;
	else pEquipInfo = m_pEquipmentInfos[m_curEquipNb];*/
	//更新动作指令，用于动画
	pSkill = pEquipInfo->m_pSkills[m_curSkillNb];
	pSkill->m_campFlag = campFlag;
	m_pBaseAnimInstance->m_motionStateString = pSkill->m_skillMotionTypeString;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, pSkill->m_skillAnimName);
	m_pBaseAnimInstance->NotifyImplementSkill(pSkill->m_skillAnimName);
	//更新技能信息
	pSkill->m_canImplementFlag = false;
	
	//实施所有信息后，恢复接口
	m_actionName = "NULL";
}

void ABaseCharacter::ImplementSkillAttachEffect(FEffectParams effectParam, ABasePhysGeo* pGeo)
{
	if (effectParam.functionNames[0].Contains("FullField_") || effectParam.functionNames[0].Contains("FullFieldLink_"))
	{
		//说明是全场型技能
		AGameModeBase* pGM = UGameplayStatics::GetGameMode(this);
		ARoguelikeBattleGameMode* pRGM = Cast<ARoguelikeBattleGameMode>(pGM);
		pRGM->m_fullFieldEffectMap.Add(pGeo, effectParam);
	}
	else
	{
		if (!effectParam.canOverlap)
		{
			bool isContainEffect = false;
			for (int32 i = 0; i < m_pEffects.Num(); i++)
			{
				if (m_pEffects[i]->m_effectName == effectParam.effectName)
				{
					isContainEffect = true;
					break;
				}
			}
			if (isContainEffect) return;
		}

		/*if (!ALuaActor::m_pGlobalLuaActor) return;
		ALuaActor::m_pGlobalLuaActor->LuaCharacterImplementSkillAttachEffect(effectName, this);*/
		FString effectName = effectParam.effectName;
		UCollisionWarSingleton* pSingleton = Cast<UCollisionWarSingleton>(GEngine->GameSingleton);
		TSubclassOf<class UObject> effectClass = pSingleton->FindEffectClassByName(effectName);
		if (!effectClass) return;
		APlayerController* pPC = UGameplayStatics::GetPlayerController(this, 0);
		ABattleLevelPlayerController* pBattlePC = Cast<ABattleLevelPlayerController>(pPC);
		UEffect* pNewEffect = NewObject<UEffect>(this, effectClass);
		pNewEffect->m_effectDefaultParam = effectParam;
		pNewEffect->m_pOriginGeo = NULL;
		pNewEffect->m_pHost = this;
		pNewEffect->m_duration = effectParam.duration;
		pNewEffect->m_effectName = effectParam.effectName;
		pNewEffect->m_effectValues = effectParam.effectValues;
		pNewEffect->m_functionNames = effectParam.functionNames;
		pNewEffect->m_effectOnIntervalList = effectParam.effectOnIntervalList;
		pNewEffect->m_isIntervalLoop = effectParam.isIntervalLoop;
		pNewEffect->m_isPhysOrMag = effectParam.isPhysOrMag;
		pNewEffect->m_isJudgeEffect = effectParam.isJudgeEffect;
		pNewEffect->m_hitColors = effectParam.hitColors;
		pNewEffect->m_hitNbs = effectParam.hitNbs;
		pNewEffect->m_isPermenant = effectParam.isPermenant;
		pNewEffect->m_canOverlap = effectParam.canOverlap;
		pNewEffect->m_appendEffectList = effectParam.appendEffectList;
		pNewEffect->m_launchType = 1;
		if (pBattlePC->m_pBattleMenu)
		{
			if (pBattlePC->m_pBattleMenu->m_pWidgetManager->m_language == "Chinese")
				pNewEffect->m_description = effectParam.chDescription;
			else
				pNewEffect->m_description = effectParam.enDescription;
		}
		m_pEffects.Add(pNewEffect);

		if (pBattlePC->m_pCharacterStatusMenu && pBattlePC->m_pCharacterStatusMenu->m_pCharacter == this)
			pBattlePC->m_pCharacterStatusMenu->UpdateStateList(pNewEffect, true);
		NotifyAddCharacterState(effectParam.effectName);
	}
}

void ABaseCharacter::NotifyAddCharacterState_Implementation(const FString& stateName)
{

}

void ABaseCharacter::NotifySetCharacterInfoWidget_Implementation()
{

}

void ABaseCharacter::NotifyCSDyeing_Implementation()
{

}

void ABaseCharacter::NotifyCSFade_Implementation()
{

}

void ABaseCharacter::SetCharacterInfoWidget(UTemplateCharacterInfo* pInfoWidget)
{
	m_pCharacterInfoWidget = pInfoWidget;
	m_pCharacterInfoWidget->m_maxHp = m_originHp;
	m_pCharacterInfoWidget->m_curHp = m_Hp;
	m_pCharacterInfoWidget->m_stateElements = m_stateNames;
	m_pCharacterInfoWidget->m_maxDFC = m_maxDFC;
	m_pCharacterInfoWidget->m_curDFC = m_DFC;
	m_pCharacterInfoWidget->m_atkAddition = m_ATKAddition;
	//m_pCharacterInfoWidget->NotifyHpChange(m_Hp);
}

void ABaseCharacter::NotifyRemoveCharacterState(FString stateName)
{
	if (!m_pCharacterInfoWidget) return;
	if (m_stateNames.Contains(stateName)) m_stateNames.Remove(stateName);
	UWidgetBlueprintFunctionLibrary::RemoveStateElementFromCharacterInfoBar(m_pCharacterInfoWidget, stateName);
}

void ABaseCharacter::UpdateJudgeCardList(int32 judgeCard)
{
	if (judgeCard == -1)
	{
		m_allJudgeCardInfos.Empty();
		//if (m_pCharacterInfoWidget) m_pCharacterInfoWidget->UpdateJudgeList(-1);
		return;
	}
	if (m_allJudgeCardInfos.Num() >= m_maxJudgeCardNb)
	{
		//if (m_pCharacterInfoWidget) m_pCharacterInfoWidget->UpdateJudgeList(-1);
		m_allJudgeCardInfos.Empty();
	}
	m_allJudgeCardInfos.Add(judgeCard);
	//if (m_pCharacterInfoWidget) m_pCharacterInfoWidget->UpdateJudgeList(judgeCard);
}

void ABaseCharacter::UpdateAllAttributes(float dT)
{
	/** 更新所有临时属性的时间，如超时删除元素，然后删除对应的元素反应组合
	*/
	TArray<uint8> removeList;
	for (TMap<uint8, float>::TConstIterator iter = m_tempAttributes.CreateConstIterator(); iter; ++iter)
	{
		if (iter->Value <= 0)
		{
			if (!removeList.Contains(iter->Key))
				removeList.Add(iter->Key);
		}
		else m_tempAttributes[iter->Key] = iter->Value - dT;
	}
	if (removeList.Num() <= 0) return;
	for (int32 i=0; i<removeList.Num(); i++)
	{
		if (!m_tempAttributes.Contains(removeList[i])) continue;
		m_tempAttributes.Remove(removeList[i]);
		AddOrRemoveAttachPS(removeList[i], false);
	}
	int32 curIdx = 0;
	while (curIdx < m_curTempActiveAttributeInfo.Num())
	{
		if (!m_tempAttributes.Contains(m_curTempActiveAttributeInfo[curIdx].reactionAttribute1) &&
			!m_tempAttributes.Contains(m_curTempActiveAttributeInfo[curIdx].reactionAttribute2))
			m_curTempActiveAttributeInfo.RemoveAt(curIdx);
		else curIdx += 1;
	}
	TArray<uint8> removeKeys;
	for (TMap<uint8, FEffectList>::TConstIterator iter = m_curIntrinsicActiveAttributeInfo.CreateConstIterator(); iter; ++iter)
	{
		if (!m_tempAttributes.Contains(iter->Key))
		{
			removeKeys.Add(iter->Key);
			for (int32 i=0; i<iter->Value.Effects.Num(); i++)
			{
				iter->Value.Effects[i]->m_isOnTimeEffectDone = true;
			}
		}
	}
	for (int32 i=0; i<removeKeys.Num(); i++)
	{
		m_curIntrinsicActiveAttributeInfo.Remove(removeKeys[i]);
	}
}

void ABaseCharacter::ChangeEquipment(int32 equipNb)
{
	if (equipNb == -1)
	{
		m_curEquipNb = -1;
		NotifyChangeEquipmentMesh(m_pBaseEquipment->m_pSkeletalMesh);
		return;
	}
	if (equipNb >= m_pEquipmentInfos.Num() || !m_pEquipmentInfos[equipNb]) return;
	m_curEquipNb = equipNb;
	if (!m_pEquipmentInfos[m_curEquipNb]->m_pSkeletalMesh) return;
	NotifyChangeEquipmentMesh(m_pEquipmentInfos[m_curEquipNb]->m_pSkeletalMesh);
}

bool ABaseCharacter::AddNewItem(FString itemName)
{
	return true;
}

void ABaseCharacter::RemoveItem(int32 itemID)
{

}

void ABaseCharacter::NotifyChangeEquipmentMesh_Implementation(USkeletalMesh* pSkeletonMesh)
{

}

void ABaseCharacter::AttachAttachmentTest(TSubclassOf<UBaseSkeletalMeshComponent> attachmentClass)
{
	m_BPAttachmentClass = attachmentClass;
	UBaseSkeletalMeshComponent* attachment = NewObject<UBaseSkeletalMeshComponent>(this, *m_BPAttachmentClass);
	attachment->RegisterComponent();
	attachment->AttachTo(GetMesh(), attachment->m_attachPointName);
	m_pHandAttachment = attachment;
}

void ABaseCharacter::HoveredCancel_Implementation()
{

}

void ABaseCharacter::CursorHovered_Implementation()
{

}

void ABaseCharacter::ReadSkillIndependentFXInfo_Implementation()
{

}

void ABaseCharacter::SetSkillDetectComponent(uint8 skillNb, UShapeComponent* pComponent)
{
	if (!m_pBaseEquipment) return;
	if (skillNb >= m_pBaseEquipment->m_pSkills.Num()) return;
	UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[skillNb];
	if (!pSkill) return;
	pSkill->m_pDetectComponent = pComponent;
	//pSkill->m_pDetectComponent->bGenerateOverlapEvents = 1;
}

void ABaseCharacter::OnDetectComponentBeginOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (!m_pBaseEquipment || !OtherComp || !OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))) || otherActor == this) return;
	for (uint8 i=0; i<m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pComponent == m_pBaseEquipment->m_pSkills[i]->m_pDetectComponent)
		{
			if (m_pBaseEquipment->m_pSkills[i]->m_skillEffectType == ESkillEffectType::SET_Heal || m_pBaseEquipment->m_pSkills[i]->m_skillEffectType == ESkillEffectType::SET_PositiveProtect)
			{
				for (int32 j = 0; j < m_pMyCharacters.Num(); j++)
				{
					if (otherActor == m_pMyCharacters[j])
					{
						if (m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Contains(m_pMyCharacters[j])) break;
						m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Add(m_pMyCharacters[j]);
						break;
					}
				}
			}
			else
			{
				for (int32 j = 0; j < m_pOppCharacters.Num(); j++)
				{
					if (otherActor == m_pOppCharacters[j])
					{
						if (m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Contains(m_pOppCharacters[j])) break;
						m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Add(m_pOppCharacters[j]);
						break;
					}
				}
			}
		}
	}
}

void ABaseCharacter::OnDetectComponentEndOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (!m_pBaseEquipment || !OtherComp || !OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter")))) return;
	for (uint8 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pComponent == m_pBaseEquipment->m_pSkills[i]->m_pDetectComponent)
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			if (m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Contains(pCharacter))
			{
				m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Remove(pCharacter);
			}
		}
	}
}

/*
void ABaseCharacter::AnimNotifyStopTransientMotion()
{
	StopShortTask();
}*/




