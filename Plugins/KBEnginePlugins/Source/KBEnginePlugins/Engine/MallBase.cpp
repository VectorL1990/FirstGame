#include "MallBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void MallBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_MallBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void MallBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_MallBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void MallBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* MallBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* MallBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void MallBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void MallBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void MallBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

MallBase::MallBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

MallBase::~MallBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

