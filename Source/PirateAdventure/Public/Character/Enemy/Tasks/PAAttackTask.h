// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PAAttackTask.generated.h"


UCLASS()
class PIRATEADVENTURE_API UPAAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UPAAttackTask();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector TargetKey;

};
