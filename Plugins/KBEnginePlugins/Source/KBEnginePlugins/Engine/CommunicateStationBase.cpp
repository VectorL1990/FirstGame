#include "CommunicateStationBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void CommunicateStationBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_CommunicateStationBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void CommunicateStationBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_CommunicateStationBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void CommunicateStationBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* CommunicateStationBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* CommunicateStationBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void CommunicateStationBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
	switch(pMethod->methodUtype)
	{
		case 123:
		{
			PHYSACTOR_INFO dispatchActorCorrectInfo_arg1;
			((DATATYPE_PHYSACTOR_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchActorCorrectInfo_arg1);
			dispatchActorCorrectInfo(dispatchActorCorrectInfo_arg1);
			break;
		}
		case 130:
		{
			BYTE_LIST dispatchBattleEnd_arg1;
			((DATATYPE_BYTE_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchBattleEnd_arg1);
			BATTLE_RESULT dispatchBattleEnd_arg2;
			((DATATYPE_BATTLE_RESULT*)pMethod->args[1])->createFromStreamEx(stream, dispatchBattleEnd_arg2);
			dispatchBattleEnd(dispatchBattleEnd_arg1, dispatchBattleEnd_arg2);
			break;
		}
		case 133:
		{
			int32 dispatchBattleStart_arg1 = stream.readInt32();
			dispatchBattleStart(dispatchBattleStart_arg1);
			break;
		}
		case 134:
		{
			int32 dispatchCalPrizeResult_arg1 = stream.readInt32();
			int32 dispatchCalPrizeResult_arg2 = stream.readInt32();
			int32 dispatchCalPrizeResult_arg3 = stream.readInt32();
			int32 dispatchCalPrizeResult_arg4 = stream.readInt32();
			int32 dispatchCalPrizeResult_arg5 = stream.readInt32();
			STRING_LIST dispatchCalPrizeResult_arg6;
			((DATATYPE_STRING_LIST*)pMethod->args[5])->createFromStreamEx(stream, dispatchCalPrizeResult_arg6);
			dispatchCalPrizeResult(dispatchCalPrizeResult_arg1, dispatchCalPrizeResult_arg2, dispatchCalPrizeResult_arg3, dispatchCalPrizeResult_arg4, dispatchCalPrizeResult_arg5, dispatchCalPrizeResult_arg6);
			break;
		}
		case 119:
		{
			CHARACTER_CORRECT_INFO dispatchCharacterCorrectInfo_arg1;
			((DATATYPE_CHARACTER_CORRECT_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchCharacterCorrectInfo_arg1);
			dispatchCharacterCorrectInfo(dispatchCharacterCorrectInfo_arg1);
			break;
		}
		case 127:
		{
			dispatchEndCorrectInfo();
			break;
		}
		case 126:
		{
			int32 dispatchGeneralCorrectInfo_arg1 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg2 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg3 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg4 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg5 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg6 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg7 = stream.readInt32();
			int32 dispatchGeneralCorrectInfo_arg8 = stream.readInt32();
			FString dispatchGeneralCorrectInfo_arg9 = stream.readString();
			int32 dispatchGeneralCorrectInfo_arg10 = stream.readInt32();
			dispatchGeneralCorrectInfo(dispatchGeneralCorrectInfo_arg1, dispatchGeneralCorrectInfo_arg2, dispatchGeneralCorrectInfo_arg3, dispatchGeneralCorrectInfo_arg4, dispatchGeneralCorrectInfo_arg5, dispatchGeneralCorrectInfo_arg6, dispatchGeneralCorrectInfo_arg7, dispatchGeneralCorrectInfo_arg8, dispatchGeneralCorrectInfo_arg9, dispatchGeneralCorrectInfo_arg10);
			break;
		}
		case 125:
		{
			ENERMY_GROUP_CORRECT_INFO dispatchGroupCorrectInfo_arg1;
			((DATATYPE_ENERMY_GROUP_CORRECT_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchGroupCorrectInfo_arg1);
			dispatchGroupCorrectInfo(dispatchGroupCorrectInfo_arg1);
			break;
		}
		case 115:
		{
			PLAYER_SPAWN_POINT_LIST dispatchLevelInfo_arg1;
			((DATATYPE_PLAYER_SPAWN_POINT_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchLevelInfo_arg1);
			ENERMY_SPAWN_GROUP_LIST dispatchLevelInfo_arg2;
			((DATATYPE_ENERMY_SPAWN_GROUP_LIST*)pMethod->args[1])->createFromStreamEx(stream, dispatchLevelInfo_arg2);
			PHYSACTOR_SPAWN_LIST dispatchLevelInfo_arg3;
			((DATATYPE_PHYSACTOR_SPAWN_LIST*)pMethod->args[2])->createFromStreamEx(stream, dispatchLevelInfo_arg3);
			FString dispatchLevelInfo_arg4 = stream.readString();
			SPECIAL_FRAME_LIST dispatchLevelInfo_arg5;
			((DATATYPE_SPECIAL_FRAME_LIST*)pMethod->args[4])->createFromStreamEx(stream, dispatchLevelInfo_arg5);
			dispatchLevelInfo(dispatchLevelInfo_arg1, dispatchLevelInfo_arg2, dispatchLevelInfo_arg3, dispatchLevelInfo_arg4, dispatchLevelInfo_arg5);
			break;
		}
		case 121:
		{
			PHYSLINE_INFO dispatchLineCorrectInfo_arg1;
			((DATATYPE_PHYSLINE_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchLineCorrectInfo_arg1);
			dispatchLineCorrectInfo(dispatchLineCorrectInfo_arg1);
			break;
		}
		case 117:
		{
			LOGIC_FRAME dispatchLogicFrame_arg1;
			((DATATYPE_LOGIC_FRAME*)pMethod->args[0])->createFromStreamEx(stream, dispatchLogicFrame_arg1);
			dispatchLogicFrame(dispatchLogicFrame_arg1);
			break;
		}
		case 135:
		{
			BATTLE_RESULT_ROUND_LIST dispatchLostRoundInfo_arg1;
			((DATATYPE_BATTLE_RESULT_ROUND_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchLostRoundInfo_arg1);
			dispatchLostRoundInfo(dispatchLostRoundInfo_arg1);
			break;
		}
		case 116:
		{
			uint8 dispatchMainMachine_arg1 = stream.readUint8();
			dispatchMainMachine(dispatchMainMachine_arg1);
			break;
		}
		case 118:
		{
			LOGIC_FRAME_LIST dispatchMakeUpFrames_arg1;
			((DATATYPE_LOGIC_FRAME_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchMakeUpFrames_arg1);
			dispatchMakeUpFrames(dispatchMakeUpFrames_arg1);
			break;
		}
		case 129:
		{
			int8 dispatchNextRound_arg1 = stream.readInt8();
			BYTE_LIST dispatchNextRound_arg2;
			((DATATYPE_BYTE_LIST*)pMethod->args[1])->createFromStreamEx(stream, dispatchNextRound_arg2);
			dispatchNextRound(dispatchNextRound_arg1, dispatchNextRound_arg2);
			break;
		}
		case 122:
		{
			PHYSPOINT_INFO dispatchPointCorrectInfo_arg1;
			((DATATYPE_PHYSPOINT_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchPointCorrectInfo_arg1);
			dispatchPointCorrectInfo(dispatchPointCorrectInfo_arg1);
			break;
		}
		case 120:
		{
			PHYSPOLY_INFO dispatchPolyCorrectInfo_arg1;
			((DATATYPE_PHYSPOLY_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchPolyCorrectInfo_arg1);
			dispatchPolyCorrectInfo(dispatchPolyCorrectInfo_arg1);
			break;
		}
		case 124:
		{
			REACTION_PAIR_INFO dispatchReactionPairCorrectInfo_arg1;
			((DATATYPE_REACTION_PAIR_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchReactionPairCorrectInfo_arg1);
			dispatchReactionPairCorrectInfo(dispatchReactionPairCorrectInfo_arg1);
			break;
		}
		case 114:
		{
			uint8 dispatchReadLevelResult_arg1 = stream.readUint8();
			dispatchReadLevelResult(dispatchReadLevelResult_arg1);
			break;
		}
		case 131:
		{
			FString dispatchRelogonInfo_arg1 = stream.readString();
			int32 dispatchRelogonInfo_arg2 = stream.readInt32();
			PLAYER_ROLETYPE_ASSIGNNUM_LIST dispatchRelogonInfo_arg3;
			((DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST*)pMethod->args[2])->createFromStreamEx(stream, dispatchRelogonInfo_arg3);
			BATTLE_RESULT dispatchRelogonInfo_arg4;
			((DATATYPE_BATTLE_RESULT*)pMethod->args[3])->createFromStreamEx(stream, dispatchRelogonInfo_arg4);
			int8 dispatchRelogonInfo_arg5 = stream.readInt8();
			FString dispatchRelogonInfo_arg6 = stream.readString();
			dispatchRelogonInfo(dispatchRelogonInfo_arg1, dispatchRelogonInfo_arg2, dispatchRelogonInfo_arg3, dispatchRelogonInfo_arg4, dispatchRelogonInfo_arg5, dispatchRelogonInfo_arg6);
			break;
		}
		case 132:
		{
			PLAYER_INFO dispatchRelogonPlayerInfo_arg1;
			((DATATYPE_PLAYER_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchRelogonPlayerInfo_arg1);
			GOODS_LIST dispatchRelogonPlayerInfo_arg2;
			((DATATYPE_GOODS_LIST*)pMethod->args[1])->createFromStreamEx(stream, dispatchRelogonPlayerInfo_arg2);
			dispatchRelogonPlayerInfo(dispatchRelogonPlayerInfo_arg1, dispatchRelogonPlayerInfo_arg2);
			break;
		}
		case 128:
		{
			dispatchStopUploadCorrectInfo();
			break;
		}
		default:
			break;
	};
}

void CommunicateStationBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void CommunicateStationBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

CommunicateStationBase::CommunicateStationBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

CommunicateStationBase::~CommunicateStationBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

