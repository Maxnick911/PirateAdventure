// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PABasePickup.generated.h"

class USphereComponent;
class USoundBase;

UCLASS()
class PIRATEADVENTURE_API APABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APABasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USoundBase* PickupSound;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

};
