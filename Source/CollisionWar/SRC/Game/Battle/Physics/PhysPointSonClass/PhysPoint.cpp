// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../../../BattleLevelGameModeBase.h"
#include "../PhysPolySonClass/PhysPolygon.h"
#include "../PhysLineSonClass/PhysLine.h"
#include "PhysPoint.h"

// Sets default values
APhysPoint::APhysPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_physGeoType = EPhysGeoType::PGT_Point;
	m_hierachy = 0;
	m_pBasicComponent = NULL;
	m_pAttachEquipInfo = NULL;
}

// Called when the game starts or when spawned
void APhysPoint::BeginPlay()
{
	Super::BeginPlay();

}

void APhysPoint::Tick(float DeltaSeconds)
{
	/*if (m_preLogicPos == m_logicPos2D) return;
	FVector offset(m_logicPos2D.X - m_preLogicPos.X, m_logicPos2D.Y - m_preLogicPos.Y, 0);
	float offsetSize = offset.Size();
	offset.Normalize(0.1);
	FVector nextLoc = GetActorLocation() + offset * m_moveSpeed / m_movePerTick;
	nextLoc.Z = m_defaultHeight + m_relativeHeight;
	FVector predictOffset(nextLoc.X - m_preLogicPos.X, nextLoc.Y - m_preLogicPos.Y, 0);
	if (predictOffset.Size() >= offsetSize)
	{
		nextLoc.X = m_logicPos2D.X;
		nextLoc.Y = m_logicPos2D.Y;
	}
	SetActorLocation(nextLoc);*/
	//DrawDebugPoint(GetWorld(), nextLoc, 20, FColor::Red, false, 0.1);
	//FVector curLogicLoc(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight);
	//DrawDebugPoint(GetWorld(), nextLoc, 20, FColor::Green, false, 0.1);
	if (!m_isGeoValid) return;

	if (m_maxLifeTime != -1)
	{
		if (m_curLifeTime >= m_maxLifeTime)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PhysPolygon/ polygon is invalid ") + GetName());
			m_isGeoValid = false;
		}
		else
		{
			m_curLifeTime += DeltaSeconds;
			FVector curForwardDir = GetActorForwardVector();
			curForwardDir.Z = 0;
			curForwardDir.Normalize(0.1);
			FVector nextLoc = GetActorLocation() + curForwardDir * m_moveSpeed * DeltaSeconds;
			SetActorLocation(nextLoc);
			if (m_pWaitReactionGeos.Num() <= 0 || !m_pPhysCalculator) return;
			for (int32 i = 0; i < m_pWaitReactionGeos.Num(); i++)
			{
				if (m_pWaitReactionGeos[i]->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(m_pWaitReactionGeos[i]))
					continue;
				GeoReaction(m_pWaitReactionGeos[i]);
			}
			m_pWaitReactionGeos.Empty();
		}
		//m_curLifeTime = m_curLifeTime + dT;
	}

}

void APhysPoint::InitialPoint(ABaseCharacter* pHost, int32 campFlag, int32 movePertick)
{
	FVector loc = GetActorLocation();
	loc.Z = m_defaultHeight;
	SetActorLocation(loc);
	m_pHost = pHost;
	//FLogicVec2D normalDir = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(fireDir, 100);
	m_campFlag = campFlag;
	//m_curRandTarget = m_logicPos2D;
	/*int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_logicForwardDir);
	SetActorRotation(FRotator(0, yaw, 0));*/
	/*if (m_pBasicComponent)
	{
	for (int32 i = 0; i < m_attributeTags.Num(); i++)
	{
	m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
	}
	}*/
	/*if (!pHost) return;
	if (m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
	{
		if (!pHost->m_timeDilationParams.Contains(GetName())) return;
		int32 minTimeDilation = 100;
		for (TMap<FString, int32>::TConstIterator iter = pHost->m_timeDilationParams.CreateConstIterator(); iter; ++iter)
		{
			if (GetName() == iter->Key) continue;
			if (iter->Value <= minTimeDilation) minTimeDilation = iter->Value;
		}

		pHost->CustomTimeDilation = (float)minTimeDilation / 100.f;
		pHost->m_speedRatePercent = minTimeDilation;
		pHost->m_timeDilationParams.Remove(GetName());
	}*/
}

