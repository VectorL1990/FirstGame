/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"

// defined in */scripts/entity_defs/Room.def

class KBENGINEPLUGINS_API EntityBaseEntityCall_RoomBase : public EntityCall
{
public:
	EntityBaseEntityCall_RoomBase() : EntityCall()
	{
		type = ENTITYCALL_TYPE_BASE;
	}

};

class KBENGINEPLUGINS_API EntityCellEntityCall_RoomBase : public EntityCall
{
public:
	EntityCellEntityCall_RoomBase() : EntityCall()
	{
		type = ENTITYCALL_TYPE_CELL;
	}

};