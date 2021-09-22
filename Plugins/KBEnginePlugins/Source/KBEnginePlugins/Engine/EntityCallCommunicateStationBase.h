/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"

// defined in */scripts/entity_defs/CommunicateStation.def

class KBENGINEPLUGINS_API EntityBaseEntityCall_CommunicateStationBase : public EntityCall
{
public:
	EntityBaseEntityCall_CommunicateStationBase() : EntityCall()
	{
		type = ENTITYCALL_TYPE_BASE;
	}

	void reqExitBattle();
	void reqLevelInfos(const FString& arg1, const FString& arg2);
	void reqRelogonInfo();
	void reqTellLeaveWorld();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_CommunicateStationBase : public EntityCall
{
public:
	EntityCellEntityCall_CommunicateStationBase() : EntityCall()
	{
		type = ENTITYCALL_TYPE_CELL;
	}

	void reqCorrectInfo();
	void reqLostRoundResult(const BYTE_LIST& arg1);
	void reqMakeUpFrames(int32 arg1, int32 arg2);
	void reqStartUploadCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10);
	void reqTellRoomIsReady();
	void reqTellRoomResetDone();
	void reqTellRoundEnd(const BATTLE_RESULT_ROUND& arg1);
	void reqUploadAIOperationList(const AI_CHARACTER_OPERATION_LIST& arg1);
	void reqUploadActorCorrectInfo(const PHYSACTOR_INFO& arg1);
	void reqUploadCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1);
	void reqUploadEndCorrectInfo();
	void reqUploadEnermyGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1);
	void reqUploadFrame(int32 arg1);
	void reqUploadLineCorrectInfo(const PHYSLINE_INFO& arg1);
	void reqUploadOperation(const PLAYER_OPERATION_INFO& arg1);
	void reqUploadPointCorrectInfo(const PHYSPOINT_INFO& arg1);
	void reqUploadPolyCorrectInfo(const PHYSPOLY_INFO& arg1);
	void reqUploadReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1);
};