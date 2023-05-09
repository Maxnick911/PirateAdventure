// Pirate Adventure Game Vietokhin AD211


#include "Character/Player/PAPlayerCharacter.h"
#include "Character/PABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PAStaminaComponent.h"
#include "Weapon/PAMusketProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerLog, All, All)

APAPlayerCharacter::APAPlayerCharacter() 
{
    PrimaryActorTick.bCanEverTick = true;

    //�������� � �������� ������
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());
    check(CameraComponent != nullptr);

    //�������� ���������� �������������
    StaminaComponent = CreateDefaultSubobject<UPAStaminaComponent>("StaminaComponent");

    //�������� � �������� ���� �����
    HookMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HookMesh");
    HookMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    HookMesh->CastShadow = false;
    check(HookMesh != nullptr);

    //�������� � �������� ���� �������
    MusketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MusketMesh");
    MusketMesh->AttachToComponent(CameraComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    MusketMesh->CastShadow = false;
    check(MusketMesh != nullptr);

}

//�����, ���������� � ������ �������� ��������
void APAPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();

    //����������� �������� ������� OnStaminaChanged
    StaminaComponent->OnStaminaChanged.AddUObject(this, &APAPlayerCharacter::OnStaminaChanged);
}

//����� ������� �� �������
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

//����� ������������ ������ ��� ����.
void APAPlayerCharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (StaminaComponent && !StaminaComponent->CanRun())
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

//����� �������� �����-�����
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

//����� �������� ������-�����
void APAPlayerCharacter::MoveRight(float Amount) 
{
    if (Amount != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Amount);
    }
}

//����� ������������� �������� ������
void APAPlayerCharacter::LookUp (float Amount)
{
    AddControllerPitchInput(Amount);
}

//����� ��������������� �������� ������
void APAPlayerCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(Amount);

} 

//����� ��������� ������������
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

//����� ������ ����
void APAPlayerCharacter::StartRunning()
{
    if (StaminaComponent && StaminaComponent->CanRun() && bIsMovingForward)
    {
        UE_LOG(PlayerLog, Display, TEXT("Start Running"));
        bIsRunning = true;
        GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
        StaminaComponent->StopRecoveringStamina();
        StaminaComponent->DrainStamina();
    }
}

//����� ��������� ����
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

//����� ������ ����������
void APAPlayerCharacter::StartCrouch()
{
    Crouch();
}

//����� ��������� ����������
void APAPlayerCharacter::StopCrouch() 
{
    UnCrouch();
}

//����� �������� ������� �� �������
void APAPlayerCharacter::MusketShot() 
{
    const FTransform SpawnTransform(MusketMesh->GetSocketRotation("MuzzleSocket"), MusketMesh->GetSocketLocation("MuzzleSocket"));
    APAMusketProjectile* Projectile = GetWorld()->SpawnActorDeferred<APAMusketProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        FVector Direction = MusketMesh->GetSocketRotation("MuzzleSocket").Vector();
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    if (MusketShotSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, MusketShotSound, MusketMesh->GetSocketLocation("MuzzleSocket"));
    }
}

//����� ����� ������
void APAPlayerCharacter::HookHit()
{
    UE_LOG(PlayerLog, Warning, TEXT("HIT"));

    if (HookHitSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, HookHitSound, GetActorLocation());
    }
}