// Pirate Adventure Game Vietokhin AD211


#include "UI/PAPlayerHUDWidget.h"

#include "Components/PAHealthComponent.h"
#include "Components/PAStaminaComponent.h"

float UPAPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!Player)
    {
        return 0.0f;
    }

    const auto Component = Player->GetComponentByClass(UPAHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UPAHealthComponent>(Component);
    if (!HealthComponent)
    {
        return 0.0f;
    }

    return HealthComponent->GetHealthPercent();
}

float UPAPlayerHUDWidget::GetStaminaPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
    {
        return 0.0f;
    }

    const auto Component = Player->GetComponentByClass(UPAStaminaComponent::StaticClass());
    const auto StaminaComponent = Cast<UPAStaminaComponent>(Component);
    if(!StaminaComponent)
    {
        return 0.0f;
    }

    return StaminaComponent->GetStaminaPercent();
}
