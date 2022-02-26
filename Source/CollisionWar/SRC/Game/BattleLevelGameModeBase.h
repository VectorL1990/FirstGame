// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CWBaseGameMode.h"
#include "../Common/CollisionWarBpFunctionLibrary.h"
#include "Battle/Team/Team.h"
#include "Battle/Physics/PhysCalculator.h"
#include "Battle/Physics/Trigger/BaseTrigger.h"
#include "Battle/Team/EnermyGroup.h"
#include "Battle/Team/PlayerSpawnPoint.h"
#include "../Base/Battle/RecastNav/RecastDetourObject.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/LogicEvents.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "Battle/LogicFrameInfo.h"
#include "Battle/CompleteFrameInfo.h"
#include "Battle/PlanSpawnPoint.h"
#include "Battle/AIManager.h"
#include "Battle/GeometricRecognize/GeometricRecognizer.h"
#include "../Common/CollisionWarSingleton.h"
#include "BattleLevelGameModeBase.generated.h"

/**
 * 
 */



UCLASS()
class COLLISIONWAR_API ABattleLevelGameModeBase : public ACWBaseGameMode
{
	GENERATED_BODY()
	
public:
	ABattleLevelGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	UCollisionWarSingleton* m_pCWSingleton;
	/************************************************************************/
	/* 修改逻辑变量函数 */
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void LevelLogic(int32 frameNb);

	void UpdateAINavigation();

	void RCDebug();

	virtual void UpdateAllCharacterAILogic(float deltaT);

	void UpdateCharacterNormalLogic(float dT);


	void UpdateAllDeadCharacters(float tick);


	/************************************************************************/
	/* 难度调整系数
	/************************************************************************/

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void ReadSpecialEffectPercent(const FString& difficultyAndLevel);

	/************************************************************************/
	/* 补帧函数 */
	/************************************************************************/

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void LoadProgress(const FString& progressCode);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void MatchResult(const FString& matchResult);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void DEBUG_FUN(const FString& msg);

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SpawnEnermyByGroup();*/

	virtual void InitialNewCharacter(ABaseCharacter* pCharacter, int32 campFlag, int32& characterID, FLogicVec2D logicSpawnLoc, bool isAlreadyAssignID);

	void RemoveCharacterFromGame(ABaseCharacter* pCharacter);

	AKing* FindPlayerCharacterEntity(int32 entityID);

	ABaseCharacter* FindAICharacterEntity(int32 entityID);

	ABaseCharacter* FindCharacterEntity(int32 entityID);

	int32 GetAnUnOccupyID();
	/************************************************************************/
	/* 修改关卡逻辑函数
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void SpawnPhysGeo();

	void ClearAllDeadCharacters();

	void DeleteTutorialStep();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyIndicatorShowUp();
	/************************************************************************/
	/* 工具函数
	/************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	int32 GenRandNumber(int32 min, int32 max);

	/************************************************************************/
	/* 战斗系统常量                                                                     */
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	float m_defaultSpawnHeight = 190;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	float m_judgeResultSpawnHeight = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game")
	int32 m_maxFrameNb = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_randMul = 9;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_randAdd = 7;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_randMod = 8192;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_randXMax = 8192;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_randXMin = -8192;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_randYMax = 8192;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game")
	int32 m_randYMin = -8192;

	bool m_isInTutorial = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FTutorialStep> m_tutorialSteps;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class AActor> m_tutorialIndicatorClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	AActor* m_pTutorialIndicator;
	/************************************************************************/
	/* 帧同步时间变量                                                                     */
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_logicExpandTickTimeDelta = 40;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_maxUpdateAINbPerFrame = 5;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	int32 m_maxUpdateTeamNbPerFrame = 1;

	/************************************************************************/
	/* 逻辑变量                                                                     */
	/************************************************************************/
	
	void ModifyCharacterProByLevel(ABaseCharacter* pCharacter, const int32& level);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_canAcceptInput = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_canRunLevelLogic = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	FString m_gameProgress = "NULL";

	UPROPERTY()
	int32 m_curRoundNb = 0;

	UPROPERTY()
	int32 m_curLogicFrameNb = -1;

	UPROPERTY()
	bool m_isStart = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_isRoundEnd = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_isBattleEnd = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_isFading = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_isMain = false;

	UPROPERTY()
	int32 m_lastFrameNb = 0;

