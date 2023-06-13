// Pirate Adventure Game Vietokhin AD211


#include "Character/Enemy/PAEnemyCharacter.h"
#include "Components/PAHealthComponent.h"
#include "Character/Enemy/PAEnemyAIController.h"
#include "Character/Player/PAPlayerCharacter.h"
#include <Kismet/GameplayStatics.h>

APAEnemyCharacter::APAEnemyCharacter() 
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = APAEnemyAIController::StaticClass();
}

void APAEnemyCharacter::Attack(APawn* Target)
{
    if (!Target) return;
    UGameplayStatics::ApplyDamage(Target, DamageAmount, GetController(), this, UDamageType::StaticClass());

    PlayAttackSound();
    PlayAttackAnimation();
}

void APAEnemyCharacter::PlayAttackSound()
{
    if (!AttackSound) return;
    UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
}

void APAEnemyCharacter::PlayAttackAnimation()
{
    if (!AttackAnimation) return;
    GetMesh()->PlayAnimation(AttackAnimation, false);
}