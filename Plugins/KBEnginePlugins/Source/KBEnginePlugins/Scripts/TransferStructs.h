// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"
#include "Engine/KBETypes.h"
#include "TransferStructs.generated.h"

/**
	所有由逻辑层产生的事件都在这里定义
*/





USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 exp;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString characterName = "Lucian";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 level;

	void set(int32 e, FString name, int32 l, TArray<FString> skinInfo, 
		TArray<FString> weaponInfo, TArray<FString> gestureInfo)
	{
		exp = e;
		characterName = name;
		level = l;
	}

	void set_CHARACTER_INFO(CHARACTER_INFO characterInfo)
	{
		exp = characterInfo.exp;
		level = characterInfo.level;
		characterName = characterInfo.characterName;
	}
};

USTRUCT(BlueprintType)
struct FPlayerTagInfo
{
	GENERATED_USTRUCT_BODY()


		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString playerName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalBattleNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 totalWinNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString headShotName;

	void set_PLAYER_TAG_INFO(PLAYER_TAG_INFO playerTagInfo)
	{
		playerName = playerTagInfo.playerName;
		totalBattleNb = playerTagInfo.totalBattleNb;
		totalWinNb = playerTagInfo.totalWinNb;
		headShotName = playerTagInfo.headShotName;
	}
};

USTRUCT(BlueprintType)
struct FPlayerTagInfoList
{
	GENERATED_USTRUCT_BODY()


		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FPlayerTagInfo> playerTagInfoList;

	void set_PLAYER_TAG_INFO_LIST(PLAYER_TAG_INFO_LIST list)
	{
		for (int32 i=0; i<list.values.Num(); i++)
		{
			FPlayerTagInfo newInfo;
			newInfo.set_PLAYER_TAG_INFO(list.values[i]);
			playerTagInfoList.Add(newInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FFriendList
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> dbidList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPlayerTagInfo> playerTagInfoList;

	void set_FRIEND_LIST(FRIEND_LIST friendList)
	{
		for (int32 i=0; i<friendList.dbidList.Num(); i++)
		{
			FString dbid = FString::Printf(TEXT("%lld"), friendList.dbidList[i]);
			dbidList.Add(dbid);
		}
		for (int32 i=0; i<friendList.playerTagList.Num(); i++)
		{
			FPlayerTagInfo newInfo;
			newInfo.set_PLAYER_TAG_INFO(friendList.playerTagList[i]);
			playerTagInfoList.Add(newInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FRankOneMap
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString mapType = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 rank;

	void set_RANK_ONE_MAP(RANK_ONE_MAP rankOneMap)
	{
		mapType = rankOneMap.mapType;
		rank = rankOneMap.rank;
	}
};

USTRUCT(BlueprintType)
struct FPlayerAllRankList
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankOneMap> singleRankList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankOneMap> twoTwoRankList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankOneMap> threeThreeRankList;

	void set_PLAYER_ALL_RANK_LIST(PLAYER_ALL_RANK_LIST playerAllRankList)
	{
		for (int32 i=0; i<playerAllRankList.singleRankList.Num(); i++)
		{
			FRankOneMap newRankMap;
			newRankMap.set_RANK_ONE_MAP(playerAllRankList.singleRankList[i]);
			singleRankList.Add(newRankMap);
		}
		for (int32 i = 0; i < playerAllRankList.twoTwoRankList.Num(); i++)
		{
			FRankOneMap newRankMap;
			newRankMap.set_RANK_ONE_MAP(playerAllRankList.twoTwoRankList[i]);
			twoTwoRankList.Add(newRankMap);
		}
		for (int32 i = 0; i < playerAllRankList.threeThreeRankList.Num(); i++)
		{
			FRankOneMap newRankMap;
			newRankMap.set_RANK_ONE_MAP(playerAllRankList.threeThreeRankList[i]);
			threeThreeRankList.Add(newRankMap);
		}
	}
};

USTRUCT(BlueprintType)
struct FEconomyInfo
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 moneyA;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 moneyB;

	void set_ECONOMY_INFO(ECONOMY_INFO economyInfo)
	{
		moneyA = economyInfo.moneyA;
		moneyB = economyInfo.moneyB;
	}
};

USTRUCT(BlueprintType)
struct FWinPercentInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName = "NULL";

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 winNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 loseNb;

	void set_WIN_PERCENT_INFO(WIN_PERCENT_INFO winPercentInfo)
	{
		levelName = winPercentInfo.levelName;
		winNb = winPercentInfo.winNb;
		loseNb = winPercentInfo.loseNb;
	}
};

USTRUCT(BlueprintType)
struct FAdditionEffect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hpModifyPercent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 physAtkModifyPercent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 magAtkModifyPercent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 physDfcModifyPercent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 magDfcModifyPercent;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString modifyAttribute;

	void set_ADDITION_EFFECT(ADDITION_EFFECT additionEffect)
	{
		hpModifyPercent = additionEffect.hpModifyPercent;
		physAtkModifyPercent = additionEffect.physAtkModifyPercent;
		magAtkModifyPercent = additionEffect.magAtkModifyPercent;
		physDfcModifyPercent = additionEffect.physDfcModifyPercent;
		magDfcModifyPercent = additionEffect.magDfcModifyPercent;
		modifyAttribute = additionEffect.modifyAttribute;
	}
};

USTRUCT(BlueprintType)
struct FPlayerRuneInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> hasRuneList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRuneConfigNb;

	void set_PLAYER_RUNE_INFO(PLAYER_RUNE_INFO info)
	{
		for (int32 i=0; i<info.hasRuneList.Num(); i++)
		{
			hasRuneList.Add(info.hasRuneList[i]);
		}
		curRuneConfigNb = info.curRuneConfigNb;
	}
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString playerName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FFriendList friendList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FCharacterInfo> characterList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FPlayerAllRankList playerAllRankList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> titleList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FEconomyInfo economyInfo;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FWinPercentInfo> winPercentInfoList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString lastSelectRoleType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString headShotName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> haveGoodsList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FAdditionEffect additionEffect;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FPlayerRuneInfo runeInfo;

	void set_PLAYER_INFO(PLAYER_INFO playerInfo)
	{
		playerName = playerInfo.playerName;
		friendList.set_FRIEND_LIST(playerInfo.friendList);
		for (int32 i=0; i<playerInfo.characterList.Num(); i++)
		{
			FCharacterInfo newCharacterInfo;
			newCharacterInfo.set_CHARACTER_INFO(playerInfo.characterList[i]);
			characterList.Add(newCharacterInfo);
		}
		playerAllRankList.set_PLAYER_ALL_RANK_LIST(playerInfo.playerAllRankList);
		titleList = playerInfo.titleList;
		economyInfo.set_ECONOMY_INFO(playerInfo.economyInfo);
		for (int32 i = 0; i < playerInfo.winPercentInfoList.Num(); i++)
		{
			FWinPercentInfo newWinPercentInfo;
			newWinPercentInfo.set_WIN_PERCENT_INFO(playerInfo.winPercentInfoList[i]);
			winPercentInfoList.Add(newWinPercentInfo);
		}
		haveGoodsList = playerInfo.haveGoodsList;
		lastSelectRoleType = playerInfo.lastSelectRoleType;
		headShotName = playerInfo.headShotName;
		additionEffect.set_ADDITION_EFFECT(playerInfo.additionEffect);
		runeInfo.set_PLAYER_RUNE_INFO(playerInfo.runeInfo);
	}
};

USTRUCT(BlueprintType)
struct FPlayerSpawnPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spawnPointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spawnPointX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spawnPointY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;

	void set_PLAYER_SPAWN_POINT_INFO(PLAYER_SPAWN_POINT_INFO playerSpawnPointInfo)
	{
		campFlag = playerSpawnPointInfo.campFlag;
		spawnPointNb = playerSpawnPointInfo.spawnPointNb;
		spawnPointX = playerSpawnPointInfo.spawnPointX;
		spawnPointY = playerSpawnPointInfo.spawnPointY;
		yaw = playerSpawnPointInfo.yaw;
	}
};

USTRUCT(BlueprintType)
struct FPlayerSpawnPointList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPlayerSpawnPointInfo> values;

	void set_PLAYER_SPAWN_POINT_LIST(PLAYER_SPAWN_POINT_LIST playerSpawnPointList)
	{
		for (int32 i=0; i<playerSpawnPointList.values.Num(); i++)
		{
			FPlayerSpawnPointInfo newSpawnInfo;
			newSpawnInfo.set_PLAYER_SPAWN_POINT_INFO(playerSpawnPointList.values[i]);
			values.Add(newSpawnInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FTriggerInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString spawnGroupName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString triggerType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isAutoGenerate;

	void set_TRIGGER_INFO(TRIGGER_INFO triggerInfo)
	{
		spawnGroupName = triggerInfo.SpawnGroupName;
		triggerType = triggerInfo.triggerType;
		positionX = triggerInfo.positionX;
		positionY = triggerInfo.positionY;
		yaw = triggerInfo.yaw;
		if (triggerInfo.isAutoGenerate == 0) isAutoGenerate = false;
		else isAutoGenerate = true;
	}

};

USTRUCT(BlueprintType)
struct FEnermySpawnOrder
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> values;

	void set_ENERMY_SPAWN_ORDER(ENERMY_SPAWN_ORDER enermySpawnOrder)
	{
		values = enermySpawnOrder.values;
	}
};

USTRUCT(BlueprintType)
struct FEnermySpawnPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spawnPointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 defRadius;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FEnermySpawnOrder spawnOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameInterval;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isCirculate;

	void set_ENERMY_SPAWN_POINT_INFO(ENERMY_SPAWN_POINT_INFO enermySpawnPointInfo)
	{
		spawnPointNb = enermySpawnPointInfo.spawnPointNb;
		positionX = enermySpawnPointInfo.positionX;
		positionY = enermySpawnPointInfo.positionY;
		yaw = enermySpawnPointInfo.yaw;
		defRadius = enermySpawnPointInfo.defRadius;
		spawnOrder.set_ENERMY_SPAWN_ORDER(enermySpawnPointInfo.spawnOrder);
		frameInterval = enermySpawnPointInfo.frameInterval;
		if (enermySpawnPointInfo.isCirculate == 0) isCirculate = false;
		else isCirculate = true;
	}
};

