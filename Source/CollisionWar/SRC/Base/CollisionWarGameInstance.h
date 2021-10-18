// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "Core.h"
#include "ThreadingBase.h"
#include "../ThirdParty/tinyxml2.h"
#include "../../../../Plugins/KBEnginePlugins/Source/KBEnginePlugins/Scripts/TransferStructs.h"
#include "CollisionWarGameInstance.generated.h"

using namespace std;
using namespace tinyxml2;
/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterGroupSpawnInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		FString characterGroupName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 Nb;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterGroupSpawnInfoList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
	TArray<FCharacterGroupSpawnInfo> list;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBattleEventInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FString> possibleEventNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 frameNb;
};

//����ṹ���ڼ�¼ÿ��Σ���еȼ���Ӧ�ĸ���������������
USTRUCT(BlueprintType, Blueprintable)
struct FGradingEnermySpawnInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<int32> levelList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<int32> groupNbList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		int32 grade;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPossibleCharacterGroupList
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Widget")
		TArray<FCharacterGroupSpawnInfoList> possibleList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBattleInfo
{
	GENERATED_USTRUCT_BODY()
public:
	/** ���ս���ĵȼ�
	* 0 = ��ͨս��
	* 1 = �¼���ս�������ϴ���ս������ͨս��Ҫ��λ���¼���ս��
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 battleLevelType;

	/** ս��������
	* 0 = ��ʱ����ս
	* 1 = ��ʱ����ս
	* 2 = ����ս
	* 3 = Ŀ���ɱս
	* 4 = Ŀ�������ռ�
	* 5 = Enermy patrol battle
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 battleType = 5;

	/** how enermy is spawned
	* 0 - by interval, which means enermies will be spawned by interval
	* 1 - enermies will be spawned when previous round enermies are killed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 updateEnermyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 targetKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 targetScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString targetKillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> specifiedLandBlockNameList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> targetCollectNameList;

	/** �����ĳһ�ֱ������ɵĵ��������ƣ�����<0,"SkeletonSoldier_1">��ʾ��һ�ֱ�������һ��SkeletonSoldier_1
	* �����Զ����ɵĵ��������������̶�������ʣ���������ȥ�Զ�����
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FPossibleCharacterGroupList> fixEnermyGroupGradeList;

	/** ���ÿ�ֱ������ɵĵ���������û�б�ǵ����������Զ����ɱ�׼����
	*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FGradingEnermySpawnInfo> fixGradingList;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 firstPeakInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 peakInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> intervalList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 firstMiniPeakInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 miniPeakInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxPeakNb;

	/** ���ս���п��ܳ��ֵ��¼�����
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FBattleEventInfo> eventList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString chDescription;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterAttributeInfo
{
	GENERATED_USTRUCT_BODY()
public:
	/** ���ս���ĵȼ�
	* 0 = ��ͨս��
	* 1 = �¼���ս�������ϴ���ս������ͨս��Ҫ��λ���¼���ս��
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxAtk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxDfc;

	FCharacterAttributeInfo()
	{
		maxLife = 0;
		maxAtk = 0;
		maxDfc = 0;
	}

	FCharacterAttributeInfo(int32 life, int32 atk, int32 dfc)
	{
		maxLife = life;
		maxAtk = atk;
		maxDfc = dfc;
	}
};

UCLASS()
class COLLISIONWAR_API UCollisionWarGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UCollisionWarGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar/Base")
	void ServerTravelByLevelName(FString levelName);

	/************************************************************************/
	/* һ����Ϣ                                                                     */
	/************************************************************************/
	UPROPERTY()
	int32 m_playerID;
	
	UPROPERTY()
	int32 m_accountEntityID;
	
	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base")
	FPlayerInfo m_playerInfo;

	UPROPERTY(BlueprintReadOnly, Category = "CollisionWar/Base")
	FGoodsList m_goodsList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/Base")
	FString m_accountStatus = "NULL";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<int32> m_cosExpandList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	TArray<int32> m_intSqrtList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Common")
	FString m_language = "Chinese";

	/************************************************************************/
	/* �ж��ܷ����ս���ı���                                                                     */
	/************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool m_hasRecievePlayerAssignNbInBattle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool m_hasRecieveAllPlayerAssignNbs = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool m_hasRecievePlayerInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool m_hasRecieveMallInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	bool m_hasCSEnterWorld = false;

	/************************************************************************/
	/* ս����ر���                                                                     */
	/************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	int32 m_playerAssignNbInBattle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FPlayerRoletypeAssignnumList m_playerInfosInBattle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/Common")
	FBattleResult m_battleResult;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/Common")
	FBattleInfo m_battleInfo;

	UPROPERTY()
	TArray<FString> m_eventBattleReturnCards;

	uint8 m_battleState;

	int32 m_totalBattleScore = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString, int32> m_attributeIncreaseValueMap;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
		TMap<FString, int32> m_attributeIncreaseMaxValueMap;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 m_chopSkillMutationType = -1;

	/** Weather conditions
	 * 0 - rain
	 * 1 - special
	 * 2 - Wind
	 * 3 - Magic
	 */
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	uint8 m_weatherType;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	bool m_dayOrNight;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<int32, int32> m_skillCapcity;
	/************************************************************************/
	/* SingleProgress Variables
	/************************************************************************/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FPlayerSingleProgressInfo> m_playerSingleProgressInfos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CollisionWar")
	FPlayerSingleProgressInfo m_curPlayerSPInfo;

	UPROPERTY()
	TArray<FString> m_doneTutorialSteps;

	UPROPERTY()
	TArray<FString> m_inheritCardNames;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Login")
		TMap<FString, float> m_sliderOptionPercent;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar/Game/Login")
		TMap<FString, FString> m_comboboxOption;
};
