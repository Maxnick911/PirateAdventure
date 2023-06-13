// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PANextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class PIRATEADVENTURE_API UPANextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UPANextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;


};
