// Pirate Adventure Game Vietokhin AD211


#include "Character/Player/PAPlayerCharacter.h"
#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerLog, All, All)

APAPlayerCharacter::APAPlayerCharacter() 
{
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());

    HookMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HookMesh");
    HookMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    MusketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MusketMesh");
    MusketMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APAPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();

    check(CameraComponent);
}

void APAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APAPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APAPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APAPlayerCharacter::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &APAPlayerCharacter::TurnAround);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APAPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APAPlayerCharacter::StartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &APAPlayerCharacter::StopRunning);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APAPlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APAPlayerCharacter::StopCrouch);
    PlayerInputComponent->BindAction("MusketShot", IE_Pressed, this, &APAPlayerCharacter::MusketShot);
    PlayerInputComponent->BindAction("HookHit", IE_Pressed, this, &APAPlayerCharacter::HookHit);


}

void APAPlayerCharacter::MoveForward(float Amount) 
{
    if (Amount != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Amount);

        if (Amount >= 0.0f)
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

void APAPlayerCharacter::StartRunning() 
{
    if (bIsMovingForward)
    {
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
        UE_LOG(PlayerLog, Display, TEXT("Running"));
    }
}

void APAPlayerCharacter::StopRunning() 
{
    UE_LOG(PlayerLog, Display, TEXT("Stop running"))
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APAPlayerCharacter::StartCrouch ()
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
}

void APAPlayerCharacter::HookHit() 
{
    UE_LOG(PlayerLog, Warning, TEXT("HIT"));
}

void APAPlayerCharacter::OnDeath() 
{
    Super::OnDeath();
}
