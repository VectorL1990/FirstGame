#include "HallBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void HallBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_HallBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void HallBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_HallBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void HallBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* HallBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* HallBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void HallBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void HallBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void HallBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

HallBase::HallBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

HallBase::~HallBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

