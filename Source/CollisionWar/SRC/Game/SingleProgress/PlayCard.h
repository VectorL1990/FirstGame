// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Base/CollisionWarGameInstance.h"
#include "ShadowActor.h"
#include "OverallIndexDemoActor.h"
#include "PlayCard.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FActionTransformInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 upperLimint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 action;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventDescription
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString textList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chTextList;

	FEventDescription()
	{}
};

USTRUCT(BlueprintType, Blueprintable)
struct FSectionDescription
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> strings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FEventDescription> descriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isReturnCard;

	FSectionDescription()
	{}
};

USTRUCT(BlueprintType, Blueprintable)
struct FOutputCardInfo
{
	GENERATED_USTRUCT_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 nb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		uint8 color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString cardName;

	FOutputCardInfo()
	{
		nb = -1;
		color = 0;
	}

	FOutputCardInfo(int32 num, uint8 cardColor)
	{
		nb = num;
		color = cardColor;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FPassiveEventInfo
{
	GENERATED_USTRUCT_BODY()
public:
	//������ǰ���¼�������̽�����ɽ���ܴ���6�����Χ�����¼�����ǰ���Ƿ����˱���ѩ�¼�
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> preconditionEvents;

	//�����ı���ʱ�䣬����Χ���¼������ڵ�ǰ�ؿ��Ѿ�������һ�����ϲſ��ܱ�����
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float progress;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> possibleEventList;

	//�жϸ��¼��Ĵ������ʣ�ϵͳ����0~100֮�����һ����������activateBound��Χ�ڣ��򴥷����¼�
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 activateBound;

	bool happenFlag = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventFunctionInfo
{
	GENERATED_USTRUCT_BODY()
public:
	//������ǰ���¼�������̽�����ɽ���ܴ���6�����Χ�����¼�����ǰ���Ƿ����˱���ѩ�¼�
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString eventName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<int32> functionValues;

};

USTRUCT(BlueprintType, Blueprintable)
struct FDiceBattleInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 difficulty;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 targetScore;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 originLife;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 maxFlipTime;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float maxAvailableTimePerRound;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float demoTime;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 diceCardColNb;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDiceBattleSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString skillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isInitial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<uint8> activateColorList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> activateNbList;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTheorizeInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 difficulty;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 targetScore;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 life;
};

USTRUCT(BlueprintType, Blueprintable)
struct FDrawCardInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 drawCardNb;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 trialTimes;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCardShopInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> possibleShopCards;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 availableCardPercent;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	bool isServe;
};

USTRUCT(BlueprintType, Blueprintable)
struct FTransformOutputStruct
{
	GENERATED_USTRUCT_BODY()
public:
		//��������ռȨ�أ�����̽�����ܼ񵽱��Ҳ�п�����������ս����ôÿ�������Ȩ�ؼ������ǲ�һ����
		UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 weight;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FSectionDescription> choiceSubsidiaryTags;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FOutputCardInfo> outputCardInfo;

