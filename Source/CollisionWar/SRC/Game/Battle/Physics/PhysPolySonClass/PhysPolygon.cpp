// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "PhysPolygon.h"
#include "../../../BattleLevelGameModeBase.h"
#include "../PhysActorSonClass/BasePhysActor.h"

// Sets default values
APhysPolygon::APhysPolygon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_physGeoType = EPhysGeoType::PGT_Poly;
	m_pFixComponent = CreateDefaultSubobject<USphereComponent>(TEXT("FixComponent"));
	m_pFixComponent->SetSimulatePhysics(false);
	m_pFixComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	m_pFixComponent->bGenerateOverlapEvents = true;
	m_pFixComponent->SetSphereRadius(10);
	RootComponent = m_pFixComponent;
	//m_isGeoValid = true;
	m_hierachy = 0;
	m_maxLifeTime = 0;
	m_pHost = NULL;
	m_campFlag = 0;
	m_pAttachEquipInfo = NULL;
}

// Called when the game starts or when spawned
void APhysPolygon::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, m_pSpawnSound, GetActorLocation());
}

void APhysPolygon::Tick(float DeltaSeconds)
{
	if (!m_isGeoValid) return;

	//进行状态更新
	if (m_moveType == 1 && m_pHost)
	{
		SetActorLocation(m_pHost->GetActorLocation());
		SetActorRotation(m_pHost->GetActorRotation());
	}

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
			if (m_pWaitReactionGeos.Num() <= 0 || !m_pPhysCalculator) return;
			for (int32 i=0; i<m_pWaitReactionGeos.Num(); i++)
			{
				if (m_pWaitReactionGeos[i]->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(m_pWaitReactionGeos[i]))
					continue;
				GeoReaction(m_pWaitReactionGeos[i]);
			}
			m_pWaitReactionGeos.Empty();
			/*GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PhysPolygon/ polygon ") + GetName() + TEXT(" now tick is: ")
			+ FString::FromInt(m_curLogicLifeTime));*/
		}
		//m_curLifeTime = m_curLifeTime + dT;
	}

}

void APhysPolygon::OnShapeComponentBeginOverlap(class AActor* otherActor, class UPrimitiveComponent* OtherComp)
{
	if (otherActor && otherActor == this) return;
	if (OtherComp)
	{
		if (OtherComp->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
			if (!pCharacter) return;
			m_pOverlapCharacters.Add(pCharacter);
		}
		else if (OtherComp->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
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

			if (!pGeo || !pGeo->m_isGeoValid || OtherComp->ComponentHasTag(FName(TEXT("PhysPoint"))) || (m_isOneTimeReaction && m_hasTriggerReaction) || (pGeo->m_isOneTimeReaction && pGeo->m_hasTriggerReaction)) return;
			m_pOverlapGeos.Add(pGeo);
			m_pWaitReactionGeos.Add(pGeo);
		}
		/*else if (OtherComp->ComponentHasTag(FName(TEXT("DumpActor"))))
		{
			ADumpPhysActor* pGeo = Cast<ADumpPhysActor>(otherActor);
			if (m_pBasicComponent->ComponentHasTag(FName(TEXT("TimeDilation"))))
			{
				if (!pGeo->m_timeDilationParams.Contains(this))
				{
					for (int32 i = 0; i < m_effectParamList.Num(); i++)
					{
						if (m_effectParamList[i].effectName != "TimeDilation") continue;
						pGeo->m_timeDilationParams.Add(this, m_effectParamList[i].duration);
						if (pGeo->CustomTimeDilation >= m_effectParamList[i].effectValues[0])
							pGeo->CustomTimeDilation = m_effectParamList[i].effectValues[0];
						break;
					}
				}
			}
		}*/
	}
}

