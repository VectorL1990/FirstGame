// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "PhysLine.h"
#include "../../../BattleLevelGameModeBase.h"

// Sets default values
APhysLine::APhysLine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_physGeoType = EPhysGeoType::PGT_Line;
	m_pFixComponent = CreateDefaultSubobject<USphereComponent>(TEXT("FixComponent"));
	m_pFixComponent->SetSimulatePhysics(false);
	m_pFixComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	m_pFixComponent->bGenerateOverlapEvents = true;
	m_pFixComponent->SetSphereRadius(10);
	RootComponent = m_pFixComponent;
	m_isGeoValid = true;
	m_pBasicComponent = NULL;
	m_pHost = NULL;
	m_campFlag = 0;
	m_isFixFlag = false;
	m_hasBroadcastDeleteFlag = false;
	m_pAttachEquipInfo = NULL;
}

// Called when the game starts or when spawned
void APhysLine::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
/*
void APhysLine::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);
if (m_hasBroadcastDeleteFlag) return;
if (!m_isGeoValid)
{
for (int32 i=0; i<m_pSonGeos.Num(); i++)
{
m_pSonGeos[i]->m_isGeoValid = false;
}
m_geoDeleteDelegate.Broadcast(this);
m_hasBroadcastDeleteFlag = true;
}
else
{
UpdateLine();
}
if (!m_pBasicComponent->ComponentHasTag(m_dependentTag)) m_isGeoValid = false;
}*/

void APhysLine::SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill)
{
	m_pBasicComponent = pComponent;
	if (!m_pBasicComponent) return;
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("BasePhysGeo")));
	m_pBasicComponent->ComponentTags.Add(FName(TEXT("PhysLine")));
	if (m_pBasicComponent)
	{
		for (int32 i = 0; i < m_attributeTags.Num(); i++)
		{
			if (!m_pBasicComponent->ComponentHasTag(m_attributeTags[i]))
				m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
		}
	}
}

