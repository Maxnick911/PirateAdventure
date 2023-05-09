// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "PAEnemyCharacter.generated.h"


UCLASS()
class PIRATEADVENTURE_API APAEnemyCharacter : public APABaseCharacter
{
	GENERATED_BODY()
	
public:
	APAEnemyCharacter();

	virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void Tick(float DeltaTime) override;

protected:

};
