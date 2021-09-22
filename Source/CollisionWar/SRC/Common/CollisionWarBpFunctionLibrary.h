// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Game/Battle/Physics/Effect.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "CollisionWarSingleton.h"
#include "../ThirdParty/tinyxml2.h"
#include "CollisionWarBpFunctionLibrary.generated.h"

using namespace tinyxml2;
/**
 * 
 */
#define pi 3.1415926535898
#define  expandLogicTick 30
#define arenaDefaultHeight 190

class UBaseSkill;
class UCharacterEquipInfo;

UENUM(BlueprintType)
enum class EGridType : uint8
{
	GT_NULL,
	GT_OwnSideDominant,
	GT_OppDominant,
	GT_Draw,
	GT_OwnBoarder,
	GT_OppBoarder,
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	BS_None,
	BS_Prepare,
	BS_NormalFighting,
	BS_BattleOver,
	BS_AllOver,
};

UENUM(BlueprintType)
enum class EEditMapState : uint8
{
	EMS_NULL,
	EMS_DirectControllCamera,
	EMS_AdjustCamera,
	EMS_SelectedPhysActorWidget,
	EMS_SelectedPhysActor,
};

UENUM(BlueprintType)
enum class EMatchStatus : uint8
{
	MS_NULL,
	MS_WaitToEnsure,
	MS_Accept,
	MS_Reject,
};

USTRUCT(BlueprintType)
struct FLogicVec3D
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Common")
		int32 X;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Common")
		int32 Y;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 Z;
public:
	FLogicVec3D()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	FLogicVec3D(int32 x, int32 y, int32 z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	FORCEINLINE FLogicVec3D operator-(const FLogicVec3D& V) const;
	FORCEINLINE FLogicVec3D operator-(const int32& a) const;
	FORCEINLINE FLogicVec3D operator+(const FLogicVec3D& V) const;
	FORCEINLINE FLogicVec3D operator+(const int32& a) const;
	int32 sqr()
	{
		int32 square = X * X + Y * Y + Z*Z;
		return square;
	}

	int32 Size()
	{
		int32 square = sqr();
		int32 expandSize = FMath::FloorToInt(FMath::Sqrt(square * 10000));
		int32 decimalSize = expandSize % 100;
		return (expandSize - decimalSize) / 100;
	}
};

