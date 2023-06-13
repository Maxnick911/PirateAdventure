// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PAHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PIRATEADVENTURE_API UPAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPAHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const;

	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	void SetHealth(float NewHealth);
    void AddHealth(float HealthAmount);

	UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

	virtual void BeginPlay() override;

private:

	float CurrentHealth = 0.0f;




};
