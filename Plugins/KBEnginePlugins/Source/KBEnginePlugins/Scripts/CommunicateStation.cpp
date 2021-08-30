#include "CommunicateStation.h"
#include "Engine/Entity.h"
#include "Engine/KBEngine.h"
#include "Engine/KBDebug.h"
//#include "Engine/KBETypes.h"
#include "LogicEvents.h"


CommunicateStation::CommunicateStation():
	CommunicateStationBase()
{
}

CommunicateStation::~CommunicateStation()
{
}

void CommunicateStation::__init__()
{
	// 注册事件
	if (isPlayer())
	{
		
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqLevelInfos", "ReqLevelInfos", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqLevelInfos& data = static_cast<const UKBEventData_reqLevelInfos&>(*pEventData);
			ReqLevelInfos(data.levelName, data.roomType);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadFrame", "ReqUploadFrame", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadFrame& data = static_cast<const UKBEventData_reqUploadFrame&>(*pEventData);
			ReqUploadFrame(data.lastFrameNb);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqTellRoomIsReady", "ReqTellRoomIsReady", [this](const UKBEventData* pEventData)
		{
			reqTellRoomIsReady();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadOperation", "ReqUploadOperation", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadOperation& data = static_cast<const UKBEventData_reqUploadOperation&>(*pEventData);
			FPlayerOperationInfo info = data.playerOperationInfo;
			PLAYER_OPERATION_INFO operationInfo = info.assign_PLAYER_OPERATION_INFO();
			ReqUploadOperation(operationInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadAIOperationList", "ReqUploadAIOperationList", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadAIOperationList& data = static_cast<const UKBEventData_reqUploadAIOperationList&>(*pEventData);
			FAICharacterOperationList oldList = data.AICharacterOperationList;
			AI_CHARACTER_OPERATION_LIST AIList = oldList.assign_AI_CHARACTER_OPERATION_LIST();
			reqUploadAIOperationList(AIList);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqMakeUpFrames", "ReqMakeUpFrames", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqMakeUpFrames& data = static_cast<const UKBEventData_reqMakeUpFrames&>(*pEventData);
			reqMakeUpFrames(data.startFrameNb, data.endFrameNb);
		});

		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqStartUploadCorrectInfo", "ReqStartUploadCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqStartUploadCorrectInfo& data = static_cast<const UKBEventData_reqStartUploadCorrectInfo&>(*pEventData);
			ReqStartUploadCorrectInfo(data.frameNb, data.totalCharacterNb, data.totalPolyNb, data.totalLineNb, data.totalPointNb,
				data.totalActorNb, data.totalPairNb, data.totalGroupNb, data.gameProgress, data.randSeed);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadCharacterCorrectInfo", "ReqUploadCharacterCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadCharacterCorrectInfo& data = static_cast<const UKBEventData_reqUploadCharacterCorrectInfo&>(*pEventData);
			FCharacterCorrectInfo info = data.info;
			CHARACTER_CORRECT_INFO convertInfo = info.assign_CHARACTER_CORRECT_INFO();
			ReqUploadCharacterCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadPolyCorrectInfo", "ReqUploadPolyCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadPolyCorrectInfo& data = static_cast<const UKBEventData_reqUploadPolyCorrectInfo&>(*pEventData);
			FPhysPolyInfo info = data.info;
			PHYSPOLY_INFO convertInfo = info.assign_PHYS_POLY_INFO();
			ReqUploadPolyCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadLineCorrectInfo", "ReqUploadLineCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadLineCorrectInfo& data = static_cast<const UKBEventData_reqUploadLineCorrectInfo&>(*pEventData);
			FPhysLineInfo info = data.info;
			PHYSLINE_INFO convertInfo = info.assign_PHYS_LINE_INFO();
			ReqUploadLineCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadPointCorrectInfo", "ReqUploadPointCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadPointCorrectInfo& data = static_cast<const UKBEventData_reqUploadPointCorrectInfo&>(*pEventData);
			FPhysPointInfo info = data.info;
			PHYSPOINT_INFO convertInfo = info.assign_PHYS_POINT_INFO();
			ReqUploadPointCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadActorCorrectInfo", "ReqUploadActorCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadActorCorrectInfo& data = static_cast<const UKBEventData_reqUploadActorCorrectInfo&>(*pEventData);
			FPhysActorInfo info = data.info;
			PHYSACTOR_INFO convertInfo = info.assign_PHYS_ACTOR_INFO();
			ReqUploadActorCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadReactionPairCorrectInfo", "ReqUploadReactionPairCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadReactionPairCorrectInfo& data = static_cast<const UKBEventData_reqUploadReactionPairCorrectInfo&>(*pEventData);
			FReactionPairInfo info = data.info;
			REACTION_PAIR_INFO convertInfo = info.assign_REACTION_PAIR_INFO();
			ReqUploadReactionPairCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadEnermyGroupCorrectInfo", "ReqUploadEnermyGroupCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadEnermyGroupCorrectInfo& data = static_cast<const UKBEventData_reqUploadEnermyGroupCorrectInfo&>(*pEventData);
			FEnermyGroupCorrectInfo info = data.info;
			ENERMY_GROUP_CORRECT_INFO convertInfo = info.assign_ENERMY_GROUP_CORRECT_INFO();
			ReqUploadEnermyGroupCorrectInfo(convertInfo);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqUploadEndCorrectInfo", "ReqUploadEndCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqUploadEndCorrectInfo& data = static_cast<const UKBEventData_reqUploadEndCorrectInfo&>(*pEventData);
			ReqUploadEndCorrectInfo();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCorrectInfo", "ReqCorrectInfo", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqCorrectInfo& data = static_cast<const UKBEventData_reqCorrectInfo&>(*pEventData);
			ReqCorrectInfo();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRelogonInfo", "ReqRelogonInfo", [this](const UKBEventData* pEventData)
		{
			ReqRelogonInfo();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqTellRoundEnd", "ReqTellRoundEnd", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqTellRoundEnd& data = static_cast<const UKBEventData_reqTellRoundEnd&>(*pEventData);
			FBattleResultRound info = data.battleResultRound;
			BATTLE_RESULT_ROUND result = info.assign_BATTLE_RESULT_ROUND();
			ReqTellRoundEnd(result);
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqExitBattle", "ReqExitBattle", [this](const UKBEventData* pEventData)
		{
			ReqExitBattle();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqTellRoomResetDone", "ReqTellRoomResetDone", [this](const UKBEventData* pEventData)
		{
			ReqTellRoomResetDone();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqTellLeaveWorld", "ReqTellLeaveWorld", [this](const UKBEventData* pEventData)
		{
			ReqTellLeaveWorld();
		});
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqLostRoundResult", "ReqLostRoundResult", [this](const UKBEventData* pEventData)
		{
			const UKBEventData_reqLostRoundResult& data = static_cast<const UKBEventData_reqLostRoundResult&>(*pEventData);
			BYTE_LIST transferLostRoundList;
			for (int32 i=0; i<data.lostRoundNbList.Num(); i++)
			{
				transferLostRoundList.values.Add(data.lostRoundNbList[i]);
			}
			ReqLostRoundResult(transferLostRoundList);
		});
	}
}

void CommunicateStation::onDestroy()
{
	// 注销注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void CommunicateStation::dispatchLevelInfo(const PLAYER_SPAWN_POINT_LIST& arg1, const ENERMY_SPAWN_GROUP_LIST& arg2, const PHYSACTOR_SPAWN_LIST& arg3, const FString& arg4, const SPECIAL_FRAME_LIST& arg5)
{
	UKBEventData_dispatchLevelInfo* pEventData = NewObject<UKBEventData_dispatchLevelInfo>();
	pEventData->playerSpawnPointList.set_PLAYER_SPAWN_POINT_LIST(arg1);
	pEventData->enermySpawnGroupList.set_ENERMY_SPAWN_GROUP_LIST(arg2);
	pEventData->physActorSpawnList.set_PHYSACTOR_SPAWN_LIST(arg3);
	pEventData->levelName = arg4;
	pEventData->specialFrameList.set_SPECIAL_FRAME_LIST(arg5);
	KBENGINE_EVENT_FIRE("dispatchLevelInfo", pEventData);
}

void CommunicateStation::dispatchMainMachine(uint8 arg1)
{
	UKBEventData_dispatchMainMachine* pEventData = NewObject<UKBEventData_dispatchMainMachine>();
	if (arg1 == 0) pEventData->assignResult = false;
	else pEventData->assignResult = true;
	KBENGINE_EVENT_FIRE("dispatchMainMachine", pEventData);
}

void CommunicateStation::dispatchLogicFrame(const LOGIC_FRAME& arg1)
{
	UKBEventData_dispatchLogicFrame* pEventData = NewObject<UKBEventData_dispatchLogicFrame>();
	pEventData->logicFrame.set_LOGIC_FRAME(arg1);
	KBENGINE_EVENT_FIRE("dispatchLogicFrame", pEventData);
}

void CommunicateStation::dispatchMakeUpFrames(const LOGIC_FRAME_LIST& arg1)
{
	UKBEventData_dispatchMakeUpFrames* pEventData = NewObject<UKBEventData_dispatchMakeUpFrames>();
	pEventData->logicFrames.set_LOGIC_FRAME_LIST(arg1);
	KBENGINE_EVENT_FIRE("dispatchMakeUpFrames", pEventData);
}

void CommunicateStation::dispatchReadLevelResult(uint8 arg1)
{
	UKBEventData_dispatchReadLevelResult* pEventData = NewObject<UKBEventData_dispatchReadLevelResult>();
	if (arg1 == 0) pEventData->readSuccessOrNot = false;
	else pEventData->readSuccessOrNot = true;
	KBENGINE_EVENT_FIRE("dispatchReadLevelResult", pEventData);
}

void CommunicateStation::dispatchGeneralCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10)
{
	UKBEventData_dispatchGeneralCorrectInfo* pEventData = NewObject<UKBEventData_dispatchGeneralCorrectInfo>();
	pEventData->frameNb = arg1;
	pEventData->totalCharacterNb = arg2;
	pEventData->totalPolyNb = arg3;
	pEventData->totalLineNb = arg4;
	pEventData->totalPointNb = arg5;
	pEventData->totalActorNb = arg6;
	pEventData->totalReactionPairNb = arg7;
	pEventData->totalEnermyGroupNb = arg8;
	pEventData->gameProgress = arg9;
	pEventData->curRandSeed = arg10;
	KBENGINE_EVENT_FIRE("dispatchGeneralCorrectInfo", pEventData);
}

void CommunicateStation::dispatchCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1)
{
	UKBEventData_dispatchCharacterCorrectInfo* pEventData = NewObject<UKBEventData_dispatchCharacterCorrectInfo>();
	pEventData->characterCorrectInfo.set_CHARACTER_CORRECT_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchCharacterCorrectInfo", pEventData);
}

