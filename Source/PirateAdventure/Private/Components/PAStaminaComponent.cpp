// Pirate Adventure Game Vietokhin AD211

#include "Components/PAStaminaComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(StaminaComponentLog, All, All)


UPAStaminaComponent::UPAStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPAStaminaComponent::BeginPlay()
{
    Super::BeginPlay();

    SetStamina(MaxStamina);
}

void UPAStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
    ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
    if (OwningCharacter && OwningCharacter->GetCharacterMovement()->IsMovingOnGround())
    {
        if (OwningCharacter->GetVelocity().Size() > 0.f)
        {
            SetStamina(CurrentStamina - StaminaDrainRate * DeltaTime);
        }
        else
        {
            SetStamina(CurrentStamina + StaminaRegenRate * DeltaTime);
        }
    }
}

void UPAStaminaComponent::SetStamina(float NewStamina) 
{
    CurrentStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
    OnStaminaChanged.Broadcast(CurrentStamina);
}

float UPAStaminaComponent::GetStamina() const
{
    return CurrentStamina;
}