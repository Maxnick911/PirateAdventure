// Pirate Adventure Game Vietokhin AD211

using UnrealBuildTool;
using System.Collections.Generic;

public class PirateAdventureEditorTarget : TargetRules
{
	public PirateAdventureEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "PirateAdventure" } );
	}
}
