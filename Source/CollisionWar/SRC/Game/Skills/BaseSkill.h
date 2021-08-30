// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Common/CollisionWarBpFunctionLibrary.h"
#include "../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "UObject/NoExportTypes.h"
#include "../Battle/Physics/Effect.h"
#include "BaseSkill.generated.h"

/**
 * 
 */
class ABaseCharacter;

UENUM(BlueprintType)
enum class ESkillGeoActionType : uint8
{
	SGAT_NULL,
	SGAT_SpawnPolygon,
	SGAT_SpawnLine,
	SGAT_SpawnPoint,
	SGAT_ThrowActor,
};

USTRUCT(BlueprintType, Blueprintable)
struct FMutationGeoClassInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 mutationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<TSubclassOf<class ABasePhysGeo> > geoClasses;
};

UCLASS(BlueprintType, Blueprintable)
class COLLISIONWAR_API UBaseSkill : public UObject
{
	GENERATED_BODY()
public:
	UBaseSkill(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintImplementableEvent, Category = "CollisionWar/Base/Animation")
	void NotifyInitial();

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Game/Skills")
	void InitialSkill();

	void CorrectSkill(const FSkillInfo& skillInfo);

	FSkillInfo ConstructSkillInfo();
	
	/************************************************************************/
	/* 蓝图初始化变量
	/************************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	FString m_skillName;

	/** 技能类型
	* 0 - 点类型、不定位的AOE
	* 1 - 定位AOE
	* 2 - 抛物线
	* 3 - 被动技能
	* 4 - 随机生成
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	uint8 m_skillType;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TArray<TSubclassOf<class UObject> > m_geoClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TMap<int32, FMutationGeoClassInfo> m_mutationGeoClass;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TMap<int32, UParticleSystem*> m_appendHostMutationPS;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	FString m_skillMotionTypeString;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	ESkillEffectType m_skillEffectType;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TArray<int32> m_spreadAngle;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TArray<int32> m_spawnGeoNb;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TArray<int32> m_spawnDistanceAmplifiedList = {1};

	/*skill cool down time*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
		float m_freezeLogicTickTime;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
		float m_preShakeLogicTickTime;

	/*time to freeze character motion*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	float m_freezeMotionTime;

	/*how long continuous skill can hold*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	int32 m_maxContinuousSkillTime;

	/*interval that skill spawn geos*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	int32 m_repeatSkillSpawnInterval = 1;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	bool m_isHostSkill;

	UPROPERTY()
	UShapeComponent* m_pDetectComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	FString m_skillAnimName = "NULL";

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	TArray<FEffectParams> m_appendHostEffectParams;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Skills")
	bool m_isAtkCardFlag = false;
	/************************************************************************/
	/* 计算变量
	/************************************************************************/
	int32 m_mutationType = -1;

	UPROPERTY()
	bool m_canImplementFlag;

	UPROPERTY()
	TArray<ABaseCharacter*> m_pOverlapCharacters;

	UPROPERTY()
	int32 m_campFlag;

	UPROPERTY()
	float m_skillFrameCount = 0;

	UPROPERTY()
	bool m_hasSpawnGeo = false;

	bool m_isNewSelectSkill = false;
	/************************************************************************/
	/* 校正临时变量
	/************************************************************************/
	UPROPERTY()
	TArray<int32> m_correctOverlapCharacterIDs;
};