void CommunicateStation::dispatchPolyCorrectInfo(const PHYSPOLY_INFO& arg1)
{
	UKBEventData_dispatchPolyCorrectInfo* pEventData = NewObject<UKBEventData_dispatchPolyCorrectInfo>();
	pEventData->polyCorrectInfo.set_PHYS_POLY_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchPolyCorrectInfo", pEventData);
}

void CommunicateStation::dispatchLineCorrectInfo(const PHYSLINE_INFO& arg1)
{
	UKBEventData_dispatchLineCorrectInfo* pEventData = NewObject<UKBEventData_dispatchLineCorrectInfo>();
	pEventData->lineCorrectInfo.set_PHYS_LINE_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchLineCorrectInfo", pEventData);
}

void CommunicateStation::dispatchPointCorrectInfo(const PHYSPOINT_INFO& arg1)
{
	UKBEventData_dispatchPointCorrectInfo* pEventData = NewObject<UKBEventData_dispatchPointCorrectInfo>();
	pEventData->pointCorrectInfo.set_PHYS_POINT_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchPointCorrectInfo", pEventData);
}

void CommunicateStation::dispatchActorCorrectInfo(const PHYSACTOR_INFO& arg1)
{
	UKBEventData_dispatchActorCorrectInfo* pEventData = NewObject<UKBEventData_dispatchActorCorrectInfo>();
	pEventData->actorCorrectInfo.set_PHYS_ACTOR_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchActorCorrectInfo", pEventData);
}

