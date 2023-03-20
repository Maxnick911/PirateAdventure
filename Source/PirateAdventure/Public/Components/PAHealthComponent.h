// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PIRATEADVENTURE_API UPAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPAHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BLueprintCallable, Category = "Health")
    bool IsDead();

	float GetHealth();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

	virtual void BeginPlay() override;

private:

	float Health = 0.0f;

	UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);

};
