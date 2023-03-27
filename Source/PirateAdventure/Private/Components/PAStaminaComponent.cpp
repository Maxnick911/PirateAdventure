// Pirate Adventure Game Vietokhin AD211

#include "Components/PAStaminaComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
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

    check(MaxStamina);
    SetStamina(MaxStamina);
}

void UPAStaminaComponent::DrainStamina()
{
    if (GetWorld() && CanRun() && CurrentStamina >= 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(DrainStaminaTimerHandle, this, &UPAStaminaComponent::DrainStamina, 1.0f, true);
        SetStamina(CurrentStamina - StaminaDrainRate);
    }

    if (CurrentStamina <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(DrainStaminaTimerHandle);
        RecoverStamina();
    }
}

void UPAStaminaComponent::RecoverStamina()
{
    if (GetWorld() && CurrentStamina >= 0.0f)
    {
    GetWorld()->GetTimerManager().SetTimer(RecoverStaminaTimerHandle, this, &UPAStaminaComponent::RecoverStamina, 1.0f, true);
    SetStamina(CurrentStamina + StaminaRecoveryRate);
    }

    if (CurrentStamina >= MaxStamina)
    {
        GetWorld()->GetTimerManager().ClearTimer(RecoverStaminaTimerHandle);
    }
}

void UPAStaminaComponent::SetStamina(float NewStamina)
{
    CurrentStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
    OnStaminaChanged.Broadcast(CurrentStamina);
}

bool UPAStaminaComponent::CanRun() const
{
    return CurrentStamina >= StaminaDrainRate;
}

float UPAStaminaComponent::GetStamina() const
{
    return CurrentStamina;
}