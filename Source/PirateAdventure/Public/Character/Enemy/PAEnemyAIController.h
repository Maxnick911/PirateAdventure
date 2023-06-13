// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PAEnemyAIController.generated.h"

class UPAAIPerceptionComponent;

UCLASS()
class PIRATEADVENTURE_API APAEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
    APAEnemyAIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UPAAIPerceptionComponent* PAAIPerceptionComponent;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    FName FocusOnKeyName = "EnemyActor";

    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocusOnActor() const;
};
