// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component")); 
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	Healthcomponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APawnBase::RotateTurret(FVector Target)
{
	// update turretmesh rotation to face towards the target passed in from child class
	// turretmesh->setworldlocation
	FVector targetCalculated = FVector(Target.X, Target.Y, TurretMesh->GetComponentLocation().Z);
	FVector startLocation = TurretMesh->GetComponentLocation();
	FRotator turretRotation = FVector(targetCalculated - startLocation).Rotation();
	TurretMesh->SetWorldRotation(turretRotation);
}

void APawnBase::Fire()
{
	// get projectile location && rotation -> spawn projectile class at location firing towards location
	if (Projectile)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		 
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile, SpawnLocation, SpawnRotation);
		tempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	// play death effect particle
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DestructionShake);

	// -- pawnturret - inform gamemodeturret died -> destroy self()

	// -- pawntank - inform gamemode player died -> then hide() all components && stop movement input
}

