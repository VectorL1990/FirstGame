/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class Room : public RoomBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "ServerErrorDescrs.h"
#include "EntityCallRoomBase.h"

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/Room.def
class KBENGINEPLUGINS_API RoomBase : public Entity
{
public:
	EntityBaseEntityCall_RoomBase* pBaseEntityCall;
	EntityCellEntityCall_RoomBase* pCellEntityCall;



	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;

	void onRemoteMethodCall(Method* pMethod, MemoryStream& stream) override;
	void onUpdatePropertys(Property* pProp, MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	RoomBase();
	virtual ~RoomBase();

};

