// Pirate Adventure Game Vietokhin AD211


#include "Components/PAAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/PAHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UPAAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for(const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = PercieveActor->FindComponentByClass<UPAHealthComponent>();
        if(HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() = Pawn->GetActorLocation()).Size();
            if(CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }
    return BestPawn;
}