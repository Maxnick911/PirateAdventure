// Pirate Adventure Game Vietokhin AD211


#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PAHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

APABaseCharacter::APABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UPAHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(GetCharacterMovement());
    check(HealthComponent);
    check(HealthTextComponent);

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &APABaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &APABaseCharacter::OnHealthChanged);
}

void APABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APABaseCharacter::OnDeath ()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

}

void APABaseCharacter::OnHealthChanged(float Health) 
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void APABaseCharacter::OnGroundLanded (const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FallDamage, FPointDamageEvent{}, nullptr, nullptr);

    UE_LOG(BaseCharacterLog, Display, TEXT("Player %s recived landed damage: %f"), *GetName(), FallDamage);

}
