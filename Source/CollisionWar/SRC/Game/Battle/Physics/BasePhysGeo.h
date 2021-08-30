// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../../Common/CollisionWarBpFunctionLibrary.h"
#include "../Attachment/CharacterEquipInfo.h"
#include "Effect.h"
#include "Animation/SkeletalMeshActor.h"
#include "BasePhysGeo.generated.h"

class APhysLine;
class APhysPoint;
class APhysPolygon;
class ABasePhysActor;
class APhysCalculator;


USTRUCT(BlueprintType, Blueprintable)
struct FPreReactionPair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geo1ID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geo2ID;

	FPreReactionPair()
	{
		geo1ID = -1;
		geo2ID = -1;
	}
	FPreReactionPair(int32 id1, int32 id2)
	{
		geo1ID = id1;
		geo2ID = id2;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FReactionSpawnPair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geo1ID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 geo2ID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FLogicVec3D logicSpawnLoc;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FLogicVec2D logicSpawnDir;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FReactionInfo reactionInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 campFlag;

	FReactionSpawnPair()
	{
		geo1ID = -1;
		geo2ID = -1;
	}
	FReactionSpawnPair(int32 id1, int32 id2, FLogicVec3D loc, FLogicVec2D dir, FReactionInfo reactInfo, int32 camp)
	{
		geo1ID = id1;
		geo2ID = id2;
		logicSpawnLoc = loc;
		logicSpawnDir = dir;
		reactionInfo = reactInfo;
		campFlag = camp;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FSuperposeAttribute
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<uint8> list;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	UParticleSystem* pPS;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEffectParamList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FEffectParams> effectParamList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEnhancePSInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FVector relativeLoc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FRotator relativeRot;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		UParticleSystem* pPS;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDetonationInfo
{
	GENERATED_USTRUCT_BODY()

		//引爆的角色类型
		//0 - 主角
		//1 - 普通敌人
		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		uint8 detonationCharacterType;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		float detonationTime;

	//引爆方式
	//0 - 自动引爆
	//1 - 一定范围引爆
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		uint8 detonationType;
};

UCLASS()
class COLLISIONWAR_API ABasePhysGeo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePhysGeo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	virtual void SetBasicComponent(UPrimitiveComponent* pComponent, bool IsEnermySkill);

	void SetAttachEquipment(UCharacterEquipInfo* pEquipInfo);

	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void AddReactionInfo(FReactionInfo reactionInfo);*/

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Game/Battle")
	void ReactionParticleEmit(const FString& reactionType, const FName& tag);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void DoSomethingToCoverCharacter();

	//virtual void AddPreOverlapGeoPair(ABasePhysGeo* pGeo);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar/Game/Battle")
	void GeoHitCharacter(ABaseCharacter* pCharacter);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Battle")
	void InitialEquipmentInfo();

	void GeoReaction(ABasePhysGeo* pHitGeo);

	void AppendEnhanceParticle(uint8 enhanceType);


	/************************************************************************/
	/* 蓝图生成属性
	/************************************************************************/
	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystemComponent* m_pEnhancePSComponent;*/

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	FString m_className;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<FName> m_attributeTags;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TArray<uint8> m_attributeList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TArray<FSuperposeAttribute> m_superposeAttributeList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int32 m_level;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	EPhysGeoType m_physGeoType;

	UPROPERTY()
	UPrimitiveComponent* m_pBasicComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	UParticleSystem* m_pHitParticleSystem = NULL;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_isHitParticleBindtoEffect = false;

	/*UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, UParticleSystem*> m_pSuperposePSMap;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	TSubclassOf<class UObject> m_attchEquipClass;

	UPROPERTY()
	UCharacterEquipInfo* m_pAttachEquipInfo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int32 m_errorTolerance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	TArray<FEffectParams> m_effectParamList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	TMap<uint8, FEffectParamList> m_enhanceEffectParamList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	TMap<uint8, FEnhancePSInfo> m_enhancePS;

	/** 元素属性
	* 0 - 火
	* 1 - 水
	* 2 - 冰
	* 3 - 木
	* 4 - 土
	* 5 - 风
	* 6 - 雷
	*/
	int32 m_enhanceType = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	int32 m_obtacleRadius = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	int32 m_obtacleHeight = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	int32 m_moveSpeed;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle/Physics")
	int32 m_defaultHeight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TArray<int32> m_defaultReactionInfoNbs;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TMap<FString, FString> m_reactionMap;

	/** 标记这个粒子用于什么时候
	* 0 - 变形的时候播放
	* 1 - Projectile变成其他几何体如爆炸polygon时播放
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TMap<uint8, UParticleSystem*> m_pTransformPS;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TSubclassOf<class AActor> m_mutatePSActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	FVector m_mutatePSActorLoc;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TMap<FString, uint8> m_spawnMutateActorPSType;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TMap<FString, TSubclassOf<class AActor> > m_pSpawnMutatePSActor;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	TMap<FString, TSubclassOf<class ABasePhysGeo> > m_spawnMutateGeo;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle/Physics")
	bool m_isOneTimeReaction;
	/************************************************************************/
	/* 后期赋值属性
	/************************************************************************/
	/*UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	virtual void SetMutationPS();*/

	void AddEnhanceEffectToOverlapCharacters(int32 enhanceType);

	UPROPERTY()
	int32 m_entityID = -1;

	UPROPERTY()
	bool m_isInitial = false;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	uint8 m_hierachy = 1;

	UPROPERTY()
	int32 m_campFlag;

	/**moveType indicates how physGeo moves
	*  moveType == 0 means geo fixed
	*  moveType == 1 means geo moves along character owned it
	*  moveType == 2 means geo moves according to information(including rotation and displacement) dispatched from server
	*  moveType == 3 means geo moves randomly
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int8 m_moveType = 0;

	/************************************************************************/
	/* 计算属性
	/************************************************************************/
	
	UPROPERTY()
	bool m_isGeoValid = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<ABasePhysGeo*> m_pRootGeos;

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<ABasePhysGeo*> m_pSonGeos;*/

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<ABasePhysGeo*> m_pSecondarySonGeos;*/

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<FReactionInfo> m_reactionInfos;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Battle")
	int32 m_relativeHeight;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Game/Battle")
	ABaseCharacter* m_pHost;

	UPROPERTY()
		TArray<ABaseCharacter*> m_pOverlapCharacters;

	APhysCalculator* m_pPhysCalculator;

	TMap<FString, float> m_timeDilationParams;

	UPROPERTY()
	TArray<ABasePhysGeo*> m_pWaitReactionGeos;

	bool m_hasTriggerReaction = false;

	/*UPROPERTY()
	TArray<FPreReactionPair> m_preReactionPairs;

	UPROPERTY()
	TArray<FReactionSpawnPair> m_reactionSpawnPairs;*/

	/*UPROPERTY()
	TArray<FPreReactionPair> m_seperatePairs;*/

	/*UPROPERTY()
	int8 m_curMovePointNb = 0;

	UPROPERTY()
	int8 m_curRotateNb = 0;

	UPROPERTY()
	FLogicVec2D m_curRandTarget;*/
};
