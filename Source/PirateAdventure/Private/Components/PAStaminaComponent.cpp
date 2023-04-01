// Pirate Adventure Game Vietokhin AD211

#include "Components/PAStaminaComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/PAPlayerCharacter.h"

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
    if (GetWorld())
    {
        if (CanRun() && MaxStamina / CurrentStamina >= 5.0f)
        {
            GetWorld()->GetTimerManager().SetTimer(DrainStaminaTimerHandle, this, &UPAStaminaComponent::DrainStamina, 0.5f, true);
            SetStamina(CurrentStamina - StaminaDrainRate);
        }
        else
        {
            StopDrainingStamina();
        }
    }
}

void UPAStaminaComponent::StopDrainingStamina()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(DrainStaminaTimerHandle);
    }
}

void UPAStaminaComponent::RecoverStamina()
{
    if (GetWorld() && CurrentStamina < MaxStamina)
    {
        GetWorld()->GetTimerManager().SetTimer(RecoverStaminaTimerHandle, this, &UPAStaminaComponent::RecoverStamina, 0.5f, true);
        SetStamina(CurrentStamina + StaminaRecoveryRate);
    }

    if (CurrentStamina > MaxStamina)
    {
        StopRecoveringStamina();
    }
}

void UPAStaminaComponent::StopRecoveringStamina()
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(RecoverStaminaTimerHandle);
    }
}

void UPAStaminaComponent::SetStamina(float NewStamina)
{
    OnStaminaChanged.Broadcast(CurrentStamina);
    CurrentStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
}

bool UPAStaminaComponent::CanRun() const
{
    return (CurrentStamina - StaminaDrainRate) >= 0.0f && (CurrentStamina > 0.0f);
}

float UPAStaminaComponent::GetStamina() const
{
    return CurrentStamina;
}

float UPAStaminaComponent::GetMaxStamina() const
{
    return MaxStamina;
}
