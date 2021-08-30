// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "CompleteFrameInfo.h"


bool UCompleteFrameInfo::copy(UCompleteFrameInfo* compareFrame)
{
	bool isSame = true;
	/*if (m_characterCorrectInfoList.Num() == compareFrame->m_characterCorrectInfoList.Num())
	{
		for (int32 i = 0; i < m_characterCorrectInfoList.Num(); i++)
		{
			bool isFoundCharacter = false;
			for (int32 j = 0; j < compareFrame->m_characterCorrectInfoList.Num(); j++)
			{
				if (m_characterCorrectInfoList[i].entityID == compareFrame->m_characterCorrectInfoList[j].entityID)
				{
					isFoundCharacter = true;
					bool isCharacterSame = m_characterCorrectInfoList[i].copy(compareFrame->m_characterCorrectInfoList[j]);
					if (!isCharacterSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  character ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundCharacter)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  character not found"));
				m_characterCorrectInfoList = compareFrame->m_characterCorrectInfoList;
				isSame = false;
				break;
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  character num is dif"));
		m_characterCorrectInfoList = compareFrame->m_characterCorrectInfoList;
		isSame = false;
	}

	if (!isSame || m_physpolyCorrectList.Num() != compareFrame->m_physpolyCorrectList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  poly num is dif"));
		m_physpolyCorrectList = compareFrame->m_physpolyCorrectList;
	}
	else
	{
		for (int32 i = 0; i < m_physpolyCorrectList.Num(); i++)
		{
			bool isFoundPoly = false;
			for (int32 j = 0; j < compareFrame->m_physpolyCorrectList.Num(); j++)
			{
				if (m_physpolyCorrectList[i].entityID == compareFrame->m_physpolyCorrectList[j].entityID)
				{
					isFoundPoly = true;
					bool isPolySame = m_physpolyCorrectList[i].copy(compareFrame->m_physpolyCorrectList[j]);
					if (!isPolySame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  poly ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundPoly)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  poly not found"));
				m_physpolyCorrectList = compareFrame->m_physpolyCorrectList;
				isSame = false;
				break;
			}
		}
	}

	if (!isSame || m_physlineCorrectList.Num() != compareFrame->m_physlineCorrectList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  line num is dif"));
		m_physlineCorrectList = compareFrame->m_physlineCorrectList;
	}
	else
	{
		for (int32 i = 0; i < m_physlineCorrectList.Num(); i++)
		{
			bool isFoundLine = false;
			for (int32 j = 0; j < compareFrame->m_physlineCorrectList.Num(); j++)
			{
				if (m_physlineCorrectList[i].entityID == compareFrame->m_physlineCorrectList[j].entityID)
				{
					isFoundLine = true;
					bool isLineSame = m_physlineCorrectList[i].copy(compareFrame->m_physlineCorrectList[j]);
					if (!isLineSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  line ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundLine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  line not found"));
				m_physlineCorrectList = compareFrame->m_physlineCorrectList;
				isSame = false;
				break;
			}
		}
	}

	if (!isSame || m_physpointCorrectList.Num() != compareFrame->m_physpointCorrectList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  point num is dif"));
		m_physpointCorrectList = compareFrame->m_physpointCorrectList;
	}
	else
	{
		for (int32 i = 0; i < m_physpointCorrectList.Num(); i++)
		{
			bool isFoundPoint = false;
			for (int32 j = 0; j < compareFrame->m_physpointCorrectList.Num(); j++)
			{
				if (m_physpointCorrectList[i].entityID == compareFrame->m_physpointCorrectList[j].entityID)
				{
					isFoundPoint = true;
					bool isPointSame = m_physpointCorrectList[i].copy(compareFrame->m_physpointCorrectList[j]);
					if (!isPointSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  point ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundPoint)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  point not found"));
				m_physpointCorrectList = compareFrame->m_physpointCorrectList;
				isSame = false;
				break;
			}
		}
	}

	if (!isSame || m_physactorCorrectList.Num() != compareFrame->m_physactorCorrectList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  physActor num is dif"));
		m_physactorCorrectList = compareFrame->m_physactorCorrectList;
	}
	else
	{
		for (int32 i = 0; i < m_physactorCorrectList.Num(); i++)
		{
			bool isFoundActor = false;
			for (int32 j = 0; j < compareFrame->m_physactorCorrectList.Num(); j++)
			{
				if (m_physactorCorrectList[i].entityID == compareFrame->m_physactorCorrectList[j].entityID)
				{
					isFoundActor = true;
					bool isActorSame = m_physactorCorrectList[i].copy(compareFrame->m_physactorCorrectList[j]);
					if (!isActorSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  physActor ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  physActor not found"));
				m_physactorCorrectList = compareFrame->m_physactorCorrectList;
				isSame = false;
				break;
			}
		}
	}

	if (!isSame || m_reactionPairInfoList.Num() != compareFrame->m_reactionPairInfoList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  reactionPair num is dif"));
		m_reactionPairInfoList = compareFrame->m_reactionPairInfoList;
	}
	else
	{
		for (int32 i = 0; i < m_reactionPairInfoList.Num(); i++)
		{
			bool isFoundReactionPair = false;
			for (int32 j = 0; j < compareFrame->m_reactionPairInfoList.Num(); j++)
			{
				if (m_reactionPairInfoList[i].reactionPairID == compareFrame->m_reactionPairInfoList[j].reactionPairID)
				{
					isFoundReactionPair = true;
					bool isPairSame = m_reactionPairInfoList[i].copy(compareFrame->m_reactionPairInfoList[j]);
					if (!isPairSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  reactionPair ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundReactionPair)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  reactionPair not found"));
				m_reactionPairInfoList = compareFrame->m_reactionPairInfoList;
				isSame = false;
				break;
			}
		}
	}

	if (!isSame || m_enermyGroupCorrectInfoList.Num() != compareFrame->m_enermyGroupCorrectInfoList.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  spawnGroup num is dif"));
		m_enermyGroupCorrectInfoList = compareFrame->m_enermyGroupCorrectInfoList;
	}
	else
	{
		for (int32 i = 0; i < m_enermyGroupCorrectInfoList.Num(); i++)
		{
			bool isFoundGroup = false;
			for (int32 j = 0; j < compareFrame->m_enermyGroupCorrectInfoList.Num(); j++)
			{
				if (m_enermyGroupCorrectInfoList[i].groupNb == compareFrame->m_enermyGroupCorrectInfoList[j].groupNb)
				{
					isFoundGroup = true;
					bool isGroupSame = m_enermyGroupCorrectInfoList[i].copy(compareFrame->m_enermyGroupCorrectInfoList[j]);
					if (!isGroupSame)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  spawnGroup ") + FString::FromInt(i) + TEXT(" is dif"));
						isSame = false;
					}
					break;
				}
			}
			if (!isFoundGroup)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  spawnGroup not found"));
				m_enermyGroupCorrectInfoList = compareFrame->m_enermyGroupCorrectInfoList;
				isSame = false;
				break;
			}
		}
	}


	if (m_gameProgress != compareFrame->m_gameProgress)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  gameProgress is dif"));
		m_gameProgress = compareFrame->m_gameProgress;
		isSame = false;
	}

	if (m_curRandSeed != compareFrame->m_curRandSeed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("CompleteFrameInfo::copy  m_curRandSeed is dif"));
		m_curRandSeed = compareFrame->m_curRandSeed;
		isSame = false;
	}*/

	return isSame;
}

