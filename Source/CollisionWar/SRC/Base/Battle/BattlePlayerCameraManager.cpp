// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionWar.h"
#include "BattlePlayerCameraManager.h"





void ABattlePlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	// Don't update outgoing viewtarget during an interpolation 
	if ((PendingViewTarget.Target != NULL) && BlendParams.bLockOutgoing && OutVT.Equal(ViewTarget))
	{
		return;
	}

	// store previous POV, in case we need it later
	FMinimalViewInfo OrigPOV = OutVT.POV;

	//@TODO: CAMERA: Should probably reset the view target POV fully here
	OutVT.POV.FOV = DefaultFOV;
	OutVT.POV.OrthoWidth = DefaultOrthoWidth;
	OutVT.POV.AspectRatio = DefaultAspectRatio;
	OutVT.POV.bConstrainAspectRatio = bDefaultConstrainAspectRatio;
	OutVT.POV.bUseFieldOfViewForLOD = true;
	OutVT.POV.ProjectionMode = bIsOrthographic ? ECameraProjectionMode::Orthographic : ECameraProjectionMode::Perspective;
	OutVT.POV.PostProcessSettings.SetBaseValues();
	OutVT.POV.PostProcessBlendWeight = 1.0f;

	bool bDoNotApplyModifiers = false;


	if (ACameraActor* CamActor = Cast<ACameraActor>(OutVT.Target))
	{
		// Viewing through a camera actor.
		CamActor->GetCameraComponent()->GetCameraView(DeltaTime, OutVT.POV);
	}
	else
	{
		if (OutVT.Target)
		{
			FVector OutLocation;
			FRotator OutRotation;
			float OutFOV;

			if (BlueprintUpdateCamera(OutVT.Target, OutLocation, OutRotation, OutFOV))
			{
				OutVT.POV.Location = OutLocation;
				OutVT.POV.Rotation = OutRotation;
				OutVT.POV.FOV = OutFOV;
			}
			else
			{
				OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
			}
		}
	}

	if (!bDoNotApplyModifiers || bAlwaysApplyModifiers)
	{
		// Apply camera modifiers at the end (view shakes for example)
		ApplyCameraModifiers(DeltaTime, OutVT.POV);
	}

	OutVT.POV.Location += m_POVLocation;
	OutVT.POV.Rotation = m_POVRotation;
	// Synchronize the actor with the view target results
	SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);

	UpdateCameraLensEffects(OutVT);


/*

	APawn* pControllPawn = PCOwner->GetPawn();// PCOwner->GetControlledPawn();
	if (pControllPawn)
	{
		FVector pawnLoc = pControllPawn->GetActorLocation();
		OutVT.POV.Location = pawnLoc + m_POVLocation;
		OutVT.POV.Rotation = m_POVRotation;

		if (!bDoNotApplyModifiers || bAlwaysApplyModifiers)
		{
			// Apply camera modifiers at the end (view shakes for example)
			ApplyCameraModifiers(DeltaTime, OutVT.POV);
		}

		// Synchronize the actor with the view target results
		SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);

		UpdateCameraLensEffects(OutVT);
	}
	else
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
	}*/
}
