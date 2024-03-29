// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ReturnToAlderaan : ModuleRules
{
	public ReturnToAlderaan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Paper2D", "NavigationSystem" });
	}
}
