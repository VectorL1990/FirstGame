// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "AIManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterSpawnInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString characterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 spawnNb;
};

//这个结构用于记录每个阵营当前各类别角色需要生成人物数数量
USTRUCT(BlueprintType, Blueprintable)
struct FGradingExpectToSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FCharacterSpawnInfo> expectSpawnNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 campFlag;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterGroup
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		TArray<FString> characterNameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		TArray<int32> numList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		int32 level;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 suitableProgress;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPreAssignCharacterStateInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FString stateName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 lowGrade;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 upGrade;
};

USTRUCT()
struct FPreAssignEffectList
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FString> list;
};


UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UAIManager : public UObject
{
	GENERATED_BODY()
	
public:
	int32 EstimateCrisisGrade(int32 hpPercent, int32 curEnermyPercent);

	int32 GetExpectCrisisGrade(bool isMainPeak, int32 curProgress);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void InitialAIManager(TArray<int32> campFlags, int32 curProgress, uint8 difficulty);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game")
	void InitialGradingNameList();

	void GetSpawnNameListAccordToCrisisGrade(int32 groupNb, int32 expectCrisisGrade);

	void GetSpawnNameList(int32 curFrame, int32 maxFrame, TArray<FGradingExpectToSpawnInfo>& allTeamExpectSpawnList, int32 mainCampFlag);

	bool m_testPressSpawnKey = false;

	bool m_testIsProducing = false;

	int32 m_testCrisitLevel = 5;

	void AssignSpecialEffectToCharacters(const TArray<FString>& spawnNameList, TMap<int32, FPreAssignEffectList>& effectNameList);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar")
	FString GetSpecialStateNames();

	void ResetAllParams();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<FGradingEnermySpawnInfo> m_enermySpawnListInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TMap<FString, FCharacterGroup> m_allLevelCharacterGroups;

	/************************************************************************/
	/* 常量                                                                     */
	/************************************************************************/
	//第一个峰值的帧数
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_firstPeakInterval;

	//峰值之间的帧数间隔
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_peakInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	TArray<int32> m_peakIntervalList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_firstMiniPeakInterval;

	//小峰值之间帧数间隔
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_miniPeakInterval;

	//各个生成时刻的间距
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_spawnInterval;

	//峰值跨度
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_peakFrameSpan;

	//小高峰的峰值跨度
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_miniPeakFrameSpan;

	//每段最大敌人生成数
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_maxSpawnEnermyNb;

	UPROPERTY()
	int32 m_specialEffectPercent;
	/************************************************************************/
	/* 逻辑变量                                                                     */
	/************************************************************************/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FBattleInfo m_battleInfo;

	bool m_isFirstMiniSpawnDone = false;

	//生成峰值与峰值之间的帧数
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	int32 m_curPeakIntervalFrameCount = 0;

	int32 m_curPeakNb = 0;

	//当获得预期敌人生成名单后，要分段按时间间隔生成，此变量用于记录时间间隔
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	int32 m_curSpawnIntervalFrameCount = m_spawnInterval;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	int32 m_curMiniPeakIntervalFrameCount = 0;

	//是否进入峰值的标记
	bool m_expectToPeak = false;

	//是否进入小高峰的标记
	bool m_expectToMiniPeak = false;

	//当前峰值计时器
	int32 m_curPeakFrameCount = 0;

	//记录当前峰值数
	int32 m_peakCount = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<FGradingExpectToSpawnInfo> m_expectToSpawnList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<FPreAssignCharacterStateInfo> m_permenantSpecialEffectNames;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString m_curTinyMapName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curProgress;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_curTinyMapLevel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_curTinyMapClassificationLevel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 m_difficulty;

	int32 m_spawnAmplificationCoe;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxPreAssignEffectNb = 3;

	//Recognize enermy amount of current round, for case enermy spawned by round, we should spawn them when previous men are all killed
	int32 m_curRoundEnermyNb = 0;

	//Current spawn round nb, for cases enermies spawned by round, first round spawn should be count by time interval
	int32 m_curRoundNb = 0;
};