void APhysLine::LineTraceHitDetect_Int()
{
	/*if (!m_isGeoValid || !m_isInitial) return;
	FVector startPoint(m_logicStartPoint.X, m_logicStartPoint.Y, m_defaultHeight + m_relativeHeight);
	FVector2D lineDelta(m_logicEndPoint.X - m_logicStartPoint.X, m_logicEndPoint.Y - m_logicStartPoint.Y);
	lineDelta.Normalize();
	FVector lineTraceEndPt = startPoint + FVector(lineDelta.X, lineDelta.Y, 0)*(m_logicLineLength + 10);
	TArray<FHitResult> hitResults;
	FCollisionResponseParams responseParams;
	responseParams.CollisionResponse.SetAllChannels(ECR_Overlap);
	GetWorld()->SweepMultiByChannel(hitResults, startPoint, lineTraceEndPt, FQuat::Identity, COLLISION_OBSTACLE_FINDING,
		FCollisionShape::MakeSphere(5), FCollisionQueryParams::DefaultQueryParam, responseParams);
	bool hitSolidFlag = false;
	TArray<ABasePhysGeo*> pOverlapGeos;

	for (int32 i = 0; i<hitResults.Num(); i++)
	{
		if (hitResults[i].GetActor() == this || !hitResults[i].GetActor()) continue;
		if (!hitResults[i].GetComponent()) continue;
		if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysGeo"))))
		{
			ABasePhysGeo* pGeo = Cast<ABasePhysGeo>(hitResults[i].GetActor());
			if (!pGeo || hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysPoint")))) continue;
			if (pGeo->m_pRootGeos.Contains(this) || m_pRootGeos.Contains(pGeo)) continue;
			if (!pGeo->m_isInitial) continue;
			//BroadcastAddReactionPair(pGeo);
			bool isIntercept = false;
			if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("PhysPolygon"))))
			{
				APhysPolygon* pPolygon = Cast<APhysPolygon>(hitResults[i].GetActor());
				if (m_pRootGeos.Contains(pPolygon)) continue;
				if (!UCollisionWarBpFunctionLibrary::IsLinePolyIntercept(m_logicStartPoint, m_logicEndPoint, pPolygon->m_logicFixPts, m_errorTolerance))
					continue;
				isIntercept = true;
				for (int32 j = 0; j < m_reactionInfos.Num(); j++)
				{
					if (hitResults[i].GetComponent()->ComponentHasTag(m_reactionInfos[j].reactionTag) &&
						m_reactionInfos[j].reactionType == EReactionType::PRT_ReflectRefract && m_hierachy < 1)
					{
						if (pPolygon->m_level < m_level) break;
						FLogicVec2D interPt;
						FLogicVec2D reflectDir2D;
						if (!GetHitPointWithPolygon_Int(pPolygon, interPt, reflectDir2D)) break;
						hitSolidFlag = CutLine_Int(this, pPolygon, interPt, reflectDir2D, hitResults[i].GetComponent(), m_reactionInfos[j]);
						break;
					}
					else if ((hitResults[i].GetComponent()->ComponentHasTag(m_reactionInfos[j].reactionTag) &&
						m_reactionInfos[j].reactionType == EReactionType::PRT_BlockLine) ||
						(hitResults[i].GetComponent()->ComponentHasTag(m_reactionInfos[j].reactionTag) &&
							m_reactionInfos[j].reactionType == EReactionType::PRT_ReflectRefract && m_hierachy >= 1))
					{
						if (pPolygon->m_level < m_level) break;
						FLogicVec2D interPt;
						FLogicVec2D reflectDir2D;
						if (!GetHitPointWithPolygon_Int(pPolygon, interPt, reflectDir2D)) break;
						BlockLine_Int(this, pPolygon, interPt, hitResults[i].GetComponent(), m_reactionInfos[j]);
						hitSolidFlag = true;
						break;
					}
				}
			}
			else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BasePhysActor"))))
			{
				ABasePhysActor* pActor = Cast<ABasePhysActor>(hitResults[i].GetActor());
				if (!pActor->m_isGeoValid) continue;
				if (m_pRootGeos.Contains(pActor)) continue;
				if (!UCollisionWarBpFunctionLibrary::IsLineActorIntercept(m_logicStartPoint, m_logicEndPoint, pActor->m_logicPos2D, pActor->m_actorRadius, m_errorTolerance)) continue;
				isIntercept = true;
				for (int32 j = 0; j < m_reactionInfos.Num(); j++)
				{
					if ((hitResults[i].GetComponent()->ComponentHasTag(m_reactionInfos[j].reactionTag) &&
						m_reactionInfos[j].reactionType == EReactionType::PRT_BlockLine) ||
						(hitResults[i].GetComponent()->ComponentHasTag(m_reactionInfos[j].reactionTag) &&
							m_reactionInfos[j].reactionType == EReactionType::PRT_ReflectRefract && m_hierachy >= 1))
					{
						if (pActor->m_level < m_level) break;
						BlockLine_Int(this, pActor, pActor->m_logicPos2D, hitResults[i].GetComponent(), m_reactionInfos[j]);
						hitSolidFlag = true;
						break;
					}
				}
			}

			if (isIntercept)
			{
				pOverlapGeos.Add(pGeo);
				if (!m_pOverlapGeos.Contains(pGeo))
				{
					m_pOverlapGeos.Add(pGeo);
					AddPreOverlapGeoPair(pGeo);
				}
			}
		}
		else if (hitResults[i].GetComponent()->ComponentHasTag(FName(TEXT("BaseCharacter"))))
		{
			ABaseCharacter* pHitCharacter = Cast<ABaseCharacter>(hitResults[i].GetActor());
			if (!UCollisionWarBpFunctionLibrary::IsLineActorIntercept(m_logicStartPoint, m_logicEndPoint, pHitCharacter->m_logicPos2D, pHitCharacter->m_characterRadius, m_errorTolerance))
				break;
			if (pHitCharacter->m_campFlag != m_campFlag) GeoHitCharacter(pHitCharacter);
			FReactionInfo emptyReactionInfo;
			BlockLine_Int(this, NULL, pHitCharacter->m_logicPos2D, hitResults[i].GetComponent(), emptyReactionInfo);
			m_pHitCharacter = pHitCharacter;
			hitSolidFlag = true;
		}
		if (hitSolidFlag) break;
	}

	int32 i = 0;
	while (i < m_pOverlapGeos.Num())
	{
		if (pOverlapGeos.Contains(m_pOverlapGeos[i]))
		{
			i += 1;
			continue;
		}
		m_seperatePairs.Add(FPreReactionPair(m_entityID, m_pOverlapGeos[i]->m_entityID));
		m_pOverlapGeos.RemoveAt(i);
	}

	if (!hitSolidFlag)
	{
		if (m_preHitComponentName != TEXT("NULL")) m_preHitComponentName = TEXT("NULL");
		//if (m_preHitGeoID != -1) m_seperatePairs.Add(FPreReactionPair(m_entityID, m_preHitGeoID));
		m_preHitGeoID = -1;
		m_preHitActorName = TEXT("NULL");
		m_pHitCharacter = NULL;
		//m_logicCutLength = m_logicLineLength;
	}*/
}

