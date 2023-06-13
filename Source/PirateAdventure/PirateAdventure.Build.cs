// Pirate Adventure Game Vietokhin AD211

using UnrealBuildTool;

public class PirateAdventure : ModuleRules
{
	public PirateAdventure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",		
			"CoreUObject",	
			"Engine", 
			"InputCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{
			"PirateAdventure/Public/Character",
			"PirateAdventure/Public/Character/Enemy",
			"PirateAdventure/Public/Character/Enemy/Tasks",
			"PirateAdventure/Public/Character/Player",
			"PirateAdventure/Public/Components",
			"PirateAdventure/Public/Development",
			"PirateAdventure/Public/Pickups",
			"PirateAdventure/Public/UI",
			"PirateAdventure/Public/Weapon"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
