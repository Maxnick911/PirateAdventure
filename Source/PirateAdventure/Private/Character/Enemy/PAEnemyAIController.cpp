// Pirate Adventure Game Vietokhin AD211


#include "Character/Enemy/PAEnemyAIController.h"
#include "Components/PAAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APAEnemyAIController::APAEnemyAIController() 
{
    PAAIPerceptionComponent = CreateDefaultSubobject<UPAAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*PAAIPerceptionComponent);

}

void APAEnemyAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* APAEnemyAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
