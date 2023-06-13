// Pirate Adventure Game Vietokhin AD211


#include "Pickups/PAHealthPickup.h"
#include "Components/PAHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HealthPickupLog, All, All)

void APAHealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UPAHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UPAHealthComponent>();
    if (HealthComponent)
    {
        HealthComponent->AddHealth(HealthToAdd);
    }

    UE_LOG(HealthPickupLog, Display, TEXT("HealthPickup was taken"));
}
