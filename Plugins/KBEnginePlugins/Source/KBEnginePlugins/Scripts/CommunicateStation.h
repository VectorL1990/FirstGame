// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Engine/KBECommon.h"

#include "Engine/CommunicateStationBase.h"


class CommunicateStation : public CommunicateStationBase
{
public:
	CommunicateStation();
	virtual ~CommunicateStation();

public:
	virtual void __init__() override;
	virtual void onDestroy() override;

	virtual void dispatchLevelInfo(const PLAYER_SPAWN_POINT_LIST& arg1, const ENERMY_SPAWN_GROUP_LIST& arg2, const PHYSACTOR_SPAWN_LIST& arg3, const FString& arg4, const SPECIAL_FRAME_LIST& arg5) override;
	virtual void dispatchMainMachine(uint8 arg1) override;
	virtual void dispatchLogicFrame(const LOGIC_FRAME& arg1) override;
	virtual void dispatchMakeUpFrames(const LOGIC_FRAME_LIST& arg1) override;
	virtual void dispatchReadLevelResult(uint8 arg1) override;
	virtual void dispatchGeneralCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10) override;
	virtual void dispatchCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1) override;
	virtual void dispatchPolyCorrectInfo(const PHYSPOLY_INFO& arg1) override;
	virtual void dispatchLineCorrectInfo(const PHYSLINE_INFO& arg1) override;
	virtual void dispatchPointCorrectInfo(const PHYSPOINT_INFO& arg1) override;
	virtual void dispatchActorCorrectInfo(const PHYSACTOR_INFO& arg1) override;
	virtual void dispatchReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1) override;
	virtual void dispatchGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1) override;
	virtual void dispatchEndCorrectInfo() override;
	virtual void dispatchStopUploadCorrectInfo() override;
	virtual void dispatchNextRound(int8 arg1,const BYTE_LIST& arg2) override;
	virtual void dispatchBattleEnd(const BYTE_LIST& arg1, const BATTLE_RESULT& arg2) override;
	virtual void dispatchRelogonInfo(const FString& arg1, int32 arg2, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& arg3, const BATTLE_RESULT& arg4, int8 arg5, const FString& arg6) override;
	virtual void dispatchRelogonPlayerInfo(const PLAYER_INFO& arg1, const GOODS_LIST& arg2) override;
	virtual void dispatchBattleStart(int32 arg1) override;
	virtual void dispatchCalPrizeResult(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, const STRING_LIST& arg6) override;
	virtual void dispatchLostRoundInfo(const BATTLE_RESULT_ROUND_LIST& arg1) override;

	void reqTellRoomIsReady();
	void ReqLevelInfos(const FString& arg1, const FString& arg2);
	void ReqUploadFrame(int32 arg1);
	void ReqUploadOperation(const PLAYER_OPERATION_INFO& arg1);
	void reqUploadAIOperationList(const AI_CHARACTER_OPERATION_LIST& arg1);
	void reqMakeUpFrames(int32 arg1, int32 arg2);

	void ReqStartUploadCorrectInfo(int32 arg1, int32 arg2, int32 arg3, int32 arg4, int32 arg5, int32 arg6, int32 arg7, int32 arg8, const FString& arg9, int32 arg10);
	void ReqUploadActorCorrectInfo(const PHYSACTOR_INFO& arg1);
	void ReqUploadCharacterCorrectInfo(const CHARACTER_CORRECT_INFO& arg1);
	void ReqUploadEndCorrectInfo();
	void ReqUploadEnermyGroupCorrectInfo(const ENERMY_GROUP_CORRECT_INFO& arg1);
	void ReqUploadLineCorrectInfo(const PHYSLINE_INFO& arg1);
	void ReqUploadPointCorrectInfo(const PHYSPOINT_INFO& arg1);
	void ReqUploadPolyCorrectInfo(const PHYSPOLY_INFO& arg1);
	void ReqUploadReactionPairCorrectInfo(const REACTION_PAIR_INFO& arg1);
	void ReqCorrectInfo();
	void ReqTellRoundEnd(const BATTLE_RESULT_ROUND& arg1);
	void ReqExitBattle();
	void ReqTellRoomResetDone();
	void ReqTellLeaveWorld();

	void ReqRelogonInfo();
	void ReqLostRoundResult(const BYTE_LIST& arg1);
};
