// Fill out your copyright notice in the Description page of Project Settings.
 
#include "PawnEnemyTank.h"

void APawnEnemyTank::BeginPlay()
{
	Super::BeginPlay();
}

void APawnEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnEnemyTank::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

