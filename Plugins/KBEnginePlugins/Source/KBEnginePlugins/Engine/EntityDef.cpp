#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/Account.h"
#include "Scripts/CommunicateStation.h"

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new Account();
			break;
		case 2:
			pEntity = new CommunicateStation();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pAccountModule = new ScriptModule("Account", 1);
	EntityDef::moduledefs.Add(TEXT("Account"), pAccountModule);
	EntityDef::idmoduledefs.Add(1, pAccountModule);

	Property* pAccount_position = new Property();
	pAccount_position->name = TEXT("position");
	pAccount_position->properUtype = 40000;
	pAccount_position->properFlags = 4;
	pAccount_position->aliasID = 0;
	KBVar* pAccount_position_defval = new KBVar(FVector());
	pAccount_position->pDefaultVal = pAccount_position_defval;
	pAccountModule->propertys.Add(TEXT("position"), pAccount_position); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_position->aliasID, pAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(position / 40000).");

	Property* pAccount_direction = new Property();
	pAccount_direction->name = TEXT("direction");
	pAccount_direction->properUtype = 40001;
	pAccount_direction->properFlags = 4;
	pAccount_direction->aliasID = 1;
	KBVar* pAccount_direction_defval = new KBVar(FVector());
	pAccount_direction->pDefaultVal = pAccount_direction_defval;
	pAccountModule->propertys.Add(TEXT("direction"), pAccount_direction); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_direction->aliasID, pAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(direction / 40001).");

	Property* pAccount_spaceID = new Property();
	pAccount_spaceID->name = TEXT("spaceID");
	pAccount_spaceID->properUtype = 40002;
	pAccount_spaceID->properFlags = 16;
	pAccount_spaceID->aliasID = 2;
	KBVar* pAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pAccount_spaceID->pDefaultVal = pAccount_spaceID_defval;
	pAccountModule->propertys.Add(TEXT("spaceID"), pAccount_spaceID); 

	pAccountModule->usePropertyDescrAlias = true;
	pAccountModule->idpropertys.Add((uint16)pAccount_spaceID->aliasID, pAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), property(spaceID / 40002).");

	TArray<DATATYPE_BASE*> Account_dispatchAddFriendRequest_args;
	Account_dispatchAddFriendRequest_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchAddFriendRequest_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_dispatchAddFriendRequest = new Method();
	pAccount_dispatchAddFriendRequest->name = TEXT("dispatchAddFriendRequest");
	pAccount_dispatchAddFriendRequest->methodUtype = 64;
	pAccount_dispatchAddFriendRequest->aliasID = 0;
	pAccount_dispatchAddFriendRequest->args = Account_dispatchAddFriendRequest_args;

	pAccountModule->methods.Add(TEXT("dispatchAddFriendRequest"), pAccount_dispatchAddFriendRequest); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchAddFriendRequest->aliasID, pAccount_dispatchAddFriendRequest);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchAddFriendRequest / 64).");

	TArray<DATATYPE_BASE*> Account_dispatchAddFriendRequestResult_args;
	Account_dispatchAddFriendRequestResult_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_dispatchAddFriendRequestResult = new Method();
	pAccount_dispatchAddFriendRequestResult->name = TEXT("dispatchAddFriendRequestResult");
	pAccount_dispatchAddFriendRequestResult->methodUtype = 65;
	pAccount_dispatchAddFriendRequestResult->aliasID = 1;
	pAccount_dispatchAddFriendRequestResult->args = Account_dispatchAddFriendRequestResult_args;

	pAccountModule->methods.Add(TEXT("dispatchAddFriendRequestResult"), pAccount_dispatchAddFriendRequestResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchAddFriendRequestResult->aliasID, pAccount_dispatchAddFriendRequestResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchAddFriendRequestResult / 65).");

	TArray<DATATYPE_BASE*> Account_dispatchAllPlayerRoletypeAndAssignNb_args;
	Account_dispatchAllPlayerRoletypeAndAssignNb_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchAllPlayerRoletypeAndAssignNb_args.Add(EntityDef::id2datatypes[8]);
	Account_dispatchAllPlayerRoletypeAndAssignNb_args.Add(EntityDef::id2datatypes[239]);
	Account_dispatchAllPlayerRoletypeAndAssignNb_args.Add(EntityDef::id2datatypes[232]);
	Account_dispatchAllPlayerRoletypeAndAssignNb_args.Add(EntityDef::id2datatypes[8]);

	Method* pAccount_dispatchAllPlayerRoletypeAndAssignNb = new Method();
	pAccount_dispatchAllPlayerRoletypeAndAssignNb->name = TEXT("dispatchAllPlayerRoletypeAndAssignNb");
	pAccount_dispatchAllPlayerRoletypeAndAssignNb->methodUtype = 59;
	pAccount_dispatchAllPlayerRoletypeAndAssignNb->aliasID = 2;
	pAccount_dispatchAllPlayerRoletypeAndAssignNb->args = Account_dispatchAllPlayerRoletypeAndAssignNb_args;

	pAccountModule->methods.Add(TEXT("dispatchAllPlayerRoletypeAndAssignNb"), pAccount_dispatchAllPlayerRoletypeAndAssignNb); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchAllPlayerRoletypeAndAssignNb->aliasID, pAccount_dispatchAllPlayerRoletypeAndAssignNb);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchAllPlayerRoletypeAndAssignNb / 59).");

	TArray<DATATYPE_BASE*> Account_dispatchAllRuneDataToClient_args;
	Account_dispatchAllRuneDataToClient_args.Add(EntityDef::id2datatypes[52]);
	Account_dispatchAllRuneDataToClient_args.Add(EntityDef::id2datatypes[55]);

	Method* pAccount_dispatchAllRuneDataToClient = new Method();
	pAccount_dispatchAllRuneDataToClient->name = TEXT("dispatchAllRuneDataToClient");
	pAccount_dispatchAllRuneDataToClient->methodUtype = 46;
	pAccount_dispatchAllRuneDataToClient->aliasID = 3;
	pAccount_dispatchAllRuneDataToClient->args = Account_dispatchAllRuneDataToClient_args;

	pAccountModule->methods.Add(TEXT("dispatchAllRuneDataToClient"), pAccount_dispatchAllRuneDataToClient); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchAllRuneDataToClient->aliasID, pAccount_dispatchAllRuneDataToClient);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchAllRuneDataToClient / 46).");

	TArray<DATATYPE_BASE*> Account_dispatchApproveAddFriendAnswer_args;
	Account_dispatchApproveAddFriendAnswer_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchApproveAddFriendAnswer_args.Add(EntityDef::id2datatypes[31]);

	Method* pAccount_dispatchApproveAddFriendAnswer = new Method();
	pAccount_dispatchApproveAddFriendAnswer->name = TEXT("dispatchApproveAddFriendAnswer");
	pAccount_dispatchApproveAddFriendAnswer->methodUtype = 66;
	pAccount_dispatchApproveAddFriendAnswer->aliasID = 4;
	pAccount_dispatchApproveAddFriendAnswer->args = Account_dispatchApproveAddFriendAnswer_args;

	pAccountModule->methods.Add(TEXT("dispatchApproveAddFriendAnswer"), pAccount_dispatchApproveAddFriendAnswer); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchApproveAddFriendAnswer->aliasID, pAccount_dispatchApproveAddFriendAnswer);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchApproveAddFriendAnswer / 66).");

	TArray<DATATYPE_BASE*> Account_dispatchBuyResult_args;
	Account_dispatchBuyResult_args.Add(EntityDef::id2datatypes[2]);
	Account_dispatchBuyResult_args.Add(EntityDef::id2datatypes[8]);
	Account_dispatchBuyResult_args.Add(EntityDef::id2datatypes[2]);
	Account_dispatchBuyResult_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchBuyResult = new Method();
	pAccount_dispatchBuyResult->name = TEXT("dispatchBuyResult");
	pAccount_dispatchBuyResult->methodUtype = 53;
	pAccount_dispatchBuyResult->aliasID = 5;
	pAccount_dispatchBuyResult->args = Account_dispatchBuyResult_args;

	pAccountModule->methods.Add(TEXT("dispatchBuyResult"), pAccount_dispatchBuyResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchBuyResult->aliasID, pAccount_dispatchBuyResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchBuyResult / 53).");

	TArray<DATATYPE_BASE*> Account_dispatchCancelMatch_args;

	Method* pAccount_dispatchCancelMatch = new Method();
	pAccount_dispatchCancelMatch->name = TEXT("dispatchCancelMatch");
	pAccount_dispatchCancelMatch->methodUtype = 70;
	pAccount_dispatchCancelMatch->aliasID = 6;
	pAccount_dispatchCancelMatch->args = Account_dispatchCancelMatch_args;

	pAccountModule->methods.Add(TEXT("dispatchCancelMatch"), pAccount_dispatchCancelMatch); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchCancelMatch->aliasID, pAccount_dispatchCancelMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchCancelMatch / 70).");

	TArray<DATATYPE_BASE*> Account_dispatchDeleteFriendRequestResult_args;
	Account_dispatchDeleteFriendRequestResult_args.Add(EntityDef::id2datatypes[2]);
	Account_dispatchDeleteFriendRequestResult_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchDeleteFriendRequestResult = new Method();
	pAccount_dispatchDeleteFriendRequestResult->name = TEXT("dispatchDeleteFriendRequestResult");
	pAccount_dispatchDeleteFriendRequestResult->methodUtype = 68;
	pAccount_dispatchDeleteFriendRequestResult->aliasID = 7;
	pAccount_dispatchDeleteFriendRequestResult->args = Account_dispatchDeleteFriendRequestResult_args;

	pAccountModule->methods.Add(TEXT("dispatchDeleteFriendRequestResult"), pAccount_dispatchDeleteFriendRequestResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchDeleteFriendRequestResult->aliasID, pAccount_dispatchDeleteFriendRequestResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchDeleteFriendRequestResult / 68).");

	TArray<DATATYPE_BASE*> Account_dispatchDisapproveAddFriendAnswer_args;
	Account_dispatchDisapproveAddFriendAnswer_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchDisapproveAddFriendAnswer = new Method();
	pAccount_dispatchDisapproveAddFriendAnswer->name = TEXT("dispatchDisapproveAddFriendAnswer");
	pAccount_dispatchDisapproveAddFriendAnswer->methodUtype = 67;
	pAccount_dispatchDisapproveAddFriendAnswer->aliasID = 8;
	pAccount_dispatchDisapproveAddFriendAnswer->args = Account_dispatchDisapproveAddFriendAnswer_args;

	pAccountModule->methods.Add(TEXT("dispatchDisapproveAddFriendAnswer"), pAccount_dispatchDisapproveAddFriendAnswer); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchDisapproveAddFriendAnswer->aliasID, pAccount_dispatchDisapproveAddFriendAnswer);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchDisapproveAddFriendAnswer / 67).");

	TArray<DATATYPE_BASE*> Account_dispatchHasConfigInfosToClient_args;
	Account_dispatchHasConfigInfosToClient_args.Add(EntityDef::id2datatypes[24]);

	Method* pAccount_dispatchHasConfigInfosToClient = new Method();
	pAccount_dispatchHasConfigInfosToClient->name = TEXT("dispatchHasConfigInfosToClient");
	pAccount_dispatchHasConfigInfosToClient->methodUtype = 47;
	pAccount_dispatchHasConfigInfosToClient->aliasID = 9;
	pAccount_dispatchHasConfigInfosToClient->args = Account_dispatchHasConfigInfosToClient_args;

	pAccountModule->methods.Add(TEXT("dispatchHasConfigInfosToClient"), pAccount_dispatchHasConfigInfosToClient); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchHasConfigInfosToClient->aliasID, pAccount_dispatchHasConfigInfosToClient);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchHasConfigInfosToClient / 47).");

	TArray<DATATYPE_BASE*> Account_dispatchLevelModelList_args;
	Account_dispatchLevelModelList_args.Add(EntityDef::id2datatypes[211]);

	Method* pAccount_dispatchLevelModelList = new Method();
	pAccount_dispatchLevelModelList->name = TEXT("dispatchLevelModelList");
	pAccount_dispatchLevelModelList->methodUtype = 50;
	pAccount_dispatchLevelModelList->aliasID = 10;
	pAccount_dispatchLevelModelList->args = Account_dispatchLevelModelList_args;

	pAccountModule->methods.Add(TEXT("dispatchLevelModelList"), pAccount_dispatchLevelModelList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchLevelModelList->aliasID, pAccount_dispatchLevelModelList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchLevelModelList / 50).");

	TArray<DATATYPE_BASE*> Account_dispatchLogonStatus_args;
	Account_dispatchLogonStatus_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchLogonStatus_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchLogonStatus = new Method();
	pAccount_dispatchLogonStatus->name = TEXT("dispatchLogonStatus");
	pAccount_dispatchLogonStatus->methodUtype = 60;
	pAccount_dispatchLogonStatus->aliasID = 11;
	pAccount_dispatchLogonStatus->args = Account_dispatchLogonStatus_args;

	pAccountModule->methods.Add(TEXT("dispatchLogonStatus"), pAccount_dispatchLogonStatus); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchLogonStatus->aliasID, pAccount_dispatchLogonStatus);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchLogonStatus / 60).");

	TArray<DATATYPE_BASE*> Account_dispatchMallInfoList_args;
	Account_dispatchMallInfoList_args.Add(EntityDef::id2datatypes[245]);

	Method* pAccount_dispatchMallInfoList = new Method();
	pAccount_dispatchMallInfoList->name = TEXT("dispatchMallInfoList");
	pAccount_dispatchMallInfoList->methodUtype = 52;
	pAccount_dispatchMallInfoList->aliasID = 12;
	pAccount_dispatchMallInfoList->args = Account_dispatchMallInfoList_args;

	pAccountModule->methods.Add(TEXT("dispatchMallInfoList"), pAccount_dispatchMallInfoList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchMallInfoList->aliasID, pAccount_dispatchMallInfoList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchMallInfoList / 52).");

	TArray<DATATYPE_BASE*> Account_dispatchMatchResult_args;
	Account_dispatchMatchResult_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchMatchResult_args.Add(EntityDef::id2datatypes[2]);
	Account_dispatchMatchResult_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchMatchResult_args.Add(EntityDef::id2datatypes[32]);

	Method* pAccount_dispatchMatchResult = new Method();
	pAccount_dispatchMatchResult->name = TEXT("dispatchMatchResult");
	pAccount_dispatchMatchResult->methodUtype = 58;
	pAccount_dispatchMatchResult->aliasID = 13;
	pAccount_dispatchMatchResult->args = Account_dispatchMatchResult_args;

	pAccountModule->methods.Add(TEXT("dispatchMatchResult"), pAccount_dispatchMatchResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchMatchResult->aliasID, pAccount_dispatchMatchResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchMatchResult / 58).");

	TArray<DATATYPE_BASE*> Account_dispatchMatchStatus_args;
	Account_dispatchMatchStatus_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchMatchStatus = new Method();
	pAccount_dispatchMatchStatus->name = TEXT("dispatchMatchStatus");
	pAccount_dispatchMatchStatus->methodUtype = 71;
	pAccount_dispatchMatchStatus->aliasID = 14;
	pAccount_dispatchMatchStatus->args = Account_dispatchMatchStatus_args;

	pAccountModule->methods.Add(TEXT("dispatchMatchStatus"), pAccount_dispatchMatchStatus); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchMatchStatus->aliasID, pAccount_dispatchMatchStatus);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchMatchStatus / 71).");

	TArray<DATATYPE_BASE*> Account_dispatchMessageFromFriend_args;
	Account_dispatchMessageFromFriend_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchMessageFromFriend_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchMessageFromFriend = new Method();
	pAccount_dispatchMessageFromFriend->name = TEXT("dispatchMessageFromFriend");
	pAccount_dispatchMessageFromFriend->methodUtype = 56;
	pAccount_dispatchMessageFromFriend->aliasID = 15;
	pAccount_dispatchMessageFromFriend->args = Account_dispatchMessageFromFriend_args;

	pAccountModule->methods.Add(TEXT("dispatchMessageFromFriend"), pAccount_dispatchMessageFromFriend); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchMessageFromFriend->aliasID, pAccount_dispatchMessageFromFriend);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchMessageFromFriend / 56).");

	TArray<DATATYPE_BASE*> Account_dispatchPlayerInfo_args;
	Account_dispatchPlayerInfo_args.Add(EntityDef::id2datatypes[59]);

	Method* pAccount_dispatchPlayerInfo = new Method();
	pAccount_dispatchPlayerInfo->name = TEXT("dispatchPlayerInfo");
	pAccount_dispatchPlayerInfo->methodUtype = 49;
	pAccount_dispatchPlayerInfo->aliasID = 16;
	pAccount_dispatchPlayerInfo->args = Account_dispatchPlayerInfo_args;

	pAccountModule->methods.Add(TEXT("dispatchPlayerInfo"), pAccount_dispatchPlayerInfo); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchPlayerInfo->aliasID, pAccount_dispatchPlayerInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchPlayerInfo / 49).");

	TArray<DATATYPE_BASE*> Account_dispatchPlayerTagInfoList_args;
	Account_dispatchPlayerTagInfoList_args.Add(EntityDef::id2datatypes[32]);

	Method* pAccount_dispatchPlayerTagInfoList = new Method();
	pAccount_dispatchPlayerTagInfoList->name = TEXT("dispatchPlayerTagInfoList");
	pAccount_dispatchPlayerTagInfoList->methodUtype = 63;
	pAccount_dispatchPlayerTagInfoList->aliasID = 17;
	pAccount_dispatchPlayerTagInfoList->args = Account_dispatchPlayerTagInfoList_args;

	pAccountModule->methods.Add(TEXT("dispatchPlayerTagInfoList"), pAccount_dispatchPlayerTagInfoList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchPlayerTagInfoList->aliasID, pAccount_dispatchPlayerTagInfoList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchPlayerTagInfoList / 63).");

	TArray<DATATYPE_BASE*> Account_dispatchRankList_args;
	Account_dispatchRankList_args.Add(EntityDef::id2datatypes[216]);

	Method* pAccount_dispatchRankList = new Method();
	pAccount_dispatchRankList->name = TEXT("dispatchRankList");
	pAccount_dispatchRankList->methodUtype = 51;
	pAccount_dispatchRankList->aliasID = 18;
	pAccount_dispatchRankList->args = Account_dispatchRankList_args;

	pAccountModule->methods.Add(TEXT("dispatchRankList"), pAccount_dispatchRankList); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchRankList->aliasID, pAccount_dispatchRankList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchRankList / 51).");

	TArray<DATATYPE_BASE*> Account_dispatchRelogonInfo_args;
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[8]);
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[239]);
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[232]);
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[6]);
	Account_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchRelogonInfo = new Method();
	pAccount_dispatchRelogonInfo->name = TEXT("dispatchRelogonInfo");
	pAccount_dispatchRelogonInfo->methodUtype = 61;
	pAccount_dispatchRelogonInfo->aliasID = 19;
	pAccount_dispatchRelogonInfo->args = Account_dispatchRelogonInfo_args;

	pAccountModule->methods.Add(TEXT("dispatchRelogonInfo"), pAccount_dispatchRelogonInfo); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchRelogonInfo->aliasID, pAccount_dispatchRelogonInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchRelogonInfo / 61).");

	TArray<DATATYPE_BASE*> Account_dispatchRelogonPlayerInfo_args;
	Account_dispatchRelogonPlayerInfo_args.Add(EntityDef::id2datatypes[59]);
	Account_dispatchRelogonPlayerInfo_args.Add(EntityDef::id2datatypes[245]);

	Method* pAccount_dispatchRelogonPlayerInfo = new Method();
	pAccount_dispatchRelogonPlayerInfo->name = TEXT("dispatchRelogonPlayerInfo");
	pAccount_dispatchRelogonPlayerInfo->methodUtype = 62;
	pAccount_dispatchRelogonPlayerInfo->aliasID = 20;
	pAccount_dispatchRelogonPlayerInfo->args = Account_dispatchRelogonPlayerInfo_args;

	pAccountModule->methods.Add(TEXT("dispatchRelogonPlayerInfo"), pAccount_dispatchRelogonPlayerInfo); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchRelogonPlayerInfo->aliasID, pAccount_dispatchRelogonPlayerInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchRelogonPlayerInfo / 62).");

	TArray<DATATYPE_BASE*> Account_dispatchRuneConfigEffectToClient_args;
	Account_dispatchRuneConfigEffectToClient_args.Add(EntityDef::id2datatypes[24]);
	Account_dispatchRuneConfigEffectToClient_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_dispatchRuneConfigEffectToClient = new Method();
	pAccount_dispatchRuneConfigEffectToClient->name = TEXT("dispatchRuneConfigEffectToClient");
	pAccount_dispatchRuneConfigEffectToClient->methodUtype = 48;
	pAccount_dispatchRuneConfigEffectToClient->aliasID = 21;
	pAccount_dispatchRuneConfigEffectToClient->args = Account_dispatchRuneConfigEffectToClient_args;

	pAccountModule->methods.Add(TEXT("dispatchRuneConfigEffectToClient"), pAccount_dispatchRuneConfigEffectToClient); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchRuneConfigEffectToClient->aliasID, pAccount_dispatchRuneConfigEffectToClient);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchRuneConfigEffectToClient / 48).");

	TArray<DATATYPE_BASE*> Account_dispatchSendMessageResult_args;
	Account_dispatchSendMessageResult_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchSendMessageResult_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchSendMessageResult = new Method();
	pAccount_dispatchSendMessageResult->name = TEXT("dispatchSendMessageResult");
	pAccount_dispatchSendMessageResult->methodUtype = 57;
	pAccount_dispatchSendMessageResult->aliasID = 22;
	pAccount_dispatchSendMessageResult->args = Account_dispatchSendMessageResult_args;

	pAccountModule->methods.Add(TEXT("dispatchSendMessageResult"), pAccount_dispatchSendMessageResult); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchSendMessageResult->aliasID, pAccount_dispatchSendMessageResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchSendMessageResult / 57).");

	TArray<DATATYPE_BASE*> Account_dispatchTeamMatchInvitation_args;
	Account_dispatchTeamMatchInvitation_args.Add(EntityDef::id2datatypes[8]);
	Account_dispatchTeamMatchInvitation_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchTeamMatchInvitation_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchTeamMatchInvitation_args.Add(EntityDef::id2datatypes[8]);

	Method* pAccount_dispatchTeamMatchInvitation = new Method();
	pAccount_dispatchTeamMatchInvitation->name = TEXT("dispatchTeamMatchInvitation");
	pAccount_dispatchTeamMatchInvitation->methodUtype = 69;
	pAccount_dispatchTeamMatchInvitation->aliasID = 23;
	pAccount_dispatchTeamMatchInvitation->args = Account_dispatchTeamMatchInvitation_args;

	pAccountModule->methods.Add(TEXT("dispatchTeamMatchInvitation"), pAccount_dispatchTeamMatchInvitation); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchTeamMatchInvitation->aliasID, pAccount_dispatchTeamMatchInvitation);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchTeamMatchInvitation / 69).");

	TArray<DATATYPE_BASE*> Account_dispatchTeamMatchStatus_args;
	Account_dispatchTeamMatchStatus_args.Add(EntityDef::id2datatypes[1]);
	Account_dispatchTeamMatchStatus_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_dispatchTeamMatchStatus = new Method();
	pAccount_dispatchTeamMatchStatus->name = TEXT("dispatchTeamMatchStatus");
	pAccount_dispatchTeamMatchStatus->methodUtype = 55;
	pAccount_dispatchTeamMatchStatus->aliasID = 24;
	pAccount_dispatchTeamMatchStatus->args = Account_dispatchTeamMatchStatus_args;

	pAccountModule->methods.Add(TEXT("dispatchTeamMatchStatus"), pAccount_dispatchTeamMatchStatus); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_dispatchTeamMatchStatus->aliasID, pAccount_dispatchTeamMatchStatus);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(dispatchTeamMatchStatus / 55).");

	TArray<DATATYPE_BASE*> Account_gameDevelopFun_args;
	Account_gameDevelopFun_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_gameDevelopFun = new Method();
	pAccount_gameDevelopFun->name = TEXT("gameDevelopFun");
	pAccount_gameDevelopFun->methodUtype = 54;
	pAccount_gameDevelopFun->aliasID = 25;
	pAccount_gameDevelopFun->args = Account_gameDevelopFun_args;

	pAccountModule->methods.Add(TEXT("gameDevelopFun"), pAccount_gameDevelopFun); 
	pAccountModule->useMethodDescrAlias = true;
	pAccountModule->idmethods.Add((uint16)pAccount_gameDevelopFun->aliasID, pAccount_gameDevelopFun);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(gameDevelopFun / 54).");

	TArray<DATATYPE_BASE*> Account_reqAddFriend_args;
	Account_reqAddFriend_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqAddFriend = new Method();
	pAccount_reqAddFriend->name = TEXT("reqAddFriend");
	pAccount_reqAddFriend->methodUtype = 20;
	pAccount_reqAddFriend->aliasID = -1;
	pAccount_reqAddFriend->args = Account_reqAddFriend_args;

	pAccountModule->methods.Add(TEXT("reqAddFriend"), pAccount_reqAddFriend); 
	pAccountModule->base_methods.Add(TEXT("reqAddFriend"), pAccount_reqAddFriend);

	pAccountModule->idbase_methods.Add(pAccount_reqAddFriend->methodUtype, pAccount_reqAddFriend);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAddFriend / 20).");

	TArray<DATATYPE_BASE*> Account_reqAllRuneDataFromServer_args;

	Method* pAccount_reqAllRuneDataFromServer = new Method();
	pAccount_reqAllRuneDataFromServer->name = TEXT("reqAllRuneDataFromServer");
	pAccount_reqAllRuneDataFromServer->methodUtype = 1;
	pAccount_reqAllRuneDataFromServer->aliasID = -1;
	pAccount_reqAllRuneDataFromServer->args = Account_reqAllRuneDataFromServer_args;

	pAccountModule->methods.Add(TEXT("reqAllRuneDataFromServer"), pAccount_reqAllRuneDataFromServer); 
	pAccountModule->base_methods.Add(TEXT("reqAllRuneDataFromServer"), pAccount_reqAllRuneDataFromServer);

	pAccountModule->idbase_methods.Add(pAccount_reqAllRuneDataFromServer->methodUtype, pAccount_reqAllRuneDataFromServer);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAllRuneDataFromServer / 1).");

	TArray<DATATYPE_BASE*> Account_reqAnswerAddFriendRequest_args;
	Account_reqAnswerAddFriendRequest_args.Add(EntityDef::id2datatypes[2]);
	Account_reqAnswerAddFriendRequest_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_reqAnswerAddFriendRequest = new Method();
	pAccount_reqAnswerAddFriendRequest->name = TEXT("reqAnswerAddFriendRequest");
	pAccount_reqAnswerAddFriendRequest->methodUtype = 21;
	pAccount_reqAnswerAddFriendRequest->aliasID = -1;
	pAccount_reqAnswerAddFriendRequest->args = Account_reqAnswerAddFriendRequest_args;

	pAccountModule->methods.Add(TEXT("reqAnswerAddFriendRequest"), pAccount_reqAnswerAddFriendRequest); 
	pAccountModule->base_methods.Add(TEXT("reqAnswerAddFriendRequest"), pAccount_reqAnswerAddFriendRequest);

	pAccountModule->idbase_methods.Add(pAccount_reqAnswerAddFriendRequest->methodUtype, pAccount_reqAnswerAddFriendRequest);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAnswerAddFriendRequest / 21).");

	TArray<DATATYPE_BASE*> Account_reqAnswerFriendMatch_args;
	Account_reqAnswerFriendMatch_args.Add(EntityDef::id2datatypes[2]);
	Account_reqAnswerFriendMatch_args.Add(EntityDef::id2datatypes[1]);
	Account_reqAnswerFriendMatch_args.Add(EntityDef::id2datatypes[1]);
	Account_reqAnswerFriendMatch_args.Add(EntityDef::id2datatypes[8]);

	Method* pAccount_reqAnswerFriendMatch = new Method();
	pAccount_reqAnswerFriendMatch->name = TEXT("reqAnswerFriendMatch");
	pAccount_reqAnswerFriendMatch->methodUtype = 15;
	pAccount_reqAnswerFriendMatch->aliasID = -1;
	pAccount_reqAnswerFriendMatch->args = Account_reqAnswerFriendMatch_args;

	pAccountModule->methods.Add(TEXT("reqAnswerFriendMatch"), pAccount_reqAnswerFriendMatch); 
	pAccountModule->base_methods.Add(TEXT("reqAnswerFriendMatch"), pAccount_reqAnswerFriendMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqAnswerFriendMatch->methodUtype, pAccount_reqAnswerFriendMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqAnswerFriendMatch / 15).");

	TArray<DATATYPE_BASE*> Account_reqBuy_args;
	Account_reqBuy_args.Add(EntityDef::id2datatypes[1]);
	Account_reqBuy_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_reqBuy = new Method();
	pAccount_reqBuy->name = TEXT("reqBuy");
	pAccount_reqBuy->methodUtype = 7;
	pAccount_reqBuy->aliasID = -1;
	pAccount_reqBuy->args = Account_reqBuy_args;

	pAccountModule->methods.Add(TEXT("reqBuy"), pAccount_reqBuy); 
	pAccountModule->base_methods.Add(TEXT("reqBuy"), pAccount_reqBuy);

	pAccountModule->idbase_methods.Add(pAccount_reqBuy->methodUtype, pAccount_reqBuy);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqBuy / 7).");

	TArray<DATATYPE_BASE*> Account_reqCancelMatch_args;

	Method* pAccount_reqCancelMatch = new Method();
	pAccount_reqCancelMatch->name = TEXT("reqCancelMatch");
	pAccount_reqCancelMatch->methodUtype = 11;
	pAccount_reqCancelMatch->aliasID = -1;
	pAccount_reqCancelMatch->args = Account_reqCancelMatch_args;

	pAccountModule->methods.Add(TEXT("reqCancelMatch"), pAccount_reqCancelMatch); 
	pAccountModule->base_methods.Add(TEXT("reqCancelMatch"), pAccount_reqCancelMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqCancelMatch->methodUtype, pAccount_reqCancelMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqCancelMatch / 11).");

	TArray<DATATYPE_BASE*> Account_reqChangeCurSelectCharacter_args;
	Account_reqChangeCurSelectCharacter_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqChangeCurSelectCharacter = new Method();
	pAccount_reqChangeCurSelectCharacter->name = TEXT("reqChangeCurSelectCharacter");
	pAccount_reqChangeCurSelectCharacter->methodUtype = 13;
	pAccount_reqChangeCurSelectCharacter->aliasID = -1;
	pAccount_reqChangeCurSelectCharacter->args = Account_reqChangeCurSelectCharacter_args;

	pAccountModule->methods.Add(TEXT("reqChangeCurSelectCharacter"), pAccount_reqChangeCurSelectCharacter); 
	pAccountModule->base_methods.Add(TEXT("reqChangeCurSelectCharacter"), pAccount_reqChangeCurSelectCharacter);

	pAccountModule->idbase_methods.Add(pAccount_reqChangeCurSelectCharacter->methodUtype, pAccount_reqChangeCurSelectCharacter);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqChangeCurSelectCharacter / 13).");

	TArray<DATATYPE_BASE*> Account_reqDeleteFriend_args;
	Account_reqDeleteFriend_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqDeleteFriend = new Method();
	pAccount_reqDeleteFriend->name = TEXT("reqDeleteFriend");
	pAccount_reqDeleteFriend->methodUtype = 23;
	pAccount_reqDeleteFriend->aliasID = -1;
	pAccount_reqDeleteFriend->args = Account_reqDeleteFriend_args;

	pAccountModule->methods.Add(TEXT("reqDeleteFriend"), pAccount_reqDeleteFriend); 
	pAccountModule->base_methods.Add(TEXT("reqDeleteFriend"), pAccount_reqDeleteFriend);

	pAccountModule->idbase_methods.Add(pAccount_reqDeleteFriend->methodUtype, pAccount_reqDeleteFriend);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqDeleteFriend / 23).");

	TArray<DATATYPE_BASE*> Account_reqEnsureEnterRoom_args;

	Method* pAccount_reqEnsureEnterRoom = new Method();
	pAccount_reqEnsureEnterRoom->name = TEXT("reqEnsureEnterRoom");
	pAccount_reqEnsureEnterRoom->methodUtype = 17;
	pAccount_reqEnsureEnterRoom->aliasID = -1;
	pAccount_reqEnsureEnterRoom->args = Account_reqEnsureEnterRoom_args;

	pAccountModule->methods.Add(TEXT("reqEnsureEnterRoom"), pAccount_reqEnsureEnterRoom); 
	pAccountModule->base_methods.Add(TEXT("reqEnsureEnterRoom"), pAccount_reqEnsureEnterRoom);

	pAccountModule->idbase_methods.Add(pAccount_reqEnsureEnterRoom->methodUtype, pAccount_reqEnsureEnterRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqEnsureEnterRoom / 17).");

	TArray<DATATYPE_BASE*> Account_reqFriendMatch_args;
	Account_reqFriendMatch_args.Add(EntityDef::id2datatypes[68]);
	Account_reqFriendMatch_args.Add(EntityDef::id2datatypes[26]);
	Account_reqFriendMatch_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqFriendMatch = new Method();
	pAccount_reqFriendMatch->name = TEXT("reqFriendMatch");
	pAccount_reqFriendMatch->methodUtype = 14;
	pAccount_reqFriendMatch->aliasID = -1;
	pAccount_reqFriendMatch->args = Account_reqFriendMatch_args;

	pAccountModule->methods.Add(TEXT("reqFriendMatch"), pAccount_reqFriendMatch); 
	pAccountModule->base_methods.Add(TEXT("reqFriendMatch"), pAccount_reqFriendMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqFriendMatch->methodUtype, pAccount_reqFriendMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqFriendMatch / 14).");

	TArray<DATATYPE_BASE*> Account_reqLoadLevelModelList_args;

	Method* pAccount_reqLoadLevelModelList = new Method();
	pAccount_reqLoadLevelModelList->name = TEXT("reqLoadLevelModelList");
	pAccount_reqLoadLevelModelList->methodUtype = 4;
	pAccount_reqLoadLevelModelList->aliasID = -1;
	pAccount_reqLoadLevelModelList->args = Account_reqLoadLevelModelList_args;

	pAccountModule->methods.Add(TEXT("reqLoadLevelModelList"), pAccount_reqLoadLevelModelList); 
	pAccountModule->base_methods.Add(TEXT("reqLoadLevelModelList"), pAccount_reqLoadLevelModelList);

	pAccountModule->idbase_methods.Add(pAccount_reqLoadLevelModelList->methodUtype, pAccount_reqLoadLevelModelList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqLoadLevelModelList / 4).");

	TArray<DATATYPE_BASE*> Account_reqMallInfoList_args;

	Method* pAccount_reqMallInfoList = new Method();
	pAccount_reqMallInfoList->name = TEXT("reqMallInfoList");
	pAccount_reqMallInfoList->methodUtype = 6;
	pAccount_reqMallInfoList->aliasID = -1;
	pAccount_reqMallInfoList->args = Account_reqMallInfoList_args;

	pAccountModule->methods.Add(TEXT("reqMallInfoList"), pAccount_reqMallInfoList); 
	pAccountModule->base_methods.Add(TEXT("reqMallInfoList"), pAccount_reqMallInfoList);

	pAccountModule->idbase_methods.Add(pAccount_reqMallInfoList->methodUtype, pAccount_reqMallInfoList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqMallInfoList / 6).");

	TArray<DATATYPE_BASE*> Account_reqNotifyRecieveAddFriendRequest_args;
	Account_reqNotifyRecieveAddFriendRequest_args.Add(EntityDef::id2datatypes[5]);

	Method* pAccount_reqNotifyRecieveAddFriendRequest = new Method();
	pAccount_reqNotifyRecieveAddFriendRequest->name = TEXT("reqNotifyRecieveAddFriendRequest");
	pAccount_reqNotifyRecieveAddFriendRequest->methodUtype = 22;
	pAccount_reqNotifyRecieveAddFriendRequest->aliasID = -1;
	pAccount_reqNotifyRecieveAddFriendRequest->args = Account_reqNotifyRecieveAddFriendRequest_args;

	pAccountModule->methods.Add(TEXT("reqNotifyRecieveAddFriendRequest"), pAccount_reqNotifyRecieveAddFriendRequest); 
	pAccountModule->base_methods.Add(TEXT("reqNotifyRecieveAddFriendRequest"), pAccount_reqNotifyRecieveAddFriendRequest);

	pAccountModule->idbase_methods.Add(pAccount_reqNotifyRecieveAddFriendRequest->methodUtype, pAccount_reqNotifyRecieveAddFriendRequest);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqNotifyRecieveAddFriendRequest / 22).");

	TArray<DATATYPE_BASE*> Account_reqOneOneMatch_args;
	Account_reqOneOneMatch_args.Add(EntityDef::id2datatypes[1]);
	Account_reqOneOneMatch_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqOneOneMatch = new Method();
	pAccount_reqOneOneMatch->name = TEXT("reqOneOneMatch");
	pAccount_reqOneOneMatch->methodUtype = 10;
	pAccount_reqOneOneMatch->aliasID = -1;
	pAccount_reqOneOneMatch->args = Account_reqOneOneMatch_args;

	pAccountModule->methods.Add(TEXT("reqOneOneMatch"), pAccount_reqOneOneMatch); 
	pAccountModule->base_methods.Add(TEXT("reqOneOneMatch"), pAccount_reqOneOneMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqOneOneMatch->methodUtype, pAccount_reqOneOneMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqOneOneMatch / 10).");

	TArray<DATATYPE_BASE*> Account_reqPlayerInfo_args;

	Method* pAccount_reqPlayerInfo = new Method();
	pAccount_reqPlayerInfo->name = TEXT("reqPlayerInfo");
	pAccount_reqPlayerInfo->methodUtype = 3;
	pAccount_reqPlayerInfo->aliasID = -1;
	pAccount_reqPlayerInfo->args = Account_reqPlayerInfo_args;

	pAccountModule->methods.Add(TEXT("reqPlayerInfo"), pAccount_reqPlayerInfo); 
	pAccountModule->base_methods.Add(TEXT("reqPlayerInfo"), pAccount_reqPlayerInfo);

	pAccountModule->idbase_methods.Add(pAccount_reqPlayerInfo->methodUtype, pAccount_reqPlayerInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqPlayerInfo / 3).");

	TArray<DATATYPE_BASE*> Account_reqPlayerTagInfoList_args;
	Account_reqPlayerTagInfoList_args.Add(EntityDef::id2datatypes[26]);

	Method* pAccount_reqPlayerTagInfoList = new Method();
	pAccount_reqPlayerTagInfoList->name = TEXT("reqPlayerTagInfoList");
	pAccount_reqPlayerTagInfoList->methodUtype = 19;
	pAccount_reqPlayerTagInfoList->aliasID = -1;
	pAccount_reqPlayerTagInfoList->args = Account_reqPlayerTagInfoList_args;

	pAccountModule->methods.Add(TEXT("reqPlayerTagInfoList"), pAccount_reqPlayerTagInfoList); 
	pAccountModule->base_methods.Add(TEXT("reqPlayerTagInfoList"), pAccount_reqPlayerTagInfoList);

	pAccountModule->idbase_methods.Add(pAccount_reqPlayerTagInfoList->methodUtype, pAccount_reqPlayerTagInfoList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqPlayerTagInfoList / 19).");

	TArray<DATATYPE_BASE*> Account_reqRankList_args;

	Method* pAccount_reqRankList = new Method();
	pAccount_reqRankList->name = TEXT("reqRankList");
	pAccount_reqRankList->methodUtype = 5;
	pAccount_reqRankList->aliasID = -1;
	pAccount_reqRankList->args = Account_reqRankList_args;

	pAccountModule->methods.Add(TEXT("reqRankList"), pAccount_reqRankList); 
	pAccountModule->base_methods.Add(TEXT("reqRankList"), pAccount_reqRankList);

	pAccountModule->idbase_methods.Add(pAccount_reqRankList->methodUtype, pAccount_reqRankList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqRankList / 5).");

	TArray<DATATYPE_BASE*> Account_reqRelogonInfo_args;

	Method* pAccount_reqRelogonInfo = new Method();
	pAccount_reqRelogonInfo->name = TEXT("reqRelogonInfo");
	pAccount_reqRelogonInfo->methodUtype = 18;
	pAccount_reqRelogonInfo->aliasID = -1;
	pAccount_reqRelogonInfo->args = Account_reqRelogonInfo_args;

	pAccountModule->methods.Add(TEXT("reqRelogonInfo"), pAccount_reqRelogonInfo); 
	pAccountModule->base_methods.Add(TEXT("reqRelogonInfo"), pAccount_reqRelogonInfo);

	pAccountModule->idbase_methods.Add(pAccount_reqRelogonInfo->methodUtype, pAccount_reqRelogonInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqRelogonInfo / 18).");

	TArray<DATATYPE_BASE*> Account_reqSendMessageToFriend_args;
	Account_reqSendMessageToFriend_args.Add(EntityDef::id2datatypes[1]);
	Account_reqSendMessageToFriend_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqSendMessageToFriend = new Method();
	pAccount_reqSendMessageToFriend->name = TEXT("reqSendMessageToFriend");
	pAccount_reqSendMessageToFriend->methodUtype = 16;
	pAccount_reqSendMessageToFriend->aliasID = -1;
	pAccount_reqSendMessageToFriend->args = Account_reqSendMessageToFriend_args;

	pAccountModule->methods.Add(TEXT("reqSendMessageToFriend"), pAccount_reqSendMessageToFriend); 
	pAccountModule->base_methods.Add(TEXT("reqSendMessageToFriend"), pAccount_reqSendMessageToFriend);

	pAccountModule->idbase_methods.Add(pAccount_reqSendMessageToFriend->methodUtype, pAccount_reqSendMessageToFriend);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqSendMessageToFriend / 16).");

	TArray<DATATYPE_BASE*> Account_reqSetRuneConfigDataToServer_args;
	Account_reqSetRuneConfigDataToServer_args.Add(EntityDef::id2datatypes[1]);
	Account_reqSetRuneConfigDataToServer_args.Add(EntityDef::id2datatypes[2]);
	Account_reqSetRuneConfigDataToServer_args.Add(EntityDef::id2datatypes[2]);
	Account_reqSetRuneConfigDataToServer_args.Add(EntityDef::id2datatypes[2]);
	Account_reqSetRuneConfigDataToServer_args.Add(EntityDef::id2datatypes[2]);

	Method* pAccount_reqSetRuneConfigDataToServer = new Method();
	pAccount_reqSetRuneConfigDataToServer->name = TEXT("reqSetRuneConfigDataToServer");
	pAccount_reqSetRuneConfigDataToServer->methodUtype = 2;
	pAccount_reqSetRuneConfigDataToServer->aliasID = -1;
	pAccount_reqSetRuneConfigDataToServer->args = Account_reqSetRuneConfigDataToServer_args;

	pAccountModule->methods.Add(TEXT("reqSetRuneConfigDataToServer"), pAccount_reqSetRuneConfigDataToServer); 
	pAccountModule->base_methods.Add(TEXT("reqSetRuneConfigDataToServer"), pAccount_reqSetRuneConfigDataToServer);

	pAccountModule->idbase_methods.Add(pAccount_reqSetRuneConfigDataToServer->methodUtype, pAccount_reqSetRuneConfigDataToServer);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqSetRuneConfigDataToServer / 2).");

	TArray<DATATYPE_BASE*> Account_reqSimpleSingleMatch_args;
	Account_reqSimpleSingleMatch_args.Add(EntityDef::id2datatypes[1]);
	Account_reqSimpleSingleMatch_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqSimpleSingleMatch = new Method();
	pAccount_reqSimpleSingleMatch->name = TEXT("reqSimpleSingleMatch");
	pAccount_reqSimpleSingleMatch->methodUtype = 8;
	pAccount_reqSimpleSingleMatch->aliasID = -1;
	pAccount_reqSimpleSingleMatch->args = Account_reqSimpleSingleMatch_args;

	pAccountModule->methods.Add(TEXT("reqSimpleSingleMatch"), pAccount_reqSimpleSingleMatch); 
	pAccountModule->base_methods.Add(TEXT("reqSimpleSingleMatch"), pAccount_reqSimpleSingleMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqSimpleSingleMatch->methodUtype, pAccount_reqSimpleSingleMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqSimpleSingleMatch / 8).");

	TArray<DATATYPE_BASE*> Account_reqSingleMatch_args;
	Account_reqSingleMatch_args.Add(EntityDef::id2datatypes[1]);
	Account_reqSingleMatch_args.Add(EntityDef::id2datatypes[1]);

	Method* pAccount_reqSingleMatch = new Method();
	pAccount_reqSingleMatch->name = TEXT("reqSingleMatch");
	pAccount_reqSingleMatch->methodUtype = 9;
	pAccount_reqSingleMatch->aliasID = -1;
	pAccount_reqSingleMatch->args = Account_reqSingleMatch_args;

	pAccountModule->methods.Add(TEXT("reqSingleMatch"), pAccount_reqSingleMatch); 
	pAccountModule->base_methods.Add(TEXT("reqSingleMatch"), pAccount_reqSingleMatch);

	pAccountModule->idbase_methods.Add(pAccount_reqSingleMatch->methodUtype, pAccount_reqSingleMatch);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Account), method(reqSingleMatch / 9).");

	ScriptModule* pCommunicateStationModule = new ScriptModule("CommunicateStation", 2);
	EntityDef::moduledefs.Add(TEXT("CommunicateStation"), pCommunicateStationModule);
	EntityDef::idmoduledefs.Add(2, pCommunicateStationModule);

	Property* pCommunicateStation_position = new Property();
	pCommunicateStation_position->name = TEXT("position");
	pCommunicateStation_position->properUtype = 40000;
	pCommunicateStation_position->properFlags = 4;
	pCommunicateStation_position->aliasID = 0;
	KBVar* pCommunicateStation_position_defval = new KBVar(FVector());
	pCommunicateStation_position->pDefaultVal = pCommunicateStation_position_defval;
	pCommunicateStationModule->propertys.Add(TEXT("position"), pCommunicateStation_position); 

	pCommunicateStationModule->usePropertyDescrAlias = true;
	pCommunicateStationModule->idpropertys.Add((uint16)pCommunicateStation_position->aliasID, pCommunicateStation_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), property(position / 40000).");

	Property* pCommunicateStation_direction = new Property();
	pCommunicateStation_direction->name = TEXT("direction");
	pCommunicateStation_direction->properUtype = 40001;
	pCommunicateStation_direction->properFlags = 4;
	pCommunicateStation_direction->aliasID = 1;
	KBVar* pCommunicateStation_direction_defval = new KBVar(FVector());
	pCommunicateStation_direction->pDefaultVal = pCommunicateStation_direction_defval;
	pCommunicateStationModule->propertys.Add(TEXT("direction"), pCommunicateStation_direction); 

	pCommunicateStationModule->usePropertyDescrAlias = true;
	pCommunicateStationModule->idpropertys.Add((uint16)pCommunicateStation_direction->aliasID, pCommunicateStation_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), property(direction / 40001).");

	Property* pCommunicateStation_spaceID = new Property();
	pCommunicateStation_spaceID->name = TEXT("spaceID");
	pCommunicateStation_spaceID->properUtype = 40002;
	pCommunicateStation_spaceID->properFlags = 16;
	pCommunicateStation_spaceID->aliasID = 2;
	KBVar* pCommunicateStation_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pCommunicateStation_spaceID->pDefaultVal = pCommunicateStation_spaceID_defval;
	pCommunicateStationModule->propertys.Add(TEXT("spaceID"), pCommunicateStation_spaceID); 

	pCommunicateStationModule->usePropertyDescrAlias = true;
	pCommunicateStationModule->idpropertys.Add((uint16)pCommunicateStation_spaceID->aliasID, pCommunicateStation_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), property(spaceID / 40002).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchActorCorrectInfo_args;
	CommunicateStation_dispatchActorCorrectInfo_args.Add(EntityDef::id2datatypes[144]);

	Method* pCommunicateStation_dispatchActorCorrectInfo = new Method();
	pCommunicateStation_dispatchActorCorrectInfo->name = TEXT("dispatchActorCorrectInfo");
	pCommunicateStation_dispatchActorCorrectInfo->methodUtype = 123;
	pCommunicateStation_dispatchActorCorrectInfo->aliasID = 0;
	pCommunicateStation_dispatchActorCorrectInfo->args = CommunicateStation_dispatchActorCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchActorCorrectInfo"), pCommunicateStation_dispatchActorCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchActorCorrectInfo->aliasID, pCommunicateStation_dispatchActorCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchActorCorrectInfo / 123).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchBattleEnd_args;
	CommunicateStation_dispatchBattleEnd_args.Add(EntityDef::id2datatypes[24]);
	CommunicateStation_dispatchBattleEnd_args.Add(EntityDef::id2datatypes[232]);

	Method* pCommunicateStation_dispatchBattleEnd = new Method();
	pCommunicateStation_dispatchBattleEnd->name = TEXT("dispatchBattleEnd");
	pCommunicateStation_dispatchBattleEnd->methodUtype = 130;
	pCommunicateStation_dispatchBattleEnd->aliasID = 1;
	pCommunicateStation_dispatchBattleEnd->args = CommunicateStation_dispatchBattleEnd_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchBattleEnd"), pCommunicateStation_dispatchBattleEnd); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchBattleEnd->aliasID, pCommunicateStation_dispatchBattleEnd);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchBattleEnd / 130).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchBattleStart_args;
	CommunicateStation_dispatchBattleStart_args.Add(EntityDef::id2datatypes[8]);

	Method* pCommunicateStation_dispatchBattleStart = new Method();
	pCommunicateStation_dispatchBattleStart->name = TEXT("dispatchBattleStart");
	pCommunicateStation_dispatchBattleStart->methodUtype = 133;
	pCommunicateStation_dispatchBattleStart->aliasID = 2;
	pCommunicateStation_dispatchBattleStart->args = CommunicateStation_dispatchBattleStart_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchBattleStart"), pCommunicateStation_dispatchBattleStart); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchBattleStart->aliasID, pCommunicateStation_dispatchBattleStart);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchBattleStart / 133).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchCalPrizeResult_args;
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchCalPrizeResult_args.Add(EntityDef::id2datatypes[26]);

	Method* pCommunicateStation_dispatchCalPrizeResult = new Method();
	pCommunicateStation_dispatchCalPrizeResult->name = TEXT("dispatchCalPrizeResult");
	pCommunicateStation_dispatchCalPrizeResult->methodUtype = 134;
	pCommunicateStation_dispatchCalPrizeResult->aliasID = 3;
	pCommunicateStation_dispatchCalPrizeResult->args = CommunicateStation_dispatchCalPrizeResult_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchCalPrizeResult"), pCommunicateStation_dispatchCalPrizeResult); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchCalPrizeResult->aliasID, pCommunicateStation_dispatchCalPrizeResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchCalPrizeResult / 134).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchCharacterCorrectInfo_args;
	CommunicateStation_dispatchCharacterCorrectInfo_args.Add(EntityDef::id2datatypes[106]);

	Method* pCommunicateStation_dispatchCharacterCorrectInfo = new Method();
	pCommunicateStation_dispatchCharacterCorrectInfo->name = TEXT("dispatchCharacterCorrectInfo");
	pCommunicateStation_dispatchCharacterCorrectInfo->methodUtype = 119;
	pCommunicateStation_dispatchCharacterCorrectInfo->aliasID = 4;
	pCommunicateStation_dispatchCharacterCorrectInfo->args = CommunicateStation_dispatchCharacterCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchCharacterCorrectInfo"), pCommunicateStation_dispatchCharacterCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchCharacterCorrectInfo->aliasID, pCommunicateStation_dispatchCharacterCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchCharacterCorrectInfo / 119).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchEndCorrectInfo_args;

	Method* pCommunicateStation_dispatchEndCorrectInfo = new Method();
	pCommunicateStation_dispatchEndCorrectInfo->name = TEXT("dispatchEndCorrectInfo");
	pCommunicateStation_dispatchEndCorrectInfo->methodUtype = 127;
	pCommunicateStation_dispatchEndCorrectInfo->aliasID = 5;
	pCommunicateStation_dispatchEndCorrectInfo->args = CommunicateStation_dispatchEndCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchEndCorrectInfo"), pCommunicateStation_dispatchEndCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchEndCorrectInfo->aliasID, pCommunicateStation_dispatchEndCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchEndCorrectInfo / 127).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchGeneralCorrectInfo_args;
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[1]);
	CommunicateStation_dispatchGeneralCorrectInfo_args.Add(EntityDef::id2datatypes[8]);

	Method* pCommunicateStation_dispatchGeneralCorrectInfo = new Method();
	pCommunicateStation_dispatchGeneralCorrectInfo->name = TEXT("dispatchGeneralCorrectInfo");
	pCommunicateStation_dispatchGeneralCorrectInfo->methodUtype = 126;
	pCommunicateStation_dispatchGeneralCorrectInfo->aliasID = 6;
	pCommunicateStation_dispatchGeneralCorrectInfo->args = CommunicateStation_dispatchGeneralCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchGeneralCorrectInfo"), pCommunicateStation_dispatchGeneralCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchGeneralCorrectInfo->aliasID, pCommunicateStation_dispatchGeneralCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchGeneralCorrectInfo / 126).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchGroupCorrectInfo_args;
	CommunicateStation_dispatchGroupCorrectInfo_args.Add(EntityDef::id2datatypes[159]);

	Method* pCommunicateStation_dispatchGroupCorrectInfo = new Method();
	pCommunicateStation_dispatchGroupCorrectInfo->name = TEXT("dispatchGroupCorrectInfo");
	pCommunicateStation_dispatchGroupCorrectInfo->methodUtype = 125;
	pCommunicateStation_dispatchGroupCorrectInfo->aliasID = 7;
	pCommunicateStation_dispatchGroupCorrectInfo->args = CommunicateStation_dispatchGroupCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchGroupCorrectInfo"), pCommunicateStation_dispatchGroupCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchGroupCorrectInfo->aliasID, pCommunicateStation_dispatchGroupCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchGroupCorrectInfo / 125).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchLevelInfo_args;
	CommunicateStation_dispatchLevelInfo_args.Add(EntityDef::id2datatypes[190]);
	CommunicateStation_dispatchLevelInfo_args.Add(EntityDef::id2datatypes[201]);
	CommunicateStation_dispatchLevelInfo_args.Add(EntityDef::id2datatypes[207]);
	CommunicateStation_dispatchLevelInfo_args.Add(EntityDef::id2datatypes[1]);
	CommunicateStation_dispatchLevelInfo_args.Add(EntityDef::id2datatypes[192]);

	Method* pCommunicateStation_dispatchLevelInfo = new Method();
	pCommunicateStation_dispatchLevelInfo->name = TEXT("dispatchLevelInfo");
	pCommunicateStation_dispatchLevelInfo->methodUtype = 115;
	pCommunicateStation_dispatchLevelInfo->aliasID = 8;
	pCommunicateStation_dispatchLevelInfo->args = CommunicateStation_dispatchLevelInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchLevelInfo"), pCommunicateStation_dispatchLevelInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchLevelInfo->aliasID, pCommunicateStation_dispatchLevelInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchLevelInfo / 115).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchLineCorrectInfo_args;
	CommunicateStation_dispatchLineCorrectInfo_args.Add(EntityDef::id2datatypes[111]);

	Method* pCommunicateStation_dispatchLineCorrectInfo = new Method();
	pCommunicateStation_dispatchLineCorrectInfo->name = TEXT("dispatchLineCorrectInfo");
	pCommunicateStation_dispatchLineCorrectInfo->methodUtype = 121;
	pCommunicateStation_dispatchLineCorrectInfo->aliasID = 9;
	pCommunicateStation_dispatchLineCorrectInfo->args = CommunicateStation_dispatchLineCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchLineCorrectInfo"), pCommunicateStation_dispatchLineCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchLineCorrectInfo->aliasID, pCommunicateStation_dispatchLineCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchLineCorrectInfo / 121).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchLogicFrame_args;
	CommunicateStation_dispatchLogicFrame_args.Add(EntityDef::id2datatypes[175]);

	Method* pCommunicateStation_dispatchLogicFrame = new Method();
	pCommunicateStation_dispatchLogicFrame->name = TEXT("dispatchLogicFrame");
	pCommunicateStation_dispatchLogicFrame->methodUtype = 117;
	pCommunicateStation_dispatchLogicFrame->aliasID = 10;
	pCommunicateStation_dispatchLogicFrame->args = CommunicateStation_dispatchLogicFrame_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchLogicFrame"), pCommunicateStation_dispatchLogicFrame); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchLogicFrame->aliasID, pCommunicateStation_dispatchLogicFrame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchLogicFrame / 117).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchLostRoundInfo_args;
	CommunicateStation_dispatchLostRoundInfo_args.Add(EntityDef::id2datatypes[227]);

	Method* pCommunicateStation_dispatchLostRoundInfo = new Method();
	pCommunicateStation_dispatchLostRoundInfo->name = TEXT("dispatchLostRoundInfo");
	pCommunicateStation_dispatchLostRoundInfo->methodUtype = 135;
	pCommunicateStation_dispatchLostRoundInfo->aliasID = 11;
	pCommunicateStation_dispatchLostRoundInfo->args = CommunicateStation_dispatchLostRoundInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchLostRoundInfo"), pCommunicateStation_dispatchLostRoundInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchLostRoundInfo->aliasID, pCommunicateStation_dispatchLostRoundInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchLostRoundInfo / 135).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchMainMachine_args;
	CommunicateStation_dispatchMainMachine_args.Add(EntityDef::id2datatypes[2]);

	Method* pCommunicateStation_dispatchMainMachine = new Method();
	pCommunicateStation_dispatchMainMachine->name = TEXT("dispatchMainMachine");
	pCommunicateStation_dispatchMainMachine->methodUtype = 116;
	pCommunicateStation_dispatchMainMachine->aliasID = 12;
	pCommunicateStation_dispatchMainMachine->args = CommunicateStation_dispatchMainMachine_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchMainMachine"), pCommunicateStation_dispatchMainMachine); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchMainMachine->aliasID, pCommunicateStation_dispatchMainMachine);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchMainMachine / 116).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchMakeUpFrames_args;
	CommunicateStation_dispatchMakeUpFrames_args.Add(EntityDef::id2datatypes[178]);

	Method* pCommunicateStation_dispatchMakeUpFrames = new Method();
	pCommunicateStation_dispatchMakeUpFrames->name = TEXT("dispatchMakeUpFrames");
	pCommunicateStation_dispatchMakeUpFrames->methodUtype = 118;
	pCommunicateStation_dispatchMakeUpFrames->aliasID = 13;
	pCommunicateStation_dispatchMakeUpFrames->args = CommunicateStation_dispatchMakeUpFrames_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchMakeUpFrames"), pCommunicateStation_dispatchMakeUpFrames); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchMakeUpFrames->aliasID, pCommunicateStation_dispatchMakeUpFrames);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchMakeUpFrames / 118).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchNextRound_args;
	CommunicateStation_dispatchNextRound_args.Add(EntityDef::id2datatypes[6]);
	CommunicateStation_dispatchNextRound_args.Add(EntityDef::id2datatypes[24]);

	Method* pCommunicateStation_dispatchNextRound = new Method();
	pCommunicateStation_dispatchNextRound->name = TEXT("dispatchNextRound");
	pCommunicateStation_dispatchNextRound->methodUtype = 129;
	pCommunicateStation_dispatchNextRound->aliasID = 14;
	pCommunicateStation_dispatchNextRound->args = CommunicateStation_dispatchNextRound_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchNextRound"), pCommunicateStation_dispatchNextRound); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchNextRound->aliasID, pCommunicateStation_dispatchNextRound);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchNextRound / 129).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchPointCorrectInfo_args;
	CommunicateStation_dispatchPointCorrectInfo_args.Add(EntityDef::id2datatypes[132]);

	Method* pCommunicateStation_dispatchPointCorrectInfo = new Method();
	pCommunicateStation_dispatchPointCorrectInfo->name = TEXT("dispatchPointCorrectInfo");
	pCommunicateStation_dispatchPointCorrectInfo->methodUtype = 122;
	pCommunicateStation_dispatchPointCorrectInfo->aliasID = 15;
	pCommunicateStation_dispatchPointCorrectInfo->args = CommunicateStation_dispatchPointCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchPointCorrectInfo"), pCommunicateStation_dispatchPointCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchPointCorrectInfo->aliasID, pCommunicateStation_dispatchPointCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchPointCorrectInfo / 122).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchPolyCorrectInfo_args;
	CommunicateStation_dispatchPolyCorrectInfo_args.Add(EntityDef::id2datatypes[120]);

	Method* pCommunicateStation_dispatchPolyCorrectInfo = new Method();
	pCommunicateStation_dispatchPolyCorrectInfo->name = TEXT("dispatchPolyCorrectInfo");
	pCommunicateStation_dispatchPolyCorrectInfo->methodUtype = 120;
	pCommunicateStation_dispatchPolyCorrectInfo->aliasID = 16;
	pCommunicateStation_dispatchPolyCorrectInfo->args = CommunicateStation_dispatchPolyCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchPolyCorrectInfo"), pCommunicateStation_dispatchPolyCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchPolyCorrectInfo->aliasID, pCommunicateStation_dispatchPolyCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchPolyCorrectInfo / 120).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchReactionPairCorrectInfo_args;
	CommunicateStation_dispatchReactionPairCorrectInfo_args.Add(EntityDef::id2datatypes[157]);

	Method* pCommunicateStation_dispatchReactionPairCorrectInfo = new Method();
	pCommunicateStation_dispatchReactionPairCorrectInfo->name = TEXT("dispatchReactionPairCorrectInfo");
	pCommunicateStation_dispatchReactionPairCorrectInfo->methodUtype = 124;
	pCommunicateStation_dispatchReactionPairCorrectInfo->aliasID = 17;
	pCommunicateStation_dispatchReactionPairCorrectInfo->args = CommunicateStation_dispatchReactionPairCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchReactionPairCorrectInfo"), pCommunicateStation_dispatchReactionPairCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchReactionPairCorrectInfo->aliasID, pCommunicateStation_dispatchReactionPairCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchReactionPairCorrectInfo / 124).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchReadLevelResult_args;
	CommunicateStation_dispatchReadLevelResult_args.Add(EntityDef::id2datatypes[2]);

	Method* pCommunicateStation_dispatchReadLevelResult = new Method();
	pCommunicateStation_dispatchReadLevelResult->name = TEXT("dispatchReadLevelResult");
	pCommunicateStation_dispatchReadLevelResult->methodUtype = 114;
	pCommunicateStation_dispatchReadLevelResult->aliasID = 18;
	pCommunicateStation_dispatchReadLevelResult->args = CommunicateStation_dispatchReadLevelResult_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchReadLevelResult"), pCommunicateStation_dispatchReadLevelResult); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchReadLevelResult->aliasID, pCommunicateStation_dispatchReadLevelResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchReadLevelResult / 114).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchRelogonInfo_args;
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[1]);
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[239]);
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[232]);
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[6]);
	CommunicateStation_dispatchRelogonInfo_args.Add(EntityDef::id2datatypes[1]);

	Method* pCommunicateStation_dispatchRelogonInfo = new Method();
	pCommunicateStation_dispatchRelogonInfo->name = TEXT("dispatchRelogonInfo");
	pCommunicateStation_dispatchRelogonInfo->methodUtype = 131;
	pCommunicateStation_dispatchRelogonInfo->aliasID = 19;
	pCommunicateStation_dispatchRelogonInfo->args = CommunicateStation_dispatchRelogonInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchRelogonInfo"), pCommunicateStation_dispatchRelogonInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchRelogonInfo->aliasID, pCommunicateStation_dispatchRelogonInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchRelogonInfo / 131).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchRelogonPlayerInfo_args;
	CommunicateStation_dispatchRelogonPlayerInfo_args.Add(EntityDef::id2datatypes[59]);
	CommunicateStation_dispatchRelogonPlayerInfo_args.Add(EntityDef::id2datatypes[245]);

	Method* pCommunicateStation_dispatchRelogonPlayerInfo = new Method();
	pCommunicateStation_dispatchRelogonPlayerInfo->name = TEXT("dispatchRelogonPlayerInfo");
	pCommunicateStation_dispatchRelogonPlayerInfo->methodUtype = 132;
	pCommunicateStation_dispatchRelogonPlayerInfo->aliasID = 20;
	pCommunicateStation_dispatchRelogonPlayerInfo->args = CommunicateStation_dispatchRelogonPlayerInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchRelogonPlayerInfo"), pCommunicateStation_dispatchRelogonPlayerInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchRelogonPlayerInfo->aliasID, pCommunicateStation_dispatchRelogonPlayerInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchRelogonPlayerInfo / 132).");

	TArray<DATATYPE_BASE*> CommunicateStation_dispatchStopUploadCorrectInfo_args;

	Method* pCommunicateStation_dispatchStopUploadCorrectInfo = new Method();
	pCommunicateStation_dispatchStopUploadCorrectInfo->name = TEXT("dispatchStopUploadCorrectInfo");
	pCommunicateStation_dispatchStopUploadCorrectInfo->methodUtype = 128;
	pCommunicateStation_dispatchStopUploadCorrectInfo->aliasID = 21;
	pCommunicateStation_dispatchStopUploadCorrectInfo->args = CommunicateStation_dispatchStopUploadCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("dispatchStopUploadCorrectInfo"), pCommunicateStation_dispatchStopUploadCorrectInfo); 
	pCommunicateStationModule->useMethodDescrAlias = true;
	pCommunicateStationModule->idmethods.Add((uint16)pCommunicateStation_dispatchStopUploadCorrectInfo->aliasID, pCommunicateStation_dispatchStopUploadCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(dispatchStopUploadCorrectInfo / 128).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqExitBattle_args;

	Method* pCommunicateStation_reqExitBattle = new Method();
	pCommunicateStation_reqExitBattle->name = TEXT("reqExitBattle");
	pCommunicateStation_reqExitBattle->methodUtype = 111;
	pCommunicateStation_reqExitBattle->aliasID = -1;
	pCommunicateStation_reqExitBattle->args = CommunicateStation_reqExitBattle_args;

	pCommunicateStationModule->methods.Add(TEXT("reqExitBattle"), pCommunicateStation_reqExitBattle); 
	pCommunicateStationModule->base_methods.Add(TEXT("reqExitBattle"), pCommunicateStation_reqExitBattle);

	pCommunicateStationModule->idbase_methods.Add(pCommunicateStation_reqExitBattle->methodUtype, pCommunicateStation_reqExitBattle);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqExitBattle / 111).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqLevelInfos_args;
	CommunicateStation_reqLevelInfos_args.Add(EntityDef::id2datatypes[1]);
	CommunicateStation_reqLevelInfos_args.Add(EntityDef::id2datatypes[1]);

	Method* pCommunicateStation_reqLevelInfos = new Method();
	pCommunicateStation_reqLevelInfos->name = TEXT("reqLevelInfos");
	pCommunicateStation_reqLevelInfos->methodUtype = 107;
	pCommunicateStation_reqLevelInfos->aliasID = -1;
	pCommunicateStation_reqLevelInfos->args = CommunicateStation_reqLevelInfos_args;

	pCommunicateStationModule->methods.Add(TEXT("reqLevelInfos"), pCommunicateStation_reqLevelInfos); 
	pCommunicateStationModule->base_methods.Add(TEXT("reqLevelInfos"), pCommunicateStation_reqLevelInfos);

	pCommunicateStationModule->idbase_methods.Add(pCommunicateStation_reqLevelInfos->methodUtype, pCommunicateStation_reqLevelInfos);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqLevelInfos / 107).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqRelogonInfo_args;

	Method* pCommunicateStation_reqRelogonInfo = new Method();
	pCommunicateStation_reqRelogonInfo->name = TEXT("reqRelogonInfo");
	pCommunicateStation_reqRelogonInfo->methodUtype = 108;
	pCommunicateStation_reqRelogonInfo->aliasID = -1;
	pCommunicateStation_reqRelogonInfo->args = CommunicateStation_reqRelogonInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqRelogonInfo"), pCommunicateStation_reqRelogonInfo); 
	pCommunicateStationModule->base_methods.Add(TEXT("reqRelogonInfo"), pCommunicateStation_reqRelogonInfo);

	pCommunicateStationModule->idbase_methods.Add(pCommunicateStation_reqRelogonInfo->methodUtype, pCommunicateStation_reqRelogonInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqRelogonInfo / 108).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqTellLeaveWorld_args;

	Method* pCommunicateStation_reqTellLeaveWorld = new Method();
	pCommunicateStation_reqTellLeaveWorld->name = TEXT("reqTellLeaveWorld");
	pCommunicateStation_reqTellLeaveWorld->methodUtype = 112;
	pCommunicateStation_reqTellLeaveWorld->aliasID = -1;
	pCommunicateStation_reqTellLeaveWorld->args = CommunicateStation_reqTellLeaveWorld_args;

	pCommunicateStationModule->methods.Add(TEXT("reqTellLeaveWorld"), pCommunicateStation_reqTellLeaveWorld); 
	pCommunicateStationModule->base_methods.Add(TEXT("reqTellLeaveWorld"), pCommunicateStation_reqTellLeaveWorld);

	pCommunicateStationModule->idbase_methods.Add(pCommunicateStation_reqTellLeaveWorld->methodUtype, pCommunicateStation_reqTellLeaveWorld);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqTellLeaveWorld / 112).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqCorrectInfo_args;

	Method* pCommunicateStation_reqCorrectInfo = new Method();
	pCommunicateStation_reqCorrectInfo->name = TEXT("reqCorrectInfo");
	pCommunicateStation_reqCorrectInfo->methodUtype = 77;
	pCommunicateStation_reqCorrectInfo->aliasID = -1;
	pCommunicateStation_reqCorrectInfo->args = CommunicateStation_reqCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqCorrectInfo"), pCommunicateStation_reqCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqCorrectInfo"), pCommunicateStation_reqCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqCorrectInfo->methodUtype, pCommunicateStation_reqCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqCorrectInfo / 77).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqLostRoundResult_args;
	CommunicateStation_reqLostRoundResult_args.Add(EntityDef::id2datatypes[24]);

	Method* pCommunicateStation_reqLostRoundResult = new Method();
	pCommunicateStation_reqLostRoundResult->name = TEXT("reqLostRoundResult");
	pCommunicateStation_reqLostRoundResult->methodUtype = 89;
	pCommunicateStation_reqLostRoundResult->aliasID = -1;
	pCommunicateStation_reqLostRoundResult->args = CommunicateStation_reqLostRoundResult_args;

	pCommunicateStationModule->methods.Add(TEXT("reqLostRoundResult"), pCommunicateStation_reqLostRoundResult); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqLostRoundResult"), pCommunicateStation_reqLostRoundResult);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqLostRoundResult->methodUtype, pCommunicateStation_reqLostRoundResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqLostRoundResult / 89).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqMakeUpFrames_args;
	CommunicateStation_reqMakeUpFrames_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqMakeUpFrames_args.Add(EntityDef::id2datatypes[8]);

	Method* pCommunicateStation_reqMakeUpFrames = new Method();
	pCommunicateStation_reqMakeUpFrames->name = TEXT("reqMakeUpFrames");
	pCommunicateStation_reqMakeUpFrames->methodUtype = 76;
	pCommunicateStation_reqMakeUpFrames->aliasID = -1;
	pCommunicateStation_reqMakeUpFrames->args = CommunicateStation_reqMakeUpFrames_args;

	pCommunicateStationModule->methods.Add(TEXT("reqMakeUpFrames"), pCommunicateStation_reqMakeUpFrames); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqMakeUpFrames"), pCommunicateStation_reqMakeUpFrames);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqMakeUpFrames->methodUtype, pCommunicateStation_reqMakeUpFrames);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqMakeUpFrames / 76).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqStartUploadCorrectInfo_args;
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[1]);
	CommunicateStation_reqStartUploadCorrectInfo_args.Add(EntityDef::id2datatypes[8]);

	Method* pCommunicateStation_reqStartUploadCorrectInfo = new Method();
	pCommunicateStation_reqStartUploadCorrectInfo->name = TEXT("reqStartUploadCorrectInfo");
	pCommunicateStation_reqStartUploadCorrectInfo->methodUtype = 78;
	pCommunicateStation_reqStartUploadCorrectInfo->aliasID = -1;
	pCommunicateStation_reqStartUploadCorrectInfo->args = CommunicateStation_reqStartUploadCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqStartUploadCorrectInfo"), pCommunicateStation_reqStartUploadCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqStartUploadCorrectInfo"), pCommunicateStation_reqStartUploadCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqStartUploadCorrectInfo->methodUtype, pCommunicateStation_reqStartUploadCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqStartUploadCorrectInfo / 78).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqTellRoomIsReady_args;

	Method* pCommunicateStation_reqTellRoomIsReady = new Method();
	pCommunicateStation_reqTellRoomIsReady->name = TEXT("reqTellRoomIsReady");
	pCommunicateStation_reqTellRoomIsReady->methodUtype = 72;
	pCommunicateStation_reqTellRoomIsReady->aliasID = -1;
	pCommunicateStation_reqTellRoomIsReady->args = CommunicateStation_reqTellRoomIsReady_args;

	pCommunicateStationModule->methods.Add(TEXT("reqTellRoomIsReady"), pCommunicateStation_reqTellRoomIsReady); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqTellRoomIsReady"), pCommunicateStation_reqTellRoomIsReady);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqTellRoomIsReady->methodUtype, pCommunicateStation_reqTellRoomIsReady);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqTellRoomIsReady / 72).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqTellRoomResetDone_args;

	Method* pCommunicateStation_reqTellRoomResetDone = new Method();
	pCommunicateStation_reqTellRoomResetDone->name = TEXT("reqTellRoomResetDone");
	pCommunicateStation_reqTellRoomResetDone->methodUtype = 88;
	pCommunicateStation_reqTellRoomResetDone->aliasID = -1;
	pCommunicateStation_reqTellRoomResetDone->args = CommunicateStation_reqTellRoomResetDone_args;

	pCommunicateStationModule->methods.Add(TEXT("reqTellRoomResetDone"), pCommunicateStation_reqTellRoomResetDone); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqTellRoomResetDone"), pCommunicateStation_reqTellRoomResetDone);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqTellRoomResetDone->methodUtype, pCommunicateStation_reqTellRoomResetDone);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqTellRoomResetDone / 88).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqTellRoundEnd_args;
	CommunicateStation_reqTellRoundEnd_args.Add(EntityDef::id2datatypes[224]);

	Method* pCommunicateStation_reqTellRoundEnd = new Method();
	pCommunicateStation_reqTellRoundEnd->name = TEXT("reqTellRoundEnd");
	pCommunicateStation_reqTellRoundEnd->methodUtype = 87;
	pCommunicateStation_reqTellRoundEnd->aliasID = -1;
	pCommunicateStation_reqTellRoundEnd->args = CommunicateStation_reqTellRoundEnd_args;

	pCommunicateStationModule->methods.Add(TEXT("reqTellRoundEnd"), pCommunicateStation_reqTellRoundEnd); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqTellRoundEnd"), pCommunicateStation_reqTellRoundEnd);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqTellRoundEnd->methodUtype, pCommunicateStation_reqTellRoundEnd);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqTellRoundEnd / 87).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadAIOperationList_args;
	CommunicateStation_reqUploadAIOperationList_args.Add(EntityDef::id2datatypes[173]);

	Method* pCommunicateStation_reqUploadAIOperationList = new Method();
	pCommunicateStation_reqUploadAIOperationList->name = TEXT("reqUploadAIOperationList");
	pCommunicateStation_reqUploadAIOperationList->methodUtype = 75;
	pCommunicateStation_reqUploadAIOperationList->aliasID = -1;
	pCommunicateStation_reqUploadAIOperationList->args = CommunicateStation_reqUploadAIOperationList_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadAIOperationList"), pCommunicateStation_reqUploadAIOperationList); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadAIOperationList"), pCommunicateStation_reqUploadAIOperationList);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadAIOperationList->methodUtype, pCommunicateStation_reqUploadAIOperationList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadAIOperationList / 75).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadActorCorrectInfo_args;
	CommunicateStation_reqUploadActorCorrectInfo_args.Add(EntityDef::id2datatypes[144]);

	Method* pCommunicateStation_reqUploadActorCorrectInfo = new Method();
	pCommunicateStation_reqUploadActorCorrectInfo->name = TEXT("reqUploadActorCorrectInfo");
	pCommunicateStation_reqUploadActorCorrectInfo->methodUtype = 83;
	pCommunicateStation_reqUploadActorCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadActorCorrectInfo->args = CommunicateStation_reqUploadActorCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadActorCorrectInfo"), pCommunicateStation_reqUploadActorCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadActorCorrectInfo"), pCommunicateStation_reqUploadActorCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadActorCorrectInfo->methodUtype, pCommunicateStation_reqUploadActorCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadActorCorrectInfo / 83).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadCharacterCorrectInfo_args;
	CommunicateStation_reqUploadCharacterCorrectInfo_args.Add(EntityDef::id2datatypes[106]);

	Method* pCommunicateStation_reqUploadCharacterCorrectInfo = new Method();
	pCommunicateStation_reqUploadCharacterCorrectInfo->name = TEXT("reqUploadCharacterCorrectInfo");
	pCommunicateStation_reqUploadCharacterCorrectInfo->methodUtype = 79;
	pCommunicateStation_reqUploadCharacterCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadCharacterCorrectInfo->args = CommunicateStation_reqUploadCharacterCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadCharacterCorrectInfo"), pCommunicateStation_reqUploadCharacterCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadCharacterCorrectInfo"), pCommunicateStation_reqUploadCharacterCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadCharacterCorrectInfo->methodUtype, pCommunicateStation_reqUploadCharacterCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadCharacterCorrectInfo / 79).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadEndCorrectInfo_args;

	Method* pCommunicateStation_reqUploadEndCorrectInfo = new Method();
	pCommunicateStation_reqUploadEndCorrectInfo->name = TEXT("reqUploadEndCorrectInfo");
	pCommunicateStation_reqUploadEndCorrectInfo->methodUtype = 86;
	pCommunicateStation_reqUploadEndCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadEndCorrectInfo->args = CommunicateStation_reqUploadEndCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadEndCorrectInfo"), pCommunicateStation_reqUploadEndCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadEndCorrectInfo"), pCommunicateStation_reqUploadEndCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadEndCorrectInfo->methodUtype, pCommunicateStation_reqUploadEndCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadEndCorrectInfo / 86).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadEnermyGroupCorrectInfo_args;
	CommunicateStation_reqUploadEnermyGroupCorrectInfo_args.Add(EntityDef::id2datatypes[159]);

	Method* pCommunicateStation_reqUploadEnermyGroupCorrectInfo = new Method();
	pCommunicateStation_reqUploadEnermyGroupCorrectInfo->name = TEXT("reqUploadEnermyGroupCorrectInfo");
	pCommunicateStation_reqUploadEnermyGroupCorrectInfo->methodUtype = 85;
	pCommunicateStation_reqUploadEnermyGroupCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadEnermyGroupCorrectInfo->args = CommunicateStation_reqUploadEnermyGroupCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadEnermyGroupCorrectInfo"), pCommunicateStation_reqUploadEnermyGroupCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadEnermyGroupCorrectInfo"), pCommunicateStation_reqUploadEnermyGroupCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadEnermyGroupCorrectInfo->methodUtype, pCommunicateStation_reqUploadEnermyGroupCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadEnermyGroupCorrectInfo / 85).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadFrame_args;
	CommunicateStation_reqUploadFrame_args.Add(EntityDef::id2datatypes[8]);

	Method* pCommunicateStation_reqUploadFrame = new Method();
	pCommunicateStation_reqUploadFrame->name = TEXT("reqUploadFrame");
	pCommunicateStation_reqUploadFrame->methodUtype = 73;
	pCommunicateStation_reqUploadFrame->aliasID = -1;
	pCommunicateStation_reqUploadFrame->args = CommunicateStation_reqUploadFrame_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadFrame"), pCommunicateStation_reqUploadFrame); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadFrame"), pCommunicateStation_reqUploadFrame);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadFrame->methodUtype, pCommunicateStation_reqUploadFrame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadFrame / 73).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadLineCorrectInfo_args;
	CommunicateStation_reqUploadLineCorrectInfo_args.Add(EntityDef::id2datatypes[111]);

	Method* pCommunicateStation_reqUploadLineCorrectInfo = new Method();
	pCommunicateStation_reqUploadLineCorrectInfo->name = TEXT("reqUploadLineCorrectInfo");
	pCommunicateStation_reqUploadLineCorrectInfo->methodUtype = 81;
	pCommunicateStation_reqUploadLineCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadLineCorrectInfo->args = CommunicateStation_reqUploadLineCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadLineCorrectInfo"), pCommunicateStation_reqUploadLineCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadLineCorrectInfo"), pCommunicateStation_reqUploadLineCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadLineCorrectInfo->methodUtype, pCommunicateStation_reqUploadLineCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadLineCorrectInfo / 81).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadOperation_args;
	CommunicateStation_reqUploadOperation_args.Add(EntityDef::id2datatypes[171]);

	Method* pCommunicateStation_reqUploadOperation = new Method();
	pCommunicateStation_reqUploadOperation->name = TEXT("reqUploadOperation");
	pCommunicateStation_reqUploadOperation->methodUtype = 74;
	pCommunicateStation_reqUploadOperation->aliasID = -1;
	pCommunicateStation_reqUploadOperation->args = CommunicateStation_reqUploadOperation_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadOperation"), pCommunicateStation_reqUploadOperation); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadOperation"), pCommunicateStation_reqUploadOperation);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadOperation->methodUtype, pCommunicateStation_reqUploadOperation);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadOperation / 74).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadPointCorrectInfo_args;
	CommunicateStation_reqUploadPointCorrectInfo_args.Add(EntityDef::id2datatypes[132]);

	Method* pCommunicateStation_reqUploadPointCorrectInfo = new Method();
	pCommunicateStation_reqUploadPointCorrectInfo->name = TEXT("reqUploadPointCorrectInfo");
	pCommunicateStation_reqUploadPointCorrectInfo->methodUtype = 82;
	pCommunicateStation_reqUploadPointCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadPointCorrectInfo->args = CommunicateStation_reqUploadPointCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadPointCorrectInfo"), pCommunicateStation_reqUploadPointCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadPointCorrectInfo"), pCommunicateStation_reqUploadPointCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadPointCorrectInfo->methodUtype, pCommunicateStation_reqUploadPointCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadPointCorrectInfo / 82).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadPolyCorrectInfo_args;
	CommunicateStation_reqUploadPolyCorrectInfo_args.Add(EntityDef::id2datatypes[120]);

	Method* pCommunicateStation_reqUploadPolyCorrectInfo = new Method();
	pCommunicateStation_reqUploadPolyCorrectInfo->name = TEXT("reqUploadPolyCorrectInfo");
	pCommunicateStation_reqUploadPolyCorrectInfo->methodUtype = 80;
	pCommunicateStation_reqUploadPolyCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadPolyCorrectInfo->args = CommunicateStation_reqUploadPolyCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadPolyCorrectInfo"), pCommunicateStation_reqUploadPolyCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadPolyCorrectInfo"), pCommunicateStation_reqUploadPolyCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadPolyCorrectInfo->methodUtype, pCommunicateStation_reqUploadPolyCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadPolyCorrectInfo / 80).");

	TArray<DATATYPE_BASE*> CommunicateStation_reqUploadReactionPairCorrectInfo_args;
	CommunicateStation_reqUploadReactionPairCorrectInfo_args.Add(EntityDef::id2datatypes[157]);

	Method* pCommunicateStation_reqUploadReactionPairCorrectInfo = new Method();
	pCommunicateStation_reqUploadReactionPairCorrectInfo->name = TEXT("reqUploadReactionPairCorrectInfo");
	pCommunicateStation_reqUploadReactionPairCorrectInfo->methodUtype = 84;
	pCommunicateStation_reqUploadReactionPairCorrectInfo->aliasID = -1;
	pCommunicateStation_reqUploadReactionPairCorrectInfo->args = CommunicateStation_reqUploadReactionPairCorrectInfo_args;

	pCommunicateStationModule->methods.Add(TEXT("reqUploadReactionPairCorrectInfo"), pCommunicateStation_reqUploadReactionPairCorrectInfo); 
	pCommunicateStationModule->cell_methods.Add(TEXT("reqUploadReactionPairCorrectInfo"), pCommunicateStation_reqUploadReactionPairCorrectInfo);

	pCommunicateStationModule->idcell_methods.Add(pCommunicateStation_reqUploadReactionPairCorrectInfo->methodUtype, pCommunicateStation_reqUploadReactionPairCorrectInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(CommunicateStation), method(reqUploadReactionPairCorrectInfo / 84).");

}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("BOOL");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("UID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("PRICE");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("MAPTYPE");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("ROTATION");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("DBID_LIST");
		DATATYPE_DBID_LIST* pDatatype = new DATATYPE_DBID_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("INT8ARRAY");
		DATATYPE_INT8ARRAY* pDatatype = new DATATYPE_INT8ARRAY();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("BYTE_LIST");
		DATATYPE_BYTE_LIST* pDatatype = new DATATYPE_BYTE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 26;
		FString typeName = TEXT("STRING_LIST");
		DATATYPE_STRING_LIST* pDatatype = new DATATYPE_STRING_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 28;
		FString typeName = TEXT("INT_LIST");
		DATATYPE_INT_LIST* pDatatype = new DATATYPE_INT_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 30;
		FString typeName = TEXT("LOGIC_VECTOR");
		DATATYPE_LOGIC_VECTOR* pDatatype = new DATATYPE_LOGIC_VECTOR();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 31;
		FString typeName = TEXT("PLAYER_TAG_INFO");
		DATATYPE_PLAYER_TAG_INFO* pDatatype = new DATATYPE_PLAYER_TAG_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 32;
		FString typeName = TEXT("PLAYER_TAG_INFO_LIST");
		DATATYPE_PLAYER_TAG_INFO_LIST* pDatatype = new DATATYPE_PLAYER_TAG_INFO_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 34;
		FString typeName = TEXT("FRIEND_LIST");
		DATATYPE_FRIEND_LIST* pDatatype = new DATATYPE_FRIEND_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 37;
		FString typeName = TEXT("PLAYER_ENTITYCALL_INFO");
		DATATYPE_PLAYER_ENTITYCALL_INFO* pDatatype = new DATATYPE_PLAYER_ENTITYCALL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 38;
		FString typeName = TEXT("PLAYER_ENTITYCALL_INFO_LIST");
		DATATYPE_PLAYER_ENTITYCALL_INFO_LIST* pDatatype = new DATATYPE_PLAYER_ENTITYCALL_INFO_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 39;
		FString typeName = TEXT("CHARACTER_INFO");
		DATATYPE_CHARACTER_INFO* pDatatype = new DATATYPE_CHARACTER_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 40;
		FString typeName = TEXT("ECONOMY_INFO");
		DATATYPE_ECONOMY_INFO* pDatatype = new DATATYPE_ECONOMY_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 41;
		FString typeName = TEXT("WIN_PERCENT_INFO");
		DATATYPE_WIN_PERCENT_INFO* pDatatype = new DATATYPE_WIN_PERCENT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 42;
		FString typeName = TEXT("RANK_ONE_MAP");
		DATATYPE_RANK_ONE_MAP* pDatatype = new DATATYPE_RANK_ONE_MAP();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 43;
		FString typeName = TEXT("PLAYER_ALL_RANK_LIST");
		DATATYPE_PLAYER_ALL_RANK_LIST* pDatatype = new DATATYPE_PLAYER_ALL_RANK_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 47;
		FString typeName = TEXT("BATTLE_RESULT_ONE_TYPE");
		DATATYPE_BATTLE_RESULT_ONE_TYPE* pDatatype = new DATATYPE_BATTLE_RESULT_ONE_TYPE();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 48;
		FString typeName = TEXT("BATTLE_RESULT_ONE_MAP");
		DATATYPE_BATTLE_RESULT_ONE_MAP* pDatatype = new DATATYPE_BATTLE_RESULT_ONE_MAP();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 50;
		FString typeName = TEXT("ADDITION_EFFECT");
		DATATYPE_ADDITION_EFFECT* pDatatype = new DATATYPE_ADDITION_EFFECT();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 51;
		FString typeName = TEXT("RUNEINFO");
		DATATYPE_RUNEINFO* pDatatype = new DATATYPE_RUNEINFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 52;
		FString typeName = TEXT("RUNEINFOLIST");
		DATATYPE_RUNEINFOLIST* pDatatype = new DATATYPE_RUNEINFOLIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 54;
		FString typeName = TEXT("RUNECONFIGINFO");
		DATATYPE_RUNECONFIGINFO* pDatatype = new DATATYPE_RUNECONFIGINFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 55;
		FString typeName = TEXT("RUNECONFIGINFOLIST");
		DATATYPE_RUNECONFIGINFOLIST* pDatatype = new DATATYPE_RUNECONFIGINFOLIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 57;
		FString typeName = TEXT("PLAYER_RUNE_INFO");
		DATATYPE_PLAYER_RUNE_INFO* pDatatype = new DATATYPE_PLAYER_RUNE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 59;
		FString typeName = TEXT("PLAYER_INFO");
		DATATYPE_PLAYER_INFO* pDatatype = new DATATYPE_PLAYER_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 65;
		FString typeName = TEXT("REQ_MATCH_PLAYER_DATA");
		DATATYPE_REQ_MATCH_PLAYER_DATA* pDatatype = new DATATYPE_REQ_MATCH_PLAYER_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 66;
		FString typeName = TEXT("REQ_MATCH_PLAYER_DATA_LIST");
		DATATYPE_REQ_MATCH_PLAYER_DATA_LIST* pDatatype = new DATATYPE_REQ_MATCH_PLAYER_DATA_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 68;
		FString typeName = TEXT("REQ_TEAM_MATCH_DATA");
		DATATYPE_REQ_TEAM_MATCH_DATA* pDatatype = new DATATYPE_REQ_TEAM_MATCH_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 69;
		FString typeName = TEXT("REQ_TEAM_MATCH_RANK_INFO");
		DATATYPE_REQ_TEAM_MATCH_RANK_INFO* pDatatype = new DATATYPE_REQ_TEAM_MATCH_RANK_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 70;
		FString typeName = TEXT("REQ_TEAM_MATCH_APPLICATION");
		DATATYPE_REQ_TEAM_MATCH_APPLICATION* pDatatype = new DATATYPE_REQ_TEAM_MATCH_APPLICATION();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 73;
		FString typeName = TEXT("REQ_MATCH_TWO_TWO_DATA");
		DATATYPE_REQ_MATCH_TWO_TWO_DATA* pDatatype = new DATATYPE_REQ_MATCH_TWO_TWO_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 74;
		FString typeName = TEXT("REQ_MATCH_TWO_TWO_DATA_LIST");
		DATATYPE_REQ_MATCH_TWO_TWO_DATA_LIST* pDatatype = new DATATYPE_REQ_MATCH_TWO_TWO_DATA_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 76;
		FString typeName = TEXT("REQ_MATCH_THREE_THREE_DATA");
		DATATYPE_REQ_MATCH_THREE_THREE_DATA* pDatatype = new DATATYPE_REQ_MATCH_THREE_THREE_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 77;
		FString typeName = TEXT("REQ_MATCH_THREE_THREE_DATA_LIST");
		DATATYPE_REQ_MATCH_THREE_THREE_DATA_LIST* pDatatype = new DATATYPE_REQ_MATCH_THREE_THREE_DATA_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 79;
		FString typeName = TEXT("REQ_MATCH_LIST_ALL_MAPS");
		DATATYPE_REQ_MATCH_LIST_ALL_MAPS* pDatatype = new DATATYPE_REQ_MATCH_LIST_ALL_MAPS();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 85;
		FString typeName = TEXT("MATCHED_PLAYER_LIST_ONE_ROOM");
		DATATYPE_MATCHED_PLAYER_LIST_ONE_ROOM* pDatatype = new DATATYPE_MATCHED_PLAYER_LIST_ONE_ROOM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 87;
		FString typeName = TEXT("MATCHED_PLAYER_TEAM");
		DATATYPE_MATCHED_PLAYER_TEAM* pDatatype = new DATATYPE_MATCHED_PLAYER_TEAM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 89;
		FString typeName = TEXT("MATCHED_TWO_TWO_LIST_ONE_ROOM");
		DATATYPE_MATCHED_TWO_TWO_LIST_ONE_ROOM* pDatatype = new DATATYPE_MATCHED_TWO_TWO_LIST_ONE_ROOM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 91;
		FString typeName = TEXT("MATCHED_THREE_THREE_LIST_ONE_ROOM");
		DATATYPE_MATCHED_THREE_THREE_LIST_ONE_ROOM* pDatatype = new DATATYPE_MATCHED_THREE_THREE_LIST_ONE_ROOM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 93;
		FString typeName = TEXT("MATCHED_ROOM_LIST");
		DATATYPE_MATCHED_ROOM_LIST* pDatatype = new DATATYPE_MATCHED_ROOM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 99;
		FString typeName = TEXT("MATCHED_LIST_ALL_MAPS");
		DATATYPE_MATCHED_LIST_ALL_MAPS* pDatatype = new DATATYPE_MATCHED_LIST_ALL_MAPS();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 101;
		FString typeName = TEXT("SKILL_INFO");
		DATATYPE_SKILL_INFO* pDatatype = new DATATYPE_SKILL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 102;
		FString typeName = TEXT("EQUIPMENT_INFO");
		DATATYPE_EQUIPMENT_INFO* pDatatype = new DATATYPE_EQUIPMENT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 104;
		FString typeName = TEXT("EFFECT_INFO");
		DATATYPE_EFFECT_INFO* pDatatype = new DATATYPE_EFFECT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 106;
		FString typeName = TEXT("CHARACTER_CORRECT_INFO");
		DATATYPE_CHARACTER_CORRECT_INFO* pDatatype = new DATATYPE_CHARACTER_CORRECT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 111;
		FString typeName = TEXT("PHYSLINE_INFO");
		DATATYPE_PHYSLINE_INFO* pDatatype = new DATATYPE_PHYSLINE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 120;
		FString typeName = TEXT("PHYSPOLY_INFO");
		DATATYPE_PHYSPOLY_INFO* pDatatype = new DATATYPE_PHYSPOLY_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 132;
		FString typeName = TEXT("PHYSPOINT_INFO");
		DATATYPE_PHYSPOINT_INFO* pDatatype = new DATATYPE_PHYSPOINT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 144;
		FString typeName = TEXT("PHYSACTOR_INFO");
		DATATYPE_PHYSACTOR_INFO* pDatatype = new DATATYPE_PHYSACTOR_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 156;
		FString typeName = TEXT("REACTION_INFO");
		DATATYPE_REACTION_INFO* pDatatype = new DATATYPE_REACTION_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 157;
		FString typeName = TEXT("REACTION_PAIR_INFO");
		DATATYPE_REACTION_PAIR_INFO* pDatatype = new DATATYPE_REACTION_PAIR_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 158;
		FString typeName = TEXT("ENERMY_SPAWN_POINT_CORRECT_INFO");
		DATATYPE_ENERMY_SPAWN_POINT_CORRECT_INFO* pDatatype = new DATATYPE_ENERMY_SPAWN_POINT_CORRECT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 159;
		FString typeName = TEXT("ENERMY_GROUP_CORRECT_INFO");
		DATATYPE_ENERMY_GROUP_CORRECT_INFO* pDatatype = new DATATYPE_ENERMY_GROUP_CORRECT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 161;
		FString typeName = TEXT("PLAYER_CORRECT_PROGRESS");
		DATATYPE_PLAYER_CORRECT_PROGRESS* pDatatype = new DATATYPE_PLAYER_CORRECT_PROGRESS();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 162;
		FString typeName = TEXT("CORRECT_INFO_LIST");
		DATATYPE_CORRECT_INFO_LIST* pDatatype = new DATATYPE_CORRECT_INFO_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 171;
		FString typeName = TEXT("PLAYER_OPERATION_INFO");
		DATATYPE_PLAYER_OPERATION_INFO* pDatatype = new DATATYPE_PLAYER_OPERATION_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 172;
		FString typeName = TEXT("AI_CHARACTER_OPERATION_INFO");
		DATATYPE_AI_CHARACTER_OPERATION_INFO* pDatatype = new DATATYPE_AI_CHARACTER_OPERATION_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 173;
		FString typeName = TEXT("AI_CHARACTER_OPERATION_LIST");
		DATATYPE_AI_CHARACTER_OPERATION_LIST* pDatatype = new DATATYPE_AI_CHARACTER_OPERATION_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 175;
		FString typeName = TEXT("LOGIC_FRAME");
		DATATYPE_LOGIC_FRAME* pDatatype = new DATATYPE_LOGIC_FRAME();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 178;
		FString typeName = TEXT("LOGIC_FRAME_LIST");
		DATATYPE_LOGIC_FRAME_LIST* pDatatype = new DATATYPE_LOGIC_FRAME_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 180;
		FString typeName = TEXT("COMPLETE_FRAME_INFO");
		DATATYPE_COMPLETE_FRAME_INFO* pDatatype = new DATATYPE_COMPLETE_FRAME_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 189;
		FString typeName = TEXT("PLAYER_SPAWN_POINT_INFO");
		DATATYPE_PLAYER_SPAWN_POINT_INFO* pDatatype = new DATATYPE_PLAYER_SPAWN_POINT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 190;
		FString typeName = TEXT("PLAYER_SPAWN_POINT_LIST");
		DATATYPE_PLAYER_SPAWN_POINT_LIST* pDatatype = new DATATYPE_PLAYER_SPAWN_POINT_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 192;
		FString typeName = TEXT("SPECIAL_FRAME_LIST");
		DATATYPE_SPECIAL_FRAME_LIST* pDatatype = new DATATYPE_SPECIAL_FRAME_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 195;
		FString typeName = TEXT("TRIGGER_INFO");
		DATATYPE_TRIGGER_INFO* pDatatype = new DATATYPE_TRIGGER_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 196;
		FString typeName = TEXT("ENERMY_SPAWN_ORDER");
		DATATYPE_ENERMY_SPAWN_ORDER* pDatatype = new DATATYPE_ENERMY_SPAWN_ORDER();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 198;
		FString typeName = TEXT("ENERMY_SPAWN_POINT_INFO");
		DATATYPE_ENERMY_SPAWN_POINT_INFO* pDatatype = new DATATYPE_ENERMY_SPAWN_POINT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 199;
		FString typeName = TEXT("ENERMY_SPAWN_GROUP_INFO");
		DATATYPE_ENERMY_SPAWN_GROUP_INFO* pDatatype = new DATATYPE_ENERMY_SPAWN_GROUP_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 201;
		FString typeName = TEXT("ENERMY_SPAWN_GROUP_LIST");
		DATATYPE_ENERMY_SPAWN_GROUP_LIST* pDatatype = new DATATYPE_ENERMY_SPAWN_GROUP_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 203;
		FString typeName = TEXT("PHYSACTOR_SPAWN_INFO");
		DATATYPE_PHYSACTOR_SPAWN_INFO* pDatatype = new DATATYPE_PHYSACTOR_SPAWN_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 207;
		FString typeName = TEXT("PHYSACTOR_SPAWN_LIST");
		DATATYPE_PHYSACTOR_SPAWN_LIST* pDatatype = new DATATYPE_PHYSACTOR_SPAWN_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 209;
		FString typeName = TEXT("LEVEL_MODEL_INFO");
		DATATYPE_LEVEL_MODEL_INFO* pDatatype = new DATATYPE_LEVEL_MODEL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 211;
		FString typeName = TEXT("LEVEL_MODEL_LIST");
		DATATYPE_LEVEL_MODEL_LIST* pDatatype = new DATATYPE_LEVEL_MODEL_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 213;
		FString typeName = TEXT("PLAYER_RANK_INFO");
		DATATYPE_PLAYER_RANK_INFO* pDatatype = new DATATYPE_PLAYER_RANK_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 214;
		FString typeName = TEXT("RANK_LIST");
		DATATYPE_RANK_LIST* pDatatype = new DATATYPE_RANK_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 216;
		FString typeName = TEXT("ALL_RANK_LIST");
		DATATYPE_ALL_RANK_LIST* pDatatype = new DATATYPE_ALL_RANK_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 221;
		FString typeName = TEXT("PLAYER_BATTLE_STATUS");
		DATATYPE_PLAYER_BATTLE_STATUS* pDatatype = new DATATYPE_PLAYER_BATTLE_STATUS();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 222;
		FString typeName = TEXT("BATTLE_TEAM_INFO");
		DATATYPE_BATTLE_TEAM_INFO* pDatatype = new DATATYPE_BATTLE_TEAM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 224;
		FString typeName = TEXT("BATTLE_RESULT_ROUND");
		DATATYPE_BATTLE_RESULT_ROUND* pDatatype = new DATATYPE_BATTLE_RESULT_ROUND();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 227;
		FString typeName = TEXT("BATTLE_RESULT_ROUND_LIST");
		DATATYPE_BATTLE_RESULT_ROUND_LIST* pDatatype = new DATATYPE_BATTLE_RESULT_ROUND_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 229;
		FString typeName = TEXT("TEAM_WIN_INFO");
		DATATYPE_TEAM_WIN_INFO* pDatatype = new DATATYPE_TEAM_WIN_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 232;
		FString typeName = TEXT("BATTLE_RESULT");
		DATATYPE_BATTLE_RESULT* pDatatype = new DATATYPE_BATTLE_RESULT();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 235;
		FString typeName = TEXT("ACCOUNT_INFO");
		DATATYPE_ACCOUNT_INFO* pDatatype = new DATATYPE_ACCOUNT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 236;
		FString typeName = TEXT("ACCOUNT_INFO_LIST");
		DATATYPE_ACCOUNT_INFO_LIST* pDatatype = new DATATYPE_ACCOUNT_INFO_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 238;
		FString typeName = TEXT("PLAYER_ROLETYPE_ASSIGNNUM");
		DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM* pDatatype = new DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 239;
		FString typeName = TEXT("PLAYER_ROLETYPE_ASSIGNNUM_LIST");
		DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST* pDatatype = new DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 241;
		FString typeName = TEXT("MALL_GOODS_INFO");
		DATATYPE_MALL_GOODS_INFO* pDatatype = new DATATYPE_MALL_GOODS_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 242;
		FString typeName = TEXT("MALL_GOODS_LIST");
		DATATYPE_MALL_GOODS_LIST* pDatatype = new DATATYPE_MALL_GOODS_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 244;
		FString typeName = TEXT("MALL_GOODS_INFO_FOR_CLIENT");
		DATATYPE_MALL_GOODS_INFO_FOR_CLIENT* pDatatype = new DATATYPE_MALL_GOODS_INFO_FOR_CLIENT();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 245;
		FString typeName = TEXT("GOODS_LIST");
		DATATYPE_GOODS_LIST* pDatatype = new DATATYPE_GOODS_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 247;
		FString typeName = TEXT("GLOBAL_INFO");
		DATATYPE_GLOBAL_INFO* pDatatype = new DATATYPE_GLOBAL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 248;
		FString typeName = TEXT("ADD_FRIEND_REQUEST");
		DATATYPE_ADD_FRIEND_REQUEST* pDatatype = new DATATYPE_ADD_FRIEND_REQUEST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 249;
		FString typeName = TEXT("ADD_FRIEND_REQUEST_LIST");
		DATATYPE_ADD_FRIEND_REQUEST_LIST* pDatatype = new DATATYPE_ADD_FRIEND_REQUEST_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 251;
		FString typeName = TEXT("ADD_FRIEND_ANSWER");
		DATATYPE_ADD_FRIEND_ANSWER* pDatatype = new DATATYPE_ADD_FRIEND_ANSWER();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 252;
		FString typeName = TEXT("ADD_FRIEND_ANSWER_LIST");
		DATATYPE_ADD_FRIEND_ANSWER_LIST* pDatatype = new DATATYPE_ADD_FRIEND_ANSWER_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 254;
		FString typeName = TEXT("DELETE_FRIEND_REQUEST");
		DATATYPE_DELETE_FRIEND_REQUEST* pDatatype = new DATATYPE_DELETE_FRIEND_REQUEST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 255;
		FString typeName = TEXT("DELETE_FRIEND_REQUEST_LIST");
		DATATYPE_DELETE_FRIEND_REQUEST_LIST* pDatatype = new DATATYPE_DELETE_FRIEND_REQUEST_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 257;
		FString typeName = TEXT("AnonymousArray_257");
		DATATYPE_AnonymousArray_257* pDatatype = new DATATYPE_AnonymousArray_257();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 258;
		FString typeName = TEXT("AnonymousArray_258");
		DATATYPE_AnonymousArray_258* pDatatype = new DATATYPE_AnonymousArray_258();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 259;
		FString typeName = TEXT("AnonymousArray_259");
		DATATYPE_AnonymousArray_259* pDatatype = new DATATYPE_AnonymousArray_259();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 260;
		FString typeName = TEXT("AnonymousArray_260");
		DATATYPE_AnonymousArray_260* pDatatype = new DATATYPE_AnonymousArray_260();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 261;
		FString typeName = TEXT("AnonymousArray_261");
		DATATYPE_AnonymousArray_261* pDatatype = new DATATYPE_AnonymousArray_261();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 262;
		FString typeName = TEXT("AnonymousArray_262");
		DATATYPE_AnonymousArray_262* pDatatype = new DATATYPE_AnonymousArray_262();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 263;
		FString typeName = TEXT("AnonymousArray_263");
		DATATYPE_AnonymousArray_263* pDatatype = new DATATYPE_AnonymousArray_263();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}

