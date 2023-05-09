// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAMusketProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PIRATEADVENTURE_API APAMusketProjectile : public AActor
{
	GENERATED_BODY()

public:
    APAMusketProjectile();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:

    void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
    float DamageAmount = 25.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
    float OnProjectileHitImpulseMagnitude = 100000.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
    float ProjectileLifeTime = 3.0f;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

};
