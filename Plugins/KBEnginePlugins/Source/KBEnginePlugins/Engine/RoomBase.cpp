#include "RoomBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void RoomBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_RoomBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void RoomBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_RoomBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void RoomBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* RoomBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* RoomBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void RoomBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void RoomBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void RoomBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

RoomBase::RoomBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

RoomBase::~RoomBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

