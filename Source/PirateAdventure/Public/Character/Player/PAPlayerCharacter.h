// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Character/PABaseCharacter.h"
#include "PAPlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class PIRATEADVENTURE_API APAPlayerCharacter : public APABaseCharacter
{
	GENERATED_BODY()
	
public:
    APAPlayerCharacter();

    virtual void BeginPlay() override;
    virtual void OnDeath() override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Musket")
    USkeletalMeshComponent* MusketMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hook")
    USkeletalMeshComponent* HookMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Musket")
    float MusketShotAnimationDelay = 0.3;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hook")
    float HookHitAnimationDelay = 0.6;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 600.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 1200.0f;


private:

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void LookUp(float Amount);
    void TurnAround(float Amount);

    bool bIsMovingForward = false;

    void StartRunning();
    void StopRunning();

    void StartCrouch();
    void StopCrouch();

    UFUNCTION(BlueprintCallable)
    void MusketShot();

    UFUNCTION(BlueprintCallable)
    void HookHit();
};