// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PABasePickup.h"
#include "PAAmmoPickup.generated.h"

class APAMusket;

UCLASS()
class PIRATEADVENTURE_API APAAmmoPickup : public APABasePickup
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsToAdd = 5; 

private:
    void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