FCorrectInfoList UCompleteFrameInfo::ConstructCorrectList()
{
	FCorrectInfoList correctList;
	correctList.characterCorrectList = m_characterCorrectInfoList;
	correctList.enermyGroupCorrectInfoList = m_enermyGroupCorrectInfoList;
	correctList.frameNb = m_frameNb;
	correctList.gameProgress = m_gameProgress;
	correctList.physactorCorrectList = m_physactorCorrectList;
	correctList.physlineCorrectList = m_physlineCorrectList;
	correctList.physpointCorrectList = m_physpointCorrectList;
	correctList.physpolyCorrectList = m_physpolyCorrectList;
	correctList.reactionPairInfoList = m_reactionPairInfoList;
	correctList.curRandSeed = m_curRandSeed;
	if (correctList.gameProgress == "") correctList.gameProgress = "NULL";
	return correctList;
}

void UCompleteFrameInfo::Reset()
{
	m_frameNb = -1;
	m_gameProgress = "NULL";
	m_totalCharacterNb = 0;
	m_totalPolyNb = 0;
	m_totalLineNb = 0;
	m_totalPointNb = 0;
	m_totalActorNb = 0;
	m_totalReactionPairNb = 0;
	m_totalEnermyGroupNb = 0;
	m_curRandSeed = 0;
	m_characterCorrectInfoList.Empty();
	m_physpolyCorrectList.Empty();
	m_physlineCorrectList.Empty();
	m_physpointCorrectList.Empty();
	m_physactorCorrectList.Empty();
	m_reactionPairInfoList.Empty();
	m_enermyGroupCorrectInfoList.Empty();
	m_redundantCharacterIDs.Empty();
	m_redundantPolyIDs.Empty();
	m_redundantLineIDs.Empty();
	m_redundantPointIDs.Empty();
	m_redundantActorIDs.Empty();
	m_redundantEnermyGroupNbs.Empty();
	m_isFrameSame = false;
}

