// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BaseStruct.generated.h"

/**
	This file contains all basic structs
*/





USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	int32 exp;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
	FString characterName = "Lucian";
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
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


		UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FString playerName;
	UPROPERTY(BlueprintReadWrite, Category = "CollisionWar")
		FString headShotName;
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
	TArray<FCharacterInfo> characterList;
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