bool APhysLine::IsLineLineIntercept(const FLogicVec2D& ownStartPoint, const FLogicVec2D& ownEndPoint, const FLogicVec2D& oppStartPoint, const FLogicVec2D& oppEndPoint)
{
	/*if (UCollisionWarBpFunctionLibrary::IsSegmentsIntersect_Int(ownStartPoint, ownEndPoint, oppStartPoint, oppEndPoint))
	{
	int32 dis1 = UCollisionWarBpFunctionLibrary::GetDisOfPointToLine_Int(ownStartPoint, ownEndPoint, oppStartPoint);
	int32 dis2 = UCollisionWarBpFunctionLibrary::GetDisOfPointToLine_Int(ownStartPoint, ownEndPoint, oppEndPoint);
	if (dis1 <= m_errorTolerance || dis2 <= m_errorTolerance) return false;
	else return true;
	}
	return false;*/
	if (UCollisionWarBpFunctionLibrary::IsSegmentsIntersect_Int(ownStartPoint, ownEndPoint, oppStartPoint, oppEndPoint))
		return true;
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("PhysLine::IsLineLineIntercept  line line intercept no!!!"));
		return false;
	}
}

void APhysLine::RefreshLine_Int(FLogicVec2D dir, FLogicVec2D startPt, int32 lineLength)
{
	/*m_logicPos2D = startPt;
	m_logicStartPoint = startPt;
	m_logicForwardDir = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(dir, 100);
	//m_lineDir.Normalize();
	FVector newPos(m_logicStartPoint.X, m_logicStartPoint.Y, m_defaultHeight + m_relativeHeight);
	SetActorLocation(newPos);
	FVector newDir(m_logicForwardDir.X, m_logicForwardDir.Y, 0);
	SetActorRotation(newDir.ToOrientationRotator());
	if (UCollisionWarBpFunctionLibrary::GetLogicVecSize(dir) == 0) m_logicLineLength = 0;
	else m_logicLineLength = lineLength;*/
}

void APhysLine::TickLine()
{
	/*if (!m_isGeoValid)
	{
		for (int32 i = 0; i < m_pSonGeos.Num(); i++)
		{
			if (!m_pSonGeos[i]) continue;
			m_pSonGeos[i]->m_isGeoValid = false;
		}
	}
	else
	{
		int32 i = 0;
		while (i < m_pSonGeos.Num())
		{
			if (!m_pSonGeos[i])
			{
				m_pSonGeos.RemoveAt(i);
				continue;
			}
			i++;
		}
		UpdateLine_Int();
		if (m_pBasicComponent && !m_pBasicComponent->ComponentHasTag(m_dependentTag) && m_dependentTag != FName(TEXT("None")))
			m_isGeoValid = false;
	}*/
}

