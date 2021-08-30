// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../PhysCalculator.h"
#include "ProjectilePoint.h"




/*
AProjectilePoint::AProjectilePoint()
{
	PrimaryActorTick.bCanEverTick = true;

	m_physGeoType = EPhysGeoType::PGT_Point;
	m_hierachy = 0;
	m_pBasicComponent = NULL;
	m_pAttachEquipInfo = NULL;
}*/

void AProjectilePoint::Tick(float DeltaSeconds)
{
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
			UpdateProjectileMovement(DeltaSeconds);

			//if (m_detonationState != 1) return;
			if (m_curDetonationTime >= m_detonationInfo.detonationTime)
			{
				//Òª±¬Õ¨ÁË
				m_isGeoValid = false;
				ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_mutateGeoClass, GetActorLocation(), GetActorRotation());
				if (m_pPhysCalculator)
					m_pPhysCalculator->AddPhysGeo(pPhysGeo, m_pHost, m_campFlag);
				if (m_pTransformPS.Contains(1) && m_pTransformPS[1])
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pTransformPS[1], GetActorLocation(), GetActorRotation());
				//m_detonationState = 2;
			}
			else
			{
				m_curDetonationTime += DeltaSeconds;

				if (m_pWaitReactionGeos.Num() <= 0 || !m_pPhysCalculator) return;
				for (int32 i = 0; i < m_pWaitReactionGeos.Num(); i++)
				{
					if (m_pWaitReactionGeos[i]->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(m_pWaitReactionGeos[i]))
						continue;
					GeoReaction(m_pWaitReactionGeos[i]);
				}
				m_pWaitReactionGeos.Empty();
			}
		}
	}
}

void AProjectilePoint::InitialProjectilePoint(const FVector& initialLoc)
{
	/*if (!m_pProjectileComponent) return;
	FVector forwardVec = GetActorForwardVector();
	forwardVec.Z = m_upliftV;
	forwardVec.Normalize(0.01);

	forwardVec = forwardVec * (float)m_moveSpeed;
	m_pProjectileComponent->Velocity = forwardVec;*/
	CalculateHorizontalVel(initialLoc);
}

void AProjectilePoint::UpdateProjectileMovement(float dT)
{
	m_upliftV = m_upliftV - dT * m_acc;
	FVector curLoc = GetActorLocation();
	curLoc.X += m_velocity.X*dT;
	curLoc.Y += m_velocity.Y*dT;
	curLoc.Z += m_upliftV * dT;
	SetActorLocation(curLoc);
}

void AProjectilePoint::CalculateHorizontalVel(FVector targetLoc)
{
	//float timeInAir = 0.f;
	m_upliftV = m_detonationInfo.detonationTime * m_acc / 2.f;
	//timeInAir = 2.f * m_upliftV / m_acc;
	FVector offset = targetLoc - GetActorLocation();
	float vx = offset.X / m_detonationInfo.detonationTime;
	float vy = offset.Y / m_detonationInfo.detonationTime;
	m_velocity.X = vx;
	m_velocity.Y = vy;
}
