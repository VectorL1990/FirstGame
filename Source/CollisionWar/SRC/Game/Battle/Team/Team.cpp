// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "Team.h"

// Sets default values
ATeam::ATeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATeam::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeam::SortCharacterCW(TArray<int32> posList, int32 pos, int32 maxPos, int32 preDifPos, int32& returnPos, int32& difPos)
{
	if (posList.Contains(pos))
	{
		pos += 1;
		preDifPos += 1;
		if (pos > maxPos) pos = 0;
		SortCharacterCW(posList, pos, maxPos, preDifPos, returnPos, difPos);
	}
	else
	{
		returnPos = pos;
		difPos = preDifPos;
	}
}

void ATeam::SortCharacterCCW(TArray<int32> posList, int32 pos, int32 maxPos, int32 preDifPos, int32& returnPos, int32& difPos)
{
	if (posList.Contains(pos))
	{
		pos -= 1;
		preDifPos += 1;
		if (pos < 0) pos = maxPos;
		SortCharacterCCW(posList, pos, maxPos, preDifPos, returnPos, difPos);
	}
	else
	{
		returnPos = pos;
		difPos = preDifPos;
	}
}

void ATeam::CharactersFormation()
{
	for (int32 i=0; i<m_pMarchSquads.Num(); i++)
	{
		if (!m_pMarchSquads[i]->IsValidLowLevel()) continue;
		m_pMarchSquads[i]->ConditionalBeginDestroy();
	}
	m_pMarchSquads.Empty();
	for (int32 i=0; i<m_pCharacters.Num(); i++)
	{
		if (m_pCharacters[i]->m_characterType == 1 || m_pCharacters[i]->m_characterType == 2 || !m_pCharacters[i]->m_pNormalLongTask ||
			!m_pCharacters[i]->m_pNormalLongTask->m_pTarget || m_pCharacters[i]->m_pNormalLongTask->m_taskType != ETaskType::TT_ChaseEnermy)
			continue;

		int32 foundMarchSquadNb = -1;
		for (int32 j=0; j<m_pMarchSquads.Num(); j++)
		{
			if (m_pMarchSquads[j]->m_pTarget == m_pCharacters[i]->m_pNormalLongTask->m_pTarget &&
				m_pMarchSquads[j]->m_atkRange == m_pCharacters[i]->m_characterAtkRange)
			{
				foundMarchSquadNb = j;
				break;
			}
		}

		if (foundMarchSquadNb != -1)
		{
			m_pMarchSquads[foundMarchSquadNb]->m_pMembers.Add(m_pCharacters[i]);
		}
		else
		{
			UMarchSquad* newSquad = NewObject<UMarchSquad>(this);
			newSquad->m_atkRange = m_pCharacters[i]->m_characterAtkRange;
			newSquad->m_pMembers.Add(m_pCharacters[i]);
			newSquad->m_pTarget = m_pCharacters[i]->m_pNormalLongTask->m_pTarget;
			m_pMarchSquads.Add(newSquad);
		}
	}
	
	for (int32 i=0; i<m_pMarchSquads.Num(); i++)
	{
		//先计算出每个人物以目标为中心的连线角度
		float minDelAngle = 0.f;
		if (m_minCharacterSurroundNb >= m_pMarchSquads[i]->m_pMembers.Num()) minDelAngle = 360.f / m_minCharacterSurroundNb;
		else minDelAngle = 360.f / m_pMarchSquads[i]->m_pMembers.Num();
		TArray<float> angles;
		for (int32 j=0; j<m_pMarchSquads[i]->m_pMembers.Num(); j++)
		{
			FVector offset = m_pMarchSquads[i]->m_pMembers[j]->GetActorLocation() - m_pMarchSquads[i]->m_pTarget->GetActorLocation();
			FVector2D offset2D(offset.X, offset.Y);
			float alpha = UCollisionWarBpFunctionLibrary::GetYawFromLogicVec(offset2D);
			angles.Add((float)alpha);
		}

		int32 maxAnglePos = 0;
		if (m_pMarchSquads[i]->m_pMembers.Num() >= m_minCharacterSurroundNb)
			maxAnglePos = m_pMarchSquads[i]->m_pMembers.Num();
		else maxAnglePos = m_minCharacterSurroundNb;

		float minOffset = 0.f;
		int32 minOffsetNb = 0;
		TArray<int32> posList;
		//TArray<float> delAngleList;
		//对角度数列进行分析
		//1.先对角度进行排列
		//2.找到距离最近的角色
		//3.对所有角色进行位置安排
		//4.
		for (int32 j = 0; j < angles.Num(); j++)
		{
			if (j < angles.Num() - 1)
			{
				for (int32 k = j + 1; k < angles.Num(); k++)
				{
					if (angles[j] >= angles[k])
					{
						float tempAngle = angles[j];
						angles[j] = angles[k];
						angles[k] = tempAngle;
						ABaseCharacter* tempCharacter1 = m_pMarchSquads[i]->m_pMembers[j];
						ABaseCharacter* tempCharacter2 = m_pMarchSquads[i]->m_pMembers[k];
						m_pMarchSquads[i]->m_pMembers.RemoveAt(j);
						m_pMarchSquads[i]->m_pMembers.Insert(tempCharacter2, j);
						m_pMarchSquads[i]->m_pMembers.RemoveAt(k);
						m_pMarchSquads[i]->m_pMembers.Insert(tempCharacter1, k);
					}
				}
			}
		}

		for (int32 j=0; j<angles.Num(); j++)
		{

			FVector targetOffset = m_pMarchSquads[i]->m_pTarget->GetActorLocation() - m_pMarchSquads[i]->m_pMembers[j]->GetActorLocation();
			targetOffset.Z = 0;
			if (j == 0 || targetOffset.Size() <= minOffset)
			{
				minOffset = targetOffset.Size();
				minOffsetNb = j;
			}

			int32 anglePos = 0;
			int32 tmpAnglePos = (int32)(angles[j] / minDelAngle);
			if ((angles[j] - tmpAnglePos * minDelAngle) < 0) anglePos = tmpAnglePos - 1;
			else anglePos = tmpAnglePos;
			int32 cwAnglePos = anglePos;
			int32 ccwAnglePos = anglePos;
			int32 cwReturnPos = 0;
			int32 ccwReturnPos = 0;
			int32 cwDifPos = 0;
			int32 ccwDifPos = 0;
			SortCharacterCW(posList, cwAnglePos, maxAnglePos - 1, 0, cwReturnPos, cwDifPos);
			SortCharacterCCW(posList, ccwAnglePos, maxAnglePos - 1, 0, ccwReturnPos, ccwDifPos);
			if (cwDifPos <= ccwDifPos)
			{
				posList.Add(cwReturnPos);
				//delAngleList.Add(angles[j] - anglePos * minDelAngle + cwDifPos * minDelAngle);
			}
			else
			{
				posList.Add(ccwReturnPos);
				//delAngleList.Add(angles[j] - anglePos * minDelAngle + (maxAnglePos - ccwDifPos)*minDelAngle);
			}
			/*FVector drawLoc = m_pMarchSquads[i]->m_pMembers[j]->GetActorLocation() + FVector(0, 0, 250);
			DrawDebugString(GetWorld(), drawLoc, TEXT("Pos:") + FString::FromInt(posList[j]), NULL, FColor::Red, 0.1);
			FVector drawLoc1 = m_pMarchSquads[i]->m_pMembers[j]->GetActorLocation() + FVector(0, 0, 350);
			DrawDebugString(GetWorld(), drawLoc1, TEXT("num:") + FString::FromInt(j), NULL, FColor::Red, 0.1);*/
		}

		float delAngle = angles[minOffsetNb];
		/*FVector drawLoc = m_pMarchSquads[i]->m_pMembers[minOffsetNb]->GetActorLocation() + FVector(0, 0, 300);
		DrawDebugString(GetWorld(), drawLoc, TEXT("delAngle:") + FString::SanitizeFloat(delAngle), NULL, FColor::Green, 0.1);*/
		for (int32 j = 0; j<m_pMarchSquads[i]->m_pMembers.Num(); j++)
		{
			float angle = ((posList[j] - posList[minOffsetNb]) * minDelAngle + delAngle)*3.14f / 180.f;
			float x = m_pMarchSquads[i]->m_pTarget->GetActorLocation().X;
			float y = m_pMarchSquads[i]->m_pTarget->GetActorLocation().Y;
			UBaseSkill* pSkill = m_pMarchSquads[i]->m_pMembers[j]->m_pBaseEquipment->m_pSkills[0];
			for (int32 k=0; k< m_pMarchSquads[i]->m_pMembers[j]->m_pBaseEquipment->m_pSkills.Num(); k++)
			{
				if (!m_pMarchSquads[i]->m_pMembers[j]->m_pBaseEquipment->m_pSkills[k]->m_canImplementFlag) continue;
				pSkill = m_pMarchSquads[i]->m_pMembers[j]->m_pBaseEquipment->m_pSkills[k];
				break;
			}
			if (pSkill->m_pDetectComponent)
			{
				if (pSkill->m_pDetectComponent->GetClass() == USphereComponent::StaticClass())
				{
					USphereComponent* pSphere = Cast<USphereComponent>(pSkill->m_pDetectComponent);
					float radius = pSphere->GetScaledSphereRadius() - 200.f;
					if (radius <= 0) radius = 0;
					x += FMath::Cos(angle)*radius;
					y += FMath::Sin(angle)*radius;
				}
			}
			m_pMarchSquads[i]->m_pMembers[j]->m_pNormalLongTask->m_destination.X = x;
			m_pMarchSquads[i]->m_pMembers[j]->m_pNormalLongTask->m_destination.Y = y;
			FVector des(x, y, m_pMarchSquads[i]->m_pMembers[j]->m_defaultHeight + m_pMarchSquads[i]->m_pMembers[j]->m_relativeHeight);
			//DrawDebugLine(GetWorld(), m_pMarchSquads[i]->m_pMembers[j]->GetActorLocation(), des, FColor::Green, false, 0.1, 0, 5);
		}
	}
}