void CommunicateStation::dispatchReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1)
{
	UKBEventData_dispatchReactionPairCorrectInfo* pEventData = NewObject<UKBEventData_dispatchReactionPairCorrectInfo>();
	pEventData->reactionPairCorrectInfo.set_REACTION_PAIR_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchReactionPairCorrectInfo", pEventData);
}

void CommunicateStation::dispatchGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1)
{
	UKBEventData_dispatchGroupCorrectInfo* pEventData = NewObject<UKBEventData_dispatchGroupCorrectInfo>();
	pEventData->enermyGroupCorrectInfo.set_ENERMY_GROUP_CORRECT_INFO(arg1);
	KBENGINE_EVENT_FIRE("dispatchGroupCorrectInfo", pEventData);
}

void CommunicateStation::dispatchEndCorrectInfo()
{
	UKBEventData_dispatchEndCorrectInfo* pEventData = NewObject<UKBEventData_dispatchEndCorrectInfo>();
	KBENGINE_EVENT_FIRE("dispatchEndCorrectInfo", pEventData);
}

void CommunicateStation::dispatchStopUploadCorrectInfo()
{
	UKBEventData_dispatchStopUploadCorrectInfo* pEventData = NewObject<UKBEventData_dispatchStopUploadCorrectInfo>();
	KBENGINE_EVENT_FIRE("dispatchStopUploadCorrectInfo", pEventData);
}