	/** ���������ϳɵĽ������
	* 0 - ��ͨ�ϳ�
	* 1 - Choices��ѡ�����
	* 2 - ս������
	* 3 - �Ĳ�����
	* 4 - ����
	* 5 - ���ֺϳ�
	* 6 - ս��
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 transformType;

	//��ƴ��ʧ�ܣ���������սս�ܴ������¼����ƣ�������
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FEventFunctionInfo> successEventName;
	
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 timeConsumingLevel;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FPassiveEventInfo> passiveEvents;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	bool isOnlyOneTime = false;

	FString curPassiveEventName;
};

USTRUCT(BlueprintType, Blueprintable)
struct FChAndEnDescription : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString enDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chDescription;

};

USTRUCT(BlueprintType, Blueprintable)
struct FCardDurabilityInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FString cardName;

	UPROPERTY()
		int32 durability;

};

USTRUCT(BlueprintType, Blueprintable)
struct FCardTransformInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//һ�ſ��ƿ����ж��ֺϳɿ��ܣ�����������鵽�ϳ��У����Ժϳ����»�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FOverallIndexValueInfo cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FSectionDescription> subsidiaryTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FTransformOutputStruct> possibleOutputList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FDiceBattleInfo diceInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FTheorizeInfo theorizeInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FDrawCardInfo m_drawCardInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FCardShopInfo m_cardShopInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FBattleInfo battleInfo;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString transformName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 curOutputNb = -1;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCardDurabilityInfo> returnCardNames;

	/** ����ת�����ͣ�������ActionCard���Ķ��屣��һ��
	* 0 - �ж��ϳ�
	* 1 - ̽��
	* 2 - ����
	* 3 - ����
	* 4 - �о�
	* 5 - ��ͨ�¼�
	* 6 - ս���¼����ɱ
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 actionType;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FChAndEnDescription overview;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FChAndEnDescription description;

	FCardTransformInfo()
	{}

	void Reset()
	{
		subsidiaryTags.Empty();
		possibleOutputList.Empty();
		transformName = "";
		curOutputNb = -1;
		returnCardNames.Empty();
	}
};

USTRUCT()
struct FCardTransformGroup
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		TArray<FCardTransformInfo> group;

	UPROPERTY()
		int32 level;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCardTextureAndTags : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString cardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString chCardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	UTexture* pTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString applyFunction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> functionValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isInitial = false;

	/** ���õĳ���
	* 0 = ѩ�س���
	* 1 = ɳĮ����
	* 2 = �ֵ�
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 suitableSenarioNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 cardValueLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 cardSellValueLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FChAndEnDescription description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 durability = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxCardNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxFunctionNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isShadowActorCard = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FPossibleEventInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString eventName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float lastTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float weight;

	/** �������¼�������
	* 0 - �¼�һ��ʼ������������
	* 1 - �¼����е���������󷢶�
	*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 eventType;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FCardTransformInfo cardTransformInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> eventValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FChAndEnDescription overview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FChAndEnDescription description;

	UPROPERTY()
	float curTick;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventTriggerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 minMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxMentality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 minSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxSuppression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 minActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxActivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 minDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 maxDarkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 minFlameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxFlameFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 minSunFaith;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxSunFaith;
};

USTRUCT(BlueprintType, Blueprintable)
struct FEndInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FEventTriggerInfo triggerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> chTexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> enTexts;
};


USTRUCT(BlueprintType, Blueprintable)
struct FEventGroupInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString eventGroupName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> prerequisiteEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FString> prerequisiteCardNames;

	UPROPERTY()
	float curTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FPossibleEventInfo> possibleEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isOccurOnce = false;

	/** ����¼�������
	* 0 = ���ڴ����¼����籩��ѩ
	* 1 = Ǳ���¼����緢�������ֻ����һ�ε��¼�
	* 2 = ��ʼ�¼�����һ��ʼ������
	* 3 = �����������¼�����
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 groupType = 0;

	UPROPERTY()
	bool isEventDone = false;

	UPROPERTY()
	int32 curEventNb = -1;

	UPROPERTY()
	int32 eventCode = -1;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterCommunicationReward
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> possibleOutputs;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> dialogs;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<int32> outputProbability;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterLikeability : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString characterName;

	int32 likeability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 communicateDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 judgeTimes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> hobbies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> likeabilityLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<FCharacterCommunicationReward> rewards;
};

USTRUCT(BlueprintType, Blueprintable)
struct FNormalCardSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FVector loc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString cardName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 nb;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 color;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	int32 durability;
};

USTRUCT(BlueprintType, Blueprintable)
struct FNumericCardSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FVector loc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 nb;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		uint8 color;
};

USTRUCT(BlueprintType, Blueprintable)
struct FActionCardSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FVector loc;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString cardName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float curLoadTime;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	float maxLoadTime;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FCardTransformInfo curTransformInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TArray<FString> returnCardNameList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	uint8 actionState;
};

USTRUCT(BlueprintType, Blueprintable)
struct FOneTimeCardTransformSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FString name;

	UPROPERTY()
	int32 outputNb;

	UPROPERTY()
	uint8 actionType;

	FOneTimeCardTransformSaveInfo()
	{
	}

	FOneTimeCardTransformSaveInfo(FString na, int32 nb, uint8 at)
	{
		name = na;
		outputNb = nb;
		actionType = at;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventCodeNameSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FString name;

	UPROPERTY()
		int32 code;

	FEventCodeNameSaveInfo()
	{
	}

	FEventCodeNameSaveInfo(FString na, int32 nb)
	{
		name = na;
		code = nb;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventGroupSaveInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		FString eventGroupName;

	UPROPERTY()
		float curTick;

	UPROPERTY()
		bool isEventDone = false;

	UPROPERTY()
		int32 curEventNb = -1;

	UPROPERTY()
		int32 eventCode = -1;

	UPROPERTY()
	float curPossibleEventTick;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelUpradeInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 exp;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSPCardCombineDemoInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TSubclassOf<class AOverallIndexDemoActor> pDemoActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	UParticleSystem* pDemoPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	float demoTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FVector actorRelativeLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FVector PSRelativeLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> enDemoWords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		TArray<FString> chDemoWords;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSPCardCombineDemoTimingInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		AActor* pActor = NULL;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		UParticleSystemComponent* pActorSurfacePSComponent;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		UParticleSystemComponent* pDemoPSComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		float curTime;

	bool needToDeletePS = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCardFunctionInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
	FString cardName;

	UPROPERTY()
	FString functionName;

	UPROPERTY()
	TArray<int32> functionValues;

	UPROPERTY()
	float maxTime;

	UPROPERTY()
	float curTime;
};

USTRUCT(BlueprintType, Blueprintable)
struct FRangeMissionOverallIndexInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 minIndex;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 maxIndex;
};

USTRUCT(BlueprintType, Blueprintable)
struct FMissionOverallIndexInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TMap<uint8, FRangeMissionOverallIndexInfo> missionIndex;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSPMissionListInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	uint8 progressNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	FString missionGroupName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<FMissionOverallIndexInfo> missionIndexList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<int32> keyFrames;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<FString> chDescription;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<FString> enDescription;

	void Reset()
	{
		missionIndexList.Empty();
		keyFrames.Empty();
		chDescription.Empty();
		enDescription.Empty();
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FOverallIndexExtraFunInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FString cardName;

	UPROPERTY()
		FString functionName;

	UPROPERTY()
		TArray<int32> values;

	UPROPERTY()
		int32 duration;

	UPROPERTY()
		int32 interval;

	UPROPERTY()
		int32 curIntervalTick = 0;

	UPROPERTY()
		int32 curTick = 0;
};

USTRUCT(BlueprintType, Blueprintable)
struct FSPDecipherParamInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 flipCardNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 cardNbPerRound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxBetTimes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxResetTimes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 maxCardNb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
		int32 targetScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	TArray<int32> bonusLevels;
};


UCLASS()
class COLLISIONWAR_API APlayCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyInitialCard(const FString& cardType, const FString& cardName, int32 cardNb);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void SetupPlayCard(UStaticMeshComponent* pBaseMesh, UTextRenderComponent* pText, UStaticMeshComponent* pCardImageMesh, 
		UStaticMeshComponent* pColorImageMesh, UTextRenderComponent* pNbText);
	
	virtual void InitialPlayCard(uint8 cardType, int32 nb, uint8 color, FString cardName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void MoveToLocation(FVector loc, bool isFlip);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void CardShowUp(FVector targetLoc, bool isFlip);

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void CardDisappear();

	UFUNCTION()
	void TurnCard();

	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void ReadCardName(const FString& enName);

	UFUNCTION(BlueprintCallable, Category = "CollisionWar")
	void HideCard();

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	UTextRenderComponent* m_pLTTextComponent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isMove = false;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	bool m_isFlip = true;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FVector m_targetLoc;

	/*UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FVector m_loc;*/

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_moveSpeed = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_rotateSpeed = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	float m_tolerance = 0.01f;

