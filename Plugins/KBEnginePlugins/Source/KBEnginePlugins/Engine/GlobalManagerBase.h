/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class GlobalManager : public GlobalManagerBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "ServerErrorDescrs.h"
#include "EntityCallGlobalManagerBase.h"

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/GlobalManager.def
class KBENGINEPLUGINS_API GlobalManagerBase : public Entity
{
public:
	EntityBaseEntityCall_GlobalManagerBase* pBaseEntityCall;
	EntityCellEntityCall_GlobalManagerBase* pCellEntityCall;



	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;

	void onRemoteMethodCall(Method* pMethod, MemoryStream& stream) override;
	void onUpdatePropertys(Property* pProp, MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	GlobalManagerBase();
	virtual ~GlobalManagerBase();

};

