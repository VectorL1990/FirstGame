// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "HolySpirit.h"


// Sets default values
AHolySpirit::AHolySpirit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHolySpirit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHolySpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHolySpirit::SetSkillDetectComponent(uint8 skillNb, UShapeComponent* pComponent)
{
	if (!m_pBaseEquipment) return;
	if (skillNb >= m_pBaseEquipment->m_pSkills.Num()) return;
	UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[skillNb];
	pSkill->m_pDetectComponent = pComponent;
	pSkill->m_pDetectComponent->bGenerateOverlapEvents = 1;
}

void AHolySpirit::OnDetectComponentBeginOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	UBaseSkill* pSkill = NULL;
	if (!m_pBaseEquipment) return;
	for (uint8 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pComponent == m_pBaseEquipment->m_pSkills[i]->m_pDetectComponent)
		{
			pSkill = m_pBaseEquipment->m_pSkills[i];
			break;
		}
	}
	if (!pSkill) return;
	if (OtherComp != NULL)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			if (pSkill->m_skillEffectType == ESkillEffectType::SET_Heal || pSkill->m_skillEffectType == ESkillEffectType::SET_PositiveProtect)
			{
				for (int32 i = 0; i < m_pMyCharacters.Num(); i++)
				{
					if (otherActor == m_pMyCharacters[i])
					{
						if (pSkill->m_pOverlapCharacters.Contains(m_pMyCharacters[i])) return;
						pSkill->m_pOverlapCharacters.Add(m_pMyCharacters[i]);
						return;
					}
				}
			}
			else
			{
				for (int32 i = 0; i < m_pOppCharacters.Num(); i++)
				{
					if (otherActor == m_pOppCharacters[i])
					{
						if (pSkill->m_pOverlapCharacters.Contains(m_pOppCharacters[i])) return;
						pSkill->m_pOverlapCharacters.Add(m_pOppCharacters[i]);
						return;
					}
				}
			}
		}
	}
}

void AHolySpirit::OnDetectComponentEndOverlap(UShapeComponent* pComponent, class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	UBaseSkill* pSkill = NULL;
	if (!m_pBaseEquipment) return;
	for (uint8 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (pComponent == m_pBaseEquipment->m_pSkills[i]->m_pDetectComponent)
		{
			pSkill = m_pBaseEquipment->m_pSkills[i];
			break;
		}
	}
	if (!pSkill) return;
	if (OtherComp != NULL)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			if (pSkill->m_pOverlapCharacters.Contains(pCharacter))
			{
				pSkill->m_pOverlapCharacters.Remove(pCharacter);
			}
		}
	}
}

void AHolySpirit::ImplementSkill_Int(int32 campFlag)
{
	//更新装备号curEquipNb
	if (!m_pBaseEquipment) return;
	//更新动作指令，用于动画
	UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[m_curSkillNb];
	pSkill->m_campFlag = campFlag;
	NotifyPlayPreParticleEffect(pSkill->m_skillName);
	//更新技能信息
	pSkill->m_canImplementFlag = false;

	//实施所有信息后，恢复接口
	m_actionName = "NULL";
}

void AHolySpirit::NotifyPlayPreParticleEffect_Implementation(const FString& skillName)
{

}

void AHolySpirit::EvaluateShortTask()
{
	/*if (!m_pNormalShortTask || !m_pBaseEquipment) return;
	ETaskType taskType = ETaskType::TT_NULL;
	int32 skillNb = -1;
	ABaseCharacter* pCharacter = NULL;
	for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag) continue;
		bool hasTarget = false;
		for (int32 j = 0; j < m_pBaseEquipment->m_pSkills[i]->m_pOverlapCharacters.Num(); j++)
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

	int32 maxCos = 0;
	int32 minHp = 0;
	int32 minDis = 0;
	int32 maxCosCharacterNb = 0;
	int32 minHpCharacterNb = 0;
	int32 minDisCharacterNb = 0;
	TArray<int32> scores;
	for (int32 i = 0; i < m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters.Num(); i++)
	{
		int32 score = 0;
		scores.Add(score);
		FLogicVec2D curDir(m_curLogicForwardDir.X, m_curLogicForwardDir.Y);
		FLogicVec2D targetDir = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->m_logicPos2D - m_logicPos2D;
		int32 expandCos = UCollisionWarBpFunctionLibrary::GetExpandCosAngleOfTwoVector_Int(curDir, targetDir);
		int32 dis = UCollisionWarBpFunctionLibrary::GetLogicVecSize(targetDir);
		int32 hp = m_pBaseEquipment->m_pSkills[skillNb]->m_pOverlapCharacters[i]->m_Hp;
		if (i == 0 || expandCos >= maxCos)
		{
			maxCos = expandCos;
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
		for (int32 i = 0; i < scores.Num(); i++)
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
	}*/
}

void AHolySpirit::InitialBaseEquipmentInfo()
{
	if (!m_pBaseEquipment)
	{
		if (!m_baseEquipInfoClass) return;
		m_pBaseEquipment = NewObject<UCharacterEquipInfo>(this, m_baseEquipInfoClass);
	}
}