void UCompleteFrameInfo::CompareGeneralInfo(const FString& gameProgress, const int32& characterNb, const int32& polyNb, const int32& lineNb, const int32& pointNb, const int32& actorNb, const int32& pairNb, const int32& groupNb, const int32& randSeed)
{
	if (gameProgress != m_gameProgress || characterNb != m_totalCharacterNb || polyNb != m_totalPolyNb ||
		lineNb != m_totalLineNb || pointNb != m_totalPointNb || actorNb != m_totalActorNb || pairNb != m_totalReactionPairNb ||
		groupNb != m_totalEnermyGroupNb || randSeed != m_curRandSeed)
	{
		m_isFrameSame = false;
	}
}

void UCompleteFrameInfo::CompareCharacterInfo(const FCharacterCorrectInfo& info)
{
	bool findCharacter = false;
	for (int32 i = 0; i < m_characterCorrectInfoList.Num(); i++)
	{
		if (m_characterCorrectInfoList[i].entityID == info.entityID)
		{
			findCharacter = true;
			bool isCharacterSame = m_characterCorrectInfoList[i].copy(info);
			if (!isCharacterSame) m_isFrameSame = false;
			m_redundantCharacterIDs.Remove(info.entityID);
			break;
		}
	}
	if (!findCharacter) m_isFrameSame = false;
}

void UCompleteFrameInfo::ComparePolyInfo(const FPhysPolyInfo& info)
{
	bool findPoly = false;
	for (int32 i = 0; i < m_physpolyCorrectList.Num(); i++)
	{
		if (m_physpolyCorrectList[i].entityID == info.entityID)
		{
			findPoly = true;
			bool isPolySame = m_physpolyCorrectList[i].copy(info);
			if (!isPolySame) m_isFrameSame = false;
			m_redundantPolyIDs.Remove(info.entityID);
			break;
		}
	}
	if (!findPoly) m_isFrameSame = false;
}

void UCompleteFrameInfo::CompareLineInfo(const FPhysLineInfo& info)
{
	bool findLine = false;
	for (int32 i = 0; i < m_physlineCorrectList.Num(); i++)
	{
		if (m_physlineCorrectList[i].entityID == info.entityID)
		{
			findLine = true;
			bool isLineSame = m_physlineCorrectList[i].copy(info);
			if (!isLineSame) m_isFrameSame = false;
			m_redundantLineIDs.Remove(info.entityID);
			break;
		}
	}
	if (!findLine) m_isFrameSame = false;
}

void UCompleteFrameInfo::ComparePointInfo(const FPhysPointInfo& info)
{
	bool findPoint = false;
	for (int32 i = 0; i < m_physpointCorrectList.Num(); i++)
	{
		if (m_physpointCorrectList[i].entityID == info.entityID)
		{
			findPoint = true;
			bool isPointSame = m_physpointCorrectList[i].copy(info);
			if (!isPointSame) m_isFrameSame = false;
			m_redundantPointIDs.Remove(info.entityID);
			break;
		}
	}
	if (!findPoint) m_isFrameSame = false;
}

void UCompleteFrameInfo::CompareActorInfo(const FPhysActorInfo& info)
{
	bool findActor = false;
	for (int32 i = 0; i < m_physactorCorrectList.Num(); i++)
	{
		if (m_physactorCorrectList[i].entityID == info.entityID)
		{
			findActor = true;
			bool isActorSame = m_physactorCorrectList[i].copy(info);
			if (!isActorSame) m_isFrameSame = false;
			m_redundantActorIDs.Remove(info.entityID);
			break;
		}
	}
	if (!findActor) m_isFrameSame = false;
}

void UCompleteFrameInfo::CompareReactionPairInfo(const FReactionPairInfo& info)
{
	bool findPair = false;
	for (int32 i = 0; i < m_reactionPairInfoList.Num(); i++)
	{
		if (m_reactionPairInfoList[i].reactionPairID == info.reactionPairID)
		{
			findPair = true;
			bool isPairSame = m_reactionPairInfoList[i].copy(info);
			if (!isPairSame) m_isFrameSame = false;
			m_redundantReactionPairIDs.Remove(info.reactionPairID);
			break;
		}
	}
	if (!findPair) m_isFrameSame = false;
}

void UCompleteFrameInfo::CompareEnermyGroupInfo(const FEnermyGroupCorrectInfo& info)
{
	bool findGroup = false;
	for (int32 i = 0; i < m_enermyGroupCorrectInfoList.Num(); i++)
	{
		if (m_enermyGroupCorrectInfoList[i].groupNb == info.groupNb)
		{
			findGroup = true;
			bool isGroupSame = m_enermyGroupCorrectInfoList[i].copy(info);
			if (!isGroupSame) m_isFrameSame = false;
			m_redundantEnermyGroupNbs.Remove(info.groupNb);
			break;
		}
	}
	if (!findGroup) m_isFrameSame = false;
}
