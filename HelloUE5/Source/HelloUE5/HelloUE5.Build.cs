// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HelloUE5 : ModuleRules
{
	public HelloUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
