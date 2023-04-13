// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PAHUD.generated.h"

/**
 * 
 */
UCLASS()
class PIRATEADVENTURE_API APAHUD : public AHUD
{
	GENERATED_BODY()

public:
    void DrawHUD() override;

private:
    void DrawCrosshair();
};
