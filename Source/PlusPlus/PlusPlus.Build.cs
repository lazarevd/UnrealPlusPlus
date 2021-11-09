// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlusPlus : ModuleRules
{
	public PlusPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"ProceduralMeshComponent"
		});
	}
}
