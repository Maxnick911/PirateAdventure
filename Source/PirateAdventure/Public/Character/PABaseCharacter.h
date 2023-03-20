// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PABaseCharacter.generated.h"

class UPAHealthComponent;
class UTextRenderComponent;

UCLASS()
class PIRATEADVENTURE_API APABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APABaseCharacter();

    virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	virtual void OnDeath();

	void OnHealthChanged(float Health);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPAHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 12000.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(1.0f, 100.0f);

	UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

};