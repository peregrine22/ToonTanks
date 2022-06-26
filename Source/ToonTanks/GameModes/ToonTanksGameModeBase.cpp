// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// Get references and game win/lose conditions/

	// Call HandleGameStart() to initialize the start countdown, turret activasion, pawn check, etc
}


void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	// check what actor died. if turret - tally, if player -> go to lose condition
}

void AToonTanksGameModeBase::HandleGameStart()
{
	// initialize the start countdown, turret activasion, pawn check, etc
	// call blueprint version GameStart();
}

void AToonTanksGameModeBase::HandleGameOver(bool PlayerWon)
{
	// see if the player has destroyed all the turrets, show win result
	// else if a turret has destroyed player -> show lose result
	// call blueprint version GameOver(boole).
}
