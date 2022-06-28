// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get references and game win/lose conditions/
	HandleGameStart();
}


void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	// check what actor died. if turret - tally, if player -> go to lose condition
	UE_LOG(LogTemp, Warning, TEXT("A pawn Died"));
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerController)
		{
			PlayerController->SetPlayerEnabled(false);
		}
	}
	else if(APawnTurret* destroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		destroyedTurret->HandleDestruction();
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

int32 AToonTanksGameModeBase::GetTurretCurrentCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

void AToonTanksGameModeBase::HandleGameStart()
{
	// initialize the start countdown, turret activasion, pawn check, etc

	TargetTurrets = GetTurretCurrentCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerController)
	{
		PlayerController->SetPlayerEnabled(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabled, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

void AToonTanksGameModeBase::HandleGameOver(bool PlayerWon)
{
	// see if the player has destroyed all the turrets, show win result
	// else if a turret has destroyed player -> show lose result
	// call blueprint version GameOver(boole).
	GameOver(PlayerWon);
}
