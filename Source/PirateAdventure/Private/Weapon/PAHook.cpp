// Pirate Adventure Game Vietokhin AD211

#include "Weapon/PAHook.h"
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HookLog, All, All)

APAHook::APAHook()
{
	PrimaryActorTick.bCanEverTick = false;

	HookMesh = CreateDefaultSubobject<USkeletalMeshComponent>("HookMesh");
	SetRootComponent(HookMesh);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(HookMesh);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APAHook::BeginPlay()
{
	Super::BeginPlay();
    CollisionComponent->OnComponentHit.AddDynamic(this, &APAHook::OnHit);
}

void APAHook::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APAHook::MakeHit()
{
	if (!bCanHit) return;

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PlayAttackAnimation();
	PlayAttackSound();

	bCanHit = false;
	GetWorldTimerManager().SetTimer(HookHitDelayTimerHandle, this, &APAHook::EnableHit, HookHitDelay, false);
}

void APAHook::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor == nullptr || OtherActor == this) return;
    UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, Hit.ImpactNormal, Hit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, nullptr);
}

void APAHook::PlayAttackAnimation()
{
	if (!AttackAnimation) return;
	HookMesh->PlayAnimation(AttackAnimation, false);
}

void APAHook::PlayAttackSound()
{
	if (!AttackSound) return;
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
}

void APAHook::EnableHit()
{
	bCanHit = true;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
