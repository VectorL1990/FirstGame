#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

void DATATYPE_DBID_LIST::createFromStreamEx(MemoryStream& stream, DBID_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint64());
	};

}

void DATATYPE_DBID_LIST::addToStreamEx(Bundle& stream, const DBID_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint64(v[i]);
	};
}

void DATATYPE_INT8ARRAY::createFromStreamEx(MemoryStream& stream, INT8ARRAY& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt8());
	};

}

void DATATYPE_INT8ARRAY::addToStreamEx(Bundle& stream, const INT8ARRAY& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt8(v[i]);
	};
}

void DATATYPE_BYTE_LIST::createFromStreamEx(MemoryStream& stream, BYTE_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_BYTE_LIST::addToStreamEx(Bundle& stream, const BYTE_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_STRING_LIST::createFromStreamEx(MemoryStream& stream, STRING_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_STRING_LIST::addToStreamEx(Bundle& stream, const STRING_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_INT_LIST::createFromStreamEx(MemoryStream& stream, INT_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_INT_LIST::addToStreamEx(Bundle& stream, const INT_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_LOGIC_VECTOR::createFromStreamEx(MemoryStream& stream, LOGIC_VECTOR& datas)
{
	datas.num = stream.readInt32();
	datas.X = stream.readInt32();
	datas.Y = stream.readInt32();
}

void DATATYPE_LOGIC_VECTOR::addToStreamEx(Bundle& stream, const LOGIC_VECTOR& v)
{
	stream.writeInt32(v.num);
	stream.writeInt32(v.X);
	stream.writeInt32(v.Y);
}

void DATATYPE_PLAYER_TAG_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_TAG_INFO& datas)
{
	datas.playerName = stream.readString();
	datas.totalBattleNb = stream.readInt32();
	datas.totalWinNb = stream.readInt32();
	datas.headShotName = stream.readString();
}

void DATATYPE_PLAYER_TAG_INFO::addToStreamEx(Bundle& stream, const PLAYER_TAG_INFO& v)
{
	stream.writeString(v.playerName);
	stream.writeInt32(v.totalBattleNb);
	stream.writeInt32(v.totalWinNb);
	stream.writeString(v.headShotName);
}

void DATATYPE_PLAYER_TAG_INFO_LIST::createFromStreamEx(MemoryStream& stream, PLAYER_TAG_INFO_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_PLAYER_TAG_INFO_LIST::addToStreamEx(Bundle& stream, const PLAYER_TAG_INFO_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_FRIEND_LIST::createFromStreamEx(MemoryStream& stream, FRIEND_LIST& datas)
{
	dbidList_DataType.createFromStreamEx(stream, datas.dbidList);
	playerTagList_DataType.createFromStreamEx(stream, datas.playerTagList);
}

void DATATYPE_FRIEND_LIST::addToStreamEx(Bundle& stream, const FRIEND_LIST& v)
{
	dbidList_DataType.addToStreamEx(stream, v.dbidList);
	playerTagList_DataType.addToStreamEx(stream, v.playerTagList);
}

void DATATYPE_PLAYER_ENTITYCALL_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_ENTITYCALL_INFO& datas)
{
	datas.entityCall = stream.readPython();
	datas.entityID = stream.readInt32();
}

void DATATYPE_PLAYER_ENTITYCALL_INFO::addToStreamEx(Bundle& stream, const PLAYER_ENTITYCALL_INFO& v)
{
	stream.writePython(v.entityCall);
	stream.writeInt32(v.entityID);
}

void DATATYPE_PLAYER_ENTITYCALL_INFO_LIST::createFromStreamEx(MemoryStream& stream, PLAYER_ENTITYCALL_INFO_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_PLAYER_ENTITYCALL_INFO_LIST::addToStreamEx(Bundle& stream, const PLAYER_ENTITYCALL_INFO_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_CHARACTER_INFO::createFromStreamEx(MemoryStream& stream, CHARACTER_INFO& datas)
{
	datas.exp = stream.readInt32();
	datas.characterName = stream.readString();
	datas.level = stream.readInt8();
	datas.basicHp = stream.readInt32();
	datas.basicDFC = stream.readInt32();
	datas.basicMagDFC = stream.readInt32();
	datas.maxSPD = stream.readInt32();
	datas.acc = stream.readInt32();
}

void DATATYPE_CHARACTER_INFO::addToStreamEx(Bundle& stream, const CHARACTER_INFO& v)
{
	stream.writeInt32(v.exp);
	stream.writeString(v.characterName);
	stream.writeInt8(v.level);
	stream.writeInt32(v.basicHp);
	stream.writeInt32(v.basicDFC);
	stream.writeInt32(v.basicMagDFC);
	stream.writeInt32(v.maxSPD);
	stream.writeInt32(v.acc);
}

void DATATYPE_ECONOMY_INFO::createFromStreamEx(MemoryStream& stream, ECONOMY_INFO& datas)
{
	datas.moneyA = stream.readInt32();
	datas.moneyB = stream.readInt32();
}

void DATATYPE_ECONOMY_INFO::addToStreamEx(Bundle& stream, const ECONOMY_INFO& v)
{
	stream.writeInt32(v.moneyA);
	stream.writeInt32(v.moneyB);
}

void DATATYPE_WIN_PERCENT_INFO::createFromStreamEx(MemoryStream& stream, WIN_PERCENT_INFO& datas)
{
	datas.levelName = stream.readString();
	datas.winNb = stream.readInt32();
	datas.loseNb = stream.readInt32();
}

void DATATYPE_WIN_PERCENT_INFO::addToStreamEx(Bundle& stream, const WIN_PERCENT_INFO& v)
{
	stream.writeString(v.levelName);
	stream.writeInt32(v.winNb);
	stream.writeInt32(v.loseNb);
}

void DATATYPE_RANK_ONE_MAP::createFromStreamEx(MemoryStream& stream, RANK_ONE_MAP& datas)
{
	datas.mapType = stream.readString();
	datas.rank = stream.readInt32();
}

void DATATYPE_RANK_ONE_MAP::addToStreamEx(Bundle& stream, const RANK_ONE_MAP& v)
{
	stream.writeString(v.mapType);
	stream.writeInt32(v.rank);
}

void DATATYPE_PLAYER_ALL_RANK_LIST::createFromStreamEx(MemoryStream& stream, PLAYER_ALL_RANK_LIST& datas)
{
	singleRankList_DataType.createFromStreamEx(stream, datas.singleRankList);
	twoTwoRankList_DataType.createFromStreamEx(stream, datas.twoTwoRankList);
	threeThreeRankList_DataType.createFromStreamEx(stream, datas.threeThreeRankList);
}

void DATATYPE_PLAYER_ALL_RANK_LIST::addToStreamEx(Bundle& stream, const PLAYER_ALL_RANK_LIST& v)
{
	singleRankList_DataType.addToStreamEx(stream, v.singleRankList);
	twoTwoRankList_DataType.addToStreamEx(stream, v.twoTwoRankList);
	threeThreeRankList_DataType.addToStreamEx(stream, v.threeThreeRankList);
}

void DATATYPE_BATTLE_RESULT_ONE_TYPE::createFromStreamEx(MemoryStream& stream, BATTLE_RESULT_ONE_TYPE& datas)
{
	datas.battleType = stream.readString();
	datas.winNb = stream.readInt32();
	datas.totalBattleNb = stream.readInt32();
	datas.killEnermyNb = stream.readInt32();
	datas.positiveScore = stream.readInt32();
	datas.negativeScore = stream.readInt32();
}

void DATATYPE_BATTLE_RESULT_ONE_TYPE::addToStreamEx(Bundle& stream, const BATTLE_RESULT_ONE_TYPE& v)
{
	stream.writeString(v.battleType);
	stream.writeInt32(v.winNb);
	stream.writeInt32(v.totalBattleNb);
	stream.writeInt32(v.killEnermyNb);
	stream.writeInt32(v.positiveScore);
	stream.writeInt32(v.negativeScore);
}

void DATATYPE_BATTLE_RESULT_ONE_MAP::createFromStreamEx(MemoryStream& stream, BATTLE_RESULT_ONE_MAP& datas)
{
	datas.mapType = stream.readString();
	resultAllTypes_DataType.createFromStreamEx(stream, datas.resultAllTypes);
}

void DATATYPE_BATTLE_RESULT_ONE_MAP::addToStreamEx(Bundle& stream, const BATTLE_RESULT_ONE_MAP& v)
{
	stream.writeString(v.mapType);
	resultAllTypes_DataType.addToStreamEx(stream, v.resultAllTypes);
}

void DATATYPE_ADDITION_EFFECT::createFromStreamEx(MemoryStream& stream, ADDITION_EFFECT& datas)
{
	datas.hpModifyPercent = stream.readInt8();
	datas.physAtkModifyPercent = stream.readInt8();
	datas.magAtkModifyPercent = stream.readInt8();
	datas.physDfcModifyPercent = stream.readInt8();
	datas.magDfcModifyPercent = stream.readInt8();
	datas.modifyAttribute = stream.readString();
}

void DATATYPE_ADDITION_EFFECT::addToStreamEx(Bundle& stream, const ADDITION_EFFECT& v)
{
	stream.writeInt8(v.hpModifyPercent);
	stream.writeInt8(v.physAtkModifyPercent);
	stream.writeInt8(v.magAtkModifyPercent);
	stream.writeInt8(v.physDfcModifyPercent);
	stream.writeInt8(v.magDfcModifyPercent);
	stream.writeString(v.modifyAttribute);
}

void DATATYPE_RUNEINFO::createFromStreamEx(MemoryStream& stream, RUNEINFO& datas)
{
	datas.RuneName = stream.readString();
	datas.RuneCount = stream.readUint8();
	datas.RuneTag = stream.readUint8();
}

void DATATYPE_RUNEINFO::addToStreamEx(Bundle& stream, const RUNEINFO& v)
{
	stream.writeString(v.RuneName);
	stream.writeUint8(v.RuneCount);
	stream.writeUint8(v.RuneTag);
}

void DATATYPE_RUNEINFOLIST::createFromStreamEx(MemoryStream& stream, RUNEINFOLIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_RUNEINFOLIST::addToStreamEx(Bundle& stream, const RUNEINFOLIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_RUNECONFIGINFO::createFromStreamEx(MemoryStream& stream, RUNECONFIGINFO& datas)
{
	datas.RuneConfigName = stream.readString();
	datas.Sky = stream.readUint8();
	datas.Ground = stream.readUint8();
	datas.Life = stream.readUint8();
	datas.Death = stream.readUint8();
}

void DATATYPE_RUNECONFIGINFO::addToStreamEx(Bundle& stream, const RUNECONFIGINFO& v)
{
	stream.writeString(v.RuneConfigName);
	stream.writeUint8(v.Sky);
	stream.writeUint8(v.Ground);
	stream.writeUint8(v.Life);
	stream.writeUint8(v.Death);
}

void DATATYPE_RUNECONFIGINFOLIST::createFromStreamEx(MemoryStream& stream, RUNECONFIGINFOLIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_RUNECONFIGINFOLIST::addToStreamEx(Bundle& stream, const RUNECONFIGINFOLIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_PLAYER_RUNE_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_RUNE_INFO& datas)
{
	hasRuneList_DataType.createFromStreamEx(stream, datas.hasRuneList);
	datas.curRuneConfigNb = stream.readUint8();
}

void DATATYPE_PLAYER_RUNE_INFO::addToStreamEx(Bundle& stream, const PLAYER_RUNE_INFO& v)
{
	hasRuneList_DataType.addToStreamEx(stream, v.hasRuneList);
	stream.writeUint8(v.curRuneConfigNb);
}

void DATATYPE_PLAYER_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_INFO& datas)
{
	datas.playerName = stream.readString();
	friendList_DataType.createFromStreamEx(stream, datas.friendList);
	characterList_DataType.createFromStreamEx(stream, datas.characterList);
	winPercentInfoList_DataType.createFromStreamEx(stream, datas.winPercentInfoList);
	titleList_DataType.createFromStreamEx(stream, datas.titleList);
	economyInfo_DataType.createFromStreamEx(stream, datas.economyInfo);
	haveGoodsList_DataType.createFromStreamEx(stream, datas.haveGoodsList);
	totalBattleResults_DataType.createFromStreamEx(stream, datas.totalBattleResults);
	playerAllRankList_DataType.createFromStreamEx(stream, datas.playerAllRankList);
	datas.lastSelectRoleType = stream.readString();
	datas.headShotName = stream.readString();
	additionEffect_DataType.createFromStreamEx(stream, datas.additionEffect);
	runeInfo_DataType.createFromStreamEx(stream, datas.runeInfo);
}

void DATATYPE_PLAYER_INFO::addToStreamEx(Bundle& stream, const PLAYER_INFO& v)
{
	stream.writeString(v.playerName);
	friendList_DataType.addToStreamEx(stream, v.friendList);
	characterList_DataType.addToStreamEx(stream, v.characterList);
	winPercentInfoList_DataType.addToStreamEx(stream, v.winPercentInfoList);
	titleList_DataType.addToStreamEx(stream, v.titleList);
	economyInfo_DataType.addToStreamEx(stream, v.economyInfo);
	haveGoodsList_DataType.addToStreamEx(stream, v.haveGoodsList);
	totalBattleResults_DataType.addToStreamEx(stream, v.totalBattleResults);
	playerAllRankList_DataType.addToStreamEx(stream, v.playerAllRankList);
	stream.writeString(v.lastSelectRoleType);
	stream.writeString(v.headShotName);
	additionEffect_DataType.addToStreamEx(stream, v.additionEffect);
	runeInfo_DataType.addToStreamEx(stream, v.runeInfo);
}

void DATATYPE_REQ_MATCH_PLAYER_DATA::createFromStreamEx(MemoryStream& stream, REQ_MATCH_PLAYER_DATA& datas)
{
	datas.accountID = stream.readInt32();
	datas.roleType = stream.readString();
	datas.rank = stream.readInt32();
}

void DATATYPE_REQ_MATCH_PLAYER_DATA::addToStreamEx(Bundle& stream, const REQ_MATCH_PLAYER_DATA& v)
{
	stream.writeInt32(v.accountID);
	stream.writeString(v.roleType);
	stream.writeInt32(v.rank);
}

void DATATYPE_REQ_MATCH_PLAYER_DATA_LIST::createFromStreamEx(MemoryStream& stream, REQ_MATCH_PLAYER_DATA_LIST& datas)
{
	datas.mapType = stream.readString();
	datas.maxPlayerNbOneRoom = stream.readInt8();
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_REQ_MATCH_PLAYER_DATA_LIST::addToStreamEx(Bundle& stream, const REQ_MATCH_PLAYER_DATA_LIST& v)
{
	stream.writeString(v.mapType);
	stream.writeInt8(v.maxPlayerNbOneRoom);
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_REQ_TEAM_MATCH_DATA::createFromStreamEx(MemoryStream& stream, REQ_TEAM_MATCH_DATA& datas)
{
	datas.playerName = stream.readString();
	datas.playerEntityID = stream.readInt32();
	datas.playerRoleType = stream.readString();
	datas.matchStatus = stream.readString();
}

void DATATYPE_REQ_TEAM_MATCH_DATA::addToStreamEx(Bundle& stream, const REQ_TEAM_MATCH_DATA& v)
{
	stream.writeString(v.playerName);
	stream.writeInt32(v.playerEntityID);
	stream.writeString(v.playerRoleType);
	stream.writeString(v.matchStatus);
}

void DATATYPE_REQ_TEAM_MATCH_RANK_INFO::createFromStreamEx(MemoryStream& stream, REQ_TEAM_MATCH_RANK_INFO& datas)
{
	datas.playerName = stream.readString();
	datas.rank = stream.readInt32();
}

void DATATYPE_REQ_TEAM_MATCH_RANK_INFO::addToStreamEx(Bundle& stream, const REQ_TEAM_MATCH_RANK_INFO& v)
{
	stream.writeString(v.playerName);
	stream.writeInt32(v.rank);
}

void DATATYPE_REQ_TEAM_MATCH_APPLICATION::createFromStreamEx(MemoryStream& stream, REQ_TEAM_MATCH_APPLICATION& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
	datas.isValid = stream.readUint8();
	datas.accumulateTime = stream.readInt32();
	datas.mapType = stream.readString();
	datas.groupNb = stream.readInt32();
	rankInfoList_DataType.createFromStreamEx(stream, datas.rankInfoList);
}

void DATATYPE_REQ_TEAM_MATCH_APPLICATION::addToStreamEx(Bundle& stream, const REQ_TEAM_MATCH_APPLICATION& v)
{
	values_DataType.addToStreamEx(stream, v.values);
	stream.writeUint8(v.isValid);
	stream.writeInt32(v.accumulateTime);
	stream.writeString(v.mapType);
	stream.writeInt32(v.groupNb);
	rankInfoList_DataType.addToStreamEx(stream, v.rankInfoList);
}

void DATATYPE_REQ_MATCH_TWO_TWO_DATA::createFromStreamEx(MemoryStream& stream, REQ_MATCH_TWO_TWO_DATA& datas)
{
	datas.accountID = stream.readInt32();
	playerMatchData1_DataType.createFromStreamEx(stream, datas.playerMatchData1);
	playerMatchData2_DataType.createFromStreamEx(stream, datas.playerMatchData2);
	datas.rank = stream.readInt32();
}

void DATATYPE_REQ_MATCH_TWO_TWO_DATA::addToStreamEx(Bundle& stream, const REQ_MATCH_TWO_TWO_DATA& v)
{
	stream.writeInt32(v.accountID);
	playerMatchData1_DataType.addToStreamEx(stream, v.playerMatchData1);
	playerMatchData2_DataType.addToStreamEx(stream, v.playerMatchData2);
	stream.writeInt32(v.rank);
}

void DATATYPE_REQ_MATCH_TWO_TWO_DATA_LIST::createFromStreamEx(MemoryStream& stream, REQ_MATCH_TWO_TWO_DATA_LIST& datas)
{
	datas.mapType = stream.readString();
	datas.maxCampNb = stream.readInt8();
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_REQ_MATCH_TWO_TWO_DATA_LIST::addToStreamEx(Bundle& stream, const REQ_MATCH_TWO_TWO_DATA_LIST& v)
{
	stream.writeString(v.mapType);
	stream.writeInt8(v.maxCampNb);
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_REQ_MATCH_THREE_THREE_DATA::createFromStreamEx(MemoryStream& stream, REQ_MATCH_THREE_THREE_DATA& datas)
{
	datas.accountID = stream.readInt32();
	playerMatchData1_DataType.createFromStreamEx(stream, datas.playerMatchData1);
	playerMatchData2_DataType.createFromStreamEx(stream, datas.playerMatchData2);
	playerMatchData3_DataType.createFromStreamEx(stream, datas.playerMatchData3);
	datas.rank = stream.readInt32();
}

void DATATYPE_REQ_MATCH_THREE_THREE_DATA::addToStreamEx(Bundle& stream, const REQ_MATCH_THREE_THREE_DATA& v)
{
	stream.writeInt32(v.accountID);
	playerMatchData1_DataType.addToStreamEx(stream, v.playerMatchData1);
	playerMatchData2_DataType.addToStreamEx(stream, v.playerMatchData2);
	playerMatchData3_DataType.addToStreamEx(stream, v.playerMatchData3);
	stream.writeInt32(v.rank);
}

void DATATYPE_REQ_MATCH_THREE_THREE_DATA_LIST::createFromStreamEx(MemoryStream& stream, REQ_MATCH_THREE_THREE_DATA_LIST& datas)
{
	datas.mapType = stream.readString();
	datas.maxCampNb = stream.readInt8();
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_REQ_MATCH_THREE_THREE_DATA_LIST::addToStreamEx(Bundle& stream, const REQ_MATCH_THREE_THREE_DATA_LIST& v)
{
	stream.writeString(v.mapType);
	stream.writeInt8(v.maxCampNb);
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_REQ_MATCH_LIST_ALL_MAPS::createFromStreamEx(MemoryStream& stream, REQ_MATCH_LIST_ALL_MAPS& datas)
{
	datas.isMatchOneRound = stream.readUint8();
	simpleSingleList_DataType.createFromStreamEx(stream, datas.simpleSingleList);
	singleList_DataType.createFromStreamEx(stream, datas.singleList);
	oneOneList_DataType.createFromStreamEx(stream, datas.oneOneList);
	twoTwoList_DataType.createFromStreamEx(stream, datas.twoTwoList);
	threeThreeList_DataType.createFromStreamEx(stream, datas.threeThreeList);
}

void DATATYPE_REQ_MATCH_LIST_ALL_MAPS::addToStreamEx(Bundle& stream, const REQ_MATCH_LIST_ALL_MAPS& v)
{
	stream.writeUint8(v.isMatchOneRound);
	simpleSingleList_DataType.addToStreamEx(stream, v.simpleSingleList);
	singleList_DataType.addToStreamEx(stream, v.singleList);
	oneOneList_DataType.addToStreamEx(stream, v.oneOneList);
	twoTwoList_DataType.addToStreamEx(stream, v.twoTwoList);
	threeThreeList_DataType.addToStreamEx(stream, v.threeThreeList);
}

void DATATYPE_MATCHED_PLAYER_LIST_ONE_ROOM::createFromStreamEx(MemoryStream& stream, MATCHED_PLAYER_LIST_ONE_ROOM& datas)
{
	datas.roomKey = stream.readInt32();
	players_DataType.createFromStreamEx(stream, datas.players);
}

void DATATYPE_MATCHED_PLAYER_LIST_ONE_ROOM::addToStreamEx(Bundle& stream, const MATCHED_PLAYER_LIST_ONE_ROOM& v)
{
	stream.writeInt32(v.roomKey);
	players_DataType.addToStreamEx(stream, v.players);
}

void DATATYPE_MATCHED_PLAYER_TEAM::createFromStreamEx(MemoryStream& stream, MATCHED_PLAYER_TEAM& datas)
{
	datas.teamID = stream.readInt32();
	playerIDList_DataType.createFromStreamEx(stream, datas.playerIDList);
}

void DATATYPE_MATCHED_PLAYER_TEAM::addToStreamEx(Bundle& stream, const MATCHED_PLAYER_TEAM& v)
{
	stream.writeInt32(v.teamID);
	playerIDList_DataType.addToStreamEx(stream, v.playerIDList);
}

void DATATYPE_MATCHED_TWO_TWO_LIST_ONE_ROOM::createFromStreamEx(MemoryStream& stream, MATCHED_TWO_TWO_LIST_ONE_ROOM& datas)
{
	datas.roomKey = stream.readInt32();
	teams_DataType.createFromStreamEx(stream, datas.teams);
}

void DATATYPE_MATCHED_TWO_TWO_LIST_ONE_ROOM::addToStreamEx(Bundle& stream, const MATCHED_TWO_TWO_LIST_ONE_ROOM& v)
{
	stream.writeInt32(v.roomKey);
	teams_DataType.addToStreamEx(stream, v.teams);
}

void DATATYPE_MATCHED_THREE_THREE_LIST_ONE_ROOM::createFromStreamEx(MemoryStream& stream, MATCHED_THREE_THREE_LIST_ONE_ROOM& datas)
{
	datas.roomKey = stream.readInt32();
	teams_DataType.createFromStreamEx(stream, datas.teams);
}

void DATATYPE_MATCHED_THREE_THREE_LIST_ONE_ROOM::addToStreamEx(Bundle& stream, const MATCHED_THREE_THREE_LIST_ONE_ROOM& v)
{
	stream.writeInt32(v.roomKey);
	teams_DataType.addToStreamEx(stream, v.teams);
}

void DATATYPE_MATCHED_ROOM_LIST::createFromStreamEx(MemoryStream& stream, MATCHED_ROOM_LIST& datas)
{
	datas.mapType = stream.readString();
	roomList_DataType.createFromStreamEx(stream, datas.roomList);
	simpleSingleList_DataType.createFromStreamEx(stream, datas.simpleSingleList);
	oneOneList_DataType.createFromStreamEx(stream, datas.oneOneList);
	twoTwoList_DataType.createFromStreamEx(stream, datas.twoTwoList);
	threeThreeList_DataType.createFromStreamEx(stream, datas.threeThreeList);
}

void DATATYPE_MATCHED_ROOM_LIST::addToStreamEx(Bundle& stream, const MATCHED_ROOM_LIST& v)
{
	stream.writeString(v.mapType);
	roomList_DataType.addToStreamEx(stream, v.roomList);
	simpleSingleList_DataType.addToStreamEx(stream, v.simpleSingleList);
	oneOneList_DataType.addToStreamEx(stream, v.oneOneList);
	twoTwoList_DataType.addToStreamEx(stream, v.twoTwoList);
	threeThreeList_DataType.addToStreamEx(stream, v.threeThreeList);
}

void DATATYPE_MATCHED_LIST_ALL_MAPS::createFromStreamEx(MemoryStream& stream, MATCHED_LIST_ALL_MAPS& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_MATCHED_LIST_ALL_MAPS::addToStreamEx(Bundle& stream, const MATCHED_LIST_ALL_MAPS& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_SKILL_INFO::createFromStreamEx(MemoryStream& stream, SKILL_INFO& datas)
{
	datas.skillName = stream.readString();
	datas.canImplement = stream.readUint8();
	datas.curFreezeFrame = stream.readInt32();
	datas.hasSpawnGeo = stream.readUint8();
}

void DATATYPE_SKILL_INFO::addToStreamEx(Bundle& stream, const SKILL_INFO& v)
{
	stream.writeString(v.skillName);
	stream.writeUint8(v.canImplement);
	stream.writeInt32(v.curFreezeFrame);
	stream.writeUint8(v.hasSpawnGeo);
}

void DATATYPE_EQUIPMENT_INFO::createFromStreamEx(MemoryStream& stream, EQUIPMENT_INFO& datas)
{
	datas.equipmentName = stream.readString();
	skillInfoList_DataType.createFromStreamEx(stream, datas.skillInfoList);
}

void DATATYPE_EQUIPMENT_INFO::addToStreamEx(Bundle& stream, const EQUIPMENT_INFO& v)
{
	stream.writeString(v.equipmentName);
	skillInfoList_DataType.addToStreamEx(stream, v.skillInfoList);
}

void DATATYPE_EFFECT_INFO::createFromStreamEx(MemoryStream& stream, EFFECT_INFO& datas)
{
	datas.isInitial = stream.readUint8();
	datas.effectName = stream.readString();
	datas.curTickTime = stream.readInt32();
	datas.originalGeoID = stream.readInt32();
	datas.hostID = stream.readInt32();
	datas.isOnTimeEffectDone = stream.readUint8();
	datas.isDeriveEffect = stream.readUint8();
	subHostIDList_DataType.createFromStreamEx(stream, datas.subHostIDList);
}

void DATATYPE_EFFECT_INFO::addToStreamEx(Bundle& stream, const EFFECT_INFO& v)
{
	stream.writeUint8(v.isInitial);
	stream.writeString(v.effectName);
	stream.writeInt32(v.curTickTime);
	stream.writeInt32(v.originalGeoID);
	stream.writeInt32(v.hostID);
	stream.writeUint8(v.isOnTimeEffectDone);
	stream.writeUint8(v.isDeriveEffect);
	subHostIDList_DataType.addToStreamEx(stream, v.subHostIDList);
}

void DATATYPE_CHARACTER_CORRECT_INFO::createFromStreamEx(MemoryStream& stream, CHARACTER_CORRECT_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.Hp = stream.readInt32();
	datas.DFC = stream.readInt32();
	datas.magDFC = stream.readInt32();
	datas.ATKPercent = stream.readInt32();
	datas.DFCPercent = stream.readInt32();
	datas.magDFCPercent = stream.readInt32();
	datas.maxSPD = stream.readInt32();
	datas.campFlag = stream.readUint8();
	datas.isInitialDone = stream.readUint8();
	equipInfoList_DataType.createFromStreamEx(stream, datas.equipInfoList);
	carrySkillNames_DataType.createFromStreamEx(stream, datas.carrySkillNames);
	datas.defRadius = stream.readInt32();
	datas.defLocX = stream.readInt32();
	datas.defLocY = stream.readInt32();
	datas.speedRatePercent = stream.readInt32();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	effects_DataType.createFromStreamEx(stream, datas.effects);
	datas.velocityX = stream.readInt32();
	datas.velocityY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.equipmentNb = stream.readInt8();
	datas.curSkillNb = stream.readInt8();
	datas.curMotionType = stream.readString();
	datas.isDoingContinuousSkill = stream.readUint8();
	controlGeoIDs_DataType.createFromStreamEx(stream, datas.controlGeoIDs);
	datas.actionName = stream.readString();
	datas.className = stream.readString();
}

void DATATYPE_CHARACTER_CORRECT_INFO::addToStreamEx(Bundle& stream, const CHARACTER_CORRECT_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.Hp);
	stream.writeInt32(v.DFC);
	stream.writeInt32(v.magDFC);
	stream.writeInt32(v.ATKPercent);
	stream.writeInt32(v.DFCPercent);
	stream.writeInt32(v.magDFCPercent);
	stream.writeInt32(v.maxSPD);
	stream.writeUint8(v.campFlag);
	stream.writeUint8(v.isInitialDone);
	equipInfoList_DataType.addToStreamEx(stream, v.equipInfoList);
	carrySkillNames_DataType.addToStreamEx(stream, v.carrySkillNames);
	stream.writeInt32(v.defRadius);
	stream.writeInt32(v.defLocX);
	stream.writeInt32(v.defLocY);
	stream.writeInt32(v.speedRatePercent);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	effects_DataType.addToStreamEx(stream, v.effects);
	stream.writeInt32(v.velocityX);
	stream.writeInt32(v.velocityY);
	stream.writeInt32(v.yaw);
	stream.writeInt8(v.equipmentNb);
	stream.writeInt8(v.curSkillNb);
	stream.writeString(v.curMotionType);
	stream.writeUint8(v.isDoingContinuousSkill);
	controlGeoIDs_DataType.addToStreamEx(stream, v.controlGeoIDs);
	stream.writeString(v.actionName);
	stream.writeString(v.className);
}

void DATATYPE_PHYSLINE_INFO::createFromStreamEx(MemoryStream& stream, PHYSLINE_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.hostID = stream.readInt32();
	datas.className = stream.readString();
	datas.hierachy = stream.readUint8();
	rootGeoIDs_DataType.createFromStreamEx(stream, datas.rootGeoIDs);
	sonGeoIDs_DataType.createFromStreamEx(stream, datas.sonGeoIDs);
	secondaryGeoIDs_DataType.createFromStreamEx(stream, datas.secondaryGeoIDs);
	datas.campFlag = stream.readUint8();
	reactionInfoNbs_DataType.createFromStreamEx(stream, datas.reactionInfoNbs);
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.startPointX = stream.readInt32();
	datas.startPointY = stream.readInt32();
	datas.endPointX = stream.readInt32();
	datas.endPointY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.cutStuffName = stream.readString();
	datas.hitCharacterID = stream.readInt32();
	datas.preHitGeoID = stream.readInt32();
	datas.preHitComponentName = stream.readString();
	datas.preHitActorName = stream.readString();
	datas.isDead = stream.readUint8();
	datas.ATKPercent = stream.readInt32();
	datas.moveType = stream.readInt8();
	moveOrder_DataType.createFromStreamEx(stream, datas.moveOrder);
	rotateOrder_DataType.createFromStreamEx(stream, datas.rotateOrder);
	datas.curMovePointNb = stream.readInt8();
	datas.curRotateNb = stream.readInt8();
	datas.curRandTargetX = stream.readInt32();
	datas.curRandTargetY = stream.readInt32();
	overlapGeoIDs_DataType.createFromStreamEx(stream, datas.overlapGeoIDs);
	attributeTags_DataType.createFromStreamEx(stream, datas.attributeTags);
}

void DATATYPE_PHYSLINE_INFO::addToStreamEx(Bundle& stream, const PHYSLINE_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.hostID);
	stream.writeString(v.className);
	stream.writeUint8(v.hierachy);
	rootGeoIDs_DataType.addToStreamEx(stream, v.rootGeoIDs);
	sonGeoIDs_DataType.addToStreamEx(stream, v.sonGeoIDs);
	secondaryGeoIDs_DataType.addToStreamEx(stream, v.secondaryGeoIDs);
	stream.writeUint8(v.campFlag);
	reactionInfoNbs_DataType.addToStreamEx(stream, v.reactionInfoNbs);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.startPointX);
	stream.writeInt32(v.startPointY);
	stream.writeInt32(v.endPointX);
	stream.writeInt32(v.endPointY);
	stream.writeInt32(v.yaw);
	stream.writeString(v.cutStuffName);
	stream.writeInt32(v.hitCharacterID);
	stream.writeInt32(v.preHitGeoID);
	stream.writeString(v.preHitComponentName);
	stream.writeString(v.preHitActorName);
	stream.writeUint8(v.isDead);
	stream.writeInt32(v.ATKPercent);
	stream.writeInt8(v.moveType);
	moveOrder_DataType.addToStreamEx(stream, v.moveOrder);
	rotateOrder_DataType.addToStreamEx(stream, v.rotateOrder);
	stream.writeInt8(v.curMovePointNb);
	stream.writeInt8(v.curRotateNb);
	stream.writeInt32(v.curRandTargetX);
	stream.writeInt32(v.curRandTargetY);
	overlapGeoIDs_DataType.addToStreamEx(stream, v.overlapGeoIDs);
	attributeTags_DataType.addToStreamEx(stream, v.attributeTags);
}

void DATATYPE_PHYSPOLY_INFO::createFromStreamEx(MemoryStream& stream, PHYSPOLY_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.hostID = stream.readInt32();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.className = stream.readString();
	datas.hierachy = stream.readUint8();
	rootGeoIDs_DataType.createFromStreamEx(stream, datas.rootGeoIDs);
	sonGeoIDs_DataType.createFromStreamEx(stream, datas.sonGeoIDs);
	secondarySonGeoIDs_DataType.createFromStreamEx(stream, datas.secondarySonGeoIDs);
	datas.campFlag = stream.readUint8();
	reactionInfoNbs_DataType.createFromStreamEx(stream, datas.reactionInfoNbs);
	datas.isDead = stream.readUint8();
	preOverlapCharacterIDs_DataType.createFromStreamEx(stream, datas.preOverlapCharacterIDs);
	overlapCharacterIDs_DataType.createFromStreamEx(stream, datas.overlapCharacterIDs);
	preOverlapGeoIDs_DataType.createFromStreamEx(stream, datas.preOverlapGeoIDs);
	overlapGeoIDs_DataType.createFromStreamEx(stream, datas.overlapGeoIDs);
	datas.curLifeTime = stream.readInt32();
	datas.ATKPercent = stream.readInt32();
	datas.moveType = stream.readInt8();
	moveOrder_DataType.createFromStreamEx(stream, datas.moveOrder);
	rotateOrder_DataType.createFromStreamEx(stream, datas.rotateOrder);
	datas.curMovePointNb = stream.readInt8();
	datas.curRotateNb = stream.readInt8();
	datas.curRandTargetX = stream.readInt32();
	datas.curRandTargetY = stream.readInt32();
	attributeTags_DataType.createFromStreamEx(stream, datas.attributeTags);
}

void DATATYPE_PHYSPOLY_INFO::addToStreamEx(Bundle& stream, const PHYSPOLY_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.hostID);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.yaw);
	stream.writeString(v.className);
	stream.writeUint8(v.hierachy);
	rootGeoIDs_DataType.addToStreamEx(stream, v.rootGeoIDs);
	sonGeoIDs_DataType.addToStreamEx(stream, v.sonGeoIDs);
	secondarySonGeoIDs_DataType.addToStreamEx(stream, v.secondarySonGeoIDs);
	stream.writeUint8(v.campFlag);
	reactionInfoNbs_DataType.addToStreamEx(stream, v.reactionInfoNbs);
	stream.writeUint8(v.isDead);
	preOverlapCharacterIDs_DataType.addToStreamEx(stream, v.preOverlapCharacterIDs);
	overlapCharacterIDs_DataType.addToStreamEx(stream, v.overlapCharacterIDs);
	preOverlapGeoIDs_DataType.addToStreamEx(stream, v.preOverlapGeoIDs);
	overlapGeoIDs_DataType.addToStreamEx(stream, v.overlapGeoIDs);
	stream.writeInt32(v.curLifeTime);
	stream.writeInt32(v.ATKPercent);
	stream.writeInt8(v.moveType);
	moveOrder_DataType.addToStreamEx(stream, v.moveOrder);
	rotateOrder_DataType.addToStreamEx(stream, v.rotateOrder);
	stream.writeInt8(v.curMovePointNb);
	stream.writeInt8(v.curRotateNb);
	stream.writeInt32(v.curRandTargetX);
	stream.writeInt32(v.curRandTargetY);
	attributeTags_DataType.addToStreamEx(stream, v.attributeTags);
}

void DATATYPE_PHYSPOINT_INFO::createFromStreamEx(MemoryStream& stream, PHYSPOINT_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.hostID = stream.readInt32();
	datas.className = stream.readString();
	datas.hierachy = stream.readUint8();
	rootGeoIDs_DataType.createFromStreamEx(stream, datas.rootGeoIDs);
	sonGeoIDs_DataType.createFromStreamEx(stream, datas.sonGeoIDs);
	secondarySonGeoIDs_DataType.createFromStreamEx(stream, datas.secondarySonGeoIDs);
	datas.campFlag = stream.readUint8();
	reactionInfoNbs_DataType.createFromStreamEx(stream, datas.reactionInfoNbs);
	datas.yaw = stream.readInt32();
	datas.fireDirZ = stream.readInt32();
	datas.locX = stream.readInt32();
	datas.locY = stream.readInt32();
	datas.locZ = stream.readInt32();
	datas.curLifeTime = stream.readInt32();
	overlapCharacterIDs_DataType.createFromStreamEx(stream, datas.overlapCharacterIDs);
	preOverlapCharacterIDs_DataType.createFromStreamEx(stream, datas.preOverlapCharacterIDs);
	preOverlapGeoIDs_DataType.createFromStreamEx(stream, datas.preOverlapGeoIDs);
	overlapGeoIDs_DataType.createFromStreamEx(stream, datas.overlapGeoIDs);
	datas.isDead = stream.readUint8();
	datas.ATKPercent = stream.readInt32();
	datas.moveType = stream.readInt8();
	moveOrder_DataType.createFromStreamEx(stream, datas.moveOrder);
	rotateOrder_DataType.createFromStreamEx(stream, datas.rotateOrder);
	datas.curMovePointNb = stream.readInt8();
	datas.curRotateNb = stream.readInt8();
	datas.curRandTargetX = stream.readInt32();
	datas.curRandTargetY = stream.readInt32();
	attributeTags_DataType.createFromStreamEx(stream, datas.attributeTags);
}

void DATATYPE_PHYSPOINT_INFO::addToStreamEx(Bundle& stream, const PHYSPOINT_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.hostID);
	stream.writeString(v.className);
	stream.writeUint8(v.hierachy);
	rootGeoIDs_DataType.addToStreamEx(stream, v.rootGeoIDs);
	sonGeoIDs_DataType.addToStreamEx(stream, v.sonGeoIDs);
	secondarySonGeoIDs_DataType.addToStreamEx(stream, v.secondarySonGeoIDs);
	stream.writeUint8(v.campFlag);
	reactionInfoNbs_DataType.addToStreamEx(stream, v.reactionInfoNbs);
	stream.writeInt32(v.yaw);
	stream.writeInt32(v.fireDirZ);
	stream.writeInt32(v.locX);
	stream.writeInt32(v.locY);
	stream.writeInt32(v.locZ);
	stream.writeInt32(v.curLifeTime);
	overlapCharacterIDs_DataType.addToStreamEx(stream, v.overlapCharacterIDs);
	preOverlapCharacterIDs_DataType.addToStreamEx(stream, v.preOverlapCharacterIDs);
	preOverlapGeoIDs_DataType.addToStreamEx(stream, v.preOverlapGeoIDs);
	overlapGeoIDs_DataType.addToStreamEx(stream, v.overlapGeoIDs);
	stream.writeUint8(v.isDead);
	stream.writeInt32(v.ATKPercent);
	stream.writeInt8(v.moveType);
	moveOrder_DataType.addToStreamEx(stream, v.moveOrder);
	rotateOrder_DataType.addToStreamEx(stream, v.rotateOrder);
	stream.writeInt8(v.curMovePointNb);
	stream.writeInt8(v.curRotateNb);
	stream.writeInt32(v.curRandTargetX);
	stream.writeInt32(v.curRandTargetY);
	attributeTags_DataType.addToStreamEx(stream, v.attributeTags);
}

void DATATYPE_PHYSACTOR_INFO::createFromStreamEx(MemoryStream& stream, PHYSACTOR_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.hostID = stream.readInt32();
	datas.className = stream.readString();
	datas.hierachy = stream.readUint8();
	rootGeoIDs_DataType.createFromStreamEx(stream, datas.rootGeoIDs);
	sonGeoIDs_DataType.createFromStreamEx(stream, datas.sonGeoIDs);
	secondarySonGeoIDs_DataType.createFromStreamEx(stream, datas.secondarySonGeoIDs);
	datas.campFlag = stream.readUint8();
	reactionInfoNbs_DataType.createFromStreamEx(stream, datas.reactionInfoNbs);
	datas.locX = stream.readInt32();
	datas.locY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.curLifeTime = stream.readInt32();
	overlapCharacterIDs_DataType.createFromStreamEx(stream, datas.overlapCharacterIDs);
	preOverlapCharacterIDs_DataType.createFromStreamEx(stream, datas.preOverlapCharacterIDs);
	preOverlapGeoIDs_DataType.createFromStreamEx(stream, datas.preOverlapGeoIDs);
	overlapGeoIDs_DataType.createFromStreamEx(stream, datas.overlapGeoIDs);
	datas.isDead = stream.readUint8();
	datas.ATKPercent = stream.readInt32();
	datas.moveType = stream.readInt8();
	moveOrder_DataType.createFromStreamEx(stream, datas.moveOrder);
	rotateOrder_DataType.createFromStreamEx(stream, datas.rotateOrder);
	datas.curMovePointNb = stream.readInt8();
	datas.curRotateNb = stream.readInt8();
	datas.curRandTargetX = stream.readInt32();
	datas.curRandTargetY = stream.readInt32();
	attributeTags_DataType.createFromStreamEx(stream, datas.attributeTags);
}

void DATATYPE_PHYSACTOR_INFO::addToStreamEx(Bundle& stream, const PHYSACTOR_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.hostID);
	stream.writeString(v.className);
	stream.writeUint8(v.hierachy);
	rootGeoIDs_DataType.addToStreamEx(stream, v.rootGeoIDs);
	sonGeoIDs_DataType.addToStreamEx(stream, v.sonGeoIDs);
	secondarySonGeoIDs_DataType.addToStreamEx(stream, v.secondarySonGeoIDs);
	stream.writeUint8(v.campFlag);
	reactionInfoNbs_DataType.addToStreamEx(stream, v.reactionInfoNbs);
	stream.writeInt32(v.locX);
	stream.writeInt32(v.locY);
	stream.writeInt32(v.yaw);
	stream.writeInt32(v.curLifeTime);
	overlapCharacterIDs_DataType.addToStreamEx(stream, v.overlapCharacterIDs);
	preOverlapCharacterIDs_DataType.addToStreamEx(stream, v.preOverlapCharacterIDs);
	preOverlapGeoIDs_DataType.addToStreamEx(stream, v.preOverlapGeoIDs);
	overlapGeoIDs_DataType.addToStreamEx(stream, v.overlapGeoIDs);
	stream.writeUint8(v.isDead);
	stream.writeInt32(v.ATKPercent);
	stream.writeInt8(v.moveType);
	moveOrder_DataType.addToStreamEx(stream, v.moveOrder);
	rotateOrder_DataType.addToStreamEx(stream, v.rotateOrder);
	stream.writeInt8(v.curMovePointNb);
	stream.writeInt8(v.curRotateNb);
	stream.writeInt32(v.curRandTargetX);
	stream.writeInt32(v.curRandTargetY);
	attributeTags_DataType.addToStreamEx(stream, v.attributeTags);
}

void DATATYPE_REACTION_INFO::createFromStreamEx(MemoryStream& stream, REACTION_INFO& datas)
{
	datas.reactionType = stream.readString();
	datas.hostTag = stream.readString();
	datas.reactionTag = stream.readString();
	datas.spawnActorClass = stream.readString();
	datas.transformActorClass1 = stream.readString();
	datas.transformActorClass2 = stream.readString();
	datas.modifyTag1 = stream.readString();
	datas.modifyTag2 = stream.readString();
}

void DATATYPE_REACTION_INFO::addToStreamEx(Bundle& stream, const REACTION_INFO& v)
{
	stream.writeString(v.reactionType);
	stream.writeString(v.hostTag);
	stream.writeString(v.reactionTag);
	stream.writeString(v.spawnActorClass);
	stream.writeString(v.transformActorClass1);
	stream.writeString(v.transformActorClass2);
	stream.writeString(v.modifyTag1);
	stream.writeString(v.modifyTag2);
}

void DATATYPE_REACTION_PAIR_INFO::createFromStreamEx(MemoryStream& stream, REACTION_PAIR_INFO& datas)
{
	datas.reactionPairID = stream.readInt32();
	datas.reactionActorID1 = stream.readInt32();
	datas.reactionActorID2 = stream.readInt32();
	datas.sonGeoID = stream.readInt32();
	reactionInfo_DataType.createFromStreamEx(stream, datas.reactionInfo);
	datas.isPairValid = stream.readUint8();
	reactionLoc_DataType.createFromStreamEx(stream, datas.reactionLoc);
	datas.reactionYaw = stream.readInt32();
	datas.hasOccur = stream.readUint8();
}

void DATATYPE_REACTION_PAIR_INFO::addToStreamEx(Bundle& stream, const REACTION_PAIR_INFO& v)
{
	stream.writeInt32(v.reactionPairID);
	stream.writeInt32(v.reactionActorID1);
	stream.writeInt32(v.reactionActorID2);
	stream.writeInt32(v.sonGeoID);
	reactionInfo_DataType.addToStreamEx(stream, v.reactionInfo);
	stream.writeUint8(v.isPairValid);
	reactionLoc_DataType.addToStreamEx(stream, v.reactionLoc);
	stream.writeInt32(v.reactionYaw);
	stream.writeUint8(v.hasOccur);
}

void DATATYPE_ENERMY_SPAWN_POINT_CORRECT_INFO::createFromStreamEx(MemoryStream& stream, ENERMY_SPAWN_POINT_CORRECT_INFO& datas)
{
	datas.spawnPointNb = stream.readInt32();
	datas.curSpawnRound = stream.readUint8();
	datas.curFrame = stream.readUint8();
	datas.curSpawnCharacterID = stream.readInt32();
}

void DATATYPE_ENERMY_SPAWN_POINT_CORRECT_INFO::addToStreamEx(Bundle& stream, const ENERMY_SPAWN_POINT_CORRECT_INFO& v)
{
	stream.writeInt32(v.spawnPointNb);
	stream.writeUint8(v.curSpawnRound);
	stream.writeUint8(v.curFrame);
	stream.writeInt32(v.curSpawnCharacterID);
}

void DATATYPE_ENERMY_GROUP_CORRECT_INFO::createFromStreamEx(MemoryStream& stream, ENERMY_GROUP_CORRECT_INFO& datas)
{
	datas.groupNb = stream.readInt32();
	datas.isTriggerOn = stream.readUint8();
	datas.isValid = stream.readUint8();
	spawnPointInfoList_DataType.createFromStreamEx(stream, datas.spawnPointInfoList);
}

void DATATYPE_ENERMY_GROUP_CORRECT_INFO::addToStreamEx(Bundle& stream, const ENERMY_GROUP_CORRECT_INFO& v)
{
	stream.writeInt32(v.groupNb);
	stream.writeUint8(v.isTriggerOn);
	stream.writeUint8(v.isValid);
	spawnPointInfoList_DataType.addToStreamEx(stream, v.spawnPointInfoList);
}

void DATATYPE_PLAYER_CORRECT_PROGRESS::createFromStreamEx(MemoryStream& stream, PLAYER_CORRECT_PROGRESS& datas)
{
	datas.stationID = stream.readInt32();
	datas.hasSendGeneralInfo = stream.readUint8();
	datas.curCharacterCorrectNb = stream.readInt32();
	datas.curPolyCorrectNb = stream.readInt32();
	datas.curLineCorrectNb = stream.readInt32();
	datas.curPointCorrectNb = stream.readInt32();
	datas.curActorCorrectNb = stream.readInt32();
	datas.curReactionPairCorrectNb = stream.readInt32();
	datas.curEnermyGroupCorrectNb = stream.readInt32();
}

void DATATYPE_PLAYER_CORRECT_PROGRESS::addToStreamEx(Bundle& stream, const PLAYER_CORRECT_PROGRESS& v)
{
	stream.writeInt32(v.stationID);
	stream.writeUint8(v.hasSendGeneralInfo);
	stream.writeInt32(v.curCharacterCorrectNb);
	stream.writeInt32(v.curPolyCorrectNb);
	stream.writeInt32(v.curLineCorrectNb);
	stream.writeInt32(v.curPointCorrectNb);
	stream.writeInt32(v.curActorCorrectNb);
	stream.writeInt32(v.curReactionPairCorrectNb);
	stream.writeInt32(v.curEnermyGroupCorrectNb);
}

void DATATYPE_CORRECT_INFO_LIST::createFromStreamEx(MemoryStream& stream, CORRECT_INFO_LIST& datas)
{
	datas.totalCharacterNb = stream.readInt32();
	datas.totalPolyNb = stream.readInt32();
	datas.totalLineNb = stream.readInt32();
	datas.totalPointNb = stream.readInt32();
	datas.totalActorNb = stream.readInt32();
	datas.totalReactionPairNb = stream.readInt32();
	datas.totalEnermyGroupNb = stream.readInt32();
	datas.mainMachineID = stream.readInt32();
	characterCorrectList_DataType.createFromStreamEx(stream, datas.characterCorrectList);
	physlineCorrectList_DataType.createFromStreamEx(stream, datas.physlineCorrectList);
	physpolyCorrectList_DataType.createFromStreamEx(stream, datas.physpolyCorrectList);
	physpointCorrectList_DataType.createFromStreamEx(stream, datas.physpointCorrectList);
	physactorCorrectList_DataType.createFromStreamEx(stream, datas.physactorCorrectList);
	reactionPairInfoList_DataType.createFromStreamEx(stream, datas.reactionPairInfoList);
	enermyGroupCorrectInfoList_DataType.createFromStreamEx(stream, datas.enermyGroupCorrectInfoList);
	datas.gameProgress = stream.readString();
	datas.randSeed = stream.readInt32();
	datas.frameNb = stream.readInt32();
	applyingPlayerList_DataType.createFromStreamEx(stream, datas.applyingPlayerList);
}

void DATATYPE_CORRECT_INFO_LIST::addToStreamEx(Bundle& stream, const CORRECT_INFO_LIST& v)
{
	stream.writeInt32(v.totalCharacterNb);
	stream.writeInt32(v.totalPolyNb);
	stream.writeInt32(v.totalLineNb);
	stream.writeInt32(v.totalPointNb);
	stream.writeInt32(v.totalActorNb);
	stream.writeInt32(v.totalReactionPairNb);
	stream.writeInt32(v.totalEnermyGroupNb);
	stream.writeInt32(v.mainMachineID);
	characterCorrectList_DataType.addToStreamEx(stream, v.characterCorrectList);
	physlineCorrectList_DataType.addToStreamEx(stream, v.physlineCorrectList);
	physpolyCorrectList_DataType.addToStreamEx(stream, v.physpolyCorrectList);
	physpointCorrectList_DataType.addToStreamEx(stream, v.physpointCorrectList);
	physactorCorrectList_DataType.addToStreamEx(stream, v.physactorCorrectList);
	reactionPairInfoList_DataType.addToStreamEx(stream, v.reactionPairInfoList);
	enermyGroupCorrectInfoList_DataType.addToStreamEx(stream, v.enermyGroupCorrectInfoList);
	stream.writeString(v.gameProgress);
	stream.writeInt32(v.randSeed);
	stream.writeInt32(v.frameNb);
	applyingPlayerList_DataType.addToStreamEx(stream, v.applyingPlayerList);
}

void DATATYPE_PLAYER_OPERATION_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_OPERATION_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.velocityX = stream.readInt32();
	datas.velocityY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.actionName = stream.readString();
	datas.collectPhysID = stream.readInt32();
	datas.equipmentNb = stream.readInt8();
	datas.skillNb = stream.readInt8();
	datas.spellSkillNb = stream.readInt8();
}

void DATATYPE_PLAYER_OPERATION_INFO::addToStreamEx(Bundle& stream, const PLAYER_OPERATION_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.velocityX);
	stream.writeInt32(v.velocityY);
	stream.writeInt32(v.yaw);
	stream.writeString(v.actionName);
	stream.writeInt32(v.collectPhysID);
	stream.writeInt8(v.equipmentNb);
	stream.writeInt8(v.skillNb);
	stream.writeInt8(v.spellSkillNb);
}

void DATATYPE_AI_CHARACTER_OPERATION_INFO::createFromStreamEx(MemoryStream& stream, AI_CHARACTER_OPERATION_INFO& datas)
{
	datas.entityID = stream.readInt32();
	datas.velocityX = stream.readInt32();
	datas.velocityY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.skillNb = stream.readInt8();
	datas.newShortTask = stream.readUint8();
	datas.actionName = stream.readString();
}

void DATATYPE_AI_CHARACTER_OPERATION_INFO::addToStreamEx(Bundle& stream, const AI_CHARACTER_OPERATION_INFO& v)
{
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.velocityX);
	stream.writeInt32(v.velocityY);
	stream.writeInt32(v.yaw);
	stream.writeInt8(v.skillNb);
	stream.writeUint8(v.newShortTask);
	stream.writeString(v.actionName);
}

void DATATYPE_AI_CHARACTER_OPERATION_LIST::createFromStreamEx(MemoryStream& stream, AI_CHARACTER_OPERATION_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
	datas.frameNb = stream.readInt32();
}

void DATATYPE_AI_CHARACTER_OPERATION_LIST::addToStreamEx(Bundle& stream, const AI_CHARACTER_OPERATION_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
	stream.writeInt32(v.frameNb);
}

void DATATYPE_LOGIC_FRAME::createFromStreamEx(MemoryStream& stream, LOGIC_FRAME& datas)
{
	playerOperationList_DataType.createFromStreamEx(stream, datas.playerOperationList);
	aiCharacterOperationList_DataType.createFromStreamEx(stream, datas.aiCharacterOperationList);
	datas.frameNb = stream.readInt32();
	datas.roundNb = stream.readInt8();
}

void DATATYPE_LOGIC_FRAME::addToStreamEx(Bundle& stream, const LOGIC_FRAME& v)
{
	playerOperationList_DataType.addToStreamEx(stream, v.playerOperationList);
	aiCharacterOperationList_DataType.addToStreamEx(stream, v.aiCharacterOperationList);
	stream.writeInt32(v.frameNb);
	stream.writeInt8(v.roundNb);
}

void DATATYPE_LOGIC_FRAME_LIST::createFromStreamEx(MemoryStream& stream, LOGIC_FRAME_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_LOGIC_FRAME_LIST::addToStreamEx(Bundle& stream, const LOGIC_FRAME_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_COMPLETE_FRAME_INFO::createFromStreamEx(MemoryStream& stream, COMPLETE_FRAME_INFO& datas)
{
	playerOperationList_DataType.createFromStreamEx(stream, datas.playerOperationList);
	aiCharacterOperationList_DataType.createFromStreamEx(stream, datas.aiCharacterOperationList);
	characterCorrectList_DataType.createFromStreamEx(stream, datas.characterCorrectList);
	physlineCorrectList_DataType.createFromStreamEx(stream, datas.physlineCorrectList);
	physpolyCorrectList_DataType.createFromStreamEx(stream, datas.physpolyCorrectList);
	physpointCorrectList_DataType.createFromStreamEx(stream, datas.physpointCorrectList);
	reactionPairInfoList_DataType.createFromStreamEx(stream, datas.reactionPairInfoList);
	enermyGroupCorrectInfoList_DataType.createFromStreamEx(stream, datas.enermyGroupCorrectInfoList);
	datas.gameProgress = stream.readString();
	datas.frameNb = stream.readInt32();
}

void DATATYPE_COMPLETE_FRAME_INFO::addToStreamEx(Bundle& stream, const COMPLETE_FRAME_INFO& v)
{
	playerOperationList_DataType.addToStreamEx(stream, v.playerOperationList);
	aiCharacterOperationList_DataType.addToStreamEx(stream, v.aiCharacterOperationList);
	characterCorrectList_DataType.addToStreamEx(stream, v.characterCorrectList);
	physlineCorrectList_DataType.addToStreamEx(stream, v.physlineCorrectList);
	physpolyCorrectList_DataType.addToStreamEx(stream, v.physpolyCorrectList);
	physpointCorrectList_DataType.addToStreamEx(stream, v.physpointCorrectList);
	reactionPairInfoList_DataType.addToStreamEx(stream, v.reactionPairInfoList);
	enermyGroupCorrectInfoList_DataType.addToStreamEx(stream, v.enermyGroupCorrectInfoList);
	stream.writeString(v.gameProgress);
	stream.writeInt32(v.frameNb);
}

void DATATYPE_PLAYER_SPAWN_POINT_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_SPAWN_POINT_INFO& datas)
{
	datas.campFlag = stream.readUint8();
	datas.spawnPointNb = stream.readUint8();
	datas.spawnPointX = stream.readInt32();
	datas.spawnPointY = stream.readInt32();
	datas.yaw = stream.readInt32();
}

void DATATYPE_PLAYER_SPAWN_POINT_INFO::addToStreamEx(Bundle& stream, const PLAYER_SPAWN_POINT_INFO& v)
{
	stream.writeUint8(v.campFlag);
	stream.writeUint8(v.spawnPointNb);
	stream.writeInt32(v.spawnPointX);
	stream.writeInt32(v.spawnPointY);
	stream.writeInt32(v.yaw);
}

void DATATYPE_PLAYER_SPAWN_POINT_LIST::createFromStreamEx(MemoryStream& stream, PLAYER_SPAWN_POINT_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_PLAYER_SPAWN_POINT_LIST::addToStreamEx(Bundle& stream, const PLAYER_SPAWN_POINT_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_SPECIAL_FRAME_LIST::createFromStreamEx(MemoryStream& stream, SPECIAL_FRAME_LIST& datas)
{
	uploadFrameList_DataType.createFromStreamEx(stream, datas.uploadFrameList);
	downloadFrameList_DataType.createFromStreamEx(stream, datas.downloadFrameList);
}

void DATATYPE_SPECIAL_FRAME_LIST::addToStreamEx(Bundle& stream, const SPECIAL_FRAME_LIST& v)
{
	uploadFrameList_DataType.addToStreamEx(stream, v.uploadFrameList);
	downloadFrameList_DataType.addToStreamEx(stream, v.downloadFrameList);
}

void DATATYPE_TRIGGER_INFO::createFromStreamEx(MemoryStream& stream, TRIGGER_INFO& datas)
{
	datas.SpawnGroupName = stream.readString();
	datas.triggerType = stream.readString();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.isAutoGenerate = stream.readUint8();
}

void DATATYPE_TRIGGER_INFO::addToStreamEx(Bundle& stream, const TRIGGER_INFO& v)
{
	stream.writeString(v.SpawnGroupName);
	stream.writeString(v.triggerType);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.yaw);
	stream.writeUint8(v.isAutoGenerate);
}

void DATATYPE_ENERMY_SPAWN_ORDER::createFromStreamEx(MemoryStream& stream, ENERMY_SPAWN_ORDER& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_ENERMY_SPAWN_ORDER::addToStreamEx(Bundle& stream, const ENERMY_SPAWN_ORDER& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_ENERMY_SPAWN_POINT_INFO::createFromStreamEx(MemoryStream& stream, ENERMY_SPAWN_POINT_INFO& datas)
{
	datas.spawnPointNb = stream.readInt32();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.defRadius = stream.readInt32();
	spawnOrder_DataType.createFromStreamEx(stream, datas.spawnOrder);
	datas.frameInterval = stream.readInt32();
	datas.isCirculate = stream.readUint8();
}

void DATATYPE_ENERMY_SPAWN_POINT_INFO::addToStreamEx(Bundle& stream, const ENERMY_SPAWN_POINT_INFO& v)
{
	stream.writeInt32(v.spawnPointNb);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.yaw);
	stream.writeInt32(v.defRadius);
	spawnOrder_DataType.addToStreamEx(stream, v.spawnOrder);
	stream.writeInt32(v.frameInterval);
	stream.writeUint8(v.isCirculate);
}

void DATATYPE_ENERMY_SPAWN_GROUP_INFO::createFromStreamEx(MemoryStream& stream, ENERMY_SPAWN_GROUP_INFO& datas)
{
	datas.groupNb = stream.readInt32();
	datas.campFlag = stream.readUint8();
	triggerInfo_DataType.createFromStreamEx(stream, datas.triggerInfo);
	spawnPointList_DataType.createFromStreamEx(stream, datas.spawnPointList);
}

void DATATYPE_ENERMY_SPAWN_GROUP_INFO::addToStreamEx(Bundle& stream, const ENERMY_SPAWN_GROUP_INFO& v)
{
	stream.writeInt32(v.groupNb);
	stream.writeUint8(v.campFlag);
	triggerInfo_DataType.addToStreamEx(stream, v.triggerInfo);
	spawnPointList_DataType.addToStreamEx(stream, v.spawnPointList);
}

void DATATYPE_ENERMY_SPAWN_GROUP_LIST::createFromStreamEx(MemoryStream& stream, ENERMY_SPAWN_GROUP_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_ENERMY_SPAWN_GROUP_LIST::addToStreamEx(Bundle& stream, const ENERMY_SPAWN_GROUP_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_PHYSACTOR_SPAWN_INFO::createFromStreamEx(MemoryStream& stream, PHYSACTOR_SPAWN_INFO& datas)
{
	datas.physActorName = stream.readString();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.yaw = stream.readInt32();
	datas.moveType = stream.readInt8();
	moveOrder_DataType.createFromStreamEx(stream, datas.moveOrder);
	rotateOrder_DataType.createFromStreamEx(stream, datas.rotateOrder);
	spawnFrames_DataType.createFromStreamEx(stream, datas.spawnFrames);
}

void DATATYPE_PHYSACTOR_SPAWN_INFO::addToStreamEx(Bundle& stream, const PHYSACTOR_SPAWN_INFO& v)
{
	stream.writeString(v.physActorName);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.yaw);
	stream.writeInt8(v.moveType);
	moveOrder_DataType.addToStreamEx(stream, v.moveOrder);
	rotateOrder_DataType.addToStreamEx(stream, v.rotateOrder);
	spawnFrames_DataType.addToStreamEx(stream, v.spawnFrames);
}

void DATATYPE_PHYSACTOR_SPAWN_LIST::createFromStreamEx(MemoryStream& stream, PHYSACTOR_SPAWN_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_PHYSACTOR_SPAWN_LIST::addToStreamEx(Bundle& stream, const PHYSACTOR_SPAWN_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_LEVEL_MODEL_INFO::createFromStreamEx(MemoryStream& stream, LEVEL_MODEL_INFO& datas)
{
	datas.price = stream.readInt32();
	datas.blueprintName = stream.readString();
	datas.levelName = stream.readString();
	datas.positionX = stream.readInt32();
	datas.positionY = stream.readInt32();
	datas.positionZ = stream.readInt32();
	availableMatchList_DataType.createFromStreamEx(stream, datas.availableMatchList);
}

void DATATYPE_LEVEL_MODEL_INFO::addToStreamEx(Bundle& stream, const LEVEL_MODEL_INFO& v)
{
	stream.writeInt32(v.price);
	stream.writeString(v.blueprintName);
	stream.writeString(v.levelName);
	stream.writeInt32(v.positionX);
	stream.writeInt32(v.positionY);
	stream.writeInt32(v.positionZ);
	availableMatchList_DataType.addToStreamEx(stream, v.availableMatchList);
}

void DATATYPE_LEVEL_MODEL_LIST::createFromStreamEx(MemoryStream& stream, LEVEL_MODEL_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_LEVEL_MODEL_LIST::addToStreamEx(Bundle& stream, const LEVEL_MODEL_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_PLAYER_RANK_INFO::createFromStreamEx(MemoryStream& stream, PLAYER_RANK_INFO& datas)
{
	datas.dbid = stream.readUint64();
	datas.playerName = stream.readString();
	datas.winPercent = stream.readInt8();
	datas.headShot = stream.readString();
	datas.rank = stream.readInt32();
}

void DATATYPE_PLAYER_RANK_INFO::addToStreamEx(Bundle& stream, const PLAYER_RANK_INFO& v)
{
	stream.writeUint64(v.dbid);
	stream.writeString(v.playerName);
	stream.writeInt8(v.winPercent);
	stream.writeString(v.headShot);
	stream.writeInt32(v.rank);
}

void DATATYPE_RANK_LIST::createFromStreamEx(MemoryStream& stream, RANK_LIST& datas)
{
	datas.mapType = stream.readString();
	rankList_DataType.createFromStreamEx(stream, datas.rankList);
}

void DATATYPE_RANK_LIST::addToStreamEx(Bundle& stream, const RANK_LIST& v)
{
	stream.writeString(v.mapType);
	rankList_DataType.addToStreamEx(stream, v.rankList);
}

void DATATYPE_ALL_RANK_LIST::createFromStreamEx(MemoryStream& stream, ALL_RANK_LIST& datas)
{
	singleRankList_DataType.createFromStreamEx(stream, datas.singleRankList);
	oneOneRankList_DataType.createFromStreamEx(stream, datas.oneOneRankList);
	twoTwoRankList_DataType.createFromStreamEx(stream, datas.twoTwoRankList);
	threeThreeRankList_DataType.createFromStreamEx(stream, datas.threeThreeRankList);
}

void DATATYPE_ALL_RANK_LIST::addToStreamEx(Bundle& stream, const ALL_RANK_LIST& v)
{
	singleRankList_DataType.addToStreamEx(stream, v.singleRankList);
	oneOneRankList_DataType.addToStreamEx(stream, v.oneOneRankList);
	twoTwoRankList_DataType.addToStreamEx(stream, v.twoTwoRankList);
	threeThreeRankList_DataType.addToStreamEx(stream, v.threeThreeRankList);
}

void DATATYPE_PLAYER_BATTLE_STATUS::createFromStreamEx(MemoryStream& stream, PLAYER_BATTLE_STATUS& datas)
{
	datas.accountID = stream.readInt32();
	datas.killEnermyNb = stream.readInt32();
	datas.outputScore = stream.readInt32();
	datas.positiveScore = stream.readInt32();
	datas.negativeScore = stream.readInt32();
}

void DATATYPE_PLAYER_BATTLE_STATUS::addToStreamEx(Bundle& stream, const PLAYER_BATTLE_STATUS& v)
{
	stream.writeInt32(v.accountID);
	stream.writeInt32(v.killEnermyNb);
	stream.writeInt32(v.outputScore);
	stream.writeInt32(v.positiveScore);
	stream.writeInt32(v.negativeScore);
}

void DATATYPE_BATTLE_TEAM_INFO::createFromStreamEx(MemoryStream& stream, BATTLE_TEAM_INFO& datas)
{
	datas.teamNb = stream.readInt8();
	playerBattleStatusList_DataType.createFromStreamEx(stream, datas.playerBattleStatusList);
}

void DATATYPE_BATTLE_TEAM_INFO::addToStreamEx(Bundle& stream, const BATTLE_TEAM_INFO& v)
{
	stream.writeInt8(v.teamNb);
	playerBattleStatusList_DataType.addToStreamEx(stream, v.playerBattleStatusList);
}

void DATATYPE_BATTLE_RESULT_ROUND::createFromStreamEx(MemoryStream& stream, BATTLE_RESULT_ROUND& datas)
{
	datas.roundNb = stream.readInt8();
	winTeamList_DataType.createFromStreamEx(stream, datas.winTeamList);
	teams_DataType.createFromStreamEx(stream, datas.teams);
}

void DATATYPE_BATTLE_RESULT_ROUND::addToStreamEx(Bundle& stream, const BATTLE_RESULT_ROUND& v)
{
	stream.writeInt8(v.roundNb);
	winTeamList_DataType.addToStreamEx(stream, v.winTeamList);
	teams_DataType.addToStreamEx(stream, v.teams);
}

void DATATYPE_BATTLE_RESULT_ROUND_LIST::createFromStreamEx(MemoryStream& stream, BATTLE_RESULT_ROUND_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_BATTLE_RESULT_ROUND_LIST::addToStreamEx(Bundle& stream, const BATTLE_RESULT_ROUND_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_TEAM_WIN_INFO::createFromStreamEx(MemoryStream& stream, TEAM_WIN_INFO& datas)
{
	datas.teamNb = stream.readInt8();
	accountIDList_DataType.createFromStreamEx(stream, datas.accountIDList);
	dbidList_DataType.createFromStreamEx(stream, datas.dbidList);
	datas.winNb = stream.readInt8();
}

void DATATYPE_TEAM_WIN_INFO::addToStreamEx(Bundle& stream, const TEAM_WIN_INFO& v)
{
	stream.writeInt8(v.teamNb);
	accountIDList_DataType.addToStreamEx(stream, v.accountIDList);
	dbidList_DataType.addToStreamEx(stream, v.dbidList);
	stream.writeInt8(v.winNb);
}

void DATATYPE_BATTLE_RESULT::createFromStreamEx(MemoryStream& stream, BATTLE_RESULT& datas)
{
	teamWinInfoList_DataType.createFromStreamEx(stream, datas.teamWinInfoList);
	battleResultList_DataType.createFromStreamEx(stream, datas.battleResultList);
}

void DATATYPE_BATTLE_RESULT::addToStreamEx(Bundle& stream, const BATTLE_RESULT& v)
{
	teamWinInfoList_DataType.addToStreamEx(stream, v.teamWinInfoList);
	battleResultList_DataType.addToStreamEx(stream, v.battleResultList);
}

void DATATYPE_ACCOUNT_INFO::createFromStreamEx(MemoryStream& stream, ACCOUNT_INFO& datas)
{
	datas.name = stream.readString();
	datas.entityCall = stream.readPython();
	datas.dbid = stream.readUint64();
	datas.entityID = stream.readInt32();
	datas.totalWinNb = stream.readInt32();
	datas.totalBattleNb = stream.readInt32();
	datas.headShotName = stream.readString();
}

void DATATYPE_ACCOUNT_INFO::addToStreamEx(Bundle& stream, const ACCOUNT_INFO& v)
{
	stream.writeString(v.name);
	stream.writePython(v.entityCall);
	stream.writeUint64(v.dbid);
	stream.writeInt32(v.entityID);
	stream.writeInt32(v.totalWinNb);
	stream.writeInt32(v.totalBattleNb);
	stream.writeString(v.headShotName);
}

void DATATYPE_ACCOUNT_INFO_LIST::createFromStreamEx(MemoryStream& stream, ACCOUNT_INFO_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_ACCOUNT_INFO_LIST::addToStreamEx(Bundle& stream, const ACCOUNT_INFO_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM::createFromStreamEx(MemoryStream& stream, PLAYER_ROLETYPE_ASSIGNNUM& datas)
{
	datas.roleType = stream.readString();
	datas.assignNb = stream.readUint8();
	datas.playerID = stream.readInt32();
}

void DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM::addToStreamEx(Bundle& stream, const PLAYER_ROLETYPE_ASSIGNNUM& v)
{
	stream.writeString(v.roleType);
	stream.writeUint8(v.assignNb);
	stream.writeInt32(v.playerID);
}

void DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST::createFromStreamEx(MemoryStream& stream, PLAYER_ROLETYPE_ASSIGNNUM_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_PLAYER_ROLETYPE_ASSIGNNUM_LIST::addToStreamEx(Bundle& stream, const PLAYER_ROLETYPE_ASSIGNNUM_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_MALL_GOODS_INFO::createFromStreamEx(MemoryStream& stream, MALL_GOODS_INFO& datas)
{
	datas.goodsName = stream.readString();
	datas.possessNb = stream.readInt32();
	datas.expectNb = stream.readInt32();
	datas.weight = stream.readInt32();
	datas.onlyForWin = stream.readUint8();
	datas.onlyForSell = stream.readUint8();
}

void DATATYPE_MALL_GOODS_INFO::addToStreamEx(Bundle& stream, const MALL_GOODS_INFO& v)
{
	stream.writeString(v.goodsName);
	stream.writeInt32(v.possessNb);
	stream.writeInt32(v.expectNb);
	stream.writeInt32(v.weight);
	stream.writeUint8(v.onlyForWin);
	stream.writeUint8(v.onlyForSell);
}

void DATATYPE_MALL_GOODS_LIST::createFromStreamEx(MemoryStream& stream, MALL_GOODS_LIST& datas)
{
	goodsList_DataType.createFromStreamEx(stream, datas.goodsList);
}

void DATATYPE_MALL_GOODS_LIST::addToStreamEx(Bundle& stream, const MALL_GOODS_LIST& v)
{
	goodsList_DataType.addToStreamEx(stream, v.goodsList);
}

void DATATYPE_MALL_GOODS_INFO_FOR_CLIENT::createFromStreamEx(MemoryStream& stream, MALL_GOODS_INFO_FOR_CLIENT& datas)
{
	datas.goodsName = stream.readString();
	datas.price = stream.readInt32();
}

void DATATYPE_MALL_GOODS_INFO_FOR_CLIENT::addToStreamEx(Bundle& stream, const MALL_GOODS_INFO_FOR_CLIENT& v)
{
	stream.writeString(v.goodsName);
	stream.writeInt32(v.price);
}

void DATATYPE_GOODS_LIST::createFromStreamEx(MemoryStream& stream, GOODS_LIST& datas)
{
	goodsList_DataType.createFromStreamEx(stream, datas.goodsList);
}

void DATATYPE_GOODS_LIST::addToStreamEx(Bundle& stream, const GOODS_LIST& v)
{
	goodsList_DataType.addToStreamEx(stream, v.goodsList);
}

void DATATYPE_GLOBAL_INFO::createFromStreamEx(MemoryStream& stream, GLOBAL_INFO& datas)
{
	datas.rankSystemDBID = stream.readUint64();
	datas.rankSystemAppNum = stream.readInt32();
	datas.switchBoardDBID = stream.readUint64();
	datas.switchBoardAppNum = stream.readInt32();
	datas.mallDBID = stream.readUint64();
	datas.mallAppNum = stream.readInt32();
}

void DATATYPE_GLOBAL_INFO::addToStreamEx(Bundle& stream, const GLOBAL_INFO& v)
{
	stream.writeUint64(v.rankSystemDBID);
	stream.writeInt32(v.rankSystemAppNum);
	stream.writeUint64(v.switchBoardDBID);
	stream.writeInt32(v.switchBoardAppNum);
	stream.writeUint64(v.mallDBID);
	stream.writeInt32(v.mallAppNum);
}

void DATATYPE_ADD_FRIEND_REQUEST::createFromStreamEx(MemoryStream& stream, ADD_FRIEND_REQUEST& datas)
{
	datas.hostDBID = stream.readUint64();
	datas.hostName = stream.readString();
	datas.requestDBID = stream.readUint64();
	datas.requestName = stream.readString();
}

void DATATYPE_ADD_FRIEND_REQUEST::addToStreamEx(Bundle& stream, const ADD_FRIEND_REQUEST& v)
{
	stream.writeUint64(v.hostDBID);
	stream.writeString(v.hostName);
	stream.writeUint64(v.requestDBID);
	stream.writeString(v.requestName);
}

void DATATYPE_ADD_FRIEND_REQUEST_LIST::createFromStreamEx(MemoryStream& stream, ADD_FRIEND_REQUEST_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_ADD_FRIEND_REQUEST_LIST::addToStreamEx(Bundle& stream, const ADD_FRIEND_REQUEST_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_ADD_FRIEND_ANSWER::createFromStreamEx(MemoryStream& stream, ADD_FRIEND_ANSWER& datas)
{
	datas.hostDBID = stream.readUint64();
	datas.hostName = stream.readString();
	datas.answerDBID = stream.readUint64();
	datas.answerName = stream.readString();
	datas.answer = stream.readUint8();
}

void DATATYPE_ADD_FRIEND_ANSWER::addToStreamEx(Bundle& stream, const ADD_FRIEND_ANSWER& v)
{
	stream.writeUint64(v.hostDBID);
	stream.writeString(v.hostName);
	stream.writeUint64(v.answerDBID);
	stream.writeString(v.answerName);
	stream.writeUint8(v.answer);
}

void DATATYPE_ADD_FRIEND_ANSWER_LIST::createFromStreamEx(MemoryStream& stream, ADD_FRIEND_ANSWER_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_ADD_FRIEND_ANSWER_LIST::addToStreamEx(Bundle& stream, const ADD_FRIEND_ANSWER_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_DELETE_FRIEND_REQUEST::createFromStreamEx(MemoryStream& stream, DELETE_FRIEND_REQUEST& datas)
{
	datas.hostDBID = stream.readUint64();
	datas.hostName = stream.readString();
	datas.requestDBID = stream.readUint64();
	datas.requestName = stream.readString();
}

void DATATYPE_DELETE_FRIEND_REQUEST::addToStreamEx(Bundle& stream, const DELETE_FRIEND_REQUEST& v)
{
	stream.writeUint64(v.hostDBID);
	stream.writeString(v.hostName);
	stream.writeUint64(v.requestDBID);
	stream.writeString(v.requestName);
}

void DATATYPE_DELETE_FRIEND_REQUEST_LIST::createFromStreamEx(MemoryStream& stream, DELETE_FRIEND_REQUEST_LIST& datas)
{
	values_DataType.createFromStreamEx(stream, datas.values);
}

void DATATYPE_DELETE_FRIEND_REQUEST_LIST::addToStreamEx(Bundle& stream, const DELETE_FRIEND_REQUEST_LIST& v)
{
	values_DataType.addToStreamEx(stream, v.values);
}

void DATATYPE_AnonymousArray_257::createFromStreamEx(MemoryStream& stream, TArray<uint64>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint64());
	};

}

void DATATYPE_AnonymousArray_257::addToStreamEx(Bundle& stream, const TArray<uint64>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint64(v[i]);
	};
}

void DATATYPE_AnonymousArray_258::createFromStreamEx(MemoryStream& stream, TArray<int8>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt8());
	};

}

void DATATYPE_AnonymousArray_258::addToStreamEx(Bundle& stream, const TArray<int8>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt8(v[i]);
	};
}

void DATATYPE_AnonymousArray_259::createFromStreamEx(MemoryStream& stream, TArray<int8>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt8());
	};

}

void DATATYPE_AnonymousArray_259::addToStreamEx(Bundle& stream, const TArray<int8>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt8(v[i]);
	};
}

void DATATYPE_AnonymousArray_260::createFromStreamEx(MemoryStream& stream, TArray<int32>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt32());
	};

}

void DATATYPE_AnonymousArray_260::addToStreamEx(Bundle& stream, const TArray<int32>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt32(v[i]);
	};
}

void DATATYPE_AnonymousArray_261::createFromStreamEx(MemoryStream& stream, TArray<int8>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt8());
	};

}

void DATATYPE_AnonymousArray_261::addToStreamEx(Bundle& stream, const TArray<int8>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt8(v[i]);
	};
}

void DATATYPE_AnonymousArray_262::createFromStreamEx(MemoryStream& stream, TArray<uint64>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readUint64());
	};

}

void DATATYPE_AnonymousArray_262::addToStreamEx(Bundle& stream, const TArray<uint64>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeUint64(v[i]);
	};
}

void DATATYPE_AnonymousArray_263::createFromStreamEx(MemoryStream& stream, TArray<FString>& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readString());
	};

}

void DATATYPE_AnonymousArray_263::addToStreamEx(Bundle& stream, const TArray<FString>& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeString(v[i]);
	};
}

