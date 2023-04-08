// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "Components/PAStaminaComponent.h"
#include "PAPlayerCharacter.generated.h"

class UCameraComponent;
class UPAStaminaComponent;
class USkeletalMeshComponent;
class APAMusketProjectile;

UCLASS()
class PIRATEADVENTURE_API APAPlayerCharacter : public APABaseCharacter
{
	GENERATED_BODY()
	
public:
    APAPlayerCharacter();

    virtual void BeginPlay() override;
    virtual void OnDeath() override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void Tick(float DeltaTime) override;

    bool IsRunning() const { return bIsRunning; };

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UPAStaminaComponent* StaminaComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Musket")
    USkeletalMeshComponent* MusketMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Musket")
    float MusketShotAnimationDelay = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Musket")
    USoundBase* MusketShotSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Musket")
    FVector MuzzleSocketLocation;

    UPROPERTY(EditDefaultsOnly, Category = "Musket")
    TSubclassOf<class APAMusketProjectile> ProjectileClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hook")
    USkeletalMeshComponent* HookMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hook")
    USoundBase* HookHitSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hook")
    float HookHitAnimationDelay = 0.6f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 600.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 1200.0f;

    void OnStaminaChanged(float Stamina);

private:

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void LookUp(float Amount);
    void TurnAround(float Amount);

    bool bIsMovingForward = false;
    bool bIsRunning = false;

    void StartRunning();
    void StopRunning();

    void StartCrouch();
    void StopCrouch();

    UFUNCTION(BlueprintCallable)
    void MusketShot();

    UFUNCTION(BlueprintCallable)
    void HookHit();

};
