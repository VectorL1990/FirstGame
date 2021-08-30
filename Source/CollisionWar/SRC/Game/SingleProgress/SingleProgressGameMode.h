// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRC/Game/CWBaseGameMode.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "EventCard.h"
#include "PlayCard.h"
#include "ActionCard.h"
#include "NumericCard.h"
#include "ActionPanel.h"
#include "Board.h"
#include "ShadowActor.h"
#include "../Character/KingCharacter/King.h"
#include "DemoCharacter.h"
#include "../Character/CamCharacter.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "../../Base/SingleProgress/SingleProgressPlayerController.h"
#include "OverallIndexDemoActor.h"
#include "AnimBook.h"
#include "EventNodeManager.h"
#include "Engine/StreamableManager.h"
#include "../../Base/AsyncLoadDataAsset.h"
#include "../../Common/CollisionWarSingleton.h"
#include "SingleProgressGameMode.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FTinyMapClassificationInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FTinyMapInfo> tinyMapList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 classificationLevel;

	FTinyMapInfo GetTinyMapByLevel(const uint8& tinyMapLevel)
	{
		FTinyMapInfo resultTinyMapInfo;
		resultTinyMapInfo.tinyMapName = "NULL";
		TArray<int32> suitableNbList;
		for (int32 i=0; i<tinyMapList.Num(); i++)
		{
			if (tinyMapList[i].tinyMapLevel != tinyMapLevel) continue;
			suitableNbList.Add(i);
		}
		if (suitableNbList.Num() == 0) return resultTinyMapInfo;
		else
		{
			int32 randNb = FMath::RandRange(0, suitableNbList.Num() - 1);
			return tinyMapList[randNb];
		}
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FTheorizePlayerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		int32 life;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		int32 curScore;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 availableFlipTimes;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 compareTimes;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSkeletalMeshInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TSubclassOf<class AShadowActor> pShadowActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString skeletalMeshName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 occupyRadiusPercent;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCaptureSceneFrameInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> captureFrames;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventLandBlockInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> physGeoNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FVector> physGeoLocList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FRotator> physGeoRotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> dumpActorNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FVector> dumpActorLocList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FRotator> dumpActorRotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> staticMeshNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FVector> staticMeshLocList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FRotator> staticMeshRotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<float> staticMeshScaleList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<UParticleSystem*> m_PSList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FVector> PSLocList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> chDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enDescription;
};

USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexDemoInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString chDemoWords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString enDemoWords;
};

USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexDemoRangeInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FOverallIndexDemoInfo> demoInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<UParticleSystem*> pPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxOverallIndex;
};

USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexDemoInfoList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FOverallIndexDemoRangeInfo> list;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 overallType;
};

