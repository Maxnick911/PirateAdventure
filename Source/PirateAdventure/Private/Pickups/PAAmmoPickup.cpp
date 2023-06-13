// Pirate Adventure Game Vietokhin AD211

#include "Pickups/PAAmmoPickup.h"
#include "Components/PAHealthComponent.h"
#include "Character/Player/PAPlayerCharacter.h"
#include "Weapon/PAMusket.h"

DEFINE_LOG_CATEGORY_STATIC(AmmoPickupLog, All, All)

void APAAmmoPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(AmmoPickupLog, Display, TEXT("Musket is found"));
    APAPlayerCharacter* Character = Cast<APAPlayerCharacter>(OtherActor);
    if (Character)
    {
        APAMusket* Musket = Character->GetMusket();
        if (Musket)
        {
            UE_LOG(AmmoPickupLog, Display, TEXT("Adding clips to character's musket"));
            Musket->AddClips(ClipsToAdd);
        }
        else
        {
            UE_LOG(AmmoPickupLog, Display, TEXT("Musket is not found"));
        }
    }
}
