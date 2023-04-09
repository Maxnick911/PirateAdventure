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

    void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Components")
    UStaticMeshComponent* ProjectileMeshComponent;

    UFUNCTION()
    void FireInDirection(const FVector& ShootDirection);

UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
        const FHitResult& Hit);


protected:
    void BeginPlay() override;

};
