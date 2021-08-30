// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "CompleteFrameInfo.generated.h"

/**
 * 
 */

UCLASS()
class COLLISIONWAR_API UCompleteFrameInfo : public UObject
{
	GENERATED_BODY()

public:
	bool copy(UCompleteFrameInfo* compareFrame);

	FCorrectInfoList ConstructCorrectList();

	void Reset();

	void CompareGeneralInfo(const FString& gameProgress, const int32& characterNb, const int32& polyNb, const int32& lineNb,
		const int32& pointNb, const int32& actorNb, const int32& pairNb, const int32& groupNb, const int32& randSeed);

	void CompareCharacterInfo(const FCharacterCorrectInfo& info);

	void ComparePolyInfo(const FPhysPolyInfo& info);

	void CompareLineInfo(const FPhysLineInfo& info);

	void ComparePointInfo(const FPhysPointInfo& info);

	void CompareActorInfo(const FPhysActorInfo& info);

	void CompareReactionPairInfo(const FReactionPairInfo& info);

	void CompareEnermyGroupInfo(const FEnermyGroupCorrectInfo& info);

	UPROPERTY()
	int32 m_frameNb = -1;
	UPROPERTY()
	FString m_gameProgress = "";
	UPROPERTY()
	int32 m_totalCharacterNb = 0;
	UPROPERTY()
	int32 m_totalPolyNb = 0;
	UPROPERTY()
	int32 m_totalLineNb = 0;
	UPROPERTY()
	int32 m_totalPointNb = 0;
	UPROPERTY()
	int32 m_totalActorNb = 0;
	UPROPERTY()
	int32 m_totalReactionPairNb = 0;
	UPROPERTY()
	int32 m_totalEnermyGroupNb = 0;


	UPROPERTY()
	bool m_hasUploadGeneralInfo = false;
	UPROPERTY()
	int32 m_curUploadCharacterNb = 0;
	UPROPERTY()
	int32 m_curUploadPolyNb = 0;
	UPROPERTY()
	int32 m_curUploadLineNb = 0;
	UPROPERTY()
	int32 m_curUploadPointNb = 0;
	UPROPERTY()
	int32 m_curUploadActorNb = 0;
	UPROPERTY()
	int32 m_curUploadPairNb = 0;
	UPROPERTY()
	int32 m_curUploadGroupNb = 0;


	UPROPERTY()
	TArray<FPlayerOperationInfo> m_playerOperationList;
	UPROPERTY()
	TArray<FAICharacterOperationInfo> m_AIOperationList;
	UPROPERTY()
	TArray<FCharacterCorrectInfo> m_characterCorrectInfoList;
	UPROPERTY()
	TArray<FPhysPolyInfo> m_physpolyCorrectList;
	UPROPERTY()
	TArray<FPhysLineInfo> m_physlineCorrectList;
	UPROPERTY()
	TArray<FPhysPointInfo> m_physpointCorrectList;
	UPROPERTY()
	TArray<FPhysActorInfo> m_physactorCorrectList;
	UPROPERTY()
	TArray<FReactionPairInfo> m_reactionPairInfoList;
	UPROPERTY()
	TArray<FEnermyGroupCorrectInfo> m_enermyGroupCorrectInfoList;
	UPROPERTY()
	TArray<int32> m_redundantCharacterIDs;
	UPROPERTY()
	TArray<int32> m_redundantPolyIDs;
	UPROPERTY()
	TArray<int32> m_redundantLineIDs;
	UPROPERTY()
	TArray<int32> m_redundantPointIDs;
	UPROPERTY()
	TArray<int32> m_redundantActorIDs;
	UPROPERTY()
	TArray<int32> m_redundantReactionPairIDs;
	UPROPERTY()
	TArray<int32> m_redundantEnermyGroupNbs;
	UPROPERTY()
	bool m_isFrameSame = true;
	UPROPERTY()
	int32 m_curRandSeed;
};
