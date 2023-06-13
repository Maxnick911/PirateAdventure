// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "PAEnemyCharacter.generated.h"

class UPAHealthComponent;
class USoundBase;
class UAnimMontage;

UCLASS()
class PIRATEADVENTURE_API APAEnemyCharacter : public APABaseCharacter
{
	GENERATED_BODY()
	
public:
	APAEnemyCharacter();

    void Attack(APawn* Target);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UAnimMontage* AttackAnimation;

private:
	void PlayAttackSound();
    void PlayAttackAnimation();

};