FORCEINLINE FLogicVec3D FLogicVec3D::operator-(const FLogicVec3D& V) const
{
	return FLogicVec3D(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE FLogicVec3D FLogicVec3D::operator+(const FLogicVec3D& V) const
{
	return FLogicVec3D(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE FLogicVec3D FLogicVec3D::operator-(const int32& a) const
{
	return FLogicVec3D(X - a, Y - a, Z - a);
}

FORCEINLINE FLogicVec3D FLogicVec3D::operator+(const int32& a) const
{
	return FLogicVec3D(X + a, Y + a, Z + a);
}


USTRUCT(BlueprintType, Blueprintable)
struct FLogicVec2D
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 Y;
public:
	FLogicVec2D()
	{
		X = 0;
		Y = 0;
	}

	FLogicVec2D(int32 x, int32 y)
	{
		X = x;
		Y = y;
	}

	FORCEINLINE FLogicVec2D operator-(const FLogicVec2D& V) const;
	FORCEINLINE FLogicVec2D operator-(const int32& a) const;
	FORCEINLINE FLogicVec2D operator+(const FLogicVec2D& V) const;
	FORCEINLINE FLogicVec2D operator+(const int32& a) const;
	FORCEINLINE FLogicVec2D operator/(const int32& a) const;
	FORCEINLINE FLogicVec2D operator*(const int32& a) const;
	FORCEINLINE bool operator==(const FLogicVec2D& V) const;
	FORCEINLINE bool operator!=(const FLogicVec2D& V) const;
	int32 sqr()
	{
		int32 square = X * X + Y * Y;
		return square;
	}
};

FORCEINLINE FLogicVec2D FLogicVec2D::operator-(const FLogicVec2D& V) const
{
	return FLogicVec2D(X - V.X, Y - V.Y);
}

FORCEINLINE FLogicVec2D FLogicVec2D::operator+(const FLogicVec2D& V) const
{
	return FLogicVec2D(X + V.X, Y + V.Y);
}

FORCEINLINE FLogicVec2D FLogicVec2D::operator-(const int32& a) const
{
	return FLogicVec2D(X - a, Y - a);
}

FORCEINLINE FLogicVec2D FLogicVec2D::operator+(const int32& a) const
{
	return FLogicVec2D(X + a, Y + a);
}

FORCEINLINE FLogicVec2D FLogicVec2D::operator/(const int32& a) const
{
	return FLogicVec2D(X / a, Y / a);
}

FORCEINLINE FLogicVec2D FLogicVec2D::operator*(const int32& a) const
{
	return FLogicVec2D(X*a, Y*a);
}

FORCEINLINE bool FLogicVec2D::operator==(const FLogicVec2D& V) const
{
	if (X == V.X && Y == V.Y) return true;
	else return false;
}

FORCEINLINE bool FLogicVec2D::operator!=(const FLogicVec2D& V) const
{
	if (X != V.X || Y != V.Y) return true;
	else return false;
}

UENUM(BlueprintType)
enum class EPhysGeoType : uint8
{
	PGT_NULL,
	PGT_Actor,
	PGT_Point,
	PGT_Line,
	PGT_Poly,
	PGT_DetonationActor,
};

UENUM(BlueprintType)
enum class ESkillEffectType : uint8
{
	SET_NULL,
	SET_Heal,
	SET_Hurt,
	SET_NegativeHurt,
	SET_PositiveProtect,
};

UENUM(BlueprintType)
enum class EPointType : uint8
{
	PT_NULL,
	PT_ZiDan,
	PT_DaoDan,
};

UENUM(BlueprintType)
enum class EReactionType : uint8
{
	PRT_NULL,
	PRT_Transform,
	PRT_ReflectRefract,
	PRT_BlockLine,
	PRT_AddTag,
	PRT_SubtractTag,
};

UENUM(BlueprintType, Blueprintable)
enum class ECharacterIdleMotionType : uint8
{
	CHAMT_NULL,
	CHAMT_HoldWeapon,
	CHAMT_HoldBySingleHand,
	CHAMT_HoldByBothHands,
	CHAMT_LiftByBothHands,
};

UENUM(BlueprintType, Blueprintable)
enum class ECharacterAtkRange : uint8
{
	CAR_NULL,
	CAR_Melee,
	CAR_Middle,
	CAR_Far,
	CAR_SuperFar
};

UENUM(BlueprintType, Blueprintable)
enum class ECharacterThinkMode : uint8
{
	CTM_RandomAtk,
	CTM_DefendDefaultLoc,
	CTM_PlayerHunter,
	CTM_StrongholdDestroyer,
	CTM_Patrol
};

USTRUCT()
struct FIntGroup
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	TArray<int32> group;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEntityPair
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 entityID1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 entityID2;

	FEntityPair()
	{
		entityID1 = 0;
		entityID2 = 0;
	}

	FEntityPair(int32 x, int32 y)
	{
		entityID1 = x;
		entityID2 = y;
	}

	bool IsExist(int32 id1, int32 id2)
	{
		if ((entityID1 == id1 && entityID2 == id2)||
			(entityID2 == id1 && entityID1 == id2))
			return true;
		else return false;
	}
};

USTRUCT()
struct FVectorPair
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		bool test;

	UPROPERTY()
		FVector v1;

	UPROPERTY()
		FVector v2;
};

USTRUCT()
struct FDynamicLoadBPInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TSubclassOf<class UObject> BPClass;

	UPROPERTY()
	FString className;

	UPROPERTY()
	FVector spawnLoc;

	UPROPERTY()
	FRotator spawnRot;

	FDynamicLoadBPInfo()
	{
		
	}

	FDynamicLoadBPInfo(FString clsName, FVector loc, FRotator rot)
	{
		className = clsName;
		spawnLoc = loc;
		spawnRot = rot;
	}
};

