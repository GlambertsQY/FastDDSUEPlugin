// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class FastDDSUEPlugin : ModuleRules
{
	public FastDDSUEPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
		// bEnableExceptions = true;

		// string fastrtpsHome = Environment.GetEnvironmentVariable("FASTRTPSHOME");
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
		PublicIncludePaths.Add( Path.Combine(ModuleDirectory, "include"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "libfastcdr-1.1.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "fastrtps-2.11.lib"));
		
		PublicDefinitions.Add("WIN32");
		PublicDefinitions.Add("_WINDOWS");
		PublicDefinitions.Add("FASTRTPS_DYN_LINK");
		PublicDefinitions.Add("FASTRTPS_NO_LIB");
		PublicDefinitions.Add("FASTCDR_NO_LIB");
		
		// 这句没用？
		// RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "dlls", "fastrtps-2.11.dll"));
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
