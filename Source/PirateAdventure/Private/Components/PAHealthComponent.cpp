// Pirate Adventure Game Vietokhin AD211

#include "Components/PAHealthComponent.h"
#include "GameFramework/Actor.h"

UPAHealthComponent::UPAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPAHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(CurrentHealth);
}

float UPAHealthComponent::GetHealth() const
{
    return CurrentHealth;
}

void UPAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(MaxHealth > 0.0f);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UPAHealthComponent::OnTakeAnyDamage);
    }
}

void UPAHealthComponent::AddHealth(float HealthAmount)
{
    SetHealth(CurrentHealth + HealthAmount);
    OnHealthChanged.Broadcast(CurrentHealth);
}

void UPAHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0 || IsDead() || !GetWorld()) return;

    SetHealth(CurrentHealth - Damage);
    OnHealthChanged.Broadcast(CurrentHealth);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UPAHealthComponent::SetHealth(float NewHealth) 
{
    CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}