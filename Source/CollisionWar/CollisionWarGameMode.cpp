// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CollisionWar.h"
#include "CollisionWarGameMode.h"
#include "CollisionWarPlayerController.h"
#include "CollisionWarCharacter.h"

ACollisionWarGameMode::ACollisionWarGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = ACollisionWarPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}