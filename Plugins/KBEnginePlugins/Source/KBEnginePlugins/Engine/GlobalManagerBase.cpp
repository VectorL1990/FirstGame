#include "GlobalManagerBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void GlobalManagerBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_GlobalManagerBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void GlobalManagerBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_GlobalManagerBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void GlobalManagerBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* GlobalManagerBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* GlobalManagerBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void GlobalManagerBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void GlobalManagerBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void GlobalManagerBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

GlobalManagerBase::GlobalManagerBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

GlobalManagerBase::~GlobalManagerBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

