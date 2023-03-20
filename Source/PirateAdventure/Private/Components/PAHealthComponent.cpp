// Pirate Adventure Game Vietokhin AD211

#include "Components/PAHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All)

UPAHealthComponent::UPAHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

bool UPAHealthComponent::IsDead()
{
    return FMath::IsNearlyZero(Health);
}

float UPAHealthComponent::GetHealth()
{
    return Health;
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

void UPAHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(HealthComponentLog, Display, TEXT("Health: %.0f"), Health);
    if (Damage <= 0.0 || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UPAHealthComponent::SetHealth(float NewHealth) 
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}