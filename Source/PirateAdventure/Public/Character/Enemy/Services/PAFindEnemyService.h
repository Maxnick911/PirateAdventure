// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PAFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class PIRATEADVENTURE_API UPAFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:

	UPAFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
