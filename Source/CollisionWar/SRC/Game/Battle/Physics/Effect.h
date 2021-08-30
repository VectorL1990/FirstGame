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

	/** �����������Ч����ʩ�ӷ�Χ
	* 0��ֻʩ���ڲ�ͬ��Ӫ����
	* 1Ϊʩ����������Ӫ����
	* 2Ϊʩ���ڼ�����Ӫ����
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
	/* �������
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

	/** ��;��Ҫ����
	* 1.�ж�OneTimeEffect�Ƿ��Ѿ�������ϣ�����������ϼ���ɾ��
	* 2.�ж�PassiveEffect�Ƿ��Ѿ����ù�������������ִ�и�Ч��
	* 3.�жϷ������ɵ�Ч���Ƿ��Ѿ����ɹ����������˺�����Ҫ���������������һ��Ч������ָ����ˣ��������ɹ���������
	*/
	UPROPERTY()
	bool m_isOnTimeEffectDone = false;

	/** ��Ǽ����ͷŽ׶�
	* 0 - ��ͨ���ܣ����м�������������
	* 1 - �ڷ���ʱ����������ֱ�Ӵ�����������ʩ���������ֱ��ʩ����ȫ����ɫ
	* 2 - enhanceʱ����
	*/
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	uint8 m_launchType = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	TArray<ABaseCharacter*> m_pSubHost;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Physics")
	bool m_hasPlayFx = false;

	FString m_description;

	/**�����жϸ�Ч���Ƿ�ΪԴͷ��������������˺���Ч��������ʱҪ��������֪ͨ
	* ��Ч���ǹ����ڵ������ϵģ�����Ҫ�������������������һ����ͬ��Ч��������ָ�����
	* ��������Ч�������ƺʹ���ʵ��λ����һ���ģ�����Ҫ������������ֿ�������ִ�е���
	* �������ϵĴ��룬����������ϵĴ���
	*/
	bool m_isLinkSource = false;

	int32 m_enhanceType = -1;

	/************************************************************************/
	/* ս������
	/************************************************************************/
	/*void OrganizeCombatDescription(TArray<int32> values, FString hostName, FString exertName);

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_chCombatDescSection;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TArray<FString> m_enCombatDescSection;*/

	FString m_finalCombatDescription;
	/************************************************************************/
	/* У����ʱ����
	/************************************************************************/
	UPROPERTY()
	TArray<int32> m_correctSubHostIDs;

	UPROPERTY()
	int32 m_correctHostID;

	UPROPERTY()
	int32 m_correctOriginGeoID;
};
