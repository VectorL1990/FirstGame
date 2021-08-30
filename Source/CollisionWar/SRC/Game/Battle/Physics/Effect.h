// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "UObject/NoExportTypes.h"
#include "Effect.generated.h"

class ABasePhysGeo;
class ABaseCharacter;
/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FEffectNameGroup
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		TArray<FString> effectNameList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAppendEffectInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		FString effectName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physics")
		TArray<int32> effectValues;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
	int32 duration;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
	bool isPhysOrMag = true;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
	bool isJudgeEffect = false;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
	TArray<int32> hitColors = { 0,1,2,3 };

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		TArray<int32> hitNbs = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
	FString chDescription;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		FString enDescription;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEffectParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	FString effectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	int32 duration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	TArray<FEffectNameGroup> preconditionEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	TArray<FString> functionNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<int32> effectValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	TArray<int32> effectOnIntervalList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	TArray<FAppendEffectInfo> appendEffectList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool isIntervalLoop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool isPermenant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool canOverlap = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool isCalculateInPreStage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool isPhysOrMag = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool isJudgeEffect = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
		TArray<int32> hitColors = { 0,1,2,3 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
		TArray<int32> hitNbs = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };

	/** 用于描述这个效果的施加范围
	* 0即只施加于不同阵营的人
	* 1为施加于所有阵营的人
	* 2为施加于己方阵营的人
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
		uint8 effectExertType = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	FString chDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	FString enDescription;
};

UCLASS(Blueprintable, BlueprintType)
class COLLISIONWAR_API UEffect : public UObject
{
	GENERATED_BODY()
	
public:

	void RecoverDefaultValues();

	void Copy(UEffect* pTargetEffect);
	/************************************************************************/
	/* 计算变量
	/************************************************************************/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Physics")
	FString m_effectName = "NULL";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CollisionWar/Game/Physics")
	FString m_effectType = "NULL";
	
	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		TArray<FEffectNameGroup> m_preconditionEffects;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physics")
	TArray<int32> m_effectValues;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
		TArray<int32> m_modifiedValues;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	FEffectParams m_effectDefaultParam;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		TArray<FString> m_functionNames;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Physcis")
		TArray<FAppendEffectInfo> m_appendEffectList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Physcis")
	int32 m_duration = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	int32 m_curTickTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Physcis")
	TArray<int32> m_effectOnIntervalList;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Physcis")
	bool m_isIntervalLoop;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool m_isPermenant;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool m_canOverlap;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
	bool m_isPhysOrMag = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
		bool m_isJudgeEffect = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
		TArray<int32> m_hitColors;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physcis")
		TArray<int32> m_hitNbs;

	UPROPERTY()
	bool m_isOnByEmbeddedEffect = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	ABasePhysGeo* m_pOriginGeo = NULL;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	ABaseCharacter* m_pHost = NULL;

	/** 用途主要有三
	* 1.判断OneTimeEffect是否已经作用完毕，如已作用完毕即可删除
	* 2.判断PassiveEffect是否已经作用过，如已作用则不执行该效果
	* 3.判断反向生成的效果是否已经生成过，如弃牌伤害，需要反向给弃牌者生成一个效果用以指向敌人，如已生成过则不用生成
	*/
	UPROPERTY()
	bool m_isOnTimeEffectDone = false;

	/** 标记技能释放阶段
	* 0 - 普通技能，即有几何体正常触发
	* 1 - 在发动时跳过几何体直接触发，可能是施加于自身或直接施加于全场角色
	* 2 - enhance时触发
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	uint8 m_launchType = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<ABaseCharacter*> m_pSubHost;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	bool m_hasPlayFx = false;

	FString m_description;

	/**用于判断该效果是否为源头，例如弃牌造成伤害的效果，弃牌时要由玩家这边通知
	* 但效果是挂载在敌人身上的，所以要反过来给玩家身上生成一个相同的效果，用以指向敌人
	* 由于两个效果的名称和代码实现位置是一样的，所以要用这个变量区分开，究竟执行的是
	* 敌人身上的代码，还是玩家身上的代码
	*/
	bool m_isLinkSource = false;

	int32 m_enhanceType = -1;

	/************************************************************************/
	/* 战斗描述
	/************************************************************************/
	/*void OrganizeCombatDescription(TArray<int32> values, FString hostName, FString exertName);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chCombatDescSection;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_enCombatDescSection;*/

	FString m_finalCombatDescription;
	/************************************************************************/
	/* 校正临时变量
	/************************************************************************/
	UPROPERTY()
	TArray<int32> m_correctSubHostIDs;

	UPROPERTY()
	int32 m_correctHostID;

	UPROPERTY()
	int32 m_correctOriginGeoID;
};
