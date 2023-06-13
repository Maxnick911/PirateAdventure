// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "PAAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class PIRATEADVENTURE_API UPAAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
    AActor* GetClosestEnemy() const;
};
