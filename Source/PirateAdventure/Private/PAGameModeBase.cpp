// Pirate Adventure Game Vietokhin AD211


#include "PAGameModeBase.h"

APAGameModeBase::APAGameModeBase() 
{
    DefaultPawnClass = APABaseCharacter::StaticClass();
    PlayerControllerClass = APABaseCharacter::StaticClass();
    HUDClass = APABaseCharacter::StaticClass();
}

