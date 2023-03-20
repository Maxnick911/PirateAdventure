// Pirate Adventure Game Vietokhin AD211

using UnrealBuildTool;
using System.Collections.Generic;

public class PirateAdventureTarget : TargetRules
{
	public PirateAdventureTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "PirateAdventure" } );
	}
}