USTRUCT()
struct FActorPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	EPointType pointType;

	UPROPERTY()
	TSubclassOf<class UObject> m_BPPointClass;

	UPROPERTY()
	FString pointName;

	UPROPERTY()
	FString pathName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FReactionInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	EReactionType reactionType;

	UPROPERTY(BlueprintReadWrite)
	int32 reactionNb;

	UPROPERTY(BlueprintReadWrite)
	FName HostTag;

	UPROPERTY(BlueprintReadWrite)
	FName reactionTag;

	UPROPERTY(BlueprintReadWrite)
	FString spawnActorClassName;

	UPROPERTY(BlueprintReadWrite)
	FString transformActor1ClassName;

	UPROPERTY(BlueprintReadWrite)
	FString transformActor2ClassName;

	UPROPERTY(BlueprintReadWrite)
	UClass* BPSpawnActorClass;

	UPROPERTY(BlueprintReadWrite)
	UClass* BPTransformActor1Class;

	UPROPERTY(BlueprintReadWrite)
	UClass* BPTransformActor2Class;

	UPROPERTY(BlueprintReadWrite)
	FName modifyTag1;

	UPROPERTY(BlueprintReadWrite)
	FName modifyTag2;

	FReactionInfo()
	{
		reactionType = EReactionType::PRT_NULL;
	}

};

USTRUCT(BlueprintType, Blueprintable)
struct FHistoryEvent
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		FString eventName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
		TArray<FItem> itemCost;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 faithCost;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	int32 supplyCost;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Game/Battle")
	TArray<int32> eventCode;

	FHistoryEvent()
	{
		eventName = "NULL";
		faithCost = 0;
		supplyCost = 0;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FSkillIndependentFXInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		UParticleSystem* particleSystem;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	FVector loc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	FRotator rot;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	FVector scale;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	bool isPermanent;
};

USTRUCT(BlueprintType, Blueprintable)
struct FJudgeInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TArray<int32> availableJudgeColors = {0,1,2,3};

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		TArray<int32> availableJudgeNbs = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
};

USTRUCT(BlueprintType, Blueprintable)
struct FFoundationCharacterConsumeInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
	TMap<int32, int32> hurtLevelConsumptionMap;
};

USTRUCT(BlueprintType, Blueprintable)
struct FFoundationCharacterOccupyInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar/Game/Battle")
		int32 characterOccupationRadius;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterHurtScoreAmplifiedInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 level;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 amplifiedCoe;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterHurtScoreInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> hurtTimes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<int32> surviveTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> scoreLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 characterLevel;
};

USTRUCT(BlueprintType, Blueprintable)
struct FHurtTypeAndValueInfo
{
	GENERATED_USTRUCT_BODY()

		/** 伤害种类
		* 0 - 普通攻击伤害
		* 1 - 附加伤害
		* 2 - 反击伤害
		*/
		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		uint8 hurtType = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 hurtVal = 0;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSkillUnlockInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar/Common")
		FString skillName;

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 unlockPointNb;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TMap<uint8, int32> unlockAttributeValueMap;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterSkillAvailableInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString skillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString chSkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString combineKeyList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 mutationType = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TSubclassOf<class UBaseSkill> skillClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString skillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chSkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	uint8 skillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<uint8> attributeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool isInitial;
};

USTRUCT(BlueprintType, Blueprintable)
struct FFoundationCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString foundationCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chFoundationCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 constructionTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		TSubclassOf<class AActor> characterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	UParticleSystem* pPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FFoundationCharacterOccupyInfo occupyInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FFoundationCharacterConsumeInfo consumeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString chDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 inputNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 outputNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool isInitial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 unlockPoints;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterAppearanceInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString characterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString appearanceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chAppearanceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 unlockPt;
};

USTRUCT(BlueprintType, Blueprintable)
struct FStateCardInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString cardName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString chCardName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FString description;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FString chDescription;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	uint8 cardType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTexture* pTexture;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FColor color;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 level;
};

