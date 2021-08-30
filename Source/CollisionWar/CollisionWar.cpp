// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CollisionWar.h"



class FCollisionWarModule : public FDefaultGameModuleImpl
{
public:
	// IModuleInterface implementations

	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FCollisionWarModule, CollisionWar, "CollisionWar" );

DEFINE_LOG_CATEGORY(LogCollisionWar)
 