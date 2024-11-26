// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class FastDDSUEPlugin : ModuleRules
{
	public FastDDSUEPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
		bEnableExceptions = true;
		// string fastrtpsHome = Environment.GetEnvironmentVariable("FASTRTPSHOME");
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
		PublicIncludePaths.Add( Path.Combine(ModuleDirectory, "include"));

        
		// PublicDefinitions.Add("FASTRTPS_DYN_LINK");
		PublicDefinitions.Add("FASTRTPS_NO_LIB"); // static link
		PublicDefinitions.Add("FASTCDR_NO_LIB"); // static link
		PublicDefinitions.Add("FOONATHAN_MEMORY=1");
		PublicDefinitions.Add("FOONATHAN_MEMORY_VERSION_MAJOR=0");
		PublicDefinitions.Add("FOONATHAN_MEMORY_VERSION_MINOR=7");
		PublicDefinitions.Add("FOONATHAN_MEMORY_VERSION_PATCH=3");
		// PublicDefinitions.Add("FASTCDR_DYN_LINK");
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicDefinitions.Add("WIN32");
			PublicDefinitions.Add("_WINDOWS");
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "win64", "libfastcdr-1.1.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "win64", "libfastrtps-2.11.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "win64", "foonathan_memory-0.7.3.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "win64", "tinyxml2.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "win64", "ShLwApi.Lib"));
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastrtps-2.11.dll"), Path.Combine(ModuleDirectory, "dlls", "fastrtps-2.11.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastcdr-1.1.dll"), Path.Combine(ModuleDirectory, "dlls", "fastcdr-1.1.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "foonathan_memory-0.7.3.dll"), Path.Combine(ModuleDirectory, "dlls", "foonathan_memory-0.7.3.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "tinyxml2.dll"), Path.Combine(ModuleDirectory, "dlls", "tinyxml2.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastrtps-2.0.dll"), Path.Combine(ModuleDirectory, "dlls", "fastrtps-2.0.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastcdr-1.0.dll"), Path.Combine(ModuleDirectory, "dlls", "fastcdr-1.0.dll"), StagedFileType.NonUFS);
		}
		// Hololens is no longer supported after UE5.1
		#if !UE_5_1_OR_LATER
		else if (Target.Platform == UnrealTargetPlatform.HoloLens)
		{
			PublicDefinitions.Add("WIN32");
			PublicDefinitions.Add("_WINDOWS");
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "libfastcdr-1.1.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "libfastrtps-2.11.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "foonathan_memory-0.7.3.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "tinyxml2.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "AdvAPI32.Lib"));
			// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "ShLwApi.Lib"));
			// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "iphlpapi.lib"));
			// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "arm64", "UserEnv.Lib"));
			// 在打包的时候
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastrtps-2.0.dll"), Path.Combine(ModuleDirectory, "dlls", "arm64", "fastrtps-2.0.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "fastcdr-1.0.dll"), Path.Combine(ModuleDirectory, "dlls", "arm64", "fastcdr-1.0.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "foonathan_memory-0.7.3.dll"), Path.Combine(ModuleDirectory, "dlls", "arm64", "foonathan_memory-0.7.3.dll"), StagedFileType.NonUFS);
			// RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "tinyxml2.dll"), Path.Combine(ModuleDirectory, "dlls", "arm64", "tinyxml2.dll"), StagedFileType.NonUFS);
		}
		#endif
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDefinitions.Add("__INTERNALDEBUG=1");
			PublicDefinitions.Add("ANDROID");
			PublicDefinitions.Add("_MSC_VER=0");
			// __APPLE__ = 0 seems no effect
			PublicDefinitions.Add("__APPLE__=0");
			PublicDefinitions.Add("__FreeBSD__=0");
			PublicDefinitions.Add("__VXWORKS__=0");
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "android_arm64", "libfastcdr.a"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "android_arm64", "libfastrtps.a"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "android_arm64", "libfoonathan_memory-0.7.3.a"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libs", "android_arm64", "libtinyxml2.a"));
		}
		
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
