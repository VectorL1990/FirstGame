#include "Account.h"
#include "Engine/Entity.h"
#include "Engine/KBEngine.h"
#include "Engine/KBDebug.h"
#include "LogicEvents.h"
#include "TransferStructs.h"


Account::Account():
	AccountBase()
{
}

Account::~Account()
{
}

void Account::__init__()
{
	// 注册事件
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqPlayerInfo", "ReqPlayerInfo", [this](const UKBEventData* pEventData)
	{
		//const UKBEventData_reqPlayerInfo& data = static_cast<const UKBEventData_reqPlayerInfo&>(*pEventData);
		reqPlayerInfo();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqMallInfoList", "ReqMallInfoList", [this](const UKBEventData* pEventData)
	{
		//const UKBEventData_reqPlayerInfo& data = static_cast<const UKBEventData_reqPlayerInfo&>(*pEventData);
		ReqMallInfoList();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqLoadLevelModelList", "ReqLoadLevelModelList", [this](const UKBEventData* pEventData)
	{
		//const UKBEventData_reqPlayerInfo& data = static_cast<const UKBEventData_reqPlayerInfo&>(*pEventData);
		ReqLoadLevelModelList();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqSimpleSingleMatch", "ReqSimpleSingleMatch", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqSimpleSingleMatch& data = static_cast<const UKBEventData_reqSimpleSingleMatch&>(*pEventData);
		ReqSimpleSingleMatch(data.mapType, data.roleType);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqSingleMatch", "ReqSingleMatch", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqSingleMatch& data = static_cast<const UKBEventData_reqSingleMatch&>(*pEventData);
		ReqSingleMatch(data.mapType, data.roleType);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqOneOneMatch", "ReqOneOneMatch", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqSingleMatch& data = static_cast<const UKBEventData_reqSingleMatch&>(*pEventData);
		ReqOneOneMatch(data.mapType, data.roleType);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqEnsureEnterRoom", "ReqEnsureEnterRoom", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqEnsureEnterRoom& data = static_cast<const UKBEventData_reqEnsureEnterRoom&>(*pEventData);
		ReqEnsureEnterRoom();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCancelMatch", "ReqCancelMatch", [this](const UKBEventData* pEventData)
	{
		ReqCancelMatch();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRelogonInfo", "ReqRelogonInfo", [this](const UKBEventData* pEventData)
	{
		ReqRelogonInfo();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRankList", "ReqRankList", [this](const UKBEventData* pEventData)
	{
		ReqRankList();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqPlayerTagInfoList", "ReqPlayerTagInfoList", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqPlayerTagInfoList& data = static_cast<const UKBEventData_reqPlayerTagInfoList&>(*pEventData);
		STRING_LIST nameList;
		nameList.values = data.nameList;
		ReqPlayerTagInfoList(nameList);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqAddFriend", "ReqAddFriend", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqAddFriend& data = static_cast<const UKBEventData_reqAddFriend&>(*pEventData);
		ReqAddFriend(data.friendName);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqAnswerAddFriendRequest", "ReqAnswerAddFriendRequest", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqAnswerAddFriendRequest& data = static_cast<const UKBEventData_reqAnswerAddFriendRequest&>(*pEventData);
		if (!data.answer) ReqAnswerAddFriendRequest(0, data.applierDBID);
		else ReqAnswerAddFriendRequest(1, data.applierDBID);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqDeleteFriend", "ReqDeleteFriend", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqDeleteFriend& data = static_cast<const UKBEventData_reqDeleteFriend&>(*pEventData);
		ReqDeleteFriend(data.friendName);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqFriendMatch", "ReqFriendMatch", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqFriendMatch& data = static_cast<const UKBEventData_reqFriendMatch&>(*pEventData);
		FReqTeamMatchData hostData = data.hostData;
		REQ_TEAM_MATCH_DATA matchData = hostData.assign_REQ_TEAM_MATCH_DATA();
		STRING_LIST list;
		list.values = data.friendNameList;
		ReqFriendMatch(matchData, list, data.mapType);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqAnswerFriendMatch", "ReqAnswerFriendMatch", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqAnswerFriendMatch& data = static_cast<const UKBEventData_reqAnswerFriendMatch&>(*pEventData);
		if (data.result == false) ReqAnswerFriendMatch(0, data.hostName, data.roleType, data.groupNb);
		else ReqAnswerFriendMatch(1, data.hostName, data.roleType, data.groupNb);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqSendMessageToFriend", "ReqSendMessageToFriend", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqSendMessageToFriend& data = static_cast<const UKBEventData_reqSendMessageToFriend&>(*pEventData);
		ReqSendMessageToFriend(data.message, data.friendName);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqChangeCurSelectCharacter", "ReqChangeCurSelectCharacter", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_reqChangeCurSelectCharacter& data = static_cast<const UKBEventData_reqChangeCurSelectCharacter&>(*pEventData);
		ReqChangeCurSelectCharacter(data.roleType);
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqAllRuneDataFromServer", "ReqAllRuneDataFromServer", [this](const UKBEventData* pEventData)
	{
		ReqAllRuneDataFromServer();
	});
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqSetRuneConfigDataToServer", "ReqSetRuneConfigDataToServer", [this](const UKBEventData* pEventData)
	{
		const UKBEventData_ReqSetRuneConfigDataToServer& data = static_cast<const UKBEventData_ReqSetRuneConfigDataToServer&>(*pEventData);
		uint8 sky = data.sky;
		uint8 ground = data.ground;
		uint8 life = data.life;
		uint8 death = data.death;
		ReqSetRuneConfigDataToServer(data.runeConfigName, sky, ground, life, death);
	});
	
	// 触发登陆成功事件
	UKBEventData_onLoginSuccessfully* pEventData = NewObject<UKBEventData_onLoginSuccessfully>();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", pEventData);

	// 向服务端请求获得角色列表

}

void Account::onDestroy()
{
	// 注销注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void Account::dispatchLogonStatus(const FString& arg1, const FString& arg2)
{
	UKBEventData_dispatchLogonStatus* pEventData = NewObject<UKBEventData_dispatchLogonStatus>();
	pEventData->accountStatus = arg1;
	pEventData->curMatchingLevelName = arg2;
	KBENGINE_EVENT_FIRE("dispatchLogonStatus", pEventData);
}

void Account::dispatchBuyResult(uint8 arg1, int32 arg2, uint8 arg3, const FString& arg4)
{
	UKBEventData_dispatchBuyResult* pEventData = NewObject<UKBEventData_dispatchBuyResult>();
	if (arg1 == 0) pEventData->isSuccessful = false;
	else pEventData->isSuccessful = true;
	pEventData->moneyB = arg2;
	pEventData->goodsType = arg3;
	pEventData->goodsName = arg4;
	KBENGINE_EVENT_FIRE("dispatchBuyResult", pEventData);
}

void Account::dispatchLevelModelList(const LEVEL_MODEL_LIST& arg1)
{
	UKBEventData_dispatchLevelModelList* pEventData = NewObject<UKBEventData_dispatchLevelModelList>();
	pEventData->levelModelList.set_LEVEL_MODEL_LIST(arg1);
	KBENGINE_EVENT_FIRE("dispatchLevelModelList", pEventData);
}

void Account::dispatchMallInfoList(const GOODS_LIST& arg1)
{
	UKBEventData_dispatchMallInfoList* pEventData = NewObject<UKBEventData_dispatchMallInfoList>();
	pEventData->goodsList.set_GOODS_LIST(arg1);
	KBENGINE_EVENT_FIRE("dispatchMallInfoList", pEventData);
}

void Account::dispatchPlayerInfo(const PLAYER_INFO& arg1)
{
	UKBEventData_dispatchPlayerInfo* pEventData = NewObject<UKBEventData_dispatchPlayerInfo>();
	pEventData->playerInfo.set_PLAYER_INFO(arg1);
	pEventData->accountEntityID = id();
	KBENGINE_EVENT_FIRE("dispatchPlayerInfo", pEventData);
}

void Account::dispatchRankList(const ALL_RANK_LIST& arg1)
{
	UKBEventData_dispatchRankList* pEventData = NewObject<UKBEventData_dispatchRankList>();
	pEventData->allRankList.set_ALL_RANK_LIST(arg1);
	KBENGINE_EVENT_FIRE("dispatchRankList", pEventData);
}

void Account::gameDevelopFun(const FString& arg1)
{
	UKBEventData_gameDevelopFun* pEventData = NewObject<UKBEventData_gameDevelopFun>();
	pEventData->developInfo = arg1;
	KBENGINE_EVENT_FIRE("gameDevelopFun", pEventData);
}

void Account::dispatchMessageFromFriend(const FString& arg1, const FString& arg2)
{
	UKBEventData_dispatchMessageFromFriend* pEventData = NewObject<UKBEventData_dispatchMessageFromFriend>();
	pEventData->friendName = arg1;
	pEventData->message = arg2;
	KBENGINE_EVENT_FIRE("dispatchMessageFromFriend", pEventData);
}

void Account::dispatchSendMessageResult(const FString& arg1, const FString& arg2)
{

}

void Account::dispatchMatchResult(const FString& arg1, uint8 arg2, const FString& arg3, const PLAYER_TAG_INFO_LIST& arg4)
{
	UKBEventData_dispatchMatchResult* pEventData = NewObject<UKBEventData_dispatchMatchResult>();
	pEventData->matchResult = arg1;
	pEventData->playerAssignNb = arg2;
	pEventData->roomType = arg3;
	pEventData->playerTagList.set_PLAYER_TAG_INFO_LIST(arg4);
	KBENGINE_EVENT_FIRE("dispatchMatchResult", pEventData);
}

void Account::dispatchAllPlayerRoletypeAndAssignNb(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int32 arg5)
{
	UKBEventData_dispatchAllPlayerRoletypeAndAssignNb* pEventData = NewObject<UKBEventData_dispatchAllPlayerRoletypeAndAssignNb>();
	pEventData->levelName = arg1;
	pEventData->playerID = arg2;
	pEventData->playerRoletypeAssignnumList.set_PLAYER_ROLETYPE_ASSIGNNUM_LIST(arg3);
	pEventData->battleResult.set_BATTLE_RESULT(arg4);
	pEventData->maxFrameNb = arg5;
	KBENGINE_EVENT_FIRE("dispatchAllPlayerRoletypeAndAssignNb", pEventData);
}

void Account::dispatchRelogonInfo(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int8 arg5, const FString& arg6)
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

void Account::dispatchRelogonPlayerInfo(const PLAYER_INFO& arg1, const GOODS_LIST& arg2)
{
	UKBEventData_dispatchRelogonPlayerInfo* pEventData = NewObject<UKBEventData_dispatchRelogonPlayerInfo>();
	pEventData->info.set_PLAYER_INFO(arg1);
	pEventData->list.set_GOODS_LIST(arg2);
	pEventData->accountEntityID = id();
	KBENGINE_EVENT_FIRE("dispatchRelogonPlayerInfo", pEventData);
}

void Account::dispatchPlayerTagInfoList(const PLAYER_TAG_INFO_LIST& arg1)
{
	UKBEventData_dispatchPlayerTagInfoList* pEventData = NewObject<UKBEventData_dispatchPlayerTagInfoList>();
	pEventData->list.set_PLAYER_TAG_INFO_LIST(arg1);
	KBENGINE_EVENT_FIRE("dispatchPlayerTagInfoList", pEventData);
}

void Account::dispatchAddFriendRequestResult(uint8 arg1)
{
	UKBEventData_dispatchAddFriendRequestResult* pEventData = NewObject<UKBEventData_dispatchAddFriendRequestResult>();
	if (arg1 == 0) pEventData->result = false;
	else pEventData->result = true;
	KBENGINE_EVENT_FIRE("dispatchAddFriendRequestResult", pEventData);
}

void Account::dispatchAddFriendRequest(const FString& arg1, uint64 arg2)
{
	UKBEventData_dispatchAddFriendRequest* pEventData = NewObject<UKBEventData_dispatchAddFriendRequest>();
	pEventData->name = arg1;
	pEventData->applierDBID = arg2;
	KBENGINE_EVENT_FIRE("dispatchAddFriendRequest", pEventData);
	ReqNotifyRecieveAddFriendRequest(arg2);
}

void Account::dispatchDisapproveAddFriendAnswer(const FString& arg1)
{
	UKBEventData_dispatchDisapproveAddFriendAnswer* pEventData = NewObject<UKBEventData_dispatchDisapproveAddFriendAnswer>();
	pEventData->name = arg1;
	KBENGINE_EVENT_FIRE("dispatchDisapproveAddFriendAnswer", pEventData);
}

void Account::dispatchApproveAddFriendAnswer(const FString& arg1, const PLAYER_TAG_INFO& arg2)
{
	UKBEventData_dispatchApproveAddFriendAnswer* pEventData = NewObject<UKBEventData_dispatchApproveAddFriendAnswer>();
	pEventData->name = arg1;
	pEventData->playerTagInfo.set_PLAYER_TAG_INFO(arg2);
	KBENGINE_EVENT_FIRE("dispatchApproveAddFriendAnswer", pEventData);
}

void Account::dispatchDeleteFriendRequestResult(uint8 arg1, const FString& arg2)
{
	UKBEventData_dispatchDeleteFriendRequestResult* pEventData = NewObject<UKBEventData_dispatchDeleteFriendRequestResult>();
	if (arg1 == 0) pEventData->result = false;
	else pEventData->result = true;
	pEventData->deleteName = arg2;
	KBENGINE_EVENT_FIRE("dispatchDeleteFriendRequestResult", pEventData);
}

void Account::dispatchTeamMatchStatus(const FString& arg1, const FString& arg2)
{
	UKBEventData_dispatchTeamMatchStatus* pEventData = NewObject<UKBEventData_dispatchTeamMatchStatus>();
	pEventData->hostName = arg1;
	pEventData->message = arg2;
	KBENGINE_EVENT_FIRE("dispatchTeamMatchStatus", pEventData);
}

void Account::dispatchTeamMatchInvitation(int32 arg1, const FString& arg2, const FString& arg3, int32 arg4)
{
	UKBEventData_dispatchTeamMatchInvitation* pEventData = NewObject<UKBEventData_dispatchTeamMatchInvitation>();
	pEventData->hostEntityID = arg1;
	pEventData->hostName = arg2;
	pEventData->matchType = arg3;
	pEventData->groupNb = arg4;
	KBENGINE_EVENT_FIRE("dispatchTeamMatchInvitation", pEventData);
}

void Account::dispatchCancelMatch()
{
	UKBEventData_dispatchCancelMatch* pEventData = NewObject<UKBEventData_dispatchCancelMatch>();
	KBENGINE_EVENT_FIRE("dispatchCancelMatch", pEventData);
}

void Account::dispatchMatchStatus(const FString& arg1)
{
	UKBEventData_dispatchMatchStatus* pEventData = NewObject<UKBEventData_dispatchMatchStatus>();
	pEventData->status = arg1;
	KBENGINE_EVENT_FIRE("dispatchMatchStatus", pEventData);
}

void Account::dispatchAllRuneDataToClient(const RUNEINFOLIST& arg1, const RUNECONFIGINFOLIST& arg2)
{
	UKBEventData_dispatchAllRuneDataToClient* pEventData = NewObject<UKBEventData_dispatchAllRuneDataToClient>();
	pEventData->runeInfoList.set_REQ_TEAM_MATCH_DATA(arg1);
	pEventData->runeConfigInfoList.set_RUNE_CONFIG_INFO_LIST(arg2);
	KBENGINE_EVENT_FIRE("dispatchAllRuneDataToClient", pEventData);
}

void Account::dispatchRuneConfigEffectToClient(const BYTE_LIST& arg1, uint8 arg2)
{
	UKBEventData_dispatchRuneConfigEffectToClient* pEventData = NewObject<UKBEventData_dispatchRuneConfigEffectToClient>();
	int32 attributeNb = arg1.values.Num() / 2;
	for (int32 i=0; i<arg1.values.Num(); i+=2)
	{
		FString attribute;
		if (arg1.values[i] == 1) attribute = TEXT("life");
		else if (arg1.values[i] == 2) attribute = TEXT("ATK");
		else if (arg1.values[i] == 3) attribute = TEXT("magATK");
		else if (arg1.values[i] == 4) attribute = TEXT("DFC");
		else attribute = TEXT("magDFC");
		int32 effect = arg1.values[i + 1];
		pEventData->runeConfigEffectInfo.attributeList.Add(attribute);
		pEventData->runeConfigEffectInfo.effectList.Add(effect);
	}
	pEventData->runeConfigEffectInfo.effectNb = arg2;
	KBENGINE_EVENT_FIRE("dispatchRuneConfigEffectToClient", pEventData);
}

void Account::dispatchHasConfigInfosToClient(const BYTE_LIST& arg1)
{
	UKBEventData_dispatchHasConfigInfosToClient* pEventData = NewObject<UKBEventData_dispatchHasConfigInfosToClient>();
	for (int32 i=0; i<arg1.values.Num(); i++)
	{
		pEventData->hasRuneList.Add(arg1.values[i]);
	}
	KBENGINE_EVENT_FIRE("dispatchHasConfigInfosToClient", pEventData);
}

void Account::reqPlayerInfo()
{
	pBaseEntityCall->reqPlayerInfo();
}

void Account::ReqMallInfoList()
{
	pBaseEntityCall->reqMallInfoList();
}

void Account::ReqLoadLevelModelList()
{
	pBaseEntityCall->reqLoadLevelModelList();
}

void Account::ReqSimpleSingleMatch(FString mapType, FString roleType)
{
	pBaseEntityCall->reqSimpleSingleMatch(mapType, roleType);
}

void Account::ReqSingleMatch(FString mapType, FString roleType)
{
	pBaseEntityCall->reqSingleMatch(mapType, roleType);
}

void Account::ReqOneOneMatch(FString mapType, FString roleType)
{
	pBaseEntityCall->reqOneOneMatch(mapType, roleType);
}

void Account::ReqEnsureEnterRoom()
{
	pBaseEntityCall->reqEnsureEnterRoom();
}

void Account::ReqCancelMatch()
{
	pBaseEntityCall->reqCancelMatch();
}

void Account::ReqRelogonInfo()
{
	pBaseEntityCall->reqRelogonInfo();
}

void Account::ReqRankList()
{
	pBaseEntityCall->reqRankList();
}

void Account::ReqPlayerTagInfoList(STRING_LIST nameList)
{
	pBaseEntityCall->reqPlayerTagInfoList(nameList);
}

void Account::ReqAddFriend(FString FriendName)
{
	pBaseEntityCall->reqAddFriend(FriendName);
}

void Account::ReqNotifyRecieveAddFriendRequest(uint64 applierDBID)
{
	pBaseEntityCall->reqNotifyRecieveAddFriendRequest(applierDBID);
}

void Account::ReqAnswerAddFriendRequest(uint8 answer, uint64 applierDBID)
{
	pBaseEntityCall->reqAnswerAddFriendRequest(answer, applierDBID);
}

void Account::ReqDeleteFriend(FString friendName)
{
	pBaseEntityCall->reqDeleteFriend(friendName);
}

void Account::ReqFriendMatch(const REQ_TEAM_MATCH_DATA& data, const STRING_LIST& friendNameList, const FString& mapType)
{
	pBaseEntityCall->reqFriendMatch(data, friendNameList, mapType);
}

void Account::ReqAnswerFriendMatch(uint8 result, FString hostName, FString roleType, int32 groupNb)
{
	pBaseEntityCall->reqAnswerFriendMatch(result, hostName, roleType, groupNb);
}

void Account::ReqSendMessageToFriend(const FString& message, const FString& friendName)
{
	pBaseEntityCall->reqSendMessageToFriend(message, friendName);
}

void Account::ReqChangeCurSelectCharacter(const FString& roleType)
{
	pBaseEntityCall->reqChangeCurSelectCharacter(roleType);
}

void Account::ReqAllRuneDataFromServer()
{
	pBaseEntityCall->reqAllRuneDataFromServer();
}

void Account::ReqSetRuneConfigDataToServer(const FString& runeConfigName, uint8 sky, uint8 ground, uint8 life, uint8 death)
{
	pBaseEntityCall->reqSetRuneConfigDataToServer(runeConfigName, sky, ground, life, death);
}