void APhysPolygon::OnShapeComponentEndOverlap(class AActor* otherActor, class UPrimitiveComponent* otherComponent)
{
	if (!m_isGeoValid || !otherActor || !otherComponent) return;
	if (otherComponent->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
	{
		ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(otherActor);
		if (!pGeo) return;
		if (m_pOverlapGeos.Contains(pGeo))
		{
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
			m_pOverlapGeos.Remove(pGeo);
		}
	}
	else if (otherComponent->ComponentHasTag(FName(TEXT("BaseCharacter"))))
	{
		ABaseCharacter* pCharacter = Cast<ABaseCharacter>(otherActor);
		if (!pCharacter) return;
		if (m_pOverlapCharacters.Contains(pCharacter)) m_pOverlapCharacters.Remove(pCharacter);
	}
}

void APhysPolygon::InitialPolygon(ABaseCharacter* pHost, int32 campFlag, int32 defaultHeight)
{
	//InitialPolygon主要用途是对fixPts、host、campFlag、attachEquipInfo赋值
	//hierachy、rootGeos、sonGeos、reactionInfos、preOverlapGeos、overlapCharacters在实际运算或校正时才会进行修改
	/*UCollisionWarBpFunctionLibrary::SortPointsClockwise_Int(m_relativeLogicFixPts);
	int32 angle = 0;
	int32 cosAngle = UCollisionWarBpFunctionLibrary::GetExpandCosAngleOfTwoVector_Int(m_logicForwardDir, FLogicVec2D(1, 0));
	if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), FLogicVec2D(1, 0), m_logicForwardDir) >= 0)
		angle = UCollisionWarBpFunctionLibrary::LogicACos(cosAngle);
	else angle = -UCollisionWarBpFunctionLibrary::LogicACos(cosAngle);
	for (int32 i = 0; i<m_relativeLogicFixPts.Num(); i++)
	{
		FLogicVec2D modifyRelativeFixPtLoc = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_relativeLogicFixPts[i], FLogicVec2D(0, 0), -angle);
		FLogicVec2D fixPt = m_logicPos2D + modifyRelativeFixPtLoc;
		m_logicFixPts.Add(fixPt);
	}*/
	/*if (m_pBasicComponent)
	{
	for (int32 i = 0; i < m_attributeTags.Num(); i++)
	{
	m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
	}
	}*/
	m_defaultHeight = defaultHeight;
	m_pHost = pHost;
	m_campFlag = campFlag;

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
	//m_curRandTarget = m_logicPos2D;
}

void APhysPolygon::UpdatePolygon()
{
	
	
	//对每个poly点进行位置更新
	/*int32 yawAngle = 0;
	int32 cosAlpha = UCollisionWarBpFunctionLibrary::GetExpandCosAngleOfTwoVector_Int(m_logicForwardDir, FLogicVec2D(1, 0));
	if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), FLogicVec2D(1, 0), m_logicForwardDir) >= 0)
		yawAngle = UCollisionWarBpFunctionLibrary::LogicACos(cosAlpha);
	else yawAngle = -UCollisionWarBpFunctionLibrary::LogicACos(cosAlpha);
	for (int32 i = 0; i<m_logicFixPts.Num(); i++)
	{
		FLogicVec2D modifyRelativeFixPtLoc = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_relativeLogicFixPts[i], FLogicVec2D(0, 0), -yawAngle);
		m_logicFixPts[i] = m_logicPos2D + modifyRelativeFixPtLoc;
	}*/
}


/*
void APhysPolygon::SetMutationPS()
{
	if (m_enhanceType == -1) return;
	if (!m_enhancePS.Contains(m_enhanceType)) return;
	m_pMutationPSComponent->SetTemplate(m_enhancePS[m_enhanceType].pPS);
}*/

void APhysPolygon::SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySpawnPolygon)
{
	if (!pComponent) return;
	m_pBasicComponent = pComponent;
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("BasePhysGeo")));
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("PhysPolygon")));
	if (IsEnermySpawnPolygon) m_pBasicComponent->ComponentTags.Add(FName(TEXT("EnermySkill")));
	if (m_pBasicComponent)
	{
		for (int32 i = 0; i < m_attributeTags.Num(); i++)
		{
			if (!m_pBasicComponent->ComponentHasTag(m_attributeTags[i]))
				m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
		}
	}
	/*m_relativeLogicFixPts.Empty();
	if (pComponent->GetClass() == UBoxComponent::StaticClass())
	{
		UBoxComponent* pBoxComponent = Cast<UBoxComponent>(pComponent);
		if (!pBoxComponent) return;
		int32 x = FMath::FloorToInt(pBoxComponent->GetScaledBoxExtent().X);
		int32 y = FMath::FloorToInt(pBoxComponent->GetScaledBoxExtent().Y);
		FLogicVec2D pt1 = FLogicVec2D(x + m_relativeLocation.X, y + m_relativeLocation.Y);
		FLogicVec2D pt2 = FLogicVec2D(m_relativeLocation.X - x, y + m_relativeLocation.Y);
		FLogicVec2D pt3 = FLogicVec2D(m_relativeLocation.X - x, m_relativeLocation.Y - y);
		FLogicVec2D pt4 = FLogicVec2D(m_relativeLocation.X + x, m_relativeLocation.Y - y);
		m_relativeLogicFixPts.Add(pt1);
		m_relativeLogicFixPts.Add(pt2);
		m_relativeLogicFixPts.Add(pt3);
		m_relativeLogicFixPts.Add(pt4);
	}
	else if (pComponent->GetClass() == UCapsuleComponent::StaticClass())
	{
		UCapsuleComponent* pCapsuleComponent = Cast<UCapsuleComponent>(pComponent);
		if (!pCapsuleComponent) return;
		int32 radius = pCapsuleComponent->GetScaledCapsuleRadius();
		FLogicVec2D pt1 = FLogicVec2D(m_relativeLocation.X + radius, m_relativeLocation.Y);
		FLogicVec2D pt2 = FLogicVec2D(m_relativeLocation.X + radius * 71 / 100, m_relativeLocation.Y + radius * 71 / 100);
		FLogicVec2D pt3 = FLogicVec2D(m_relativeLocation.X, m_relativeLocation.Y + radius);
		FLogicVec2D pt4 = FLogicVec2D(m_relativeLocation.X - radius * 71 / 100, m_relativeLocation.Y + radius * 71 / 100);
		FLogicVec2D pt5 = FLogicVec2D(m_relativeLocation.X - radius, m_relativeLocation.Y);
		FLogicVec2D pt6 = FLogicVec2D(m_relativeLocation.X - radius * 71 / 100, m_relativeLocation.Y - radius * 71 / 100);
		FLogicVec2D pt7 = FLogicVec2D(m_relativeLocation.X, m_relativeLocation.Y -radius);
		FLogicVec2D pt8 = FLogicVec2D(m_relativeLocation.X + radius * 71 / 100, m_relativeLocation.Y - radius * 71 / 100);
		m_relativeLogicFixPts.Add(pt1);
		m_relativeLogicFixPts.Add(pt2);
		m_relativeLogicFixPts.Add(pt3);
		m_relativeLogicFixPts.Add(pt4);
		m_relativeLogicFixPts.Add(pt5);
		m_relativeLogicFixPts.Add(pt6);
		m_relativeLogicFixPts.Add(pt7);
		m_relativeLogicFixPts.Add(pt8);
	}
	else if (pComponent->GetClass() == USphereComponent::StaticClass())
	{
		USphereComponent* pSphereComponent = Cast<USphereComponent>(pComponent);
		if (!pSphereComponent) return;
		int32 radius = pSphereComponent->GetScaledSphereRadius();
		FLogicVec2D pt1 = FLogicVec2D(m_relativeLocation.X + radius, m_relativeLocation.Y);
		FLogicVec2D pt2 = FLogicVec2D(m_relativeLocation.X + radius * 71 / 100, m_relativeLocation.Y + radius * 71 / 100);
		FLogicVec2D pt3 = FLogicVec2D(m_relativeLocation.X, m_relativeLocation.Y + radius);
		FLogicVec2D pt4 = FLogicVec2D(m_relativeLocation.X - radius * 71 / 100, m_relativeLocation.Y + radius * 71 / 100);
		FLogicVec2D pt5 = FLogicVec2D(m_relativeLocation.X - radius, m_relativeLocation.Y);
		FLogicVec2D pt6 = FLogicVec2D(m_relativeLocation.X - radius * 71 / 100, m_relativeLocation.Y - radius * 71 / 100);
		FLogicVec2D pt7 = FLogicVec2D(m_relativeLocation.X, m_relativeLocation.Y - radius);
		FLogicVec2D pt8 = FLogicVec2D(m_relativeLocation.X + radius * 71 / 100, m_relativeLocation.Y - radius * 71 / 100);
		m_relativeLogicFixPts.Add(pt1);
		m_relativeLogicFixPts.Add(pt2);
		m_relativeLogicFixPts.Add(pt3);
		m_relativeLogicFixPts.Add(pt4);
		m_relativeLogicFixPts.Add(pt5);
		m_relativeLogicFixPts.Add(pt6);
		m_relativeLogicFixPts.Add(pt7);
		m_relativeLogicFixPts.Add(pt8);
	}*/
}

