// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawnturret.h"
#include "PawnEnemyTank.generated.h"

UCLASS()
class TOONTANKS_API APawnEnemyTank : public APawnTurret
{
	GENERATED_BODY()

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
