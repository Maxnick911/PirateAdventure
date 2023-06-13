// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PABasePickup.h"
#include "PAHealthPickup.generated.h"

UCLASS()
class PIRATEADVENTURE_API APAHealthPickup : public APABasePickup
{
	GENERATED_BODY()
	

protected:
    void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1"))
    float HealthToAdd = 20.0f;
};