void AHolySpirit::UpdateAllSkills()
{
	//技能时钟主要包括是否生成几何体，是否冻结活动，是否冻结使用
	//看当前执行的skill是否已经过了前摇阶段，如过了前摇阶段则开始生成几何体
	//如还没度过前摇则不生成技能

	/*if (!m_pBaseEquipment) return;
	for (int32 i = 0; i < m_pBaseEquipment->m_pSkills.Num(); i++)
	{
		int32 scaleFreezeLogicTime = m_speedRatePercent * m_pBaseEquipment->m_pSkills[i]->m_freezeLogicTickTime / 100;
		int32 scaleFreezeMotionTime = m_speedRatePercent * m_pBaseEquipment->m_pSkills[i]->m_freezeMotionTime / 100;
		int32 scaleMaxContinuousTime = m_speedRatePercent * m_pBaseEquipment->m_pSkills[i]->m_maxContinuousSkillTime / 100;
		if (m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_TransientPunch")
		{
			//如果是TransientPunch的技能，只有当当前计时大于等于冻结时间，才能解锁
			if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
			{
				m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += 1;
				if (m_curSkillNb == i && m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= scaleFreezeMotionTime)
					StopContinuousTask();
				if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= scaleFreezeLogicTime)
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount = 0;
					m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;
					m_pBaseEquipment->m_pSkills[i]->m_hasSpawnGeo = false;
				}

			}
		}
		else if (m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_ContinuousPunch" ||
			m_pBaseEquipment->m_pSkills[i]->m_skillMotionTypeString == "PMS_RepeatPunch")
		{
			//如果是持续型技能，同时此技能为正在使用
			if (m_curSkillNb == i)
			{
				if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= scaleMaxContinuousTime)
					StopContinuousTask();
				if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag &&
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= scaleFreezeLogicTime)
					m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag = true;

				m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += 1;
			}
			else
			{
				if (!m_pBaseEquipment->m_pSkills[i]->m_canImplementFlag)
				{
					m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount += 1;
					if (m_pBaseEquipment->m_pSkills[i]->m_skillFrameCount >= scaleFreezeLogicTime)
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
		}
	}*/
}

void AHolySpirit::UpdateCurSkillState()
{
	//如果技能号为-1，说明角色当前行为不是施放技能，退出
	//技能施放分几个阶段
	//1.当时间等于前摇结束时间，生成几何体
	//2.如技能为短暂型技能，当时间等于动作冻结结束时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	//3.如技能为持续型技能，当时间等于最大持续时间时，说明技能结束，将curSkillNb、m_pBaseAnimInstance->m_motionStateString
	/*if (!m_pBaseEquipment) return;

	bool isSpawnGeo = false;
	UBaseSkill* pSkill = m_pBaseEquipment->m_pSkills[m_curSkillNb];

	int32 scalePreShakeLogicTick = m_speedRatePercent * pSkill->m_preShakeLogicTickTime / 100;

	if (!pSkill->m_hasSpawnGeo &&
		(pSkill->m_skillMotionTypeString == "PMS_TransientPunch" || pSkill->m_skillMotionTypeString == "PMS_ContinuousPunch") &&
		pSkill->m_skillFrameCount >= scalePreShakeLogicTick)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, TEXT("BaseCharacter::UpdateCurSkillState start to spawn geo and cur skill num is: ") + FString::FromInt(m_curSkillNb));
		isSpawnGeo = true;
		pSkill->m_hasSpawnGeo = true;
	}
	if (isSpawnGeo)
	{
		//可以生成几何体了
		pSkill->m_campFlag = m_campFlag;
		if (pSkill->m_geoClass.Num() == 0) return;
		if (pSkill->m_spawnGeoNb.Num() == 0) return;
		
		TArray<ABasePhysGeo*> spawnGeos;
		for (int32 i = 0; i < pSkill->m_geoClass.Num(); i++)
		{
			int32 halfNb = (pSkill->m_spawnGeoNb[i] - pSkill->m_spawnGeoNb[i] % 2) / 2;
			int32 divisionAngle = FMath::FloorToInt(pSkill->m_spreadAngle[i] / pSkill->m_spawnGeoNb[i]);
			TSubclassOf<class UObject> geoClass = pSkill->m_geoClass[i];
			for (int32 j = 0; j < pSkill->m_spawnGeoNb[i]; j++)
			{
				FLogicVec2D launchLogicDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_curLogicForwardDir, FLogicVec2D(0, 0), (j - halfNb)*divisionAngle);
				FVector launchVector(launchLogicDir.X, launchLogicDir.Y, 0);
				FRotator launchRotator = launchVector.ToOrientationRotator();
				FVector launchLoc(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight);
				ABasePhysGeo* pGeo = GetWorld()->SpawnActor<ABasePhysGeo>(pSkill->m_geoClass[i], launchLoc, launchRotator);
				for (int32 k = 0; k < spawnGeos.Num(); k++)
				{
					spawnGeos[k]->m_pRootGeos.Add(pGeo);
					pGeo->m_pRootGeos.Add(spawnGeos[k]);
				}
				//pGeo->SetAttachEquipment(pEquipInfo);
				pGeo->m_logicPos2D = m_logicPos2D;
				pGeo->m_logicForwardDir = launchLogicDir;
				m_pNewSpawnPhysGeos.Add(pGeo);
				if (pSkill->m_isHostSkill)
					m_pControlPhysGeos.Add(pGeo);
			}
		}
	}*/
}

void AHolySpirit::StopContinuousTask()
{
	m_curSkillNb = -1;
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
	m_actionName = "NULL";
}


