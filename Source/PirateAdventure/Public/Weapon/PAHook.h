// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAHook.generated.h"

class USkeletalMeshComponent;
class USoundBase;
class UAnimationAsset;
class UBoxComponent;
class USceneComponent;

UCLASS()
class PIRATEADVENTURE_API APAHook : public AActor
{
	GENERATED_BODY()
	
public:	
	APAHook();

	void MakeHit();

protected:
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* HookMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* CollisionRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UAnimationAsset* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    float HookHitDelay = 0.3f;

	UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:	
	bool bCanHit = true;
    FTimerHandle HookHitDelayTimerHandle;

	void PlayAttackAnimation();
    void PlayAttackSound();
    void EnableHit();
};