USTRUCT(BlueprintType, Blueprintable)
struct FRangeInt
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 min;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 max;

	FRangeInt()
	{
		min = 0;
		max = 0;
	}

	FRangeInt(int32 x, int32 y)
	{
		min = x;
		max = y;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FActionNodeWeight
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FRangeInt> actionNodeRangeList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<uint8> actionTypeList;

	/** 标记奖励的种类
	* 0 = 技能
	* 1 = 元素
	* 2 = 金钱
	* 3 = 属性
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FRangeInt> rewardRangeList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FActionLayerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	uint8 progressNb;

	/** 用以标识每一关对应层的难度
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> difficultyAndEventLayerMap;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSpeculativeParamInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 battleAvailableSkillNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 theorizeExtraLife;
};

USTRUCT(BlueprintType, Blueprintable)
struct FKnowledgeParamInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 extraAdditionAtk;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 diceExtralife;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDiceAndTheorizeSkillAppendInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FString skillName;

	UPROPERTY()
		FString functionName;

	UPROPERTY()
		float leftTime;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDiceAndTheorizeSkillPSInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		FString skillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		UParticleSystem* pPS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar")
		float time;
};

UCLASS()
class COLLISIONWAR_API ASingleProgressGameMode : public ACWBaseGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void StopTick();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ResumeTick();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void HideAllCardWidget();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void HideAllCard();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ShowAllCardWidget();

	void ShowAllCard();
		
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OutputAllStaticMeshInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SpawnStaticMeshActors(const TArray<FString>& staticMeshNames, const TArray<FVector>& locs, const TArray<FRotator>& rots, const TArray<FVector>& scales, const TArray<FString>& matNames, const FVector& camLoc, const FRotator& camRot);

	void PlayBeamParticle(AActor* pSource, AActor* pTarget, uint8 beamType);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_diceMaxNb = 6;

	ASingleProgressPlayerController* m_pSPPC;

	UCollisionWarSingleton* m_pCWSingleton;
	/************************************************************************/
	/* 一般信息
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadTextureInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadAllEventInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AddCardTransformInfo(FString transformName, FCardTransformInfo transformInfo);

	bool FindEmptyActionCardLoc(FVector& emptyLoc);

	bool FindEmptyCardLoc(FVector& emptyLoc);

	void DeleteCard(APlayCard* pPlayCard, bool shouldUpdateIntrinsicFunction);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadSkillCardInfo();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	TSubclassOf<class ADemoCharacter> ReadCharacterBP(const FString& characterName);

	UFUNCTION()
	void InitialRuneMode();

	UFUNCTION()
	void EndRuneMode();

	void ApplyCombineCardFunctions(AActionCard* pActionCard);

	void ApplyIntrinsicFunction(APlayCard* pPlayCard);

	void ApplyCombineTimeFunction(AActionCard* pActionCard);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadOverallIndexDemoInfoList();

	void UpdateOverallIndexDemoActorList(float dT);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifySetSkyColorMatParam(uint8 curProgress, bool dayOrNight, bool battleOrSP);
	
	/** 由于存在多个游戏模式，所以要进行模式区分
	* 0 - 普通SP模式
	* 1 - DiceBattle模式
	* 2 - 记忆力模式
	* 3 - 随机模式
	* 4 - 交易模式
	* 5 - 战斗模式
	* 6 - 解锁模式
	*/
	uint8 m_gameState = 0;

	bool m_tickFlag = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	float m_curTickTime;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curTickCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class APlayCard> m_playCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class ANumericCard> m_numericCardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AActionCard> m_actionCardClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	AActionCard* m_pNumericActionCard;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_actionPanelZ;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_cardZ;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_actionCardBoardLDPoint = FVector2D(-2000, -2000);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_actionCardBoardRTPoint = FVector2D(2000, 2000);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_LDPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector2D m_RTPoint;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_generateNumericCardInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_actionCardWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_actionCardHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_cardWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_cardHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_shadowActorHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_panelSweepXDis;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_panelSweepYDis;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_numericCardSpawnNb = 2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxNumericCardNb = 2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_actionCombineDuration = 5;

	UPROPERTY()
	ACamCharacter* m_pControlCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterialInstance* m_pBurningTextureMI;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pMatActionCardType;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pMatCardAttachment;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UMaterial* m_pSurfaceMatRoundButton;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_pColorTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FCardTextureAndTags> m_pPlayCardTextureMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_pActionTypeTextureMap;

	/** 每种行动都有一些描述文字，例如记忆类玩法有“我努力去记起那些已经失去的记忆，它们就像风中的飞蓬”
	* key 对应行动类型
	* 0 - 普通战斗
	* 1 - 记忆类玩法
	* 2 - 卡牌玩法
	* 3 - 困难战斗
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<uint8, FChAndEnDescriptionList> m_actionDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, float> m_timeConsumeMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_loseBonusCardPercent = 30;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_skillCardUpgradeK1 = 3;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_skillCardUpgradeK2 = 50;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_skillCardUpgradeK3 = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_skillCardIncreaseEXPStep = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_skillCardLoseIncreaseEXPPercent = 25;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxSkillCardLevel = 6;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FLevelUpradeInfo> m_skillCardLevelInfoMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_fadeOutTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_endSPTime = 2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_launchEventTime = 0.3;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pDeleteCardPS;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxPlayCardNb = 20;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxActionCardNb = 5;

	FTimerHandle m_openBattleLevelTimeHandler;

	FTimerHandle m_endSPTimeHandler;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_diceAndTheorizeFadeOutTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxDumpCardNb = 5;

	FTimerHandle m_diceAndTheorizeTimeHandler;

	UPROPERTY()
	TArray<FCardFunctionInfo> m_cardFunctionList;

	TArray<FString> m_dumpCardList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_progressMaxTickMap;

	int32 m_curProgressMaxTick;

	bool m_canTriggerBattle = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<uint8, FOverallIndexDemoInfoList> m_overallIndexDemoInfoMap;

	TArray<AOverallIndexDemoActor*> m_pOIDemoActors;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AOverallIndexDemoActor> m_pDefaultOIDemoActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_defaultUpdateOIDemoActorInterval;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AOverallIndexDemoActor> m_overallIndexDemoActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_OIDemoTime;

	int32 m_curUpdateOIDemoActorTick;

	uint8 m_curDemoOverallIndexNb = 0;

	
	/************************************************************************/
	/* 玩家生命信息
	/************************************************************************/
	FOverallIndexSlopeInfo ModifyOverallIndexSlopeByExtraFunction(const FOverallIndexSlopeInfo& slopeIndex);

	void UpdateOverallIndex(float dT);

	TArray<FOverallIndexExtraFunInfo> m_extraOverallIndexSlopeFuns;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_originLife = 100;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curLife = 100;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_curMoney = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_curEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_energyReductionInterval = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_energyReduction = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_lifeReduction = 5;

	float m_curLifeUpdateTime = 0.f;

	float m_curEnergyReductionTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FOverallIndexValueInfo m_overallIndexCostCoe;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FOverallIndexValueInfo m_maxOverallIndexValue;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FOverallIndexValueInfo m_curOverallIndex;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, FOverallIndexSlopeInfo> m_curOverallSlopeIndex;

	TMap<int32, float> m_overallSlopeTickCount;

	TMap<FString, FEventOverallIndexSlopInfo> m_curEventOverallSlopeIndex;

	/************************************************************************/
	/* 进程信息
	/************************************************************************/
	UFUNCTION()
	void InitialSingleprogressInfo(uint8 initialType);
	
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AddTinyMapInfoToClassificationInfo(const FString& mapName, const uint8& classification, const TArray<uint8>& gameTypes, const uint8& tinyMapLevel);

	UFUNCTION()
	void ProceedNextGame();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyGenTinyMap(const FString& tinyMapName);

	void GenerateNumericCards(float dT);

	void UpdateAllCards();

	/** 根据大地图名称和行动类型决定进入哪张地图
	*/
	UFUNCTION()
	void EnterMap();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyFadeIn();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyChangeGameState(uint8 state);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitialMissionList();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyGetMissionListByName(const FString& groupName);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FTinyMapClassificationInfo> m_tinyMapClassificationList;

	float m_curNumericCardGenerateTick = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FSPMissionListInfo m_missionList;

	int32 m_curMissionIndexFrameKeyNb = 0;
	/************************************************************************/
	/* 卡牌合成数据
	/************************************************************************/

	void GenerateJudgeCard(uint8& judgeColor, int32& judgeNb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	APlayCard* SpawnNewPlayCard(int32 cardNb, uint8 color, FString cardName);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadCardCombineDemoInfo();
	
	UPROPERTY()
	TArray<AActionCard*> m_pActionCards;

	UPROPERTY()
	TArray<APlayCard*> m_pNumericCards;

	UPROPERTY()
	TArray<APlayCard*> m_pPlayCards;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FActionTransformInfo> m_actionTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FCardTransformInfo> m_thoughtsCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_jobCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_researchCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_forgeCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_communicateCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_exploreCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FCardTransformInfo> m_eventCardTransformInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FOneTimeCardTransformSaveInfo> m_oneTimeOutputRecords;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FSPCardCombineDemoInfo> m_cardCombineDemoInfoMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FSPCardCombineDemoInfo> m_allOIDemoInfos;

	UPROPERTY()
	TArray<FSPCardCombineDemoTimingInfo> m_cardCombineDemoTimingInfos;

	UPROPERTY()
	TMap<int32, float> m_cardCombineDemoTimeCount;

	UPROPERTY()
	TMap<int32, AActor*> m_pCardCombineDemoActors;

	UPROPERTY()
	TMap<int32, UParticleSystemComponent*> m_pCardCombinePSComponents;
	/************************************************************************/
	/* 事件部分
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadAllEvents();

	UFUNCTION(BlueprintCallable,Category = "CollisionWar")
	void InitialEvent(FEventGroupInfo event);

	int32 GenerateEventCode();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyTriggerEvent();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifyEndEventMode();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FEventLandBlockInfo ReadEventDemoInfos(const FString& eventName);

	UFUNCTION()
	void EndEventMode();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		UStaticMesh* ReadStaticBP(const FString& name);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_eventDemoCenterLoc;

	//潜伏事件，当系统触发事件时，会自动检测是否触发了某些潜伏事件
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEventGroupInfo> m_potentialEvents;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEventGroupInfo> m_periodicEvents;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEventGroupInfo> m_initialEvents;

	TMap<int32, FString> m_existEventCodeNameMap;

	TArray<FString> m_curEventNameList;

	UPROPERTY()
	TArray<AActor*> m_pEventDemoActorList;

	UPROPERTY()
	TArray<UParticleSystemComponent*> m_pEventDemoPSList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_eventDemoPOVLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FRotator m_eventDemoPOVRot;

	/************************************************************************/
	/* 随机卡牌生成部分
	/************************************************************************/

	TArray<int32> m_leftJudgeCardList;

	/************************************************************************/
	/* 掷骰地下城玩法部分
	/************************************************************************/

	void InitialDiceBattle();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void EndDiceBattle();

	void UpdateDiceLogic(float dT);

	void GenerateDiceCard();

	void InitialDiceBattleParam(int32 difficulty, bool isCharacterDice);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadDiceSkillPS(uint8 readType);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadAllDifficultyDiceInfo();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void AssignDiceParamAccordKnowledge();

	void TriggerDiceAppendSkill(bool bingoOrNot);

	void PlayDiceOrTheorizeSkillPS(FString skillName, uint8 type);

	UFUNCTION()
	void DiceSkillFlipCardEnd();

	/** DiceBattle中各类型倒计时的列表
	*0 = 从开始到展示Start字样的倒计时
	*1 = 展示Start到结束展示的倒计时
	*2 = 生成数字卡牌的总时长
	*3 = 展示PlayerRound字样的总时长
	*4 = 单个skillPanel热身的时长
	*5 = 单个skillPanel行动的总时长
	*6 = 展示EnermyRound字样的总时长
	*7 = 单个skillPanel热身的时长
	*8 = 单个skillPanel行动的总时长
	*/
	uint8 m_diceBattleStage = 0;

	/** DiceBattle中各类型倒计时的列表
	*0 = 从开始到展示Start字样的倒计时
	*1 = 展示Start到结束展示的倒计时
	*2 = 生成数字卡牌的总时长
	*3 = 展示PlayerRound字样的总时长
	*4 = 单个skillPanel热身的时长
	*5 = 单个skillPanel行动的总时长
	*6 = 展示EnermyRound字样的总时长
	*7 = 单个skillPanel热身的时长
	*8 = 单个skillPanel行动的总时长
	*9 = 展示结语的总时长
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, float> m_diceIntervalMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_diceCardZ = 810;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AActionPanel> m_pDicePanelClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_diceCardOriginLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_diceCardOffset;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_diceBattleCharacterLoc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 m_diceSkillNb = 2;

	float m_curDiceCount = 0.f;

	float m_curDiceTotalCount = 0.f;
	
	int32 m_curDiceScore = 0;

	int32 m_curDiceFlipCardNb = 0;

	int32 m_diceBattleColNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, FDiceBattleInfo> m_allLevelDiceBattleInfos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, FKnowledgeParamInfo> m_knowledgeAttributeParamInfo;

	FDiceBattleInfo m_diceBattleInfo;

	int32 m_diceCardNb = 36;

	UPROPERTY()
	TArray<APlayCard*> m_pDiceCardList;

	TArray<APlayCard*> m_pDiceSkillFlipCards;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FDiceAndTheorizeSkillPSInfo> m_pDiceOrTheorizeSkillParticleMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pSPBeamParticle_1;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pSPBeamParticle_2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pSmokePS;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector m_defaultDiceCharacterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FRotator m_defaultDiceCharacterRot;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector m_diceSkillPSLoc;

	UPROPERTY()
	TMap<UParticleSystemComponent*, float> m_allDiceAndTheorizeSkillPSDurations;

	UPROPERTY()
	TMap<int32,FDiceAndTheorizeSkillAppendInfo> m_curAppendDiceSkillInfos;

	UPROPERTY()
	FTimerHandle m_diceSkillTimerHandler;

	bool m_diceAndTheorizeCanAction = false;

	bool m_isInDiceTutorialState = false;
	/************************************************************************/
	/* 猜牌玩法部分
	/************************************************************************/

	void InitialTheorizePanel();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void EndTheorize();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyGetTheorizeParamFromDT(int32 difficulty, uint8 readType);

	void InitialTheorizeParam(int32 difficulty);

	void DispatchTheorizeCards();

	void DeleteTheorizeCard(ANumericCard* pCard);

	void ResetAllTheorizeCards();

	uint8 Bet(ANumericCard* pPlayerCard, ANumericCard* pOppCard);

	void Theorize(ANumericCard* pTheorizeCard);

	void UncoverTheorizeCard(ANumericCard* pTheorizeCard);

	void UpdateTheorize(float dT);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AssignTheorizeParamAccordSpeculative();

	void LaunchTheorizeSkill(FString skillName);

	void TriggerTheorizeSkill(uint8 actionType, ANumericCard* pTargetCard, ANumericCard* pSourceCard);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AActor> m_pTheorizeBoardClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_theorizeBoardZ = 800;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_theorizeCardZ = 810;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_oppCardCenterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_playerCardCenterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_theorizeCardPanelWidth;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector m_theorizeCharacterLoc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 m_theorizeSkillNb = 2;

	UPROPERTY()
	ABoard* m_pTheorizeBoard;

	UPROPERTY()
	TArray<ANumericCard*> m_pOppTheorizeCards;

	UPROPERTY()
	TArray<ANumericCard*> m_pPlayerTheorizeCards;

	UPROPERTY()
	TArray<FOutputCardInfo> m_allTheorizeCardInfos;

	uint8 m_theorizeState = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, float> m_theorizeIntervalMap;

	float m_curTheorizeTimeCount = 0.f;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_flipCardNb = 1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_cardNbPerRound = 6;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_maxResetTimes = 3;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_maxCardNb = 8;

	int32 m_curTheorizeLevel = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 m_targetScore = 10;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FTheorizePlayerInfo m_theorizePlayerInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_theorizeSkillPSLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_defaultTheorizeCharacterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FRotator m_defaultTheorizeCharacterRot;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FVector m_defaultTheorizeDemoEnermyLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		FRotator m_defaultTheorizeDemoEnermyRot;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, FSpeculativeParamInfo> m_speculativeAttributeParamInfo;

	ADemoCharacter* m_pDemoEnermy;

	UPROPERTY()
		TMap<int32, FDiceAndTheorizeSkillAppendInfo> m_curAppendTheorizeSkillInfos;

	bool m_isInTheorizeTutorialState = false;
	/************************************************************************/
	/* 随机抽卡玩法部分
	/************************************************************************/

	void UpdateDrawCard(float dT);

	void InitialDrawCard(int32 drawCardNb, int32 trialTimes);

	void GenerateDrawCardInfo();

	void EndDrawCard();
	
	UPROPERTY()
	TArray<FOutputCardInfo> m_allDrawCardsInfo;

	int32 m_drawCardNb;

	int32 m_drawTrialTimes;

	int32 m_winDrawCardNb;

	uint8 m_drawCardState = 0;

	float m_curDrawCardTimeCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, float> m_drawCardTimeIntervalMap;
	/************************************************************************/
	/* 商铺部分
	/************************************************************************/
	void InitialShop();

	void UpdateShop();

	void EndShop();

	uint8 m_shopState = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_cardValuePriceMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TMap<int32, int32> m_cardSellValuePriceMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxMoney = 1000;
	/************************************************************************/
	/* 进入战斗部分
	/************************************************************************/
	void InitialBattle(const FBattleInfo& battleInfo);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void OpenBattleLevel();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	TArray<int32> GetBattleBonusLevels(uint8 battleLevel);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_expLevelBonusCoe = 1.5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxWeaponNb = 5;
	/************************************************************************/
	/* 生成暗影粒子模型
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadShadowSkeletalMesh();

	AShadowActor* AddShadowActor(FString skeletalMeshName, FVector spawnLoc, FRotator spawnRot, uint8 shadowPSType, int32 idx);

	void DeleteShadowActor(AShadowActor* pShadowActor);

	/** 此函数为按下切换模式键时触发，主要功能是暂停Tick，隐藏卡牌等
	*/
	void InitialShadowMode();

	/** 此函数是当卡牌已经隐藏完毕，同时后处理动画已经完毕后，生成暗影模型
	*/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SpawnAllShadowActors();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void EndShadowMode();

	/** idleState标记初始化demoCharacter时的动画状态
	* 0. runeMode
	* 1. theorize状态
	* 2. diceBattle状态
	*/
	void SpawnRuneDemoCharacter(uint8 idleState);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void ResetItemList(const FCharacterItemList& itemList);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TMap<FString, FSAOverallIndexSlopInfo> m_weatherEffectInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UParticleSystem*> m_shadowPSMap;

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FSkeletalMeshInfo> m_pShadowSkeletalMeshMap;*/

	UPROPERTY()
	TArray<AShadowActor*> m_pShadowActorList;

	UPROPERTY()
	TArray<UParticleSystemComponent*> m_pShadowActorPSComponentList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_runeCharacterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_demoCharacterLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FRotator m_demoCharacterRot;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_runePOVLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_SPPOVLoc;

	ADemoCharacter* m_pDemoCharacter;
	/************************************************************************/
	/* 转场及结局
	/************************************************************************/
	
	void UpdateCaptureScenes();

	UFUNCTION()
	void EndSP();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadAllEndingInfo(uint8 state);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void GetEndInfo(const TArray<FEndInfo>& endInfos, uint8 endType);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FEndInfo m_endInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_noPictureActivateTextTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_gotPictureActivateTextTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, FCaptureSceneFrameInfo> m_captureFramesInfo;

	uint8 m_endType = 0;
	/************************************************************************/
	/* 引导部分
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadTutorialSteps();

	void UpdateTutorialStep();

	void DeleteTutorialStep();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyIndicatorShowUp();

	virtual void RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type) override;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_fixTutorialSerialNames;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FTutorialStep> m_tutorialSteps;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AActor> m_tutorialIndicatorClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	AActor* m_pTutorialIndicator;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		TArray<AActor*> m_pTutorialIndicators;

	bool m_isInTutorial = false;
	/************************************************************************/
	/* 固定卡系统
	/************************************************************************/
	TArray<FCursedCardInfo> m_curCursedCardInfo;

	/************************************************************************/
	/* 天气系统
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, int32> m_weatherWeight;

	/************************************************************************/
	/* 主流程部分
	/************************************************************************/
	AAnimBook* m_pAnimBook;

	UEventNodeManager* m_pEventNodeManager;

	/** 难度应该随着关数和层数不断变难
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FActionLayerInfo> m_actionLayerInfo;

	int32 m_curNodeNb = 0;

	//一个关卡由多层组成，而每层由多个行动点组成
	int32 m_curEventNodeNb = 0;

	//例如每6个行动组成一层，而每个关卡可能有多层组成，所以此变量用于记录现在处于那一层
	int32 m_curEventNodeLayerNb = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FActionNodeWeight m_actionNodePercent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxActionNodeNbPerLine = 10;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_SAOriginalLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		float m_SADemoOffset;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AEventCard> m_eventCardClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<uint8, FEventCardInfoList> m_allEventInfoMap;

	UPROPERTY()
		bool m_isInBossBattleLayer = false;

	UPROPERTY()
	TArray<FActionNodeBriefInfoList> m_actionNodeList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UTexture*> m_eventCardTypeTextureMap;

	/** Textures of different bonus types
	 * 0 = skill
	 * 1 = attribute
	 * 2 = money
	 * 3 = physAttribute
	 * 4 = relics
	 */
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TMap<uint8, UTexture*> m_rewardTypeTextureMap;

	/** Bonus proportion of all types
	 * 0 - skill
	 * 1 = attribute
	 * 2 = money
	 * 3 = physAttribute
	 * 4 = relics
	 * Maybe it's better to calculate number of different kinds of bonus by proportion instead of giving an exact number
	 * because we want to keep all bonus in proportion but also make it look ramdom
	 * however, problem is that total amount of bonus may be changed from time to time, so we can setup
	 * a number X which is a little bit larger than original plan, mutiply X by this proportion so that we can get all
	 * bonus number fluctuated 1 or 2.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, float> m_allBonusTypeProportion;

	/** Total bonus nb which is a little bit larger than original total nb.
	 * Maybe it's better to calculate number of different kinds of bonus by proportion instead of giving an exact number
	 * because we want to keep all bonus in proportion but also make it look ramdom
	 * however, problem is that total amount of bonus may be changed from time to time, so we can setup
	 * a number X which is a little bit larger than original plan, mutiply X by this proportion so that we can get all
	 * bonus number fluctuated 1 or 2.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_fluctuatedTotalBonusNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_skillSlotNbMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AAnimBook> m_pAnimBookClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UEventNodeManager> m_pEventNodeManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_animBookSpawnLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FRotator m_animBookSpawnRot;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FVector m_animBookScale;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_maxBonusChoiseCardNb = 2;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxAvailableSkillNb = 30;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_maxDiceSkillNb = 10;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_maxTheorizeSkillNb = 10;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FCharacterAttributeInfo GetCharacterAttributeInfo(const FString& characterName);

	UPROPERTY()
	TArray<int32> m_curAvailableNodeIDs;

	int32 m_curDayNb = 1;

	void GenerateRandActionNodeWeb(bool isIncludeBossBattle);

	/** This is where truely execute action card's action
	 */
	void UpdateEventCardAction(bool isChoiceEvent);

	void TriggerChoiceEvent(FEventFunction fun);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void AddEventInfo(const FEventCardInfo& eventCardInfo);

	/** updateType represents which type of update it is
	* 0. Normal update, such as update after actions of dice or theorize
	* 1. Battle update, all data like messages inside CWGI should be reloaded
	* 2. New map update, such as player transfer from snow map to desert map
	*/
	void UpdateActionNode(uint8 updateType);

	void DecideWeather();

	void DecideDayOrNight();

	/** This function responsible for bonus calculation
	 * type - represent what game it is
	 * 0. battle - skill or attribute
	 * 1. diceBattle - money
	 * 2. theorize - physattribute or relics
	 * CalculateBonus should be run before game started, and every bonus type should be in proportion
	 * for example proportions of attribute,skills,physAttribute should be 40/40/20
	 * battle can get attribute and skill, dice can get big money, theorize can get physAttribute(or equivalent)
	 */
	void CalculateBonus(int32 totalCardNb, uint8 type, bool winFlag, TArray<FString>& bonusCards);

	void InterpretBonus();

	void UpdateCursedCardRound();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	FSAOverallIndexSlopInfo ReadWeatherEffectInfo(const FString& weatherType);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyLoadCalenderMenu();
};