void CommunicateStation::dispatchNextRound(int8 arg1, const BYTE_LIST& arg2)
{
	UKBEventData_dispatchNextRound* pEventData = NewObject<UKBEventData_dispatchNextRound>();
	pEventData->roundNb = arg1;
	for (int32 i=0; i<arg2.values.Num(); i++)
	{
		pEventData->winTeamList.Add(arg2.values[i]);
	}
	KBENGINE_EVENT_FIRE("dispatchNextRound", pEventData);
}

void CommunicateStation::dispatchBattleEnd(const BYTE_LIST& arg1, const BATTLE_RESULT& arg2)
{
	UKBEventData_dispatchBattleEnd* pEventData = NewObject<UKBEventData_dispatchBattleEnd>();
	for (int32 i=0; i<arg1.values.Num(); i++)
	{
		pEventData->winTeamList.Add(arg1.values[i]);
	}
	pEventData->battleResult.set_BATTLE_RESULT(arg2);
	KBENGINE_EVENT_FIRE("dispatchBattleEnd", pEventData);
}

void CommunicateStation::dispatchRelogonInfo(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int8 arg5, const FString& arg6)
{
	UKBEventData_dispatchRelogonInfo* pEventData = NewObject<UKBEventData_dispatchRelogonInfo>();
	pEventData->levelName = arg1;
	pEventData->playerID = arg2;
	pEventData->list.set_PLAYER_ROLETYPE_ASSIGNNUM_LIST(arg3);
	pEventData->result.set_BATTLE_RESULT(arg4);
	pEventData->assignNbInBattle = arg5;
	pEventData->battleType = arg6;
	KBENGINE_EVENT_FIRE("dispatchRelogonInfo", pEventData);
}

void CommunicateStation::dispatchRelogonPlayerInfo(const PLAYER_INFO& arg1, const GOODS_LIST& arg2)
{
	UKBEventData_dispatchRelogonPlayerInfo* pEventData = NewObject<UKBEventData_dispatchRelogonPlayerInfo>();
	pEventData->info.set_PLAYER_INFO(arg1);
	pEventData->list.set_GOODS_LIST(arg2);
	KBENGINE_EVENT_FIRE("dispatchRelogonPlayerInfo", pEventData);
}

void CommunicateStation::dispatchBattleStart(int32 arg1)
{
	UKBEventData_dispatchBattleStart* pEventData = NewObject<UKBEventData_dispatchBattleStart>();
	pEventData->randSeed = arg1;
	KBENGINE_EVENT_FIRE("dispatchBattleStart", pEventData);
}