void APhysPoint::OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent)
{
	if (!m_isGeoValid || !otherActor || !otherComponent || otherActor == this) return;
	if (otherComponent->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (pGeo)
		{
			if (pGeo->m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
			{
				if (!m_timeDilationParams.Contains(GetName()))
				{
					for (int32 i = 0; i < pGeo->m_effectParamList.Num(); i++)
					{
						if (pGeo->m_effectParamList[i].effectName != "TimeDilation" ||
							(pGeo->m_effectParamList[i].effectExertType == 0 && pGeo->m_campFlag == m_campFlag)) continue;
						m_timeDilationParams.Add(pGeo->GetName(), pGeo->m_effectParamList[i].duration);
						if (CustomTimeDilation >= ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f)
							CustomTimeDilation = ((float)pGeo->m_effectParamList[i].effectValues[0]) / 100.f;
						break;
					}
				}
			}
		}
	}
	if (otherComponent->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo || !pGeo->m_isGeoValid) return;
		m_pOverlapGeos.Add(pGeo);
		if (otherComponent->ComponentHasTag(FName(TEXT("Boundary"))) || otherComponent->ComponentHasTag(FName(TEXT("BlockSkill"))))
			m_hitSolid = true;
		else
		{
			if ((m_isOneTimeReaction && m_hasTriggerReaction) || (pGeo->m_isOneTimeReaction && pGeo->m_hasTriggerReaction)) return;
			m_pWaitReactionGeos.Add(pGeo);
		}
	}
	else if (otherComponent->ComponentHasTag(FName(TEXT("DumpActor"))) && otherComponent->ComponentHasTag(FName(TEXT("Boundary")))) m_hitSolid = true;
	else if (otherComponent->ComponentHasTag(FName(TEXT("BaseCharacter"))))
	{
		ABaseCharacter* pHitCharacter = Cast<ABaseCharacter>(otherActor);
		if (!pHitCharacter || pHitCharacter->m_campFlag == m_campFlag) return;
		m_pOverlapCharacters.Add(pHitCharacter);
	}
}

void APhysPoint::OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent)
{
	if (!m_isGeoValid || !otherActor || !otherComponent) return;
	if (otherComponent->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo) return;

		//这里要将时间膨胀的顺序理清
		if (m_timeDilationParams.Contains(pGeo->GetName()))
		{
			//
			float minTimeDilation = 1.f;
			for (TMap<FString, float>::TConstIterator iter = m_timeDilationParams.CreateConstIterator(); iter; ++iter)
			{
				if (pGeo->GetName() == iter->Key) continue;
				if (iter->Value <= minTimeDilation) minTimeDilation = iter->Value;
			}
			CustomTimeDilation = minTimeDilation;
			m_timeDilationParams.Remove(pGeo->GetName());
		}

		if (m_pOverlapGeos.Contains(pGeo)) m_pOverlapGeos.Remove(pGeo);
	}
	else if (otherComponent->ComponentHasTag(FName(TEXT("BaseCharacter"))))
	{
		ABaseCharacter* pHitCharacter = Cast<ABaseCharacter>(otherActor);
		if (!pHitCharacter) return;
		if (m_pOverlapCharacters.Contains(pHitCharacter)) m_pOverlapCharacters.Remove(pHitCharacter);
	}
}

/*
void APhysPoint::SetMutationPS()
{
	if (m_enhanceType == -1) return;
	if (!m_enhancePS.Contains(m_enhanceType)) return;
	m_pMutationPSComponent->SetTemplate(m_enhancePS[m_enhanceType].pPS);
}*/

void APhysPoint::SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill)
{
	m_pBasicComponent = pComponent;
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("BasePhysGeo")));
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("PhysPoint")));
	if (IsEnermySkill) m_pBasicComponent->ComponentTags.Add(FName(TEXT("EnermySkill")));
	if (m_pBasicComponent)
	{
		for (int32 i = 0; i < m_attributeTags.Num(); i++)
		{
			if (!m_pBasicComponent->ComponentHasTag(m_attributeTags[i]))
				m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
		}
	}
}