USTRUCT(BlueprintType)
struct FEnermySpawnGroupInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 groupNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FTriggerInfo triggerInfo;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEnermySpawnPointInfo> spawnPointList;

	void set_ENERMY_SPAWN_GROUP_INFO(ENERMY_SPAWN_GROUP_INFO enermySpawnGroupInfo)
	{
		groupNb = enermySpawnGroupInfo.groupNb;
		campFlag = enermySpawnGroupInfo.campFlag;
		triggerInfo.set_TRIGGER_INFO(enermySpawnGroupInfo.triggerInfo);
		for (int32 i=0; i<enermySpawnGroupInfo.spawnPointList.Num(); i++)
		{
			FEnermySpawnPointInfo newEnermySpawnPointInfo;
			newEnermySpawnPointInfo.set_ENERMY_SPAWN_POINT_INFO(enermySpawnGroupInfo.spawnPointList[i]);
			spawnPointList.Add(newEnermySpawnPointInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FEnermySpawnGroupList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEnermySpawnGroupInfo> values;

	void set_ENERMY_SPAWN_GROUP_LIST(ENERMY_SPAWN_GROUP_LIST enermySpawnGroupList)
	{
		for (int32 i=0; i<enermySpawnGroupList.values.Num(); i++)
		{
			FEnermySpawnGroupInfo newEnermySpawnGroupInfo;
			newEnermySpawnGroupInfo.set_ENERMY_SPAWN_GROUP_INFO(enermySpawnGroupList.values[i]);
			values.Add(newEnermySpawnGroupInfo);
		}
	}
};


USTRUCT(BlueprintType, Blueprintable)
struct FIntLogicVector
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 Y;

	void set_LOGIC_VECTOR(LOGIC_VECTOR info)
	{
		num = info.num;
		X = info.X;
		Y = info.Y;
	}

	LOGIC_VECTOR assign_LOGIC_VECTOR()
	{
		LOGIC_VECTOR vec;
		vec.X = X;
		vec.Y = Y;
		vec.num = num;
		return vec;
	}

	bool copy(const FIntLogicVector& info)
	{
		bool isSame = true;
		if (num != info.num)
		{
			num = info.num;
			isSame = false;
		}
		if (X != info.X)
		{
			X = info.X;
			isSame = false;
		}
		if (Y != info.Y)
		{
			Y = info.Y;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FPhysActorSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString physActorName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 moveType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FIntLogicVector> moveOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> rotateOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> spawnFrames;

	void set_PHYSACTOR_SPAWN_INFO(PHYSACTOR_SPAWN_INFO physActorSpawnInfo)
	{
		physActorName = physActorSpawnInfo.physActorName;
		positionX = physActorSpawnInfo.positionX;
		positionY = physActorSpawnInfo.positionY;
		yaw = physActorSpawnInfo.yaw;
		moveType = physActorSpawnInfo.moveType;
		for (int32 i = 0; i < physActorSpawnInfo.moveOrder.Num(); i++)
		{
			FIntLogicVector movePoint;
			movePoint.set_LOGIC_VECTOR(physActorSpawnInfo.moveOrder[i]);
			moveOrder.Add(movePoint);
		}
		rotateOrder = physActorSpawnInfo.rotateOrder;
		spawnFrames = physActorSpawnInfo.spawnFrames;
	}
};

USTRUCT(BlueprintType)
struct FPhysActorSpawnList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPhysActorSpawnInfo> values;

	void set_PHYSACTOR_SPAWN_LIST(PHYSACTOR_SPAWN_LIST physActorSpawnList)
	{
		for (int32 i=0; i<physActorSpawnList.values.Num(); i++)
		{
			FPhysActorSpawnInfo newPhysActorSpawnInfo;
			newPhysActorSpawnInfo.set_PHYSACTOR_SPAWN_INFO(physActorSpawnList.values[i]);
			values.Add(newPhysActorSpawnInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FSpecialFrameList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> uploadFrameList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> downloadFrameList;

	void set_SPECIAL_FRAME_LIST(SPECIAL_FRAME_LIST frameList)
	{
		uploadFrameList = frameList.uploadFrameList;
		downloadFrameList = frameList.downloadFrameList;
	}
};

USTRUCT(BlueprintType)
struct FLevelModelInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 price;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString blueprintName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString levelName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionZ;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> availableMatchList;

	void set_LEVEL_MODEL_INFO(LEVEL_MODEL_INFO levelModelInfo)
	{
		price = levelModelInfo.price;
		blueprintName = levelModelInfo.blueprintName;
		levelName = levelModelInfo.levelName;
		positionX = levelModelInfo.positionX;
		positionY = levelModelInfo.positionY;
		positionZ = levelModelInfo.positionZ;
		for (int32 i=0; i<levelModelInfo.availableMatchList.Num(); i++)
		{
			availableMatchList.Add(levelModelInfo.availableMatchList[i]);
		}
	}
};

USTRUCT(BlueprintType)
struct FLevelModelList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FLevelModelInfo> values;

	void set_LEVEL_MODEL_LIST(LEVEL_MODEL_LIST levelModelList)
	{
		for (int32 i=0; i<levelModelList.values.Num(); i++)
		{
			FLevelModelInfo newLevelModelInfo;
			newLevelModelInfo.set_LEVEL_MODEL_INFO(levelModelList.values[i]);
			values.Add(newLevelModelInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FMallGoodsInfoForClient
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString goodsName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 price;

	void set_MALL_GOODS_INFO_FOR_CLIENT(MALL_GOODS_INFO_FOR_CLIENT goodsInfo)
	{
		goodsName = goodsInfo.goodsName;
		price = goodsInfo.price;
	}
};

USTRUCT(BlueprintType)
struct FGoodsList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FMallGoodsInfoForClient> goodsList;

	void set_GOODS_LIST(GOODS_LIST list)
	{
		for (int32 i = 0; i < list.goodsList.Num(); i++)
		{
			FMallGoodsInfoForClient newGoodsInfo;
			newGoodsInfo.set_MALL_GOODS_INFO_FOR_CLIENT(list.goodsList[i]);
			goodsList.Add(newGoodsInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FPlayerRankInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString sdbid = "0";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString playerName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 winPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString headShot = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 rank;

	void set_PLAYER_RANK_INFO(PLAYER_RANK_INFO playerRankInfo)
	{
		sdbid = FString::Printf(TEXT("%lld"), playerRankInfo.dbid);
		playerName = playerRankInfo.playerName;
		winPercent = playerRankInfo.winPercent;
		headShot = playerRankInfo.headShot;
		rank = playerRankInfo.rank;
	}
};

USTRUCT(BlueprintType)
struct FRankList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString mapType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPlayerRankInfo> rankList;

	void set_RANK_LIST(RANK_LIST rList)
	{
		mapType = rList.mapType;
		for (int32 i=0; i<rList.rankList.Num(); i++)
		{
			FPlayerRankInfo newRankInfo;
			newRankInfo.set_PLAYER_RANK_INFO(rList.rankList[i]);
			rankList.Add(newRankInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FAllRankList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankList> singleRankList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankList> oneOneRankList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankList> twoTwoRankList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRankList> threeThreeRankList;

	void set_ALL_RANK_LIST(ALL_RANK_LIST allRankList)
	{
		for (int32 i = 0; i < allRankList.singleRankList.Num(); i++)
		{
			FRankList newRankList;
			newRankList.set_RANK_LIST(allRankList.singleRankList[i]);
			singleRankList.Add(newRankList);
		}
		for (int32 i = 0; i < allRankList.oneOneRankList.Num(); i++)
		{
			FRankList newRankList;
			newRankList.set_RANK_LIST(allRankList.oneOneRankList[i]);
			oneOneRankList.Add(newRankList);
		}
		for (int32 i = 0; i < allRankList.twoTwoRankList.Num(); i++)
		{
			FRankList newRankList;
			newRankList.set_RANK_LIST(allRankList.twoTwoRankList[i]);
			twoTwoRankList.Add(newRankList);
		}
		for (int32 i = 0; i < allRankList.threeThreeRankList.Num(); i++)
		{
			FRankList newRankList;
			newRankList.set_RANK_LIST(allRankList.threeThreeRankList[i]);
			threeThreeRankList.Add(newRankList);
		}
	}
};

USTRUCT(BlueprintType)
struct FPlayerRoletypeAssignnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString roleType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 assignNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 playerID;

	void set_PLAYER_ROLETYPE_ASSIGNNUM(PLAYER_ROLETYPE_ASSIGNNUM info)
	{
		roleType = info.roleType;
		assignNb = info.assignNb;
		playerID = info.playerID;
	}
};

USTRUCT(BlueprintType)
struct FPlayerRoletypeAssignnumList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPlayerRoletypeAssignnum> values;

	void set_PLAYER_ROLETYPE_ASSIGNNUM_LIST(PLAYER_ROLETYPE_ASSIGNNUM_LIST list)
	{
		for (int32 i=0; i<list.values.Num(); i++)
		{
			FPlayerRoletypeAssignnum newInfo;
			newInfo.set_PLAYER_ROLETYPE_ASSIGNNUM(list.values[i]);
			values.Add(newInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FAICharacterOperationInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	float velocityX = 0;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	float velocityY = 0;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	float yaw = 0;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 skillNb = 0;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool newShortTask = false;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString actionName = TEXT("NULL");
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FVector targetLoc;

	void set_AI_CHARACTER_OPERATION_INFO(AI_CHARACTER_OPERATION_INFO info)
	{
		entityID = info.entityID;
		velocityX = info.velocityX;
		velocityY = info.velocityY;
		yaw = info.yaw;
		skillNb = info.skillNb;
		if (info.newShortTask == 0) newShortTask = false;
		else newShortTask = true;
		actionName = info.actionName;
	}

	AI_CHARACTER_OPERATION_INFO assign_AI_CHARACTER_OPERATION_INFO()
	{
		AI_CHARACTER_OPERATION_INFO newInfo;
		newInfo.entityID = entityID;
		newInfo.velocityX = velocityX;
		newInfo.velocityY = velocityY;
		newInfo.yaw = yaw;
		newInfo.skillNb = skillNb;
		if (newShortTask) newInfo.newShortTask = 1;
		else newInfo.newShortTask = 0;
		newInfo.actionName = actionName;
		return newInfo;
	}

	void reset()
	{
		velocityX = 0;
		velocityY = 0;
		yaw = 0;
		skillNb = 0;
		newShortTask = 0;
		actionName = TEXT("NULL");
		targetLoc = FVector::ZeroVector;
	}
};

USTRUCT(BlueprintType)
struct FAICharacterOperationList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FAICharacterOperationInfo> values;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameNb;

	void set_AI_CHARACTER_OPERATION_LIST(AI_CHARACTER_OPERATION_LIST list)
	{
		frameNb = list.frameNb;
		for (int32 i = 0; i < list.values.Num(); i++)
		{
			FAICharacterOperationInfo newInfo;
			newInfo.set_AI_CHARACTER_OPERATION_INFO(list.values[i]);
			values.Add(newInfo);
		}
	}

	AI_CHARACTER_OPERATION_LIST assign_AI_CHARACTER_OPERATION_LIST()
	{
		AI_CHARACTER_OPERATION_LIST newList;
		newList.frameNb = frameNb;
		for (int32 i=0; i<values.Num(); i++)
		{
			AI_CHARACTER_OPERATION_INFO newInfo = values[i].assign_AI_CHARACTER_OPERATION_INFO();
			newList.values.Add(newInfo);
		}
		return newList;
	}
};

USTRUCT(BlueprintType)
struct FPlayerOperationInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 velocityX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 velocityY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 equipmentNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 skillNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FVector skillClickLoc;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString actionName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 collectPhysID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spellSkillNb;

	void set_PLAYER_OPERATION_INFO(PLAYER_OPERATION_INFO info)
	{
		entityID = info.entityID;
		velocityX = info.velocityX;
		velocityY = info.velocityY;
		yaw = info.yaw;
		equipmentNb = info.equipmentNb;
		skillNb = info.skillNb;
		actionName = info.actionName;
		collectPhysID = info.collectPhysID;
		spellSkillNb = info.spellSkillNb;
	}

	PLAYER_OPERATION_INFO assign_PLAYER_OPERATION_INFO()
	{
		PLAYER_OPERATION_INFO newInfo;
		newInfo.entityID = entityID;
		newInfo.actionName = actionName;
		newInfo.collectPhysID = collectPhysID;
		newInfo.equipmentNb = equipmentNb;
		newInfo.skillNb = skillNb;
		newInfo.spellSkillNb = spellSkillNb;
		newInfo.velocityX = velocityX;
		newInfo.velocityY = velocityY;
		newInfo.yaw = yaw;
		return newInfo;
	}

	void reset()
	{
		actionName = "NULL";
		collectPhysID = -1;
		equipmentNb = 0;
		skillNb = 0;
		spellSkillNb = 0;
		velocityX = 0;
		velocityY = 0;
		yaw = 0;
	}
};

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString skillName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool canImplement;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curFreezeFrame;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		bool hasSpawnGeo;

	void set_SKILL_INFO(SKILL_INFO info)
	{
		skillName = info.skillName;
		if (info.canImplement == 0) canImplement = false;
		else canImplement = true;
		curFreezeFrame = info.curFreezeFrame;
		if (info.hasSpawnGeo == 0) hasSpawnGeo = 0;
		else hasSpawnGeo = 1;
	}

	bool copy(const FSkillInfo& info)
	{
		bool isSame = true;
		if (canImplement != info.canImplement)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FSkillInfo::copy  canImplement is dif"));
			canImplement = info.canImplement;
			isSame = false;
		}
		if (curFreezeFrame != info.curFreezeFrame)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FSkillInfo::copy  curFreezeFrame is dif"));
			curFreezeFrame = info.curFreezeFrame;
			isSame = false;
		}
		if ((hasSpawnGeo == false && info.hasSpawnGeo != 0) || (hasSpawnGeo == true && info.hasSpawnGeo != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FSkillInfo::copy  hasSpawnGeo is dif"));
			if (info.hasSpawnGeo == 0) hasSpawnGeo = false;
			else hasSpawnGeo = true;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FEquipmentInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString equipmentName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FSkillInfo> skillInfoList;

	void set_EQUIPMENT_INFO(EQUIPMENT_INFO info)
	{
		equipmentName = info.equipmentName;
		for (int32 i=0; i<info.skillInfoList.Num(); i++)
		{
			FSkillInfo newInfo;
			newInfo.skillName = info.skillInfoList[i].skillName;
			if (info.skillInfoList[i].canImplement == 0) newInfo.canImplement = false;
			else newInfo.canImplement = true;
			newInfo.curFreezeFrame = info.skillInfoList[i].curFreezeFrame;
		}
	}

	EQUIPMENT_INFO assign_EQUIPMENT_INFO()
	{
		EQUIPMENT_INFO info;
		info.equipmentName = equipmentName;
		for (int32 i=0; i<skillInfoList.Num(); i++)
		{
			SKILL_INFO skillInfo;
			skillInfo.skillName = skillInfoList[i].skillName;
			skillInfo.canImplement = skillInfoList[i].canImplement;
			skillInfo.curFreezeFrame = skillInfoList[i].curFreezeFrame;
			info.skillInfoList.Add(skillInfo);
		}
		return info;
	}

	bool copy(const FEquipmentInfo& info)
	{
		bool isSame = true;
		if (skillInfoList.Num() != info.skillInfoList.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEquipmentInfo::copy  skill num is dif"));
			skillInfoList = info.skillInfoList;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < skillInfoList.Num(); i++)
			{
				bool foundSkill = false;
				for (int32 j = 0; j < info.skillInfoList.Num(); j++)
				{
					if (skillInfoList[i].skillName == info.skillInfoList[j].skillName)
					{
						foundSkill = true;
						bool isSkillSame = skillInfoList[i].copy(info.skillInfoList[j]);
						if (!isSkillSame)
						{
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEquipmentInfo::copy  skill ") + FString::FromInt(i) + TEXT("is dif"));
							isSame = false;
						}
						break;
					}
				}
				if (!foundSkill || !isSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEquipmentInfo::copy  can not find skill"));
					skillInfoList = info.skillInfoList;
					isSame = false;
					break;
				}
			}
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FEffectInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		bool isInitial;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString effectName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curTickTime;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 originalGeoID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hostID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		bool isOnTimeEffectDone;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		bool isDeriveEffect;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> subHostIDList;

	void set_EFFECT_INFO(EFFECT_INFO info)
	{
		if (info.isInitial == 0) isInitial = false;
		else isInitial = true;
		effectName = info.effectName;
		curTickTime = info.curTickTime;
		originalGeoID = info.originalGeoID;
		hostID = info.hostID;
		if (info.isOnTimeEffectDone == 0) isOnTimeEffectDone = false;
		else isOnTimeEffectDone = true;
		if (info.isDeriveEffect == 0) isDeriveEffect = false;
		else isDeriveEffect = true;
		subHostIDList = info.subHostIDList;
	}

	EFFECT_INFO assign_EFFECT_INFO()
	{
		EFFECT_INFO info;
		if (isInitial == false) info.isInitial = 0;
		else info.isInitial = 1;
		info.effectName = effectName;
		info.curTickTime = curTickTime;
		info.originalGeoID = originalGeoID;
		info.hostID = hostID;
		if (isOnTimeEffectDone == false) info.isOnTimeEffectDone = 0;
		else info.isOnTimeEffectDone = 1;
		if (isDeriveEffect == false) info.isDeriveEffect = 0;
		else info.isDeriveEffect = 1;
		info.subHostIDList = subHostIDList;
		return info;
	}

	bool copy(const FEffectInfo& info)
	{
		bool isSame = true;
		if (subHostIDList.Num() != info.subHostIDList.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  subHostIDs num is dif"));
			subHostIDList = info.subHostIDList;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < subHostIDList.Num(); i++)
			{
				bool foundID = false;
				for (int32 j = 0; j < info.subHostIDList.Num(); j++)
				{
					if (subHostIDList[i] == info.subHostIDList[j])
					{
						foundID = true;
						break;
					}
				}
				if (!foundID || !isSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  can not find id"));
					subHostIDList = info.subHostIDList;
					isSame = false;
					break;
				}
			}
		}
		if ((isInitial == false && info.isInitial != 0) || (isInitial == true && info.isInitial != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  isInitial is dif"));
			if (info.isInitial == 0) isInitial = false;
			else isInitial = true;
			isSame = false;
		}
		if (curTickTime != info.curTickTime)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  curTickTime is dif"));
			curTickTime = info.curTickTime;
			isSame = false;
		}
		if (originalGeoID != info.originalGeoID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  originalGeoID is dif"));
			originalGeoID = info.originalGeoID;
			isSame = false;
		}
		if (hostID != info.hostID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  hostID is dif"));
			hostID = info.hostID;
			isSame = false;
		}
		if ((isOnTimeEffectDone == false && info.isOnTimeEffectDone != 0) || (isOnTimeEffectDone == true && info.isOnTimeEffectDone != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  isOnTimeEffectDone is dif"));
			if (info.isOnTimeEffectDone == 0) isOnTimeEffectDone = false;
			else isOnTimeEffectDone = true;
			isSame = false;
		}
		if ((isDeriveEffect == false && info.isDeriveEffect != 0) || (isDeriveEffect == true && info.isDeriveEffect != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEffectInfo::copy  isDeriveEffect is dif"));
			if (info.isDeriveEffect == 0) isDeriveEffect = false;
			else isDeriveEffect = true;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FCharacterCorrectInfo
{
	GENERATED_USTRUCT_BODY()
	

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 Hp;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 DFC;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 magDFC;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 ATKPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 DFCPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 magDFCPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 maxSPD;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isInitialDone;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEquipmentInfo> equipInfoList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> carrySkillNames;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 defRadius;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 defLocX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 defLocY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 speedRatePercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEffectInfo> effects;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 velocityX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 velocityY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 equipmentNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curSkillNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString curMotionType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isDoingContinuousSkill;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> controlGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString actionName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString className = "NULL";

	void set_CHARACTER_CORRECT_INFO(CHARACTER_CORRECT_INFO info)
	{
		entityID = info.entityID;
		Hp = info.Hp;
		DFC = info.DFC;
		magDFC = info.magDFC;
		ATKPercent = info.ATKPercent;
		DFCPercent = info.DFCPercent;
		magDFCPercent = info.magDFCPercent;
		maxSPD = info.maxSPD;
		campFlag = info.campFlag;
		if (info.isInitialDone == 0) isInitialDone = false;
		else isInitialDone = true;
		for (int32 i=0; i<info.equipInfoList.Num(); i++)
		{
			FEquipmentInfo equipInfo;
			equipInfo.set_EQUIPMENT_INFO(info.equipInfoList[i]);
			equipInfoList.Add(equipInfo);
		}
		carrySkillNames = info.carrySkillNames;
		defRadius = info.defRadius;
		defLocX = info.defLocX;
		defLocY = info.defLocY;
		speedRatePercent = info.speedRatePercent;
		positionX = info.positionX;
		positionY = info.positionY;
		for (int32 i=0; i<info.effects.Num(); i++)
		{
			FEffectInfo effectInfo;
			effectInfo.set_EFFECT_INFO(info.effects[i]);
			effects.Add(effectInfo);
		}
		velocityX = info.velocityX;
		velocityY = info.velocityY;
		yaw = info.yaw;
		equipmentNb = info.equipmentNb;
		curSkillNb = info.curSkillNb;
		curMotionType = info.curMotionType;
		if (info.isDoingContinuousSkill == 0) isDoingContinuousSkill = false;
		else isDoingContinuousSkill = true;
		controlGeoIDs = info.controlGeoIDs;
		actionName = info.actionName;
		className = info.className;
	}

	CHARACTER_CORRECT_INFO assign_CHARACTER_CORRECT_INFO()
	{
		CHARACTER_CORRECT_INFO info;
		info.entityID = entityID;
		info.Hp = Hp;
		info.DFC = DFC;
		info.magDFC = magDFC;
		info.ATKPercent = ATKPercent;
		info.DFCPercent = DFCPercent;
		info.magDFCPercent = magDFCPercent;
		info.maxSPD = maxSPD;
		info.campFlag = campFlag;
		if (isInitialDone == false) info.isInitialDone = 0;
		else info.isInitialDone = 1;
		for (int32 i=0; i<equipInfoList.Num(); i++)
		{
			EQUIPMENT_INFO equipInfo = equipInfoList[i].assign_EQUIPMENT_INFO();
			info.equipInfoList.Add(equipInfo);
		}
		info.carrySkillNames = carrySkillNames;
		info.defRadius = defRadius;
		info.defLocX = defLocX;
		info.defLocY = defLocY;
		info.speedRatePercent = speedRatePercent;
		info.positionX = positionX;
		info.positionY = positionY;
		for (int32 i=0; i<effects.Num(); i++)
		{
			EFFECT_INFO effectInfo = effects[i].assign_EFFECT_INFO();
			info.effects.Add(effectInfo);
		}
		info.velocityX = velocityX;
		info.velocityY = velocityY;
		info.yaw = yaw;
		info.equipmentNb = equipmentNb;
		info.curSkillNb = curSkillNb;
		info.curMotionType = curMotionType;
		if (isDoingContinuousSkill == false) info.isDoingContinuousSkill = 0;
		else info.isDoingContinuousSkill = 1;
		info.controlGeoIDs = controlGeoIDs;
		info.actionName = actionName;
		info.className = className;
		return info;
	}

	bool copy(const FCharacterCorrectInfo& info)
	{
		bool isSame = true;
		if (entityID != info.entityID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  entityID is dif"));
			entityID = info.entityID;
			isSame = false;
		}
		if (Hp != info.Hp)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  Hp is dif"));
			Hp = info.Hp;
			isSame = false;
		}
		if (DFC != info.DFC)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  DFC is dif"));
			DFC = info.DFC;
			isSame = false;
		}
		if (magDFC != info.magDFC)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  magDFC is dif"));
			magDFC = info.magDFC;
			isSame = false;
		}
		if (ATKPercent != info.ATKPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  ATKPercent is dif"));
			ATKPercent = info.ATKPercent;
			isSame = false;
		}
		if (DFCPercent != info.DFCPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  DFCPercent is dif"));
			DFCPercent = info.DFCPercent;
			isSame = false;
		}
		if (magDFCPercent != info.magDFCPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  magDFCPercent is dif"));
			magDFCPercent = info.magDFCPercent;
			isSame = false;
		}
		if (maxSPD != info.maxSPD)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  maxSPD is dif"));
			maxSPD = info.maxSPD;
			isSame = false;
		}
		if (campFlag != info.campFlag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  campFlag is dif"));
			campFlag = info.campFlag;
			isSame = false;
		}
		if (curSkillNb != info.curSkillNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  curSkillNb is dif"));
			curSkillNb = info.curSkillNb;
			isSame = false;
		}
		if ((isInitialDone == false && info.isInitialDone != 0) || (isInitialDone == true && info.isInitialDone != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  isInitialDone is dif"));
			if (info.isInitialDone == 0) isInitialDone = false;
			else isInitialDone = true;
			isSame = false;
		}
		if (equipInfoList.Num() != info.equipInfoList.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  equipInfo num is dif"));
			equipInfoList = info.equipInfoList;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < equipInfoList.Num(); i++)
			{
				bool foundEquip = false;
				for (int32 j = 0; j < info.equipInfoList.Num(); j++)
				{
					if (equipInfoList[i].equipmentName == info.equipInfoList[j].equipmentName)
					{
						foundEquip = true;
						bool isEquipSame = equipInfoList[i].copy(info.equipInfoList[j]);
						if (!isEquipSame)
						{
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  equipInfo ") + FString::FromInt(i) + TEXT(" is dif"));
							isSame = false;
						}
						break;
					}
				}
				if (!foundEquip || !isSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  can not find equip"));
					equipInfoList = info.equipInfoList;
					isSame = false;
					break;
				}
			}
		}
		if (carrySkillNames.Num() == info.carrySkillNames.Num())
		{
			for (int32 i = 0; i < info.carrySkillNames.Num(); i++)
			{
				if (!carrySkillNames.Contains(info.carrySkillNames[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  carrySkills ")+info.carrySkillNames[i] );
					carrySkillNames = info.carrySkillNames;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  carrySkills num is dif"));
			carrySkillNames = info.carrySkillNames;
			isSame = false;
		}
		if (defRadius != info.defRadius)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  defRadius is dif"));
			defRadius = info.defRadius;
			isSame = false;
		}
		if (defLocX != info.defLocX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  defLocX is dif"));
			defLocX = info.defLocX;
			isSame = false;
		}
		if (defLocY != info.defLocY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  defLocY is dif"));
			defLocY = info.defLocY;
			isSame = false;
		}
		if (speedRatePercent != info.speedRatePercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  speedRatePercent is dif"));
			speedRatePercent = info.speedRatePercent;
			isSame = false;
		}
		if (positionX != info.positionX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  positionX is dif"));
			positionX = info.positionX;
			isSame = false;
		}
		if (positionY != info.positionY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  positionY is dif"));
			positionY = info.positionY;
			isSame = false;
		}
		if (effects.Num() != info.effects.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  effects num is dif"));
			effects = info.effects;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < effects.Num(); i++)
			{
				bool foundEffect = false;
				for (int32 j = 0; j < info.effects.Num(); j++)
				{
					if (effects[i].effectName == info.effects[j].effectName)
					{
						foundEffect = true;
						bool isEffectSame = effects[i].copy(info.effects[j]);
						if (!isEffectSame)
						{
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  effects ") + FString::FromInt(i) + TEXT(" is dif"));
							isSame = false;
						}
						break;
					}
				}
				if (!foundEffect || !isSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  can not find effect"));
					effects = info.effects;
					isSame = false;
					break;
				}
			}
		}
		if (velocityX != info.velocityX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  velocityX is dif"));
			velocityX = info.velocityX;
			isSame = false;
		}
		if (velocityY != info.velocityY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  velocityY is dif"));
			velocityY = info.velocityY;
			isSame = false;
		}
		if (yaw != info.yaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  yaw is dif"));
			yaw = info.yaw;
			isSame = false;
		}
		if (equipmentNb != info.equipmentNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  equipmentNb is dif"));
			equipmentNb = info.equipmentNb;
			isSame = false;
		}
		if (curSkillNb != info.curSkillNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  curSkillNb is dif"));
			curSkillNb = info.curSkillNb;
			isSame = false;
		}
		if (curMotionType != info.curMotionType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  curMotionType is dif"));
			curMotionType = info.curMotionType;
			isSame = false;
		}
		if ((isDoingContinuousSkill == false && info.isDoingContinuousSkill != 0) || (isDoingContinuousSkill == true && info.isDoingContinuousSkill != 1))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  isDoingContinuousSkill is dif"));
			if (info.isDoingContinuousSkill == 0) isDoingContinuousSkill = false;
			else isDoingContinuousSkill = true;
			isSame = false;
		}
		if (controlGeoIDs.Num() == info.controlGeoIDs.Num())
		{
			for (int32 i = 0; i < info.controlGeoIDs.Num(); i++)
			{
				if (!controlGeoIDs.Contains(info.controlGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  controlIDs not contain ") + FString::FromInt(info.controlGeoIDs[i]));
					controlGeoIDs = info.controlGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  controlIDs num is dif"));
			controlGeoIDs = info.controlGeoIDs;
			isSame = false;
		}
		if (actionName != info.actionName)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  actionName is dif"));
			actionName = info.actionName;
			isSame = false;
		}
		if (className != info.className)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FCharacterCorrectInfo::copy  className is dif"));
			className = info.className;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FPhysPolyInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID = -1;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hostID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString className = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hierachy;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rootGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> sonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> secondarySonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> reactionInfoNbs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isDead;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> overlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> preOverlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> preOverlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> overlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curLifeTime;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 ATKPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 moveType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FIntLogicVector> moveOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> rotateOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curMovePointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curRotateNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FString> attributeTags;

	void set_PHYS_POLY_INFO(PHYSPOLY_INFO info)
	{
		entityID = info.entityID;
		hostID = info.hostID;
		positionX = info.positionX;
		positionY = info.positionY;
		yaw = info.yaw;
		className = info.className;
		hierachy = info.hierachy;
		rootGeoIDs = info.rootGeoIDs;
		sonGeoIDs = info.sonGeoIDs;
		secondarySonGeoIDs = info.secondarySonGeoIDs;
		campFlag = info.campFlag;
		reactionInfoNbs = info.reactionInfoNbs;
		if (info.isDead == 0) isDead = false;
		else isDead = true;
		preOverlapCharacterIDs = info.preOverlapCharacterIDs;
		overlapCharacterIDs = info.overlapCharacterIDs;
		preOverlapGeoIDs = info.preOverlapGeoIDs;
		overlapGeoIDs = info.overlapGeoIDs;
		curLifeTime = info.curLifeTime;
		ATKPercent = info.ATKPercent;
		moveType = info.moveType;
		for (int32 i=0; i<info.moveOrder.Num(); i++)
		{
			FIntLogicVector movePoint;
			movePoint.set_LOGIC_VECTOR(info.moveOrder[i]);
			moveOrder.Add(movePoint);
		}
		rotateOrder = info.rotateOrder;
		curMovePointNb = info.curMovePointNb;
		curRotateNb = info.curRotateNb;
		curRandTargetX = info.curRandTargetX;
		curRandTargetY = info.curRandTargetY;
		attributeTags = info.attributeTags;
	}

	PHYSPOLY_INFO assign_PHYS_POLY_INFO()
	{
		PHYSPOLY_INFO info;
		info.campFlag = campFlag;
		info.className = className;
		info.curLifeTime = curLifeTime;
		info.entityID = entityID;
		info.hierachy = hierachy;
		info.hostID = hostID;
		info.isDead = isDead;
		info.overlapCharacterIDs = overlapCharacterIDs;
		info.overlapGeoIDs = overlapGeoIDs;
		info.positionX = positionX;
		info.positionY = positionY;
		info.preOverlapCharacterIDs = preOverlapCharacterIDs;
		info.preOverlapGeoIDs = preOverlapGeoIDs;
		info.reactionInfoNbs = reactionInfoNbs;
		info.rootGeoIDs = rootGeoIDs;
		info.secondarySonGeoIDs = secondarySonGeoIDs;
		info.sonGeoIDs = sonGeoIDs;
		info.yaw = yaw;
		info.ATKPercent = ATKPercent;
		info.moveType = moveType;
		for (int32 i=0; i<moveOrder.Num(); i++)
		{
			LOGIC_VECTOR movePoint = moveOrder[i].assign_LOGIC_VECTOR();
			info.moveOrder.Add(movePoint);
		}
		info.rotateOrder = rotateOrder;
		info.curMovePointNb = curMovePointNb;
		info.curRotateNb = curRotateNb;
		info.curRandTargetX = curRandTargetX;
		info.curRandTargetY = curRandTargetY;
		info.attributeTags = attributeTags;
		return info;
	}

	bool copy(const FPhysPolyInfo& info)
	{
		bool isSame = true;
		if (hostID != info.hostID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  hostID is dif"));
			hostID = info.hostID;
			isSame = false;
		}
		if (positionX != info.positionX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  positionX is dif"));
			positionX = info.positionX;
			isSame = false;
		}
		if (positionY != info.positionY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  positionY is dif"));
			positionY = info.positionY;
			isSame = false;
		}
		if (yaw != info.yaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  yaw is dif"));
			yaw = info.yaw;
			isSame = false;
		}
		if (className != info.className)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  className is dif"));
			className = info.className;
			isSame = false;
		}
		if (hierachy != info.hierachy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  hierachy is dif"));
			hierachy = info.hierachy;
			isSame = false;
		}
		if (campFlag != info.campFlag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  campFlag is dif"));
			campFlag = info.campFlag;
			isSame = false;
		}
		if (rootGeoIDs.Num() == info.rootGeoIDs.Num())
		{
			for (int32 i = 0; i < info.rootGeoIDs.Num(); i++)
			{
				if (!rootGeoIDs.Contains(info.rootGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  rootGeo not contain ") + FString::FromInt(info.rootGeoIDs[i]));
					rootGeoIDs = info.rootGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  rootIDs num is dif"));
			rootGeoIDs = info.rootGeoIDs;
			isSame = false;
		}

		if (sonGeoIDs.Num() == info.sonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.sonGeoIDs.Num(); i++)
			{
				if (!sonGeoIDs.Contains(info.sonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  sonGeo not contain ") + FString::FromInt(info.sonGeoIDs[i]));
					sonGeoIDs = info.sonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  sonIDs num is dif"));
			sonGeoIDs = info.sonGeoIDs;
			isSame = false;
		}

		if (secondarySonGeoIDs.Num() == info.secondarySonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.secondarySonGeoIDs.Num(); i++)
			{
				if (!secondarySonGeoIDs.Contains(info.secondarySonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  secondary not contain ") + FString::FromInt(info.secondarySonGeoIDs[i]));
					secondarySonGeoIDs = info.secondarySonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  secondary sonIDs num is dif"));
			secondarySonGeoIDs = info.secondarySonGeoIDs;
			isSame = false;
		}

		if (reactionInfoNbs.Num() == info.reactionInfoNbs.Num())
		{
			for (int32 i = 0; i < info.reactionInfoNbs.Num(); i++)
			{
				if (!reactionInfoNbs.Contains(info.reactionInfoNbs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  reactionInfos not contain ") + FString::FromInt(info.reactionInfoNbs[i]));
					reactionInfoNbs = info.reactionInfoNbs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  reactionInfos num is dif"));
			reactionInfoNbs = info.reactionInfoNbs;
			isSame = false;
		}
		if (isDead != info.isDead)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  isDead is dif"));
			isDead = info.isDead;
			isSame = false;
		}
		if (overlapCharacterIDs.Num() != info.overlapCharacterIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  overlapCharacterID num is dif"));
			overlapCharacterIDs = info.overlapCharacterIDs;
			isSame = false;
		}
		else
		{
			for (int32 i=0; i<info.overlapCharacterIDs.Num(); i++)
			{
				if (!overlapCharacterIDs.Contains(info.overlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  overlapCharacter not contain ") + FString::FromInt(info.overlapCharacterIDs[i]));
					overlapCharacterIDs = info.overlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		if (preOverlapCharacterIDs.Num() != info.preOverlapCharacterIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  preOverlapCharacter num is dif"));
			preOverlapCharacterIDs = info.preOverlapCharacterIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.preOverlapCharacterIDs.Num(); i++)
			{
				if (!preOverlapCharacterIDs.Contains(info.preOverlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  preOverlapCharacter not contain ") + FString::FromInt(info.preOverlapCharacterIDs[i]));
					preOverlapCharacterIDs = info.preOverlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		if (preOverlapGeoIDs.Num() != info.preOverlapGeoIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  preOverlapGeo num is dif"));
			preOverlapGeoIDs = info.preOverlapGeoIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.preOverlapGeoIDs.Num(); i++)
			{
				if (!preOverlapGeoIDs.Contains(info.preOverlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  preOverlapGeo not contain ") + FString::FromInt(info.preOverlapGeoIDs[i]));
					preOverlapGeoIDs = info.preOverlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		if (overlapGeoIDs.Num() != info.overlapGeoIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  overlapGeoID num is dif"));
			overlapGeoIDs = info.overlapGeoIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.overlapGeoIDs.Num(); i++)
			{
				if (!overlapGeoIDs.Contains(info.overlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  overlapGeo not contain ") + FString::FromInt(info.overlapGeoIDs[i]));
					overlapGeoIDs = info.overlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}

		if (curLifeTime != info.curLifeTime)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  curLifeTime is dif"));
			curLifeTime = info.curLifeTime;
			isSame = false;
		}
		if (ATKPercent != info.ATKPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  ATKPercent is dif"));
			ATKPercent = info.ATKPercent;
			isSame = false;
		}
		if (moveType != info.moveType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  moveType is dif"));
			moveType = info.moveType;
			isSame = false;
		}
		if (moveOrder.Num() != info.moveOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  moveOrder num is dif"));
			moveOrder = info.moveOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < moveOrder.Num(); i++)
			{
				bool isPointSame = moveOrder[i].copy(info.moveOrder[i]);
				if (!isPointSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  moveOrder ") + FString::FromInt(i) + TEXT("is dif"));
					moveOrder = info.moveOrder;
					isSame = false;
					break;
				}
			}
		}
		if (rotateOrder.Num() != info.rotateOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  rotateOrder num is dif"));
			rotateOrder = info.rotateOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.rotateOrder.Num(); i++)
			{
				if (rotateOrder[i] != info.rotateOrder[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  rotateOrder not contain ") + FString::FromInt(info.rotateOrder[i]));
					rotateOrder = info.rotateOrder;
					isSame = false;
					break;
				}
			}
		}
		if (curMovePointNb != info.curMovePointNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  curMovePointNb is dif"));
			curMovePointNb = info.curMovePointNb;
			isSame = false;
		}
		if (curRotateNb != info.curRotateNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  curRotateNb is dif"));
			curRotateNb = info.curRotateNb;
			isSame = false;
		}
		if (curRandTargetX != info.curRandTargetX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  curRandTargetX is dif"));
			curRandTargetX = info.curRandTargetX;
			isSame = false;
		}
		if (curRandTargetY != info.curRandTargetY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  curRandTargetY is dif"));
			curRandTargetY = info.curRandTargetY;
			isSame = false;
		}
		if (attributeTags.Num() != info.attributeTags.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  attributeTags num is dif"));
			attributeTags = info.attributeTags;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.attributeTags.Num(); i++)
			{
				if (!attributeTags.Contains(info.attributeTags[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspolygon::copy  attributeTags not contain ") + info.attributeTags[i]);
					attributeTags = info.attributeTags;
					isSame = false;
					break;
				}
			}
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FPhysPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID = -1;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hostID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString className = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hierachy;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rootGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> sonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> secondarySonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> reactionInfoNbs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 fireDirZ;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 locX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 locY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 locZ;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curLifeTime;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> overlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> preOverlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> preOverlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> overlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isDead;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 ATKPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 moveType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FIntLogicVector> moveOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rotateOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curMovePointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRotateNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FString> attributeTags;
	

	void set_PHYS_POINT_INFO(PHYSPOINT_INFO info)
	{
		entityID = info.entityID;
		hostID = info.hostID;
		className = info.className;
		hierachy = info.hierachy;
		rootGeoIDs = info.rootGeoIDs;
		sonGeoIDs = info.sonGeoIDs;
		secondarySonGeoIDs = info.secondarySonGeoIDs;
		campFlag = info.campFlag;
		reactionInfoNbs = info.reactionInfoNbs;
		yaw = info.yaw;
		fireDirZ = info.fireDirZ;
		locX = info.locX;
		locY = info.locY;
		locZ = info.locZ;
		curLifeTime = info.curLifeTime;
		preOverlapCharacterIDs = info.preOverlapCharacterIDs;
		overlapCharacterIDs = info.overlapCharacterIDs;
		preOverlapGeoIDs = info.preOverlapGeoIDs;
		overlapGeoIDs = info.overlapGeoIDs;
		if (info.isDead == 0) isDead = false;
		else isDead = true;
		ATKPercent = info.ATKPercent;
		moveType = info.moveType;
		for (int32 i = 0; i < info.moveOrder.Num(); i++)
		{
			FIntLogicVector movePoint;
			movePoint.set_LOGIC_VECTOR(info.moveOrder[i]);
			moveOrder.Add(movePoint);
		}
		rotateOrder = info.rotateOrder;
		curMovePointNb = info.curMovePointNb;
		curRotateNb = info.curRotateNb;
		curRandTargetX = info.curRandTargetX;
		curRandTargetY = info.curRandTargetY;
		attributeTags = info.attributeTags;
	}

	PHYSPOINT_INFO assign_PHYS_POINT_INFO()
	{
		PHYSPOINT_INFO info;
		info.campFlag = campFlag;
		info.className = className;
		info.curLifeTime = curLifeTime;
		info.entityID = entityID;
		info.fireDirZ = fireDirZ;
		info.hierachy = hierachy;
		info.hostID = hostID;
		info.isDead = isDead;
		info.locX = locX;
		info.locY = locY;
		info.locZ = locZ;
		info.reactionInfoNbs = info.reactionInfoNbs;
		info.rootGeoIDs = rootGeoIDs;
		info.secondarySonGeoIDs = secondarySonGeoIDs;
		info.sonGeoIDs = sonGeoIDs;
		info.yaw = yaw;
		info.preOverlapCharacterIDs = preOverlapCharacterIDs;
		info.overlapCharacterIDs = overlapCharacterIDs;
		info.preOverlapGeoIDs = preOverlapGeoIDs;
		info.overlapGeoIDs = overlapGeoIDs;
		info.ATKPercent = ATKPercent;
		info.moveType = moveType;
		for (int32 i = 0; i < moveOrder.Num(); i++)
		{
			LOGIC_VECTOR movePoint = moveOrder[i].assign_LOGIC_VECTOR();
			info.moveOrder.Add(movePoint);
		}
		info.rotateOrder = rotateOrder;
		info.curMovePointNb = curMovePointNb;
		info.curRotateNb = curRotateNb;
		info.curRandTargetX = curRandTargetX;
		info.curRandTargetY = curRandTargetY;
		info.attributeTags = attributeTags;
		return info;

	}

	bool copy(const FPhysPointInfo& info)
	{
		bool isSame = true;
		if (hostID != info.hostID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  hostID is dif"));
			hostID = info.hostID;
			isSame = false;
		}
		if (className != info.className)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  className is dif"));
			className = info.className;
			isSame = false;
		}
		if (hierachy != info.hierachy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  hierachy is dif"));
			hierachy = info.hierachy;
			isSame = false;
		}
		if (campFlag != info.campFlag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  campFlag is dif"));
			campFlag = info.campFlag;
			isSame = false;
		}
		if (rootGeoIDs.Num() == info.rootGeoIDs.Num())
		{
			for (int32 i = 0; i < info.rootGeoIDs.Num(); i++)
			{
				if (!rootGeoIDs.Contains(info.rootGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  rootGeo not contain ") +FString::FromInt(info.rootGeoIDs[i]));
					rootGeoIDs = info.rootGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  rootGeoID num is dif"));
			rootGeoIDs = info.rootGeoIDs;
			isSame = false;
		}

		if (sonGeoIDs.Num() == info.sonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.sonGeoIDs.Num(); i++)
			{
				if (!sonGeoIDs.Contains(info.sonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  sonGeo not contain ") + FString::FromInt(info.sonGeoIDs[i]));
					sonGeoIDs = info.sonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  sonGeoID num is dif"));
			sonGeoIDs = info.sonGeoIDs;
			isSame = false;
		}

		if (secondarySonGeoIDs.Num() == info.secondarySonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.secondarySonGeoIDs.Num(); i++)
			{
				if (!secondarySonGeoIDs.Contains(info.secondarySonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  secondaryGeo not contain ")+FString::FromInt(info.secondarySonGeoIDs[i]));
					secondarySonGeoIDs = info.secondarySonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  secondaryGeo num is dif"));
			secondarySonGeoIDs = info.secondarySonGeoIDs;
			isSame = false;
		}

		if (preOverlapCharacterIDs.Num() == info.preOverlapCharacterIDs.Num())
		{
			for (int32 i = 0; i < info.preOverlapCharacterIDs.Num(); i++)
			{
				if (!preOverlapCharacterIDs.Contains(info.preOverlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  preOverlapCharacter not contain ") + FString::FromInt(info.preOverlapCharacterIDs[i]));
					preOverlapCharacterIDs = info.preOverlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  preOverlapCharacterIDs num is dif"));
			preOverlapCharacterIDs = info.preOverlapCharacterIDs;
			isSame = false;
		}

		if (overlapCharacterIDs.Num() == info.overlapCharacterIDs.Num())
		{
			for (int32 i = 0; i < info.overlapCharacterIDs.Num(); i++)
			{
				if (!overlapCharacterIDs.Contains(info.overlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  overlapCharacterIDs not contain ") + FString::FromInt(info.overlapCharacterIDs[i]));
					overlapCharacterIDs = info.overlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  overlapCharacterIDs num is dif"));
			overlapCharacterIDs = info.overlapCharacterIDs;
			isSame = false;
		}

		if (preOverlapGeoIDs.Num() == info.preOverlapGeoIDs.Num())
		{
			for (int32 i = 0; i < info.preOverlapGeoIDs.Num(); i++)
			{
				if (!preOverlapGeoIDs.Contains(info.preOverlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  preOverlapGeoIDs not contain ") + FString::FromInt(info.preOverlapGeoIDs[i]));
					preOverlapGeoIDs = info.preOverlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  preOverlapGeoIDs num is dif"));
			preOverlapGeoIDs = info.preOverlapGeoIDs;
			isSame = false;
		}

		if (overlapGeoIDs.Num() == info.overlapGeoIDs.Num())
		{
			for (int32 i = 0; i < info.overlapGeoIDs.Num(); i++)
			{
				if (!overlapGeoIDs.Contains(info.overlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  overlapGeoIDs not contain ") + FString::FromInt(info.overlapGeoIDs[i]));
					overlapGeoIDs = info.overlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  overlapGeoIDs num is dif"));
			overlapGeoIDs = info.overlapGeoIDs;
			isSame = false;
		}

		if (reactionInfoNbs.Num() == info.reactionInfoNbs.Num())
		{
			for (int32 i = 0; i < info.reactionInfoNbs.Num(); i++)
			{
				if (!reactionInfoNbs.Contains(info.reactionInfoNbs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  reactionInfo not contain ")+FString::FromInt(info.reactionInfoNbs[i]));
					reactionInfoNbs = info.reactionInfoNbs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  reactionInfo num is dif"));
			reactionInfoNbs = info.reactionInfoNbs;
			isSame = false;
		}

		if (yaw != info.yaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  yaw is dif"));
			yaw = info.yaw;
			isSame = false;
		}
		if (fireDirZ != info.fireDirZ)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  fireDirZ is dif"));
			fireDirZ = info.fireDirZ;
			isSame = false;
		}
		if (locX != info.locX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  locX is dif"));
			locX = info.locX;
			isSame = false;
		}
		if (locY != info.locY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  locY is dif"));
			locY = info.locY;
			isSame = false;
		}
		if (locZ != info.locZ)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  locZ is dif"));
			locZ = info.locZ;
			isSame = false;
		}
		if (curLifeTime != info.curLifeTime)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  curLifeTime is dif"));
			curLifeTime = info.curLifeTime;
			isSame = false;
		}
		if (isDead != info.isDead)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  isDead is dif"));
			isDead = info.isDead;
			isSame = false;
		}
		if (ATKPercent != info.ATKPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  ATKPercent is dif"));
			ATKPercent = info.ATKPercent;
			isSame = false;
		}
		if (moveType != info.moveType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  moveType is dif"));
			moveType = info.moveType;
			isSame = false;
		}
		if (moveOrder.Num() != info.moveOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  moveOrder num is dif"));
			moveOrder = info.moveOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < moveOrder.Num(); i++)
			{
				bool isPointSame = moveOrder[i].copy(info.moveOrder[i]);
				if (!isPointSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  moveOrder ") + FString::FromInt(i) + TEXT("is dif"));
					moveOrder = info.moveOrder;
					isSame = false;
					break;
				}
			}
		}
		if (rotateOrder.Num() != info.rotateOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  rotateOrder num is dif"));
			rotateOrder = info.rotateOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.rotateOrder.Num(); i++)
			{
				if (rotateOrder[i] != info.rotateOrder[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  rotateOrder not contain ") + FString::FromInt(info.rotateOrder[i]));
					rotateOrder = info.rotateOrder;
					isSame = false;
					break;
				}
			}
		}
		if (curMovePointNb != info.curMovePointNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  curMovePointNb is dif"));
			curMovePointNb = info.curMovePointNb;
			isSame = false;
		}
		if (curRotateNb != info.curRotateNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  curRotateNb is dif"));
			curRotateNb = info.curRotateNb;
			isSame = false;
		}
		if (curRandTargetX != info.curRandTargetX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  curRandTargetX is dif"));
			curRandTargetX = info.curRandTargetX;
			isSame = false;
		}
		if (curRandTargetY != info.curRandTargetY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  curRandTargetY is dif"));
			curRandTargetY = info.curRandTargetY;
			isSame = false;
		}
		if (attributeTags.Num() != info.attributeTags.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  attributeTags num is dif"));
			attributeTags = info.attributeTags;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.attributeTags.Num(); i++)
			{
				if (attributeTags[i] != info.attributeTags[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhyspoint::copy  attributeTags not contain ") + info.attributeTags[i]);
					attributeTags = info.attributeTags;
					isSame = false;
					break;
				}
			}
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FPhysLineInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID = -1;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hostID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString className = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 hierachy;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rootGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> sonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> secondaryGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> reactionInfoNbs;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positionY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 startPointX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 startPointY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 endPointX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 endPointY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString cutStuffName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 hitCharacterID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 preHitGeoID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString preHitComponentName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString preHitActorName = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isDead;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 ATKPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 moveType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FIntLogicVector> moveOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rotateOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curMovePointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRotateNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRandTargetY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> overlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FString> attributeTags;

	void set_PHYS_LINE_INFO(PHYSLINE_INFO info)
	{
		entityID = info.entityID;
		hostID = info.hostID;
		positionX = info.positionX;
		positionY = info.positionY;
		className = info.className;
		hierachy = info.hierachy;
		rootGeoIDs = info.rootGeoIDs;
		sonGeoIDs = info.sonGeoIDs;
		secondaryGeoIDs = info.secondaryGeoIDs;
		campFlag = info.campFlag;
		reactionInfoNbs = info.reactionInfoNbs;
		startPointX = info.startPointX;
		startPointY = info.startPointY;
		endPointX = info.endPointX;
		endPointY = info.endPointY;
		yaw = info.yaw;
		cutStuffName = info.cutStuffName;
		hitCharacterID = info.hitCharacterID;
		preHitGeoID = info.preHitGeoID;
		preHitComponentName = info.preHitComponentName;
		preHitActorName = info.preHitActorName;
		if (info.isDead == 0)isDead = false;
		else isDead = true;
		ATKPercent = info.ATKPercent;
		moveType = info.moveType;
		for (int32 i = 0; i < info.moveOrder.Num(); i++)
		{
			FIntLogicVector movePoint;
			movePoint.set_LOGIC_VECTOR(info.moveOrder[i]);
			moveOrder.Add(movePoint);
		}
		rotateOrder = info.rotateOrder;
		curMovePointNb = info.curMovePointNb;
		curRotateNb = info.curRotateNb;
		curRandTargetX = info.curRandTargetX;
		curRandTargetY = info.curRandTargetY;
		overlapGeoIDs = info.overlapGeoIDs;
		attributeTags = info.attributeTags;
	}

	PHYSLINE_INFO assign_PHYS_LINE_INFO()
	{
		PHYSLINE_INFO info;
		info.campFlag = campFlag;
		info.className = className;
		info.cutStuffName = cutStuffName;
		info.endPointX = endPointX;
		info.endPointY = endPointY;
		info.entityID = entityID;
		info.hierachy = hierachy;
		info.hitCharacterID = hitCharacterID;
		info.hostID = hostID;
		info.isDead = isDead;
		info.positionX = positionX;
		info.positionY = positionY;
		info.preHitGeoID = preHitGeoID;
		info.preHitActorName = preHitActorName;
		info.preHitComponentName = preHitComponentName;
		info.reactionInfoNbs = reactionInfoNbs;
		info.rootGeoIDs = rootGeoIDs;
		info.secondaryGeoIDs = secondaryGeoIDs;
		info.sonGeoIDs = sonGeoIDs;
		info.startPointX = startPointX;
		info.startPointY = startPointY;
		info.yaw = yaw;
		info.ATKPercent = ATKPercent;
		info.moveType = moveType;
		for (int32 i = 0; i < moveOrder.Num(); i++)
		{
			LOGIC_VECTOR movePoint = moveOrder[i].assign_LOGIC_VECTOR();
			info.moveOrder.Add(movePoint);
		}
		info.rotateOrder = rotateOrder;
		info.curMovePointNb = curMovePointNb;
		info.curRotateNb = curRotateNb;
		info.curRandTargetX = curRandTargetX;
		info.curRandTargetY = curRandTargetY;
		info.overlapGeoIDs = overlapGeoIDs;
		info.attributeTags = attributeTags;
		return info;
	}

	bool copy(const FPhysLineInfo& info)
	{
		bool isSame = true;
		if (hostID != info.hostID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  hostID is dif"));
			hostID = info.hostID;
			isSame = false;
		}
		if (positionX != info.positionX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  positionX is dif"));
			positionX = info.positionX;
			isSame = false;
		}
		if (positionY != info.positionY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  positionY is dif"));
			positionY = info.positionY;
			isSame = false;
		}
		if (className != info.className)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  className is dif"));
			className = info.className;
			isSame = false;
		}
		if (hierachy != info.hierachy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  hierachy is dif"));
			hierachy = info.hierachy;
			isSame = false;
		}
		if (campFlag != info.campFlag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  campFlag is dif"));
			campFlag = info.campFlag;
			isSame = false;
		}
		if (rootGeoIDs.Num() == info.rootGeoIDs.Num())
		{
			for (int32 i = 0; i < info.rootGeoIDs.Num(); i++)
			{
				if (!rootGeoIDs.Contains(info.rootGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  rootGeo not contain ")+FString::FromInt(info.rootGeoIDs[i]));
					rootGeoIDs = info.rootGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  rootGeo num is dif"));
			rootGeoIDs = info.rootGeoIDs;
			isSame = false;
		}

		if (sonGeoIDs.Num() == info.sonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.sonGeoIDs.Num(); i++)
			{
				if (!sonGeoIDs.Contains(info.sonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  sonGeo not contain ") + FString::FromInt(info.sonGeoIDs[i]));
					sonGeoIDs = info.sonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  sonGeo num is dif"));
			sonGeoIDs = info.sonGeoIDs;
			isSame = false;
		}

		if (secondaryGeoIDs.Num() == info.secondaryGeoIDs.Num())
		{
			for (int32 i = 0; i < info.secondaryGeoIDs.Num(); i++)
			{
				if (!secondaryGeoIDs.Contains(info.secondaryGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  secondaryGeo not contain ")+ info.secondaryGeoIDs[i]);
					secondaryGeoIDs = info.secondaryGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  secondaryGeo num is dif"));
			secondaryGeoIDs = info.secondaryGeoIDs;
			isSame = false;
		}

		if (reactionInfoNbs.Num() == info.reactionInfoNbs.Num())
		{
			for (int32 i = 0; i < info.reactionInfoNbs.Num(); i++)
			{
				if (!reactionInfoNbs.Contains(info.reactionInfoNbs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  reactionPair not contain ") + info.reactionInfoNbs[i]);
					reactionInfoNbs = info.reactionInfoNbs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  reactionPair num is dif"));
			reactionInfoNbs = info.reactionInfoNbs;
			isSame = false;
		}

		if (startPointX != info.startPointX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  startPointX is dif"));
			startPointX = info.startPointX;
			isSame = false;
		}
		if (startPointY != info.startPointY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  startPointY is dif"));
			startPointY = info.startPointY;
			isSame = false;
		}
		if (endPointX != info.endPointX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  endPointX is dif"));
			endPointX = info.endPointX;
			isSame = false;
		}
		if (endPointY != info.endPointY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  endPointY is dif"));
			endPointY = info.endPointY;
			isSame = false;
		}
		if (yaw != info.yaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  yaw is dif"));
			yaw = info.yaw;
			isSame = false;
		}
		if (cutStuffName != info.cutStuffName)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  cutStuffName is dif"));
			cutStuffName = info.cutStuffName;
			isSame = false;
		}
		if (hitCharacterID != info.hitCharacterID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  hitCharacterID is dif"));
			hitCharacterID = info.hitCharacterID;
			isSame = false;
		}
		if (preHitGeoID != info.preHitGeoID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  preHitGeoID is dif"));
			preHitGeoID = info.preHitGeoID;
			isSame = false;
		}
		if (preHitComponentName != info.preHitComponentName)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  preHitComponentName is dif"));
			preHitComponentName = info.preHitComponentName;
			isSame = false;
		}
		if (preHitActorName != preHitActorName)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  preHitActorName is dif"));
			preHitActorName = info.preHitActorName;
			isSame = false;
		}
		if (isDead != info.isDead)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  isDead is dif"));
			isDead = info.isDead;
			isSame = false;
		}
		if (ATKPercent != info.ATKPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  ATKPercent is dif"));
			ATKPercent = info.ATKPercent;
			isSame = false;
		}
		if (moveType != info.moveType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  moveType is dif"));
			moveType = info.moveType;
			isSame = false;
		}
		if (moveOrder.Num() != info.moveOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  moveOrder num is dif"));
			moveOrder = info.moveOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < moveOrder.Num(); i++)
			{
				bool isPointSame = moveOrder[i].copy(info.moveOrder[i]);
				if (!isPointSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  moveOrder ") + FString::FromInt(i) + TEXT("is dif"));
					moveOrder = info.moveOrder;
					isSame = false;
					break;
				}
			}
		}
		if (rotateOrder.Num() != info.rotateOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  rotateOrder num is dif"));
			rotateOrder = info.rotateOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.rotateOrder.Num(); i++)
			{
				if (rotateOrder[i] != info.rotateOrder[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  rotateOrder not contain ") + FString::FromInt(info.rotateOrder[i]));
					rotateOrder = info.rotateOrder;
					isSame = false;
					break;
				}
			}
		}
		if (curMovePointNb != info.curMovePointNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  curMovePointNb is dif"));
			curMovePointNb = info.curMovePointNb;
			isSame = false;
		}
		if (curRotateNb != info.curRotateNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  curRotateNb is dif"));
			curRotateNb = info.curRotateNb;
			isSame = false;
		}
		if (curRandTargetX != info.curRandTargetX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  curRandTargetX is dif"));
			curRandTargetX = info.curRandTargetX;
			isSame = false;
		}
		if (curRandTargetY != info.curRandTargetY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  curRandTargetY is dif"));
			curRandTargetY = info.curRandTargetY;
			isSame = false;
		}
		if (overlapGeoIDs.Num() != info.overlapGeoIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  overlapGeoIDs num is dif"));
			overlapGeoIDs = info.overlapGeoIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.overlapGeoIDs.Num(); i++)
			{
				if (overlapGeoIDs[i] != info.overlapGeoIDs[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  overlapGeoIDs not contain ") + FString::FromInt(info.overlapGeoIDs[i]));
					overlapGeoIDs = info.overlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		if (attributeTags.Num() != info.attributeTags.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  attributeTags num is dif"));
			attributeTags = info.attributeTags;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.attributeTags.Num(); i++)
			{
				if (attributeTags[i] != info.attributeTags[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysline::copy  attributeTags not contain ") + info.attributeTags[i]);
					attributeTags = info.attributeTags;
					isSame = false;
					break;
				}
			}
		}
		return isSame;
	}
};


USTRUCT(BlueprintType)
struct FPhysActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 entityID = -1;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 hostID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString className = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 hierachy;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> rootGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> sonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> secondarySonGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 campFlag;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> reactionInfoNbs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 locX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 locY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 yaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curLifeTime;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> overlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> preOverlapCharacterIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> preOverlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> overlapGeoIDs;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isDead;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 ATKPercent;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 moveType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FIntLogicVector> moveOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> rotateOrder;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curMovePointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 curRotateNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curRandTargetX;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curRandTargetY;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FString> attributeTags;

	void set_PHYS_ACTOR_INFO(PHYSACTOR_INFO info)
	{
		entityID = info.entityID;
		hostID = info.hostID;
		yaw = info.yaw;
		className = info.className;
		hierachy = info.hierachy;
		rootGeoIDs = info.rootGeoIDs;
		sonGeoIDs = info.sonGeoIDs;
		secondarySonGeoIDs = info.secondarySonGeoIDs;
		campFlag = info.campFlag;
		reactionInfoNbs = info.reactionInfoNbs;
		locX = info.locX;
		locY = info.locY;
		curLifeTime = info.curLifeTime;
		overlapCharacterIDs = info.overlapCharacterIDs;
		preOverlapCharacterIDs = info.preOverlapCharacterIDs;
		preOverlapGeoIDs = info.preOverlapGeoIDs;
		overlapGeoIDs = info.overlapGeoIDs;
		if (info.isDead == 0) isDead = false;
		else isDead = true;
		ATKPercent = info.ATKPercent;
		moveType = info.moveType;
		for (int32 i = 0; i < info.moveOrder.Num(); i++)
		{
			FIntLogicVector movePoint;
			movePoint.set_LOGIC_VECTOR(info.moveOrder[i]);
			moveOrder.Add(movePoint);
		}
		rotateOrder = info.rotateOrder;
		curMovePointNb = info.curMovePointNb;
		curRotateNb = info.curRotateNb;
		curRandTargetX = info.curRandTargetX;
		curRandTargetY = info.curRandTargetY;
		attributeTags = info.attributeTags;
	}

	PHYSACTOR_INFO assign_PHYS_ACTOR_INFO()
	{
		PHYSACTOR_INFO info;
		info.campFlag = campFlag;
		info.className = className;
		info.curLifeTime = curLifeTime;
		info.entityID = entityID;
		info.hierachy = hierachy;
		info.hostID = hostID;
		info.isDead = isDead;
		info.overlapCharacterIDs = overlapCharacterIDs;
		info.overlapGeoIDs = overlapGeoIDs;
		info.locX = locX;
		info.locY = locY;
		info.preOverlapCharacterIDs = preOverlapCharacterIDs;
		info.preOverlapGeoIDs = preOverlapGeoIDs;
		info.reactionInfoNbs = reactionInfoNbs;
		info.rootGeoIDs = rootGeoIDs;
		info.secondarySonGeoIDs = secondarySonGeoIDs;
		info.sonGeoIDs = sonGeoIDs;
		info.yaw = yaw;
		info.ATKPercent = ATKPercent;
		info.moveType = moveType;
		for (int32 i = 0; i < moveOrder.Num(); i++)
		{
			LOGIC_VECTOR movePoint = moveOrder[i].assign_LOGIC_VECTOR();
			info.moveOrder.Add(movePoint);
		}
		info.rotateOrder = rotateOrder;
		info.curMovePointNb = curMovePointNb;
		info.curRotateNb = curRotateNb;
		info.curRandTargetX = curRandTargetX;
		info.curRandTargetY = curRandTargetY;
		info.attributeTags = attributeTags;
		return info;
	}

	bool copy(const FPhysActorInfo& info)
	{
		bool isSame = true;

		if (hostID != info.hostID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  hostID is dif"));
			hostID = info.hostID;
			isSame = false;
		}
		if (yaw != info.yaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  yaw is dif"));
			yaw = info.yaw;
			isSame = false;
		}
		if (className != info.className)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  className is dif"));
			className = info.className;
			isSame = false;
		}
		if (hierachy != info.hierachy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  hierachy is dif"));
			hierachy = info.hierachy;
			isSame = false;
		}
		if (campFlag != info.campFlag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  campFlag is dif"));
			campFlag = info.campFlag;
			isSame = false;
		}

		if (locX != info.locX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  locX is dif"));
			locX = info.locX;
			isSame = false;
		}
		if (locY != info.locY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  locY is dif"));
			locY = info.locY;
			isSame = false;
		}
		if (curLifeTime != info.curLifeTime)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  curLifeTime is dif"));
			curLifeTime = info.curLifeTime;
			isSame = false;
		}
		if (overlapCharacterIDs.Num() == info.overlapCharacterIDs.Num())
		{
			for (int32 i=0; i<info.overlapCharacterIDs.Num(); i++)
			{
				if (!overlapCharacterIDs.Contains(info.overlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  overlapCharacter not contain ") +FString::FromInt(info.overlapCharacterIDs[i]));
					overlapCharacterIDs = info.overlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  overlapC num is dif"));
			overlapCharacterIDs = info.overlapCharacterIDs;
			isSame = false;
		}
		if (preOverlapCharacterIDs.Num() != info.preOverlapCharacterIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  preOverlapC num is dif"));
			preOverlapCharacterIDs = info.preOverlapCharacterIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.preOverlapCharacterIDs.Num(); i++)
			{
				if (!preOverlapCharacterIDs.Contains(info.preOverlapCharacterIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy preOverlapC not contain ") + FString::FromInt(info.preOverlapCharacterIDs[i]));
					preOverlapCharacterIDs = info.preOverlapCharacterIDs;
					isSame = false;
					break;
				}
			}
		}
		if (preOverlapGeoIDs.Num() != info.preOverlapGeoIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  preOverlapGeo num is dif"));
			preOverlapGeoIDs = info.preOverlapGeoIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.preOverlapGeoIDs.Num(); i++)
			{
				if (!preOverlapGeoIDs.Contains(info.preOverlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  preOverlapG not contain ")+FString::FromInt(info.preOverlapGeoIDs[i]));
					preOverlapGeoIDs = info.preOverlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		if (overlapGeoIDs.Num() != info.overlapGeoIDs.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  overlapGeo num is dif"));
			overlapGeoIDs = info.overlapGeoIDs;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.overlapGeoIDs.Num(); i++)
			{
				if (!overlapGeoIDs.Contains(info.overlapGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy overlapGeo not contain ")+FString::FromInt(info.overlapGeoIDs[i]));
					overlapGeoIDs = info.overlapGeoIDs;
					isSame = false;
					break;
				}
			}
		}

		if (rootGeoIDs.Num() == info.rootGeoIDs.Num())
		{
			for (int32 i = 0; i < info.rootGeoIDs.Num(); i++)
			{
				if (!rootGeoIDs.Contains(info.rootGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy rootGeo not contain ") + FString::FromInt(info.rootGeoIDs[i]));
					rootGeoIDs = info.rootGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  rootGeo num is dif"));
			rootGeoIDs = info.rootGeoIDs;
			isSame = false;
		}

		if (sonGeoIDs.Num() == info.sonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.sonGeoIDs.Num(); i++)
			{
				if (!sonGeoIDs.Contains(info.sonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy sonGeo not contain ") + FString::FromInt(info.sonGeoIDs[i]));
					sonGeoIDs = info.sonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  sonGeo num is dif"));
			sonGeoIDs = info.sonGeoIDs;
			isSame = false;
		}
		if (secondarySonGeoIDs.Num() == info.secondarySonGeoIDs.Num())
		{
			for (int32 i = 0; i < info.secondarySonGeoIDs.Num(); i++)
			{
				if (!secondarySonGeoIDs.Contains(info.secondarySonGeoIDs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy secondaryGeo not contain ") + FString::FromInt(info.secondarySonGeoIDs[i]));
					secondarySonGeoIDs = info.secondarySonGeoIDs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  secondaryGeo num is dif"));
			secondarySonGeoIDs = info.secondarySonGeoIDs;
			isSame = false;
		}

		if (reactionInfoNbs.Num() == info.reactionInfoNbs.Num())
		{
			for (int32 i = 0; i < info.reactionInfoNbs.Num(); i++)
			{
				if (!reactionInfoNbs.Contains(info.reactionInfoNbs[i]))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy reactionPair not contain ") + FString::FromInt(info.reactionInfoNbs[i]));
					reactionInfoNbs = info.reactionInfoNbs;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  reactionPair num is dif"));
			reactionInfoNbs = info.reactionInfoNbs;
			isSame = false;
		}
		if (isDead != info.isDead)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy isDead is dif"));
			isDead = info.isDead;
			isSame = false;
		}
		if (ATKPercent != info.ATKPercent)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy ATKPercent is dif"));
			ATKPercent = info.ATKPercent;
			isSame = false;
		}
		if (moveType != info.moveType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  moveType is dif"));
			moveType = info.moveType;
			isSame = false;
		}
		if (moveOrder.Num() != info.moveOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  moveOrder num is dif"));
			moveOrder = info.moveOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < moveOrder.Num(); i++)
			{
				bool isPointSame = moveOrder[i].copy(info.moveOrder[i]);
				if (!isPointSame)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  moveOrder ") + FString::FromInt(i) + TEXT("is dif"));
					moveOrder = info.moveOrder;
					isSame = false;
					break;
				}
			}
		}
		if (rotateOrder.Num() != info.rotateOrder.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  rotateOrder num is dif"));
			rotateOrder = info.rotateOrder;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.rotateOrder.Num(); i++)
			{
				if (rotateOrder[i] != info.rotateOrder[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  rotateOrder not contain ") + FString::FromInt(info.rotateOrder[i]));
					rotateOrder = info.rotateOrder;
					isSame = false;
					break;
				}
			}
		}
		if (curMovePointNb != info.curMovePointNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  curMovePointNb is dif"));
			curMovePointNb = info.curMovePointNb;
			isSame = false;
		}
		if (curRotateNb != info.curRotateNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  curRotateNb is dif"));
			curRotateNb = info.curRotateNb;
			isSame = false;
		}
		if (curRandTargetX != info.curRandTargetX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  curRandTargetX is dif"));
			curRandTargetX = info.curRandTargetX;
			isSame = false;
		}
		if (curRandTargetY != info.curRandTargetY)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  curRandTargetY is dif"));
			curRandTargetY = info.curRandTargetY;
			isSame = false;
		}
		if (attributeTags.Num() != info.attributeTags.Num())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  attributeTags num is dif"));
			attributeTags = info.attributeTags;
			isSame = false;
		}
		else
		{
			for (int32 i = 0; i < info.attributeTags.Num(); i++)
			{
				if (attributeTags[i] != info.attributeTags[i])
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FPhysactor::copy  attributeTags not contain ") + info.attributeTags[i]);
					attributeTags = info.attributeTags;
					isSame = false;
					break;
				}
			}
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FKBEReactionInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString reactionType = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString hostTag = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString reactionTag = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString spawnActorClass = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString transformActorClass1 = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString transformActorClass2 = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString modifyTag1 = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString modifyTag2 = "NULL";

	void set_REACTION_INFO(REACTION_INFO info)
	{
		reactionType = info.reactionType;
		hostTag = info.hostTag;
		reactionTag = info.reactionTag;
		spawnActorClass = info.spawnActorClass;
		transformActorClass1 = info.transformActorClass1;
		transformActorClass2 = info.transformActorClass2;
		modifyTag1 = info.modifyTag1;
		modifyTag2 = info.modifyTag2;
	}

	REACTION_INFO assign_REACTION_INFO()
	{
		REACTION_INFO info;
		info.hostTag = hostTag;
		info.modifyTag1 = modifyTag1;
		info.modifyTag2 = modifyTag2;
		info.reactionTag = reactionTag;
		info.reactionType = reactionType;
		info.spawnActorClass = spawnActorClass;
		info.transformActorClass1 = transformActorClass1;
		info.transformActorClass2 = transformActorClass2;
		return info;
	}

	bool copy(const FKBEReactionInfo& info)
	{
		bool isSame = true;
		if (reactionType != info.reactionType)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy reactionType is dif"));
			reactionType = info.reactionType;
			isSame = false;
		}
		if (hostTag != info.hostTag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy hostTag is dif"));
			hostTag = info.hostTag;
			isSame = false;
		}
		if (reactionTag != info.reactionTag)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy reactionTag is dif"));
			reactionTag = info.reactionTag;
			isSame = false;
		}
		if (spawnActorClass != info.spawnActorClass)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy spawnActorClass is dif"));
			spawnActorClass = info.spawnActorClass;
			isSame = false;
		}
		if (transformActorClass1 != info.transformActorClass1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy transferClass1 is dif"));
			transformActorClass1 = info.transformActorClass1;
			isSame = false;
		}
		if (transformActorClass2 != info.transformActorClass2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy transferClass2 is dif"));
			transformActorClass2 = info.transformActorClass2;
			isSame = false;
		}
		if (modifyTag1 != info.modifyTag1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy modifyClass1 is dif"));
			modifyTag1 = info.modifyTag1;
			isSame = false;
		}
		if (modifyTag2 != info.modifyTag2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionInfo::copy modifyTag2 is dif"));
			modifyTag2 = info.modifyTag2;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FReactionPairInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 reactionPairID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 reactionActorID1;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 reactionActorID2;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 sonGeoID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FKBEReactionInfo reactionInfo;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isPairValid;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FIntLogicVector reactionLoc;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 reactionYaw;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool hasOccur;

	void set_REACTION_PAIR_INFO(REACTION_PAIR_INFO info)
	{
		reactionPairID = info.reactionPairID;
		reactionActorID1 = info.reactionActorID1;
		reactionActorID2 = info.reactionActorID2;
		sonGeoID = info.sonGeoID;
		reactionInfo.set_REACTION_INFO(info.reactionInfo);
		if (info.isPairValid == 0) isPairValid = false;
		else isPairValid = true;
		reactionLoc.set_LOGIC_VECTOR(info.reactionLoc);
		reactionYaw = info.reactionYaw;
		if (info.hasOccur == 0) hasOccur = false;
		else hasOccur = true;
	}

	REACTION_PAIR_INFO assign_REACTION_PAIR_INFO()
	{
		REACTION_PAIR_INFO info;
		info.hasOccur = hasOccur;
		info.isPairValid = isPairValid;
		info.reactionActorID1 = reactionActorID1;
		info.reactionActorID2 = reactionActorID2;
		info.reactionInfo = reactionInfo.assign_REACTION_INFO();
		info.reactionLoc.X = reactionLoc.X;
		info.reactionLoc.Y = reactionLoc.Y;
		info.reactionPairID = reactionPairID;
		info.reactionYaw = reactionYaw;
		info.sonGeoID = sonGeoID;
		return info;
	}

	bool copy(const FReactionPairInfo& info)
	{
		bool isSame = true;
		if (reactionActorID1 != info.reactionActorID1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy actor1 is dif"));
			reactionActorID1 = info.reactionActorID1;
			isSame = false;
		}
		if (reactionActorID2 != info.reactionActorID2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy actor2 is dif"));
			reactionActorID2 = info.reactionActorID1;
			isSame = false;
		}
		if (sonGeoID != info.sonGeoID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy sonGeo is dif"));
			sonGeoID = info.sonGeoID;
			isSame = false;
		}
		bool isReactionInfoSame = reactionInfo.copy(info.reactionInfo);
		if (!isReactionInfoSame)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy reactionInfo is dif"));
			isSame = false;
		}
		if (isPairValid != info.isPairValid)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy isPairValid is dif"));
			isPairValid = info.isPairValid;
			isSame = false;
		}
		bool isReactionLocSame = reactionLoc.copy(info.reactionLoc);
		if (!isReactionLocSame)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy reactionLoc is dif"));
			isSame = false;
		}
		if (reactionYaw != info.reactionYaw)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy reactionYaw is dif"));
			reactionYaw = info.reactionYaw;
			isSame = false;
		}
		if (hasOccur != info.hasOccur)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FReactionPair::copy hasOccur is dif"));
			hasOccur = info.hasOccur;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FEnermySpawnPointCorrectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 spawnPointNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curSpawnRound;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curFrame;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curSpawnCharacterID;

	void set_ENERMY_SPAWN_POINT_CORRECT_INFO(ENERMY_SPAWN_POINT_CORRECT_INFO info)
	{
		spawnPointNb = info.spawnPointNb;
		curSpawnRound = info.curSpawnRound;
		curFrame = info.curFrame;
		curSpawnCharacterID = info.curSpawnCharacterID;
	}

	ENERMY_SPAWN_POINT_CORRECT_INFO assign_ENERMY_SPAWN_POINT_CORRECT_INFO()
	{
		ENERMY_SPAWN_POINT_CORRECT_INFO info;
		info.curFrame = curFrame;
		info.curSpawnCharacterID = curSpawnCharacterID;
		info.curSpawnRound = curSpawnRound;
		info.spawnPointNb = spawnPointNb;
		return info;
	}

	bool copy(const FEnermySpawnPointCorrectInfo& info)
	{
		bool isSame = false;
		if (spawnPointNb != info.spawnPointNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermySpawnPoint::copy spawnPointNb is dif"));
			spawnPointNb = info.spawnPointNb;
			isSame = false;
		}
		if (curSpawnRound != info.curSpawnRound)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermySpawnPoint::copy spawnRound is dif"));
			curSpawnRound = info.curSpawnRound;
			isSame = false;
		}
		if (curFrame != info.curFrame)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermySpawnPoint::copy curFrame is dif"));
			curFrame = info.curFrame;
			isSame = false;
		}
		if (curSpawnCharacterID != info.curSpawnCharacterID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermySpawnPoint::copy spawnCharacterID is dif"));
			curSpawnCharacterID = info.curSpawnCharacterID;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FEnermyGroupCorrectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 groupNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isTriggerOn;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	bool isValid;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEnermySpawnPointCorrectInfo> spawnPointInfoList;

	void set_ENERMY_GROUP_CORRECT_INFO(ENERMY_GROUP_CORRECT_INFO info)
	{
		groupNb = info.groupNb;
		if (info.isTriggerOn == 0) isTriggerOn = false;
		else isTriggerOn = true;
		if (info.isValid == 0) isValid = false;
		else isValid = true;
		for (int32 i=0; i<info.spawnPointInfoList.Num(); i++)
		{
			FEnermySpawnPointCorrectInfo newInfo;
			newInfo.set_ENERMY_SPAWN_POINT_CORRECT_INFO(info.spawnPointInfoList[i]);
			spawnPointInfoList.Add(newInfo);
		}
	}

	ENERMY_GROUP_CORRECT_INFO assign_ENERMY_GROUP_CORRECT_INFO()
	{
		ENERMY_GROUP_CORRECT_INFO info;
		info.groupNb = groupNb;
		info.isTriggerOn = isTriggerOn;
		info.isValid = isValid;
		for (int32 i=0; i<spawnPointInfoList.Num(); i++)
		{
			ENERMY_SPAWN_POINT_CORRECT_INFO pointInfo = spawnPointInfoList[i].assign_ENERMY_SPAWN_POINT_CORRECT_INFO();
			info.spawnPointInfoList.Add(pointInfo);
		}
		return info;
	}

	bool copy(const FEnermyGroupCorrectInfo& info)
	{
		bool isSame = false;
		if (groupNb != info.groupNb)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy groupNb is dif"));
			groupNb = info.groupNb;
			isSame = false;
		}
		if (isTriggerOn != info.isTriggerOn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy isTriggerOn is dif"));
			isTriggerOn = info.isTriggerOn;
			isSame = false;
		}
		if (isValid != info.isValid)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy isValid is dif"));
			isValid = info.isValid;
			isSame = false;
		}
		if (spawnPointInfoList.Num() == info.spawnPointInfoList.Num())
		{
			for (int32 i = 0; i < spawnPointInfoList.Num(); i++)
			{
				bool isFoundSpawnPoint = false;
				for (int32 j = 0; j < info.spawnPointInfoList.Num(); j++)
				{
					if (spawnPointInfoList[i].spawnPointNb == info.spawnPointInfoList[j].spawnPointNb)
					{
						isFoundSpawnPoint = true;
						bool isSpawnPointSame = spawnPointInfoList[i].copy(info.spawnPointInfoList[j]);
						if (!isSpawnPointSame)
						{
							GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy spawnPoint is dif ") + FString::FromInt(i));
							isSame = false;
						}
						break;
					}
				}
				if (!isFoundSpawnPoint)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy not find point"));
					spawnPointInfoList = info.spawnPointInfoList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("TransferStructs.h/FEnermyGroup::copy spawnPOint num is dif"));
			spawnPointInfoList = info.spawnPointInfoList;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FCorrectInfoList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FCharacterCorrectInfo> characterCorrectList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPhysPolyInfo> physpolyCorrectList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPhysPointInfo> physpointCorrectList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPhysLineInfo> physlineCorrectList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPhysActorInfo> physactorCorrectList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FReactionPairInfo> reactionPairInfoList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FEnermyGroupCorrectInfo> enermyGroupCorrectInfoList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString gameProgress = "NULL";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 curRandSeed;

	void set_CORRECT_INFO_LIST(CORRECT_INFO_LIST list)
	{
		frameNb = list.frameNb;
		gameProgress = list.gameProgress;
		curRandSeed = list.randSeed;
		for (int32 i = 0; i < list.characterCorrectList.Num(); i++)
		{
			FCharacterCorrectInfo newInfo;
			newInfo.set_CHARACTER_CORRECT_INFO(list.characterCorrectList[i]);
			characterCorrectList.Add(newInfo);
		}
		for (int32 i=0; i<list.physpolyCorrectList.Num(); i++)
		{
			FPhysPolyInfo newInfo;
			newInfo.set_PHYS_POLY_INFO(list.physpolyCorrectList[i]);
			physpolyCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < list.physpointCorrectList.Num(); i++)
		{
			FPhysPointInfo newInfo;
			newInfo.set_PHYS_POINT_INFO(list.physpointCorrectList[i]);
			physpointCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < list.physlineCorrectList.Num(); i++)
		{
			FPhysLineInfo newInfo;
			newInfo.set_PHYS_LINE_INFO(list.physlineCorrectList[i]);
			physlineCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < list.physactorCorrectList.Num(); i++)
		{
			FPhysActorInfo newInfo;
			newInfo.set_PHYS_ACTOR_INFO(list.physactorCorrectList[i]);
			physactorCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < list.reactionPairInfoList.Num(); i++)
		{
			FReactionPairInfo newInfo;
			newInfo.set_REACTION_PAIR_INFO(list.reactionPairInfoList[i]);
			reactionPairInfoList.Add(newInfo);
		}
		for (int32 i = 0; i < list.enermyGroupCorrectInfoList.Num(); i++)
		{
			FEnermyGroupCorrectInfo newInfo;
			newInfo.set_ENERMY_GROUP_CORRECT_INFO(list.enermyGroupCorrectInfoList[i]);
			enermyGroupCorrectInfoList.Add(newInfo);
		}
	}

	CORRECT_INFO_LIST assign_CORRECT_INFO_LIST()
	{
		CORRECT_INFO_LIST correctList;
		correctList.frameNb = frameNb;
		correctList.gameProgress = gameProgress;
		correctList.randSeed = curRandSeed;
		for (int32 i = 0; i < characterCorrectList.Num(); i++)
		{
			CHARACTER_CORRECT_INFO newInfo = characterCorrectList[i].assign_CHARACTER_CORRECT_INFO();
			correctList.characterCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < physpolyCorrectList.Num(); i++)
		{
			PHYSPOLY_INFO newInfo = physpolyCorrectList[i].assign_PHYS_POLY_INFO();
			correctList.physpolyCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < physpointCorrectList.Num(); i++)
		{
			PHYSPOINT_INFO newInfo = physpointCorrectList[i].assign_PHYS_POINT_INFO();
			correctList.physpointCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < physlineCorrectList.Num(); i++)
		{
			PHYSLINE_INFO newInfo = physlineCorrectList[i].assign_PHYS_LINE_INFO();
			correctList.physlineCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < physactorCorrectList.Num(); i++)
		{
			PHYSACTOR_INFO newInfo = physactorCorrectList[i].assign_PHYS_ACTOR_INFO();
			correctList.physactorCorrectList.Add(newInfo);
		}
		for (int32 i = 0; i < reactionPairInfoList.Num(); i++)
		{
			REACTION_PAIR_INFO newInfo = reactionPairInfoList[i].assign_REACTION_PAIR_INFO();
			correctList.reactionPairInfoList.Add(newInfo);
		}
		for (int32 i = 0; i < enermyGroupCorrectInfoList.Num(); i++)
		{
			ENERMY_GROUP_CORRECT_INFO newInfo = enermyGroupCorrectInfoList[i].assign_ENERMY_GROUP_CORRECT_INFO();
			correctList.enermyGroupCorrectInfoList.Add(newInfo);
		}
		return correctList;
	}

	bool copy(const FCorrectInfoList& info)
	{
		bool isSame = true;
		if (characterCorrectList.Num() == info.characterCorrectList.Num())
		{
			for (int32 i=0; i<characterCorrectList.Num(); i++)
			{
				bool isFoundCharacter = false;
				for (int32 j=0; j<info.characterCorrectList.Num(); j++)
				{
					if (characterCorrectList[i].entityID == info.characterCorrectList[j].entityID)
					{
						isFoundCharacter = true;
						bool isCharacterSame = characterCorrectList[i].copy(info.characterCorrectList[j]);
						if (!isCharacterSame) isSame = false;
						break;
					}
				}
				if (!isFoundCharacter || !isSame)
				{
					characterCorrectList = info.characterCorrectList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			characterCorrectList = info.characterCorrectList;
			isSame = false;
		}

		if (physpolyCorrectList.Num() == info.physpolyCorrectList.Num())
		{
			for (int32 i = 0; i < physpolyCorrectList.Num(); i++)
			{
				bool isFoundPoly = false;
				for (int32 j = 0; j < info.physpolyCorrectList.Num(); j++)
				{
					if (physpolyCorrectList[i].entityID == info.physpolyCorrectList[j].entityID)
					{
						isFoundPoly = true;
						bool isPolySame = physpolyCorrectList[i].copy(info.physpolyCorrectList[j]);
						if (!isPolySame) isSame = false;
						break;
					}
				}
				if (!isFoundPoly || !isSame)
				{
					physpolyCorrectList = info.physpolyCorrectList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			physpolyCorrectList = info.physpolyCorrectList;
			isSame = false;
		}

		if (physlineCorrectList.Num() == info.physlineCorrectList.Num())
		{
			for (int32 i = 0; i < physlineCorrectList.Num(); i++)
			{
				bool isFoundLine = false;
				for (int32 j = 0; j < info.physlineCorrectList.Num(); j++)
				{
					if (physlineCorrectList[i].entityID == info.physlineCorrectList[j].entityID)
					{
						isFoundLine = true;
						bool isLineSame = physlineCorrectList[i].copy(info.physlineCorrectList[j]);
						if (!isLineSame) isSame = false;
						break;
					}
				}
				if (!isFoundLine || !isSame)
				{
					physlineCorrectList = info.physlineCorrectList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			physlineCorrectList = info.physlineCorrectList;
			isSame = false;
		}

		if (physpointCorrectList.Num() == info.physpointCorrectList.Num())
		{
			for (int32 i = 0; i < physpointCorrectList.Num(); i++)
			{
				bool isFoundPoint = false;
				for (int32 j = 0; j < info.physpointCorrectList.Num(); j++)
				{
					if (physpointCorrectList[i].entityID == info.physpointCorrectList[j].entityID)
					{
						isFoundPoint = true;
						bool isPointSame = physpointCorrectList[i].copy(info.physpointCorrectList[j]);
						if (!isPointSame) isSame = false;
						break;
					}
				}
				if (!isFoundPoint || !isSame)
				{
					physpointCorrectList = info.physpointCorrectList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			physpointCorrectList = info.physpointCorrectList;
			isSame = false;
		}

		if (physactorCorrectList.Num() == info.physactorCorrectList.Num())
		{
			for (int32 i = 0; i < physactorCorrectList.Num(); i++)
			{
				bool isFoundActor = false;
				for (int32 j = 0; j < info.physactorCorrectList.Num(); j++)
				{
					if (physactorCorrectList[i].entityID == info.physactorCorrectList[j].entityID)
					{
						isFoundActor = true;
						bool isActorSame = physactorCorrectList[i].copy(info.physactorCorrectList[j]);
						if (!isActorSame) isSame = false;
						break;
					}
				}
				if (!isFoundActor || !isSame)
				{
					physactorCorrectList = info.physactorCorrectList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			physactorCorrectList = info.physactorCorrectList;
			isSame = false;
		}

		if (reactionPairInfoList.Num() == info.reactionPairInfoList.Num())
		{
			for (int32 i = 0; i < reactionPairInfoList.Num(); i++)
			{
				bool isFoundReactionPair = false;
				for (int32 j = 0; j < info.reactionPairInfoList.Num(); j++)
				{
					if (reactionPairInfoList[i].reactionPairID == info.reactionPairInfoList[j].reactionPairID)
					{
						isFoundReactionPair = true;
						bool isPairSame = reactionPairInfoList[i].copy(info.reactionPairInfoList[j]);
						if (!isPairSame) isSame = false;
						break;
					}
				}
				if (!isFoundReactionPair || !isSame)
				{
					reactionPairInfoList = info.reactionPairInfoList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			reactionPairInfoList = info.reactionPairInfoList;
			isSame = false;
		}

		if (enermyGroupCorrectInfoList.Num() == info.enermyGroupCorrectInfoList.Num())
		{
			for (int32 i = 0; i < enermyGroupCorrectInfoList.Num(); i++)
			{
				bool isFoundGroup = false;
				for (int32 j = 0; j < info.enermyGroupCorrectInfoList.Num(); j++)
				{
					if (enermyGroupCorrectInfoList[i].groupNb == info.enermyGroupCorrectInfoList[j].groupNb)
					{
						isFoundGroup = true;
						bool isGroupSame = enermyGroupCorrectInfoList[i].copy(info.enermyGroupCorrectInfoList[j]);
						if (!isGroupSame) isSame = false;
						break;
					}
				}
				if (!isFoundGroup || !isSame)
				{
					enermyGroupCorrectInfoList = info.enermyGroupCorrectInfoList;
					isSame = false;
					break;
				}
			}
		}
		else
		{
			enermyGroupCorrectInfoList = info.enermyGroupCorrectInfoList;
			isSame = false;
		}

		if (gameProgress != info.gameProgress)
		{
			gameProgress = info.gameProgress;
			isSame = false;
		}

		if (curRandSeed != info.curRandSeed)
		{
			curRandSeed = info.curRandSeed;
			isSame = false;
		}
		return isSame;
	}
};

USTRUCT(BlueprintType)
struct FLogicFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FPlayerOperationInfo> playerOperationList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FAICharacterOperationInfo> AIOperationList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 frameNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 roundNb;

	void set_LOGIC_FRAME(LOGIC_FRAME info)
	{
		frameNb = info.frameNb;
		roundNb = info.roundNb;
		for (int32 i = 0; i < info.playerOperationList.Num(); i++)
		{
			FPlayerOperationInfo newInfo;
			newInfo.set_PLAYER_OPERATION_INFO(info.playerOperationList[i]);
			playerOperationList.Add(newInfo);
		}
		for (int32 i=0; i<info.aiCharacterOperationList.Num(); i++)
		{
			FAICharacterOperationInfo newInfo;
			newInfo.set_AI_CHARACTER_OPERATION_INFO(info.aiCharacterOperationList[i]);
			AIOperationList.Add(newInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FLogicFrameList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FLogicFrame> values;

	void set_LOGIC_FRAME_LIST(LOGIC_FRAME_LIST list)
	{
		for (int32 i = 0; i < list.values.Num(); i++)
		{
			FLogicFrame newInfo;
			newInfo.set_LOGIC_FRAME(list.values[i]);
			values.Add(newInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FTeamWinInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 teamNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> accountIDList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 winNb;

	void set_TEAM_WIN_INFO(TEAM_WIN_INFO info)
	{
		teamNb = info.teamNb;
		winNb = info.winNb;
		for (int32 i = 0; i < info.accountIDList.Num(); i++)
		{
			accountIDList.Add(info.accountIDList[i]);
		}
	}

	TEAM_WIN_INFO assign_TEAM_WIN_INFO()
	{
		TEAM_WIN_INFO teamInfo;
		teamInfo.teamNb = teamNb;
		for (int32 i=0; i<accountIDList.Num(); i++)
		{
			teamInfo.accountIDList.Add(accountIDList[i]);
		}
		teamInfo.winNb = winNb;
		return teamInfo;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerBattleStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 accountID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 killEnermyNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 outputScore;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 positiveScore;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 negativeScore;

	void set_PLAYER_BATTLE_STATUS(PLAYER_BATTLE_STATUS info)
	{
		accountID = info.accountID;
		killEnermyNb = info.killEnermyNb;
		outputScore = info.outputScore;
		positiveScore = info.positiveScore;
		negativeScore = info.negativeScore;
	}

	PLAYER_BATTLE_STATUS assign_PLAYER_BATTLE_STATUS()
	{
		PLAYER_BATTLE_STATUS playerBattleStatus;
		playerBattleStatus.accountID = accountID;
		playerBattleStatus.killEnermyNb = killEnermyNb;
		playerBattleStatus.negativeScore = negativeScore;
		playerBattleStatus.outputScore = outputScore;
		playerBattleStatus.positiveScore = positiveScore;
		return playerBattleStatus;
	}

	void reset()
	{
		killEnermyNb = 0;
		negativeScore = 0;
		outputScore = 0;
		positiveScore = 0;
	}
};

USTRUCT(BlueprintType)
struct FBattleTeamInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 teamNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FPlayerBattleStatus> playerBattleStatusList;

	void set_BATTLE_TEAM_INFO(BATTLE_TEAM_INFO info)
	{
		teamNb = info.teamNb;
		for (int32 i=0; i<info.playerBattleStatusList.Num(); i++)
		{
			FPlayerBattleStatus newStatus;
			newStatus.set_PLAYER_BATTLE_STATUS(info.playerBattleStatusList[i]);
			playerBattleStatusList.Add(newStatus);
		}
	}

	BATTLE_TEAM_INFO assign_BATTLE_TEAM_INFO()
	{
		BATTLE_TEAM_INFO teamInfo;
		teamInfo.teamNb = teamNb;
		for (int32 i=0; i<playerBattleStatusList.Num(); i++)
		{
			PLAYER_BATTLE_STATUS status = playerBattleStatusList[i].assign_PLAYER_BATTLE_STATUS();
			teamInfo.playerBattleStatusList.Add(status);
		}
		return teamInfo;
	}
};

USTRUCT(BlueprintType)
struct FBattleResultRound
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 roundNb;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> winTeamList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FBattleTeamInfo> teams;

	void set_BATTLE_RESULT_ROUND(BATTLE_RESULT_ROUND info)
	{
		roundNb = info.roundNb;
		for (int32 i = 0; i < info.winTeamList.Num(); i++)
		{
			winTeamList.Add((int32)info.winTeamList[i]);
		}
		for (int32 i=0; i<info.teams.Num(); i++)
		{
			FBattleTeamInfo newInfo;
			newInfo.set_BATTLE_TEAM_INFO(info.teams[i]);
			teams.Add(newInfo);
		}
	}

	BATTLE_RESULT_ROUND assign_BATTLE_RESULT_ROUND()
	{
		BATTLE_RESULT_ROUND battleResultRound;
		battleResultRound.roundNb = roundNb;
		for (int32 i=0; i<winTeamList.Num(); i++)
		{
			battleResultRound.winTeamList.Add((int8)winTeamList[i]);
		}
		for (int32 i=0; i<teams.Num(); i++)
		{
			BATTLE_TEAM_INFO info = teams[i].assign_BATTLE_TEAM_INFO();
			battleResultRound.teams.Add(info);
		}
		return battleResultRound;
	}
};

USTRUCT(BlueprintType)
struct FBattleResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FTeamWinInfo> teamWinInfoList;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FBattleResultRound> battleResultList;

	void set_BATTLE_RESULT(BATTLE_RESULT info)
	{
		for (int32 i = 0; i < info.teamWinInfoList.Num(); i++)
		{
			FTeamWinInfo newInfo;
			newInfo.set_TEAM_WIN_INFO(info.teamWinInfoList[i]);
			teamWinInfoList.Add(newInfo);
		}
		for (int32 i = 0; i < info.battleResultList.Num(); i++)
		{
			FBattleResultRound newInfo;
			newInfo.set_BATTLE_RESULT_ROUND(info.battleResultList[i]);
			battleResultList.Add(newInfo);
		}
	}

	BATTLE_RESULT assign_BATTLE_RESULT()
	{
		BATTLE_RESULT result;
		for (int32 i=0; i<teamWinInfoList.Num(); i++)
		{
			TEAM_WIN_INFO info = teamWinInfoList[i].assign_TEAM_WIN_INFO();
			result.teamWinInfoList.Add(info);
		}
		for (int32 i=0; i<battleResultList.Num(); i++)
		{
			BATTLE_RESULT_ROUND info = battleResultList[i].assign_BATTLE_RESULT_ROUND();
			result.battleResultList.Add(info);
		}
		return result;
	}

	void reset()
	{
		teamWinInfoList.Empty();
		battleResultList.Empty();
	}
};

USTRUCT(BlueprintType)
struct FReqTeamMatchData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString playerName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 playerEntityID;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString playerRoleType;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString matchStatus;

	void set_REQ_TEAM_MATCH_DATA(REQ_TEAM_MATCH_DATA info)
	{
		playerName = info.playerName;
		playerEntityID = info.playerEntityID;
		playerRoleType = info.playerRoleType;
		matchStatus = info.matchStatus;
	}

	REQ_TEAM_MATCH_DATA assign_REQ_TEAM_MATCH_DATA()
	{
		REQ_TEAM_MATCH_DATA data;
		data.playerName = playerName;
		data.playerEntityID = playerEntityID;
		data.playerRoleType = playerRoleType;
		data.matchStatus = matchStatus;
		return data;
	}
};

USTRUCT(BlueprintType)
struct FBattleResultRoundList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FBattleResultRound> values;

	void set_REQ_TEAM_MATCH_DATA(BATTLE_RESULT_ROUND_LIST list)
	{
		for (int32 i=0; i<list.values.Num(); i++)
		{
			FBattleResultRound newRoundInfo;
			newRoundInfo.set_BATTLE_RESULT_ROUND(list.values[i]);
			values.Add(newRoundInfo);
		}
	}
};

USTRUCT(BlueprintType)
struct FRuneInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString runeName;
	
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	int32 runeTag;

	void set_RUNE_INFO(RUNEINFO info)
	{
		runeName = info.RuneName;
		runeTag = info.RuneTag;
	}
};

USTRUCT(BlueprintType)
struct FRuneInfoList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FRuneInfo> values;

	void set_REQ_TEAM_MATCH_DATA(RUNEINFOLIST list)
	{
		for (int32 i = 0; i < list.values.Num(); i++)
		{
			FRuneInfo info;
			info.set_RUNE_INFO(list.values[i]);
			values.Add(info);
		}
	}
};


USTRUCT(BlueprintType)
struct FRuneConfigInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	FString runeConfigName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 sky;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 ground;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 life;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 death;

	void set_RUNE_CONFIG_INFO(RUNECONFIGINFO info)
	{
		runeConfigName = info.RuneConfigName;
		sky = info.Sky;
		ground = info.Ground;
		life = info.Life;
		death = info.Death;
	}
};

USTRUCT(BlueprintType)
struct FRuneConfigInfoList
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<FRuneConfigInfo> values;

	void set_RUNE_CONFIG_INFO_LIST(RUNECONFIGINFOLIST list)
	{
		for (int32 i = 0; i < list.values.Num(); i++)
		{
			FRuneConfigInfo info;
			info.set_RUNE_CONFIG_INFO(list.values[i]);
			values.Add(info);
		}
	}
};

USTRUCT(BlueprintType)
struct FRuneConfigEffectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<FString> attributeList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		TArray<int32> effectList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 effectNb;
};

USTRUCT(BlueprintType)
struct FTinyMapInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString tinyMapName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<uint8> gameTypes;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	TArray<int32> gameScores;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 curGameProgress = 0;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 classificationLevel;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
	uint8 tinyMapLevel;
};

USTRUCT(BlueprintType)
struct FCardInfos
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		FString cardName;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		int32 cardNb;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar/KBEngine")
		uint8 cardType;
};

USTRUCT(BlueprintType)
struct FSelectSkillInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	FString chopSkillName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	FString dodgeSkillName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	FString blockSkillName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TArray<FString> normalSkillNames;

	void Reset()
	{
		chopSkillName = "";
		blockSkillName = "";
		dodgeSkillName = "";
		normalSkillNames.Empty();
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FPlayerSingleProgressInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString characterName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TArray<FCardInfos> cardInfoList;

	//记录玩家现在拥有什么技能
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CollisionWar")
	TArray<FString> availableExtraSkillList;

	//记录玩家拥有什么虫魂
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CollisionWar")
	TMap<FString, int32> availableFCList;

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	TMap<FString, int32> FCLevelInfoList;

	//记录玩家拥有什么道具合成
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "CollisionWar")
	TArray<FString> availableEquipList;

	//记录合成型虫魂的额外可用合成公式，Key表示合成公式名字，Value表示FC名字
	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TArray<FString> availableExtraCombineCards;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TMap<FString, int32> availableAppearanceList;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TMap<FString, int32> availableDiceBattleSkillMap;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TMap<FString, int32> availableTheorizeSkillMap;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	FSelectSkillInfo selectSkillInfo;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	TMap<FString, uint8> skillAttributeAssignment;

	/** 分别为IncreaseLife、IncreaseAtk、IncreaseDfc、Mentality
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CollisionWar")
	TMap<FString ,int32> attributeIncreaseMap;

	/** 分别为物理属性加点、FC解锁加点、皮肤解锁加点
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	TMap<uint8, int32> unlockPointMap;

	/** represent amount of all bonus type
	 * 0 - skill
	 * 1 - attribute
	 * 2 - physAttribute
	 * 3 - Money
	 * 4 - relics
	 */
	TMap<uint8, int32> bonusAmount;

	UPROPERTY()
	int32 money;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	FString curAppearanceName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar/KBEngine")
	uint8 difficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	int32 curProgress;

	UPROPERTY()
	FString progressName;

	UPROPERTY()
	int32 year;

	UPROPERTY()
	int32 month;

	UPROPERTY()
	int32 day;

	UPROPERTY()
	int32 hour;

	UPROPERTY()
	int32 minute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionWar")
	bool isInitial;

	void Reset()
	{
		characterName = "Lucian";
		cardInfoList.Empty();
		availableAppearanceList.Empty();
		availableEquipList.Empty();
		availableExtraCombineCards.Empty();
		availableExtraSkillList.Empty();
		selectSkillInfo.Reset();
		skillAttributeAssignment.Empty();
		availableFCList.Empty();
		FCLevelInfoList.Empty();
		curAppearanceName = "";
		for (TMap<FString, int32>::TConstIterator iter = attributeIncreaseMap.CreateConstIterator(); iter; ++iter)
		{
			attributeIncreaseMap[iter->Key] = 0;
		}
		for (TMap<uint8, int32>::TConstIterator iter = unlockPointMap.CreateConstIterator(); iter; ++iter)
		{
			unlockPointMap[iter->Key] = 0;
		}
		//attributeIncreaseMap.Empty();
		curProgress = 0;
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		isInitial = true;
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FEventFunction
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FString functionName;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		TArray<int32> values;

	FEventFunction()
	{
		functionName = "";
	}
};

USTRUCT(BlueprintType, Blueprintable)
struct FCursedCardInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		FEventFunction eventFunction;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString chDescription;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
	FString description;

	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		int32 steps;

	/** 标识要作用的角色种类
	* 0. 施加于敌人
	* 1. 施加于玩家
	* 2. 施加于圣灵
	*/
	UPROPERTY(EditAnywhere, Category = "CollisionWar")
		uint8 exertTargetType;

	UPROPERTY()
		int32 doneStep;
};
