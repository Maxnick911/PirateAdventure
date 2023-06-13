// Pirate Adventure Game Vietokhin AD211


#include "Character/Player/PAPlayerCharacter.h"
#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PAStaminaComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/PAMusket.h"
#include "Weapon/PAHook.h"
#include "Engine/World.h"
#include "UI/PAPlayerHUDWidget.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerLog, All, All)

//Constructor
APAPlayerCharacter::APAPlayerCharacter() 
{
    PrimaryActorTick.bCanEverTick = true;

    //Creating camera in scene
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());

    //Creating stamina in scene
    StaminaComponent = CreateDefaultSubobject<UPAStaminaComponent>("StaminaComponent");

    //Creating Hook Dummy with relative locations
    HookMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HookMesh");
    HookMesh->SetupAttachment(CameraComponent);

    //Creating Musket Dummy with relative locations
    MusketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MusketMesh");
    MusketMesh->SetupAttachment(CameraComponent);
}

//Called when the game starts
void APAPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();
    
    //Bind the OnStaminaChanged event to the OnStaminaChanged function in this class
    StaminaComponent->OnStaminaChanged.AddUObject(this, &APAPlayerCharacter::OnStaminaChanged);
    SpawnMusket();
    SpawnHook();
}

//Method for game bindings
void APAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Movement axis bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &APAPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APAPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APAPlayerCharacter::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &APAPlayerCharacter::TurnAround);

    //Action bindings
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APAPlayerCharacter::StartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &APAPlayerCharacter::StopRunning);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APAPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APAPlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APAPlayerCharacter::StopCrouch);
    PlayerInputComponent->BindAction("MusketShot", IE_Pressed, this, &APAPlayerCharacter::MusketShot);
    PlayerInputComponent->BindAction("MusketReload", IE_Pressed, this, &APAPlayerCharacter::MusketReload);
    PlayerInputComponent->BindAction("HookHit", IE_Pressed, this, &APAPlayerCharacter::HookHit);

}

//Called every tick when the game starts
void APAPlayerCharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (StaminaComponent && !StaminaComponent->CanRun())
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

//Move forward-backward
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

//Move left-right
void APAPlayerCharacter::MoveRight(float Amount) 
{
    if (Amount != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Amount);
    }
}

//Look up-down
void APAPlayerCharacter::LookUp (float Amount)
{
    AddControllerPitchInput(Amount);
}

//Look left-right
void APAPlayerCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(Amount);

} 

//Method of stamina change
void APAPlayerCharacter::OnStaminaChanged(float Stamina)
{
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
    if (StaminaComponent && StaminaComponent->CanRun() && bIsMovingForward)
    {
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
        bIsRunning = false;
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        StaminaComponent->StopDrainingStamina();
        StaminaComponent->RecoverStamina();
    }
}

void APAPlayerCharacter::StartCrouch()
{
    Crouch();
}

void APAPlayerCharacter::StopCrouch() 
{
    UnCrouch();
}

void APAPlayerCharacter::SpawnMusket()
{

    Musket = GetWorld()->SpawnActor<APAMusket>(MusketClass);
    if (!Musket) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Musket->AttachToComponent(MusketMesh, AttachmentRules, "");
}

void APAPlayerCharacter::SpawnHook()
{
    Hook = GetWorld()->SpawnActor<APAHook>(HookClass);
    if (!Hook) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Hook->AttachToComponent(HookMesh, AttachmentRules, "");
}

void APAPlayerCharacter::MusketShot()
{
   Musket->Fire();
}

void APAPlayerCharacter::MusketReload()
{
   Musket->Reload();
}

void APAPlayerCharacter::HookHit()
{
   Hook->MakeHit();
}

void APAPlayerCharacter::OnDeath()
{
    Super::OnDeath();

    Musket->Destroy();
    Hook->Destroy();
}