USTRUCT(BlueprintType, Blueprintable)
struct FItemCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString cardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chCardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chDescription;

	/** 卡牌类型
	* 1 - 蛰伏卡牌
	* 2 - 可使用道具卡
	* 3 - 计时销毁卡牌
	* 4 - 自动合成 + 倒计时销毁卡牌
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		uint8 cardType;

	//用于描述此张卡牌的具体作用数值，例如兽类感染是让所有兽类角色加上WoodWeak效果，效果的数值由此获得
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FEffectParams cardEffectParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FColor color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxCardNb = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TSubclassOf<class UCharacterEquipInfo> equipClass;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString effectName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FItemCardCondition
{
	GENERATED_USTRUCT_BODY()
public:
	FString cardName;

	uint8 cardType;

	int32 curTick;

	bool isDead = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCardCombineInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString combineName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString chCombineName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 inputNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> inputList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> outputList;

	/** 合成类型
	* 0 - 对自身有利祭坛
	* 1 - 对敌人祭坛
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString triggerFCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TMap<int32, int32> cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isInitial;
};

USTRUCT(BlueprintType, Blueprintable)
struct FFCSpawnEffectPSInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString cardCombineName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystem* pFCSpawnEffectPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystem* pFCSelfSpawnEffectPS;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterItemList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<USkeletalMesh*> pItemMeshList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterSKComponentInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	USkeletalMeshComponent* pComponent;

	/** 标记组件类别
	* 0 - 普通组件
	* 1 - Cloth组件
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 componentType;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTutorialStep : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString operationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString chExplanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString enExplanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isSpawnIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FVector indicatorRelativeLoc;

	bool isDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString spawnIndicationActorName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FAppendPSInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		UParticleSystem* pPS;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FVector relativeLoc;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDiceBattleAndTheorizeSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString skillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chSkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString skillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		FString chSkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
		bool isInitial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FString functionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<int32> values;
};

UCLASS()
class COLLISIONWAR_API UCollisionWarBpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	//UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
		//static void SavePlayerInfo(APlayerInfo* pPlayerInfo);

	static UCollisionWarSingleton* GetGlobalSingleton(bool& IsValid);

	static void IntBigAdd(TArray<int32> a, TArray<int32> b, TArray<int32>& c, uint8 aSym, uint8 bSym, uint8& sym);

	static void IntBigSub(TArray<int32> a, TArray<int32> b, TArray<int32>& c, uint8 aSym, uint8 bSym, uint8& sym);

	static void IntBigMul(int32 a, int32 b, TArray<int32>& c, uint8& symbol);

	static int32 IntBigDiv(TArray<int32>& a, int32 b , uint8 aSymbol);

	static int32 IntSqrt(int32 n);

	static int32 GetLogicVecSize(const FLogicVec2D& vec);

	static FLogicVec2D NormalizeLogicVecToPositiveScale(const FLogicVec2D& originVec,const int32& scale);

	static bool IsSegmentsIntersect_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3, FLogicVec2D pt4);

	//现实中的顺时针为正，逆时针为负
	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static float GetDirectionOfPointToSegment(FVector2D pt1, FVector2D pt2, FVector2D pt3);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static int32 GetDirectionOfPointToSegment_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static bool TellWhetherPointInsideConvex_Int(TArray<FLogicVec2D> pts, FLogicVec2D pt);

	static bool IsPointInRectDefineByTwoPoints_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3);

	static int32 GetDisOfPointToLine_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3);

	static float GetDisFromPointToPoint(FVector2D pt1, FVector2D pt2);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static int32 GetDisFromPointToPoint_Int(FLogicVec2D pt1, FLogicVec2D pt2);

	UFUNCTION()
	static float GetExpandCosAngleOfTwoVector(FVector2D v1, FVector2D v2);

	static FLogicVec2D GetLogicVecByYaw_Int(int32 yaw);

	static float GetYawFromLogicVec(FVector2D vec);

	UFUNCTION()
	static bool GetInteractionOfTwoLines_Int(FLogicVec2D line1Pt1, FLogicVec2D line1Pt2, FLogicVec2D line2Pt1, FLogicVec2D line2Pt2, FLogicVec2D& interaction);

	//alpha是弧度
	UFUNCTION()
	static FLogicVec2D GetPtRotateAroundPtByAlpha_Int(FLogicVec2D rotatePt, FLogicVec2D origine, int32 alpha);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static FVector2D GetCenterPt(TArray<FVector2D> pts);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static FLogicVec2D GetCenterPt_Int(TArray<FLogicVec2D> pts);

	static void SortPointsClockwise_Int(TArray<FLogicVec2D>& pts);

	static bool GetPointSymmetryToLine_Int(FLogicVec2D linePt1, FLogicVec2D linePt2, FLogicVec2D pt, FLogicVec2D& symmetryPt);

	/*UFUNCTION()
	static void GetReflectDirWithDirAndBaseLine_Int(FLogicVec3D originDir, FLogicVec2D baseLinePt1, FLogicVec2D baseLinePt2, FLogicVec3D& reflectDir);*/

	UFUNCTION()
	static void GetNormalLine_Int(FLogicVec2D footPt, FLogicVec2D baseLinePt1, FLogicVec2D baseLinePt2, FLogicVec3D& line);
	UFUNCTION()
	static void DynamicUpdateBox(FVector startPt, FVector endPt, FVector& newWorldLoc,
	float& newLineLengthHalf, FRotator& newWorldRotator);

	/*static bool GetReflectPointWithDirAndBaseLine_Int(FLogicVec2D originPt, FLogicVec2D dir, FLogicVec2D baseLinePt1,
		FLogicVec2D baseLinePt2, FLogicVec2D& reflectPoint, FLogicVec2D& interPt);*/
	static bool GetReflectVectorWithDirAndNormalVector(const FVector2D& originVec, const FVector2D& normalVec, FVector2D& reflectVec);

	static bool AreTwoLinesParallel_Int(FLogicVec2D line1Pt1, FLogicVec2D line1Pt2, FLogicVec2D line2Pt1, FLogicVec2D line2Pt2);

	UFUNCTION()
	static bool GetCOCAndRadiusFromThreePoints_Int(FLogicVec2D pt1, FLogicVec2D pt2, FLogicVec2D pt3, FLogicVec2D& coc, int32& r);

	static bool GetInterPtOfSegmentAndCircle_Int(FLogicVec2D coc, int32 r, FLogicVec2D segmentPt1, FLogicVec2D segmentPt2, TArray<FLogicVec2D>& interPt);

	static bool GetFirstInterPtOfSegmentAndCircle_Int(FLogicVec2D coc, int32 r, FLogicVec2D segmentPt1, FLogicVec2D segmentPt2, FLogicVec2D& interPt);

	static bool IsPointPolyIntercept(const TArray<FLogicVec2D>& polyPoints, const FLogicVec2D& logicPos, const bool& isCircular, const int32& pointRadius);

	static bool IsPointLineIntercept(const FLogicVec2D& lineStartPoint, const FLogicVec2D& lineEndPoint, const FLogicVec2D& logicPos, const int32& pointRadius);

	static bool IsPointPointIntercept(const FLogicVec2D& pt1Loc, const int32& pt1Radius, const FLogicVec2D& pt2Loc, const int32 pt2Radius);

	static bool IsLinePolyIntercept(const FLogicVec2D& startPoint, const FLogicVec2D& endPoint, const TArray<FLogicVec2D>& polyPts, const int32& errorTolerance);

	//static bool IsLineActorIntercept(const FLogicVec2D& linePt1, const FLogicVec2D& linePt2, const FLogicVec2D& pt3, const int32& actorRadius, const int32& errorTolerance);

	static bool IsPolyPolyIntercept(const TArray<FLogicVec2D>& polyPoints1, const TArray<FLogicVec2D>& polyPoints2);

	static bool IsPolyCircleIntercept(const TArray<FLogicVec2D>& polyPoints,const FLogicVec2D& centerPt, const int32& radius);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static UTexture2D* GetTextureFromName(const FString& actorName, const FString& typeName);

	static UClass* GetAttachEquipBlueprintClassDynamic(FString className);

	static FVector2D GetMouseScreenPosition(APlayerController* pController);

	static XMLElement* SearchXMLNodeByAttribute(XMLElement* pSourceNode, FString targetNodeName, FString targetNodeAttribute, FString attributeValue);

	static XMLElement* SearchXMLNodeByContent(XMLElement* pSourceNode, FString targetNodeName, FString content);

	static XMLElement* GetXMLFirstWorksheetNode(XMLElement* pSourceNode);

	static XMLElement* GetXMLRowByContentFromTableNode(XMLElement* pTableNode, FString content);

	UFUNCTION()
	static bool IsStringArrayContaintString(TArray<FString> strings, FString string);

	static FVector2D GetVectorByBreakComma(FString string);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static	void LoadPlayerInfo(FString playerName, TArray<FString>& kingCharacterTypes);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static void PushStringIntoArray(FString str, TArray<FString>& stringArray);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static void AppendStringListToStringList(TArray<FString>& newList, TArray<FString>& originalList);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static void CopyReactionInfo(FReactionInfo copyInfo, FReactionInfo& targetInfo);

	static int32 LogicCos(int32 angle);

	static int32 LogicSin(int32 angle);

	static int32 CheckACosList(const TArray<int32>& list, const int32& target, int32 head, int32 end);

	static int32 LogicACos(int32 expandCos);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Common")
	static int32 CalExpByLevel(const int32& K, const int32& N, const int32& C, const int32& level);
};
