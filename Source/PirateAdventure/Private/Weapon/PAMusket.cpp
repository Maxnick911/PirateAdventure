// Pirate Adventure Game Vietokhin AD211

#include "Weapon/PAMusket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon/PAMusketProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(MusketLog, All, All)

APAMusket::APAMusket()
{
    PrimaryActorTick.bCanEverTick = false;

    MusketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MusketMesh");
    SetRootComponent(MusketMesh);
}

void APAMusket::BeginPlay()
{
    Super::BeginPlay();

    check(MusketMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));

    AnimInstance = MusketMesh->GetAnimInstance();
    if(AnimInstance)
    {
        UE_LOG(MusketLog, Display, TEXT("AnimInstance is valid"));
    }
    else
    {
        UE_LOG(MusketLog, Display, TEXT("AnimInstance - Error"));
    }
    CurrentAmmo = DefaultAmmo;
}

void APAMusket::Fire()
{
    MakeShot();
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
    }
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APAMusket::EnableShoot, ShotDelay, false);
}

void APAMusket::Reload()
{
    if (!IsAmmoEmpty() && !IsClipFull() && CanReload())
    {
        ChangeClip();
    }
}

void APAMusket::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        bCanShoot = false;
        return;
    }

    if(bCanShoot)
    {
        SpawnProjectile();
        SpawnSmokeEmitter();
        PlayShotSound();
        PlayShotAnimation();
        DecreaseAmmo();
    }
    bCanShoot = false;
}

void APAMusket::SpawnProjectile()
{
    const FTransform SpawnTransform = MusketMesh->GetSocketTransform(MuzzleSocketName);
    APAMusketProjectile* Projectile = GetWorld()->SpawnActorDeferred<APAMusketProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        const FVector Direction = SpawnTransform.GetRotation().GetForwardVector();
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
        
    }
}

void APAMusket::DecreaseAmmo() 
{
    if(CurrentAmmo.Bullets == 0)
    {
        UE_LOG(MusketLog, Warning, TEXT("Clip is empty"));
        return;
    }
    CurrentAmmo.Bullets--;
    LogAmmo();
    if(IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
    }
    NotifyAmmoChanged();
}

void APAMusket::NotifyAmmoChanged()
{
    FAmmoData AmmoData;
    GetMusketAmmoData(AmmoData);

    OnAmmoChanged.Broadcast(AmmoData);
}

void APAMusket::ChangeClip()
{
    if (CurrentAmmo.Clips == 0)
    {
        return;
    }

    if(!CurrentAmmo.Infinite)
    {
        if(CurrentAmmo.Clips == 0)
        {
            UE_LOG(MusketLog, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    PlayReloadAnimation();
    PlayReloadSound();

    bCanShoot = false;
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(MusketLog, Display, TEXT("Clip has been changed"));
}

void APAMusket::AddClips(int32 ClipsToAdd)
{
    CurrentAmmo.Clips += ClipsToAdd;
    LogAmmo();
}

void APAMusket::LogAmmo() 
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(MusketLog, Display, TEXT("%s"), *AmmoInfo);
}

void APAMusket::SpawnSmokeEmitter()
{
    if (!GetWorld()) return;

    const FTransform SpawnTransform = MusketMesh->GetSocketTransform(MuzzleSocketName);
    const FVector SocketLocation = SpawnTransform.GetLocation();
    const FRotator SocketRotation = SpawnTransform.Rotator();

    UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlashEmitter, SocketLocation, SocketRotation);

    if (ParticleComponent)
    {
        float SmokeEmitterLifeTime = 0.2f;

        FTimerDelegate EmitterDestroyTimerDelegate;
        EmitterDestroyTimerDelegate.BindLambda([=](){ ParticleComponent->DestroyComponent(); });
        GetWorldTimerManager().SetTimer(EmitterDestroyTimerHandle, EmitterDestroyTimerDelegate, SmokeEmitterLifeTime, false);
    }
}

void APAMusket::PlayShotAnimation()
{
    if(!AnimInstance || !ShotAnimation) return;
    MusketMesh->PlayAnimation(ShotAnimation, false);
}

void APAMusket::PlayShotSound()
{
    if (!ShotSound) return;

    const FTransform SpawnTransform = MusketMesh->GetSocketTransform(MuzzleSocketName);
    UGameplayStatics::PlaySoundAtLocation(this, ShotSound, SpawnTransform.GetLocation());
}

void APAMusket::PlayReloadAnimation()
{
    if (!AnimInstance) return;
    MusketMesh->PlayAnimation(ReloadAnimation, false);
}

void APAMusket::PlayReloadSound()
{
    if (!ReloadSound) return;

    const FTransform SpawnTransform = MusketMesh->GetSocketTransform(MuzzleSocketName);
    UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, SpawnTransform.GetLocation());
}

bool APAMusket::GetMusketAmmoData(FAmmoData& AmmoData) const
{
    AmmoData = CurrentAmmo;
    return true;
}

void APAMusket::EnableShoot()
{
    bCanShoot = true;
}

bool APAMusket::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool APAMusket::IsClipFull() const
{
    return CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool APAMusket::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool APAMusket::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}