// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "SRC/Game/BattleLevelGameModeBase.h"
#include "MapGenerator.h"
#include "Physics/PhysActorSonClass/ConstructionSite.h"
#include "../../Base/Battle/BattleLevelPlayerController.h"
#include "../Character/CamCharacter.h"
#include "NavManager.h"
#include "RoguelikeBattleGameMode.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRoguelikeBlockData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FRoguelikeBlockData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	FString blockName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		FString mapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		FString landBlockType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<FString> elementNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> elementLocationXList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> elementLocationYList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> elementYawList;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<FString> dumpActorNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> dumpActorLocXList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> dumpActorLocYList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		TArray<int32> dumpActorYawList;
};

UCLASS()
class COLLISIONWAR_API ARoguelikeBattleGameMode : public ABattleLevelGameModeBase
{
	GENERATED_BODY()
public:
	ARoguelikeBattleGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	ABattleLevelPlayerController* m_pBPC;

	
	
	/************************************************************************/
	/* Main Logic                                                                     */
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	UClass* ReadSpawnPointBPDynamic(const FString& className);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void GenRogueMap(const TArray<FString>& specifiedLandBlockList);
	
	void UpdateCharacterActionInstruction(const FPlayerOperationInfo& playerOperation, const TArray<FAICharacterOperationInfo>& aiCharacterOperations);

	virtual void UpdateAllCharacterAILogic(float deltaT) override;

	virtual void UpdateTeamSquads() override;

	void UpdateAICharacterOperation();

	uint8 UpdateVictoryCheck();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyWinLose(uint8 winLoseFlag);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void BackSingleprogressLevel();

	void UpdateTutorialStep();

	void CollectAllDeadCharacters();

	virtual void RefreshTutorial(const FString& tutorialStepName, bool needToShowTutorialButton, uint8 type) override;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TArray<FString> m_fixTutorialSerialNames;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_fadeOutTime = 2.f;

	FTimerHandle m_backToSPTimerHandler;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, FAppendPSInfo> m_pWeatherPSMap;
	/************************************************************************/
	/* Secondary Logic                                                                     */
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	UClass* ReadCharacterBPDynamic(const FString& className);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void InitialLevel();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySetSkyColorMatParam(uint8 curProgress, bool dayOrNight, bool battleOrSP);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
	void OutputAllActorLocations();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game")
		void OutputAllEventDemoActorLocations();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void DrawAllTiles();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SpawnPrefabActors(TArray<FString> physGeoNameList, TArray<FVector2D> physGeoSpawnLocs, TArray<float> physActorYaws,
		TArray<FString> dumpActorNameList, TArray<FVector2D> dumpActorSpawnLocs, TArray<float> dumpActorYaws, float spawnHeight);

	virtual void InitialNewCharacter(ABaseCharacter* pCharacter, int32 campFlag, int32& characterID, FLogicVec2D logicSpawnLoc, bool isAlreadyAssignID) override;

	void SpawnEnermyByGroup();

	void TestSpawnEnermyByGroup();

	TArray<ULandBlockTile*> GetPlayerAdjoinTiles();

	TArray<FVector> GetEnermySpawnPointRandomly();

	/** 
	 * item list have to be in order, for example helmet is first and 
	 */
	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
		void ResetItemList(const FCharacterItemList& itemList);

	void CalculateHurtScore();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadTutorialSteps();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadTutorialEnermyGroup(TArray<FGradingExpectToSpawnInfo>& tutorialEnermyGroup);

	void UpdateFrameDemonstration();

	void UpdateFullFieldStates(bool addOrSub, ABasePhysGeo* pGeo, const FEffectParams& param);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyAddSkillMask(const FString& skillMaskNb, const FString& radiusMaskNb, FVector loc);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyDeleteSkillMask(const FString& skillMaskNb, const FString& radiusMaskNb, FVector loc);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifySetFullFieldState(const TArray<uint8>& stateList);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class UMapGenerator> m_BPMapGeneratorClass;

	UPROPERTY()
	float m_curTickInterval = 0.f;

	UPROPERTY()
	TArray<FAICharacterOperationInfo> m_AIOperationList;

	UPROPERTY()
	UPlayerSpawnPoint* m_pPlayerSpawnPoint;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	FPlayerSpawnPointInfo m_originPlayerSpawnPointInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game")
	bool m_tickFlag = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UMapGenerator * m_pMapGenerator;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_tutorialExtraTick = 3000;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FGradingExpectToSpawnInfo m_TutorialDumpEnermies;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_tutorialMaxTick = 7500;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_chTutorialDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	FString m_enTutorialDescription;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class ACamCharacter> m_camCharacterClass;

	UPROPERTY()
	ACamCharacter* m_pCamCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isBattleTestFinish = false;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar")
	TMap<int32, uint8> m_fullFieldStates;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxSkillMaskNb = 5;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, ABasePhysGeo*> m_skillMaskMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TSubclassOf<class ANavManager> NavManagerBPClass;

	UPROPERTY()
	ANavManager* NavManager;
	/************************************************************************/
	/* Battle economic logic
	/************************************************************************/

	void DealEventList();

	virtual void RecordAllScores(TArray<ABaseCharacter*> pAllDeadCharacters) override;

	void TriggerAllEventCards();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, FCharacterHurtScoreInfo> m_characterScoreLevels;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_scoreLevelMaps;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_hurtLevelFinalScoreConvertMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		UParticleSystem* m_pTransferStationConnectPS;

	TArray<FString> m_deadCharacterNameList;

	TMap<ABasePhysGeo*, FEffectParams> m_fullFieldEffectMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxInventoryNb = 50;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_maxNumericCardNb = 100;
	/************************************************************************/
	/* Event logic
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyEventOccur(const FString& eventName);

	int32 m_curEventNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, UParticleSystem*> m_pEventPSMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, FEffectParams> m_eventEffectParamMap;

};
