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

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    float GetStamina() const;

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void DrainStamina();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void RecoverStamina();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetStamina(float NewStamina);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    bool CanRun() const;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxStamina = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Stamina")
    float StaminaDrainRate = 10.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Stamina")
    float StaminaRecoveryRate = 5.0f;

private: 
    float CurrentStamina = 0.0f;

    FTimerHandle DrainStaminaTimerHandle;
    FTimerHandle RecoverStaminaTimerHandle;
};
