// Pirate Adventure Game Vietokhin AD211


#include "Character/Player/PAPlayerCharacter.h"
#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PAStaminaComponent.h"
#include "Weapon/PAMusketProjectile.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerLog, All, All)

APAPlayerCharacter::APAPlayerCharacter() 
{
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());

    StaminaComponent = CreateDefaultSubobject<UPAStaminaComponent>("StaminaComponent");

    HookMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HookMesh");
    HookMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    HookMesh->CastShadow = false;

    MusketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MusketMesh");
    MusketMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    MusketMesh->CastShadow = false;

    MuzzleSocketLocation = MusketMesh->GetSocketLocation("MuzzleSocket");


}

void APAPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();

    check(CameraComponent);
    check(StaminaComponent);

    StaminaComponent->OnStaminaChanged.AddUObject(this, &APAPlayerCharacter::OnStaminaChanged);
}

void APAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APAPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APAPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APAPlayerCharacter::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &APAPlayerCharacter::TurnAround);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APAPlayerCharacter::StartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &APAPlayerCharacter::StopRunning);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APAPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APAPlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APAPlayerCharacter::StopCrouch);
    PlayerInputComponent->BindAction("MusketShot", IE_Pressed, this, &APAPlayerCharacter::MusketShot);
    PlayerInputComponent->BindAction("HookHit", IE_Pressed, this, &APAPlayerCharacter::HookHit);

}

void APAPlayerCharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void APAPlayerCharacter::MoveForward(float Amount)
{
    if (Amount != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Amount);

        if (Amount > 0.0f)
        {
            bIsMovingForward = true;
        }
    }
}

void APAPlayerCharacter::MoveRight(float Amount) 
{
    if (Amount != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Amount);
    }
}

void APAPlayerCharacter::LookUp (float Amount)
{
    AddControllerPitchInput(Amount);
}

void APAPlayerCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(Amount);

} 

void APAPlayerCharacter::OnStaminaChanged(float Stamina)
{
    UE_LOG(PlayerLog, Display, TEXT("Stamina: %.0f"), Stamina);
    if (bIsMovingForward)
    {
        if (!bIsRunning)
        {
            if (Stamina <= 0.0f)
            {
                StopRunning();
            }
            else if (Stamina >= StaminaComponent->GetStamina() && StaminaComponent->CanRun() && bIsRunning)
            {
                StartRunning();
            }
        }
        else
        {
            if (Stamina <= 0.0f || Stamina < StaminaComponent->GetStamina() || !StaminaComponent->CanRun() || !bIsRunning)
            {
                StopRunning();
            }
        }
    }
}

void APAPlayerCharacter::StartRunning()
{
    if (StaminaComponent && StaminaComponent->CanRun())
    {
        UE_LOG(PlayerLog, Display, TEXT("Start Running"));
        bIsRunning = true;
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
        StaminaComponent->StopRecoveringStamina();
        StaminaComponent->DrainStamina();
    }
}

void APAPlayerCharacter::StopRunning()
{
    if (StaminaComponent)
    {
        UE_LOG(PlayerLog, Display, TEXT("Stop Running"));
        bIsRunning = false;
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        StaminaComponent->StopDrainingStamina();
        StaminaComponent->RecoverStamina();
    }
}

void APAPlayerCharacter::StartCrouch()
{
    UE_LOG(PlayerLog, Display, TEXT("Crouch"))
    Crouch();
}

void APAPlayerCharacter::StopCrouch() 
{
    UE_LOG(PlayerLog, Display, TEXT("UnCrouch"))
    UnCrouch();
}

void APAPlayerCharacter::MusketShot() 
{
    UE_LOG(PlayerLog, Warning, TEXT("SHOT"));
    // try and fire a projectile
    if (ProjectileClass != nullptr)
    {
        UWorld* const World = GetWorld();
        if (World != nullptr)
        {
            const FRotator SpawnRotation = GetControlRotation();

            const FVector SpawnLocation = ((MuzzleSocketLocation.IsZero()) ? MuzzleSocketLocation : GetActorLocation());

            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride =
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            World->SpawnActor<APAMusketProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }

    if (MusketShotSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, MusketShotSound, GetActorLocation());
    }
}

void APAPlayerCharacter::HookHit() 
{
    UE_LOG(PlayerLog, Warning, TEXT("HIT"));

    if (HookHitSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, HookHitSound, GetActorLocation());
    }
}

void APAPlayerCharacter::OnDeath() 
{
    Super::OnDeath();
}
