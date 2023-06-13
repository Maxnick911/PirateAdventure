// Pirate Adventure Game Vietokhin AD211


#include "Weapon/PAMusketProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

APAMusketProjectile::APAMusketProjectile()
{
    PrimaryActorTick.bCanEverTick = false;


    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->SetGenerateOverlapEvents(true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &APAMusketProjectile::OnProjectileHit);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

}

void APAMusketProjectile::BeginPlay() 
{
    Super::BeginPlay();

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(ProjectileLifeTime);

}

void APAMusketProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (GetWorld())
    {
        MovementComponent->StopMovementImmediately();

        UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, Hit.ImpactNormal, Hit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, nullptr);

        UCharacterMovementComponent* OtherCharacterMovement = OtherActor->FindComponentByClass<UCharacterMovementComponent>();
        if (OtherCharacterMovement)
        {
            FVector ImpulseDirection = (OtherActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            OtherCharacterMovement->AddImpulse(ImpulseDirection * OnProjectileHitImpulseMagnitude, false);
        }
        Destroy();
    }
}
