// Pirate Adventure Game Vietokhin AD211


#include "Character/Enemy/Tasks/PAAttackTask.h"
#include "Character/Enemy/PAEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UPAAttackTask::UPAAttackTask()
{
    NodeName = "Attack";
}

EBTNodeResult::Type UPAAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Failed;

    const auto Pawn = Cast<APAEnemyCharacter>(Controller->GetPawn());
    if (!Pawn) return EBTNodeResult::Failed;

    const auto Target = Cast<APawn>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
    if (!Target) return EBTNodeResult::Failed;

    Pawn->Attack(Target);
    return EBTNodeResult::Succeeded;
}