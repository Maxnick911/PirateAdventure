// Pirate Adventure Game Vietokhin AD211


#include "Character/Enemy/Services/PAFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/PAAIPerceptionComponent.h"

UPAFindEnemyService::UPAFindEnemyService()
{
    NodeName = "Find Enemy";
}

void UPAFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->FindComponentByClass<UPAAIPerceptionComponent>();
        if(PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}