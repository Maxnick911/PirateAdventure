// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "Components/PAStaminaComponent.h"
#include "PAPlayerCharacter.generated.h"

class UCameraComponent;
class UPAHealthComponent;
class UPAStaminaComponent;
class USkeletalMeshComponent;
class APAMusketProjectile;
class APAMusket;
class APAHook;

UCLASS()
class PIRATEADVENTURE_API APAPlayerCharacter : public APABaseCharacter
{
	GENERATED_BODY()
	
public:
    APAPlayerCharacter();

    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void Tick(float DeltaTime) override;

    void OnDeath() override;

    bool IsRunning() const { return bIsRunning; }
    APAMusket* GetMusket() const { return Musket; }

    UPAHealthComponent* GetHealthComponent() const { return HealthComponent; }
    UPAStaminaComponent* GetStaminaComponent() const { return StaminaComponent; }

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UPAStaminaComponent* StaminaComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<APAMusket> MusketClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Musket")
    USkeletalMeshComponent* MusketMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<APAHook> HookClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hook")
    USkeletalMeshComponent* HookMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 600.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 1200.0f;

private:

    APAMusket* Musket;
    APAHook* Hook;

    bool bIsMovingForward = false;
    bool bIsRunning = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void LookUp(float Amount);
    void TurnAround(float Amount);

    void OnStaminaChanged(float Stamina);

    void StartRunning();
    void StopRunning();

    void StartCrouch();
    void StopCrouch();

    void SpawnMusket();
    void SpawnHook();

    void MusketShot();

    void MusketReload();

    void HookHit();
};

