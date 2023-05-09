// Pirate Adventure Game Vietokhin AD211


#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PAHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

APABaseCharacter::APABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UPAHealthComponent>("HealthComponent");
    check(HealthComponent != nullptr);

}

void APABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &APABaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &APABaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &APABaseCharacter::OnGroundLanded);

}

void APABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APABaseCharacter::OnDeath ()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("%s is dead"), *GetName());

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void APABaseCharacter::OnHealthChanged(float Health) 
{
    UE_LOG(BaseCharacterLog, Display, TEXT("%s's Health: %.0f"), *GetName(), Health);
}

void APABaseCharacter::OnGroundLanded (const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FallDamage, FPointDamageEvent{}, nullptr, nullptr);

    UE_LOG(BaseCharacterLog, Display, TEXT("%s recived landed damage: %f"), *GetName(), FallDamage);
}