	bool m_canTick = true;

	/************************************************************************/
	/* ���ƻ�����Ϣ
	/************************************************************************/
	UPROPERTY()
	UStaticMeshComponent* m_pBaseMesh;

	UPROPERTY()
	UStaticMeshComponent* m_pCardImageMesh;

	UPROPERTY()
	UTextRenderComponent* m_pCardName;

	UPROPERTY()
		UStaticMeshComponent* m_pColorImageMesh;

	UPROPERTY()
		UTextRenderComponent* m_pCardNbText;

	/** ��ǿ�������
	* 0 - ������
	* 1 - ��ͨ��
	* 2 - �ж���
	*/
	uint8 m_cardType;

	FString m_cardName;

	TArray<FString> m_tags;

	FString m_cardFunction;

	TArray<int32> m_functionValues;

	bool m_isDead = false;

	int32 m_durability = -1;

	int32 m_nb;

	uint8 m_color;
	/************************************************************************/
	/* ���Ʒ�����������
	/************************************************************************/
	UFUNCTION(BlueprintNativeEvent, Category = "CollisionWar")
	void NotifyChangeState(uint8 state);

	bool IsSatisfyTags(TArray<FString> tags);
	/************************************************************************/
	/* ���䲿��
	/************************************************************************/
	bool m_isInSkillState;

	float m_skillCountDown = 0.f;
};
