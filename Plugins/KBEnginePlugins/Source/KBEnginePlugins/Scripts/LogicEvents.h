// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"
#include "Engine/KBEvent.h"
#include "Engine/KBETypes.h"
#include "TransferStructs.h"
#include "LogicEvents.generated.h"

/**
	所有由逻辑层产生的事件都在这里定义
*/



UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqLoadLevelModelList : public UKBEventData
{
	GENERATED_BODY()
public:

};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLevelModelList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FLevelModelList levelModelList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLevelInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerSpawnPointList playerSpawnPointList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FEnermySpawnGroupList enermySpawnGroupList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPhysActorSpawnList physActorSpawnList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FSpecialFrameList specialFrameList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLogonStatus : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString accountStatus;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString curMatchingLevelName;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchBuyResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isSuccessful;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 moneyB;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 goodsType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString goodsName;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMallInfoList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FGoodsList goodsList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchRankList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FAllRankList allRankList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchPlayerInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerInfo playerInfo;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 accountEntityID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqPlayerInfo : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqMallInfoList : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchReadLevelResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool readSuccessOrNot;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchGeneralCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalCharacterNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalPolyNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalLineNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalPointNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalActorNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalReactionPairNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalEnermyGroupNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString gameProgress = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curRandSeed;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchCharacterCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FCharacterCorrectInfo characterCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchPolyCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPhysPolyInfo polyCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLineCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPhysLineInfo lineCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchPointCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPhysPointInfo pointCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchActorCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPhysActorInfo actorCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchReactionPairCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FReactionPairInfo reactionPairCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchGroupCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FEnermyGroupCorrectInfo enermyGroupCorrectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchEndCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchStopUploadCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchNextRound : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 roundNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> winTeamList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchBattleEnd : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> winTeamList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FBattleResult battleResult;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMatchResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString matchResult;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 playerAssignNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roomType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerTagInfoList playerTagList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchAllPlayerRoletypeAndAssignNb : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 playerID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerRoletypeAssignnumList playerRoletypeAssignnumList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FBattleResult battleResult;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 maxFrameNb;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_gameDevelopFun : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString developInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqSimpleSingleMatch : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString mapType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roleType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqSingleMatch : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString mapType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString roleType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqOneOneMatch : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString mapType;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString roleType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqCancelMatch : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqLevelInfos : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roomType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqEnsureEnterRoom : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqTellRoomIsReady : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMainMachine : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool assignResult;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLogicFrame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FLogicFrame logicFrame;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMakeUpFrames : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FLogicFrameList logicFrames;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadAIOperationList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FAICharacterOperationList AICharacterOperationList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadFrame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 lastFrameNb;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadOperation : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerOperationInfo playerOperationInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqMakeUpFrames : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 startFrameNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 endFrameNb;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:

};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqTellRoundEnd : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FBattleResultRound battleResultRound;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqExitBattle : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqTellRoomResetDone : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqStartUploadCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalCharacterNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 totalPolyNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalLineNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalPointNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalActorNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalPairNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalGroupNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString gameProgress;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 randSeed;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadCharacterCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FCharacterCorrectInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadPolyCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPhysPolyInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadLineCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPhysLineInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadPointCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPhysPointInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadActorCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPhysActorInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadReactionPairCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FReactionPairInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadEnermyGroupCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FEnermyGroupCorrectInfo info;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqUploadEndCorrectInfo : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchRelogonInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 playerID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerRoletypeAssignnumList list;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FBattleResult result;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 assignNbInBattle;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString battleType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchRelogonPlayerInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerInfo info;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 accountEntityID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FGoodsList list;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchPlayerTagInfoList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPlayerTagInfoList list;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchAddFriendRequestResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool result;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchAddFriendRequest : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString name;

		uint64 applierDBID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchDisapproveAddFriendAnswer : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString name;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchApproveAddFriendAnswer : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString name;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerTagInfo playerTagInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchDeleteFriendRequestResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		bool result;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString deleteName;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqRelogonInfo : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchBattleStart : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 randSeed;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchCalPrizeResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 exp;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 constK;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 constN;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 constC;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curLevel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> prizeNameList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqRankList : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqPlayerTagInfoList : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> nameList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqAddFriend : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString friendName;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqDeleteFriend : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString friendName;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqAnswerAddFriendRequest : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool answer;

	uint64 applierDBID;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqFriendMatch : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FReqTeamMatchData hostData;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FString> friendNameList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString mapType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqAnswerFriendMatch : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool result;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString hostName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roleType = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 groupNb = 0;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchTeamMatchStatus : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString hostName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString message = "NULL";
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchTeamMatchInvitation : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hostEntityID;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString hostName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString matchType = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 groupNb;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqSendMessageToFriend : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString message = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString friendName = "NULL";
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchCancelMatch : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMatchStatus : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString status = "NULL";
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchLostRoundInfo : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FBattleResultRoundList list;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqLostRoundResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> lostRoundNbList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqChangeCurSelectCharacter : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roleType;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_reqTellLeaveWorld : public UKBEventData
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchMessageFromFriend : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString friendName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString message;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchAllRuneDataToClient : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FRuneInfoList runeInfoList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FRuneConfigInfoList runeConfigInfoList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchRuneConfigEffectToClient : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FRuneConfigEffectInfo runeConfigEffectInfo;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_dispatchHasConfigInfosToClient : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> hasRuneList;
};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_ReqAllRuneDataFromServer : public UKBEventData
{
	GENERATED_BODY()
public:

};

UCLASS(Blueprintable, BlueprintType)
class KBENGINEPLUGINS_API UKBEventData_ReqSetRuneConfigDataToServer : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString runeConfigName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 sky;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 ground;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 life;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 death;
};