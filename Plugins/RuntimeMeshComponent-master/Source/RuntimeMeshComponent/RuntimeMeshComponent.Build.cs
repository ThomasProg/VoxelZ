// Copyright 2016-2018 Chris Conway (Koderz). All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class RuntimeMeshComponent : ModuleRules
{
    public RuntimeMeshComponent(ReadOnlyTargetRules rules) : base(rules)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //PublicIncludePaths.AddRange(
        //    new string[] {
        //             "RuntimeMeshComponent/Public"
        //        // ... add public include paths required here ...
        //    }
        //    );
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));


        //PrivateIncludePaths.AddRange(
        //     new string[] {
        //             "RuntimeMeshComponent/Private",
        //         // ... add other private include paths required here ...
        //     }
        //     );
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

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
				// ... add private dependencies that you statically link with here ...	
                "RenderCore",
                "ShaderCore",
                "RHI",
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
