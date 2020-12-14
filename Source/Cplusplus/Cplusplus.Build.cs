// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cplusplus : ModuleRules
{
	public Cplusplus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = true;
		MinFilesUsingPrecompiledHeaderOverride = 1;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
