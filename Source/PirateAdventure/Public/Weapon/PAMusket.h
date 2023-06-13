// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Player/PAPlayerCharacter.h"
#include "PAMusket.generated.h"

class USkeletalMeshComponent;
class APAMusketProjectile;
class UParticleSystem;
class UAnimationAsset;
class USoundBase;
class FName;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedSignature, FAmmoData& AmmoData);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (EditCondition = "|Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo") 
    bool Infinite;
};

UCLASS()
class PIRATEADVENTURE_API APAMusket : public AActor
{
	GENERATED_BODY()
	
public:	
	APAMusket();

	UFUNCTION(BlueprintCallable)
	void Fire();

    UFUNCTION(BlueprintCallable)
    void Reload();

    bool GetMusketAmmoData(FAmmoData& AmmoData) const;
    void AddClips(int32 ClipsToAdd);

    bool CanReload() const;
    void NotifyAmmoChanged();
    void ChangeClip();

    FOnAmmoChangedSignature OnAmmoChanged;

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TSubclassOf<APAMusketProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* MusketMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
    float ShotDelay = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
    UParticleSystem* MuzzleFlashEmitter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    USoundBase* ShotSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UAnimationAsset* ShotAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UAnimationAsset* ReloadAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    USoundBase* ReloadSound;
    
private:
    FTimerHandle ShotTimerHandle;
    FTimerHandle SmokeEmitterTimerHandle;
    FTimerHandle EmitterDestroyTimerHandle;


    bool bCanShoot = true;
    UAnimInstance* AnimInstance;
    FAmmoData CurrentAmmo;

    void MakeShot();

    void SpawnProjectile();
    void PlayShotSound();
    void SpawnSmokeEmitter();
    void PlayShotAnimation();
    void PlayReloadAnimation();
    void PlayReloadSound();

    void EnableShoot();

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    bool IsClipFull() const;
    void LogAmmo();
};