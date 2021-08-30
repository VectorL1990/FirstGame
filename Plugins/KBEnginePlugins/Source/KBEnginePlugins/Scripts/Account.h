// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/AccountBase.h"


class Account : public AccountBase
{
public:
	Account();
	virtual ~Account();

public:
	virtual void __init__() override;
	virtual void onDestroy() override;

	virtual void dispatchLogonStatus(const FString& arg1, const FString& arg2) override;
	virtual void dispatchBuyResult(uint8 arg1, int32 arg2, uint8 arg3, const FString& arg4) override;
	virtual void dispatchLevelModelList(const LEVEL_MODEL_LIST& arg1) override;
	virtual void dispatchMallInfoList(const GOODS_LIST& arg1) override;
	virtual void dispatchPlayerInfo(const PLAYER_INFO& arg1) override;
	virtual void dispatchRankList(const ALL_RANK_LIST& arg1) override;
	virtual void gameDevelopFun(const FString& arg1) override;
	virtual void dispatchMessageFromFriend(const FString& arg1, const FString& arg2) override;
	virtual void dispatchSendMessageResult(const FString& arg1, const FString& arg2)override;
	virtual void dispatchMatchResult(const FString& arg1, uint8 arg2, const FString& arg3, const PLAYER_TAG_INFO_LIST& arg4) override;
	virtual void dispatchAllPlayerRoletypeAndAssignNb(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int32 arg5) override;
	virtual void dispatchRelogonInfo(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int8 arg5, const FString& arg6) override;
	virtual void dispatchRelogonPlayerInfo(const PLAYER_INFO& arg1, const GOODS_LIST& arg2) override;
	virtual void dispatchPlayerTagInfoList(const PLAYER_TAG_INFO_LIST& arg1) override;
	virtual void dispatchAddFriendRequestResult(uint8 arg1) override;
	virtual void dispatchAddFriendRequest(const FString& arg1, uint64 arg2) override;
	virtual void dispatchDisapproveAddFriendAnswer(const FString& arg1) override;
	virtual void dispatchApproveAddFriendAnswer(const FString& arg1, const PLAYER_TAG_INFO& arg2) override;
	virtual void dispatchDeleteFriendRequestResult(uint8 arg1, const FString& arg2) override;
	virtual void dispatchTeamMatchStatus(const FString& arg1, const FString& arg2) override;
	virtual void dispatchTeamMatchInvitation(int32 arg1, const FString& arg2, const FString& arg3, int32 arg4) override;
	virtual void dispatchCancelMatch() override;
	virtual void dispatchMatchStatus(const FString& arg1) override;
	virtual void dispatchAllRuneDataToClient(const RUNEINFOLIST& arg1, const RUNECONFIGINFOLIST& arg2) override;
	virtual void dispatchRuneConfigEffectToClient(const BYTE_LIST& arg1, uint8 arg2) override;
	virtual void dispatchHasConfigInfosToClient(const BYTE_LIST& arg1) override;


	void reqPlayerInfo();
	void ReqMallInfoList();
	void ReqLoadLevelModelList();
	void ReqSimpleSingleMatch(FString mapType, FString roleType);
	void ReqSingleMatch(FString mapType, FString roleType);
	void ReqOneOneMatch(FString mapType, FString roleType);
	void ReqEnsureEnterRoom();
	void ReqCancelMatch();
	void ReqRelogonInfo();
	void ReqRankList();
	void ReqPlayerTagInfoList(STRING_LIST nameList);
	void ReqAddFriend(FString FriendName);
	void ReqNotifyRecieveAddFriendRequest(uint64 applierDBID);
	void ReqAnswerAddFriendRequest(uint8 answer, uint64 applierDBID);
	void ReqDeleteFriend(FString friendName);
	void ReqFriendMatch(const REQ_TEAM_MATCH_DATA& data,const STRING_LIST& friendNameList, const FString& mapType);
	void ReqAnswerFriendMatch(uint8 result, FString hostName, FString roleType, int32 groupNb);
	void ReqSendMessageToFriend(const FString& message, const FString& friendName);
	void ReqChangeCurSelectCharacter(const FString& roleType);
	void ReqAllRuneDataFromServer();
	void ReqSetRuneConfigDataToServer(const FString& runeConfigName, uint8 sky, uint8 ground, uint8 life, uint8 death);
/*

	void reqAnswerFriendMatch(uint8 arg1, const FString& arg2, const FString& arg3);
	void reqBuy(const FString& arg1, uint8 arg2);
	void reqCancelMatch();
	void reqChangeCurSelectCharacter(const FString& arg1);
	void reqEnsureEnterRoom();
	void reqFriendMatch(const FString& arg1, const FString& arg2);
	void reqLevelInfos(const FString& arg1, const FString& arg2);
	void reqLoadLevelModelList();
	void reqMallInfoList();
	void reqOneOneMatch(const FString& arg1, const FString& arg2);
	void reqPlayerInfo();
	void reqSendMessageToFriend(const FString& arg1, const FString& arg2);
	void reqSimpleSingleMatch(const FString& arg1, const FString& arg2);
	void reqSingleMatch(const FString& arg1, const FString& arg2);
	void reqThreeThreeMatch(const FString& arg1, const FString& arg2, const FString& arg3, const FString& arg4, int32 arg5, int32 arg6, int32 arg7);
	void reqTwoTwoMatch(const FString& arg1, const FString& arg2, const FString& arg3, int32 arg4, int32 arg5);*/
};