void APhysLine::InitialLine(FLogicVec2D fixLoc, ABaseCharacter* pHost, int32 campFlag, FLogicVec2D dir, int32 lineHeight)
{
	m_defaultHeight = lineHeight;
	m_logicCutLength = m_logicLineLength;
	FVector spawnLoc(fixLoc.X, fixLoc.Y, m_defaultHeight + m_relativeHeight);
	SetActorLocation(spawnLoc);
	m_pHost = pHost;
	m_campFlag = campFlag;
	//m_logicForwardDir = dir;
	//m_curRandTarget = m_logicPos2D;
	SetActorRotation(m_pHost->GetActorRotation());
	/*if (m_pBasicComponent)
	{
	for (int32 i = 0; i < m_attributeTags.Num(); i++)
	{
	m_pBasicComponent->ComponentTags.Add(m_attributeTags[i]);
	}
	}*/
}

void APhysLine::UpdateLine_Int()
{
	/*if (m_moveType == 1)
	{
		if (m_pHost)
		{
			FLogicVec2D spawnPoint = m_pHost->m_logicSpawnPoint;
			m_logicPos2D = spawnPoint;
			m_logicStartPoint = spawnPoint;
			FVector newPos(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight);
			SetActorLocation(newPos);
			m_logicForwardDir = m_pHost->m_curLogicForwardDir;
			SetActorRotation(m_pHost->GetActorRotation());
		}
	}
	else if (m_moveType == 2)
	{
		if (m_curMovePointNb < m_moveOrder.Num())
		{
			FLogicVec2D curMoveTarget = m_moveOrder[m_curMovePointNb];
			FLogicVec2D offset = curMoveTarget - m_logicPos2D;
			int32 offsetSize = UCollisionWarBpFunctionLibrary::GetLogicVecSize(offset);
			if (offsetSize <= 10)
			{
				//说明已到达终点，需要切换到下一目标点
				m_curMovePointNb += 1;
				if (m_curMovePointNb >= m_moveOrder.Num()) m_curMovePointNb = 0;
			}
			FLogicVec2D moveDir = m_moveOrder[m_curMovePointNb] - m_logicPos2D;
			FLogicVec2D normalizeDir = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(moveDir, 100);
			FLogicVec2D moveOffset = normalizeDir * m_moveSpeed / 100;
			m_logicPos2D = m_logicPos2D + moveOffset;
			m_logicStartPoint = m_logicPos2D;
			FVector pos(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight);
			SetActorLocation(pos);
		}

		if (m_curRotateNb < m_rotateOrder.Num())
		{
			FLogicVec2D targetDir = UCollisionWarBpFunctionLibrary::GetLogicVecByYaw_Int(m_rotateOrder[m_curRotateNb]);
			if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), targetDir, m_logicForwardDir) > 0)
			{
				//说明当前方向转到目标方向在现实世界的坐标中为顺时针
				FLogicVec2D predictDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicForwardDir, FLogicVec2D(0, 0), -m_rotateSpeed);
				if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), targetDir, predictDir) <= 0)
				{
					m_logicForwardDir = targetDir;
					m_curRotateNb += 1;
					if (m_curRotateNb >= m_rotateOrder.Num()) m_curRotateNb = 0;
				}
				else m_logicForwardDir = predictDir;
			}
			else
			{
				FLogicVec2D predictDir = UCollisionWarBpFunctionLibrary::GetPtRotateAroundPtByAlpha_Int(m_logicForwardDir, FLogicVec2D(0, 0), m_rotateSpeed);
				if (UCollisionWarBpFunctionLibrary::GetDirectionOfPointToSegment_Int(FLogicVec2D(0, 0), targetDir, predictDir) >= 0)
				{
					m_logicForwardDir = targetDir;
					m_curRotateNb += 1;
					if (m_curRotateNb >= m_rotateOrder.Num()) m_curRotateNb = 0;
				}
				else m_logicForwardDir = predictDir;
			}
			int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_logicForwardDir);
			SetActorRotation(FRotator(0, yaw, 0));
		}
	}
	else if (m_moveType == 3)
	{
		FLogicVec2D offset = m_curRandTarget - m_logicPos2D;
		int32 offsetSize = UCollisionWarBpFunctionLibrary::GetLogicVecSize(offset);
		if (offsetSize <= 10)
		{
			//说明已到达随机点，需要重新生成随机点并设定为目标点
			AGameModeBase* pGameMode = UGameplayStatics::GetGameMode(GetWorld());
			ABattleLevelGameModeBase* pCWGameMode = Cast<ABattleLevelGameModeBase>(pGameMode);
			int32 randX = pCWGameMode->GenRandNumber(pCWGameMode->m_randXMin, pCWGameMode->m_randXMax);
			int32 randY = pCWGameMode->GenRandNumber(pCWGameMode->m_randYMin, pCWGameMode->m_randYMax);
			m_curRandTarget.X = randX;
			m_curRandTarget.Y = randY;
		}
		FLogicVec2D moveDir = m_curRandTarget - m_logicPos2D;
		FLogicVec2D normalizeDir = UCollisionWarBpFunctionLibrary::NormalizeLogicVecToPositiveScale(moveDir, 100);
		FLogicVec2D moveOffset = normalizeDir * m_moveSpeed / 100;
		m_logicPos2D = m_logicPos2D + moveOffset;
		FVector pos(m_logicPos2D.X, m_logicPos2D.Y, m_defaultHeight + m_relativeHeight);
		SetActorLocation(pos);
	}
	m_logicEndPoint = m_logicStartPoint + m_logicForwardDir * m_logicLineLength / 100;
	//DrawDebugPoint(GetWorld(), pos, 20, FColor::Green, false, 0.1);
	int32 i = 0;
	while (i < m_pSonGeos.Num())
	{
		if (!m_pSonGeos[i]) m_pSonGeos.RemoveAt(i);
		else i = i + 1;
	}

	i = 0;
	while (i < m_pSecondarySonGeos.Num())
	{
		if (!m_pSecondarySonGeos[i]) m_pSecondarySonGeos.RemoveAt(i);
		else i = i + 1;
	}

	UBoxComponent* pBoxComponent = Cast<UBoxComponent>(m_pBasicComponent);
	FVector newBoxExtent = pBoxComponent->GetScaledBoxExtent();
	newBoxExtent.X = m_logicLineLength / 2;
	int32 yaw = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(m_logicForwardDir);
	pBoxComponent->SetWorldRotation(FRotator(0, yaw, 0));
	FLogicVec2D newLoc = (m_logicStartPoint + m_logicEndPoint) / 2;
	pBoxComponent->SetWorldLocation(FVector(newLoc.X, newLoc.Y, m_defaultHeight + m_relativeHeight));
	pBoxComponent->SetBoxExtent(newBoxExtent);

	LineTraceHitDetect_Int();
	//这段代码只是为了绘制line，所以用浮点数没问题
	FVector newWorldLoc;
	FRotator newWorldRot;
	FVector drawStartPoint(m_logicStartPoint.X, m_logicStartPoint.Y, m_defaultHeight + m_relativeHeight);
	FVector drawEndPoint(m_logicEndPoint.X, m_logicEndPoint.Y, m_defaultHeight + m_relativeHeight);
	DrawDebugLine(GetWorld(), drawStartPoint, drawEndPoint, FColor::Black, false, 0.1, 0, 10);*/

}

