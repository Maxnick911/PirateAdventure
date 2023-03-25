// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PAStaminaComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATEADVENTURE_API UPAStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPAStaminaComponent();

    FOnStaminaChangedSignature OnStaminaChanged;

    UFUNCTION(BlueprintCallable)
    float GetStamina() const;

protected:
    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxStamina = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Stamina")
    float StaminaDrainRate = 10.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Stamina")
    float StaminaRegenRate = 5.0f;

    void SetStamina(float NewStamina);

private: 

    float CurrentStamina;

};
