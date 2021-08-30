// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CollisionWar.h"
#include "CollisionWarPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

ACollisionWarPlayerController::ACollisionWarPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACollisionWarPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ACollisionWarPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACollisionWarPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACollisionWarPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACollisionWarPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ACollisionWarPlayerController::MoveToTouchLocation);
}

void ACollisionWarPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ACollisionWarPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ACollisionWarPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ACollisionWarPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ACollisionWarPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