bool APhysLine::CutLine_Int(APhysLine* pLine, ABasePhysGeo* pCutGeo, FLogicVec2D interPt, FLogicVec2D reflectRefractDir2D, UPrimitiveComponent* pHitComponent, FReactionInfo reactionInfo)
{
	//DrawDebugPoint(GetWorld(), FVector(interPt.X, interPt.Y, m_defaultHeight), 10, FColor::Red, false, 0.1);
	/*pLine->m_logicEndPoint.X = interPt.X;
	pLine->m_logicEndPoint.Y = interPt.Y;
	FString hitComponentName = pHitComponent->GetName();
	FString hitActorName = pCutGeo->GetName();
	if (hitComponentName == pLine->m_preHitComponentName && hitActorName == pLine->m_preHitActorName)
	{
		FLogicVec2D refreshPt(interPt.X, interPt.Y);
		for (int32 k = 0; k < pLine->m_pSonGeos.Num(); k++)
		{
			if (!m_pSonGeos[k]) continue;
			if (pLine->m_pSonGeos[k]->m_physGeoType == EPhysGeoType::PGT_Line)
			{
				APhysLine* pSonLine = Cast<APhysLine>(pLine->m_pSonGeos[k]);
				FLogicVec2D offset = pLine->m_logicEndPoint - pLine->m_logicStartPoint;
				int32 trunckLength = pLine->m_logicLineLength - UCollisionWarBpFunctionLibrary::GetLogicVecSize(offset);
				pSonLine->RefreshLine_Int(reflectRefractDir2D, refreshPt, trunckLength);
			}
			else
			{
				pLine->m_pSonGeos[k]->m_logicPos2D = refreshPt;
				FVector newPos(refreshPt.X, refreshPt.Y, m_defaultHeight + m_relativeHeight);
				pLine->m_pSonGeos[k]->SetActorLocation(newPos);
			}
		}
	}
	else
	{
		//if (pLine->m_pPreHitComponent) pLine->m_geoSeperationDelegate.Broadcast(pLine, pLine->m_pPreHitComponent->GetOwner());
		//告诉PhysCalculator两个物体seperate了
		//if (m_preHitGeoID != -1) m_seperatePairs.Add(FPreReactionPair(pLine->m_entityID, m_preHitGeoID));
		//pLine->AddPreOverlapGeoPair(pCutGeo);
		pLine->m_preHitGeoID = pCutGeo->m_entityID;
		pLine->m_preHitComponentName = hitComponentName;
		pLine->m_preHitActorName = hitActorName;
		pLine->m_pHitCharacter = NULL;
		FLogicVec3D hitPoint(interPt.X, interPt.Y, m_defaultHeight + m_relativeHeight);
		FReactionSpawnPair reactionSpawnPair(pLine->m_entityID, pCutGeo->m_entityID, hitPoint, reflectRefractDir2D, reactionInfo, m_campFlag);
		m_reactionSpawnPairs.Add(reactionSpawnPair);
	}*/
	return true;
}

