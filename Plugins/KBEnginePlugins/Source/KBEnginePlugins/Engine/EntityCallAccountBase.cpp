#include "EntityCallAccountBase.h"
#include "Bundle.h"

void EntityBaseEntityCall_AccountBase::reqAddFriend(const FString& arg1)
{
	Bundle* pBundle = newCall("reqAddFriend");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqAllRuneDataFromServer()
{
	Bundle* pBundle = newCall("reqAllRuneDataFromServer");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqAnswerAddFriendRequest(uint8 arg1, uint64 arg2)
{
	Bundle* pBundle = newCall("reqAnswerAddFriendRequest");
	if(!pBundle)
		return;

	pBundle->writeUint8(arg1);
	pBundle->writeUint64(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqAnswerFriendMatch(uint8 arg1, const FString& arg2, const FString& arg3, int32 arg4)
{
	Bundle* pBundle = newCall("reqAnswerFriendMatch");
	if(!pBundle)
		return;

	pBundle->writeUint8(arg1);
	pBundle->writeString(arg2);
	pBundle->writeString(arg3);
	pBundle->writeInt32(arg4);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqBuy(const FString& arg1, uint8 arg2)
{
	Bundle* pBundle = newCall("reqBuy");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeUint8(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqCancelMatch()
{
	Bundle* pBundle = newCall("reqCancelMatch");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqChangeCurSelectCharacter(const FString& arg1)
{
	Bundle* pBundle = newCall("reqChangeCurSelectCharacter");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqDeleteFriend(const FString& arg1)
{
	Bundle* pBundle = newCall("reqDeleteFriend");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqEnsureEnterRoom()
{
	Bundle* pBundle = newCall("reqEnsureEnterRoom");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqFriendMatch(const REQ_TEAM_MATCH_DATA& arg1, const STRING_LIST& arg2, const FString& arg3)
{
	Bundle* pBundle = newCall("reqFriendMatch");
	if(!pBundle)
		return;

	((DATATYPE_REQ_TEAM_MATCH_DATA*)EntityDef::id2datatypes[68])->addToStreamEx(*pBundle, arg1);
	((DATATYPE_STRING_LIST*)EntityDef::id2datatypes[26])->addToStreamEx(*pBundle, arg2);
	pBundle->writeString(arg3);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqLoadLevelModelList()
{
	Bundle* pBundle = newCall("reqLoadLevelModelList");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqMallInfoList()
{
	Bundle* pBundle = newCall("reqMallInfoList");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqNotifyRecieveAddFriendRequest(uint64 arg1)
{
	Bundle* pBundle = newCall("reqNotifyRecieveAddFriendRequest");
	if(!pBundle)
		return;

	pBundle->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqOneOneMatch(const FString& arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqOneOneMatch");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeString(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqPlayerInfo()
{
	Bundle* pBundle = newCall("reqPlayerInfo");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqPlayerTagInfoList(const STRING_LIST& arg1)
{
	Bundle* pBundle = newCall("reqPlayerTagInfoList");
	if(!pBundle)
		return;

	((DATATYPE_STRING_LIST*)EntityDef::id2datatypes[26])->addToStreamEx(*pBundle, arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRankList()
{
	Bundle* pBundle = newCall("reqRankList");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqRelogonInfo()
{
	Bundle* pBundle = newCall("reqRelogonInfo");
	if(!pBundle)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqSendMessageToFriend(const FString& arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqSendMessageToFriend");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeString(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqSetRuneConfigDataToServer(const FString& arg1, uint8 arg2, uint8 arg3, uint8 arg4, uint8 arg5)
{
	Bundle* pBundle = newCall("reqSetRuneConfigDataToServer");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeUint8(arg2);
	pBundle->writeUint8(arg3);
	pBundle->writeUint8(arg4);
	pBundle->writeUint8(arg5);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqSimpleSingleMatch(const FString& arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqSimpleSingleMatch");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeString(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_AccountBase::reqSingleMatch(const FString& arg1, const FString& arg2)
{
	Bundle* pBundle = newCall("reqSingleMatch");
	if(!pBundle)
		return;

	pBundle->writeString(arg1);
	pBundle->writeString(arg2);
	sendCall(NULL);
}


