// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Study002 : ModuleRules
{
	public Study002(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GeometryScriptingCore", "DynamicMesh" });
	}
}
