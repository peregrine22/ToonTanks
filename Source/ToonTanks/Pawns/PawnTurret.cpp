// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireConditions, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || GetDistanceToPlayer() > FireRange) 
		return;

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireConditions()
{
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
		return;
			
	//TODO: check if player is in range - fire!
	if (GetDistanceToPlayer() <= FireRange) 
	{
		Fire();
	}
}

float APawnTurret::GetDistanceToPlayer()
{
	if (!PlayerPawn)
		return 0.0f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}


void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
