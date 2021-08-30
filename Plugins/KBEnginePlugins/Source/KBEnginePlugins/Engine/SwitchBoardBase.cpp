#include "SwitchBoardBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"


void SwitchBoardBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_SwitchBoardBase();
	pBaseEntityCall->id = id();
	pBaseEntityCall->className = className();
}

void SwitchBoardBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_SwitchBoardBase();
	pCellEntityCall->id = id();
	pCellEntityCall->className = className();
}

void SwitchBoardBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* SwitchBoardBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* SwitchBoardBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void SwitchBoardBase::onRemoteMethodCall(Method* pMethod, MemoryStream& stream)
{
}

void SwitchBoardBase::onUpdatePropertys(Property* pProp, MemoryStream& stream)
{
}

void SwitchBoardBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs[className()];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

}

SwitchBoardBase::SwitchBoardBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

SwitchBoardBase::~SwitchBoardBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;
}

