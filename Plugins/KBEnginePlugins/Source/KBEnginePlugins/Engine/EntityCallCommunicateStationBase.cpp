#include "EntityCallCommunicateStationBase.h"
#include "Bundle.h"

void EntityBaseEntityCall_CommunicateStationBase::reqExitBattle()
{
	Bundle* pBundle = newCall("reqExitBattle");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_CommunicateStationBase::reqLevelInfos(const FString& arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqLevelInfos");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeString(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_CommunicateStationBase::reqRelogonInfo()
{
	Bundle* pBundle = newCall("reqRelogonInfo");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_CommunicateStationBase::reqTellLeaveWorld()
{
	Bundle* pBundle = newCall("reqTellLeaveWorld");
	if(!pBundle)
		return;

	sendCall(NULL);
}


void EntityCellEntityCall_CommunicateStationBase::reqCorrectInfo()
{
	Bundle* pBundle = newCall("reqCorrectInfo");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqLostRoundResult(const BYTE_LIST& arg1)
{
	Bundle* pBundle = newCall("reqLostRoundResult");
	if(!pBundle)
		return;

	((DATATYPE_BYTE_LIST*)EntityDef::id2datatypes[24])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqMakeUpFrames(int32 arg1, int32 arg2)
{
	Bundle* pBundle = newCall("reqMakeUpFrames");
	if(!pBundle)
		return;

	pBundle->writeInt32(arg1);
	pBundle->writeInt32(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqStartUploadCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10)
{
	Bundle* pBundle = newCall("reqStartUploadCorrectInfo");
	if(!pBundle)
		return;

	pBundle->writeInt32(arg1);
	pBundle->writeInt32(arg2);
	pBundle->writeInt32(arg3);
	pBundle->writeInt32(arg4);
	pBundle->writeInt32(arg5);
	pBundle->writeInt32(arg6);
	pBundle->writeInt32(arg7);
	pBundle->writeInt32(arg8);
	pBundle->writeString(arg9);
	pBundle->writeInt32(arg10);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqTellRoomIsReady()
{
	Bundle* pBundle = newCall("reqTellRoomIsReady");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqTellRoomResetDone()
{
	Bundle* pBundle = newCall("reqTellRoomResetDone");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqTellRoundEnd(const BATTLE_RESULT_ROUND& arg1)
{
	Bundle* pBundle = newCall("reqTellRoundEnd");
	if(!pBundle)
		return;

	((DATATYPE_BATTLE_RESULT_ROUND*)EntityDef::id2datatypes[224])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadAIOperationList(const AI_CHARACTER_OPERATION_LIST& arg1)
{
	Bundle* pBundle = newCall("reqUploadAIOperationList");
	if(!pBundle)
		return;

	((DATATYPE_AI_CHARACTER_OPERATION_LIST*)EntityDef::id2datatypes[173])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadActorCorrectInfo(const PHYSACTOR_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadActorCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_PHYSACTOR_INFO*)EntityDef::id2datatypes[144])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadCharacterCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_CHARACTER_CORRECT_INFO*)EntityDef::id2datatypes[106])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadEndCorrectInfo()
{
	Bundle* pBundle = newCall("reqUploadEndCorrectInfo");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadEnermyGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadEnermyGroupCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_ENERMY_GROUP_CORRECT_INFO*)EntityDef::id2datatypes[159])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadFrame(int32 arg1)
{
	Bundle* pBundle = newCall("reqUploadFrame");
	if(!pBundle)
		return;

	pBundle->writeInt32(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadLineCorrectInfo(const PHYSLINE_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadLineCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_PHYSLINE_INFO*)EntityDef::id2datatypes[111])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadOperation(const PLAYER_OPERATION_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadOperation");
	if(!pBundle)
		return;

	((DATATYPE_PLAYER_OPERATION_INFO*)EntityDef::id2datatypes[171])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadPointCorrectInfo(const PHYSPOINT_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadPointCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_PHYSPOINT_INFO*)EntityDef::id2datatypes[132])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadPolyCorrectInfo(const PHYSPOLY_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadPolyCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_PHYSPOLY_INFO*)EntityDef::id2datatypes[120])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_CommunicateStationBase::reqUploadReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1)
{
	Bundle* pBundle = newCall("reqUploadReactionPairCorrectInfo");
	if(!pBundle)
		return;

	((DATATYPE_REACTION_PAIR_INFO*)EntityDef::id2datatypes[157])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

