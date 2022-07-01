// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksAIController.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToonTanksAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Enemy %s: %s"), *GetName(), *PlayerPawn->GetName());

	SetFocus(PlayerPawn);
	MoveToActor(PlayerPawn, 100);
}
