// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "../PhysCalculator.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "DetonationActor.h"





ADetonationActor::ADetonationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	/*m_pFixComponent = CreateDefaultSubobject<USphereComponent>(TEXT("FixComponent"));
	m_pFixComponent->SetSimulatePhysics(false);
	m_pFixComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	m_pFixComponent->bGenerateOverlapEvents = true;
	m_pFixComponent->SetSphereRadius(10);
	RootComponent = m_pFixComponent;*/
	m_physGeoType = EPhysGeoType::PGT_DetonationActor;
	//m_physActorLifeTime = 0;
	//m_isCollectable = true;
	m_pAttachEquipInfo = NULL;
}

void ADetonationActor::Tick(float DeltaSeconds)
{
	if (m_detonationState != 1) return;
	if (m_curDetonationTime >= m_detonationInfo.detonationTime)
	{
		//要爆炸了
		m_isGeoValid = false;
		UGameplayStatics::SpawnEmitterAtLocation(m_pPhysCalculator, m_pTransformPS[1], GetActorLocation(), GetActorRotation(), true);
		ABasePhysGeo* pPhysGeo = GetWorld()->SpawnActor<ABasePhysGeo>(m_mutateGeoClass, GetActorLocation(), GetActorRotation());
		if (m_pPhysCalculator)
			m_pPhysCalculator->AddPhysGeo(pPhysGeo, m_pHost, m_campFlag);
		m_detonationState = 2;
	}
	else
	{
		m_curDetonationTime += DeltaSeconds;
		UMaterialInterface* pMaterialInterface = m_pBasicSMComponent->GetMaterial(0);
		if (!pMaterialInterface) return;
		UMaterialInstanceDynamic* pMI = Cast<UMaterialInstanceDynamic>(pMaterialInterface);
		if (!pMI) return;
		float detonationIndex = m_curDetonationTime / m_detonationInfo.detonationTime;
		pMI->SetScalarParameterValue(FName("EmissionScale"), detonationIndex);
		if (m_pWaitReactionGeos.Num() <= 0 || !m_pPhysCalculator) return;
		for (int32 i = 0; i < m_pWaitReactionGeos.Num(); i++)
		{
			if (!m_pWaitReactionGeos[i] || m_pWaitReactionGeos[i]->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(m_pWaitReactionGeos[i]))
				continue;
			GeoReaction(m_pWaitReactionGeos[i]);
		}
		m_pWaitReactionGeos.Empty();
	}
}

void ADetonationActor::SetSMComponent(UStaticMeshComponent* pSMComponent)
{
	if (!pSMComponent) return;
	m_pBasicSMComponent = pSMComponent;
}

/*
void ADetonationActor::UpdateProjectileMovement(float dT)
{

}*/

void ADetonationActor::InitialDetonationActor()
{

	if (m_detonationInfo.detonationType == 0) m_detonationState = 1;
	UMaterialInstanceDynamic* pMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, m_pPhysCalculator->m_pCWSingleton->m_detonationMaterial);
	m_pBasicSMComponent->SetMaterial(0, pMI);
}

void ADetonationActor::ActivateDetonation(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (m_detonationInfo.detonationType == 0 || m_detonationState == 1) return;
	if (!otherActor || !OtherComp) return;
	//生成引爆提示特效
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			if (m_detonationInfo.detonationCharacterType == 0 && pCharacter->m_characterType == 1) m_detonationState = 1;
			else if (m_detonationInfo.detonationCharacterType == 1 && pCharacter->m_characterType == 0) m_detonationState = 1;
		}
	}
}

void ADetonationActor::OnBaseComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (otherActor && otherActor == this) return;
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			if (!m_pOverlapCharacters.Contains(pCharacter))
				m_pOverlapCharacters.Add(pCharacter);
			ActivateDetonation(otherActor, OtherComp);
		}
		if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
		{
			ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);

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

			if (!pGeo || !pGeo->m_isGeoValid || OtherComp->ComponentHasTag(FName(TEXT("PhysPolygon"))) || OtherComp->ComponentHasTag(FName(TEXT("PhysPoint")))
				|| (m_isOneTimeReaction && m_hasTriggerReaction) || (pGeo->m_isOneTimeReaction && pGeo->m_hasTriggerReaction)) return;

			m_pWaitReactionGeos.Add(pGeo);
		}
	}
}
