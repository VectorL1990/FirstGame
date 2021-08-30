// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CollisionWarTarget : TargetRules
{
	public CollisionWarTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.Add("CollisionWar");
    }

	//
	// TargetRules interface.
	//
    /*
	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.Add("CollisionWar");
	}
    */
}
