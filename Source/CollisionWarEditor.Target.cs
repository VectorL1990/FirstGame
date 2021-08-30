// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CollisionWarEditorTarget : TargetRules
{
	public CollisionWarEditorTarget(TargetInfo Target): base (Target)
	{
		Type = TargetType.Editor;
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
