#include "RankSystemBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void RankSystemBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_RankSystemBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void RankSystemBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_RankSystemBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void RankSystemBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* RankSystemBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* RankSystemBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void RankSystemBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void RankSystemBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void RankSystemBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

RankSystemBase::RankSystemBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

RankSystemBase::~RankSystemBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