	UPROPERTY()
	TArray<ULogicFrameInfo*> m_toProcessFrames;

	UPROPERTY()
	TArray<ULogicFrameInfo*> m_pHistoryFrames;

	UPROPERTY()
	FPlayerOperationInfo m_playerOperation;

	UPROPERTY()
	UCompleteFrameInfo* m_pToCompareCorrectFrame;

	UPROPERTY()
	UCompleteFrameInfo* m_pLatestMemoryFrame;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	TSubclassOf<class UAIManager> m_aiManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	TSubclassOf<class UGeometricRecognizer> m_geometricRecognizerClass;

	UPROPERTY()
	UAIManager* m_pAIManager;

	UPROPERTY()
	UGeometricRecognizer* m_pGeometricRecognizer;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<APlanSpawnPoint*> m_pPlanSpawnPoints;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game")
	TArray<ATeam*> m_pTeams;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<ABaseCharacter*> m_pAllCharacters;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<ABaseCharacter*> m_pAICharacters;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<AKing*> m_pPlayerCharacters;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<ABaseCharacter*> m_pDeadCharacters;

	UPROPERTY()
	TArray<int32> m_occupyIDs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	AKing* m_pPlayerCharacter;

	UPROPERTY()
	EBattleState m_curBattleState;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<UPlayerSpawnPoint*> m_pPlayerSpawnPoints;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	TArray<UEnermyGroup*> m_pSpawnEnermyGroups;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	TSubclassOf<class UObject> m_BPPhysCalculatorClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game")
	TSubclassOf<class UObject> m_BPTeamClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	APhysCalculator* m_pPhysCalculator = NULL;

	UPROPERTY()
	URecastDetourObject* m_pRecastDetourObject;

	UPROPERTY()
	int32 m_curAIUpdateNb = 0;

	UPROPERTY()
	int32 m_curTeamAIUpdateNb = 0;

	UPROPERTY()
	TArray<int32> m_lostFrameNbs;

	UPROPERTY()
	TArray<int32> m_mainMachineUploadFrameList;

	UPROPERTY()
	TArray<int32> m_downloadFrameList;

	UPROPERTY()
	bool m_isGoingToCorrectLogic = false;

	UPROPERTY()
	bool m_isUploadingCorrectInfo = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	FPhysActorSpawnList m_originPhysActorSpawnList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	int32 m_curRandSeed;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_increaseTickPerFrame = 100;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_extraCDWhenSwitchSkill = 25000;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_maxFCNb = 6;
	/************************************************************************/
	/* 难度调整系数
	/************************************************************************/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/BattleLevel")
	int32 m_specialEffectPercent = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/BattleLevel")
	int32 m_hpAmplification = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/BattleLevel")
	int32 m_atkAmplification = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/BattleLevel")
	int32 m_dfcAmplification = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base/BattleLevel")
	int32 m_spawnAmplification = 0;
	/************************************************************************/
	/* 生产经营系统
	/************************************************************************/

	void RecoverPlayerPerInterval();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadEquipmentClass();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadCharacterHurtScoreLevels();

	int32 m_recoverIntervalTickCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_recoverInterval = 75;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_playerRecoverPercent = 5;

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FCharacterHurtScoreAmplifiedInfo> m_characterHurtScoreLevels;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FHurtScoreInfo> m_hurtScoreLevels;*/

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, int32> m_hurtTypeScoreCoeMap;

	int32 m_hurtScore = 0;

	int32 m_comboHitNb = 0;

	UPROPERTY()
	TMap<ABaseCharacter*, FHurtTypeAndValueInfo> m_characterHurtOneTickMap;*/

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, TSubclassOf<class UCharacterEquipInfo> > m_characterEquipInfoClassMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FFCSpawnEffectPSInfo> m_cardCombinePSMap;
	/************************************************************************/
	/* 异步加载部分
	/************************************************************************/
	bool m_hasApplyAsyncLoad = false;

	bool m_hasAsyncLoadDone = false;

	/************************************************************************/
	/* 得分记录系统
	/************************************************************************/

	virtual void RecordAllScores(TArray<ABaseCharacter*> pAllDeadCharacters);

	/************************************************************************/
	/* 临时变量                                                                     */
	/************************************************************************/
	UPROPERTY()
	TArray<FPlayerBattleStatus> m_tempPlayerStatics;
};