void CommunicateStation::dispatchCalPrizeResult(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, const STRING_LIST& arg6)
{
	UKBEventData_dispatchCalPrizeResult* pEventData = NewObject<UKBEventData_dispatchCalPrizeResult>();
	pEventData->exp = arg1;
	pEventData->constK = arg2;
	pEventData->constN = arg3;
	pEventData->constC = arg4;
	pEventData->curLevel = arg5;
	pEventData->prizeNameList = arg6.values;
	KBENGINE_EVENT_FIRE("dispatchCalPrizeResult", pEventData);
}

void CommunicateStation::dispatchLostRoundInfo(const BATTLE_RESULT_ROUND_LIST& arg1)
{
	UKBEventData_dispatchLostRoundInfo* pEventData = NewObject<UKBEventData_dispatchLostRoundInfo>();
	pEventData->list.set_REQ_TEAM_MATCH_DATA(arg1);
	KBENGINE_EVENT_FIRE("dispatchLostRoundInfo", pEventData);
}

void CommunicateStation::reqTellRoomIsReady()
{
	pCellEntityCall->reqTellRoomIsReady();
}

void CommunicateStation::ReqLevelInfos(const FString& arg1, const FString& arg2)
{
	pBaseEntityCall->reqLevelInfos(arg1, arg2);
}

void CommunicateStation::ReqUploadFrame(int32 arg1)
{
	pCellEntityCall->reqUploadFrame(arg1);
}

void CommunicateStation::ReqUploadOperation(const PLAYER_OPERATION_INFO& arg1)
{
	pCellEntityCall->reqUploadOperation(arg1);
}

void CommunicateStation::reqUploadAIOperationList(const AI_CHARACTER_OPERATION_LIST& arg1)
{
	pCellEntityCall->reqUploadAIOperationList(arg1);
}

void CommunicateStation::reqMakeUpFrames(int32 arg1, int32 arg2)
{
	pCellEntityCall->reqMakeUpFrames(arg1, arg2);
}

void CommunicateStation::ReqStartUploadCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10)
{
	pCellEntityCall->reqStartUploadCorrectInfo(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

void CommunicateStation::ReqUploadActorCorrectInfo(const PHYSACTOR_INFO& arg1)
{
	pCellEntityCall->reqUploadActorCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1)
{
	pCellEntityCall->reqUploadCharacterCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadEndCorrectInfo()
{
	pCellEntityCall->reqUploadEndCorrectInfo();
}

void CommunicateStation::ReqUploadEnermyGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1)
{
	pCellEntityCall->reqUploadEnermyGroupCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadLineCorrectInfo(const PHYSLINE_INFO& arg1)
{
	pCellEntityCall->reqUploadLineCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadPointCorrectInfo(const PHYSPOINT_INFO& arg1)
{
	pCellEntityCall->reqUploadPointCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadPolyCorrectInfo(const PHYSPOLY_INFO& arg1)
{
	pCellEntityCall->reqUploadPolyCorrectInfo(arg1);
}

void CommunicateStation::ReqUploadReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1)
{
	pCellEntityCall->reqUploadReactionPairCorrectInfo(arg1);
}

void CommunicateStation::ReqCorrectInfo()
{
	pCellEntityCall->reqCorrectInfo();
}

void CommunicateStation::ReqTellRoundEnd(const BATTLE_RESULT_ROUND& arg1)
{
	pCellEntityCall->reqTellRoundEnd(arg1);
}

void CommunicateStation::ReqExitBattle()
{
	pBaseEntityCall->reqExitBattle();
}

void CommunicateStation::ReqTellRoomResetDone()
{
	pCellEntityCall->reqTellRoomResetDone();
}

void CommunicateStation::ReqTellLeaveWorld()
{
	pBaseEntityCall->reqTellLeaveWorld();
}

void CommunicateStation::ReqRelogonInfo()
{
	pBaseEntityCall->reqRelogonInfo();
}

void CommunicateStation::ReqLostRoundResult(const BYTE_LIST& arg1)
{
	pCellEntityCall->reqLostRoundResult(arg1);
}

