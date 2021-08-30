// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../../Character/BaseCharacter.h"
#include "BasePhysGeo.h"
#include "PhysPolySonClass/PhysPolygon.h"
#include "PhysLineSonClass/PhysLine.h"
#include "PhysPointSonClass/PhysPoint.h"
#include "PhysActorSonClass/BasePhysActor.h"
#include "PhysActorSonClass/DetonationActor.h"
#include "PhysActorSonClass/ProducePhysActor.h"
#include "DumpPhysActor.h"
#include "../../Character/KingCharacter/King.h"
#include "PhysCalculator.generated.h"

class UCollisionWarSingleton;
class ARoguelikeBattleGameMode;

USTRUCT(BlueprintType, Blueprintable)
struct FReactionPair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geoID1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geoID2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	ABasePhysGeo* pGeo1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	ABasePhysGeo* pGeo2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FVector reactionLoc1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FRotator reactionRot1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		FVector reactionLoc2;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		FRotator reactionRot2;

	/** 记录是哪个geo反应
	* 0 - 只是geo1发生反应，geo2不变
	* 1 - 只是geo2发生反应，geo1不变
	* 2 - geo1和geo2同时变
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	uint8 reactionType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FString reactionName1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FString reactionName2;

	bool isInitial = true;
};


USTRUCT(BlueprintType)
struct FBindPSInformation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	ABaseCharacter* pHost;

	UPROPERTY()
	ABaseCharacter* pGuest;

	UPROPERTY()
	UEffect* pEffect;

	FBindPSInformation()
	{
		
	}

	FBindPSInformation(ABaseCharacter* Host, ABaseCharacter* Guest, UEffect* Effect)
	{
		pHost = Host;
		pGuest = Guest;
		pEffect = Effect;
	}
};


UCLASS()
class COLLISIONWAR_API APhysCalculator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysCalculator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	ABasePhysGeo* FindEntity(int32 entityNb);

	/*UFUNCTION()
	int32 FindReactionPair(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2);*/

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<APhysPoint*> m_pPoints;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<APhysPolygon*> m_pPolygons;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<APhysLine*> m_pLines;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<ABasePhysActor*> m_pPhysActors;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<ABasePhysGeo*> m_pPhysGeos;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TMap<int32, ABasePhysGeo*> m_occupyGeoIDs;

	float m_defaultSpawnHeight = 190.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_geoActionTimesPerTick = 3;

	UCollisionWarSingleton* m_pCWSingleton;

	ARoguelikeBattleGameMode* m_pRGM;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, UParticleSystem*> m_pActorPSMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, UParticleSystem*> m_pAttributeHitPSMap;

	//int32 GenerateUnOccupiedPairID();

	int32 GenerateUnOccupiedGeoID();

	//void UpdateReactionGeoPair();

	void CollectAllNewPhysGeos();

	void UpdateAllPhysGeos();

	void UpdateBindPS();

	void UpdateCharacterEffects();
	UFUNCTION()
	void AddPhysGeo(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter, int32 campFlag);

	void PlayHitParticle(ABasePhysGeo* pGeo, FVector loc);

	/*UFUNCTION()
	void ReactionGeoTransform(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo);*/

	/*UFUNCTION()
	void CollectReactionPair();*/

	void DeleteInValidGeos();
	
	/*UFUNCTION()
	void ReactionGeoAddTag(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo,const int32& pairNb);

	UFUNCTION()
	void ReactionGeoSubtractTag(ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2, FReactionInfo reactionInfo,const int32& pairNb);*/

	UFUNCTION()
	void DeletePhysGeo(ABasePhysGeo* pGeo);

	UFUNCTION()
	void CharacterCallDeleteGeo(ABaseCharacter* pCharacter);

	/*UFUNCTION()
	bool DetermineReactionType(int32 pairNb);*/
	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void AddReactionInfoCache(FReactionInfo reactionInfo);*/
	/*UFUNCTION()
	void AddReactionInfoAccordingToTag(FName tag, ABasePhysGeo* pGeo);*/
	/*UFUNCTION()
	void SubtractReactionInfoAccordingToTag(FName tag, ABasePhysGeo* pGeo);*/
	/*UFUNCTION()
	void CopyReactionInfo(FReactionInfo& originInfo, FReactionInfo& targetInfo);*/
	UFUNCTION()
	ABasePhysGeo* SpawnPhysGeo(TSubclassOf<class UObject> spawnClass, FVector spawnLoc, FRotator spawnRot);
	/*UFUNCTION()
	void AwakeReactionPair(int32 pairNb, ABasePhysGeo* pGeo1, ABasePhysGeo* pGeo2);*/

	void SpawnActorEmitter(ABasePhysGeo* pHost, AActor* pActor, uint8 type);

	/************************************************************************/
	/* 效果计算部分
	/************************************************************************/
	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	TSubclassOf<class UEffect> FindEffectClassByName(FString effectName);*/

	bool SpawnEffectOnCharacter(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter);

	void AddEnhanceEffectToCharacter(ABasePhysGeo* pGeo, ABaseCharacter* pCharacter, int32 enhanceType);

	void SpawnPolyPreCalculateEffect(ABasePhysGeo* pGeo, FString functionName, const FEffectParams& effectParam, ABaseCharacter* pCharacter, TArray<ABaseCharacter*> pSubHosts);

	void SpawnEventEffect(const FEffectParams& effectParam, uint8 exertType, FString eventName);

	void SpawnOverallEffect(const FEffectParams& effectParam, ABasePhysGeo* pGeo);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void EffectOnCharacter(UEffect* pEffect, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void EffectEndCharacter(UEffect* pEffect, ABaseCharacter* pCharacter);

	void ActivatePassiveEffects(UEffect* pIntroEffect, ABaseCharacter* pCharacter);

	void AppendSuperpositionEffects(ABasePhysGeo* pIntroGeo);

	void ActivateEmbeddedEffects(UEffect* pIntroEffect, ABaseCharacter* pCharacter);

	void ActivateJudgeEffect(int32& judgeColor, int32& judgeNb, ABaseCharacter* pTargetCharacter);

	void ActivateAccumulateJudgeEffect(ABaseCharacter* pCharacter);

	void ActivateSourceJudgeEffect(const int32& judgeColor, const int32& judgeNb, ABaseCharacter* pSourceCharacter);

	void ActivateEffectDeleteEffect(UEffect* pDeleteEffect, ABaseCharacter* pCharacter);

	int32 ActivateHurtPassiveEffect(int32 hurtVal, UEffect* pHurtEffect, ABaseCharacter* pHurtTarget);

	int32 ActivateRecoverPassiveEffect(int32 recoverVal, UEffect* pRecoverEffect, ABaseCharacter* pRecoverTarget);

	void ActivateDeadEffect(ABaseCharacter* pCharacter);

	void AddPermenantEffectOnCharacter(FString effectName, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void EffectPlayFxByName(const FString& geoName, const FString& effectName, ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
		void NotifySpawnEffectParticle(const FString& geoName, ABaseCharacter* pCharacter);

	void PolygonEffectPreCalculate(APhysPolygon* pPolygon, TArray<FEffectParams>& effectParamList);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void DestroyEffect(UEffect* pEffect);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void CountEffectScore(UEffect* pEffect, ABaseCharacter* pCharacter);

	void CalGeoReactions();

	void CalCharacterAttributeReaction(ABaseCharacter* pHitCharacter, TArray<uint8> atkAttributes, TArray<FActiveAttributeReactionInfo>& flashEffects);

	void AddAttributeReactionEffect(ABaseCharacter* pCharacter, const FActiveAttributeReactionInfo& reactionInfo, ABasePhysGeo* pGeo);

	void AddSpecificTagScaleEffect(ABaseCharacter* pCharacter, ABasePhysGeo* pGeo);

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEffectParams> m_permenantEffectParams;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_damageCoeK1 = 1;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		int32 m_damageCoeK2 = 1;

	UPROPERTY()
	bool m_isAnalyzingFlag = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<ABaseCharacter*> m_pCharacterList;

	UPROPERTY()
	TArray<FReactionPair> m_reactionPairs;
	UPROPERTY()
	TArray<FReactionInfo> m_reactionInfoCaches;

	void AddPlayerToList(ABaseCharacter* pCharacter);

	UPROPERTY()
	bool m_initialPhys;

	UFUNCTION(BlueprintCallable, Category = TestFunction)
	void InitialPhys();

	UFUNCTION(BlueprintNativeEvent, Category = TestFunction)
	void ReadAllPreAssignEffectParams();

	UFUNCTION(BlueprintNativeEvent, Category = TestFunction)
	void ReadDefaultAttributeReactionInfos();

	void AddStateToCharacter(ABaseCharacter* pCharacter, FString stateName);

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		TArray<FScorePair> m_tempScorePairs;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, TSubclassOf<class ABasePhysGeo> > m_effectAppendGeoClassMap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FDefaultAttributeRestrainInfo> m_defaultAttributeReactionInfos;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<uint8, float> m_attributeAttachTimeMap;

	TMap<UParticleSystemComponent*, FBindPSInformation> m_bindPSMap;

	TMap<ABasePhysGeo*, UParticleSystemComponent*> m_spawnMutateActorPSMap;

	TMap<ABasePhysGeo*, AActor*> m_spawnMutateActorMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	int32 m_specificTagEffectReduction = 80;
	/************************************************************************/
	/* 道具部分
	/************************************************************************/

	UFUNCTION()
	void ReqCombineItem();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FItem> m_combineItemList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FItem> m_itemList;

	UPROPERTY()
	FString m_reqCombineItemName;
};
