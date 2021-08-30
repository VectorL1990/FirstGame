#include "AccountBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void AccountBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_AccountBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void AccountBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_AccountBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void AccountBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* AccountBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* AccountBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void AccountBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
	switch(pMethod->methodUtype)
	{
		case 64:
		{
			FString dispatchAddFriendRequest_arg1 = stream.readString();
			uint64 dispatchAddFriendRequest_arg2 = stream.readUint64();
			dispatchAddFriendRequest(dispatchAddFriendRequest_arg1, dispatchAddFriendRequest_arg2);
			break;
		}
		case 65:
		{
			uint8 dispatchAddFriendRequestResult_arg1 = stream.readUint8();
			dispatchAddFriendRequestResult(dispatchAddFriendRequestResult_arg1);
			break;
		}
		case 59:
		{
			FString dispatchAllPlayerRoletypeAndAssignNb_arg1 = stream.readString();
			int32 dispatchAllPlayerRoletypeAndAssignNb_arg2 = stream.readInt32();
			PLAYER_ROLETYPE_ASSIGNNUM_LIST dispatchAllPlayerRoletypeAndAssignNb_arg3;
			((DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST*)pMethod->args[2])->createFromStreamEx(stream, dispatchAllPlayerRoletypeAndAssignNb_arg3);
			BATTLE_RESULT dispatchAllPlayerRoletypeAndAssignNb_arg4;
			((DATATYPE_BATTLE_RESULT*)pMethod->args[3])->createFromStreamEx(stream, dispatchAllPlayerRoletypeAndAssignNb_arg4);
			int32 dispatchAllPlayerRoletypeAndAssignNb_arg5 = stream.readInt32();
			dispatchAllPlayerRoletypeAndAssignNb(dispatchAllPlayerRoletypeAndAssignNb_arg1, dispatchAllPlayerRoletypeAndAssignNb_arg2, dispatchAllPlayerRoletypeAndAssignNb_arg3, dispatchAllPlayerRoletypeAndAssignNb_arg4, dispatchAllPlayerRoletypeAndAssignNb_arg5);
			break;
		}
		case 46:
		{
			RUNEINFOLIST dispatchAllRuneDataToClient_arg1;
			((DATATYPE_RUNEINFOLIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchAllRuneDataToClient_arg1);
			RUNECONFIGINFOLIST dispatchAllRuneDataToClient_arg2;
			((DATATYPE_RUNECONFIGINFOLIST*)pMethod->args[1])->createFromStreamEx(stream, dispatchAllRuneDataToClient_arg2);
			dispatchAllRuneDataToClient(dispatchAllRuneDataToClient_arg1, dispatchAllRuneDataToClient_arg2);
			break;
		}
		case 66:
		{
			FString dispatchApproveAddFriendAnswer_arg1 = stream.readString();
			PLAYER_TAG_INFO dispatchApproveAddFriendAnswer_arg2;
			((DATATYPE_PLAYER_TAG_INFO*)pMethod->args[1])->createFromStreamEx(stream, dispatchApproveAddFriendAnswer_arg2);
			dispatchApproveAddFriendAnswer(dispatchApproveAddFriendAnswer_arg1, dispatchApproveAddFriendAnswer_arg2);
			break;
		}
		case 53:
		{
			uint8 dispatchBuyResult_arg1 = stream.readUint8();
			int32 dispatchBuyResult_arg2 = stream.readInt32();
			uint8 dispatchBuyResult_arg3 = stream.readUint8();
			FString dispatchBuyResult_arg4 = stream.readString();
			dispatchBuyResult(dispatchBuyResult_arg1, dispatchBuyResult_arg2, dispatchBuyResult_arg3, dispatchBuyResult_arg4);
			break;
		}
		case 70:
		{
			dispatchCancelMatch();
			break;
		}
		case 68:
		{
			uint8 dispatchDeleteFriendRequestResult_arg1 = stream.readUint8();
			FString dispatchDeleteFriendRequestResult_arg2 = stream.readString();
			dispatchDeleteFriendRequestResult(dispatchDeleteFriendRequestResult_arg1, dispatchDeleteFriendRequestResult_arg2);
			break;
		}
		case 67:
		{
			FString dispatchDisapproveAddFriendAnswer_arg1 = stream.readString();
			dispatchDisapproveAddFriendAnswer(dispatchDisapproveAddFriendAnswer_arg1);
			break;
		}
		case 47:
		{
			BYTE_LIST dispatchHasConfigInfosToClient_arg1;
			((DATATYPE_BYTE_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchHasConfigInfosToClient_arg1);
			dispatchHasConfigInfosToClient(dispatchHasConfigInfosToClient_arg1);
			break;
		}
		case 50:
		{
			LEVEL_MODEL_LIST dispatchLevelModelList_arg1;
			((DATATYPE_LEVEL_MODEL_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchLevelModelList_arg1);
			dispatchLevelModelList(dispatchLevelModelList_arg1);
			break;
		}
		case 60:
		{
			FString dispatchLogonStatus_arg1 = stream.readString();
			FString dispatchLogonStatus_arg2 = stream.readString();
			dispatchLogonStatus(dispatchLogonStatus_arg1, dispatchLogonStatus_arg2);
			break;
		}
		case 52:
		{
			GOODS_LIST dispatchMallInfoList_arg1;
			((DATATYPE_GOODS_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchMallInfoList_arg1);
			dispatchMallInfoList(dispatchMallInfoList_arg1);
			break;
		}
		case 58:
		{
			FString dispatchMatchResult_arg1 = stream.readString();
			uint8 dispatchMatchResult_arg2 = stream.readUint8();
			FString dispatchMatchResult_arg3 = stream.readString();
			PLAYER_TAG_INFO_LIST dispatchMatchResult_arg4;
			((DATATYPE_PLAYER_TAG_INFO_LIST*)pMethod->args[3])->createFromStreamEx(stream, dispatchMatchResult_arg4);
			dispatchMatchResult(dispatchMatchResult_arg1, dispatchMatchResult_arg2, dispatchMatchResult_arg3, dispatchMatchResult_arg4);
			break;
		}
		case 71:
		{
			FString dispatchMatchStatus_arg1 = stream.readString();
			dispatchMatchStatus(dispatchMatchStatus_arg1);
			break;
		}
		case 56:
		{
			FString dispatchMessageFromFriend_arg1 = stream.readString();
			FString dispatchMessageFromFriend_arg2 = stream.readString();
			dispatchMessageFromFriend(dispatchMessageFromFriend_arg1, dispatchMessageFromFriend_arg2);
			break;
		}
		case 49:
		{
			PLAYER_INFO dispatchPlayerInfo_arg1;
			((DATATYPE_PLAYER_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchPlayerInfo_arg1);
			dispatchPlayerInfo(dispatchPlayerInfo_arg1);
			break;
		}
		case 63:
		{
			PLAYER_TAG_INFO_LIST dispatchPlayerTagInfoList_arg1;
			((DATATYPE_PLAYER_TAG_INFO_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchPlayerTagInfoList_arg1);
			dispatchPlayerTagInfoList(dispatchPlayerTagInfoList_arg1);
			break;
		}
		case 51:
		{
			ALL_RANK_LIST dispatchRankList_arg1;
			((DATATYPE_ALL_RANK_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchRankList_arg1);
			dispatchRankList(dispatchRankList_arg1);
			break;
		}
		case 61:
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
		case 62:
		{
			PLAYER_INFO dispatchRelogonPlayerInfo_arg1;
			((DATATYPE_PLAYER_INFO*)pMethod->args[0])->createFromStreamEx(stream, dispatchRelogonPlayerInfo_arg1);
			GOODS_LIST dispatchRelogonPlayerInfo_arg2;
			((DATATYPE_GOODS_LIST*)pMethod->args[1])->createFromStreamEx(stream, dispatchRelogonPlayerInfo_arg2);
			dispatchRelogonPlayerInfo(dispatchRelogonPlayerInfo_arg1, dispatchRelogonPlayerInfo_arg2);
			break;
		}
		case 48:
		{
			BYTE_LIST dispatchRuneConfigEffectToClient_arg1;
			((DATATYPE_BYTE_LIST*)pMethod->args[0])->createFromStreamEx(stream, dispatchRuneConfigEffectToClient_arg1);
			uint8 dispatchRuneConfigEffectToClient_arg2 = stream.readUint8();
			dispatchRuneConfigEffectToClient(dispatchRuneConfigEffectToClient_arg1, dispatchRuneConfigEffectToClient_arg2);
			break;
		}
		case 57:
		{
			FString dispatchSendMessageResult_arg1 = stream.readString();
			FString dispatchSendMessageResult_arg2 = stream.readString();
			dispatchSendMessageResult(dispatchSendMessageResult_arg1, dispatchSendMessageResult_arg2);
			break;
		}
		case 69:
		{
			int32 dispatchTeamMatchInvitation_arg1 = stream.readInt32();
			FString dispatchTeamMatchInvitation_arg2 = stream.readString();
			FString dispatchTeamMatchInvitation_arg3 = stream.readString();
			int32 dispatchTeamMatchInvitation_arg4 = stream.readInt32();
			dispatchTeamMatchInvitation(dispatchTeamMatchInvitation_arg1, dispatchTeamMatchInvitation_arg2, dispatchTeamMatchInvitation_arg3, dispatchTeamMatchInvitation_arg4);
			break;
		}
		case 55:
		{
			FString dispatchTeamMatchStatus_arg1 = stream.readString();
			FString dispatchTeamMatchStatus_arg2 = stream.readString();
			dispatchTeamMatchStatus(dispatchTeamMatchStatus_arg1, dispatchTeamMatchStatus_arg2);
			break;
		}
		case 54:
		{
			FString gameDevelopFun_arg1 = stream.readString();
			gameDevelopFun(gameDevelopFun_arg1);
			break;
		}
		default:
			break;
	};
}

void AccountBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void AccountBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

AccountBase::AccountBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

AccountBase::~AccountBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

