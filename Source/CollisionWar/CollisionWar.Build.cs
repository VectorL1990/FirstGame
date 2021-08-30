// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;
using Tools.DotNETCommon;

public class CollisionWar : ModuleRules
{
    
    /***********第三库引入，都放在MyLibrary这个文件夹，谢谢*********************************************/
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../MyLibrary/")); }
    }
    /********************************************************/

    public CollisionWar(ReadOnlyTargetRules Target) : base (Target)
    {
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
        //PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "HeadMountedDisplay", "KBEnginePlugins", "MediaAssets" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        //PrivateIncludePathModuleNames.AddRange(new string[] { "slua_unreal" });

        //PublicIncludePathModuleNames.AddRange(new string[] { "slua_unreal" });

        /**********************加入第三方库**********************************/
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Includes"));
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "Libs", "SDL2.lib"));
        /********************************************************/
    }
}