void APhysLine::BlockLine_Int(APhysLine* pLine, ABasePhysGeo* pBlockGeo, FLogicVec2D interPt, UPrimitiveComponent* pHitComponent, FReactionInfo reactionInfo)
{
	/*pLine->m_logicEndPoint.X = interPt.X;
	pLine->m_logicEndPoint.Y = interPt.Y;
	FString hitComponentName = pHitComponent->GetName();
	FString hitActorName = "NULL";
	if (pBlockGeo) hitActorName = pBlockGeo->GetName();
	else hitActorName = pHitComponent->GetOwner()->GetName();
	if (hitComponentName == pLine->m_preHitComponentName && hitActorName == pLine->m_preHitActorName)
	{
		for (int32 k = 0; k < pLine->m_pSonGeos.Num(); k++)
		{
			if (!pLine->m_pSonGeos[k]) continue;
			if (pLine->m_pSonGeos[k]->m_physGeoType == EPhysGeoType::PGT_Line) pLine->m_pSonGeos[k]->m_isGeoValid = false;
			else
			{
				pLine->m_pSonGeos[k]->m_logicPos2D = m_logicEndPoint;
				FVector newPos(m_logicEndPoint.X, m_logicEndPoint.Y, m_defaultHeight + m_relativeHeight);
				pLine->m_pSonGeos[k]->SetActorLocation(newPos);
			}
		}
	}
	else
	{
		//if (m_preHitGeoID != -1) m_seperatePairs.Add(FPreReactionPair(pLine->m_entityID, m_preHitGeoID));
		if (!pBlockGeo) return;
		//pLine->AddPreOverlapGeoPair(pBlockGeo);
		pLine->m_preHitGeoID = pBlockGeo->m_entityID;
		pLine->m_preHitComponentName = hitComponentName;
		pLine->m_preHitActorName = hitActorName;
		pLine->m_pHitCharacter = NULL;
	}*/
}



