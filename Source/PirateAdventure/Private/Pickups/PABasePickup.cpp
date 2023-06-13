// Pirate Adventure Game Vietokhin AD211


#include "Pickups/PABasePickup.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Weapon/PAMusketProjectile.h>
#include <Character/Enemy/PAEnemyCharacter.h>

DEFINE_LOG_CATEGORY_STATIC(BasePickupLog, All, All)

APABasePickup::APABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void APABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
    check(CollisionComponent);
}

void APABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    
    if (OtherActor && !OtherActor->IsA<APAMusketProjectile>())
    {
        if (!PickupSound) return;

        UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
        Destroy();
    }
}