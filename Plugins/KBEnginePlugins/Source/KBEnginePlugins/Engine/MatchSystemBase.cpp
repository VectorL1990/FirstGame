#include "MatchSystemBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void MatchSystemBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_MatchSystemBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void MatchSystemBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_MatchSystemBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void MatchSystemBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* MatchSystemBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* MatchSystemBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void MatchSystemBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void MatchSystemBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void MatchSystemBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

MatchSystemBase::MatchSystemBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

MatchSystemBase::~MatchSystemBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

